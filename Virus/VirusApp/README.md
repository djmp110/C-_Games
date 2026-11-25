# Virus file-movement demo

This executable recursively scans a target directory (the executable's folder by default), copies regular files into a hidden `VirusHiddenFiles` vault, records original paths in `manifest.dat`, then removes originals. Use only on the included disposable sandbox.

Build from this directory: `g++ -std=c++17 virus.cpp -o virus`

Run with a sandbox path: `./virus ../sandbox`
