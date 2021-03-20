#include <stdio.h>
#include <stdlib.h>
#include <pid.h>
#include <quit.h>
#include <bme280.h>
#include <ncurses.h>
#include <csv.h>
#include <data.h>

#ifndef MENU_H_
#define MENU_H_

void menu_handler();
void print_data(Data data);
void clear_menu(WINDOW *window);

#endif /* MENU_H_ */
