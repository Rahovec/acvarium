/*
 * Sample example for Olimexino-328 Rev.C and thermistor 10 kOhm, B=3435
 * In order to work connect: 
 * one of the outputs of thermistor to 3.3V;
 * the other one to A0;
 * A0 through 10 kOhm to GND.
 * 
 *    ^ 3.3V
 *    |
 *   _|_
 *  |NTC|
 *  |10K|
 *  |___|
 *    |
 *    |
 *    +------------ A0
 *    |
 *   _|_
 *  |   |
 *  |10K|
 *  |___|
 *    |
 * ___|___  GND
 *   ___
*/


void setup()
{
  Serial.begin (9600);
  pinMode (A0, INPUT);
}

int tmp;
float r, temperature;

#define	R0	((float)10000)
#define	B	((float)3435)
// R0 = 10000 [ohm]
// B  = 3435
// T0 = 25 [C] = 298.15, [K]
// r = (ADC_MAX * R0) / (ADC_VAL) - R0
// R_ = R0 * e ^ (-B / T0), [ohm] --> const ~= 0.09919 (10K);
// T = B/ln (r/R_), [K]

void loop()
{
  tmp = analogRead (A0);
  Serial.print ("A0 = ");
  Serial.println (tmp);
  r = ((1023.0*R0)/(float)tmp)-R0;
  temperature = B/log(r/0.09919) - 273.15;	// log is ln in this case
  
  Serial.print ("T = ");
  Serial.print (temperature);
  Serial.println (", C");
  delay (1000);
}
