/*simple bluetooth robot
*using an HC-06 Bluetooth card (generic, from ebay)
*and a L298N motor controller.
*by Leon Harris, Jan 2017
*
*In this implementation, the data direction is from phone to
*robot, but it doesn't have to be. The phone app is coded in 
*MIT App Inventor 2, available at http://ai2.appinventor.mit.edu
*
*Truth table Left Motor
*IN1    In2   Motor state
* 0       0     stopped (brake)
* 1       0     forwards
* 0       1     backwards
* 1       1     stopped
*
* The truth table is the same for the right motor, but with IN3 and IN4
* substituting for IN1 and IN2
*
* There are two "modes" - step, where a click on a button makes the robot 
* move in the indicated direction for steptime milliseconds. (change this in
* the declaration near the top of this file). The other mode is "run" mode
* in which the robot moves in the direction of the button press until it
* recieves another command.
*
 */


// Bridge pins
int IN1 = 5;
int IN2 = 6;
int IN3 = 7;
int IN4 = 8;

// Define the commands for the robot
static char upCMD[] = "up";
static char downCMD[] = "down";
static char leftCMD[] = "left";
static char rightCMD[] = "right";
static char stopCMD[] = "stop";
static char changetorunCMD[] = "run";
static char changetostepCMD[] = "step";

int sizeofcombuffer = 8 ;
bool stepFlag = true;
int steptime=300; // length of each "step" in milliseconds
char command[8] = {0};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.flush();
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //breaks on both motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);


}

char *readSerial() { // read in commands from the bluetooth via serial port
  int i = 0;
  if (Serial.available() > 0) {
    while (Serial.available() > 0) {
      command[i] = Serial.read();
      i++;
      if (i > sizeofcombuffer) {
        break;
      }
    }
  }
  command[i] = '\0';
  return (command);
}





void loop() {
  // put your main code here, to run repeatedly:

  delay(100); // no idea why a delay is needed, Ardy isn't threaded ! The serial port seems to need it to settle down.

  char *command = readSerial();


  if (strcmp(command, "")) { // don't fill the com monitor unless a new command is present
    Serial.println(command);
  }

  if (!strcmp(command, downCMD)) {
    Serial.println("going down!");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  if (!strcmp(command, upCMD)) {
    Serial.println("going up!");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

  if (!strcmp(command, leftCMD)) {
    Serial.println("going left!");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }

  if (!strcmp(command, rightCMD)) {
    Serial.println("going right!");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

  if (!strcmp(command, stopCMD)) {
    Serial.println("stopping!");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }

  if (!strcmp(command, changetorunCMD)) {
    Serial.println("continuous mode");
    stepFlag = false;
  }
  if (!strcmp(command, changetostepCMD)) {
    Serial.println("stepping mode");
    stepFlag = true;
  }



  if (stepFlag == true) {
    delay(steptime); // run the motors for this time and then kill them
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

  }
}
