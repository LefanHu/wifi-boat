# Wifi Controlled Boat (Completed-School-Project)
A project was assigned for TDJ3M-03 (Gr 11 Tech Design). The project outline can be found [here](https://github.com/LefanHu/wifi-boat/blob/main/1%20Designing%20a%20Boat%20Challenge%20Outline.pdf).

## What I've learned.
- As a complete beginner to circuits and electronics, I thought a servo driver should be able to control DC motors. However, they simply cannot. Hence, a regular motor driver was used in the end (like it should have been).
- Diodes allow current to pass in one direction and not the other direction. This function can be used to protect an arduino or a transistor from a negative spike of voltage from a motor when you turn it off.
- Avoid sharing power sources between motors and NODEMCU. When motors are in use, the voltage can drop below the acceptable threshold of the microcontroller, causing it to turn off.
- Some mosfets are designed to use a higher gate threshold than others, typically 3V or 5V for microcontrollers. The gpio pins on the NODEMCU outputs 3.3V max, which is too low for some mosfets.

Note to future self. Do not attempt to use servo drivers to control DC motors that only have 2 pins (V+ V-).

## Other notes
- The body of the "boat" is valid as holes and openings were cut into it, such a case was allowed by the teacher.
- Code was taken and modified from [here](https://www.hackster.io/alankrantas/simple-nodemcu-wifi-controlled-car-esp8266-c5491e)
- D1 (GPIO5) on NODEMCU was used as pwm signal pin

## Images
![boat image 1](https://github.com/LefanHu/wifi-boat/blob/main/boat1.jpg)
![boat image 2](https://github.com/LefanHu/wifi-boat/blob/main/boat2.jpg)

## Components used
- ~~PCA9685 16-channel 12-bit PWM driver~~
- ESP-8266 NODEMCU
- 2 DC Motors
- 9 volt battery
- ~~Resistor (specifications)~~
- ~~Diode (specifications)~~
- D-Sun step down voltage regulator
- 3D printed ship ~~body~~ parts
- N-MOS motor driver

## Useful Links
[Servo Driver Overview](https://learn.adafruit.com/16-channel-pwm-servo-driver?view=all)

[ESP8266 connections with driver](http://www.esp8266learning.com/pca9685-led-controller-and-esp8266-example.php)

[Usage of diodes & transistors](https://electronics.stackexchange.com/questions/95140/purpose-of-the-diode-and-capacitor-in-this-motor-circuit#:~:text=Without%20the%20diode%2C%20the%20voltage,probably%20require%20frying%20the%20transistor.&text=The%20resistor%20is%20to%20limit,the%20transistor%20base%20xiust%20handle.)

[arduino: run function when key is pressed](https://www.arduino.cc/en/Reference/KeyPressed)

[Nodemcu wifi controlled motors](https://www.hackster.io/alankrantas/simple-nodemcu-wifi-controlled-car-esp8266-c5491e)

[arduino setpwm() parameters](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/issues/26)