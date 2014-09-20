/*
  Robot generic modules
 */
#include <SoftwareSerial.h> 
 
//Software Serial Port #define RxD 10 #define TxD 11 
SoftwareSerial blueToothSerial(2,3); 

int ENB = 3;
int IN4 = 4;
int IN3 = 5;

int ENA = 9;
int IN2 = 10;
int IN1 = 11;

int direction = 3; //0 forward, 1 backward

void disableMotor() {
  analogWrite (ENB, 0);
  analogWrite(ENA, 0);
}

void enableMotor() {
  analogWrite (ENB, 255);
  analogWrite(ENA, 240);

}

// the setup routine runs once when you press reset:
void setup() {                
  pinMode(ENB, OUTPUT);     
  pinMode(IN4, OUTPUT);     
  pinMode(IN3, OUTPUT);     
  pinMode(ENA, OUTPUT);     
  pinMode(IN2, OUTPUT);     
  pinMode(IN1, OUTPUT);       
  disableMotor();
  blueToothSerial.begin(9600); 
  Serial.begin(9600);
  while(blueToothSerial.available()) {
    blueToothSerial.read();
  }
}

// the loop routine runs over and over again forever:
void loop() {
  String command = "";
  byte rangeA = 255;
  readInstruction(command, rangeA);
  if(command ==  "AF") {
    turnOnMotorA(rangeA);
    motorAForward();
  } else if (command == "AB") {
    turnOnMotorA(rangeA);
    motorABackward();
  } else if (command == "AR") {
    motorABrake();
  } else if (command == "BF") {
     turnOnMotorB(rangeA);
    motorBForward();
  } else if (command == "BB") {
    turnOnMotorB(rangeA);
    motorBBackward();
  } else if (command == "BR") {
    motorBBrake();
  } else if (command == "NA") {
    // Do nothing

  }
  delay(10);
}


/*****************************************************************/
/* read bluetooth instruction                                    */
/*****************************************************************/

// Stating with 2 character instruction for simplicity
/*
   AF : motor A forward
   AB : Motor A backward
   AR : Motor A brake
   BF : motor B forward
   BB : motor B backward
   BR : motor B barke
   NA : do nothing 
   so we always expect 2 byte
*/
void readInstruction(String &command, byte &range) {
  command = "";
  if (blueToothSerial.available() >=3) {
    char b1 = blueToothSerial.read();
    char b2 = blueToothSerial.read();
    range = blueToothSerial.read();
    command +=b1;
    command += b2;
    Serial.println(command + "(" +range +")");
//    blueToothSerial.println(command);
  } else {
    command = "NA";
  }
}


/*****************************************************************/
/* Motor controlled commands                                     */
/*****************************************************************/
void turnOnMotorA(byte val) {
  analogWrite(ENA, val);
}

void turnOnMotorB(byte val) {
  analogWrite(ENB, val);
}

void turnOffMotorA() {
  analogWrite(ENA, 0);
}

void turnOffMotorB() {
   analogWrite(ENB, 0);
}

void motorAForward() {
    digitalWrite(IN2, HIGH);
    digitalWrite(IN1, LOW);
}

void motorABackward() {
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, HIGH);
}

void motorABrake() {
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, LOW);
}

void motorBForward() {
    digitalWrite(IN4, HIGH);
    digitalWrite(IN3, LOW);  
}


void motorBBackward() {
    digitalWrite(IN4, LOW);
    digitalWrite(IN3, HIGH);  
}

void motorBBrake() {
    digitalWrite(IN4, LOW);
    digitalWrite(IN3, LOW);
}







