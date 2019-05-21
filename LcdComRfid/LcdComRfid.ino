#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#include <SPI.h>

//Programa: Teste de Display LCD 16 x 2
//Autor: FILIPEFLOP
 
//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>
#define SDA_PIN  9
#define RST_PIN 8
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(6, 7, 5, 4, 3, 2);
MFRC522 mfrc522(SDA_PIN, RST_PIN);  // Create MFRC522 instance.
String UID = "";

void setup()
{
  //Define o número de colunas e linhas do LCD
  Serial.begin(9600);
  lcd.begin(16, 2);
  SPI.begin();    
  mfrc522.PCD_Init(); 
    Serial.println("start");
 

}
 
void loop()
{ 
  String UID = "";

  
  if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial() ) {
         delay(50);
         return;
        }
   // Pega o ID da Tag através da função LeitorRFID.uid e Armazena o ID na variável IDtag        
        for (byte i = 0; i < mfrc522.uid.size; i++) {        
            UID.concat(String(mfrc522.uid.uidByte[i], HEX));
        }   
  Serial.println(UID);
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(4, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Tag:");
  lcd.setCursor(1, 1);
  lcd.print(UID);
 
  delay(1000);
   
}
