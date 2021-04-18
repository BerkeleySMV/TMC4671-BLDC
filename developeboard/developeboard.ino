#include <SPI.h>
#include "developeboard.h"
#include "src/TMC4671.h"
void setup() {
  SPI.begin();                            
  SPI.setClockDivider(SPI_CLOCK_DIV8); 
  digitalWrite(SS,HIGH);   
}
uint8_t tmc4671_readwriteByte(uint8_t motor, uint8_t data, uint8_t lastTransfer) {
  return digitalRead(2);
}

void loop(){
  tmc4671_readInt(0x00, 0xFF);
}
