#ifndef SERIAL_WRAPPER_HPP_
#define SERIAL_WRAPPER_HPP_

#if defined(__cplusplus) && !defined(AVRLIB_PORT_CPP)

#include <stdint.h>

#include "pins_def.hpp"

#define nop() __asm__ volatile ("nop")

#include "../lib/avrlib/async_usart.hpp"
#include "../lib/avrlib/usart0.hpp"
#include "../lib/avrlib/bootseq.hpp"

typedef avrlib::async_usart<avrlib::usart0, 32, 64, avrlib::bootseq, uint8_t, pin_uart_dir> uart_t;
extern uart_t uart;

typedef uart_t HardwareSerial;
#define Serial uart

extern void (*serialEventRun)(void);

#endif // __cplucplus

#endif // SERIAL_WRAPPER_HPP_
