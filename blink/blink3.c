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

    int x = 0;
    while(1){
        //Rendering
        x++;
        if(x > 16){
            x = 0;
        }
        for(int i = 0; i < 16; i++){
            if(i < x){
                buffer[i] = 1;
            }else{
                buffer[i] = 0;
            }

        }
        
        //Display
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

        //Quick PMW
        for(int n = 0; n < 1000;n++){
            PORTC |= (1 << PC1);
            _delay_us(150);
            PORTC &= ~(1 << PC1);
            _delay_us(10);
        }
    }
        
}

