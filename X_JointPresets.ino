void SetJointPresets() {

  //J[0].servo[PitchAxis].Min = -500;
  //J[0].servo[PitchAxis].Max = 500;
  //J[0].servo[PitchAxis].Center = 0;
  //J[0].servo[RollAxis].Min = -500;
  //J[0].servo[RollAxis].Max = 500;
  //J[0].servo[RollAxis].Center = 0;
  J[0].servo[RollAxis].address = 1;
  J[0].servo[PitchAxis].address = 0;
  J[0].servo[PitchAxis].Invert = 1;

  //J[1].servo[PitchAxis].Min = -500;
  //J[1].servo[PitchAxis].Max = 500;
  //J[1].servo[PitchAxis].Center = 0;
  //J[1].servo[RollAxis].Min = -500;
  //J[1].servo[RollAxis].Max = 500;
  //J[1].servo[RollAxis].Center = 0;
  J[1].servo[RollAxis].address = 2;
  J[1].servo[PitchAxis].address = 3;
  J[1].servo[PitchAxis].Invert = 1;


  //J[2].servo[PitchAxis].Min = -500;
  //J[2].servo[PitchAxis].Max = 500;
  //J[2].servo[PitchAxis].Center = 0;
  //J[2].servo[RollAxis].Min = -500;
  //J[2].servo[RollAxis].Max = 500;
  //J[2].servo[RollAxis].Center = 0;
  J[2].servo[RollAxis].address = 4;
  J[2].servo[PitchAxis].address = 5;
  J[2].servo[RollAxis].Invert = 1;

  //J[3].servo[PitchAxis].Min = -500;
  //J[3].servo[PitchAxis].Max = 500;
  //J[3].servo[PitchAxis].Center = 0;
  //J[3].servo[RollAxis].Min = -500;
  //J[3].servo[RollAxis].Max = 500;
  //J[3].servo[RollAxis].Center = 0;
  J[3].servo[RollAxis].address = 6;
  J[3].servo[PitchAxis].address = 7;
  J[3].servo[PitchAxis].Invert = 1;

  //J[4].servo[PitchAxis].Min = -500;
  //J[4].servo[PitchAxis].Max = 500;
  //J[4].servo[PitchAxis].Center = 0;
  //J[4].servo[RollAxis].Min = -500;
  ///J[4].servo[RollAxis].Max = 500;
  //J[4].servo[RollAxis].Center = 0;
  J[4].servo[RollAxis].address = 8;
  J[4].servo[PitchAxis].address = 9;

  //J[5].servo[PitchAxis].Min = -500;
  //J[5].servo[PitchAxis].Max = 500;
  //J[5].servo[PitchAxis].Center = 0;
  //J[5].servo[RollAxis].Min = -500;
  //J[5].servo[RollAxis].Max = 500;
  //J[5].servo[RollAxis].Center = 0;
  J[5].servo[RollAxis].address = 10;
  J[5].servo[PitchAxis].address = 11;

  //J[6].servo[PitchAxis].Min = -500;
  //J[6].servo[PitchAxis].Max = 500;
  //J[6].servo[PitchAxis].Center = 0;
  //J[6].servo[RollAxis].Min = -500;
  //J[6].servo[RollAxis].Max = 500;
  //J[6].servo[RollAxis].Center = 0;
  J[6].servo[RollAxis].address = 13;
  J[6].servo[PitchAxis].address = 12;
  J[6].servo[PitchAxis].Invert = 1;
  J[6].servo[RollAxis].Invert = 1;

  //J[7].servo[PitchAxis].Min = -500;
  //J[7].servo[PitchAxis].Max = 500;
  //J[7].servo[PitchAxis].Center = 0;
  //J[7].servo[RollAxis].Min = -500;
  //J[7].servo[RollAxis].Max = 500;
  //J[7].servo[RollAxis].Center = 0;
  J[7].servo[RollAxis].address = 14;
  J[7].servo[PitchAxis].address = 15;


  J[1].RotC = -45;
  J[3].RotC = -45;
  J[4].RotC = 90;
  J[5].RotC = 90;
  J[7].RotC = 45;



}

