#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <LiquidCrystal.h>
TinyGPS gps;
SoftwareSerial ss1(0, 1);
SoftwareSerial ss(9, 10);
int sensor=4, state=0;
float flat, flon;
int bump=7;
int buzzer=6;
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);

void setup() 
{
  Serial.begin(9600);
  ss.begin(9600);
  ss1.begin(9600);
  lcd.begin(16, 2);  
  pinMode(sensor, INPUT_PULLUP);
  pinMode(bump, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  lcd.setCursor(0,0);
  lcd.print(" Accidental  ");
  lcd.setCursor(0,1);
  lcd.print(" Info system  ");
  delay(2000);
}

void loop() 

{
  state=digitalRead(sensor);
   if(state==LOW)
   {
     lcd.setCursor(0,0);
       lcd.print("Accident  ");
       lcd.setCursor(0,1);
       lcd.print("Happened  ");
       delay(1000);
       lcd.setCursor(0,1);
       lcd.print("SMS Send       ");
    Serial.println("Pressed");
     digitalWrite(buzzer, HIGH);
        delay(200);
         digitalWrite(buzzer, LOW);
        delay(200);
        digitalWrite(buzzer, HIGH);
        delay(200);
         digitalWrite(buzzer, LOW);
        delay(200);
    getGSM();
   
   }
   else
   {
    GetGPS();


   }    
  int got=digitalRead(bump);
  if(got==LOW)
  {
    Serial.println("Accident Happened!");
       lcd.setCursor(0,0);
       lcd.print("Accident      ");
       lcd.setCursor(0,1);
       lcd.print("Happened      ");
       digitalWrite(buzzer, HIGH);
        delay(500);
         digitalWrite(buzzer, LOW);
        delay(500);
        digitalWrite(buzzer, HIGH);
        delay(500);
         digitalWrite(buzzer, LOW);
        delay(500);
  }
 if(got==HIGH)
  {
    Serial.println("Normal Condition.");
       lcd.setCursor(0,0);
       lcd.print("Normal      ");
       lcd.setCursor(0,1);
       lcd.print("Condition    ");
       digitalWrite(buzzer, LOW);
        
  }
}
void getGSM()
{
    ss1.println("AT\r\n");
       delay(1000);
  ss1.println("ATE0\r\n");
        delay(1000);  
  ss1.println("AT+CMGF=1\r\n");
  delay(1000);
  ss1.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
   lcd.clear();
   lcd.setCursor(0,0);
  lcd.print("SMS Send to");
  lcd.setCursor(0,1);
  lcd.print("7906417774");
  ss1.println("AT+CMGS=\"+917906417774\"\r");  // change to the phone number you using
  delay(1000);
  ss1.println("Alert : someting suspicious found at \r\n");//the content of the message
 
   delay(1000); 
   ss1.print("http://www.google.com/maps/place/");
   ss1.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0  : flat, 6);
   ss1.print(",");
   ss1.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.00 : flon, 6);
   delay(1000); 
   lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LAT=");
  lcd.print(flat);
    lcd.print("  ");
  lcd.setCursor(0,1);
  lcd.print("LOG=");
  lcd.print(flon);
  lcd.print("  "); 
   ss1.println((char)26);
    delay(500);
  
   lcd.clear();
  lcd.print("SMS Send");
   delay(1000); 

}
void GetGPS()
   {
      bool newData = false;
      unsigned long chars;
      unsigned short sentences, failed;
    
      // For one second we parse GPS data and report some key values
      for (unsigned long start = millis(); millis() - start < 1000;)
      {
        while (ss.available())
        {
          char c = ss.read();
          // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
          if (gps.encode(c)) // Did a new valid sentence come in?
            newData = true;
        }
      }
    
      if (newData)
      {
        unsigned long age;
        gps.f_get_position(&flat, &flon, &age);

      }
  }
