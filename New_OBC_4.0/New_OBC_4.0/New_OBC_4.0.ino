/*
Version 1.0:
Integrate IMU and GPS into one single file
Version 2.0: 
Integrate IMU, GPS, and temperature sensor into one single file
Version 2.1
Integrate float arrays for GPS, IMU and Temperature values to be stored as global variables
float arrays: gpsInfo, imuArray. Variables: tempSensor
Version 3.0 
Integrated the pressure sensor
Variables: Temperature, Pressure.
Verson 3.1 
Integrated the SD card function to save the variables to the SD Card
Version 3.2
Converted all of the serial functions into the serial tab, and added new GPS code
Version 4.0
Updated with RTC code, that interfere's with GPS clock code
Added further commentary for understanding of the code
*/

//----------------------------------------------------------------
//------------------------ HARDWARE ------------------------------
//  The following Peripherals are used with the Teensy 4.1: 
//    - NEO 6M GPS
//    - IMU (Inertial Measurement Unit) MPU-9250
//    - Parallax (#29124): Altimeter/Pressure Sensor MS5607
//    - RTC (Real Time Clock) DS3231 //Still needs code Implemented
//    - TMP (Temperature Sensor) TMP 36 //Still needs code Implemented
//  
//  Voltage Req: 3.3V
// 
//  Teensy 4.1      ----> Peripherals
//  Pin 19 (SCL-0)  ----> Pressure-Sensor SCL
//  Pin 18 (SDA-0)  ----> Pressure-Sensor SDA
//  Pin 00 (RX-1)   ----> GPS RX-B //changed from pin 09 (teensy 3.5)
//  Pin 01 (TX-1)   ----> GPS TX-B //changed from pin 10 (teensy 3.5)
//  Pin 18 (SDA-0)  ----> MPU-9250 SDA
//  Pin 19 (SCL-0)  ----> MPU-9250 SCL
//  Pin 18 (SDA-0)  ----> DS3231 RTC SDA
//  Pin 19 (SCL-0)  ----> DS3231 RTC SCL
//  Pin 18 (SDA-0)  ----> Parallax MS5607 SDA
//  Pin 19 (SCL-0)  ----> Parallax MS5607 SCL
//----------------------------------------------------------------
//----------------------------------------------------------------

////////////////////////////////////////////////////
// Variables for SD Card .                        //
////////////////////////////////////////////////////

#include <SPI.h>                //SD
#include <SD.h>                 //SD

long int currentTime;
String filename = "";
bool file;
int i =0;

File LOG;                       // Create file object
String dataString ="";          // Prepare string variable for data
////////////////////////////////////////////////////
// Variables for RTC .                            //
////////////////////////////////////////////////////
#define DS3231_I2C_ADDRESS 0x68
//// Convert normal decimal numbers to binary coded decimal
//Code below has interference with GPS RTC code. Needs further investigation
//byte decToBcd(byte val)
//{
//  return( (val/10*16) + (val%10) );
//}
//// Convert binary coded decimal to normal decimal numbers
//byte bcdToDec(byte val)
//{
//  return( (val/16*10) + (val%16) );
//}
////////////////////////////////////////////////////
// Variables for Pressure Sensor .                //
////////////////////////////////////////////////////

#include <Wire.h>
#include <math.h>


//#define ADDRESS 0x76 // Address of Parallax - Pressure Sensor MS5607 REV A
#define ADDRESS 0x77 // Address of Far Horizons - Pressure Sensor MS5607 REV B

uint32_t D1 = 0;
uint32_t D2 = 0;
float dT = 0;
int32_t TEMP = 0;
float OFF = 0; 
float SENS = 0; 
float P = 0;
float T2  = 0;
float OFF2  = 0;
float SENS2 = 0;
uint16_t C[7];
//int count = 0;

float Temperature; // Stores Temperature taken from the Pressure Sensor
float Pressure; //Stores Pressure taken from the Pressure Sensor

////////////////////////////////////////////////////
// Variables for TMP 36 .                         //
////////////////////////////////////////////////////
int sensorPin = 21; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures

float tempSensor = 0;
 
////////////////////////////////////////////////////
// Variables for IMU (MPU9250) .                  //
////////////////////////////////////////////////////
#include "MPU9250.h"
// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x69
MPU9250 IMU(Wire,0x69);
int status;

// 9 value array storing IMU values, See IMU tab to specifically see array contents
float imuArray[10];

////////////////////////////////////////////////////
// Variables for GPS                              //
////////////////////////////////////////////////////
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
//const char *gpsStream ="";

static const int RXPin = 0, TXPin = 1; //Update the RX pin and the TX pin here 
static const uint32_t GPSBaud = 9600; //Update the GPS Baud rate here

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
//SoftwareSerial ss(RXPin, TXPin);
//TinyGPS gps;
#define ss Serial1

//Gps Variable's defined below
int Sat, Age;
double Hdop, Lat, Lon, Alt, Course, Speed;
String Cardinal, Deg, Date, Time;

void setup() {

////////////////////////////////////////////////////
// SD Card Setup                                  //
////////////////////////////////////////////////////
  Serial.begin(115200);
  SDsetup();
  delay(1000);
  
  //Header
  String header = 
    String("millis") + "," + 
    String(" Pressure Temp. (C)") + "," + String("Pressure(bar)") + "," + String("Temp.(C)") + "," + String("IMU Accel X ") + "," + String("IMU Accel Y") + "," + String("IMU Accel Z") + "," + String("IMU Gyro X")
    + "," + String("IMU Gyro Y") + "," + String("IMU Gyro Z") + "," + String("IMU Mag X") + "," + String("IMU Gyro Y") + "," + String("IMU Gyro Z") + "," + String("IMU Temperature"); 
  logData(header);              // Header is saved to the top of the file

////////////////////////////////////////////////////
// Pressure Sensor Setup                          //
////////////////////////////////////////////////////
 // Disable internal pullups, 10Kohms are on the breakout
 PORTC |= (1 << 4);
 PORTC |= (1 << 5);

  Wire.begin();
  Serial.begin(57600); //9600 changed 'cos of timing?
  delay(1000); //Give the open log a second to get in gear. 
  initial(ADDRESS);
   
////////////////////////////////////////////////////
// Shared Setup                                   //
////////////////////////////////////////////////////
  Serial.begin(9600); // GPS, IMU
  
////////////////////////////////////////////////////
// Setup for IMU (MPU9250) .                      //
////////////////////////////////////////////////////
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);  // setting the accelerometer full scale range to +/-8G 
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS); // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ); // setting DLPF bandwidth to 20 Hz
  IMU.setSrd(99);  // DATA OUTPUT RATE = 1000/(1+SRD) HZ 
////////////////////////////////////////////////////
// Setup for GPS                                  //
////////////////////////////////////////////////////
  ss.begin(GPSBaud);
 
}
void loop()
{
  //GPS
  get_gps();
    String dataStream = String(Date) + "," +  String(Time) + "," + 
                      String(Lat, 6) + "," + String(Lon, 6) + "," + String(Alt) + "," + 
                      String(Course) + "," + String(Speed) + "," + String(Cardinal) + "," + 
                      String(Sat) + "," + String(Hdop);
  smartDelay(1000); //Waits for Full Gps sentence to be recieved, then waits 1 second
  //Temperature sensor
  get_temp();
  //imu
  get_imu();
  //pressure sensor
  get_pressure();
  //updates pressure information onto sd card
  get_sd();
  //turns on Serial Monitor
  getSerial(); //turn off when in flight
}
