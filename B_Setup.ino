

void setup() {
  Serial.begin(115200);
  Serial.println(F("READY!"));
  pwm.begin();

  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
  SetJointPresets();

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Wire.setClock(1200000);
  //myFile = SD.open("P3.txt"); dancing
  myFile = SD.open("P4.txt"); // waving hand.
  // Serial1.begin(115200);
  // void GCodeControl ();
  // void Gcodeinit ();

  DriveAllTo(0);

  delay(500);

}
