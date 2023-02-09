#include <iostream>
#include "SerialPort.cpp"
#include "TypeAbbreviations.hpp"
#include <chrono>
#include <thread>

using namespace std;

class GreenHouse
{
  public:
    int CountNumber, Temperature, Humidity, Moisture, Acidity;
    int TemperatureLimit, HumidityLimit, MoistureLimit, AcidityLimit;
    bool isDataReady;

  GreenHouse(int TemperatureLimitInput = 23,  int HumidityLimitInput = 65, int MoistureLimitInput = 65, int AcidityLimitInput = 18)
  {
    TemperatureLimit = TemperatureLimitInput; HumidityLimit = HumidityLimitInput;
    MoistureLimit = MoistureLimitInput; AcidityLimit = AcidityLimitInput;
    CountNumber = 0; Temperature = 0; Humidity = 0; Moisture = 0; Acidity = 0;
    isDataReady = false;
  }

  ~GreenHouse()
  {

  }

  void SetParamsFromSerialPort(char* InputString)
  {
    if (sscanf(InputString, "%d, %d, %d, %d, %d", &CountNumber, &Temperature, &Humidity, &Moisture, &Acidity) == 5) 
        {
            isDataReady = true;
            cout << "Data Received OK!" << endl;
        }
  }

  bool TempAlarmCheck()
  {
      if(isDataReady)
      {
          if(Temperature < TemperatureLimit)
            return false;
          else
              return true;
      }
  }
};


int main(int argc, const char * argv[])
{
    using namespace std::this_thread;
    using namespace std::chrono; // nanoseconds, system_clock, seconds

    GreenHouse GreenHouseOne(23, 66, 66, 15);

    int sfd = openAndConfigureSerialPort("/dev/cu.usbmodem14201", 9600);
    if (sfd < 0) 
    {
        if (sfd == -1) 
        {
            printf("Unable to connect to serial port.\n");
        }
        else 
        { //sfd == -2
            printf("Error setting serial port attributes.\n");
        }
        return 0;
    }
    
    while(serialPortIsOpen)
    {
        char IncomingData[150];
        readSerialData(IncomingData, 120);

        GreenHouseOne.SetParamsFromSerialPort(IncomingData);
        
        cout << "Current Temperature: " << GreenHouseOne.Temperature << " C" << endl;
        cout << "Temperatre Alarm State: " << GreenHouseOne.TempAlarmCheck() << endl << endl;

        memset(IncomingData, 0, sizeof IncomingData);
        sleep_for(seconds(1));
    }
}