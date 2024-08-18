#include <Ps3Controller.h>
#include <ESP32Servo.h>

// Pin definitions
const int escPin = 25; // Pin for PWM signal to ESC (motor control output)
const int steeringServoPin = 27; // Pin for PWM signal to steering servo
const int potPin = 34; // Pin for the potentiometer (analog input)
const int stopLedPin = 2; // Optional: LED to indicate total stop status

// Variables
Servo esc;
Servo steeringServo;
int motorSpeed = 1500; // Middle value for ESC stop (1.5 ms)
int direction = 1; // 1 = forward, -1 = backward
int localThrottle = 0; // Value from the potentiometer for local throttle control
bool totalStop = false; // Variable to handle total stop status
unsigned long previousMillis = 0; // Will store the last time the loop was updated
const long interval = 10; // Interval for loop update in milliseconds

void setup() {
  // Initialize servos for ESC and steering
  esc.attach(escPin, 1000, 2000); // ESC expects PWM signal in the range of 1-2 ms
  steeringServo.attach(steeringServoPin);

  // Initialize serial for debugging
  Serial.begin(115200);

  // Attempt to connect to Ps3 controller
  if (!Ps3.begin("00:00:00:00:00:00")) { // Replace with the MAC address of your ESP32, or leave as "00:00:00:00:00:00" for pairing mode
    Serial.println("No controller paired, waiting for new pairing...");
    Ps3.begin(); // Enter pairing mode
  }

  Ps3.attach(onConnect);

  // Initialize potentiometer pin and stop LED
  pinMode(potPin, INPUT);
  pinMode(stopLedPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Read value from potentiometer (local throttle)
    localThrottle = analogRead(potPin);
    localThrottle = map(localThrottle, 0, 4095, 1000, 2000); // Map to range 1000-2000 µs (1-2 ms)

    // Check if the controller is connected and handle total stop
    if (Ps3.isConnected()) {
      if (Ps3.data.button.cross) {
        totalStop = true; // Engage total stop if the "X" button is pressed
      } else if (Ps3.data.button.circle) {
        totalStop = false; // Disengage total stop if the "Circle" button is pressed
      }

      if (totalStop) {
        motorSpeed = 1500; // Stop the motor
        digitalWrite(stopLedPin, HIGH); // Turn on LED to indicate total stop
      } else {
        digitalWrite(stopLedPin, LOW); // Turn off LED if not in total stop

        // Read from joystick for control
        int joystickY = Ps3.data.analog.stick.ly; // Forward/backward (left joystick Y)
        int joystickX = Ps3.data.analog.stick.rx; // Left/right (right joystick X)

        // Convert values for speed and direction
        motorSpeed = map(joystickY, 0, 255, 1000, 2000); // Map to PWM signal for ESC

        // Remote control has priority; use local throttle only if no input from remote
        if (joystickY < 128 - 10 || joystickY > 128 + 10) {
          // Use remote control if the joystick is outside the dead zone
          motorSpeed = map(joystickY, 0, 255, 1000, 2000);
        } else {
          motorSpeed = localThrottle; // Use local throttle if no significant remote input
        }

        int steeringValue = map(joystickX, 0, 255, 1000, 2000); // Map to PWM signal for steering

        // Set motor speed and steering direction
        esc.writeMicroseconds(motorSpeed); // Control ESC
        steeringServo.writeMicroseconds(steeringValue); // Control steering
      }
    } else {
      // If the controller is not connected, use local throttle only
      esc.writeMicroseconds(localThrottle); // Control ESC
    }
  }
}

void onConnect() {
  Serial.println("Ps3 Controller connected!");

  // Example: We can vibrate the controller to confirm connection
  Ps3.setRumble(100.0, 1000);  // Turn on vibration
  delay(500);
  Ps3.setRumble(0.0);  // Turn off vibration
}
