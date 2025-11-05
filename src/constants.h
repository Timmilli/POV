
#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#ifndef F_CPU
#define F_CPU 13000000UL
#endif
#ifndef BAUD
#define BAUD 38400
#endif
#ifndef MYUBRR
#define MYUBRR F_CPU / 8 / BAUD - 1
#endif

#ifndef SDI_ON
#define SDI_ON PORTB |= (1 << PB3)
#endif
#ifndef SDI_OFF
#define SDI_OFF PORTB &= ~(1 << PB3)
#endif

#ifndef CLK_ON
#define CLK_ON PORTB |= (1 << PB5)
#endif
#ifndef CLK_OFF
#define CLK_OFF PORTB &= ~(1 << PB5)
#endif

#ifndef LE_ON
#define LE_ON PORTC |= (1 << PC2)
#endif
#ifndef LE_OFF
#define LE_OFF PORTC &= ~(1 << PC2)
#endif

#ifndef OE_ON
#define OE_ON PORTC |= (1 << PC1)
#endif
#ifndef OE_OFF
#define OE_OFF PORTC &= ~(1 << PC1)
#endif

#endif // __CONSTANTS_H__
