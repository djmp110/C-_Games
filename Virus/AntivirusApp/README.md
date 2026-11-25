# Antivirus restore demo

This executable looks for the `VirusHiddenFiles` vault in a target directory (the executable's folder by default), reads `manifest.dat`, restores saved files to their original paths, and removes the stored copies.

Build from this directory: `g++ -std=c++17 antivirus.cpp -o antivirus`

Run with a sandbox path: `./antivirus ../sandbox`
