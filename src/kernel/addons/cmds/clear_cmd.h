// GNU General Public License 3.0
/*
 * toffus/reqs/kernel/cmds/clear_cmd.c
 *
 * Copyright (C) 2025  Arseniy Rayotov
 *
 * May be freely distributed as part of Toffus.
*/

#include <stdio.h>

#ifndef CLEAR_CMD_H
#define CLEAR_CMD_H

void clear_screen() {
    char *video_memory = (char *) 0xB8000;
    for (int i = 0; i < 25 * 80 * 2; i++) {
        video_memory[i] = ' ';
        video_memory[i + 1] = 0x07;
    }
}

#endif