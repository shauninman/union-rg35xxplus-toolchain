#!/bin/sh

cd /opt/
tar --xz -cvf rg35xxplus-toolchain.tar.xz rg35xxplus-toolchain/
mv rg35xxplus-toolchain.tar.xz ~/workspace/

printf "rg35xxplus-toolchain.tar.xz can be shared as a blob\nby placing in support before calling 'make shell'\n"