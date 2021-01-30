#define SETTING 5
#define DELAY 15
#define BITLENGTH 8
#define DIFFERENCE 10
#define S1 4
#define ID 129
#define sensorPin A0
int sensorValue = 0;
int middleValue;
int inputByte;
int inputByte2;
void checkMiddle();
int readByte();
int j;
float temperature; 
float humidity;
long counter=millis();
int count=0;
void setup() {
 Serial.begin(115200);
 checkMiddle();//Setting the value between Logic 0 and Logic 1
 Serial.println("Sensor is calibrated ");
}
void loop() {
 //do
// {
// if(digitalRead(S1)==HIGH)
// {
// checkMiddle();
// Serial.println("Sensor is calibrated ");
// }
// sensorValue = analogRead(sensorPin);
//}while(sensorValue<=middleValue);
if((inputByte=readByte())==ID)
{
 inputByte=readByte(); //Reading 1 Byte
  inputByte2=readByte();
 //Calculating temperature
// temperature = (float)inputByte*5/1024;
// temperature=(temperature -0.5)*100;
temperature = (float)inputByte*100/255;
humidity = (float)inputByte2;

Serial.print (" count : ");
Serial.println(++count); // Sending the value of temperature
 Serial.println(inputByte);
 Serial.print (" : The tempereature is ");
 Serial.print(temperature); // Sending the value of temperature
 Serial.println(" 'C");

Serial.println(inputByte2);
Serial.print (" : The humidity is ");
Serial.print(humidity);
Serial.println(" %");

 if (count >256)
 {
 count=0;
 }
}
}
void checkMiddle()
{
  Serial.println("checking Middle value ");
 int difference;
 middleValue = analogRead(sensorPin); //Cehcking initial voltage on the sensor
 do{
 sensorValue=analogRead(sensorPin);//Checking second voltage on sensor
 difference= sensorValue - middleValue;//Comparing the values of the voltage
 delay(SETTING);
 }while(difference<DIFFERENCE && difference>-DIFFERENCE);
 //Calculating the middle value between Logic 1 and Logic 0
 middleValue = (sensorValue + middleValue)/2;
 Serial.print("middle Value is ");
 Serial.println(middleValue);
}

int readByte()
{
 int i,input=0;
for(i=0;i<BITLENGTH;i++)
{//Repeat for each bit
 sensorValue= analogRead(sensorPin);//Read the sensor Value
 if(sensorValue>= middleValue) // ปรับค่าเองระหว่าง 55 - 60, 58 rec.
 {
 input++;
 }
//Binary shift to store another bit
input=input<<1;
delay(DELAY);
}
//Return the value if input
input=input>>1;
return input;
}
