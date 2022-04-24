#include <SPI.h>
#include "lower_level_API.h"
#include "src/TMC4671.h"
boolean transaction_in_progress = false;
void setup() {
  SPI.begin();                            
  SPI.setClockDivider(SPI_CLOCK_DIV8); 
  digitalWrite(SS,HIGH);   
}
uint8_t tmc4671_readwriteByte(uint8_t motor, uint8_t data, uint8_t lastTransfer) {
  if (transaction_in_progress == false) {
    transaction_in_progress = true;
    digitalWrite(SS, LOW);
    return SPI.transfer(data);
  } else {
    uint8_t return_val = SPI.transfer(data);
    if (lastTransfer){
      digitalWrite(SS,HIGH);
      transaction_in_progress = false;
    }
    return return_val;
  }
}

void loop(){
  //tmc4671_readInt(0x00, 0xFF);
}
