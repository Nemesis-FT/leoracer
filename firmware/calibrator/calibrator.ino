#define AXIS_1 A0 // Right throttle
#define AXIS_2 A1 // Right tilt
#define AXIS_3 A2 // Left tilt
#define AXIS_4 A3 // Left throttle
#define BT_NEXT 2 // Right button

#include <EEPROM.h>

int status = 0;
int calibration[] = {0,255,0, 255,0, 255,0, 255};
int pins[] = {A0, A1, A2, A3};


void setup() {
  // put your setup code here, to run once:
  pinMode(AXIS_1, INPUT);
  pinMode(AXIS_2, INPUT);
  pinMode(AXIS_3, INPUT);
  pinMode(AXIS_4, INPUT);
  pinMode(BT_NEXT, INPUT_PULLUP);
  Serial.begin(9600);
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  Serial.println("All data erased. Ready for calibration.");
}

void repr_calibration(){
  for(int i=0; i<8; i++){
    Serial.println(calibration[i]);
  }
}

void save(){
  for(int i=0; i<8; i++){
    EEPROM.write(i, calibration[i]);
  }
  Serial.println("Saved calibration data to EEPROM.");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(BT_NEXT) && status <8){
    calibration[status] = analogRead(pins[status/2]);
    status+=1;
    Serial.println("OK");
    delay(1000);
  }
  if(status==8){
    repr_calibration();
    save();
    status+=1;
    delay(1000);
  }
}
