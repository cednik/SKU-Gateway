#ifndef PINS_DEF_HPP_
#define PINS_DEF_HPP_


#include "../lib/avrlib/pin.hpp"
#include "../lib/avrlib/portb.hpp"
#include "../lib/avrlib/portc.hpp"
#include "../lib/avrlib/portd.hpp"

typedef avrlib::    pin<avrlib::portb, 0> pin_eth_int;
typedef avrlib::    pin<avrlib::portb, 1> pin_eth_reset;
typedef avrlib::    pin<avrlib::portb, 2> pin_eth_cs;
typedef avrlib::    pin<avrlib::portb, 3> pin_mosi;
typedef avrlib::    pin<avrlib::portb, 4> pin_miso;
typedef avrlib::    pin<avrlib::portb, 5> pin_sck;
typedef avrlib::    pin<avrlib::portb, 6> pin_xtal1;
typedef avrlib::    pin<avrlib::portb, 7> pin_xtal2;
typedef avrlib::    pin<avrlib::portc, 0> pin_jumper;
typedef avrlib::    pin<avrlib::portc, 1> pin_io_reset;
typedef avrlib::    pin<avrlib::portc, 2> pin_io_int_a;
typedef avrlib::    pin<avrlib::portc, 3> pin_io_int_b;
typedef avrlib::    pin<avrlib::portc, 4> pin_sda;
typedef avrlib::    pin<avrlib::portc, 5> pin_scl;
typedef avrlib::    pin<avrlib::portd, 0> pin_uart_rxd;
typedef avrlib::    pin<avrlib::portd, 1> pin_uart_txd;
typedef avrlib::    pin<avrlib::portd, 2> pin_uart_dir;
typedef avrlib::inv_pin<avrlib::portd, 3> pin_led1;
typedef avrlib::inv_pin<avrlib::portd, 4> pin_led2;
typedef avrlib::    pin<avrlib::portd, 5> pin_onewire;
typedef avrlib::    pin<avrlib::portd, 6> pin_spi_cs;
typedef avrlib::    pin<avrlib::portd, 7> pin_data;


#endif // PINS_DEF_HPP_
