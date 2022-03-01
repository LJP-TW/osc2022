// Ref: https://github.com/s-matyukevich/raspberry-pi-os/blob/master/src/lesson01/src/mini_uart.c
#include <mini_uart.h>
#include <BCM2837.h>
#include <utils.h>

void uart_send(char c)
{
	while (!(get32(AUX_MU_LSR_REG) & 0x20)) {};

	put32(AUX_MU_IO_REG, c);
}

char uart_recv(void)
{
    while (!(get32(AUX_MU_LSR_REG) & 0x01)) {};

	return (get32(AUX_MU_IO_REG) & 0xFF);
}

void uart_send_string(char *str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		uart_send(str[i]);
	}
}

void uart_init(void)
{
	unsigned int selector;

	selector = get32(GPFSEL1);
	selector &= ~(7 << 12);            // Clean gpio14
	selector |= 2 << 12;               // Set alt5 for gpio14
	selector &= ~(7 << 15);            // Clean gpio15
	selector |= 2 << 15;               // Set alt5 for gpio15
	put32(GPFSEL1, selector);

	put32(GPPUD, 0);
	delay(150);
	put32(GPPUDCLK0, (1 << 14) | (1 << 15));
	delay(150);
	put32(GPPUDCLK0, 0);

	put32(AUX_ENABLES, 1);             // Enable mini uart (this also enables access to its registers)
	put32(AUX_MU_CNTL_REG, 0);         // Disable auto flow control and disable receiver and transmitter (for now)
	put32(AUX_MU_IER_REG, 0);          // Disable receive and transmit interrupts
	put32(AUX_MU_LCR_REG, 3);          // Enable 8 bit mode
	put32(AUX_MU_MCR_REG, 0);          // Set RTS line to be always high
	put32(AUX_MU_BAUD_REG, 270);       // Set baud rate to 115200
	put32(AUX_MU_IIR_REG, 6);		   // Clear the Rx/Tx FIFO
	put32(AUX_MU_CNTL_REG, 3);         // Finally, enable transmitter and receiver
}