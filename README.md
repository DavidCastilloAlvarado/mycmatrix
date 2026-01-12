# MyCMatrix

A Matrix-style digital rain terminal effect with customizable logo support, inspired by cmatrix.

## Features

- Matrix-style falling characters
- Characters concentrate and become bolder around the letters Y, A, P, E
- Creates a shaped effect where YAPE is visible through character density
- Real-time terminal animation using ncurses
- Customizable speed and appearance

## Requirements

- GCC compiler
- ncurses library

## Installation

Install ncurses development library (if not already installed):

```bash
# On Ubuntu/Debian
sudo apt-get install libncurses5-dev libncurses-dev

# On Fedora/RHEL
sudo dnf install ncurses-devel

# On Arch
sudo pacman -S ncurses
```

## Building

```bash
make
```

## Usage

Run the program:

```bash
./mycmatrix
```

Or:

```bash
make run
```

To quit, press `q`, `Q`, or `ESC`.

## How It Works

The program creates falling columns of characters (like in The Matrix movie). The characters are:
- **Very bold and bright** when they fall through the letter shapes of YAPE
- **Bold** when near the YAPE letters
- **Normal** at medium distance
- **Dim** when far from YAPE

This creates a visual effect where the word "YAPE" appears to be formed by the concentration and boldness of the falling Matrix characters.

## Installation (System-wide)

```bash
sudo make install
```

To uninstall:

```bash
sudo make uninstall
```

## License

MIT License - Feel free to modify and distribute!
