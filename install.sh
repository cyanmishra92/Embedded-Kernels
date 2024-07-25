#!/bin/bash

set -e

# Function to install packages
install_packages() {
    sudo apt-get update
    sudo apt-get install -y build-essential gcc-arm-linux-gnueabi g++-arm-linux-gnueabi
}

# Check and install dependencies
echo "Checking and installing dependencies..."
install_packages
echo "All dependencies are installed."

