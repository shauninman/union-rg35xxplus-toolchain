#!/bin/sh

# Install XQuartz, then
defaults write org.xquartz.X11 enable_iglx -bool YES
sudo xhost +localhost

