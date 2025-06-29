//HE THONG CHONG TROM
//HIEN THI DONG HO 24H TREN LED LCD 16X2 (khong dung I2C cho led lcd)
//Sau 12h KHUYA, hệ thống chống trộm được bật bằng cảm biến SIR 505, nếu có chuyển động, còi sẽ kêu 5 lần. Hệ thống hoạt động đến 6h sáng
//sau 6h sáng, hệ thống hoạt động bình thường

//Khai báo các thành phần sử dụng

//RTC clock
//


#include<LiquidCrystal.h>
#include<RTClib.h>

//khai bao cho lcd

LiquidCrystal lcd(13,12,8,9,10,11);
int sensor=6;
int buzzer=7;

RTC_DS1307 rtc;

void setup() {
  // put your setup code here, to run once:

lcd.begin(16,2);
//FIND RTC 
if(!rtc.begin())
{ lcd.setCursor(0,0);
  lcd.print("RTC NOT FOUND");
  while(1);
}
rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));

pinMode(sensor,INPUT);
pinMode(buzzer,OUTPUT);
digitalWrite(buzzer,LOW);
}


void loop() {
  // put your main code here, to run repeatedly:

DateTime now= rtc.now();
  lcd.setCursor(0,0); 
  lcd.print("     ");
  lcd.setCursor(0,0);
  
  lcd.print(now.day());
  lcd.print('/');
  lcd.print(now.month());
  lcd.print('/');
  lcd.print(now.year());


  lcd.setCursor(0,1);
  lcd.print("        ");
  lcd.setCursor(0,1);
  lcd.print(now.hour());
  lcd.print(':');
  lcd.print(now.minute());
  lcd.print(':');
  lcd.print(now.second());
  delay(1000);

  if(now.hour()>=0 and now.hour()<=6)
  {//SENSOR IS ON AND WE USE INTERRUPT
  lcd.setCursor(9,1);
  lcd.print("Active");
  int doccambien=digitalRead(sensor);

  if(doccambien==HIGH)
    {
    for(int i=0;i<3;i++)
   {
    digitalWrite(buzzer,HIGH);
    delay(500);
    digitalWrite(buzzer,LOW);
    delay(500);
   } 
    }

  }

  else 
  {
  lcd.setCursor(9,1);
  lcd.print("      ");
  }
}
