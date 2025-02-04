// gnu gpl license 3.0
/*
 * kernel/src/kernel/main.c
 *
 * copyright (c) 2025  Arseniy Rayotov
 *
 * free to distribute as part of Kernel.
*/

#include "addons/kernel.h"

extern void kmain();

void start() {
    kmain();
}

void kmain() {
    char *video_memory = (char *) 0xB8000;
    const char *message = "kernel load sy0.\n";
    
    for (int i = 0; message[i]; ++i) {
        video_memory[i * 2] = message[i];
        video_memory[i * 2 + 0x01] = 0x07;
    }

    char input_buffer[256];
    bool running = true;

    while (running) {
        memset(input_buffer, 0, sizeof(input_buffer));
        
        write_to_screen("> ");

        read_input(input_buffer, sizeof(input_buffer));

        if (strcmp(input_buffer, "exit") == 0) {
            exit_system(&running);
        } else if (strcmp(input_buffer, "clear") == 0) {
            clear_screen();
        } else {
            write_to_screen("command find op1.\n");
        }
    }

    while (1);
}
