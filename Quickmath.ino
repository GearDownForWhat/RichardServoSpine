double ConvertRtoD(double Rads) {

  double Degs =  Rads * 180.0 / pi;
  return Degs;
}
double ConvertDtoR(double Degs) {

  double Rads =  Degs / 180.0 * pi;
  return Rads;
}


bool TON(int TimerID, int PRE) {
  unsigned long CurTime = millis();
  if ((CurTime - TimerVal[TimerID]) >= PRE ) {
    TimerVal[TimerID] = CurTime;
    return 1;
  }
  else {
    return 0;
  }


}
