#define __AVR_ATmega328P__
#include <avr/io.h>
#define F_CPU 13000000UL
#include <util/delay.h>

int buffer[16] = {0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,0};

int main(void) {
    // Configure le bit 3 et 5 du registre DDRD en sortie
    DDRB |= (1 << PB3); // SDI
    DDRB |= (1 << PB5); // CLK
    DDRC |= (1 << PC1); // OE, 
    DDRC |= (1 << PC2); // LE, Fin de série
    PORTC = 0;
    PORTB = 0;

    
    for(int i = 0;i < 16;i++){
        PORTB &= ~(1 << PB3);
        if(buffer[i]){
            PORTB |= (1 << PB3);
        }
        PORTB |= (1 << PB5);
        PORTB &= ~(1 << PB5); 
    }
    PORTC |= (1 << PC2);
    PORTC &= ~(1 << PC2);
    PORTC |= (1 << PC1);
    PORTC &= ~(1 << PC1);
        
}

