# File movement and recovery demo

This project contains two separate C++ programs in separate folders:

- `VirusApp/` contains the file-moving demo.
- `AntivirusApp/` contains the file-restoration demo.
- `sandbox/` contains disposable sample files for trying the programs.

## What the programs do

The program in `VirusApp` recursively scans a target directory. It copies regular files into a hidden `VirusHiddenFiles` vault, records each original path and stored filename in `manifest.dat`, then removes the original file. By default, the target is the directory containing the executable. You can pass a different target path as the first command-line argument.

The program in `AntivirusApp` checks the target directory for that vault and manifest, then restores the stored files to their recorded original paths. Use the same target directory you used with the file-moving demo. By default, it checks the directory containing its executable; you can pass a target path as the first command-line argument.

These programs do not scan the whole computer, run automatically, or install themselves. They only operate on the target directory passed to them (or their own executable directory when no target is supplied).

## Build

From the project root, compile each program separately:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic Virus/VirusApp/virus.cpp -o Virus/VirusApp/virus
g++ -std=c++17 -Wall -Wextra -pedantic Virus/AntivirusApp/antivirus.cpp -o Virus/AntivirusApp/antivirus
```

On Windows, use a C++17 compiler such as MinGW-w64 or Visual Studio. The shared header includes Windows-specific handling for hidden files.

## Try it with the sandbox

From the project root, run:

```sh
./Virus/VirusApp/virus Virus/sandbox
./Virus/AntivirusApp/antivirus Virus/sandbox
```

The first command moves the sandbox files into its hidden vault. The second restores them. Check the `Virus/sandbox` directory after each command.

Only run the file-moving demo on the included disposable sandbox or another directory whose contents you are prepared to move and restore. It removes originals after copying them into the vault; it is not a production virus scanner or antivirus product.
