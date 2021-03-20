#include "menu.h"

#define WIDTH 50
#define HEIGHT 13

WINDOW *window;
int is_reference_screen;

char *options[] = {
	"Alterar referência",
	"Limpar referência",
	"Sair",
};

int startx = 0;
int starty = 0;
int n_options = sizeof(options) / sizeof(char *);

void clear_reference() {
  pid_limpa_referencia_usuario();
  refresh();
}

void print_input(WINDOW *window, int y, int x, char *input) {
  wattron(window, COLOR_PAIR(1));
  mvwprintw(window, y, x, input);
  wattroff(window, COLOR_PAIR(1));
}

void set_reference() {
  WINDOW *reference_window;

  float reference;
  int max_height, max_width;
  int _startx, _starty;

  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  getmaxyx(stdscr, max_height, max_width);

  _starty = (LINES - max_height) / 2;   
  _startx = (COLS - max_width) / 2; 
  refresh();

  reference_window = newwin(HEIGHT, WIDTH, _starty, _startx);

  wborder(reference_window, ACS_VLINE, ACS_VLINE,ACS_HLINE,ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

  print_input(reference_window, _starty + 1, _startx + 1, "Referência: ____________________");

  echo();
  wmove(reference_window, _starty + 1, _startx + 13);
  wscanw(reference_window, "%f", &reference);

  pid_referencia_usuario(reference);
  is_reference_screen = 0;

  clear_menu(reference_window);
}

void print_menu(WINDOW *window, int highlight) {
	int x = 2, y = 2, i;

	box(window, 0, 0);
	for(i = 0; i < n_options; i++) {
		if (highlight == i + 1) {
			wattron(window, A_REVERSE);
			mvwprintw(window, y, x, "\t%s", options[i]);
			wattroff(window, A_REVERSE);
		} else {
			mvwprintw(window, y, x, "\t%s", options[i]);
		}
		++y;
	}
	wrefresh(window);
}

void clear_menu(WINDOW *window_param) {
	wclear(window_param);
	wborder(window_param, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');  
	wrefresh(window_param);
	delwin(window_param); 
}

void print_data(Data data) {
  if (is_reference_screen == 1) {
    return;
  }

  char *on = "ON ";
  char *off = "OFF";

  mvwprintw(window, 6, 1, "\tTI: %4.2f TE: %4.2f", data.internal, data.external);
  mvwprintw(window, 7, 1, "\tTR: %4.2f TA: %4.2f", data.reference, data.control);
  mvwprintw(window, 9, 1, "\tRESISTOR: %s", data.control > 0 ? on : off);
  mvwprintw(window, 10, 1, "\tCOOLER: %s", data.control < -40 ? on : off);
  wrefresh(window);
}

void menu_handler() {
	int highlight = 1;
	int option = 0;
	int c;

	initscr();
	start_color(); 
	clear();
	noecho();
	cbreak();
	curs_set(0);
     
	window = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(window, TRUE);
	refresh();
 
	do {
		print_menu(window, highlight);
		c = wgetch(window);

		switch(c) {
			case KEY_UP:
				if(highlight == 1)
					highlight = n_options;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_options)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:    
				option = highlight;
				if (option == 1) {
					clear_menu(window);
          is_reference_screen = 1;
          set_reference();
					window = newwin(HEIGHT, WIDTH, starty, startx);
					keypad(window, TRUE);
					refresh();
				}

				if (option == 2) {
					clear_reference();
				}

				if (option == 3) {
					quit_handler();
				}

				break;
			default:
				refresh();
				break;
		}
	} while(1);
}
