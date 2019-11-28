#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
// 객체 생성 _ lcd는 주소에 맞게 수정. 
int sw = 5;
int obstacle = 7;
int isobstacle = HIGH;
int score = 0;

int buzzer = 6;
int sec = 0;
int min = 0;
int hour =0;
int counter =0;
 
void setup() {
  pinMode(sw,INPUT_PULLUP);
  pinMode(obstacle,INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  
  lcd.init(); // lcd 초기화
  lcd.backlight(); // lcd 백라이트 켬.
  lcd.setCursor(5,0);
  lcd.print("FINGER");
  lcd.setCursor(3,1);
  lcd.print("BASKETBALL");
  delay(1000);
  lcd.setCursor(4,0);
  lcd.print("Loading");
  lcd.setCursor(3,1);
  lcd.print("SOKSOK.com");
}

void loop() { 
  sec = millis()/1000-60*counter;
  isobstacle = digitalRead(obstacle);
  delay(1000);

  if(sec == 60) {
  counter++;
  min++;
  Serial.println("게임 종료");
  analogWrite(buzzer,63);
  lcd.setCursor(0,0);
  lcd.print("Game");
  lcd.setCursor(0,1);
  lcd.print("OVER");
  }
  
  if(digitalRead(sw)==LOW){
  score = 0;
  Serial.println("게임 시작");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Game");
  lcd.setCursor(0,1);
  lcd.print("START");
  delay(1000);
  }
    
  if(isobstacle==LOW){
    score ++;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Goal!");
    lcd.setCursor(0,1);
    lcd.print("Score : ");
    lcd.print(score);
    } 


}
