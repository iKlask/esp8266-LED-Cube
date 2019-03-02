# esp8266-LED-Cube
This is a Blynk based Arduino LED Cube. The cube is a 3x3x3 matrix of LEDs which are controlled via the internet over the Blynk API with an app or with their RESTful api.

<p align="center">
 <img src="https://iklask.github.io/images/CUBE/loop.gif"/>
</p>

### Arduino Library Requirements:
* [Arduino IDE esp8266 Library](https://arduino-esp8266.readthedocs.io/en/latest/installing.html#boards-manager)
* [Blynk Library](https://www.blynk.cc/getting-started/)
* [WifiManager Library](https://github.com/tzapu/WiFiManager)
* [SimpleTimer Library](https://github.com/schinken/SimpleTimer)

Here is a bill of material with the part numbers I used:

* (x1) ESP-01 esp8266 module
   - Any generic ESP-01 should work
* (x2) 74hc595 Shift Register ICs
   - SN74hc595N
* (x27) 3mm LED (I used Red 1.85v LEDs)
   - WP710A10SRD/E
* (x3) 2n3904 NPN Transistors
   - 2N3904TA
* (x3) 1k Ohms Resistors
   - CF14JT1K00
* (x2) 330 Ohms Resistors
   - CF14JT330R
* (x3) 220 Ohms Resistors
   - CF14JT220R
* (x1) TO-220 3.3v Linear Voltage Regulator
   - LD1117V33C
* (x2) Radial 10uF 50VDC 2mm Electrolytic Capacitors
   - SKR100M1HD11M
* (x1) DC Barrel jack
   - PJ-102AH
* (x1) Barrel Jack Power supply (Must fit the LD1117v33C input requirements)
   - SunFounder DC 9V/650mA Power Supply Plug Adapter
* Break away headers
    - 2 pins for access to Rx/Tx
    - 3 pins + jumper for restarting in programming mode
        - Alternativley use a mini 3 pin single pole, double throw (SPDT) switch

You can copy my project by scanning this QR into the Blynk app. You'll need to supply your new Authtoken in the sketch's ```char auth[]``` field.
<p align="center">
 <img src="https://iklask.github.io/images/CUBE/blynk_project_QR.png"/>
</p>

The current sketch expects the following on a Blynk App:

* A Blynk Text LCD to display what the current animation is
   - Input: V2
* A Blynk Menu for Changing the animation of the cube.
   - Output: V0
   - Animations are set to the following indices
       1. Random
       2. Slither
       3. Center Spin
       4. Rain
       5. Flip
       6. Windmill
* A Blynk Slider to adjust the speed of the animations.
   - Output: V1
   - This number is applied as a delay between each "draw", so higher numbers mean slower animations
   - I have mine set to decimal values between 50-5000

A project post-mortem can be seen [here.](https://iklask.github.io/blog/wifi-enabled-3d-led-cube/)

Schematic of the PCB here:
<p align="center">
 <img src="https://iklask.github.io/images/CUBE/ESP_LED_CUBE_SCH.png"/>
</p>