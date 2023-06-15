#define BT_TOGGLE 5
#define BT_WARP 4
#define BT_REPAIR 3
#define BT_BRAKE 2
#define AXIS_1 A0 // Right throttle
#define AXIS_2 A1 // Right tilt
#define AXIS_3 A2 // Left tilt
#define AXIS_4 A3 // Left throttle

#include <Joystick.h>
#include <EEPROM.h>

Joystick_ Joystick(0x03, 0x4, 5, 0, true, true, true, false, false, false, false, false, false, false, false);

const int pinToButtonMap = 2;

int lastButtonState[4] = {0,0,0};

int p_toll = 5; // Tollerance (in percentage) over data from axis

int calibration[] = {240,440,55,254,150,327,449,670};

void repr_calibration(){
  for(int i=0; i<8; i++){
    Serial.println(calibration[i]);
  }
}

int readIntFromEEPROM(int address)
{
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  return (byte1 << 8) + byte2;
}


void read_calibration(){
  Serial.println("Attempting data load from EEPROM...");
  int tmp;
  for(int i=0; i<16; i=i+2){
    calibration[i/2] = readIntFromEEPROM(i);;
  }
  Serial.println("Calibration data loaded from EEPROM.");
  repr_calibration();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(BT_WARP, INPUT_PULLUP);
  pinMode(BT_REPAIR, INPUT_PULLUP);
  pinMode(BT_TOGGLE, INPUT_PULLUP);
  pinMode(BT_BRAKE, INPUT_PULLUP);
  pinMode(AXIS_1, INPUT);
  pinMode(AXIS_2, INPUT);
  pinMode(AXIS_3, INPUT);
  pinMode(AXIS_4, INPUT);
  Serial.begin(9600);
  delay(1000);
  read_calibration();
  Joystick.setXAxisRange(-100, 100);
  Joystick.setYAxisRange(0, 1);
  Joystick.setZAxisRange(0, 100);
  Joystick.begin();
}

void handle_buttons(){
  bool override = false;
  for (int index = 0; index < 3; index++)
  {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState == HIGH)
    {
      
      lastButtonState[index] = currentButtonState;
    }
    else{
      
      lastButtonState[index] = currentButtonState;
    }
  }
  for(int index = 0; index < 3; index++){
    if(index == 0 && lastButtonState[0] && lastButtonState[1]){
      Joystick.setButton(2,1);
      Joystick.setButton(1,0);
      Joystick.setButton(0,0);
      override = true;
    }
    else{
      if(index==2 && override == true){

      }
      else{
        Joystick.setButton(index, lastButtonState[index]);
      }
      
    }
    
  }
}

int to_percent(int min, int max, int value){
  return map(value, min, max, 0, 100);;
}

int handle_y(){
    int currentButtonState = !digitalRead(BT_TOGGLE);
    if (currentButtonState)
    {
      return 1;
    }
    return 0;
}

int handle_x(int perc_l, int perc_r){
  if(perc_l-p_toll < perc_r && perc_l+p_toll > perc_r){
    return 0;
  }
  else if (perc_r-p_toll < perc_l && perc_r+p_toll > perc_l){
    return 0;
  }
  return (perc_l - perc_r);
}

int handle_throttle(int perc_l, int perc_r){
  if(perc_l>perc_r){
    return perc_l;
  }
  else{
    return perc_r;
  }
}

void handle_ry(int perc_l, int perc_r){
  Serial.println(perc_r);
  Serial.println(perc_l);
  Serial.println("====");
  if(perc_l < 15 && perc_r < 15){
    Joystick.setButton(3, 1);
  }
  else{
    Joystick.setButton(3, 0);
  }
  if(perc_l>85 && perc_r > 85){
    Joystick.setButton(4, 1);
  }
  else{
    Joystick.setButton(4, 0);
  }
}

void handle_axis(){
  int r_thr = to_percent(calibration[0], calibration[1], analogRead(AXIS_1));
  int r_til = to_percent(calibration[2], calibration[3], analogRead(AXIS_2));
  int l_til = to_percent(calibration[4], calibration[5], analogRead(AXIS_3));
  int l_thr = to_percent(calibration[6], calibration[7], analogRead(AXIS_4));
  // Calculate X axis according to throttle level on both sides;
  int x_axis = handle_x(l_thr, r_thr);
  // Calculate Y axis according to toggle status;
  int y_axis = handle_y();
  // Calculate throttle by selecting the highest throttle level;
  int throttle = handle_throttle(l_thr, r_thr);
  // Calculate ry axis according to tilt controls;
  handle_ry(l_til, r_til);
  Joystick.setXAxis(x_axis);
  Joystick.setYAxis(y_axis);
  Joystick.setZAxis(throttle);
}

void loop() {
  handle_buttons();
  handle_axis();
  delay(50);
}
