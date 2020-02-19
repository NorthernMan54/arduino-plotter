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
#include "ADS1115.h"

#define SCL_PIN D5
#define SDA_PIN D6

ADS1115 adc0(ADS1115_DEFAULT_ADDRESS);

double a0,a1,a2,a3;

Plotter p;



void setup()
{
    p.Begin();

    p.AddTimeGraph( "ESP8266 / NodeMCU ADS1115 Voltmeter", 1500, "A0", a0, "A1", a1, "A2", a2, "A3", a3 );
    Wire.begin(SDA_PIN, SCL_PIN);

    adc0.initialize(); // initialize ADS1115 16 bit A/D chip

    // We're going to do single shot sampling
    adc0.setMode(ADS1115_MODE_CONTINUOUS);

    // Slow things down so that we can see that the "poll for conversion" code works
    adc0.setRate(ADS1115_RATE_860);

    // Set the gain (PGA) +/- 6.144V
    // Note that any analog input must be higher than –0.3V and less than VDD +0.3
    adc0.setGain(ADS1115_PGA_4P096);
    // ALERT/RDY pin will indicate when conversion is ready

    // pinMode(alertReadyPin,INPUT_PULLUP);
    // adc0.setConversionReadyPinMode();
}

void loop() {
    /*
    x = 10*sin( 2.0*PI*( millis() / 5000.0 ) );
    */

    // x = analogRead(A0)/1024 * 3.3;
    // a0 = adc0.getMilliVolts(true);
    //  // usually called within loop()
    // The below method sets the mux and gets a reading.
    adc0.setMultiplexer(ADS1115_MUX_P0_NG);
    a0 = adc0.getMilliVolts(true)/1000;
    // adc0.triggerConversion();
    // pollAlertReadyPin();
    //Serial.print("A0: "); Serial.print(adc0.getMilliVolts(true)); Serial.print("mV\t");
/*
    adc0.setMultiplexer(ADS1115_MUX_P1_NG);
    a1 = adc0.getMilliVolts(true)/1000;
    // adc0.triggerConversion();
    // pollAlertReadyPin();
    //Serial.print("A1: "); Serial.print(adc0.getMilliVolts(true)); Serial.print("mV\t");

    adc0.setMultiplexer(ADS1115_MUX_P2_NG);
    a2 = adc0.getMilliVolts(true)/1000;
    // adc0.triggerConversion();
    // pollAlertReadyPin();
    //Serial.print("A2: "); Serial.print(adc0.getMilliVolts(true)); Serial.print("mV\t");

    adc0.setMultiplexer(ADS1115_MUX_P3_NG);
    a3 = adc0.getMilliVolts(true)/1000;
    // Do conversion polling via I2C on this last reading:
    //Serial.print("A3: "); Serial.print(adc0.getMilliVolts(true)); Serial.print("mV");
*/
    //Serial.println();
    //delay(500);
    p.Plot();
}

/*
#include "ADS1115.h"

ADS1115 adc0(ADS1115_DEFAULT_ADDRESS);

// Wire ADS1115 ALERT/RDY pin to Arduino pin 2
const int alertReadyPin = 2;

void setup() {
    //I2Cdev::begin();  // join I2C bus
    Wire.begin();
    Serial.begin(115200); // initialize serial communication

    Serial.println("Testing device connections...");
    Serial.println(adc0.testConnection() ? "ADS1115 connection successful" : "ADS1115 connection failed");

    adc0.initialize(); // initialize ADS1115 16 bit A/D chip

    // We're going to do single shot sampling
    adc0.setMode(ADS1115_MODE_SINGLESHOT);

    // Slow things down so that we can see that the "poll for conversion" code works
    adc0.setRate(ADS1115_RATE_8);

    // Set the gain (PGA) +/- 6.144V
    // Note that any analog input must be higher than –0.3V and less than VDD +0.3
    adc0.setGain(ADS1115_PGA_6P144);
    // ALERT/RDY pin will indicate when conversion is ready

    pinMode(alertReadyPin,INPUT_PULLUP);
    adc0.setConversionReadyPinMode();

    // To get output from this method, you'll need to turn on the
    //#define ADS1115_SERIAL_DEBUG // in the ADS1115.h file
    #ifdef ADS1115_SERIAL_DEBUG
    adc0.showConfigRegister();
    Serial.print("HighThreshold="); Serial.println(adc0.getHighThreshold(),BIN);
    Serial.print("LowThreshold="); Serial.println(adc0.getLowThreshold(),BIN);
    #endif
}


void pollAlertReadyPin() {
  for (uint32_t i = 0; i<100000; i++)
    if (!digitalRead(alertReadyPin)) return;
   Serial.println("Failed to wait for AlertReadyPin, it's stuck high!");
}

void loop() {

    // The below method sets the mux and gets a reading.
    adc0.setMultiplexer(ADS1115_MUX_P0_NG);
    adc0.triggerConversion();
    pollAlertReadyPin();
    Serial.print("A0: "); Serial.print(adc0.getMilliVolts(false)); Serial.print("mV\t");

    adc0.setMultiplexer(ADS1115_MUX_P1_NG);
    adc0.triggerConversion();
    pollAlertReadyPin();
    Serial.print("A1: "); Serial.print(adc0.getMilliVolts(false)); Serial.print("mV\t");

    adc0.setMultiplexer(ADS1115_MUX_P2_NG);
    adc0.triggerConversion();
    pollAlertReadyPin();
    Serial.print("A2: "); Serial.print(adc0.getMilliVolts(false)); Serial.print("mV\t");

    adc0.setMultiplexer(ADS1115_MUX_P3_NG);
    // Do conversion polling via I2C on this last reading:
    Serial.print("A3: "); Serial.print(adc0.getMilliVolts(true)); Serial.print("mV");

    Serial.println(digitalRead(alertReadyPin));
    delay(500);
}
*/
