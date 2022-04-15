/*TDS*/

#define SERIAL Serial
#define sensorPin A2
#include <SoftwareSerial.h>
SoftwareSerial bt(10,11); // RX, TX
float sensorValue = 0;
float sensorValueTUR = 0;

float Voltage = 0;
float tempc;
float phValue;
float tdsValue;
float turValue;

 
void setup() {
    SERIAL.begin(9600);
     bt.begin(9600); 
 Serial.println("Ready");
}
void loop() {
   if (bt.available())  /* If data is available on serial port */
    {
     Serial.write(bt.read()); /* Print character received on to the serial monitor */
    }
   
sensorValue = analogRead(sensorPin);
    Voltage = sensorValue*5/1024.0; //Convert analog reading to Voltage
    tdsValue=(133.42/Voltage*Voltage*Voltage - 255.86*Voltage*Voltage + 857.39*Voltage)*0.5; //Convert voltage value to TDS value
    SERIAL.print("TDS Value = "); 
    Serial.print("\t");
    SERIAL.print(tdsValue);
    delay(1000); 

  float sensorValueTUR = analogRead(A3);// read the input on analog pin A0:
  float turValue = sensorValueTUR * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  
  Serial.println("Turbidity Value Is = ");
  Serial.print("\t");
  Serial.println(turValue); // print out the value you read:
  delay(500);


float calibration = -5.00; //change this value to calibrate
const float analogInPin = A4; 
float sensorValueph = 0; 
unsigned long int avgValue; 
float b;
int buf[10],temp;
 
 for(int i=0;i<10;i++) 
 { 
 buf[i]=analogRead(analogInPin);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buf[i]>buf[j])
 {
 temp=buf[i];
 buf[i]=buf[j];
 buf[j]=temp;
 }
 }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 float pHVol=(float)avgValue*5.0/1024/6;
 float phValue = 3.5 * pHVol+calibration;
 Serial.print("Ph value sensor is  = ");
 Serial.println(phValue);
 
 delay(500);



 const float sensor=A5; // Assigning analog pin A1 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius
float tempf;  //variable to store temperature in Fahreinheit 
float vout;  //temporary variable to hold sensor reading

vout=analogRead(sensor);
vout=(vout*500)/2047;
tempc=vout; // Storing value in Degree Celsius
tempf=(vout*1.8)+32; // Converting to Fahrenheit 
Serial.print("in DegreeC=");
Serial.print("\t");
Serial.print(tempc);
Serial.println();

delay(1000); //Delay of 1 second for ease of viewing 


 bt.print(tempc); //send to MIT App
 bt.print(";");
 
 bt.print(phValue); //send to MIT App 
 bt.println(";");

 
 bt.println(tdsValue);
 bt.println(",");


 bt.println(turValue);
 bt.println(",");
 
  
  delay(1000);
}
