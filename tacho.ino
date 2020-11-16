// Easy Tachometer for TME project ver 0.1
// K. Chanon 2020 
// contanct chanon.khong@mail.kmutt.ac.th
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define ENCODER_PIN 2
#define RESOLUTION 90
 
unsigned long gulCount = 0;
 
unsigned long gulStart_Timer = 0;
unsigned short gusChange = 0;
unsigned long gulStart_Read_Timer = 0;
short gsRPM = 0;

#define sensor 13

float value=0;
float rev=0;
int rpm;
int oldtime=0;        
int time;

void isr()       
{
rev++;
while(!digitalRead(2));
}


void setup() 
{
  Serial.begin(115200);
  pinMode(sensor, INPUT);
  lcd.begin(16, 2);
  lcd.print("Techometer2");
  digitalWrite(HIGH, 2);
  attachInterrupt(digitalPinToInterrupt(2),COUNT,CHANGE  ); 
}

void loop() 
{
      lcd.setCursor(0,1);
      if ((millis() - gulStart_Read_Timer) >= 500)
      {
      gsRPM = usRead_RPM();
       
      if (gsRPM >= 300)
      {
      gsRPM = gsRPM - 230;
      }
      Serial.print("RPM: ");
      Serial.println(gsRPM);
      gulStart_Read_Timer = millis();
      }
      lcd.clear();
      lcd.print("RPM=");
      lcd.print(gsRPM);
      delay(50);

}

short usRead_RPM(void)
{
  unsigned long ulRPM = 0;
  unsigned long ulTimeDif = 0;
   
  detachInterrupt(digitalPinToInterrupt(ENCODER_PIN));
   
  ulTimeDif = millis() - gulStart_Timer;
  ulRPM = 60000 * gulCount;
  ulRPM = ulRPM / ulTimeDif;
  ulRPM = ulRPM / RESOLUTION;
  //usRPM = ((60*1000*gulCount)/ulTimeDif)/RESOLUTION;
   
  gulCount = 0;
  gulStart_Timer = millis();
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), COUNT, CHANGE);
   
  return (short)ulRPM;
}
 
void COUNT(void)
{
gulCount++;
gusChange = 1;
}
