#ifndef	_MINI_UART_H
#define	_MINI_UART_H

int uart_recvline(char *buff, int maxlen);
void uart_init(void);
char uart_recv(void);
void uart_send(char c);
void uart_send_string(char *str);

#endif  /* _MINI_UART_H */