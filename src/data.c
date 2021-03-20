#include "data.h"

// Initialize previous data state
Data previous_data;

void data_init() {
	previous_data.internal = -1;
	previous_data.external = -1;
	previous_data.reference = -1;
	previous_data.control = -1;
}

Data read_data() {
	Data data;
	data.external = bme280_read();
	data.internal = arduino_read_internal();
	data.reference = arduino_read_reference();

	// If `internal` temperature can't be read, use previous value
	if (data.internal < 0 && previous_data.internal > 0) {
		data.internal = previous_data.internal;
	}
	// If `reference` temperature can't be read, use previous value
	if (data.reference < 0 && previous_data.reference > 0) {
		data.reference = previous_data.reference;
	}

	previous_data = data;

	return data;
}
