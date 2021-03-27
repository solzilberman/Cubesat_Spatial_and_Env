void get_pressure()
 {
/*******************************************************************************/
/**************                PRESSURE                   **********************/
/*******************************************************************************/
  
  D1 = getVal(ADDRESS, 0x48); // Pressure raw
  D2 = getVal(ADDRESS, 0x58);// Temperature raw

  dT   = (float)D2 - ((uint32_t)C[5] * 256);
  OFF  = ((float)C[2] * 131072) + ((dT * C[4]) / 64);
  SENS = ((float)C[1] * 65536) + (dT * C[3] / 128);

  TEMP = (int64_t)dT * (int64_t)C[6] / 8388608 + 2000;
  
 if(TEMP < 2000) // if temperature lower than 20 Celsius 
  {
    
    T2=pow(dT,2)/2147483648;
    OFF2=61*pow((TEMP-2000),2)/16;
    SENS2=2*pow((TEMP-2000),2);
    
   if(TEMP < -1500) // if temperature lower than -15 Celsius 
    {
     OFF2=OFF2+15*pow((TEMP+1500),2);
     SENS2=SENS2+8*pow((TEMP+1500),2);
    }

    TEMP = TEMP - T2;
    OFF = OFF - OFF2; 
    SENS = SENS - SENS2;   
  }
  
  Temperature = (float)TEMP / 100;  
  P  = (D1 * SENS / 2097152 - OFF) / 32768;
  Pressure = (float)P / 100;

//  Serial.print("$FHDAT");
//  Serial.print(",");
//  Serial.print(count);
  /* RESET THE CORECTION FACTORS */
  
    T2 = 0;
    OFF2 = 0;
    SENS2 = 0;

  delay(100);
 }





long getVal(int address, byte code)
{
  unsigned long ret = 0;
  Wire.beginTransmission(address);
  Wire.write(code);
  Wire.endTransmission();
  delay(10);
  // start read sequence
  Wire.beginTransmission(address);
  Wire.write((byte) 0x00);
  Wire.endTransmission();
  Wire.beginTransmission(address);
  Wire.requestFrom(address, (int)3);
  if (Wire.available() >= 3)
  {
    ret = Wire.read() * (unsigned long)65536 + Wire.read() * (unsigned long)256 + Wire.read();
  }
  else {
    ret = -1;
  }
  Wire.endTransmission();
  return ret;
}

void initial(uint8_t address)
{
  //Serial.println();
  //Serial.println("PRESSURE SENSOR PROM COEFFICIENTS");

  Wire.beginTransmission(address);
  Wire.write(0x1E); // reset
  Wire.endTransmission();
  delay(10);


  for (int i=0; i<6  ; i++) {

    Wire.beginTransmission(address);
    Wire.write(0xA2 + (i * 2));
    Wire.endTransmission();

    Wire.beginTransmission(address);
    Wire.requestFrom(address, (uint8_t) 6);
    delay(1);
    if(Wire.available())
    {
       C[i+1] = Wire.read() << 8 | Wire.read();
    }
    //Serial.println(C[i+1]);   // Prints out the coefficients.
  }
  //Serial.println();
}
