;
; gnu gpl license 3.0
;
; kernel/src/boot/boot.asm
;
; copyright (c) 2025  Arseniy Rayotov
;
; free to distribute as part of Kernel.
;

bits 16
org 0x7C00

jmp short start
nop

msg db 'boot load sy0.', 13, 10, 0
filename db 'kernel.bin', 0
buffer equ 0x9000

start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    cld
    mov si, msg
    call print_string

    mov ax, 0x0201
    mov cx, 2
    mov dx, 0
    mov bx, buffer
    int 0x13
    jc error_reading_sector

    mov si, filename
    mov di, buffer + 32
    mov cx, 14
.next_entry:
    push cx
    mov cx, 11
    repe cmpsb
    je found_file
    add di, 32
    pop cx
    loop .next_entry
    jmp file_not_found

found_file:
    mov ax, [di + 26]
    mov word [cluster], ax
    mov ax, [di + 20]
    mov word [file_size], ax

.read_cluster:
    mov ax, 0x201
    mov bx, buffer
    call read_fat
    jc error_reading_file
    call read_data
    jc error_reading_file
    cmp word [cluster], 0xFFF8
    ja .read_cluster

    jmp buffer

error_reading_sector:
    mov si, reading_error_msg
    call print_string
    cli
    hlt

file_not_found:
    mov si, file_not_found_msg
    call print_string
    cli
    hlt

error_reading_file:
    mov si, reading_error_msg
    call print_string
    cli
    hlt

file_not_found_msg db 'kernel find op1.', 13, 10, 0
reading_error_msg db 'kernel read op1.', 13, 10, 0

print_char:
    mov ah, 0x0E
    int 0x10
    ret

print_string:
    lodsb
    or al, al
    jz .done
    call print_char
    jmp print_string

.done:
    ret

read_fat:
    push ax
    push bx
    push cx
    push dx
    push es

    mov ax, 0x1000
    mov es, ax
    mov bx, [cluster]
    shl bx, 1
    add bx, 0x50
    mov ax, [es:bx]
    mov [cluster], ax

    pop es
    pop dx
    pop cx
    pop bx
    pop ax
    clc
    ret

read_data:
    push ax
    push bx
    push cx
    push dx
    push es

    mov ax, 0x1000
    mov es, ax
    mov bx, [cluster]
    sub bx, 2
    shl bx, 9
    add bx, buffer
    mov ax, 0x0201
    mov cx, 1
    mov dx, 0
    int 0x13
    jc .error

    pop es
    pop dx
    pop cx
    pop bx
    pop ax
    clc
    ret
.error:
    stc
    ret

cluster dw 0
file_size dw 0

times 510 - ($ -$$) db 0
dw 0xAA55
