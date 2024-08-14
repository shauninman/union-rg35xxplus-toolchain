#!/bin/sh

SYSROOT_TAR=sysroot.tar.xz
RELEASE_TAG=sysroot-20240813-1

if [ ! -f $SYSROOT_TAR ]; then
	wget https://github.com/shauninman/union-rg35xxplus-toolchain/releases/download/$RELEASE_TAG/$SYSROOT_TAR
fi

TARGET_DIR=/opt/h700

mv $SYSROOT_TAR /opt && cd /opt
mkdir $TARGET_DIR
tar -xvf $SYSROOT_TAR -C $TARGET_DIR
rm $SYSROOT_TAR
rsync -a --ignore-existing $TARGET_DIR/ /opt/rg35xxplus-toolchain/usr/arm-buildroot-linux-gnueabihf/sysroot/
rm -rf $TARGET_DIR