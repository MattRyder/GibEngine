#!/bin/bash

##
# Ensures g++-8 is setup and available
function setupCompiler() {
    sudo unlink /usr/bin/g++ && sudo ln -s /usr/bin/g++-8 /usr/bin/g++
    g++ --version
}

##
# Installs vcpkg
function installVcpkg() {
    cd $HOME
    git clone https://github.com/Microsoft/vcpkg.git
    cd vcpkg
    chmod +x ./bootstrap-vcpkg.sh
    ./bootstrap-vcpkg.sh
    git checkout 178517052f42d428bb2f304946e635d3c1f318e9 ports/fmt
    git checkout 2a0bf9c488d5291e82a37d19d4b0f81e79678f0d ports/spdlog
    git checkout 809eb64c97e6ec459cd1e1d601e916100395529e ports/cxxopts
    ./vcpkg install glfw3 assimp cxxopts json11 gtest sqlite3 spdlog glm
    ./vcpkg integrate install
}

##
# Grabs the prebuilt linux dep-bins
function grabVcpkgExport() {
    cd $HOME
    wget http://s3.gibengine.xyz/gibengine-ci/vcpkg/x64-linux/gibengine-vcpkg.7z
    7z x gibengine-vcpkg.7z
} 

##
# Installs the latest compatible version of Cmake
function installCmake() {
    cd $HOME
    wget https://cmake.org/files/v3.11/cmake-3.11.4-Linux-x86_64.sh
    sudo sh cmake-3.11.4-Linux-x86_64.sh --prefix=/usr/local --exclude-subdir
    cmake --version
}

function install() {
    setupCompiler

    installCmake
    
    # installVcpkg

    grabVcpkgExport
}

install
