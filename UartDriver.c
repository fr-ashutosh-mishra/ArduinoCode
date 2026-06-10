#include<avr/io.h>
#include<avr/interrupt.h>

volatile char received_data_ptr[100]; // Buffer to store received data
void USART_transmit_string(char* str);

void USART_init()
{
    UBRR0H = 0; // Set baud rate to 9600 (assuming F_CPU = 16MHz)
    UBRR0L = 103;
    UCSR0B = 1 << RXEN0 | 1 << TXEN0; // Enable receiver and transmitter
    UCSR0C = 1 << UCSZ00 | 1 << UCSZ01; // Set frame format to 8 data bits, no parity, 1 stop bit
    UCSR0B |= 1 << RXCIE0; // Enable receive complete interrupt
    sei(); // Enable global interrupts
}

void USART_transmit(uint8_t data)
{
    while(!(UCSR0A & (1 << UDRE0))); // Wait for empty transmit buffer
    UDR0 = data; // Transmit data
}

// void USART_receive()
// {
//     static uint8_t i = 0; // Index for received data buffer
//     while(!(UCSR0A & (1 << RXC0))); // Wait for data to be received
//     uint8_t received_data = UDR0; // Read received data
//     if(received_data == '\n')
//     {
//         memset(received_data_ptr,0,100);
//     }
//     received_data_ptr[i++] = received_data;
// }

ISR(USART_RX_vect)
{
   static uint8_t i = 0; // Index for received data buffer
    while(!(UCSR0A & (1 << RXC0))); // Wait for data to be received
    uint8_t received_data = UDR0; // Read received data
    if(received_data == '\n')
    {
        received_data_ptr[i] = "\0";
        i=0;
        USART_transmit_string(received_data_ptr);
    }
    else
    {
        received_data_ptr[i++] = received_data;
    }
}

void USART_transmit_string(char* str)
{
    while (*str)
    {
        USART_transmit(*str++);
    }
}

int main(void)
{
    USART_init();
    USART_transmit_string("Hello, UART!");

    while (1)
    {
    //   USART_receive();    // Main loop - you can add code to receive data or perform other tasks
    }

    return 0;
}
