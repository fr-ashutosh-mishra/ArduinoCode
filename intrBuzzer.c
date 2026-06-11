#include<avr/io.h>
#include<avr/interrupt.h>


void init()
{
    DDRB |= 1 << DDB5;
    DDRD &= ~(1 << DDD2);
    
    EICRA |= (1 << 1);
    EIMSK |=(1<<INT0);
    sei();
    PORTD = ~(1<<PD2);
}

ISR(INT0_vect)
{
    PORTB ^= (1 << PB5);
}


int main()
{
    init();
    while(1)
    {

    }
}
