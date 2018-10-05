/*
 *  reset.hpp
 *
 * Created: 29.5.2016 21:57:00
 *  Author: kubas
 */ 


#ifndef RESET_HPP_
#define RESET_HPP_

#define BLRF 4

struct reset_t
{
	reset_t()
		:source(get_reset_source())
	{
		MCUSR = 0x00;
	}
	
	template <typename Serial>
	void print_source(Serial& serial, const char* prefix = nullptr, const char* postfix = nullptr)
	{
		if(prefix != nullptr)
			send_spgm(serial, prefix);
		bool first = true;
		print_item(serial, 1<<WDRF , PSTR("WDR") , first);
		print_item(serial, 1<<BORF , PSTR("BOR") , first);
		print_item(serial, 1<<EXTRF, PSTR("EXT") , first);
		print_item(serial, 1<<PORF , PSTR("POR") , first);
		print_item(serial, 1<<BLRF , PSTR("BLR") , first);
		if(postfix != nullptr)
			send_spgm(serial, postfix);
	}

	void operator()()
	{
		cli();
		// use watchdog
		for(;;);
	}
	
	const uint8_t source;
	
private:
	template <typename Serial>
	void print_item(Serial& serial, const uint8_t& mask, const char* name, bool& first)
	{
		if(source & mask)
		{
			if(!first)
				send_spgm(serial, PSTR(", "));
			send_spgm(serial, name);
			first = false;
		}
	}

	static uint8_t get_reset_source()
	{
		uint8_t rst = MCUSR;
		if (rst == 0)
			rst |= (1<<BLRF);
		return rst;
	}
	
};

reset_t reset;


#endif /* RESET_HPP_ */
