// Motor pin definitions
int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 4;
int motor2pin2 = 5;

// Ultrasonic sensor pin definitions
const int trigPin = 11;
const int echoPin = 12;

// Motor speed control pins
const int ENA = 9;
const int ENB = 10;

void setup() {
  // Motor pins setup
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  // Motor speed control pins setup
  pinMode(ENA, OUTPUT); 
  pinMode(ENB, OUTPUT);

  // Ultrasonic sensor pins setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Start the Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Ultrasonic sensor distance measurement
  long duration;
  int distance;
  
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the sensor by setting the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH, 30000); // Timeout after 30ms

  // Check if a valid echo was received
  if (duration == 0) {
    Serial.println("No echo received");
    distance = -1; // Invalid distance
  } else {
    // Calculate the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (round trip)
  }

  // Print the distance on the Serial Monitor
  Serial.print("Distance: ");
  if (distance == -1) {
    Serial.println("Out of range");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }

  // Control motor speed and direction based on distance
  if (distance < 20 && distance != -1) { // If an obstacle is detected within 20 cm and distance is valid
    // Rush towards the enemy
    analogWrite(ENA, 255); // Max speed for motor1
    analogWrite(ENB, 255); // Max speed for motor2

    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
  } else {
    // Keep turning around to search for enemies
    analogWrite(ENA, 100); // Speed for motor1
    analogWrite(ENB, 100); // Speed for motor2

    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
  }

  delay(100); // Small delay to avoid flooding the Serial Monitor
}