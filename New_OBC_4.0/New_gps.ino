// defines smart delay
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available()) // while the gps signal is being recieved
      gps.encode(ss.read()); // reads the gps information
  } while (millis() - start < ms);
}
// Updates the variables with GPS information
void get_gps(){

  Sat = gps.satellites.value();
  Hdop = gps.hdop.hdop();
  Lat = gps.location.lat();
  Lon = gps.location.lng();
  DateTime(gps.date, gps.time);
  Alt = gps.altitude.meters();
  Course = gps.course.deg();
  Speed = gps.speed.kmph();
  Cardinal = TinyGPSPlus::cardinal(Course);
  
}
// GPS RTC
static void DateTime(TinyGPSDate &d, TinyGPSTime &t)
{  
    char date[32];
    char time[32];
    sprintf(date, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    sprintf(time, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Date = date;
    Time = time;
}
