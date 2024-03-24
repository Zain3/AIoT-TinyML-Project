# AIoT-TinyML-Project
Interfacing a remote camera feed for AI/AIot-based image processing using an RTOS.

You need the BeagleBone Black board, which is specialized in on-device AI/AIot tasks.

Steps to run the project:

1. Setup the BeagleBone
* Power it on with the cable that comes with it. After a couple of minutes, you should be able to SSH into it.
* The remote address is "debian@192.168.7.2", and the password is "temppwd"
* Connect the BeagleBone to an Ethernet wire to establish Internet connection. Do "ping 8.8.8.8" and see if that works to confirm.
* So "sudo apt-get update" and "sudo apt-get upgrade"
* Use Pip3 to install the following commands:
* * "pip3 install -upgrade pip", "pip3 install PySerial", and "sudo apt install python3-opencv"
  * In the SSH terminal, run: python3, import cv2, import serial (on new lines) to see if install properly

2. SSH into the BeagleBone, and transfer the Client.py file into it.
3. Run the Server.py on your server, then run Client.py on the BeagleBone.
