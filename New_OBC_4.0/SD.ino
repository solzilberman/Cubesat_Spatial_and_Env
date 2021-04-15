// define length of char array
#define N 255


///// USER CAN CHANGE VALUES BELOW /////
String FILE_BODY = "LOG";
String FILE_EXTENSION = ".CSV";
const unsigned int CHIP = BUILTIN_SDCARD;
const unsigned int BAUD_RATE = 9600;

////////////////////////////////////////
unsigned int FILE_NUMBER_INT = 0;
String FILE_NUMBER_STRING = "000";
String testFilename = FILE_BODY + FILE_NUMBER_STRING + FILE_EXTENSION;
char FILENAME[N] = {};


void SDsetup() { 
  if (initSD()) {
    // create filename
    initFile();

    // attempt to open file
    checkSD();
  }
  delay(1000);
}


int initSD() {
  // attempt to initialize SD card
  Serial.print("Initializing SD card... ");
  if (!SD.begin(CHIP)) {
    Serial.println("initialization failed / no SD card.");
    // return failure
    
  } else {
    Serial.println("initialization successful.");
    // return success
    
  }
}


void initFile() {
  
  File root = SD.open("/");               // open root
  // iterate over root
  
  while (true) {
    File entry = root.openNextFile();    // open the first / next file in the directory
    if (!entry) break;                   // reached last file and no match found, so filename is OK

    // current filename exists
    if (  String( entry.name() ).equals(testFilename)  ) {
      
      FILE_NUMBER_INT++;                  // increment file number integer
      updateFileNumberString();           // update the file number string to match file number integer
      testFilename = FILE_BODY + FILE_NUMBER_STRING + FILE_EXTENSION;  // create the next filename to look for
    }
  }
  // when loop is broken, viable filename has been found
  // transfer string to char[] for SD function
  for (unsigned int i = 0; i < N; i++) {
    FILENAME[i] = testFilename[i];
  }
}

void checkSD() {
  // open file
  LOG = SD.open(FILENAME, FILE_WRITE);
  filename = FILENAME;
  
  if (LOG) {
    // print to console
    Serial.print("Writing to ");
    Serial.print(FILENAME);
    Serial.print("...");
    
    // close the file
    LOG.close();
    Serial.println("done.");
    file = true;
    
  } else {
    // if the file didn't open, print an error
    Serial.print("Error opening ");
    Serial.println(FILENAME);
    file = false;
  }
}

void updateFileNumberString() {
  // check digits of FILE_NUMBER_INT
  if (FILE_NUMBER_INT >= 100) {
    
    FILE_NUMBER_STRING = String(FILE_NUMBER_INT);         // three digits
  } else if (FILE_NUMBER_STRING >= 10) {
    
    FILE_NUMBER_STRING = "0" + String(FILE_NUMBER_INT);   // two digits
  } else {
    
    FILE_NUMBER_STRING = "00" + String(FILE_NUMBER_INT);  // one digit
  }
}


void logData(String logS) {
  // open file for writing

  if (LOG = SD.open(FILENAME, FILE_WRITE)) {
    file = true;
    LOG.println(logS);
    LOG.close();
     
     if (Serial) 
     {
      Serial.println(logS);
     }
  }
}
void get_sd()
{
currentTime=millis();         // get time  
// Prepare data from all global variables into dataString
  dataString =
    String(currentTime) + "," + String(Temperature) + "," +  String(Pressure) + "," +  String(tempSensor) + "," +  String(imuArray[0]) + "," +  String(imuArray[1]) + "," +  String(imuArray[2]) + "," +  String(imuArray[3]) + "," +  String(imuArray[4])
     + "," +  String(imuArray[5]) + "," +  String(imuArray[6]) + "," +  String(imuArray[7]) + "," +  String(imuArray[8]) + "," +  String(imuArray[9]);

    logData(dataString);        // Opens SD Card and saves a full string of global variables

  delay(200);
}
