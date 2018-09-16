
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

  double NewX, NewY, NewR, NewS;
  int command = GetVal(BN, 'G', -1);
  switch (command) {
    case  0: {
        Pause(GetVal(BN, 'P', 0));
        command = GetVal(BN, 'J', -1);
        switch (command) {
          case -1: { // All Joints
              NewX = GetVal(BN, 'X', -.1);
              NewY = GetVal(BN, 'Y', -.1);
              NewR = GetVal(BN, 'R', -.1);
              NewS = GetVal(BN, 'S', -.1);
              for (int Joint = 0; Joint < NumJoints; Joint++) {
                J[Joint].NC = 1;
                if (NewX != -.1 ) {
                  J[Joint].X = NewX;
                }
                if (NewY != -.1 ) {
                  J[Joint].Y = NewY;
                }
                if (NewR != -.1 ) {
                  J[Joint].RotNew = NewR;
                  J[Joint].RotIP = 1;
                }
                if (NewS != -.1 ) {
                  J[Joint].RotSpd = NewS;
                }

              }
              //for (int Joint; Joint < NumJoints; Joint++) {
              // Serial.print(" Jnum: ");
              // Serial.println(Joint);
              /// CommandAndCorrectJoint(Joint);
              //}
              break;
            } // end of switch J-1 cmd

          case 0 ... NumJoints : {
              J[command].NC = 1;
              J[command].X = GetVal(BN, 'X', J[command].X);
              J[command].Y = GetVal(BN, 'Y', J[command].Y);
              NewR = GetVal(BN, 'R', 0);
              NewS = GetVal(BN, 'S', 0);
              if (NewR != 0 ) {
                J[command].RotNew = NewR;
                J[command].RotIP = 1;
              }
              if (NewS != 0 ) {
                J[command].RotSpd = NewS;
              }
              break;
            } // end of Case ... numjoints cmd

          default:  break;
        } // end of switch J Cmd

        command = GetVal(BN, 'N', -1);
        switch (command) {
          case 1 : {
              ReadNextCommand = 1;
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


    case 200: {
        break;
      }
    case 201: {

        break;
      }
    case 300: {
        GetFileName(BN);
        myFile.close(); // Viewer Program
        CurFile = NewFile;
        myFile = SD.open(CurFile); // Viewer Program

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



bool GetFileName(int BN) {
  int SaveVal = 0;
  bool RecievedName = 0;
  if (BN == 0) {

    for (int Inc = 0; Inc <= buf0Length; Inc++) {
      if (buff0[Inc] == 34) { // if you find a quote bracket
        if (SaveVal == 0) {
          NewFile = "";
          SaveVal = 1;
          RecievedName = 1;
        }
        else {
          SaveVal = 0;
        }

      }

      if (SaveVal == 1 && buff0[Inc] != 34) { // if you are between the quotes but not on the quotes
        NewFile += buff0[Inc];
      }
    }
    Serial.print("I Recieved : ");
    Serial.println(NewFile);
  }
  if (BN == 1) {

    for (int Inc = 0; Inc <= buf1Length; Inc++) {
      if (buff1[Inc] == 34) { // if you find a quote bracket
        if (SaveVal == 0) {
          NewFile = "";
          SaveVal = 1;
          RecievedName = 1;
        }
        else {
          SaveVal = 0;
        }

      }

      if (SaveVal == 1 && buff1[Inc] != 34) { // if you are between the quotes but not on the quotes
        NewFile += buff1[Inc];
      }
    }
    Serial.print("I Recieved : ");
    Serial.println(NewFile);

    
  }
  return RecievedName;
}
//string.charAt(n)
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
    Serial.print(c);  // repeat it back so I know you got the message
    if (buf0Length < BUF_SIZE - 1) {
      buff0[buf0Length++] = c; // store it
    }

    if (c == '\n') {
      buff0[buf0Length] = 0; // end the buffer so string functions work right
      ParseGCode(0);  // do something with the command
      //Serial.println("END");
      // use "both NL & CR" in serial monitor
    }
  }

}
void Print(char *code, float val) {
  Serial.print(code);
  Serial.print(val);
  Serial.print(" ");
}

void Pause( unsigned int PauseTime) {
  delay(PauseTime);
}

