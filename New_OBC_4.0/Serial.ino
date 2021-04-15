void getSerial()
{
//IMU Information
  if (status < 0) 
  {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    Serial.print("-----------------------------------------------------------------------------------\n");
    delay(10);
  }
  else if(status > 0)
{
  // display the data
  Serial.print("Acceleration X: ");
  Serial.print(imuArray[0],6);
  Serial.print("\t");
  Serial.print("Acceleration Y: ");
  Serial.print(imuArray[1],6);
  Serial.print("\t");
  Serial.print("Acceleration Z: ");
  Serial.print(imuArray[2],6);
  Serial.print("\n");
  Serial.print("Gyro X: ");
  Serial.print(imuArray[3],6);
  Serial.print("\t\t");
  Serial.print("Gyro Y: ");
  Serial.print(imuArray[4],6);
  Serial.print("\t\t");
  Serial.print("Gyro Z: ");
  Serial.print(imuArray[5],6);
  Serial.print("\n");
  Serial.print("Magnetometer X: ");
  Serial.print(imuArray[6],6);
  Serial.print("\t");
  Serial.print("Magnetometer Y: ");
  Serial.print(imuArray[7],6);
  Serial.print("\t");
  Serial.print("Magnetometer Z: ");
  Serial.print(imuArray[8],6);
  Serial.print("\n");
  Serial.print("IMU Temperature in Celcius: ");
  Serial.println(imuArray[9],6);
  Serial.print("-----------------------------------------------------------------------------------\n");
  delay(20);
}
//Pressure Information
  Serial.print(F("Temperature from Pressure Sensor: "));
  Serial.print(Temperature);
  Serial.print(F(" Pressure: "));
  Serial.println(Pressure);
  Serial.print("-----------------------------------------------------------------------------------\n");
//Temperature Information 
  Serial.print(tempSensor); Serial.println(" degrees C");
  Serial.print("-----------------------------------------------------------------------------------\n");
//GPS Information
 Serial.print(F("Date: ")); 
 Serial.print(Date);
 Serial.print(F(" Time: "));
 Serial.print(Time);
 Serial.print(F(" Lattitude: "));
 Serial.print(Lat, 6);
 Serial.print(F(" Longitude: "));
 Serial.print(Lon, 6);
 Serial.print(F(" Altitude: "));
 Serial.print(Alt);
 Serial.print(F(" Course: "));
 Serial.print(Course);
 Serial.print(F(" Speed: "));
 Serial.print(Speed);
 Serial.print(F(" Cardinal: "));
 Serial.print(Cardinal);
 Serial.print(F(" Satellite Count: "));
 Serial.print(Sat);
 Serial.print(F(" HDOP: "));
 Serial.print(Hdop);
  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
 Serial.println("\n-----------------------------------------------------------------------------------\n");
 if(!Wire.available())
  Serial.println("Error reading PROM 1"); // error reading the PROM or communicating with the device
 Serial.println("\n-----------------------------------------------------------------------------------\n");
}
