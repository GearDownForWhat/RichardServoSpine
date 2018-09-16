

void setup() {
  Serial.begin(115200);
  Serial.println(F("Gear Down For What Servo Spine Robot!"));
  Serial.println(F("How To Use:"));
  Serial.println(F("Set Serial Monitor to Newline or Both NR and CR"));
  Serial.println(F("and type an example command like this:"));
  Serial.println(F("G0 J1 X100 Y0"));
  Serial.println(F("Other Commands exist such as "));
  Serial.println(F("G0 J1 R360"));
  Serial.println(F("G0 J0 R360 N1 - N1 means read next line of code before executing"));
  Serial.println(F("G0 J-1 R360 -  J-1 means drive all joints"));
  Serial.println(F("M300 - means read code from SD card"));
  Serial.println(F("M301 - means stop reading file from SD Card"));
   
  pinMode(8,INPUT);



  Serial.println(F("READY!"));
  Serial.println(F("READY!"));
  pwm.begin();

  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
  SetJointPresets();
 if (playbackFromSD == 1){
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
 }
  Wire.setClock(1200000);
  //myFile = SD.open("P3.txt"); //dancing Interferance moves exist
  //myFile = SD.open("Breakf.txt"); //Breakfest helper robot
  //myFile = SD.open("Spoon.txt"); // Spoon shoveling
  //myFile = SD.open("LawnM.txt"); // Spoon shoveling
  //myFile = SD.open("Fight.txt"); // Looks Like cracking joints
  //myFile = SD.open("Sonic.txt"); // Swirls tail around like sonics sidekick
  //myFile = SD.open("Guitar2.txt"); // strumming guitar
  //myFile = SD.open("TestAll.txt"); // Drive Each Section
  myFile = SD.open(CurFile); // Viewer Program
  // Serial1.begin(115200);
  // void GCodeControl ();
  // void Gcodeinit ();

  DriveAllTo(0);

  delay(500);

}
