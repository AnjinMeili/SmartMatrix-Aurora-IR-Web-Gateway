# SmartMatrix-Aurora-IR-Web-Gateway
IR remote control of Aurora running on a SmartMatrix display using a web proxy on an ESP8266.

I lost the remote for my SmartMatrix display. I set about hunting for a new one without much success.  I ordered a new one from Adafruit, and of course, misplaced that one as well.  I pondered recompiling the firmware to use any random remote I had laying about.  But... Found it near impossible to compile up clean from my MBP with Catalina.

What is a poor geek todo!  I dug about in a drawer and found some bits, and slapped together an IR sender. 

## Parts
1. esp8266, I used an esp-01s module.
2. 2N3904 NPN Transistor, 2N2222 would work fine as well.
3. 940nm IR LED.
4. 100 ohm resistor.
5. 3.3k ohm resistor.

## IR Codes
All the required IR codes is in the Aurora source. I wrote a bit of gawk to read the header and spit out something I could test with.

[Aurora ircodes.h](https://github.com/pixelmatix/aurora/blob/master/IrCodes.h)

In the end, I settled on just using the original SmartMatrix remote code set.

## Build
Fairly simple. I use GPIO3 to drive the LED so we dont have to deal with the quirks of GPIO2 on an esp-01s. Esp8266 does not have a lot of current on any pin, so you can drive the transistor directly.  Small current limit resistor on the IR LED just for safety, adjust as required for the LED you are using.
![Schematic](https://github.com/AnjinMeili/SmartMatrix-Aurora-IR-Web-Gateway/blob/master/esp-01s_IR-sender.png?raw=true)

## Use
When running, the esp8266 creates a web server on port 80 that shows a picture of the SmartMatrix remote control.  The image has been mapped to allow clicking on the buttons to send the IR codes.  Click on the image just like it is the original remote.  Make sure the finished device is pointing mostly sorta kinda at the SmartMatrix panel :)

![SmartMatrix Remote](https://github.com/AnjinMeili/SmartMatrix-Aurora-IR-Web-Gateway/blob/master/SmartMatrixRemote.png?raw=true)
