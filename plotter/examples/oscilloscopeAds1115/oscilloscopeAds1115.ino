/*
  ===========================================================================================
  Example used in Quick-Start
  -------------------------------------------------------------------------------------------
  Plotter
  v2.3.0
  https://github.com/devinaconley/arduino-plotter
  by Devin Conley
  ===========================================================================================
*/

#include "Plotter.h"
#include "ADS1115.h" // From the library https://github.com/jrowberg/i2cdevlib

#define SCL_PIN D5
#define SDA_PIN D6

// I/O
#define Status_LED 2 // D4
#define Status_LED_On digitalWrite(Status_LED, LOW)
#define Status_LED_Off digitalWrite(Status_LED, HIGH)

ADS1115 adc0(ADS1115_DEFAULT_ADDRESS);

double a0,a1,a2,a3;

Plotter p;



void setup()
{

    pinMode(Status_LED, OUTPUT);
    Status_LED_On;
    p.Begin();

    // p.AddTimeGraph( "ESP8266 / NodeMCU ADS1115 Voltmeter", 1500, "A0", a0, "A1", a1, "A2", a2, "A3", a3 );
    p.AddTimeGraph( "ESP8266 / NodeMCU ADS1115 Voltmeter", 1500, "A0", a0 );
    p.AddTimeGraph( "ESP8266 / NodeMCU ADS1115 Voltmeter", 1500, "A1", a1 );
    p.AddTimeGraph( "ESP8266 / NodeMCU ADS1115 Voltmeter", 1500, "A2", a2);
    p.AddTimeGraph( "ESP8266 / NodeMCU ADS1115 Voltmeter", 1500, "A3", a3 );
    p.SetColor(1,"cyan");
    p.SetColor(2,"yellow");
    p.SetColor(3,"orange");
    Wire.begin(SDA_PIN, SCL_PIN);

    adc0.initialize(); // initialize ADS1115 16 bit A/D chip

    // We're going to do single shot sampling
    adc0.setMode(ADS1115_MODE_CONTINUOUS);

    // Slow things down so that we can see that the "poll for conversion" code works
    adc0.setRate(ADS1115_RATE_860);

    // Set the gain (PGA) +/- 6.144V
    // Note that any analog input must be higher than –0.3V and less than VDD +0.3
    adc0.setGain(ADS1115_PGA_6P144);
    // ALERT/RDY pin will indicate when conversion is ready

    // pinMode(alertReadyPin,INPUT_PULLUP);
    // adc0.setConversionReadyPinMode();
}

void loop() {
    /*
    x = 10*sin( 2.0*PI*( millis() / 5000.0 ) );
    */

    // a0 = analogRead(A0)/1024 * 3.3;
    // a0 = adc0.getMilliVolts(true);
    //  // usually called within loop()
    // The below method sets the mux and gets a reading.
    adc0.setMultiplexer(ADS1115_MUX_P0_NG);
    a0 = adc0.getMilliVolts(true)/1000;
    // adc0.triggerConversion();
    // pollAlertReadyPin();
    // Serial.print("A0: "); Serial.print(adc0.getMilliVolts(true)); Serial.print("mV\t");

    adc0.setMultiplexer(ADS1115_MUX_P1_NG);
    a1 = adc0.getMilliVolts(true)/1000;
    // adc0.triggerConversion();
    // pollAlertReadyPin();
    // Serial.print("A1: "); Serial.print(adc0.getMilliVolts(true)); Serial.print("mV\t");

    adc0.setMultiplexer(ADS1115_MUX_P2_NG);
    a2 = adc0.getMilliVolts(true)/1000;
    // adc0.triggerConversion();
    // pollAlertReadyPin();
    // Serial.print("A2: "); Serial.print(adc0.getMilliVolts(true)); Serial.print("mV\t");

    adc0.setMultiplexer(ADS1115_MUX_P3_NG);
    a3 = adc0.getMilliVolts(true)/1000;
    // Do conversion polling via I2C on this last reading:
    // Serial.print("A3: "); Serial.print(adc0.getMilliVolts(true)); Serial.print("mV");

    // Serial.println();
    //delay(500);
    p.Plot();
}
