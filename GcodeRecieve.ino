
#define BUF_SIZE (32)
char buff0[BUF_SIZE];
char buff1[BUF_SIZE];
//char buff2[BUF_SIZE];

bool absoluteMode = 1;

float GetVal(int BN, char letter, float NA_val) {
  char *bufPtr0 = buff0;
  char *bufPtr1 = buff1;
  // char *bufPtr2 = buff2;

  if (BN == 0) {
    while (bufPtr0  > (char*) 1 && *bufPtr0 && bufPtr0 < buff0 + buf0Length) {
      if (*bufPtr0 == letter) {
        return atof(bufPtr0 + 1 );
      }
      bufPtr0 = strchr(bufPtr0, ' ') + 1;
    }
  } else if (BN == 1) {
    while (bufPtr1  > (char*) 1 && *bufPtr1 && bufPtr1 < buff1 + buf1Length) {
      if (*bufPtr1 == letter) {
        return atof(bufPtr1 + 1 );
      }
      bufPtr1 = strchr(bufPtr1, ' ') + 1;
    }
  }
  return NA_val;
}

void ParseGCode(int BN) {

  ResetBuffer[BN] = 1;

  double NewX, NewY, NewR;
  int command = GetVal(BN, 'G', -1);
  switch (command) {
    case  0: {

        int Pause = GetVal(BN, 'P', 0);
        delay(Pause);
        command = GetVal(BN, 'J', -1);
        switch (command) {
          case -1: { // All Joints
              NewX = GetVal(BN, 'X', 0);
              NewY = GetVal(BN, 'Y', 0);
              NewR = GetVal(BN, 'R', 0);
              if (NewR != 0 ) {
                RotateCmd = NewR;
                RotationInProgress = 1;
              }
              for (int Joint = 0; Joint < NumJoints; Joint++) {
                J[Joint].NC = 1;
                if (NewX != 0 ) {
                  J[Joint].X = NewX;
                }
                if (NewY != 0 ) {
                  J[Joint].Y = NewY;
                }
              }
              //for (int Joint; Joint < NumJoints; Joint++) {
              // Serial.print(" Jnum: ");
              // Serial.println(Joint);
              /// CommandAndCorrectJoint(Joint);
              //}
              break;
            }

          case 0 ... NumJoints : {
              J[command].NC = 1;
              J[command].X = GetVal(BN, 'X', J[command].X);
              J[command].Y = GetVal(BN, 'Y', J[command].Y);
              NewR = GetVal(BN, 'R', 0);
              if (NewR != 0 ) {
                RotateCmd = NewR;
                RotationInProgress = 1;
              }
              break;
            }

          default:  break;
        }
        break;
      }
    case 90:  absoluteMode = 1;  Serial.println(F("ABSMODE")); break;
    case 91:  absoluteMode = 0; Serial.println(F("RELMODE")); break;
    default:  break;
  }
  command = GetVal(BN, 'M', -1);
  switch (command) {
    case 10: { // this is a Rotate All Command

        Serial.println(F("RAC"));
        RotationInProgress = 1;
        RotateCmd = GetVal(BN, 'R', 0);

        break;
      }

    case 200: {

        break;
      }
    case 201: {

        break;
      }
    case 300: {
        Serial.println(F("PlayFromSD"));
        playbackFromSD = 1;

        break;
      }
    case 301: {
        Serial.println(F("SD File Complete"));
        playbackFromSD = 0;
        break;
      }

    default:  break;
  }
}

void ready() {
  //lastPos = wipPos;
  buf0Length = 0; // clear input buffer
  Serial.print(F("ok "));  // signal ready to receive input
  Serial.println(F(">"));  // signal readfy to receive input
}
void GCodeControl() {
  // listen for serial commands
  while (Serial.available() > 0) { // if something is available
    char c = Serial.read(); // get it
    //Serial.print(c);  // repeat it back so I know you got the message
    if (buf0Length < BUF_SIZE - 1) buff0[buf0Length++] = c; // store it
    if (c == '\n') {
      buff0[buf0Length] = 0; // end the buffer so string functions work right
      ParseGCode(0);  // do something with the command
    }
  }

}
void Print(char *code, float val) {
  Serial.print(code);
  Serial.print(val);
  Serial.print(" ");
}


