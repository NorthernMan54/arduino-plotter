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

double x;

Plotter p;

void setup()
{
    p.Begin();

    p.AddTimeGraph( "ESP8266 / NodeMCU Voltmeter", 1500, "A0", x );
}

void loop() {
    /*
    x = 10*sin( 2.0*PI*( millis() / 5000.0 ) );
    */

    x = analogRead(A0)/1024 * 3.3;

    p.Plot(); // usually called within loop()
}
