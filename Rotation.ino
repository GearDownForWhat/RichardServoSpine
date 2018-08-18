
int RotationCommandInterval = 1;



void TimeAndExecuteRotation() {
  int NumSteps = (abs(RotateCmd)/2);
  if (RotateCmdStep <= NumSteps) {

  //if (TON(0, RotationCommandInterval) && (RotateCmdStep <= NumSteps)) {

    //int NumSteps = ((RotateCmd - OldRotateCmd)/10);

    int CurAngle = map(RotateCmdStep, 0, NumSteps, 0, RotateCmd);


    //Serial.print("Curangle : ");

    //Serial.println(CurAngle);
    //Serial.println();
    for (int Joint = 0; Joint < NumJoints; Joint ++) {

      J[Joint].Rot = CurAngle;
      J[Joint].NC = 1;


      //Rotate(J[Joint].X,J[Joint].Y, CurAngle);
      //J[Joint].Ch_Out[0] = ChannelsOut.Ch1;
      //J[Joint].Ch_Out[1] = ChannelsOut.Ch2;
      //CommandAndCorrectJoint(Joint);
      RotateCmdStep++;


    }
  }
  else {
    RotationInProgress = 0;
  }
}


void Rotate(int Ch1, int Ch2, int Angle) { // this will mix the channels based upon an angle to allow the machine to "cascade" or appear spin in a circle
  Angle = (Angle * -1); // the angle was reversed compared to what i expected.
  //Serial.print("Ch1: ");
  //Serial.println(Ch1);
  //Serial.print("Ch2: ");
  //Serial.println(Ch2);
  float rotate = ConvertRtoD(atan2(Ch1 , Ch2)); //Find the absolute angle of rotation.
  //Serial.print("CurABSRotate: ");
  //Serial.println(rotate);
  //Serial.print("ButGoToHere: ");
  //Serial.println(Angle);
  float Test1 = (Ch1 * Ch1 + Ch2 * Ch2);
  float Hypotenuse = sqrt(abs(Test1));
  //Serial.print("Test1: ");
  //Serial.println(Test1);
  // Serial.print("Hypt: ");
  // Serial.println(Hypotenuse);

  float Test2 = sin(ConvertDtoR(Angle + rotate)) * Hypotenuse;
  //Serial.print("Test2: ");
  //Serial.println(Test2);
  ChannelsOut.Ch1 = sin(ConvertDtoR(Angle + rotate)) * Hypotenuse; //this calculates the output for Ch1
  ChannelsOut.Ch2 = cos(ConvertDtoR(Angle + rotate)) * Hypotenuse; //this calculates the output for Ch2
  //Serial.print("Ch1 New: ");
  //Serial.println(ChannelsOut.Ch1);
  //Serial.print("Ch2 New: ");
  //Serial.println(ChannelsOut.Ch2);

  //Serial.println();

}
