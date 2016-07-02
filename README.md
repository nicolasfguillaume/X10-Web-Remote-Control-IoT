# X10 Web Remote Control with NodeMCU

Required material:
- NodeMCU ESP-12E
- FS1000A 433MHz RF transmitter (X10 compatible)
- X10RF library (by [domocreation](http://www.domocreation.fr/projets/librairies/x10-rf-arduino.html))

## Putting together the NodeMCU and the X10 transmitter (433 MHz)

![Pic 1](https://github.com/nicolasfguillaume/X10-Web-Remote-Control-IoT/blob/master/X10-3.jpg)

Connect the 'ATAD' pin of the FS1000A to the 'D1' pin of the NodeMCU.

![Pic 2](https://github.com/nicolasfguillaume/X10-Web-Remote-Control-IoT/blob/master/X10-22.jpg)

## Accessing the web server (living on the NodeMCU)

Simply type the NodeMCU local ip address in your web browser. 

![Pic 3](https://github.com/nicolasfguillaume/X10-Web-Remote-Control-IoT/blob/master/screenshot-android.jpg)

Note: If you want to access your web server from anywhere, you will have to modify the port forwarding on your router.

