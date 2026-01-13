# MyCMatrix

A customizable Matrix-style digital rain terminal effect with logo support, inspired by cmatrix.

![Matrix Effect](https://img.shields.io/badge/Matrix-Digital%20Rain-00ff00?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-lightgrey?style=flat-square)
![License](https://img.shields.io/badge/license-MIT-blue?style=flat-square)

## Features

- 🌈 **Customizable Colors**: Choose rain and logo colors from 7 different options
- 🖼️ **Custom Logo Support**: Display any image as a logo in the rain effect
- ⚡ **High Performance**: Optimized C code with ncurses
- 🎨 **Matrix Aesthetic**: Authentic Matrix-style falling characters
- 💻 **Cross-Platform**: Works on Linux and macOS
- 🔧 **Easy to Use**: Simple command-line interface

## Installation

### Quick Install (Linux/macOS)

Download and run the install script:

```bash
curl -sSL https://raw.githubusercontent.com/DavidCastilloAlvarado/mycmatrix/main/install.sh | bash
```

### Manual Installation

Download the latest release for your platform from the [releases page](https://github.com/DavidCastilloAlvarado/mycmatrix/releases/latest):

- **Linux x86_64**: `mycmatrix-linux-x86_64`
- **Linux ARM64**: `mycmatrix-linux-arm64`
- **macOS Intel**: `mycmatrix-macos-x86_64`
- **macOS Apple Silicon**: `mycmatrix-macos-arm64`

Make it executable and run:

```bash
chmod +x mycmatrix-*
./mycmatrix-*
```

### Build from Source

#### Requirements

- GCC compiler
- ncurses library
- make

#### Install Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev build-essential
```

**Fedora/RHEL:**
```bash
sudo dnf install ncurses-devel gcc make
```

**macOS:**
```bash
brew install ncurses
```

**Arch Linux:**
```bash
sudo pacman -S ncurses base-devel
```

#### Build

```bash
git clone https://github.com/DavidCastilloAlvarado/mycmatrix.git
cd mycmatrix
make
```

#### Install System-wide

```bash
sudo make install
```

## Usage

### Basic Usage

Run with default settings (green rain, yellow logo):

```bash
mycmatrix
```

### Color Options

Change rain color with `-C`:

```bash
mycmatrix -C red       # Red rain
mycmatrix -C blue      # Blue rain
mycmatrix -C cyan      # Cyan rain
mycmatrix -C yellow    # Yellow rain
mycmatrix -C white     # White rain
mycmatrix -C magenta   # Magenta rain
mycmatrix -C green     # Green rain (default)
```

Change logo color with `-L`:

```bash
mycmatrix -L cyan      # Cyan logo
mycmatrix -L red       # Red logo
mycmatrix -L white     # White logo
mycmatrix -L green     # Green logo
mycmatrix -L blue      # Blue logo
mycmatrix -L magenta   # Magenta logo
mycmatrix -L yellow    # Yellow logo (default)
```

Combine both:

```bash
mycmatrix -C blue -L cyan    # Blue rain with cyan logo
mycmatrix -C red -L white    # Red rain with white logo
```

### Help

```bash
mycmatrix -h
```

### Exit

Press `q`, `Q`, or `ESC` to exit.

## Custom Logo

To use your own logo image:

1. Place your image in the `script/` directory
2. Install Python dependencies:
   ```bash
   cd script
   poetry install
   ```
3. Run the conversion script:
   ```bash
   poetry run python demo.py
   ```
4. Copy the generated array into `mycmatrix.c`
5. Update `YAPE_HEIGHT` and `YAPE_WIDTH` defines
6. Rebuild: `make clean && make`

## Examples

```bash
# Classic Matrix look
mycmatrix -C green -L white

# Cyberpunk style
mycmatrix -C cyan -L magenta

# Fire effect
mycmatrix -C red -L yellow

# Ocean theme
mycmatrix -C blue -L cyan
```

## Performance

MyCMatrix is designed to be lightweight and efficient:
- Low CPU usage (~3-5%)
- Minimal memory footprint
- Smooth animation at 25 FPS
- Scales to any terminal size

## Development

### Project Structure

```
mycmatrix/
├── mycmatrix.c           # Main source code
├── Makefile              # Build configuration
├── README.md             # This file
├── .gitignore           # Git ignore rules
├── install.sh           # Installation script
├── script/              # Logo conversion tools
│   ├── demo.py          # Image to C array converter
│   └── pyproject.toml   # Python dependencies
└── .github/
    └── workflows/
        └── release.yml  # GitHub Actions CI/CD
```

### Building for Development

```bash
make clean
make
./mycmatrix
```

### Running Tests

```bash
make run
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## Credits

Inspired by [cmatrix](https://github.com/abishekvashok/cmatrix) by Chris Allegretta and Abishek V Ashok.

## License

MIT License - see LICENSE file for details

## Author

David Castillo Alvarado - [@DavidCastilloAlvarado](https://github.com/DavidCastilloAlvarado)

---

⭐ Star this repo if you like it!

🐛 Found a bug? [Open an issue](https://github.com/DavidCastilloAlvarado/mycmatrix/issues)
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
