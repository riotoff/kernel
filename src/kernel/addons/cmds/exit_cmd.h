// GNU General Public License 3.0
/*
 * toffus/reqs/kernel/cmds/exit_cmd.c
 *
 * Copyright (C) 2025  Arseniy Rayotov
 *
 * May be freely distributed as part of Toffus.
*/

#include <stdbool.h>

#ifndef EXIT_CMD_H
#define EXIT_CMD_H

void exit_system(bool *running) {
    *running = false;
}

#endif