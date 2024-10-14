#!/bin/bash

LAB19_CONFIG_TYPE=defconfig
LAB19_VERSION='5.15-rc1'

LAB19_WD=`pwd`

sudo apt install gcc-arm-linux-gnueabihf qemu-system -y

echo LAB19: Download sources
wget https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/snapshot/linux-$LAB19_VERSION.tar.gz

echo LAB19: Unpack sources
tar -xf linux-$LAB19_VERSION.tar.gz

cd linux-$LAB19_VERSION

echo LAB19: Clear dist before all
make distclean

echo LAB19: Make $LAB19_CONFIG_TYPE for ARM
ARCH=arm make $LAB19_CONFIG_TYPE

echo LAB19: Build for ARM
ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- make -j4 zImage

echo LAB19: Make DTBS
ARCH=arm make dtbs

echo LAB19: switch to boot directory
cd ../run-qemu

echo LAB19: Copy kernel image and DTB
cp ../linux-5.15-rc1/arch/arm/boot/zImage .
cp ../linux-5.15-rc1/arch/arm/boot/dts/vexpress-v2p-ca9.dtb .

QEMU_AUDIO_DRV=none qemu-system-arm -M vexpress-a9 -kernel zImage -dtb vexpress-v2p-ca9.dtb -append "console=ttyAMA0" -nographic
