#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS  100
#define EEPROM_SIZE                 512

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);
bool foundCalib = false;

int numberCalib = 0;

void setup(void)
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Orientation Sensor Test"); Serial.println("");
 
  // Initialise the sensor
  if(!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  setSensorCalibration(); 

  delay(1000);
   
  // Display some basic information on this sensor
  displaySensorDetails();

  // Display current status
  displaySensorStatus();

  // Crystal must be configured AFTER loading calibration data into BNO055.
  bno.setExtCrystalUse(true);

  Serial.println("End of Setup"); Serial.println("");  
}

void loop(void)
{
  sensors_event_t event;
  bno.getEvent(&event);
 
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");

  // Display calibration status
  displayCalStatus();
  
  // Display current status
  //displaySensorStatus();
  
  Serial.println("");
 
  delay(BNO055_SAMPLERATE_DELAY_MS);
}

//////////////////////
// BNO055 functions //
//////////////////////
void displaySensorDetails(void)
{
  sensor_t sensor;
  bno.getSensor(&sensor);
  
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx"); 
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displaySensorStatus(void)
{
  uint8_t system_status, self_test_results, system_error;
  system_status = self_test_results = system_error = 0;
  bno.getSystemStatus(&system_status, &self_test_results, &system_error);

  Serial.println("");
  Serial.print("System Status: 0x");
  Serial.println(system_status, HEX);
  Serial.print("Self Test:     0x");
  Serial.println(self_test_results, HEX);
  Serial.print("System Error:  0x");
  Serial.println(system_error, HEX);
  Serial.println("");
  delay(500);
}

void setSensorCalibration()
{
  byte calData;
  
  bno.setMode( bno.OPERATION_MODE_CONFIG );    // Put into CONFIG_Mode
  delay(25);

  // Acc Radius
  calData = bno.setCalvalARL(232);
  calData = bno.setCalvalARM(3);
  
  // Mag Radius
  calData = bno.setCalvalMRL(87);
  calData = bno.setCalvalMRM(3);

  // Acc Offset X
  calData = bno.setCalvalAOXL(231);
  calData = bno.setCalvalAOXM(255);
  // Acc Offset Y
  calData = bno.setCalvalAOYL(253);
  calData = bno.setCalvalAOYM(255);
  // Acc Offset Z
  calData = bno.setCalvalAOZL(5);
  calData = bno.setCalvalAOZM(0);
  
  // Mag Offset X
  calData = bno.setCalvalMOXL(14);
  calData = bno.setCalvalMOXM(1);
  // Mag Offset Y
  calData = bno.setCalvalMOYL(127);
  calData = bno.setCalvalMOYM(0);
  // Mag Offset Z
  calData = bno.setCalvalMOZL(173);
  calData = bno.setCalvalMOZM(1);

  // Gyro Offset X
  calData = bno.setCalvalGOXL(155);
  calData = bno.setCalvalGOXM(255);
  // Gyro Offset Y
  calData = bno.setCalvalGOYL(255);
  calData = bno.setCalvalGOYM(255);
  // Gyro Offset Z
  calData = bno.setCalvalGOZL(254);
  calData = bno.setCalvalGOZM(255);
 
  bno.setMode( bno.OPERATION_MODE_NDOF );    // Put into NDOF Mode
  delay(25);
}

void getSensorCalibration()
{
  byte calData;
  
  bno.setMode( bno.OPERATION_MODE_CONFIG );    // Put into CONFIG_Mode

  Serial.println("******************");
  Serial.println("Calibration Data: ");
  Serial.println("******************");
 
  calData = bno.getCalvalARL();
  Serial.println(calData);
  calData = bno.getCalvalARM();
  Serial.println(calData);
 
  calData = bno.getCalvalMRL();
  Serial.println(calData);
  calData = bno.getCalvalMRM();
  Serial.println(calData);
 
  calData = bno.getCalvalAOXL();
  Serial.println(calData);
  calData = bno.getCalvalAOXM();
  Serial.println(calData);
 
  calData = bno.getCalvalAOYL();
  Serial.println(calData);
  calData = bno.getCalvalAOYM();
  Serial.println(calData);
 
  calData = bno.getCalvalAOZL();
  Serial.println(calData);
  calData = bno.getCalvalAOZM();
  Serial.println(calData);
 
  calData = bno.getCalvalMOXL();
  Serial.println(calData);
  calData = bno.getCalvalMOXM();
  Serial.println(calData);
 
  calData = bno.getCalvalMOYL();
  Serial.println(calData);
  calData = bno.getCalvalMOYM();
  Serial.println(calData);
 
  calData = bno.getCalvalMOZL();
  Serial.println(calData);
  calData = bno.getCalvalMOZM();
  Serial.println(calData);
 
  calData = bno.getCalvalGOXL();
  Serial.println(calData);
  calData = bno.getCalvalGOXM();
  Serial.println(calData);
 
  calData = bno.getCalvalGOYL();
  Serial.println(calData);
  calData = bno.getCalvalGOYM();
  Serial.println(calData);
 
  calData = bno.getCalvalGOZL();
  Serial.println(calData);
  calData = bno.getCalvalGOZM();
  Serial.println(calData);

  Serial.println("******************");

  bno.setMode( bno.OPERATION_MODE_NDOF );    // Put into NDOF Mode
  delay(25);
}

void displayCalStatus()
{
  byte cal = bno.getCalib();
  byte calSys = (0xC0 & cal) >> 6;
  byte calGyro = (0x30 & cal) >> 4;
  byte calAccel = (0x0C & cal) >> 2;
  byte calMag = (0x03 & cal) >> 0;

  Serial.print("Cal:");
  Serial.print(cal, HEX);
  Serial.print(" Num:");
  Serial.print(numberCalib);

  Serial.print(" Sys:");
  Serial.print(calSys);
  Serial.print(" G:");
  Serial.print(calGyro);
  Serial.print(" A:");
  Serial.print(calAccel);
  Serial.print(" M:");
  Serial.println(calMag);
 
  delay(500);
  
  if ((cal == 255) && (foundCalib == false))
  {
    getSensorCalibration();
    foundCalib = true;
    numberCalib ++;
  }

  if (cal != 255)
   foundCalib = false;
}
