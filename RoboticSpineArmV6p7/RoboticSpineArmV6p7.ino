
bool playbackFromSD = 1; // set this to 1 if you would like to start playing from SD on Bootup

String CurFile = "START.TXT";
String NewFile;

#include <SPI.h>
#include <SD.h>
#define chipSelect 10
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
File myFile;
#define ServoMinEng -100
#define ServoMaxEng 100

//150
//600
//#define MinPulseLength  240 // this is the 'minimum' pulse length count (out of 4096)// Normal config
//#define MaxPulseLength  510 // this is the 'maximum' pulse length count (out of 4096)// Normal config
//#define MinPulseLength  200 // this is the 'minimum' pulse length count (out of 4096) // 
//#define MaxPulseLength  540 // this is the 'maximum' pulse length count (out of 4096)
#define MinPulseLength  150 // this is the 'minimum' pulse length count (out of 4096) unconstrained
#define MaxPulseLength  600 // this is the 'maximum' pulse length count (out of 4096) unconstrained

#define PitchAxis 1
#define RollAxis 0
#define NumJoints 8
#define pi 3.1415926
bool ResetBuffer[2];
struct ServoUDT {
  byte address;
  bool Invert = 0;
};

struct Joint {
  ServoUDT servo[2];
  int X;
  int Y;
  int Ch_Out[2];
  int Rot;
  int RotOld;
  int RotNew;
  int RotC = 0;
  int RotCmdStep;
  int RotNumSteps;
  byte RotSpd = 200;
  bool RotIP = 0;
  bool NC = 0; // New Command
};

Joint J[NumJoints];
struct DualChannel {
  int Ch1;
  int Ch2;
};

DualChannel ChannelsOut;

//int RotateCmd = 0;
//int RotateCmdStep;

unsigned long TimerVal[5];
bool Pin8LastState = 0;
bool Restart = 0;




/***************************************************
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These drivers use I2C to communicate, 2 pins are required to
  interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/



// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
/*

  // our servo # counter
  uint8_t servonum = 0;



  // you can use this function if you'd like to set the pulse length in seconds
  // e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
  void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period");
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit");
  pulse *= 1000000;  // convert to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
  }
*/

