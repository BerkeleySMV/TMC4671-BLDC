byte bldc_step;
void setup() {
  //Serial.begin(9600);
  DDRD |= B11100000;
  PCICR  = 1;                        // Enable pin change interrupt for pins 8 to 13
  PCMSK0 = 7;                         // Enable pin change interrupt for pins 8, 9 and 10
  bldc_step = 0;
}
ISR (PCINT0_vect){
  bldc_step = (~PINB & 7);              // Read and save hall effect sensors status (PINB: read from PORTB which is arduino pins 8..13)
  bldc_move();                       // Move the BLDC motor
}
void bldc_move() {
  //Serial.println(step, BIN);
  switch(bldc_step) {
    case 1:
      PORTD = B00100000;
      break;
    case 2:
      PORTD = B01000000;
      break;
    case 3:
      PORTD = B01100000;
      break;
    case 4:
      PORTD = B10000000;
      break;
    case 5:
      PORTD = B10100000;
      break;
    case 6:
      PORTD = B11000000;
      break;
    case 7:
      PORTD = B11100000;
      break;
    default:
      PORTD = 0;
      break;
  }
  //delay(5000);
}
void loop(){
  
}
