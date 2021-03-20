#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Used for UART
#include <fcntl.h>   // Used for UART
#include <termios.h> // Used for UART
#include <stdint.h>

#ifndef UART_H_
#define UART_H_

float arduino_read_internal();
float arduino_read_reference();

#endif /* UART_H_ */
