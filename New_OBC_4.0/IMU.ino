/*
Advanced_I2C.ino
Brian R Taylor
brian.taylor@bolderflight.com

Copyright (c) 2017 Bolder Flight Systems

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


void get_imu()
{
 //check status. This will be decoded as a '0' for a failure, disconnection or IMU failure
  if (status < 0) 
  {
  imuArray[0] = 0;
  imuArray[1] = 0;
  imuArray[2] = 0;
  imuArray[3] = 0;
  imuArray[4] = 0;
  imuArray[5] = 0;
  imuArray[6] = 0;
  imuArray[7] = 0;
  imuArray[8] = 0;
  imuArray[9] = 0;
    delay(10);
  }
  //check status. If the checksum is met, the array will take the values of the IMU
else if(status > 0)
{
  
  // read the sensor
  IMU.readSensor();

  //Store the Imu data to the array
  imuArray[0] = IMU.getAccelX_mss();
  imuArray[1] = IMU.getAccelY_mss();
  imuArray[2] = IMU.getAccelZ_mss();
  imuArray[3] = IMU.getGyroX_rads();
  imuArray[4] = IMU.getGyroY_rads();
  imuArray[5] = IMU.getGyroZ_rads();
  imuArray[6] = IMU.getMagX_uT();
  imuArray[7] = IMU.getMagY_uT();
  imuArray[8] = IMU.getMagZ_uT();
  imuArray[9] = IMU.getTemperature_C();
}
}
