int openPin = 7;
int closePin = 8;
byte com = 0;
bool isOpen = false; 
bool wakeCommand = false;
void setup() {
  // Set Pin Out modes
  pinMode(closePin, OUTPUT);
  pinMode(openPin, OUTPUT);
  //Begin serial session
  Serial.begin(9600);
  delay(2000);
  //Send Wait Mode and Compact Mode Hex
  Serial.write(0xAA);
  Serial.write(0x37);
  delay(1000);
  //Send Wait mode and Load Command 1 Hex
  Serial.write(0xAA);
  Serial.write(0x21);
}

void loop() {
  // put your main code here, to run repeatedly:
  com = Serial.read();
  if(com == 0x11){
    wakeCommand = true;
  }
  if(wakeCommand == true){
    if(com == 0x12 && isOpen == false){
      digitalWrite(openPin, HIGH);
      digitalWrite(closePin, LOW);
      wakeCommand = false;
      isOpen = true;
    } else if(com == 0x13 && isOpen == true){
      digitalWrite(openPin, LOW);
      digitalWrite(closePin, HIGH);
      wakeCommand = false;
      isOpen = false;
    } else if(com == 0x15){
      if(isOpen == true){
        digitalWrite(closePin, HIGH);
        digitalWrite(openPin, LOW);
      }
    } 
  }
}