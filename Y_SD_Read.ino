
void SDReadGcodeLine() {
  //Serial.println("Read GC SD");
  buf1Length = 0;
  bool Null = 0;
  while (buf1Length < 32 && Null == 0 ) {
    //Read++;

    char c = myFile.read();
    Serial.print(c);
    if (buf1Length < 32 - 1) {
      buff1[buf1Length] = c; // store it
      buf1Length++;
    }
    if (c == '\n') {
      //Serial.println("Null");
      Null = 1;
      buff1[buf1Length] = 0; // end the buffer so string functions work right
      //Serial.println("Process From Buffer #1");
      ParseGCode(1);  // do something with the command
    }

    //char c = myFile.read();
    //if (c == '\n') { Null = 1;}
    //Serial.print(c);
    //strcat(line, c);
    //Serial.print(line);

  }
  //Serial.print(buf2Length);
  // for (int Junk = 0; Junk < buf2Length; Junk ++) {
  //   Serial.print(buff2[Junk]);
  // }


}
/*
  void SDRead() {
  myFile = SD.open("test.txt", FILE_WRITE);

  if (myFile) {
    //Serial.print("Writing to test.txt...");
    //myFile.println("testing 1, 2, 3.");
    // close the file:
    //myFile.close();
    //Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    //while (myFile.available()) {
    Serial.write(myFile.read());
    //}
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  }*/
