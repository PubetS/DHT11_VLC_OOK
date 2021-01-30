
#include "DHT.h"
#define DHTPIN 2 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

#define DELAY 15
#define LED 10 //Output pin where LED is connected
#define ID 129 //ID of Receiver
#define BITLENGTH 8 //1 Byte
#define FIRSTBIT pow(2,(BITLENGTH-1))//MSB Value
#define TRUE 1
#define TEMPERATURE A0
float temp_data, humid_data;
int count=0;
long Timer = millis();
float voltage;
void writeByte(int);
int counter=0;

void setup() {
 //Setting the LED as Output
 pinMode(LED,OUTPUT);
 Serial.begin(115200);
  Serial.println("VLC Environmental sensor transmitter");
dht.begin();
}
void loop()
{
//if ((millis()-Timer)<20000)
//{
//i=analogRead(TEMPERATURE); //Reading the temperature(i.e. the voltage drop on the sensor)
//i = 150;
//j = 250;

 // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  temp_data = map(t,0,100,0,255); //(t/500) * 1024;
  humid_data = h;
writeByte(ID); //Sending ID of Receiver
writeByte(temp_data);//sending the temperature to the receiver
writeByte(humid_data);

  
//float temperature = (float)i*5/1024;
 //temperature=(temperature -0.5)*100;
 Serial.print (" : The tempereature is ");
 Serial.print(t); // Sending the value of temperature
 Serial.println(" 'C");

 Serial.print(++count); // Sending the value of temperature
  Serial.print (" : The temp convert data is ");
 Serial.println(temp_data); // Sending the value of temperature
 
 Serial.print (" : The redo tempereature is ");
 float redo_t = temp_data * 100/255;//map(i,0,1023,0,100);
 Serial.print(redo_t);//(float)i*500/1024); // Sending the value of temperature
 Serial.println(" 'C");

// print humid
 Serial.print (" : The humid is ");
 Serial.print(h); // Sending the value of temperature
 Serial.println(" %");

  Serial.print (" : The humid convert data is ");
 Serial.println(humid_data); // Sending the value of temperature
 
 Serial.print (" : The redo humid is ");
 float redo_h = humid_data;//map(i,0,1023,0,100);
 Serial.print(redo_h);//(float)i*500/1024); // Sending the value of temperature
 Serial.println(" %");
 delay(30); // เพิ่มมาเพื่อให้ระยะห่างแต่ละ 8 บิต มากขึ้น
if (count >256)
 {
 count=0;
 }
//}
}
//Sending 1byte number
void writeByte(int decimal)
{
  //converting the decimal value to binary and sending 8 bit information from MSB to LSB
 int i,binary;
 for(i=0;i<BITLENGTH;i++)
 {
 binary = (int)decimal/FIRSTBIT; //Getting the first binary bit value
 decimal= (decimal & ((int)FIRSTBIT -1));//Setting the first bit to zero
 decimal=decimal<<1; //Shift all bits by one to left
 if(binary==TRUE)
 {
 digitalWrite(LED,HIGH);
 Serial.print("1");
 }else
 {
 digitalWrite(LED,LOW);
Serial.print("0");
 }
 delay(DELAY);
 }
Serial.println();
digitalWrite(LED,LOW);
}
