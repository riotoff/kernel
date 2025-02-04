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
buffer equ 0x1000

start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    cld
    mov si, msg
    call print_string

    mov ax, 0xFFFF
    mov ds, ax
    mov [0x80], byte 128

    mov dx, filename
    mov cx, 0
    mov ah, 4Eh
    int 21h
    jc error_file_not_found

    mov bx, 0x81
    mov di, bx
    mov cx, 11
    rep movsb

    mov bx, 0xFFFF
    add bx, 1Ah
    mov ax, [bx]
    mov word [file_size], ax

    mov dx, buffer
    mov bx, 0xFFFF
    mov ah, 3Fh
    int 21h
    jc error_reading_file

    jmp buffer

error_file_not_found:
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

file_size dw 0

times 510 - ($ -$$) db 0
dw 0xAA55