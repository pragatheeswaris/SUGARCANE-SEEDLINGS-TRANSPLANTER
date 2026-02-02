// === Motor X (horizontal) ===
#define DIR_X 2
#define PWM_X 3
#define BRK_X 4

// === Motor Y (vertical) ===
#define DIR_Y 5
#define PWM_Y 6
#define BRK_Y 7

// === Dropper ===
#define DROP_PIN 8

// === Settings ===
const int moveDelay = 5000;   // time to move one cell (tune this)
const int dropDelay = 1000;   // time to drop seedling
const int speedPWM = 500;     // motor speed (0–255)

void setup() {
  pinMode(DIR_X, OUTPUT);
  pinMode(PWM_X, OUTPUT);
  pinMode(BRK_X, OUTPUT);

  pinMode(DIR_Y, OUTPUT);
  pinMode(PWM_Y, OUTPUT);
  pinMode(BRK_Y, OUTPUT);

  pinMode(DROP_PIN, OUTPUT);

  stopMotors();
}

void loop() {
  for (int row = 0; row < 5; row++) {
    if (row % 2 == 0) {
      // Even row → move right
      for (int col = 0; col < 5; col++) {
        dropSeedling();
        if (col < 5) moveOneStepX(true); // move right
      }
    } else {
      // Odd row → move left
      for (int col = 0; col < 5; col++) {
        dropSeedling();
        if (col < 5) moveOneStepX(false); // move left
      }
    }

    // Move down to next row (except after last row)
    if (row < 5) moveOneStepY(true);
  }

  // Return to origin
  moveBackY(5);
  moveBackX(5);

  while (true); // stop after one cycle
}

// === Movement Functions ===
void moveOneStepX(bool forward) {
  digitalWrite(DIR_X, forward ? HIGH : LOW);
  digitalWrite(BRK_X, LOW);
  analogWrite(PWM_X, speedPWM);
  delay(moveDelay);
  stopMotors();
}

void moveOneStepY(bool forward) {
  digitalWrite(DIR_Y, forward ? HIGH : LOW);
  digitalWrite(BRK_Y, LOW);
  analogWrite(PWM_Y, speedPWM);
  delay(moveDelay);
  stopMotors();
}

void moveBackX(int steps) {
  digitalWrite(DIR_X, LOW);
  digitalWrite(BRK_X, LOW);
  analogWrite(PWM_X, speedPWM);
  delay(steps * moveDelay);
  stopMotors();
}

void moveBackY(int steps) {
  digitalWrite(DIR_Y, LOW);
  digitalWrite(BRK_Y, LOW);
  analogWrite(PWM_Y, speedPWM);
  delay(steps * moveDelay);
  stopMotors();
}

void dropSeedling() {
  digitalWrite(DROP_PIN, HIGH);
  delay(dropDelay);
  digitalWrite(DROP_PIN, LOW);
}

void stopMotors() {
  digitalWrite(BRK_X, HIGH);
  analogWrite(PWM_X, 0);

  digitalWrite(BRK_Y, HIGH);
  analogWrite(PWM_Y, 0);
}