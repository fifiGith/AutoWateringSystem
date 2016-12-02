#include <avr/io.h>
#include "peri.h"

void init_peripheral()
{
	DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2);
	DDRC &= ~(1 << PC3);
	DDRC &= ~(1 << PC4);
	PORTC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC4));
	PORTC |= (1 << PC3);
}

void set_led(uint8_t pin,uint8_t state)
{
	if (state == 1)
   		PORTC |= (1 << pin);
	else 
		PORTC &= ~(1 << pin);
}

void set_led_value(uint8_t x)
{
	PORTC &= (0b11111000);
	PORTC |= (x & 0b00000111);
}
uint16_t read_adc(uint8_t channel)
{
	ADMUX = (0<<REFS1) |(1<<REFS0) | (0<<ADLAR)|(channel & 0b1111);
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADSC);
	while((ADCSRA & (1<<ADSC)))
	;
	return ADCL + ADCH*256; 
}

uint16_t get_light()
{
    return read_adc(PC4);
}

