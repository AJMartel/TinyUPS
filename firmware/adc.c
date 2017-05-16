#include "adc.h"
#include <avr/io.h>

#if defined(REFS2)
#define ADC_MUX_CONFIG _BV(ADLAR) | _BV(REFS2) | _BV(REFS1) // left adjusted, uses 2.56V internal reference
#else
#define ADC_MUX_CONFIG _BV(ADLAR) | _BV(REFS1) | _BV(REFS0) // left adjusted, uses 1.1V internal reference
#endif
#if (defined(ADEN)&&defined(ADPS2)&&defined(ADPS1)&&defined(ADPS0))
#define ADC_SRA_CONFIG _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) // very slow conversion
#endif

void adc_init(void)
{
    ADMUX = ADC_MUX_CONFIG;
    ADCSRA = ADC_SRA_CONFIG;
}

uint16_t adc_read(uint8_t chan)
{
    ADMUX = ADC_MUX_CONFIG | chan; // select channel
    ADCSRA |= (1 << ADSC);         // start ADC measurement
    while (ADCSRA & (1 << ADSC)); // wait till conversion complete 
    return ADC; // GCC is smart enough to return this in the correct order
}
