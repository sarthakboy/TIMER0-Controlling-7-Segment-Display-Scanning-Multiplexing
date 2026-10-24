# AVR Timer0-Based 7-Segment Display Multiplexing

An Embedded C project demonstrating **Timer0 overflow interrupts and multiplexed 7-segment display control** using an AVR microcontroller.

The project displays a date in `DD-MM-YY` format across eight seven-segment digits. Timer0 generates periodic overflow interrupts, and the ISR refreshes one digit at a time to create the appearance of a continuously displayed date.

**Microcontroller clock:** 16 MHz

**Programming language:** Embedded C

**Timer:** AVR Timer0, Normal/Overflow mode

## 🚀 Features

- **Timer0 Overflow Interrupt:** Uses the Timer0 overflow interrupt to refresh the display periodically.
- **8-Digit Multiplexing:** Activates one digit at a time, cycling through all eight digits.
- **7-Segment Lookup Table:** Converts numeric digits into common-cathode segment patterns.
- **Date Formatting:** Displays a date in `DD-MM-YY` format.
- **Register-Level Programming:** Configures GPIO, Timer0, interrupt masks, and the global interrupt enable.
- **Interrupt-Driven Operation:** Keeps the main loop free while the timer interrupt handles display refresh.

## 🛠️ Hardware and Tools

- AVR microcontroller compatible with the `TCCR0`, `TCNT0`, `TIMSK`, and `TIMER0_OVF_vect` registers
- Eight-digit multiplexed seven-segment display
- Current-limiting resistors and supporting circuitry
- AVR-GCC-compatible development environment
- Simulator or physical hardware, depending on your setup

## ⚙️ Pin Configuration

| AVR pins | Function |
|---|---|
| PORTC (PC0–PC7) | Seven-segment segment data |
| PD0–PD7 | Digit selection lines |

The code sets `PORTD` to `0xFF` and clears one digit-select bit at a time. This indicates **active-low digit selection**.

The segment lookup table is intended for a common-cathode display. Confirm the display type, wiring, and segment order against your actual circuit.

## 🧠 How It Works

### 1. Timer0 configuration

Timer0 is configured with a prescaler of 64:

```c
TCCR0 = (1 << CS01) | (1 << CS00);
TCNT0 = 6;
TIMSK |= (1 << TOIE0);
sei();
```

- `CS01` and `CS00` select a prescaler of 64 on the assumed AVR timer configuration.
- `TCNT0 = 6` sets the starting counter value.
- `TOIE0` enables the Timer0 overflow interrupt.
- `sei()` enables global interrupts.

### 2. Timer overflow interrupt

```c
ISR(TIMER0_OVF_vect)
{
    TCNT0 = 6;
    display_Date(120408, mode);

    mode++;
    if (mode == 8) {
        mode = 0;
    }
}
```

Whenever Timer0 overflows, the ISR reloads the counter, refreshes the current digit, and advances to the next digit. After digit 7, scanning starts again at digit 0.

### 3. Multiplexed display

The `display_Date()` function extracts individual digits from the supplied numeric date and uses `mode` to select which digit is displayed.

For the current value `120408`, the intended display is:

**12-04-08**

Each digit is activated separately while its segment pattern is written to `PORTC`. Rapidly repeating this sequence makes all eight digits appear illuminated continuously.

## 📚 Concepts Practiced

- AVR Timer0 and prescalers
- Timer overflow interrupts
- Interrupt Service Routines (ISRs)
- Seven-segment display encoding
- Multiplexing multiple display digits
- GPIO register manipulation
- Bitwise operations and bit masks
- Numeric digit extraction using division and modulo

## 🔧 Possible Improvements

- Calculate and document the actual timer interrupt frequency.
- Move lengthy processing and digit extraction outside the ISR.
- Add blanking between digit changes to reduce ghosting.
- Use a variable date instead of a hard-coded value.
- Verify the refresh rate and display brightness on the target circuit.
- Add a timer-based system tick for other non-blocking tasks.

## 👨‍💻 Author

**Sarthak Pandey**

Aspiring Embedded Software / Firmware Engineer

**Focus areas:** Embedded C · AVR Microcontrollers · Timers · Interrupts · GPIO · Peripheral Interfacing
