#include "uart.h"
#include "crc16.h"

void writeUART(int uart0_filestream, char subcode) {
  unsigned char tx_buffer[20];
  unsigned char mensagem[200];
  unsigned char *p_tx_buffer;
  
  p_tx_buffer = &tx_buffer[0];
  *p_tx_buffer++ = 0x01; // Código do arduino
  *p_tx_buffer++ = 0x23; // Código Solicitação
  *p_tx_buffer++ = subcode; // Subcódigo
  *p_tx_buffer++ = 0x06; // Matrícula
  *p_tx_buffer++ = 0x08; // Matrícula
  *p_tx_buffer++ = 0x02; // Matrícula
  *p_tx_buffer++ = 0x02; // Matrícula

  CRCUnion crc;
  memcpy(mensagem, tx_buffer, 7);
  crc.crc = calcula_CRC(tx_buffer, 7);
  memcpy(&mensagem[7], crc.bytes, 2);

  if (uart0_filestream != -1) {
    int count = write(uart0_filestream, &mensagem, 9);
    if (count < 0) {
      printf("UART write error.\n");
      exit(1);
    }
  }
}

float readUART(int uart0_filestream) {
  unsigned char rx_buffer[256];
  if (uart0_filestream != -1) {
    int rx_length = read(uart0_filestream, (void*)rx_buffer, 255); // Filestream, buffer to store in, number of bytes to read (max)
    if (rx_length < 0) {
      printf("Erro na leitura.\n"); // An error occured (will occur if there are no bytes)
      return -1;
    }
    else if (rx_length == 0) {
      printf("Nenhum dado disponível.\n"); // No data waiting
      return -1;
    }
    else {
      // Bytes received
      rx_buffer[rx_length] = '\0';
    }

    // Expected data size
    if (rx_length != 9) {
      printf("Leitura incorreta!\n");
      return -1;
    }

    // Check CRC
    short crc_response;
    memcpy(&crc_response, &rx_buffer[rx_length - 2], 2);

    // Check if response CRC is valid
    unsigned char response[7];
    memcpy(&response, &rx_buffer[0], rx_length - 2);
    if (crc_response != calcula_CRC(response, 7)) {
      printf("CRC Inválido!\n");
      return -1;
    }

    // Return temperature
    float temperature;
    memcpy(&temperature, &rx_buffer[3], 4);

    return temperature;
  }

  return -1;
}

int openUART() {
  int uart0_filestream = -1;

  uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);  //Open in non blocking read/write mode
  if (uart0_filestream == -1) {
    printf("Erro - Não foi possível iniciar a UART.\n");
    exit(1);
  }

  struct termios options;
  tcgetattr(uart0_filestream, &options);
  options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;  // < Set baud rate
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(uart0_filestream, TCIFLUSH);
  tcsetattr(uart0_filestream, TCSANOW, &options);

  return uart0_filestream;
}

float arduino_read_internal() {
  int uart0_filestream;

  uart0_filestream = openUART();

  writeUART(uart0_filestream, 0xC1);

  usleep(100000);

  float temperature = readUART(uart0_filestream);

  close(uart0_filestream);

  return temperature;
}

float arduino_read_reference() {
  int uart0_filestream;

  uart0_filestream = openUART();

  writeUART(uart0_filestream, 0xC2);

  usleep(100000);

  float temperature = readUART(uart0_filestream);

  close(uart0_filestream);

  return temperature;
}
