#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

constexpr uint16_t ADDRESS = 0xfe01;
constexpr uint16_t COMMAND_POWER = 0xfc03;
constexpr uint16_t COMMAND_SWITCH_INPUT = 0xfb04;


static inline void carrierTurnOn() {
    DDRB |= _BV(0);
}

static inline void carrierTurnOff() {
    DDRB &= ~_BV(0);
}

static void sendWord(uint16_t data) {
    uint16_t mask = 1;
    do {
        carrierTurnOn();
        _delay_ms(0.5625);
        carrierTurnOff();

        if (data & mask) {
            _delay_ms(1.6875);
        } else {
            _delay_ms(0.5625);
        }
        mask = mask << 1u;
    } while (mask);
}

static void sendNecCode(uint16_t address, uint16_t command) {
    PORTB |= _BV(1);

    carrierTurnOn();
    _delay_ms(9.0);
    carrierTurnOff();
    _delay_ms(4.5);

    sendWord(address);
    sendWord(command);

    carrierTurnOn();
    _delay_ms(0.5625);
    carrierTurnOff();

    PORTB &= ~_BV(1);
}

int main() {
    DDRB |= _BV(1);
    PORTB &= ~_BV(0);

    wdt_disable();

    carrierTurnOff();

    _delay_ms(10.0);

    sendNecCode(ADDRESS, COMMAND_POWER);

    _delay_ms(500.0);
    _delay_ms(500.0);
    _delay_ms(500.0);

    sendNecCode(ADDRESS, COMMAND_SWITCH_INPUT);

    while (true) {
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
    }
}
