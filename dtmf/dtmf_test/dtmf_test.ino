#define PIN_DTMF_STD 9
#define PINS_DTMF_DATA PINB
#define PINS_DTMF_DATA_LSB 2

void setup()
{
  pinMode(LATCH,OUTPUT);
  pinMode(CLK,OUTPUT);
  pinMode(DATA,OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON1, INPUT);    // I/O-Pin als Eingang
  digitalWrite(BUZZER, HIGH); // BUZZER aus (Low-Aktiv)

  pinMode(PIN_DTMF_STD, INPUT);

  TCCR1A = 0;                 // Register loeschen
  OCR1A = 1000;               // Vergleichswert x = (CPU / (2 x Teiler x f)) - 1
  TCCR1B |= (1 << CS10) | (1 << CS11) | (1 << WGM12);   // CTC-Mode, Teiler = 64
  TIMSK1 |= (1 << OCIE1A);   // Output Compare A Match Interrupt Enable
  sei();                     // IRQ Enable
}

void loop()
{
  uint8_t dtmfValue, dtmfState;
  static uint8_t dtmfState_old = LOW;
  uint16_t value;

  dtmfState = digitalRead(PIN_DTMF_STD);
  if( (dtmfState == HIGH) && (dtmfState_old == LOW) )
  {
    dtmfValue = PINS_DTMF_DATA;
    dtmfValue = dtmfValue >> PINS_DTMF_DATA_LSB;
    if(dtmfValue >= 10)
    {
      dtmfValue = 0;
    }
    value = DisplayValue;
    value = ((uint32_t)value * 10) % 10000;
    value += dtmfValue;
    DisplayValue = value;
  }
  dtmfState_old = dtmfState;
} 