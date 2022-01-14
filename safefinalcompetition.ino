//Definitions
#define PHOTORESISTOR A0
#define BUTTON_ACTIVE 4

#define CW  1
#define CCW 0

#define STEPPER_PIN_1 8
#define STEPPER_PIN_2 9
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 11

double x = 0;
boolean opened = 0;
int step_number = 0;
const int STEPS_PER_ROTATION = 2048;

void setup() {
  Serial.begin(9600);
  pinMode(0,INPUT);

  pinMode(PHOTORESISTOR,INPUT);
  pinMode(BUTTON_ACTIVE,INPUT);
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);

  //rotateMotor(90, CCW);
  //Serial.println("Rotated");
 
}

void loop() {
  /*if(digitalRead(0)==HIGH){
  rotateMotor(90, CW);
  delay(5000)
  opened==1;
}
  */
  x = analogRead(PHOTORESISTOR);
  Serial.println(x);
  delay(100);
 
  if (digitalRead(BUTTON_ACTIVE) == HIGH) {
    Serial.println("Button Activated");
    if ( x > 400) {
      Serial.println("clockwise");
      rotateMotor(90,CW );
      delay(500);
      opened = 1;
    } else {
      Serial.println("Not Within Range");
    }
    delay(500);
  }

  if (opened == true) {
    while (opened){
      if (digitalRead(4)==HIGH){
        rotateMotor(90,CCW);
      } 
    }
  }
}


void OneStep(bool dir) {
  if (dir) {
    switch (step_number) {
      case 0:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
    }
  } else {
    switch (step_number) {
      case 0:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);


    }
  }
  step_number++;
  if (step_number > 3) {
    step_number = 0;
  }
}

void rotateMotor(float deg, bool direction) {
  float rotations = (STEPS_PER_ROTATION / 360.0) * deg;

  for (int i = 1; i <= rotations; i++) {
    OneStep(direction);
    Serial.println(i);
    delay(2);
  }
  
}
