/*
 *  led.hpp
 *
 * Created: 29.5.2016 23:41:53
 *  Author: kubas
 */ 


#ifndef LED_HPP_
#define LED_HPP_


namespace detail
{
	
typedef timeout::time_type led_time_type;

class led_impl_t
{
public:
	typedef led_time_type time_type;
	typedef uint8_t count_type;

	led_impl_t()
		:m_timer(0), m_on_time(0), m_off_time(0), m_stop_counter(0), m_state(0), m_value(false)
	{
		m_timer.cancel();
	}
	void set() { m_state = 1; }
	void clear() { m_state = 2; }
	void toggle()
	{
		switch(m_state)
		{
			case 0: m_state = 3; break;
			case 1: m_state = 2; break;
			case 2: m_state = 1; break;
			case 3: break;
		}
	}
	void set(const uint8_t& value)
	{
		if(value)
			set();
		else
			clear();
	}
	void blink(const time_type& period, const time_type& difference = 0, const count_type& count = 0)
	{
		m_on_time = (period>>1) + difference;
		m_off_time = (period>>1) - difference;
		m_stop_counter = count;
		m_timer.set_timeout(m_on_time);
		m_timer.restart();
		//set();
		toggle();
	}
	void on()
	{
		m_timer.cancel();
		set();
	}
	void off()
	{
		m_timer.cancel();
		clear();
	}
	void operator() (const bool& value) { if (value) on(); else off(); }
	void operator = (const bool& value) { if (value) on(); else off(); }
	uint8_t get() const { return m_value; }
	uint8_t blinking() const { return m_timer.running(); }
	bool process()
	{
		switch(m_state)
		{
			case 0: break;
			case 1: _set(); m_state = 0; break;
			case 2: _clear(); m_state = 0; break;
			case 3: _toggle(); m_state = 0; break;
		}
		if(m_timer.running() && m_timer)
		{
			if(m_off_time == 0) // last blink ends
			{
				//_clear();
				_toggle();
				m_timer.stop();
			}
			else
			{
				if(get()) // dark half-period starts
				{
					//_clear();
					_toggle();
					m_timer.ack();
					m_timer.set_timeout(m_off_time);
					if(m_stop_counter != 0 && --m_stop_counter == 0) // stop after next tiemout
						m_off_time = 0;
				}
				else // light half-period start
				{
				//	_set();
					_toggle();
					m_timer.ack();
					m_timer.set_timeout(m_on_time);
				}
			}
		}
		return m_value;
	}
private:
	void _set()    { m_value = true; }
	void _clear()  { m_value = false; }
	void _toggle() { m_value = !m_value; }
	
	timeout m_timer;
	time_type m_on_time;
	time_type m_off_time;
	count_type m_stop_counter;
	uint8_t m_state;
	bool m_value;
};

const led_time_type led_process_period = msec(10);

} // namespace detail

template <class pin>
class led_t
	:public detail::led_impl_t
{
public:
	led_t()
		:detail::led_impl_t()
	{}
		
	void process()
	{
		pin::set_value(detail::led_impl_t::process());
	}
};


#endif /* LED_HPP_ */