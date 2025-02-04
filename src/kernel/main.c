// gnu gpl license 3.0
/*
 * kernel/src/kernel/main.c
 *
 * copyright (c) 2025  Arseniy Rayotov
 *
 * free to distribute as part of Kernel.
*/

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
    }

    while (1);
}