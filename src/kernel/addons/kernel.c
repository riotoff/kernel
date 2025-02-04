// gnu gpl license 3.0
/*
 * kernel/src/kernel/addons/kernel.c
 *
 * copyright (c) 2025  Arseniy Rayotov
 *
 * free to distribute as part of Kernel.
*/

#include "kernel.h"

void *memset(void *ptr, int value, size_t num) {
    unsigned char *p = (unsigned char *)ptr;
    while (num--) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

void write_to_screen(const char *str) {
    char *video_memory = (char *) 0xB8000;
    for (int i = 0; str[i]; ++i) {
        video_memory[(i + 80) * 2] = str[i];
        video_memory[(i + 80) * 2 + 1] = 0x07;
    }
}

void clear_screen() {
    char *video_memory = (char *) 0xB8000;
    for (int i = 0; i < 80 * 25 * 2; ++i) {
        video_memory[i] = 0;
    }
}

void read_input(char *buffer, size_t buffer_size) {
    char ch;
    size_t index = 0;

    while ((ch = get_key()) != '\n' && index < buffer_size - 1) {
        buffer[index++] = ch;
        write_to_screen(&ch);
    }

    buffer[index] = '\0';
}

char get_key() {
    unsigned char scancode;

    while (!(inb(0x64) & 1)) {}

    scancode = inb(0x60);

    if (scancode < 128) {
        return ascii_table[scancode];
    }

    return 0;
}

inline unsigned char inb(unsigned short port) {
    unsigned char result;
    asm volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void exit_system(bool *running) {
    *running = false;
}

const char ascii_table[] = {
    0,   27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
    '9', '0', '-', '=', '\b', /* Backspace */
    '\t', /* Tab */
    'q', 'w', 'e', 'r', /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,   /* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
    '\'', '`', 0,   /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
    'm', ',', '.', '/', 0,   /* Right shift */
    '*',
    0,   /* Alt */
    ' ', /* Space bar */
    0,   /* Caps lock */
    0,   /* 59 - F1  ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,   /* < ... F10 */
    0,   /* 69 - Num lock*/
    0,   /* Scroll Lock */
    0,   /* Home key */
    0,   /* Up Arrow */
    0,   /* Page Up */
    '-',
    0,   /* Left Arrow */
    0,
    0,   /* Right Arrow */
    '+',
    0,   /* 79 - End key*/
    0,   /* Down Arrow */
    0,   /* Page Down */
    0,   /* Insert Key */
    0,   /* Delete Key */
    0,   0,   0,
    0,   /* F11 Key */
    0,   /* F12 Key */
    0,   /* All other keys are undefined */
};
