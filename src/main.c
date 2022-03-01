#include <mini_uart.h>

void start_kernel(void)
{
    uart_init();
    uart_recv();
    uart_send_string("Hello, world!\r\n");

    while (1) {
        uart_send(uart_recv());
    }
}
