#define TRIG_PIN 9       // Ultrasonic TRIG
#define ECHO_PIN 10      // Ultrasonic ECHO
#define UPPER_SWITCH 6   // Upper float switch
#define LOWER_SWITCH 5   // Lower float switch
#define MOTOR_PIN 3      // Motor control pin (via transistor)

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(UPPER_SWITCH, INPUT_PULLUP);
  pinMode(LOWER_SWITCH, INPUT_PULLUP);
  pinMode(MOTOR_PIN, OUTPUT);

  digitalWrite(MOTOR_PIN, LOW); // Ensure motor is off initially
  Serial.begin(9600);          // Initialize Serial Monitor
}

void loop() {
  // Measure distance using ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration * 0.0343) / 2; // Distance in cm

  // Read float switch states
  bool upperSwitch = digitalRead(UPPER_SWITCH);
  bool lowerSwitch = digitalRead(LOWER_SWITCH);

  // Display sensor values in Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print("Upper Switch: ");
  Serial.println(upperSwitch == LOW ? "ON" : "OFF");
  Serial.print("Lower Switch: ");
  Serial.println(lowerSwitch == LOW ? "ON" : "OFF");

  // Motor Control Logic
  if (lowerSwitch == LOW) {
    // Turn OFF motor if water level is too low
    digitalWrite(MOTOR_PIN, LOW);
    Serial.println("Motor OFF (Low Level Trigger)");
  } else if (upperSwitch == LOW) {
    // Turn OFF motor when upper level is reached
    digitalWrite(MOTOR_PIN, LOW);
    Serial.println("Motor OFF (Upper Level Trigger)");
  } else if (distance > 15 && distance < 30) {
    // Turn ON motor when water level is between 15-30 cm
    digitalWrite(MOTOR_PIN, HIGH);
    Serial.println("Motor ON");
  } else {
    // Default state: Motor OFF
    digitalWrite(MOTOR_PIN, LOW);
  }

  delay(1000); // Delay for stability
}
