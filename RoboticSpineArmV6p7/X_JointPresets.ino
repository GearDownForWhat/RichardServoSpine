void SetJointPresets() {


  J[0].servo[RollAxis].address = 1;
  J[0].servo[PitchAxis].address = 0;
  J[0].servo[PitchAxis].Invert = 1;

  J[1].servo[RollAxis].address = 2;
  J[1].servo[PitchAxis].address = 3;
  J[1].servo[PitchAxis].Invert = 1;

  J[2].servo[RollAxis].address = 4;
  J[2].servo[PitchAxis].address = 5;
  J[2].servo[RollAxis].Invert = 1;

  J[3].servo[RollAxis].address = 6;
  J[3].servo[PitchAxis].address = 7;
  J[3].servo[PitchAxis].Invert = 1;

  J[4].servo[RollAxis].address = 8;
  J[4].servo[PitchAxis].address = 9;

  J[5].servo[RollAxis].address = 10;
  J[5].servo[PitchAxis].address = 11;

  J[6].servo[RollAxis].address = 13;
  J[6].servo[PitchAxis].address = 12;
  J[6].servo[PitchAxis].Invert = 1;
  J[6].servo[RollAxis].Invert = 1;

  J[7].servo[RollAxis].address = 14;
  J[7].servo[PitchAxis].address = 15;


  J[1].RotC = -45;
  J[3].RotC = -45;
  J[4].RotC = 70; // positive numbers correct in the clockwise direction, negative numbers correct CCW
  J[5].RotC = 110; // this applies a rotational correction factor
  J[6].RotC = -10;
  J[7].RotC = 110;



}

