nasm -f bin src/boot/boot.asm -o build/boot.bin
gcc -c -m00 -ffreestanding -nostdlib -Wall -Wextra src/kernel/addons/kernel.c -o build/modules_kernel.o # change -m00 to -m32 or -m64 (depends on your device and architecture)
ld -T linker.ld -m XXXX -o build/kernel.tmp build/kernel.o build/modules_kernel.o # change XXXX to your emulation mode. (i386pe, i386pep, i386linux, elf_i386, elf32_x86_64)
objcopy -O binary build/kernel.tmp build/kernel.bin
dd if=/dev/zero of=build/kernel_x-x-x.img bs=512 count=100000 # change x-x-x to actual version of Kernel you're using
dd conv=notrunc if=build/boot.bin of=build/kernel_x-x-x.img # change x-x-x to actual version of Kernel you're using
dd conv=notrunc seek=1 if=build/kernel.bin of=build/kernel_x-x-x.img # change x-x-x to actual version of Kernel you're using
