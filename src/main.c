#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <lcd.h>
#include <bme280.h>
#include <gpio.h>
#include <data.h>
#include <csv.h>
#include <quit.h>

#include <menu.h>
#include <app.h>

int main() {
	lcd_init(); // setup LCD
	bme280_init(); // setup BME280
	gpio_init(); // setup GPIO
	data_init(); // setup Data
	csv_init(); // setup CSV
	quit_init(); // setup QUIT

	pthread_t tid[2];
	pthread_create(&tid[0], NULL, (void *) app_handler, (void *) NULL);
	pthread_create(&tid[1], NULL, (void *) menu_handler, (void *) NULL);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}
