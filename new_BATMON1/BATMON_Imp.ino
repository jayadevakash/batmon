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
float Amps_Offset = 1395;
double Amps_V = 0;
double Current = 0;

float Power;
float Amp = 0;
float Sample = 0;

float Status = 0;

float Ws = 0;

void Volts() {

  //Reading Voltage Value//

  RawV = analogRead(ANALOG_PIN_0);
  Voltage = (RawV * 54) / 4095;
  Serial.print("Voltage=");
  Serial.print(Voltage);/*
  Serial.print("RawV=");
  Serial.print(RawV);*/
}

void Ampere() {
  //Reading Current Value//
  for (int i = 0; i < 100; i++)
  {
    Amp = analogRead(ANALOG_PIN_2);
    Sample = Amp + Sample;
    delay(10);
  }
  RawAmps = Sample / 100;
  Sample = 0;
  Amps_V = ((RawAmps * 3100) / 4095);
  Current = ((Amps_V - Amps_Offset) / Vref);
  delay(500);

  Serial.print(" Current=");
  Serial.print(Current);
  //Serial.print(" Amps_V=");
  //Serial.print(Amps_V);
  //Serial.print("RawAmps=");
  //Serial.println(RawAmps);/*

}

void Celsius() {
  //Reading Tempearture Value//

  RawTemp = analogRead(ANALOG_PIN_1);
  Temp_V = (RawTemp / 4095) * 3300;
  Temperature = Temp_V * 0.1;

  //Serial.print("RawTemp=");
  //Serial.print(RawTemp);
  Serial.print("Temperature (C) =");
  Serial.print(Temperature);
  delay(500);

}

void Watts() {
  Power = Voltage * Current;
  Serial.print(" Power=");
  Serial.println(Power);
}

void State() {

  //Battery Indication
  if (Current < 0)
  {
    if (Current > -0.5) {
      //SerialBT.print("Resting");
      //SerialBT.print(",");
      Status = 0;
      //Serial.print(",");
    }
    else {
      //SerialBT.print("Discharging");
      //SerialBT.print(",");
      Status = -1;
      //Serial.print(",");
    }
  }
  else if (Current > 0)
  {
    if (Current < 0.5) {
      //SerialBT.print("Resting");
      //SerialBT.print(",");
      Status = 0;
      //Serial.print(",");
    }
    else {
      //SerialBT.print("Charging");
      //SerialBT.print(",");
      Status = 1;
      //Serial.print(",");
    }
  }
  else {
    //SerialBT.print("Resting");
    //SerialBT.print(",");
    Status = 0;
    //Serial.print(",");
  }
  Serial.print("State = ");
  Serial.print(Status);

}


void Energy() {
  Ws = Ws + (Power / 3600);
  Serial.print("Energy = ");
  Serial.print(Ws);
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
  Energy();

  delay(1000);
}
//Testing with the Git
