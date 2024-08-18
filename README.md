# ESP32 Children's Remote-Controlled Car with PS3 Controller

This project utilizes an ESP32 microcontroller to control a children's car and support prioritised remote-controller using a PS3 controller over Bluetooth. The car's motor speed is managed by an Electronic Speed Controller (ESC), and a high-torque servo is used for steering. Additionally, a local throttle control via a potentiometer is integrated, with the PS3 controller having priority control. A "total stop" feature is also implemented using the PS3 controller's "X" button and release pushing "Circle" button.

## Features

- **PS3 Controller Support:** Full control over forward/reverse motion and steering.
- **ESC Control:** Motor speed controlled using a model ESC via standard PWM signals.
- **Steering Servo Control:** High-torque servo for responsive steering.
- **Local Throttle Control:** Manual speed control using a potentiometer, with PS3 controller taking priority.
- **Total Stop Functionality:** Press the "X" button on the PS3 controller to immediately stop the vehicle and "Circle" button to release.

## Recommended Hardware

- **Microcontroller:** [ESP32 DevKit v1](https://www.amazon.com/HiLetgo-ESP-WROOM-32-Development-Microcontroller-Integrated/dp/B07Q576VWZ)
- **Electronic Speed Controller (ESC):** [30A Brushed DC Motor ESC](https://www.amazon.com/30A-Brushed-Electronic-Speed-Controller/dp/B00JBBEX9Q)
- **High-Torque Servo:** [Savox SB-2290SG Monster Torque Servo](https://www.savoxusa.com/products/sb-2290sg) or equivalent (70 kg/cm at 7.4V)
- **DC Motor:** [775 DC Motor](https://www.pololu.com/product/1117) (12V, capable of 20-30A current draw)
- **Battery:** [LiPo 3S or 4S Battery](https://www.hobbyking.com/hobbyking/store/__9179__Turnigy_5000mAh_3S_20C_Lipo_Pack.html) (11.1V or 14.8V, 5000mAh or higher)
- **Potentiometer:** [10kΩ Linear Potentiometer](https://www.amazon.com/BOJACK-Potentiometer-Variable-Resistors-Switch/dp/B07V4F1PZL)
- **Cooling:** Passive heatsinks and active cooling (e.g., 30mm fans) for ESC and other components.
- **Safety Switch:** [60A Circuit Breaker](https://www.amazon.com/ANJOSHI-Voltage-Circuit-Breaker-Reset/dp/B07JMPQ13G) for overcurrent protection.
- **Wiring:** 10 AWG wiring for motor and ESC connections, XT60 or XT90 connectors.

## Software Requirements

This project requires the following libraries:

- **PS3Controller Library:** Handles Bluetooth communication with the PS3 controller. Install via the Arduino Library Manager or [GitHub](https://github.com/jvpernis/esp32-ps3).
- **ESP32Servo Library:** Provides PWM control compatible with model ESCs and servos. Install via the Arduino Library Manager.

## Setup Instructions

### 1. Install Arduino IDE and ESP32 Board
- Download and install the latest version of the Arduino IDE.
- Follow the [ESP32 setup guide](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/) to add ESP32 support to the Arduino IDE.

### 2. Install Required Libraries
- Use the Arduino Library Manager to install the `PS3Controller` and `ESP32Servo` libraries.

### 3. Clone the Repository
```bash
git clone https://github.com/kappi/esp32_kids_car_controller.git
cd esp32_kids_car_controller
```

### 4. Wiring
- **ESC Pin:** Connect to GPIO 25 on the ESP32.
- **Steering Servo Pin:** Connect to GPIO 27 on the ESP32.
- **Potentiometer Pin:** Connect the wiper (middle pin) to GPIO 34 (analog input).
- **Total Stop Indicator (Optional):** Connect an LED with a suitable resistor to GPIO 2 to indicate when the car is in total stop mode.

### 5. Upload the Code
1. Open the `esp32_kids_car_controller.ino` file in the Arduino IDE.
2. Select your ESP32 board and the correct COM port.
3. Upload the code to your ESP32.

### Usage

#### Power On:
- Ensure the ESP32 and ESC are properly connected to the motor and battery. Power on the system.

#### Pairing the PS3 Controller:
- The ESP32 will automatically attempt to pair with a PS3 controller when turned on. Ensure the controller is in pairing mode.

#### Control the Car:
- Use the left joystick on the PS3 controller to control the speed and direction of the car.
- The right joystick controls the steering.
- The "X" button on the PS3 controller engages the total stop feature, which immediately halts the car.

#### Local Throttle Control:
- Adjust the potentiometer to manually control the speed if no significant input is received from the PS3 controller.

### Troubleshooting

#### PS3 Controller Not Connecting:
- Ensure the MAC address of your ESP32 is correctly set in the code. You may need to pair the controller using a USB cable and `SixaxisPairTool`.

#### Motor Not Responding:
- Check all wiring connections and ensure the ESC is properly configured. Verify the potentiometer's operation by monitoring the `localThrottle` variable in the serial output.

### License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

### Acknowledgments
- [Savox Servos](https://www.savoxusa.com/) for high-torque servo motors.
- [PS3Controller Library](https://github.com/jvpernis/esp32-ps3) for Bluetooth controller support.
