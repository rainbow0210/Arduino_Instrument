// NeoPixel
#include <Adafruit_NeoPixel.h>
#define PIN 4
#define NUMPIXELS 24 

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// LCD
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd_1(0);

// 変数
int ultrasound = 0; // 超音波距離センサ―
int pich = 0; // 圧電スピーカー
int tonguing = 0; // Digital 3の信号
int right_num = 0; // NeoPixelの個数制限用
int red = 0; // NeoPixelのLEDの赤用
int blue = 0; // NeoPixelのLEDの青用
String oto = "";

void setup()
{
  pinMode(3, OUTPUT);
  pixels.begin(); // NeoPixel 初期化
  lcd_1.begin(16, 2); // LCD
  Serial.begin(9600);
}

void loop()
{
  // 押しボタン
  tonguing = digitalRead(3);
  
  // 超音波距離センサ
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
  pinMode(2, INPUT);
  ultrasound = 0.01723 * pulseIn(2, HIGH);
  Serial.println(ultrasound);
  
  // 圧電スピーカー
  pich = map(ultrasound, 37, 309, 261, 523);
  if ( tonguing == 0 ){
  	tone(8, pich, 800);
    //delay(800);
  }
  Serial.println(pich);
  
  // NeoPixel
  right_num = map(ultrasound, 37, 309, 0, 24);
  red = map(ultrasound, 37, 309, 0, 255);
  blue = map(ultrasound, 37, 309, 255, 0);
  
  for( int i=0; i < right_num; i++) {
  	pixels.setPixelColor(i, pixels.Color(red, 0, blue));
  }
  
  for( int i=right_num; i < NUMPIXELS; i++) {
  	pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
 
  pixels.show();
  
  // LCD
  lcd_1.setCursor(0, 1);

  if( pich >= 523 ) {
  	oto = "C";
  }
  else if( pich >= 493 ) {
  	oto = "H";
  }
  else if( pich >= 466 ) {
  	oto = "Ais";
  }
  else if( pich >= 440 ) {
  	oto = "A";
  }
  else if( pich >= 415 ) {
  	oto = "Gis";
  }
  else if( pich >= 391 ) {
  	oto = "G";
  }
  else if( pich >= 369 ) {
  	oto = "Fis";
  }
  else if( pich >= 349 ) {
  	oto = "F";
  }
  else if( pich >= 329 ) {
  	oto = "E";
  }
  else if( pich >= 311 ) {
  	oto = "Dis";
  }
  else if( pich >= 293 ) {
  	oto = "D";
  }
  else if( pich >= 277 ) {
  	oto = "Cis";
  }
  else{
  	oto = "C";
  }
  
  lcd_1.print(oto);
  lcd_1.setBacklight(1);
  
  delay(750); // Wait for 100 millisecond(s)
}