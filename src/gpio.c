#include <gpio.h>

void gpio_init() {
  wiringPiSetup();
}

void toggle(int item, int status) {
  pinMode(item, OUTPUT);
  softPwmCreate(item, 1, ON);
  softPwmWrite(item, status);
}

void gpio_controle(double controle) {
  // Controle > 0
  if (controle > 0) {
    toggle(FAN, OFF);
    toggle(RESISTOR, controle);
  // Controle < -40
  } else if (controle < -40) {
    toggle(RESISTOR, OFF);
    toggle(FAN, controle * -1);
  // Controle < 0 && Controle > -40
  } else {
    all_off();
  }
}

void all_off() {
  // RESISTOR
  pinMode(RESISTOR, OUTPUT);
  softPwmWrite(RESISTOR, OFF);

  // FAN
  pinMode(FAN, OUTPUT);
  softPwmWrite(FAN, OFF);
}