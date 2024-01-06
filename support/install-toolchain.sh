#!/bin/sh

mkdir -p /opt/rg35xxplus-toolchain
if [ -d /opt/rg35xxplus-toolchain/usr ]; then
	rm -fr /opt/rg35xxplus-toolchain/usr
fi
cp -rf ~/buildroot/output/host/usr/ /opt/rg35xxplus-toolchain/
# this version of buildroot doesn't have relocate-sdk.sh yet so we bring our own
cp ~/relocate-sdk.sh /opt/rg35xxplus-toolchain/
cp ~/sdk-location /opt/rg35xxplus-toolchain/
/opt/rg35xxplus-toolchain/relocate-sdk.sh