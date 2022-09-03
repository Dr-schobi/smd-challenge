#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

void blink(int A, int B) {

    // enable LED from A to B
    DDRB = ( 1 << A ) | ( 1 << B );
    PORTB |= ( 1 << A ); 
    PORTB &= ~( 1 << B );
    _delay_ms(5);
    DDRB = 0;
    
    WDTCR = _BV(WDTIE) |  _BV(WDP1) | _BV(WDP0);    // enable WDT Interrupt, Set WDT 125MS
    wdt_reset();
    sei();
    sleep_mode();
    cli();
    
    WDTCR = _BV(WDTIE) |  _BV(WDP2);    // enable WDT Interrupt, Set WDT 250MS
    wdt_reset();
    sei();
    sleep_mode();
    cli();

}

ISR(WDT_vect) { 

}



int main( void ) {
    
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
 
    while( 1 ) {       
             
        blink( PB2, PB1 );
        blink( PB1, PB2 );

        blink( PB3, PB1 );
        blink( PB1, PB3 );
        
        blink( PB1, PB0 );
        blink( PB0, PB1 );

        blink( PB3, PB0 );
        blink( PB0, PB3 );
        
        blink( PB0, PB2 );
        blink( PB2, PB0 );
        
        blink( PB3, PB2 );
        blink( PB2, PB3 );


        WDTCR = _BV(WDTIE) |  _BV(WDP2) | _BV(WDP1);    // enable WDT Interrupt, Set WDT 1S    
        wdt_reset();
        sei();
        sleep_mode();
        cli();

        WDTCR = _BV(WDTIE) |  _BV(WDP2) | _BV(WDP0);    // enable WDT Interrupt, Set WDT 500MS
        wdt_reset();
        sei();
        sleep_mode();
        cli();
  
    }
 
    return 0;
}


