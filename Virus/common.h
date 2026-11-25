#pragma once

#ifdef _WIN32
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif
  #include <Windows.h>
#else
  #include <unistd.h>
  #ifdef __APPLE__
    #include <mach-o/dyld.h>
  #endif
#endif

#include <filesystem>
#include <string>
#include <system_error>

namespace fs = std::filesystem;

#ifdef _WIN32
  inline constexpr const char* VAULT_NAME = "VirusHiddenFiles";
#else
  inline constexpr const char* VAULT_NAME = ".VirusHiddenFiles";
#endif
inline constexpr const char* MANIFEST_NAME = "manifest.dat";

// ---------- self path ----------
inline fs::path selfPath() {
#ifdef _WIN32
    wchar_t buf[MAX_PATH];
    DWORD n = GetModuleFileNameW(nullptr, buf, MAX_PATH);
    return n ? fs::path(std::wstring(buf, n)) : fs::path{};
#elif defined(__APPLE__)
    char buf[4096];
    uint32_t size = sizeof(buf);
    if (_NSGetExecutablePath(buf, &size) != 0) return {};
    std::error_code ec;
    fs::path p = fs::canonical(buf, ec);
    return ec ? fs::path{} : p;
#else
    std::error_code ec;
    fs::path p = fs::read_symlink("/proc/self/exe", ec);
    return ec ? fs::path{} : p;
#endif
}

inline fs::path selfDirectory() {
    fs::path p = selfPath();
    return p.empty() ? fs::current_path() : p.parent_path();
}

// ---------- hide / unhide ----------
// Returns the path to use after the operation.
// Windows: unchanged (attribute changes in place).
// Unix:    possibly renamed to ".name"; caller must use the return value.
inline fs::path hideFile(const fs::path& p) {
#ifdef _WIN32
    DWORD a = GetFileAttributesW(p.c_str());
    if (a != INVALID_FILE_ATTRIBUTES)
        SetFileAttributesW(p.c_str(), a | FILE_ATTRIBUTE_HIDDEN);
    return p;
#else
    std::string name = p.filename().string();
    if (name.empty() || name[0] == '.') return p;       // already hidden
    fs::path hidden = p.parent_path() / ("." + name);
    std::error_code ec;
    fs::rename(p, hidden, ec);
    return ec ? p : hidden;
#endif
}

inline fs::path unhideFile(const fs::path& p) {
#ifdef _WIN32
    DWORD a = GetFileAttributesW(p.c_str());
    if (a != INVALID_FILE_ATTRIBUTES)
        SetFileAttributesW(p.c_str(), a & ~FILE_ATTRIBUTE_HIDDEN);
    return p;
#else
    std::string name = p.filename().string();
    if (name.size() < 2 || name[0] != '.') return p;    // not hidden
    fs::path visible = p.parent_path() / name.substr(1);
    std::error_code ec;
    fs::rename(p, visible, ec);
    return ec ? p : visible;
#endif
}

inline bool isAlreadyHidden(const fs::path& p) {
#ifdef _WIN32
    DWORD a = GetFileAttributesW(p.c_str());
    return a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_HIDDEN) != 0;
#else
    std::string name = p.filename().string();
    return !name.empty() && name[0] == '.';
#endif
}

inline bool startsWithDot(const fs::path& p) {
    std::string name = p.filename().string();
    return !name.empty() && name[0] == '.';
}