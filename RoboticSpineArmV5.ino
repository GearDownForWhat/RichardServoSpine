
#include <SPI.h>
#include <SD.h>


#define chipSelect 10
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
File myFile;
#define ServoMinEng -100
#define ServoMaxEng 100
#define MinPulseLength  250 // this is the 'minimum' pulse length count (out of 4096)
#define MaxPulseLength  500 // this is the 'maximum' pulse length count (out of 4096)

#define PitchAxis 1
#define RollAxis 0
#define NumJoints 7
#define pi 3.1415926
bool ResetBuffer[2];
bool ReadFromSD;
struct ServoUDT {
  byte address;
  //int CurPos;
  //byte Center = 0;
  //byte Min = -500;
  //byte Max = 500;
  bool Invert = 0;
};

struct Joint {
  bool NC = 0; // New Command
  ServoUDT servo[2];
  int Rot;
  int RotC = 0;
  int X;
  int Y;
  int Ch_Out[2];
};
Joint J[NumJoints];
//Joint XJ[NumJoints];

struct DualChannel {
  int Ch1;
  int Ch2;
};

DualChannel ChannelsOut;

bool RotationInProgress = 0;

int RotateCmd = 0;
//int OldRotateCmd = 0;

int RotateCmdStep;

unsigned long TimerVal[5];

bool playbackFromSD = 1;



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

