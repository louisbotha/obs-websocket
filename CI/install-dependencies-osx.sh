#!/bin/sh
set -ex

# OBS Studio deps
brew update
brew install ffmpeg
brew install libav

# qtwebsockets deps
brew install qt5
#echo "Qt path: $(find /usr/local/Cellar/qt5 -d 1 | tail -n 1)"

# Build obs-studio
cd ..
git clone --recursive https://github.com/jp9000/obs-studio
cd obs-studio
git checkout 19.0.3
mkdir build && cd build
cmake .. \
  -DCMAKE_PREFIX_PATH=/usr/local/opt/qt/lib/cmake \
&& make -j4

sudo make install

# Packages app
cd ..
curl -L -O https://www.slepin.fr/obs-websocket/ci/Packages.pkg -f --retry 5 -C -
sudo installer -pkg ./Packages.pkg -target /
