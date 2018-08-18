

int buf0Length;
int buf1Length;
int buf2Length;
void loop() {

  GCodeControl();
  if (ResetBuffer[0]) {
    buf0Length = 0;
    ResetBuffer[0] = 0;
  }
  if (ResetBuffer[1]) {
    buf1Length = 0;
    ResetBuffer[1] = 0;
  }

  if (RotationInProgress) {
    TimeAndExecuteRotation();

  } else {
    RotateCmdStep = 0;
    //OldRotateCmd = RotateCmd;
    RotateCmd = 0;
  }
  //delay(1000);
  if (playbackFromSD && (RotationInProgress == 0)) { // if no command in the cue and set to read from SD card, grab the next command from the SD
    //delay(250);
    SDReadGcodeLine(); // read the next line of G code from the SD Card and place the step commands into the que.
  }
  //Serial.println("Scan");
  //delay(0);

  for (int Joint = 0; Joint < NumJoints; Joint++) {


    if (J[Joint].NC == 1) {
      //Serial.print(" JNC:");
      //Serial.println(Joint);

      CommandAndCorrectJoint(Joint);

      J[Joint].NC = 0;
    }
  }


}


void CommandAndCorrectJoint(int Joint) {

  //Serial.print(" X:");
  //Serial.print(J[Joint].X);
  //Serial.print(" Y :");
  //Serial.println(J[Joint].Y);

  Rotate(J[Joint].X, J[Joint].Y, J[Joint].RotC + J[Joint].Rot);


  int CalcCh1;
  if (J[Joint].servo[0].Invert) {
    CalcCh1 = map(ChannelsOut.Ch1, ServoMinEng, ServoMaxEng, MaxPulseLength, MinPulseLength);
  } else {
    CalcCh1 = map(ChannelsOut.Ch1, ServoMinEng, ServoMaxEng, MinPulseLength, MaxPulseLength);
  }
  int pulselenCh1 = constrain(CalcCh1, MinPulseLength, MaxPulseLength);
  pwm.setPWM(J[Joint].servo[0].address, 0, pulselenCh1);

  int CalcCh2;
  if (J[Joint].servo[1].Invert) {
    CalcCh2 = map(ChannelsOut.Ch2, ServoMinEng, ServoMaxEng, MaxPulseLength, MinPulseLength);
  } else {
    CalcCh2 = map(ChannelsOut.Ch2, ServoMinEng, ServoMaxEng, MinPulseLength, MaxPulseLength);
  }
  int pulselenCh2 = constrain(CalcCh2, MinPulseLength, MaxPulseLength);
  pwm.setPWM(J[Joint].servo[1].address, 0, pulselenCh2);

  //Serial.print("Pulselength:");
  //Serial.print(pulselen2);
  //Serial.print(" . ServoAddress:");
  //Serial.println(J[JointNum].servo[ServoNum].address);

  //Serial.print(" Xout:");
  //Serial.print(J[Joint].Ch_OutB[0]);
  //Serial.print(" Yout:");
  //Serial.println(J[Joint].Ch_OutB[1]);
  //WritePosToServo2(Joint, 0);
  //WritePosToServo2(Joint, 1);



}
void WritePosToServo2(int Joint, int ServoNum) {


  int pulselen = map(J[Joint].Ch_Out[ServoNum], ServoMinEng, ServoMaxEng, MinPulseLength, MaxPulseLength);
  int pulselen2 = constrain(pulselen, MinPulseLength, MaxPulseLength);
  //Serial.print("Pulselength:");
  //Serial.print(pulselen2);
  //Serial.print(" . ServoAddress:");
  //Serial.println(J[JointNum].servo[ServoNum].address);
  pwm.setPWM(J[Joint].servo[ServoNum].address, 0, pulselen2);

  //delay(100);

}

void WritePosToServo(int JointNum, int ServoAddress, int ServoPosition) {

  int pulselen = map(ServoPosition, -500, 500, MinPulseLength, MaxPulseLength);
  //Serial.print("Pulselength:");
  //Serial.print(pulselen);
  //Serial.print(" . ServoAddress:");
  //Serial.println(ServoAddress);
  pwm.setPWM(ServoAddress, 0, pulselen);
  //delay(100);

}


void DriveAllTo(int ServoPosition) {
  Serial.print("DRTZ");
  for (int JointNum  = 0; JointNum < (NumJoints); JointNum++) {
    J[JointNum].Rot = 0;

    WritePosToServo(JointNum, J[JointNum].servo[PitchAxis].address , ServoPosition);
    WritePosToServo(JointNum, J[JointNum].servo[RollAxis].address , ServoPosition);
    delay(100);
  }
}


/*
  Serial.println(servonum);


  for (uint16_t pulselen = MinPulseLength; pulselen < MaxPulseLength; pulselen++) {


    //pulselen = (MaxPulseLength - MinPulseLength)/2;
     pwm.setPWM(servonum, 0, pulselen);
     pwm.setPWM(servonum+1, 0, pulselen);
     pwm.setPWM(servonum+2, 0, pulselen);
     pwm.setPWM(servonum+3, 0, pulselen);
  }

  //delay(10);
  for (uint16_t pulselen = MaxPulseLength; pulselen > MinPulseLength; pulselen--) {
    //pulselen = (MaxPulseLength - MinPulseLength)/2;
    pwm.setPWM(servonum, 0, pulselen);
    pwm.setPWM(servonum+1, 0, pulselen);
    pwm.setPWM(servonum+2, 0, pulselen);
     pwm.setPWM(servonum+3, 0, pulselen);
  }

  //delay(10);

  servonum ++;
  if (servonum > 4) servonum = 0;
*/
/*
  // Drive each servo one at a time
  Serial.println(servonum);
  for (uint16_t pulselen = MinPulseLength; pulselen < MaxPulseLength; pulselen++) {

    pwm.setPWM(servonum, 0, pulselen);
  }

  delay(500);
  for (uint16_t pulselen = MaxPulseLength; pulselen > MinPulseLength; pulselen--) {
    pwm.setPWM(servonum, 0, pulselen);
  }

  delay(500);

  servonum ++;
  if (servonum > 7) servonum = 0;
*/
