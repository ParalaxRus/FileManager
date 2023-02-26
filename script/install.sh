#!/bin/bash

echo "Make sure you've udpated OS with 'sudo apt update'"

apt -y update
apt -y install git
apt -y install g++
apt-get -y install libboost-all-dev
apt-get -y install cmake

git clone https://github.com/ParalaxRus/FileManager.git
cd FileManager/

mkdir build
cd build/
cmake .. || exit 1

cmake --build . || exit 1

ctest || exit 1

pkgvar=$(cpack | grep -Po 'FileManagerPrj.*deb' | xargs -L 1 basename)
dpkg --install $pkgvar

echo "filemanager tool should be located in the 'home' folder"
