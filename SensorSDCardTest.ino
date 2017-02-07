#include <Wire.h>
#include <SPI.h>
#include <SD.h>

//Digital pin 12 is the MicroSD slave select pin on the Mayfly
#define SD_SS_PIN 12

//The data log file
#define FILE_NAME "DataLog.txt"

//Data header  (these lines get written to the beginning of a file when it's created)
#define LOGGERNAME "Mayfly microSD Card Tester"
#define DATA_HEADER "SampleNumber, Battery_volts"

int sampleinterval = 1;    //time between samples, in seconds

int samplenum = 1;      // declare the variable "samplenum" and start with 1
int moisturePin = A0;    // on the Mayfly board, pin A6 is connected to a resistor divider on the battery input

double moistureValue = 0;  // variable to store the value coming from the analogRead function
float moisture;       // the battery voltage as calculated by the formula below


void setup() 
{
  //Initialise the Serial1 connection
  Serial.begin(9600);
  //Serial.begin(57600);
  //Initialise log file
  setupLogFile();
  
  //Echo the data header to the Serial1 connection
  Serial.println(DATA_HEADER);
  
}

void loop() 
{
  String dataRec = createDataRecord();
  
  //Save the data record to the log file
  logData(dataRec);
  
  //Echo the data to the Serial1 connection
  Serial.println(dataRec);
  
  delay(sampleinterval*1000);   //multiply by 1000 to convert from milliseconds to seconds

}


void setupLogFile()
{
  //Initialise the SD card
  if (!SD.begin(SD_SS_PIN))
  {
    Serial.println("Error: SD card failed to initialise or is missing.");
    //Hang
  //  while (true); 
  }
  
  //Check if the file already exists
  bool oldFile = SD.exists(FILE_NAME);  
  
  //Open the file in write mode
  File logFile = SD.open(FILE_NAME, FILE_WRITE);
  // write to file if old file exists
  //Add header information if the file did not already exist
  if (!oldFile)
  {
    logFile.println(LOGGERNAME);
    logFile.println(DATA_HEADER);
  }
  
  //Close the file to save it
  logFile.close();  
}


void logData(String rec)
{
  //Re-open the file
  File logFile = SD.open(FILE_NAME, FILE_WRITE);
  
  //Write the CSV data
  logFile.println(rec);
  
  //Close the file to save it
  logFile.close();  
}

String createDataRecord()
{
  //Create a String type data record in csv format
  //SampleNumber, Battery
  String data = "";
  data += "Sample number: ";
  data += samplenum;           //creates a string called "data", put in the sample number 
  data += ",  Soil moisture: ";                 //adds a comma between values
  moistureValue = analogRead(A0);         // reads the analog voltage on the batteryPin, reported in bits
  Serial.println(moistureValue);
  double voltage1 = (moistureValue/1023)*3;
 // Serial.println(voltage1);
  double vwc;
  if(voltage1 <= 1.1)
  {
    vwc = 10*voltage1-1;
    }
  else if(voltage1 <= 1.3)
  {
    vwc = 25*voltage1-17.5;
    }
  else if(voltage1 <= 1.82)
  {
    vwc = 48.08*voltage1-47.5;
    }
  else if(voltage1 <= 2.2)
  {
    vwc = 26.32*voltage1-7.89;
    }
 else vwc = 0;
  //moisture = (3.3/1023.) * 1.47 * moistureValue;      // converts bits into volts (see batterytest sketch for more info)
  data += vwc;     //adds the battery voltage to the data string
  samplenum++;   //increment the sample number
  return data;
}
