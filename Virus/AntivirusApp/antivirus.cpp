#include "common.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

int main(int argc, char** argv) {
    fs::path target = (argc > 1) ? fs::path(argv[1]) : selfDirectory();
    fs::path vault  = target / VAULT_NAME;

    std::error_code ec;
    if (!fs::exists(vault, ec)) {
        std::cout << "[antivirus] no vault in " << target.string()
                  << " — system clean.\n";
        return 0;
    }

    vault = unhideFile(vault);

    fs::path manifestPath = vault / MANIFEST_NAME;
    if (!fs::exists(manifestPath)) {
        std::cerr << "[antivirus] vault found but manifest.dat missing — "
                     "cannot restore.\n";
        return 2;
    }

    std::ifstream manifest(manifestPath);
    std::string line;
    int restored = 0, failed = 0;

    while (std::getline(manifest, line)) {
        if (line.empty()) continue;

        std::istringstream entry(line);
        std::string originalName;
        std::string storedName;
        if (!(entry >> std::quoted(originalName) >> std::quoted(storedName))) { ++failed; continue; }

        fs::path original = fs::path(originalName);
        fs::path stored   = vault / storedName;

        if (!fs::exists(stored, ec)) {
            std::cerr << "[antivirus] payload missing for "
                      << original.string() << "\n";
            ++failed;
            continue;
        }

        stored = unhideFile(stored);

        // Rebuild any subfolders that no longer exist.
        fs::create_directories(original.parent_path(), ec);
        if (ec) {
            std::cerr << "[antivirus] cannot create "
                      << original.parent_path().string() << "\n";
            ec.clear(); ++failed; continue;
        }

        fs::copy_file(stored, original, fs::copy_options::overwrite_existing, ec);
        if (ec) {
            std::cerr << "[antivirus] restore failed: "
                      << original.string() << " (" << ec.message() << ")\n";
            ec.clear(); ++failed; continue;
        }

        fs::remove(stored, ec);             // remove the vault copy
        ec.clear();
        ++restored;
    }
    manifest.close();

    // Clean up: manifest, then the (now hopefully empty) vault.
    fs::remove(manifestPath, ec);
    ec.clear();
    fs::remove(vault, ec);                  // non-recursive on purpose
    if (ec) {
        std::cout << "[antivirus] note: vault not fully removed ("
                  << ec.message() << ") — unrecovered files may remain.\n";
    }

    std::cout << "[antivirus] restored " << restored
              << " file(s), " << failed << " failure(s).\n";
    return failed == 0 ? 0 : 3;
}
