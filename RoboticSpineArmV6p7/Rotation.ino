
int RotationCommandInterval = 1;

#define MinRotateInterval 500
#define MaxRotateInterval 20

void TimeAndExecuteRotation(int Joint) {
  if (J[Joint].RotIP) {
   int Calc1 =  map(J[Joint].RotSpd, 0, 255, MaxRotateInterval, MinRotateInterval);
    float InverseSpeed =  ((float)Calc1 / 30);
     // Serial.print("InverseSpeed: ");
     // Serial.println(InverseSpeed);
    int NumSteps = round((abs(J[Joint].RotOld - J[Joint].RotNew) / InverseSpeed));
  ///  if (NumSteps <= 255) {
     J[Joint].RotNumSteps = NumSteps;
  //  }
  //  else {
  //    J[Joint].RotNumSteps = 255;
   // }



    if (J[Joint].RotCmdStep <= J[Joint].RotNumSteps) {

      J[Joint].Rot = map(J[Joint].RotCmdStep, 0, J[Joint].RotNumSteps, J[Joint].RotOld, J[Joint].RotNew);
      J[Joint].NC = 1;
      J[Joint].RotCmdStep++;
      //Serial.print("Joint: ");
      //Serial.println(Joint);
      //Serial.print("J[Joint].RotCmdStep: ");
      //Serial.println(J[Joint].RotCmdStep);
    }
    else {
      J[Joint].RotIP = 0;
      J[Joint].RotOld = J[Joint].Rot % 360;

    }

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
