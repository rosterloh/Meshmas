#include "Particle.h"

SYSTEM_THREAD(ENABLED); // run system and app on different threads

#define NUM_COLUMNS     (4)
#define NUM_COLORS      (3)
#define NUM_BTN_ROWS    (1)
#define NUM_BTN_COLUMNS (4)
#define SWITCH_PIN      (D13)
#define MAX_DEBOUNCE    (3)

static uint8_t LED_outputs[NUM_COLUMNS];
static int8_t debounce_count[NUM_BTN_COLUMNS];
static int32_t next_scan;

static const uint16_t ledcolumnpins[NUM_COLUMNS]    = { D5, D6, D7, D8 };
static const uint16_t btncolumnpins[NUM_COLUMNS]    = { D0, D1, D2, D3 };
static const uint16_t colorpins[NUM_COLORS]         = { A0, A1, A2 };

static void scan()
{
    static uint8_t current = 0;
    uint8_t val;
    uint8_t i;
    
    // Select a column
    digitalWrite(btncolumnpins[current], LOW);
    digitalWrite(ledcolumnpins[current], LOW);
    
    val = (LED_outputs[current] & 0x03);
    
    if(val)
    {
        digitalWrite(colorpins[val-1], HIGH);
    }
    
    // pause a moment to let led glow
    delay(1);
    
    // read the button
    val = digitalRead(SWITCH_PIN);
        
    if(val == LOW)
    {
        if (debounce_count[current] < MAX_DEBOUNCE)
        {
            debounce_count[current]++;
            if (debounce_count[current] == MAX_DEBOUNCE)
            {
                Mesh.publish("mode", current);
                LED_outputs[current]++;
            }
        }
    } else {
        // otherwise, button is released
        if (debounce_count[current] > 0)
        {
            debounce_count[current]--;
            if (debounce_count[current] == 0)
            {
                //Particle.publish("key-up", String(current));
            }
        }
    }
    
    delay(1);
    
    digitalWrite(btncolumnpins[current], HIGH);
    digitalWrite(ledcolumnpins[current], HIGH);
    
    for(i = 0; i < NUM_COLORS; i++)
    {
        digitalWrite(colorpins[i], LOW);
    }

    // Move on to the next column
    current++;
    if (current >= NUM_COLUMNS)
    {
        current = 0;
    }
}

void setup()
{
    uint8_t i;
    
    for(i = 0; i < NUM_COLUMNS; i++)
    {
        // led columns
        pinMode(ledcolumnpins[i], OUTPUT);
        digitalWrite(ledcolumnpins[i], HIGH);
        // button columns
        pinMode(btncolumnpins[i], OUTPUT);
        digitalWrite(btncolumnpins[i], HIGH);
    }
    
    // button row
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    
    // LED drive lines
    for(i = 0; i < NUM_COLORS; i++)
    {
        pinMode(colorpins[i], OUTPUT);
        digitalWrite(colorpins[i], LOW);
    }

    // Initialise the LED display array
    for(i = 0; i < NUM_COLUMNS; i++)
    {
        debounce_count[i] = 0;
        LED_outputs[i] = 0;
    }
    
    // init global variables
    next_scan = millis() + 1;
}

void loop() 
{
    if(millis() >= next_scan)
    {
        next_scan = millis() + 1;
        scan();
    }
}