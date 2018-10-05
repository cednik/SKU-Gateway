/*
 * fw.cpp
 *
 * Created: 30.8.2018 16:19:41
 * Author : Jakub Streit <xstrei03@stud.feec.vutbr.cz>
 */ 


#include <Arduino.h>
#include <avrlib.hpp>

#include "serial_wrapper.hpp"
#include "pins_def.hpp"

#define debug Serial

#include "reset.hpp"
#include "build_info.hpp"
#include "arduino_pinout.hpp"

#include "led.hpp"

typedef pin_io_int_a pin_backlight;

led_t<pin_led1> led_green;
led_t<pin_led2> led_red;

uart_t uart;
ISR(USART_RX_vect) { uart.process_rx(); }
void (*serialEventRun)(void) = 0;

template <class Stream>
void print_device_info(Stream& stream, const bool& with_reset = true)
{
	send_spgm(stream, PSTR("\nSKU - Gateway\n"));
	BUILD_INFO::print(stream, 1, '\t');
	if(with_reset)
		reset.print_source(stream, PSTR("\tLast reset: "), PSTR("\n"));
}

#include <Modbus.h>

ModbusIP modbus;

void process()
{
	led_red.process();
	led_green.process();
    modbus.task();
    uart.process_tx();
}

template <class Stream>
char busy_read(Stream& stream)
{
    while (stream.available() == 0)
        process();
    return stream.read();
}

uint8_t mac [6] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };
uint8_t IP  [4] = { 192, 168,   1,   6 };
uint8_t MASK[4] = { 255, 255, 255,   0 };
uint8_t DNS [4] = {   0,   0,   0,   0 };
uint8_t GW  [4] = {   0,   0,   0,   0 };

#define BACKGLIGHT_ADDR 100

void setup()
{
    pin_eth_int::pullup();
	pin_eth_reset::make_low();
	pin_eth_cs::make_high();
	pin_mosi::make_output();
	pin_miso::pullup();
	pin_sck::make_output();
	pin_jumper::pullup();
	pin_io_reset::make_low();
	pin_io_int_a::pullup();
	pin_io_int_b::pullup();
	pin_sda::pullup();
	pin_scl::pullup();
	pin_uart_rxd::pullup();
	pin_uart_txd::make_high();
	//pin_uart_dir::make_high(); // because of external UART/USB converter connected directly to the MPU
    pin_uart_dir::make_low();
	pin_led1::make_high();
	pin_led2::make_low();
	pin_onewire::pullup();
	pin_spi_cs::make_high();
	pin_data::pullup();

    pin_backlight::make_high();

    uart.usart().open(115200UL, true);
    wait(msec(1));
	print_device_info(debug);
    debug.flush();
    led_green.blink(msec(1000));

    pin_eth_reset::set_high();
    wait(msec(1));
    modbus.config(mac, IP, DNS, GW, MASK);

    modbus.addCoil(BACKGLIGHT_ADDR);

    send_spgm(debug, PSTR("Starting loop\n"));
}

void loop()
{
    debug.flush();
    if (debug.available())
    {
        led_red.toggle();
        char c = debug.read();
        switch(c)
		{
        case '\r':
            debug.write('\n');
            break;
        case 't':
        case '~':
        case 'z':
        case '3':
        break;
        default:
            debug.write(c);
        }
    }
    pin_backlight::set_value(!modbus.Coil(BACKGLIGHT_ADDR));
    process();
}

// void uip_log(char * msg)
// {
//     send(debug, msg);
//     debug.write('\n');
// }
