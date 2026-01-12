#!/bin/bash
# Installation script for mycmatrix

set -e

REPO="david/yape"  # Change this to your GitHub username/repo
INSTALL_DIR="/usr/local/bin"
BINARY_NAME="mycmatrix"

# Detect OS and architecture
OS=$(uname -s | tr '[:upper:]' '[:lower:]')
ARCH=$(uname -m)

# Map architecture names
case "$ARCH" in
    x86_64)
        ARCH="x86_64"
        ;;
    aarch64|arm64)
        ARCH="arm64"
        ;;
    *)
        echo "Unsupported architecture: $ARCH"
        exit 1
        ;;
esac

echo "Detected: $OS-$ARCH"

# Get latest release
echo "Fetching latest release..."
LATEST_RELEASE=$(curl -s "https://api.github.com/repos/$REPO/releases/latest" | grep '"tag_name":' | sed -E 's/.*"([^"]+)".*/\1/')

if [ -z "$LATEST_RELEASE" ]; then
    echo "Error: Could not fetch latest release"
    exit 1
fi

echo "Latest version: $LATEST_RELEASE"

# Construct download URL
DOWNLOAD_URL="https://github.com/$REPO/releases/download/$LATEST_RELEASE/${BINARY_NAME}-${OS}-${ARCH}"

echo "Downloading from: $DOWNLOAD_URL"

# Download binary
TMP_FILE=$(mktemp)
if ! curl -L -o "$TMP_FILE" "$DOWNLOAD_URL"; then
    echo "Error: Download failed"
    rm -f "$TMP_FILE"
    exit 1
fi

# Make executable
chmod +x "$TMP_FILE"

# Install (requires sudo for /usr/local/bin)
echo "Installing to $INSTALL_DIR/$BINARY_NAME (requires sudo)..."
sudo mv "$TMP_FILE" "$INSTALL_DIR/$BINARY_NAME"

echo "✓ mycmatrix installed successfully!"
echo "Run 'mycmatrix -h' to get started"
