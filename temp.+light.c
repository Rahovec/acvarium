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
const int pResistor = A5; // Photoresistor at Arduino analog pin A5
const int ledPin=9;       // Led pin at Arduino pin 9 {eventualno tuk 6te e lampata}


void setup()
{
  Serial.begin (9600);
  pinMode (A0, INPUT);
  pinMode(ledPin, OUTPUT);  // Set ledPin - 9 pin as an output
  pinMode(pResistor, INPUT);// Set pResistor - A0 pin as an input (optional)
}

int tmp;
float r, temperature;
int value;          // Store value from photoresistor (0-1023)

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
  delay (500);
  value = analogRead(pResistor);
  
  //You can change value "25"
  if (value > 400){
    digitalWrite(ledPin, LOW);  //Turn led off
  }
  else{
    digitalWrite(ledPin, HIGH); //Turn led on
  }
  Serial.println ("\npResistor value:");
  Serial.println (value);
}
