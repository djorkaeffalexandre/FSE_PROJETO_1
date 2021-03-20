#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ncurses.h>

#ifndef QUIT_H_
#define QUIT_H_

void quit_init();
void quit_handler();

#endif /* QUIT_H_ */
