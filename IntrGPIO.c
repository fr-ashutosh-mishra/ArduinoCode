// Controlling the led using button 
// Concept GPIO-INTR


#include <avr/io.h>
#include <avr/interrupt.h>

void init(void)
{
    DDRB |= (1 << DDB5);           // PB5 as output
    DDRD &= ~(1 << DDD3);          // PD3 as input

    EICRA |= (1 << ISC01);         // Trigger on falling edge
    EIMSK |= (1 << INT1);          // Enable external interrupt INT1
    PORTD |= (1 << PIND3);         // Enable internal pull-up on PD3

    sei();                         // Enable global interrupts
}

ISR(INT1_vect)
{
    PORTB ^= (1 << PORTB5);        // Toggle PB5
}

int main(void)
{
    init();
    while (1)
    {
        // Main loop - interrupts handle PB5 toggling
    }

    return 0;
}
