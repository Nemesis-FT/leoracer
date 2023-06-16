#define AXIS_1 A0 // Right throttle
#define AXIS_2 A1 // Right tilt
#define AXIS_3 A2 // Left tilt
#define AXIS_4 A3 // Left throttle
#define BT_NEXT 2 // Right button

#include <EEPROM.h>
// Current state
int status = 0;
// Calibration vector
int calibration[] = {0,255,0, 255,0, 255,0, 255};
// Pins of the analog sources
int pins[] = {A0, A1, A2, A3};


void setup() {
  // I/O Setup
  pinMode(AXIS_1, INPUT);
  pinMode(AXIS_2, INPUT);
  pinMode(AXIS_3, INPUT);
  pinMode(AXIS_4, INPUT);
  pinMode(BT_NEXT, INPUT_PULLUP);
  Serial.begin(9600);
  // Erase the eeprom
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  Serial.println("All data erased. Ready for calibration.");
}

void repr_calibration(){
  // Print the contents of the calibration vector
  for(int i=0; i<8; i++){
    Serial.println(calibration[i]);
  }
}

void read_calibration(){
  // Try to read the calibration data
  Serial.println("Attempting data load from EEPROM...");
  int tmp;
  for(int i=0; i<16; i=i+2){
    calibration[i/2] = readIntFromEEPROM(i);;
  }
  Serial.println("Calibration data loaded from EEPROM.");
  repr_calibration();
}

void writeIntIntoEEPROM(int address, int number)
{ 
  // 2 bytes are needed in order to properly store an integer
  byte byte1 = number >> 8;
  byte byte2 = number & 0xFF;
  EEPROM.write(address, byte1);
  EEPROM.write(address + 1, byte2);
}

int readIntFromEEPROM(int address)
{
  // Read an int from a starting address
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  return (byte1 << 8) + byte2;
}

void save(){
  // Save calibration data
  for(int i=0; i<16; i=i+2){
    writeIntIntoEEPROM(i, calibration[i/2]);
  }
  Serial.println("Saved calibration data to EEPROM.");
}

void loop() {
  // Calibrate the axis one by one
  if(!digitalRead(BT_NEXT) && status <8){
    calibration[status] = analogRead(pins[status/2]);
    status+=1;
    Serial.println("OK");
    delay(1000);
  }
  if(status==8){
    // Saving state, then deadlock
    repr_calibration();
    save();
    status+=1;
    delay(1000);
    read_calibration();
  }
}
