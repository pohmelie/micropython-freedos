#!/usr/bin/env bash


base=$(pwd)

if [ ! -d "$base/djgpp" ]; then
  git clone https://github.com/andrewwutw/build-djgpp
  cd build-djgpp
  export DJGPP_PREFIX=$base/djgpp
  source build-djgpp.sh 5.2.0
  cd ..
  cp djgpp/bin/i586-pc-msdosdjgpp-size djgpp/i586-pc-msdosdjgpp/bin/size
fi

export PATH=$base/djgpp/bin:$base/djgpp/i586-pc-msdosdjgpp/bin:$PATH
make clean
make freedos
source cws-combine.sh
