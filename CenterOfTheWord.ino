#include <Adafruit_NeoPixel.h> //Dołączenie biblioteki
#include <LiquidCrystal.h> //Dołączenie bilbioteki
#include "DHT.h"
#define DHT11_PIN 9
DHT dht;




LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza
const uint8_t LICZBA_DIOD_RGB = 10;
const uint8_t PIN_GPIO = 8;
long i;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LICZBA_DIOD_RGB, PIN_GPIO, NEO_GRB + NEO_KHZ800);

unsigned long aktualnyCzas = 0;
unsigned long zapamietanyCzasLED1 = 0;
unsigned long zapamietanyCzasLED2 = 0;
unsigned long miganieLCD = 800;
 
void setup() {
dht.setup(DHT11_PIN);
   
int wilgotnosc = dht.getHumidity();
int temperatura = dht.getTemperature();
  lcd.begin(16, 2); //Deklaracja typu
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("CENTRUM DOWODZENIA JULIANKA"); //Wyświetlenie tekstu
  lcd.setCursor(0, 1); //Ustawienie kursora
  lcd.print("Temp: "); //Wyświetlenie tekstu
  lcd.setCursor(9, 1); //Ustawienie kursora
  lcd.print("Wilg:"); //Wyświetlenie tekstu
  lcd.blink(); //Włącznie kursora


  strip.begin();
  strip.show();
}


 
void loop() {
aktualnyCzas = millis();




i = i + 1;
  for (int d = 0; d < LICZBA_DIOD_RGB; d++) {
    int G = sin((float)(i - d * 250) / 250.0) * 100 + 100;
    int B = cos((float)(i - d * 250) / 250.0) * 100 + 100;
    int R = sin(!(float)(i - d * 250) / 250.0) * 100 + 100;
    strip.setPixelColor(d, 0, G, B, 0);
    int D = sin((float)(i - d * 250) / 250.0) * 100 + 100;
    int E = cos((float)(i - d * 250) / 250.0) * 100 + 100;
    int F = sin(!(float)(i - d * 250) / 250.0) * 100 + 100;
    strip.setPixelColor(d, F, D, E, 0);
  
  }

  strip.show();


 if (aktualnyCzas - zapamietanyCzasLED1 >= miganieLCD) {
  zapamietanyCzasLED1 = aktualnyCzas; 
     for (int positionCounter = 0; positionCounter < 1; positionCounter++) {
//     scroll one position left:
    lcd.scrollDisplayLeft();
    
    int wilgotnosc = dht.getHumidity();
    int temperatura = dht.getTemperature();
    lcd.setCursor(5, 1); //Ustawienie kursora
    lcd.print(temperatura); //Wyświetlenie tekstu
    lcd.setCursor(7, 1); //Ustawienie kursora
    lcd.print("C"); //Wyświetlenie tekstu
    lcd.setCursor(14, 1); //Ustawienie kursora
  
    lcd.print(wilgotnosc); //Wyświetlenie tekstu
    lcd.setCursor(16, 1); //Ustawienie kursora
    lcd.print("%"); //Wyświetlenie tekstu
}
}
}
