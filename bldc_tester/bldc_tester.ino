#include <SPI.h>
#include "bldc_tester.h"
#include "src/TMC4671.h"

int MOTORS[] = { 0 };

int MOTOR_TYPE = TMC4671_THREE_PHASE_BLDC;
int MOTOR_NPP = 4; // number of pole pairs

void setup() {

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  digitalWrite(SS, HIGH);

  for (int i = 0; i < sizeof(MOTORS) - 1; i++) {
    // motor type configuration
    tmc4671_writeInt(MOTORS[i], TMC4671_MOTOR_TYPE_N_POLE_PAIRS, 0x00030004);
    tmc4671_writeInt(MOTORS[i], TMC4671_MODE_RAMP_MODE_MOTION, 0x00000000); // 0: nothing, 1-2: velocity-torque, 5-6: PRBS, 10-11: AGPI_A, 13-14: PWM_I
    
    // pwm configuration
    tmc4671_writeInt(MOTORS[i], TMC4671_PWM_POLARITIES, 0x00000000); 
    tmc4671_writeInt(MOTORS[i], TMC4671_PWM_SV_CHOP, 0x00000017); // centered PWM w/ SVPWM

    // encoder configuration
    tmc4671_writeInt(MOTORS[i], TMC4671_PHI_E_SELECTION, 0x00000000);
    tmc4671_writeInt(MOTORS[i], TMC4671_VELOCITY_SELECTION, 0x00000000);
    tmc4671_writeInt(MOTORS[i], TMC4671_POSITION_SELECTION, 0x00000000);

    // PID parameter configuration in order (open --> torque --> velocity -\-> position [won't be using position most likely])
    tmc4671_writeInt(MOTORS[i], TMC4671_PID_TORQUE_FLUX_OFFSET, 0x00000000);
    tmc4671_writeInt(MOTORS[i], TMC4671_PID_VELOCITY_OFFSET, 0x00000000);
    tmc4671_writeInt(MOTORS[i], TMC4671_PID_VELOCITY_LIMIT, 0x00000000);
    tmc4671_writeInt(MOTORS[i], TMC4671_PID_FLUX_P_FLUX_I, 0x00000000);
    tmc4671_writeInt(MOTORS[i], TMC4671_PID_TORQUE_P_TORQUE_I, 0x00000000);
    tmc4671_writeInt(MOTORS[i], TMC4671_PID_VELOCITY_P_VELOCITY_I, 0x00000000);
    
    Serial.begin(9600);
    
  }

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

void loop() {

  tmc4671_writeInt(MOTORS[0], TMC4671_PID_VELOCITY_TARGET, 0x00000000);
  Serial.println(tmc4671_readInt(MOTORS[0], TMC4671_PID_VELOCITY_ACTUAL));

}
