#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

int main() {
#define DELAY_MS    500

    DDRB &= ~_BV(0);
    PORTB &= ~_BV(0);

    for (;;) {
        _delay_ms(DELAY_MS);
    }
}

#pragma clang diagnostic pop