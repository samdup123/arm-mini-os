/* uart.h - UART initialization & communication */
// by ??

#ifndef UART_H
#define UART_H

#define UART_BUFFER_EMPTY (0)
#define UART_BUFFER_FULL (255)
#define UART_BUFFER_PARTIALLY_FULL (1)

#include <stdint.h>

/*
 * Initialize UART0.
 */
void uart_init();

/*
 * Transmit a byte via UART0.
 * uint8_t Byte: byte to send.
 */
void uart_putc(uint8_t byte);

// read one character
uint8_t uart_readc(void);

/*
 * print a string to the UART one character at a time
 * const char *str: 0-terminated string
 */
void uart_puts(const char *str);

void uart_enable_transmit_interrupt(void);
void uart_disable_transmit_interrupt(void);
char uart_check_buffer(char a);

#endif  // #ifndef UART_H
