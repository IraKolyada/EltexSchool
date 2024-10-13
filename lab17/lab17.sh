#!/bin/bash

LAB17_CONFIG_TYPE=defconfig
LAB17_VERSION='5.15-rc1'


# Check args

echo LAB17: Install deps
sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison -y

echo LAB17: Download sources
wget https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/snapshot/linux-$LAB17_VERSION.tar.gz

echo LAB17: Unpack sources
tar -xf linux-$LAB17_VERSION.tar.gz

#cd linux-$LAB17_VERSION

echo LAB17: Create config
#make $LAB17_CONFIG_TYPE

echo LAB17: Build kernel
#make -j4 bzImage

echo LAB17: Build modules
#make -j4 modules
