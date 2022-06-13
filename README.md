![https://platformio.org/](https://camo.githubusercontent.com/8fc14af039bcce01d826030e0c74cdc8a8f84cadca809a95be0b6973db5dbbfb/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6275696c74253230776974682d706c6174666f726d696f2d6f72616e6765 "platformio")

# Tha Grabber
A machine to show what we can do with our [Toolsquare](www.toolsquare.io) units. Here's the [project page](https://github.com/Toolsquare-io/Grabber/projects/1).

## Timeline
### Deadline
* [Laborama](https://expo.laborama.be/nl/) 19 & 20 mei
* [Nerdland](https://www.nerdlandfestival.be/) 3, 4 & 5 juni

### Build timeline
* CAD approval -> 8th of April

---

**Everything below is draft and could change, keep those affected in the loop!**

---

## Requirements
* Dimensions footprint: 60x60cm
* Should reflect a Toolsquare machine: locked, idle, running. 
* Gadget max dimension: 14x12cm, height 7cm
* Should be easy to install by one person
* Should be able to run without supervision (so not too easy to break in) 
* Lights!

## The game
1. Unlock the machine using a Toolsquare unit or something else (a coin, a simple nfc reader,..)
2. Use the joystick to positon X and Y
3. Press a button to auto **lower the grabber, raise and dump the gadget**
5. Once a timout is reached the crane goes back to home and needs to be unlocked again

## BOM
The full [BOM](https://docs.google.com/spreadsheets/d/1Js6a-A9pP3j60k_G_hthX2zwbCBgAsaMytp7D8mz5XA/edit?usp=sharing)
* [Bosch-Rexroth](https://benl.rs-online.com/web/c/engineering-materials-industrial-hardware/structural-systems/) and connections
* [Optional Neopixels](https://www.adafruit.com/product/1138?length=1)
* ESP32
* [Linear Bearings](https://benl.rs-online.com/web/p/products/2346942/)
* [Linear Guide](https://benl.rs-online.com/web/p/products/4485449/) and cariage (https://benl.rs-online.com/web/p/products/3752445/)
* [Motors](https://www.amazon.nl/gp/product/B06Y2BSCL7/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)

## CAD
[The Fusion model](https://a360.co/3vmHt5T)

## Inspirations
[CoreXY](http://corexy.com/theory.html)

![CoreXY Math](http://corexy.com/reference.png)

## Electronics

Pinouts
![CNCShield](https://blog.protoneer.co.nz/wp-content/uploads/2013/07/Arduino-CNC-Shield-Schematics.png "pinmapping")

|  Function | Pin Number   |  
|---|---|
|  Stepper X |   |  
|  Stepper Y |  |  
|  Stepper Z  |  |   
|  Interlock X |  |   
|  Interlock Y  |  |   
|  Interlock Z  |  |   
|  JoyStick X  |  |   
|  JoyStick Y  |  |  
|  Button 1  |  |   
|  Button 2  |  |   
|  Button 1 LED  |  |
|  Button 2 LED  |  |   
|  NeoPixel  |  |   
|  Running Out  |  | 
|  Machine Lock  |  |   
|  Magnet Relais  |  |   




