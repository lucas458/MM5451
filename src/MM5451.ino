
#define DATA  PB0 // D8
#define CLK   PB1 // D9

bool buttonPressed;

uint8_t SEGMENT_MAP[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
uint8_t counters[6];
uint8_t displayBuffer[35];

uint8_t displaySegmentDigitsOutputs[5][8] = {
  {3, 4, 5, 6, 7, 8, 9, 10},
  {27, 28, 29, 30, 31, 32, 33, 34},
  {19, 20, 21, 22, 23, 24, 25, 26},
  {11, 12, 13, 14, 15, 16, 17, 18}
};




void setCurrentBase( uint8_t base ){
  displayBuffer[0] = (base == 1);
  displayBuffer[1] = (base == 2);
}




void setLeds(uint8_t data){

  for (uint8_t i = 0; i < 6; i++){

    if ( data & 1 << i ){
      displayBuffer[11+i] = 1;
    }else{
      displayBuffer[11+i] = 0;
    }

  }

}




void setDigit(uint8_t data, uint8_t digit){
  
  if ( digit > 4 ){
    return;
  }

  if ( digit == 4 ){
    digit = 0;
  }

  for (uint8_t i = 0; i < 8; i++){
    uint8_t outputBit = displaySegmentDigitsOutputs[digit][i];

    if ( data & 1 << i ){
      displayBuffer[outputBit] = 1;
    }else{
      displayBuffer[outputBit] = 0;
    }

  }

}




void clearDisplay(){
  
  PORTB &= ~(1 << DATA);

  for (uint8_t i = 0; i < 35; i++){ 
    // CLOCK
    PORTB |= 1 << CLK;
    delayMicroseconds(4);
    PORTB &= ~(1 << CLK);
    delayMicroseconds(4);
  }

}




void updateDisplay(){

  clearDisplay();

  // START bit
  PORTB |= 1 << DATA;
  // CLOCK
  PORTB |= 1 << CLK;
  delayMicroseconds(4);
  PORTB &= ~(1 << CLK);
  delayMicroseconds(4);

  for (uint8_t i = 0; i < sizeof(displayBuffer); i++){

    // DATA
    if ( displayBuffer[i] ){
      PORTB |= 1 << DATA;
    }else{
      PORTB &= ~(1 << DATA);
    }

    // CLOCK
    PORTB |= 1 << CLK;
    delayMicroseconds(4);
    PORTB &= ~(1 << CLK);
    delayMicroseconds(4);

  }

}





void setup() {
  // CLK, DATA
  DDRB  = (1 << DDB1) | (1 << DDB0); 
  PORTB = 0x00;

  // D7 to D2 -- INPUT_PULLUP
  DDRD  &= ~0xFC;
  PORTD |= 0xFC;
  
  buttonPressed = false;

}





void loop() {
  
  uint8_t buttonBuffer = PIND;

  if ( !(buttonBuffer & 1 << 7) || !(buttonBuffer & 1 << 6) || !(buttonBuffer & 1 << 5) || !(buttonBuffer & 1 << 4) || !(buttonBuffer & 1 << 3) || !(buttonBuffer & 1 << 2) ){
    
    if ( !buttonPressed ){
      buttonPressed = true;

      for (uint8_t i = 2; i <= 7; i++){

        if ( !(buttonBuffer & 1 << i) ){

          if ( i-2 == 5 ){
            counters[i-2] = (counters[i-2] + 1) % 64;
          }else{
            counters[i-2] = (counters[i-2] + 1) % 10;
          }

          break;
        }

      }
      
    }

  }else{
    buttonPressed = false;
  }

  

  setCurrentBase(2);
  setLeds( counters[5] );
  setDigit( SEGMENT_MAP[ counters[4] ], 0 );
  updateDisplay();
  delay(5);
  setCurrentBase(1);
  setDigit( SEGMENT_MAP[ counters[3] ], 1 );
  setDigit( SEGMENT_MAP[ counters[2] ], 2 );
  setDigit( SEGMENT_MAP[ counters[1] ], 3 );
  setDigit( SEGMENT_MAP[ counters[0] ], 4 );
  updateDisplay();
  delay(5);

}













