#include "app.h"

// A second minus UART usleep
#define SECOND 800000

// Time state
int should_log = 0;

void app_handler() {
	while(1) {
		Data data = read_data();

		pid_atualiza_referencia(data.reference);
		double controle = pid_controle(data.internal);
		gpio_controle(controle);
		data.control = controle;

		data.reference = pid_le_referencia();

		lcd_loc_first_line();
		typeLn("TI:");
		typeFloat(data.internal);
		typeLn(" ");
		typeLn("TE:");
		typeFloat(data.external);
		lcd_loc_second_line();
		typeLn("TR:");
		typeFloat(data.reference);

		print_data(data);

		if (should_log == 0) {
			should_log += 1;
		} else if (should_log == 1) {
			// Write data only after 2 seconds / 2 interactions
			write_data(data);
			should_log = 0;
		}

		usleep(SECOND);
	}
}
