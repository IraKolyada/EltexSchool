#!/bin/bash

echo LAB18: Download busybox sources
wget https://busybox.net/downloads/busybox-1.36.1.tar.bz2

echo LAB18: Unpack sources
tar -xf busybox-1.36.1.tar.bz2

cd busybox-1.36.1

echo LAB18: Clear dist before all
make distclean

echo LAB18: Make config ARM
ARCH=arm make defconfig
ARCH=arm make menuconfig

echo LAB18: Build busybox
make -j4

echo LAB18: Is for ARM?
file busybox | grep ARM | grep statically

echo LAB18: Install
make install

echo LAB18: Go to _install
cd _install

find . | cpio -o -H newc | gzip > initramfs.cpio.gz

echo LAB18: Copy initramfs to lab19/run-qemu
cp initramfs.cpio.gz ../../../lab19/run-qemu/

cd ../../../lab19/run-qemu

QEMU_AUDIO_DRV=none qemu-system-arm -M vexpress-a9 -kernel zImage -dtb vexpress-v2p-ca9.dtb -append "console=ttyAMA0 rdinit=/bin/ash" -nographic -initrd initramfs.cpio.gz

