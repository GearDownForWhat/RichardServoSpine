# RichardServoSpine
Richard 9000 the Servo Spine Robot Controls many servos with G Code
Richard uses an Arduino UNO with an external SD card reader and a "Adafruit 16-Channel 12-bit PWM/Servo Shield - I2C interface" shield to control the servos 

How to enter G-Code with Serial Prompt - 
Make sure you have Arduino serial prompt set to New Line
 - Every command needs to end with a new line
 - Every movement command starts with G0
 - Joints Commands are limited to +/- 100
 - Direct movement commands for only one joint look like this        						G0 J0 X50 Y0
 - Commands that apply to all joints, you just exclude the “J”          						G0 X50 Y50
- Rotate commands, or, cascade commands can be written for all joints, like this 		        G0 R1080
- or else they can specify just one single joint like this                           						G0 J1 R1080
- You can request that it reads the next line of commands before executing the current line (only with SD)  G0 R360 N1
 - Using the N1 Command is fun when running rotate commands, for example, you can command the bottom joint and the top joint to cascade in opposite directions simultaneously with this section of code
 
G0 J0 X50 N1

G0 R1080 N1

G0 J7 X-50 N1

G0 R-1080

 - Rotate (cascade) commands default to a speed of 200 if you dont specify a speed (0-255) To specify, use  G0 R360 S255
 - You can specify diffrent speeds and rotate commands for diffrent joints such as,
 G0 J0 R360 S100 N1 // means cascade joint0 360 degrees at a speed of 100 but read the next line of code first and do both
 G0 J1 R1080 S255


Things that apply to reading from the SD card only:
 - The last line needs to be M301 and needs to have a new line after it, else it goes mad
 - The first file it will open is coded in the program, from there you can use M300 to tell it to open a different file, like this 
M300 “MyFile.txt”
will tell it to close the master file and open MyFile.txt, it will NOT return to the master file when done. 
 - Direct movement commands (G0 X50 Y50) are assumed to be done instantly,
so you need to program pauses into the G-Code, like this: 
G0 P100  //means pause 100 ms
 
 
 
