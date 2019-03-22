#include <SPIFFS.h>
#define ANALOG_PIN_0 39
#define ANALOG_PIN_1 34
#define ANALOG_PIN_2 36

float RawV = 0;
float Voltage = 0;

float RawTemp = 0;
double Temp_V = 0;
double Temperature = 0;

float Vref = 38;
float RawAmps = 0;
float Amps_Offset = 1392;
double Amps_V = 0;
double Current = 0;
double PCurrent = 0;
float Power = 0;
float Amp = 0;
float Sample = 0;

int Status = 0;
float Energy = 0;
float Capacity = 0;
float E_Last_Value = 0;
float C_Last_Value = 0;

void Volts()
{
  //Reading Voltage Value//
  RawV = analogRead(ANALOG_PIN_0);
  Voltage = (RawV * 53) / 4095;
  Serial.print("Voltage=");
  Serial.print(Voltage);
}

void Ampere()
{
  //Reading Current Value//
  for (int i = 0; i < 5; i++)
  {
    Amp = analogRead(ANALOG_PIN_2);
    Sample = Amp + Sample;
    delay(10);
  }
  RawAmps = Sample / 5;
  Sample = 0;
  Amps_V = ((RawAmps * 3100) / 4095);
  Current = ((Amps_V - Amps_Offset) / Vref)*-1;
  delay(500);
  Serial.print(" Current=");
  Serial.print(Current);

}

void Celsius() {
  //Reading Tempearture Value//
  RawTemp = analogRead(ANALOG_PIN_1);
  Temp_V = (RawTemp / 1024) * 3300;
  Temperature = Temp_V * 0.1;
  Serial.print("Temperature (C) =");
  Serial.print(Temperature);
  delay(500);

}

void Watts() {
  if (Current < 0)
  {
    PCurrent = Current*-1;
  }
  else
  {
    PCurrent = Current;
  } 
  Power = Voltage * PCurrent;
  Serial.print(" Power=");
  Serial.print(Power);
}

int State() {
  //Battery Indication
  if (Current < 0)
  {
    if (Current > -0.5) {
      //SerialBT.print("Resting");
      //SerialBT.print(",");
      Status = 0;
      //
    }
    else {
      //SerialBT.print("Discharging");
      //SerialBT.print(",");
      Status = -1;
      //
    }
  }
  else if (Current > 0)
  {
    if (Current < 0.5) {
      //SerialBT.print("Resting");
      //SerialBT.print(",");
      Status = 0;
      //
    }
    else {
      //SerialBT.print("Charging");
      //SerialBT.print(",");
      Status = 1;
      //
    }
  }
  else {
    //SerialBT.print("Resting");
    //SerialBT.print(",");
    Status = 0;
    //
  }
  Serial.print("State = ");
  Serial.print(Status);
  return Status;

}
/*void energy() {
  Energy = Energy + (Power / 3600);
  Serial.print("Energy = ");
  Serial.print(Energy);
  }

  void capacity() {
  Capacity= Capacity + (Current/3600);
    Serial.print("Capacity = ");
    Serial.print(Capacity);
  }*/

void SOC() {
  //Resting
  if (Status == 0)
  {
    Energy =  E_Last_Value;
    Capacity =  C_Last_Value;
    // Energy=EEPROM.read(0);
    // Capacity=EEPROM.read(1);
    Serial.println("Battery is at REST: ");
    Serial.print(" Energy = ");
    Serial.print(Energy, 6);
    
    Serial.print(" Capacity = ");
    Serial.print(Capacity, 6);
  }

  //Charging
  else if (Status == 1)
  {
    Energy =  E_Last_Value;
    Capacity =  C_Last_Value;
    Serial.print(" Charging: ");
    Energy = Energy + (Power / 3600);
    Capacity = Capacity + (Current / 3600);
    Serial.print(" Energy = ");
    Serial.print(Energy, 6);
    Serial.print(" Capacity = ");
    Serial.print(Capacity, 6);
    E_Last_Value = Energy;
    C_Last_Value = Capacity;
    if (Status == 0)
    {
      Energy =  E_Last_Value;
      Capacity =  C_Last_Value;
      Serial.println("Battery is at REST: ");
      Serial.print(" Energy = ");
      Serial.print(Energy, 6);
      Serial.print(" Capacity = ");
      Serial.print(Capacity, 6);
      E_Last_Value = Energy;
      C_Last_Value = Capacity;
    }
  else if (Status == -1)
  {
    Energy =  E_Last_Value;
    Capacity =  C_Last_Value;
    Serial.print(" Discharging: ");
    Energy = Energy + (Power / 3600);
    Capacity = Capacity + (Current / 3600);
    Serial.print("Energy = ");
    Serial.print(Energy, 6);
    Serial.print(" Capacity = ");
    Serial.print(Capacity, 6);
    E_Last_Value = Energy;
    C_Last_Value = Capacity;
  }
}

//Discharging

else if (Status == -1)
{
  Energy =  E_Last_Value;
  Capacity =  C_Last_Value;
  Serial.print(" Discharging: ");
  Energy = Energy + (Power / 3600);
  Capacity = Capacity + (Current / 3600);
  Serial.print("Energy = ");
  Serial.print(Energy, 6); 
  Serial.print(" Capacity = ");
  Serial.print(Capacity, 6);
  E_Last_Value = Energy;
  C_Last_Value = Capacity;

  if (Status == 0)
  {
    Energy =  E_Last_Value;
    Capacity =  C_Last_Value;
    Serial.println("Battery is at REST: ");
    Serial.print(" Energy = ");
    Serial.print(Energy, 6);
    Serial.print(" Capacity = ");
    Serial.print(Capacity, 6);
    E_Last_Value = Energy;
    C_Last_Value = Capacity;
  }

  else if (Status == 1)
  {
    Energy =  E_Last_Value;
    Capacity =  C_Last_Value;
    Serial.print(" Charging: ");
    Energy = Energy + (Power / 3600);
    Capacity = Capacity + (Current / 3600);
    Serial.print(" Energy = ");
    Serial.print(Energy, 6);
    Serial.print(" Capacity = ");
    Serial.print(Capacity, 6);
    E_Last_Value = Energy;
    C_Last_Value = Capacity;
  }
}
}

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  Volts();
  Ampere();
  Watts();
  Celsius();
  State();
  SOC();
delay(1000);
}
