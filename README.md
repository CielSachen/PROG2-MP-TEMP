# Simple Translator

## Compilation

### Windows

```bash
cmake -B ./build/ -S ./
cmake --build ./build --target all
```

### macOS

> [!IMPORTANT]
> The Homebrew installed versions of gcc and g++ make are named `gcc-14` and `g++-14`, respectively.

```bash
cmake -DCMAKE_C_COMPILER:FILEPATH=/usr/local/bin/gcc-14 -DCMAKE_CXX_COMPILER:FILEPATH=/usr/local/bin/g++-14 -B ./build/ -S ./
cmake --build ./build --target all
```

## Usage

> [!WARNING]
> This CLI game uses UTF-8 characters, which Powershell (in Windows) does not fully support yet. To allow Powershell to display UTF-8 characters, run this script before running the game:
>
> ```pwsh
> $OutputEncoding = [console]::InputEncoding = [console]::OutputEncoding = New-Object System.Text.UTF8Encoding
> ```

```bash
./build/src/a.out
```

---

<img src="https://upload.wikimedia.org/wikipedia/en/thumb/c/c2/De_La_Salle_University_Seal.svg/2048px-De_La_Salle_University_Seal.svg.png" alt="DLSU Seal" height="125px"> <img src="https://www.dlsu.edu.ph/wp-content/uploads/2019/06/ccs-logo.png" alt="CCS Logo" height="125px">

## De La Salle University (Undergraduate)

This repository contains the source code of my machine project for **Logic Formulation and Introductory Programming** (Term 1, A.Y. 2024-25).
