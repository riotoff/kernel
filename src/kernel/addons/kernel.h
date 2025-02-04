// gnu gpl license 3.0
/*
 * kernel/src/kernel/addons/kernel.h
 *
 * copyright (c) 2025  Arseniy Rayotov
 *
 * free to distribute as part of Kernel.
*/

#ifndef KERNEL_H
#define KERNEL_H

#include <stdbool.h>
#include <stddef.h>

void *memset(void *ptr, int value, size_t num);

int strcmp(const char *s1, const char *s2);

void write_to_screen(const char *str);

void clear_screen();

void read_input(char *buffer, size_t buffer_size);

char get_key();

unsigned char inb(unsigned short port);

void exit_system(bool *running);

extern const char ascii_table[];

#endif