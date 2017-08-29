#!/bin/bash

set -eu
set -o pipefail

function install() {
  mason install $1 $2
  mason link $1 $2
}

# setup mason
./scripts/setup.sh --config local.env
source local.env

install protozero 1.5.1

# install gzip-hpp headers
if [ ! -d "vendor/gzip-hpp" ]
then
  mkdir -p vendor
  git clone https://github.com/mapbox/gzip-hpp.git vendor/gzip-hpp --depth=1
fi
