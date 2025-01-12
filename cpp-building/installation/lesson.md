# C++ Installation

**Author:** *Brian Magnuson*

In this lesson, we will cover how to set up a C++ development environment on your computer. We will briefly touch on various C++ compilers and text editors before covering GCC installation and usage.

In this lesson, we will cover:
- C++ compilers
- Text editors
- GCC installation
- GCC usage

# Introduction

To start programming in C++, you need two things: a compiler and a text editor.
There are many options for both, so we'll touch on a few of the most popular ones.

# C++ Compilers

Unlike Java, Rust, or Go, the C++ language does not have a single compiler that is considered the "official" compiler. Rather, there are sevaral compilers, each designed to comply with the C++ ISO standard. The ones you'll most likely encounter are GCC, Clang, and MSVC.

## GNU Compiler Collection (GCC)

- **License:** GNU General Public License v3.0
- **Platforms:** Linux, macOS, Windows

Originally the GNU C Compiler, GCC is a free and open-source collection of compilers for various programming languages, including C, C++, Objective-C, Fortran, Ada, D, and Go. 
It was developed for the GNU operating system and is the default compiler for most Unix-like operating systems.
It can be installed on Windows using GNU ports such as MinGW or Cygwin.

## Clang

- **License:** Apache License 2.0
- **Platforms:** Linux, macOS, Windows

Clang provides a language front-end for C, C++, Objective C/C++, OpenCL, and CUDA. 
It was developed for the LLVM project and is designed to be compatible with GCC and MSVC.
In many cases, it can be used as a drop-in replacement for GCC.
It is the default compiler for macOS and can be installed on Windows using MSYS2.

## Microsoft Visual C++ (MSVC)

- **License:** Proprietary
- **Platforms:** Windows

MSVC is the official compiler for Microsoft's Visual Studio IDE. It is used to develop many Windows applications and integrates well with the Visual Studio debugger and other tools.

------

These compilers each provide some version of the C++ standard library (`libstdc++` for GCC and `libc++` for Clang, for example). You can use any of these to compile C++ code; the differences between them are mostly in performance, command-line options, compatibility with other tools, debugging tools, and error messages (there are more differences, but these are the ones you'll most likely notice). For this lesson, we'll focus on GCC, which can be installed on most platforms.

# Text Editors

A text editor is a program that allows you to write and edit text files. Some guides may use terms like **IDE (Integrated Development Environment)** or **code editor**. These are essentially text editors with additional features like syntax highlighting, code completion, and debugging tools.

Everyone has their opinion what text editor is best, so I won't spend much time arguing for one over another.

**For quick edits**
- [Notepad++](https://notepad-plus-plus.org/)
  - GUI text editor for Windows
  - Free and open-source
- [GNU nano](https://www.nano-editor.org/)
  - Terminal-based text editor for Unix-like systems
  - Can be installed on Windows using GNU ports
  - Free and open-source

**Lightweight code editors**
- [Visual Studio Code](https://code.visualstudio.com/)
  - GUI text editor for Windows, macOS, Linux
  - Free, built on open-source
  - Highly extensible
- [VSCodium](https://vscodium.com/)
  - GUI text editor for Windows, macOS, Linux
  - Free, open-source
  - Like Visual Studio Code, but just the open-source binaries
- [Sublime Text](https://www.sublimetext.com/)
  - GUI text editor for Windows, macOS, Linux
  - Free to try, purchase license for continued use

**For those who like the terminal**
- [Vim](https://www.vim.org/)
  - Terminal-based text editor for Unix-like systems
  - Can be installed on Windows using GNU ports
  - Free and open-source
- [Neovim](https://neovim.io/)
  - Terminal-based text editor for Unix-like systems
  - Can be installed on Windows using GNU ports
  - Free and open-source
  - Like Vim, but highly extensible with Vimscript and Lua
- [GNU Emacs](https://www.gnu.org/software/emacs/)
  - Terminal-based text editor for Unix-like systems
  - Can be installed on Windows using GNU ports
  - Free and open-source

**Full-featured IDEs**
- [Visual Studio](https://visualstudio.microsoft.com/)
  - GUI IDE for Windows
  - Free Community edition, paid Professional and Enterprise editions
- [CLion](https://www.jetbrains.com/clion/)
  - GUI IDE for Windows, macOS, Linux
  - Free for students, paid for professionals
- [Other JetBrains IDEs](https://www.jetbrains.com/products/)
  - GUI IDEs for various languages and platforms
  - Free for students, paid for professionals
  - Less C++-support, but still useful for development.
  - IntelliJ IDEA (Java), PyCharm (Python), WebStorm (JavaScript), RustRover (Rust), and Rider (.NET) are available for free for non-commercial use.

Just to make sure we're on the same page, a word processor is NOT a text editor.

Maybe your favorite text editor isn't listed here. You're welcome to use whatever text editor you like. If you're not sure which one to use, I recommend Visual Studio Code. It's free, highly extensible, and great for most programming tasks (not just C++).

# GCC Installation

This next section will cover how to install GCC on your Windows, macOS, and Linux systems.

## Linux

Most Linux distributions provide GCC in their package repositories. You can install them using your package manager.

Open your terminal and run the installation command(s) for your distribution:

### Debian-based systems (Debian, Ubuntu, Mint)

```bash
sudo apt update
sudo apt install build-essential
```

If you already have GCC installed, you can update it using the following command:

```bash
sudo apt upgrade gcc
```

### Red Hat-based systems (Fedora, CentOS, RHEL)

```bash
sudo dnf install gcc
```

If you already have GCC installed, you can update it using the following command:

```bash
sudo dnf upgrade gcc
```

### Arch-based systems (Arch, Manjaro)

```bash
sudo pacman -Syu gcc
```

If you already have GCC installed, you can update it using the same command as above.

------

In addition to GCC, you may be interested in installing these packages:
- `gdb` for debugging
- `make` for building projects
- `valgrind` for memory debugging
- `clang` for an alternative compiler

## macOS

Mac users can install GCC using the Homebrew package manager. If you prefer to use Clang instead of GCC, you can install the Xcode Command Line Tools.

### GCC via Homebrew

If you don't have Homebrew installed, you can install it by running the following command in your terminal:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Once you have Homebrew installed, you can install GCC using the following command:

```bash
brew update
brew install gcc
```

If you already have GCC installed, you can update it using the following command:

```bash
brew upgrade gcc
```

### Clang via Xcode Command Line Tools

Clang can be used as a drop-in replacement for GCC on macOS. You can install the Xcode Command Line Tools by running the following command in your terminal:

```bash
xcode-select --install
```

This will install Clang, `make`, and other development tools.

## Windows

Installing GCC on Windows can be a bit more complicated than on Linux or macOS. For this lesson, I'll be following [this guide](https://code.visualstudio.com/docs/cpp/config-mingw#_prerequisites), which uses MSYS2 to install GCC. Although this guide is for Visual Studio Code, you can use MSYS2 with any text editor.

Windows users also have the option to use Windows Subsystem for Linux (WSL) to install GCC. WSL provides a full Linux environment on Windows. Learn how to install WSL [here](https://learn.microsoft.com/en-us/windows/wsl/install). If you choose to use WSL, you may also want a text editor that can connect to WSL, like Visual Studio Code. You can follow VSCode's guide [here](https://code.visualstudio.com/docs/remote/wsl).

**Step 1:** Install MSYS2

You can install it from the [MSYS2 website](https://www.msys2.org/). Download the installer and run it. You can choose the default options for the installation. 

The files for MSYS2 will be installed in a directory like `C:\msys64`. If you'd like to start over, you can delete this directory and run the installer again.

**Step 2:** Open an MSYS2 terminal

MSYS2 provides multiple environments for building software. If you don't know which one to use, you can use the UCRT64 environment. If the terminal did not open automatically, you can find it in the Start menu or by running `C:\msys64\msys2.exe`.

**Step 3:** Install GCC (and other tools)

You can install GCC and other tools using the following command:

```bash
pacman -Syu mingw-w64-ucrt-x86_64-gcc
```

If you already have GCC installed, you can update it using the same command as above. You can also update all installed packages using the following command:

```bash
pacman -Syu
```

In addition to GCC, you may be interested in installing these packages:
- `mingw-w64-ucrt-x86_64-gdb` for debugging
- `make` for building projects

Note: if you install `mingw-w64-ucrt-x86_64-make` instead of `make`, you may need to use `mingw32-make` instead of `make` in your Makefiles.

**Step 4:** Update your PATH

In the Windows search bar, type "Environment Variables" and select "Edit the system environment variables". In the System Properties window, click the "Environment Variables" button. In the Environment Variables window, select the "Path" variable in the "System variables" section and click the "Edit" button. Click the "New" button to add a new entry to the PATH.

I recommend adding the following directories to your PATH:
- `C:\msys64\ucrt64\bin`
- `C:\msys64\usr\bin`

Note that adding the second entry to your PATH may result in many GNU utilities (like `ls`, `grep`, and `sed`) being available in your Command Prompt or PowerShell.

**Step 5:** Restart any open terminals

If you had any terminals open before updating your PATH, you'll need to close and reopen them to see the changes. If you're using a program with an integrated terminal (like Visual Studio Code), you may need *close* the program completely and reopen it.

If this doesn't work, try restarting your computer.

After this, you should have GCC set up. You can test it by running `gcc --version` in your terminal.

# GCC Usage

At this point, you should have GCC installed on your system. You can check your installation by running this command:
```bash
gcc --version
```

We'll now cover how to compile and run a simple C++ program using GCC.

Create a new file on your computer called `main.cpp` and add the following code:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
```

To compile this program, navigate to the directory containing `main.cpp` in your terminal and run the following command:

```bash
g++ main.cpp
```

This should create an executable with the default name (something like `a.exe` or `a.out`).

If you have multiple source files to compile, you can list them all in the command:

```bash
g++ main.cpp other.cpp
```

If you want to specify the name of the output file, you can use the `-o` flag followed by the desired name:

```bash
g++ main.cpp -o main
```

On Windows, this will create an executable named `main.exe`. Unix-like systems may just have `main` without an extension.

You can then run the executable by typing its name in the terminal:
```bash
./main
```

If compilation was successful, you should see `Hello, world!` printed to the terminal.

To enable debugging information, you can use the `-g` flag:

```bash
g++ main.cpp -g -o main
```

This leaves debugging information in the executable, which can be useful for debugging with GDB. However, it can be a security risk, so you may want to remove it if you're releasing the program publicly.

To specify the C++ standard to use, you can use the `-std` flag:

```bash
g++ main.cpp -std=c++14 -o main
```

This ensures that only features up to C++14 are used.

There are various warning options you can use with GCC. Here, we'll use `-Wall` to enable most warnings:

```bash
g++ main.cpp -Wall -o main
```

This will show more warnings than the default settings. Here are a few more warning options you can use:
- `-Wextra` to enable more warnings than `-Wall`
- `-Werror` to treat warnings as errors (errors will stop the compilation)
- `-Wuninitialized` to warn about uninitialized variables
- `-pedantic` to warn about non-standard C++ code

To prevent the compiler from automatically linking the compiled object files, you can use the `-c` flag:

```bash
g++ main.cpp -c -o main.o
```

Here, I name the output file `main.o` to indicate that it's an object file. You can then link the object file(s) together to create an executable:

```bash
g++ main.o -o main
```

This is useful when you want to compile multiple source files separately and then link them together.

## Including Libraries

You likely won't need to include external libraries for simple programs, but for the sake of completeness, I've provided the options here:

To include a library in a standard location, you can use the `-l` flag followed by the library name:

```bash
g++ main.cpp -lmymath -o main
```

Note that static libraries tend to have the prefix `lib` but the option to link the library excludes this prefix. In this example, the library file is `libmymath.a` and the option to link it is `-lmymath`.

If the library is in a non-standard location, you can use the `-L` flag followed by the directory containing the library:

```bash
g++ main.cpp -L/usr/local/lib -lmymath -o main
```

If the header files for the library are in a non-standard location, you can use the `-I` flag followed by the directory containing the header files:

```bash
g++ main.cpp -I/usr/local/include -o main
```

# Conclusion

In this lesson, we discussed C++ compilers and text editors. We then covered how to install GCC on Linux, macOS, and Windows. Finally, we discussed how to compile and run a simple C++ program using GCC.

As a side note, you may prefer to use a build system like CMake or Ninja instead of compiling your programs directly with GCC. These build systems can automate the compilation process and make it easier to manage large projects.

# References

- [GCC](https://gcc.gnu.org/)
- [Clang](https://clang.llvm.org/)
