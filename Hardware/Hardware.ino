class GreenHouse
{
  private:
    int Temperature, Humidity, Moisture, Acidity;
    byte CountNumber;
  public:
    GreenHouse(byte CountNumberInput)
    {
      CountNumber = CountNumberInput;
      Temperature = 0; Humidity = 0; Moisture = 0; Acidity = 0;
    }

    ~GreenHouse()
    {

    }

    void GetSensorsData()
    {
      Temperature = random(20, 25);
      Humidity = random(60, 80);
      Moisture = random(60, 80);
      Acidity = random(10, 20);
    }

    void SendToSerial()
    {
      GetSensorsData();
      char GreenHouse_Data[100];
      //sprintf(GreenHouse_Data, "Green House #%d: Temperature: %dC, Humidity: %d%c, Moisture: %d%c, Acidity: %d%c", CountNumber, Temperature, Humidity, '%', Moisture, '%', Acidity, '%');
      sprintf(GreenHouse_Data, "%d, %d, %d, %d, %d", CountNumber, Temperature, Humidity, Moisture, Acidity);
      Serial.println(GreenHouse_Data);
    }
};

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  GreenHouse GreenHouseOne(1);
  
  while (1)
  {
    GreenHouseOne.SendToSerial();

    delay(1000);
  }
}
