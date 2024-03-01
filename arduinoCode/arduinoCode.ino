#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

//LED
const int ON = 1;
const int OFF = 0;
#define RED_LED A1
#define GREEN_LED A0
//RFID
#define SS_PIN 10
#define RST_PIN 9
//buzzer
#define BUZZER A2

//LCD 1602 instance
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
//RFID RC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

const String NO_MESSAGE_RECEIVED = "No message received from server";

//metoda szablonowa w jezyku Arduino, która wykonuje się tylko raz podczas odpalenia
void setup() {
  //LED
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  //buzzer
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);

  initialState();
//inicjalizacja interfejsu SPI oraz modułu czytnika RFID
  SPI.begin();
  mfrc522.PCD_Init();


}
//metoda szablonowa w jezyku Arduino, która wykonuje się w pętli cały czas
void loop() {
  
  if(tagDetected()){
    beeperOn(1000);
    lcdScreenDisplayText("Authorizing...");
    delay(1000);
    sendDataToServer();
    String screenText = receiveStringFromServer();
    finalTask(screenText);
    delay(5000);

    initialState(); //powrót do stanu pierwotnego

  }
  delay(1000);
}
//ustawienie stanu inicjalizacji
void initialState(){
  lcdScreenDisplayText("Scan your tag");
  setLedState(RED_LED,ON);
  setLedState(GREEN_LED,OFF);
}
//sprawdza czy pojawiła się nowa karta oraz odczytuje kod UID karty
 boolean tagDetected(){
    return mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial();
}


  void finalTask(String message){
    if(message != "Unauthorized" && message != NO_MESSAGE_RECEIVED){
      setLedState(RED_LED,OFF);
      setLedState(GREEN_LED,ON);
    }
    lcdScreenDisplayText(message);
  }
//ustawia LED w odpowiedni stan
  void setLedState(int ledName, int state){
    if(state == OFF){
        digitalWrite(ledName, LOW);
    } else{
        digitalWrite(ledName, HIGH);
    }

  }
//wyświetla na LCD dowolny tekst
  void lcdScreenDisplayText(String message){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
  }
//uruchamia beeper na odpowiednią długość
  void beeperOn(int beepLength_ms){
    digitalWrite(BUZZER, HIGH);
    delay(beepLength_ms);
    digitalWrite(BUZZER, LOW);

  }
//wysyła odczytane z karty na port szeregowy
  void sendDataToServer(){
        for (byte i = 0; i < mfrc522.uid.size; i++) {
          Serial.print(mfrc522.uid.uidByte[i], HEX);
        }
        delay(500); // Delay to avoid continuous reading
      }

//odczytuje informacje wyslane na port szeregowy
  String receiveStringFromServer(){
    delay(2000); // time required to retrieve data from server if exist
    if(Serial.available() > 0){
        return Serial.readStringUntil('\n');
    }
    return NO_MESSAGE_RECEIVED;
        
  }
