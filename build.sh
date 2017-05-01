#!/bin/bash

echo Building cos

CURDIR=`pwd`
INCLUDE=`pwd`/include
OBJ=`pwd`/obj
CFLAGS="-std=gnu99 -ffreestanding -O2 -Wall -Wextra -fdiagnostics-color=auto"
OUT=cos.bin
ISOOUT=cos.iso

echo Building the boot asm file
i686-elf-as boot/boot.s -o obj/boot.o

echo Compiling kernel c files
cd kernel
for i in *.c; do
	echo Compiling $i
	i686-elf-gcc -c $i -o $OBJ/kernel_$i.o $CFLAGS -I$INCLUDE
done
echo Assembling kernel asm files
for i in *.asm; do
	echo Assembling $i
	nasm -felf32 $i -o $OBJ/kernel_asm_$i.o
done
echo Compiling kernel/display files
cd display
for i in *.c; do
	echo Compiling $i
	i686-elf-gcc -c $i -o $OBJ/kernel_$i.o $CFLAGS -I$INCLUDE
done
cd ..
cd ..

echo Linking all .o files to $OUT
cd obj
i686-elf-gcc -T linker.ld -o $OUT -ffreestanding -O2 -nostdlib *.o -lgcc
echo cleaning up...
rm ../cos.bin
rm *.o
mv cos.bin ../cos.bin
cd ..

if [ $1 = "run" ]; then
	qemu-system-i386 -kernel cos.bin
fi
if [ $1 = ""]; then
	if grub-file --is-x86-multiboot $OUT; then
		echo multiboot OS in $OUT confirmed, creating iso
		mkdir -p isodir/boot/grub
		cp $OUT isodir/boot/$OUT
		cp grub/grub.cfg isodir/boot/grub/grub.cfg
		grub-mkrescue -o $ISOOUT isodir
	else
		echo $OUT is not multiboot
	fi
fi
if [ $1 = "iso" ]; then
		if grub-file --is-x86-multiboot $OUT; then
		echo multiboot OS in $OUT confirmed, creating iso
		mkdir -p isodir/boot/grub
		cp $OUT isodir/boot/$OUT
		cp grub/grub.cfg isodir/boot/grub/grub.cfg
		grub-mkrescue -o $ISOOUT isodir
	else
		echo $OUT is not multiboot
	fi
fi
