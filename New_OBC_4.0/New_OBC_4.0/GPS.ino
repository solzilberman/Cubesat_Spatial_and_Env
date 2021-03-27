// Former GPS code, has since been replaced with "New_gps"
/*
void displayInfo()
{
  Serial.println("------------------------------------------------");
  Serial.println("Latitude  Longitude  Date       Time");
  if (gps.location.isValid())
  {
    gpsInfo[0]= gps.location.lat();
    gpsInfo[1]= gps.location.lng();
    Serial.print(gpsInfo[0], 6);
    Serial.print(F(" "));
    Serial.print(gpsInfo[1], 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.date.isValid())
  {
    // Save the Gps date information to the array
    gpsTimestamp[0] = gps.date.month();
    gpsTimestamp[1] = gps.date.day();
    gpsTimestamp[2] = gps.date.year();
    
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  
  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    //Save the Gps time information to the array
    gpsTimestamp[3] = gps.time.hour();
    gpsTimestamp[4] = gps.time.minute();
    gpsTimestamp[5] = gps.time.second();
    gpsTimestamp[6] = gps.time.centisecond();
    
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
    
  }
  Serial.println("");
  Serial.println("------------------------------------------------");

}


//void get_GPS()
//{
//  while (gps.available())
//  {
//    int c = gps.read();
//    //if (digitalRead(DIP_6) != HIGH){
//    //  Serial.write(c);     // Write NMAE Sentences
//    //}
//    
//    if (gps.encode(c))
//    {
//      gps.f_get_position(&flatitude, &flongitude);
//      gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths);
//      gps.stats(&chars, &sentences, &failed_checksum);
//      sprintf(s_month, "%02d", (int)month); sprintf(s_day, "%02d", (int)day);
//      sprintf(s_hour, "%02d", (int)hour); sprintf(s_minute, "%02d", (int)minute); sprintf(s_second, "%02d", (int)second);
//
//      sat = gps.satellites();
//      alt = gps.f_altitude();
//      course = gps.f_course();
//      speed = gps.f_speed_mph();
//    }
//  }
//}

// Use this function to print out the NMEA Sentence.
void read_gpsNMEA() {
  while (ss.available()){
      gps.encode(ss.read());
      displayInfo();
  }
}
*/
