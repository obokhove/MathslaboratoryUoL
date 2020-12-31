// Initialise Constants
const int 
PWM_A   = 3,
DIR_A   = 12,
BRAKE_A = 9,
SNS_A   = A0;
int counter = 0;
int counter_lim = 2;
int pwm = 255;
int period = 1600;   // Arbitrary value, to be changed in program.

// Set Switch Inputs
int val; 
 int switchA = 6;
 int switchB = 7;
 int switchC = 5;
 int normal = 2;
 int encoderPos = 0;
 int switchALast = LOW;
 int a = LOW;
 int b = LOW;
 int c = LOW;
 int norm = LOW;
 
void setup() {
  //MOTOR
  // Configure the A output
  pinMode(BRAKE_A, OUTPUT);  // Brake pin on channel A
  pinMode(DIR_A, OUTPUT);    // Direction pin on channel A

  //Switches
  pinMode (switchA,INPUT);
  pinMode (switchB,INPUT);
  pinMode (switchC,INPUT);
  pinMode (normal,INPUT);  
  digitalWrite(switchA,HIGH); 
  digitalWrite(switchB,HIGH); 
  digitalWrite(switchC,HIGH);
  digitalWrite(normal,HIGH); 
  digitalWrite(BRAKE_A, HIGH);
  
  // Open Serial communication
  Serial.begin(9600);
  Serial.println("Motor shield DC motor Test:\n");
 
}

void loop() {
// Read Switches
norm = digitalRead(normal);
a = digitalRead(switchA);
b = digitalRead(switchB);
c = digitalRead(switchC);

// Set Period and/or Direction
if(norm ==LOW) {
pwm = 255;
//period = 1280;
period = 1280;
digitalWrite(DIR_A, HIGH); 
digitalWrite(BRAKE_A, HIGH);
}
if(norm == HIGH){
pwm = 175;
period = 850; 
digitalWrite(DIR_A, LOW);
digitalWrite(BRAKE_A, HIGH);
}

// ------- Continuous Waves -----------//
if(a == LOW){
  
// Run half a loop forward
while(counter <1){
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disables motor brake
  digitalWrite(DIR_A, HIGH);   // setting direction to HIGH the motor spins forward

  analogWrite(PWM_A, pwm);     // Set the speed of the motor, 255 is the maximum value
  delay(period/4);             // hold the motor at full speed for (P/4) seconds
  digitalWrite(BRAKE_A, HIGH);
  counter++;
}

// Run back and forth
while(counter<counter_lim){
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disables motor brake
  digitalWrite(DIR_A, LOW);    // setting direction to LOW the motor spins backward

  analogWrite(PWM_A, pwm);     // Set the speed of the motor, 255 is the maximum value
  delay(period/2);             // hold the motor at full speed for (P/2) seconds
  
  // Brake the motor
  digitalWrite(BRAKE_A, HIGH);  // raise the brake

// Set the outputs to run the motor forwards
  digitalWrite(BRAKE_A, LOW);  
  digitalWrite(DIR_A, HIGH);    // now change the direction to Forward setting HIGH the DIR_A pin

  analogWrite(PWM_A, pwm);      // Set the speed of the motor
  delay(period/2);
  
  // Brake
  digitalWrite(BRAKE_A, HIGH);  // raise the brake
 
 counter++;                     // increment counter
}

// Run Backwards Again
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, LOW);    // setting direction to LOW the motor will spin backward

  analogWrite(PWM_A, pwm);     // Set the speed of the motor, 255 is the maximum value

  delay(period/2);             // hold the motor at full speed for (P/2) seconds


// Run half a loop forwards
while(counter == counter_lim){
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, HIGH);   // setting direction to HIGH the motor will spin forwards

  analogWrite(PWM_A, pwm);     // Set the speed of the motor, 255 is the maximum value
  delay(period/4);
  digitalWrite(BRAKE_A, HIGH);
  counter++;
}
}
counter = 0;

// ------------ Single Wave ---------- //
if(b == LOW){
// Run half a loop forward
while(counter <1){
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, HIGH);   // setting direction to HIGH the motor will spin forward

  analogWrite(PWM_A, pwm);     // Set the speed of the motor, 255 is the maximum value
  delay(period/4);             // hold the motor at full speed for (P/4) seconds
  digitalWrite(BRAKE_A, HIGH);
  counter++;
}

// Run back and forth
while(counter<counter_lim){
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, LOW);    // setting direction to LOW the motor will spin backward

  analogWrite(PWM_A, pwm);     // Set the speed of the motor, 255 is the maximum value

  delay(period/2);             // hold the motor at full speed for (P/2) seconds
  
  // Brake the motor
  digitalWrite(BRAKE_A, HIGH);  // raise the brake

// Set the outputs to run the motor forwards
  digitalWrite(BRAKE_A, LOW);  // setting againg the brake LOW to disable motor brake
  digitalWrite(DIR_A, HIGH);   // now change the direction to Forward setting DIR_A pin HIGH

  analogWrite(PWM_A, pwm);     // Set the speed of the motor
  delay(period/2);
  
  // Brake
  digitalWrite(BRAKE_A, HIGH);  // raise the brake
 
 counter++;
}

// Run half a loop backward
while(counter == counter_lim){
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(DIR_A, LOW);    // setting direction to LOW the motor will spin backward

  analogWrite(PWM_A, pwm);     // Set the speed of the motor, 255 is the maximum value
  delay(period/4);
  digitalWrite(BRAKE_A, HIGH);
  counter++;
}
  
counter = 0; 
}

// -------------- Adjust Position ------------------//
// Adjustment
if(c == LOW) {
   
  // Set Speed
  pwm = 50;
  
  // Run for (P/8) seconds and brake
  digitalWrite(BRAKE_A, LOW);      
  analogWrite(PWM_A, pwm);      
  delay(period/8);
  digitalWrite(BRAKE_A, HIGH); 
}

}
