# Copilot instructions (BankII.cpp)

## Project snapshot
- This repo is currently a single-file C++ program: [Requirments.cpp](Requirments.cpp).
- VS Code workflow is preconfigured via [.vscode/tasks.json](.vscode/tasks.json) and [.vscode/launch.json](.vscode/launch.json).

## Build & run (macOS)
- Preferred: use the VS Code task **“C/C++: clang build active file”** (it compiles the currently open file).
- CLI equivalent for the current program:
  - Build: `clang++ -std=c++17 -g Requirments.cpp -o Requirments`
  - Run: `./Requirments`

## Debugging
- Use the VS Code launch config **“C/C++: clang build and debug active file”** in [.vscode/launch.json](.vscode/launch.json).
- It uses LLDB (`MIMode: lldb`) and runs the binary produced next to the source file.

## Code conventions found in this repo
- Entry point is `int main()` in [Requirments.cpp](Requirments.cpp).
- The program currently uses `<iostream>` and prints with `std::cout` via `using namespace std;`.
- Keep changes minimal and consistent with the existing style (simple console I/O).

## When adding more C++ files
- This workspace’s task/debug setup is **“active file”** based; it will not automatically build a multi-file project.
- If you introduce additional `.cpp`/`.h` files that must compile together, update:
  - [.vscode/tasks.json](.vscode/tasks.json) to compile/link all required sources, and
  - [.vscode/launch.json](  {
    // ...existing code...
    "configurations": [
      {
        // ...existing code...
        "console": "integratedTerminal",
        "internalConsoleOptions": "neverOpen"
        // ...existing code...
      }
    ]
  }) if the output binary name/path changes.

## What to optimize for
- Prefer changes that preserve the VS Code task/debug flow (compile to `${fileBasenameNoExtension}` in the same folder).
- If you refactor into multiple translation units, keep the build command explicit in the task so others can reproduce it.
