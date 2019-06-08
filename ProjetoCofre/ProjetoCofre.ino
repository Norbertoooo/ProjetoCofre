#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <SPI.h>        // RC522 Module uses SPI protocol
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // Criando um LCD de 16x2 no endereço 0x27
// Create MFRC522 instance.
#define SS_PIN 53
#define RST_PIN 5
#define rele 8
MFRC522 mfrc522(SS_PIN, RST_PIN);
byte readCard[4];

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.init();                 // Inicializando o LCD
  lcd.backlight();            // Ligando o BackLight do LCD
  SPI.begin();           // MFRC522 Hardware uses SPI protocol
  mfrc522.PCD_Init();    // Initialize MFRC522 Hardware
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
  lcd.print("Sistema de cofre");
  pinMode(rele,OUTPUT);
}
void loop()
{
  String conteudo = "";
    
    if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
    return 0;
  }
  lcd.clear();
  lcd.print("UID:");
  for ( uint8_t i = 0; i < 4; i++) {
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
    lcd.print(mfrc522.uid.uidByte[i], HEX);
  }
  conteudo.toUpperCase();
   if (conteudo.substring(1) == "CD 53 43 73")
  {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.println("Liberado");
    digitalWrite(rele,HIGH);
    delay(1000);
  }
    if (conteudo.substring(1) == "21 39 3E 2E")
  {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.println("fechado");
    digitalWrite(rele,LOW);
    delay(1000);
  }
  
  delay(1000);  
}


  
