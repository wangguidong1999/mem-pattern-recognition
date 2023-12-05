#!/bin/bash
mpr_dir="/home/wangguidong/mem-pattern-recognition"
# MAKEFLAGS="-j $(grep -c ^processor /proc/cpuinfo)"
MAKEFLAGS="-j50"
# git clone https://github.com/SeanLi-OI/mem-pattern-recognition.git ${mpr_dir}
# cd ${mpr_dir}
# git submodule update --recursive

build_submodule() {
  echo "Building glog..."
  cd "${mpr_dir}/external/glog/"
  mkdir -p build
  cd build
  cmake3 ../ -DBUILD_SHARED_LIBS=OFF
  make ${MAKEFLAGS}

  echo "Building gflags..."
  cd "${mpr_dir}/external/gflags/"
  mkdir -p build
  cd build
  cmake3 ../
  make ${MAKEFLAGS}
}

build_mpr() {
  echo "Building mem-pattern-recognition..."
  cd "${mpr_dir}"
  mkdir -p build
  cd build
  cmake3 ../
  make ${MAKEFLAGS}
}

if [ "$1" == "submodule" ]; then
  build_submodule
elif [ "$1" == "mpr" ]; then
  build_mpr
else
  echo "Usage: ./build.sh submodule - to build glog and gflags"
  echo "       ./build.sh mpr      - to build mem-pattern-recognition"
fi