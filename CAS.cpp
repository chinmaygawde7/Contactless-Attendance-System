#include <SPI.h>
#include <WiFiNINA.h>
#include <SPI.h>
#include <MFRC522.h>

IPAddress myAddress = "http://www.mydatabase.com" //update your server here
WiFiClient client;

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup()
{
  SPI.begin();
  mfrc522.PCD_Init();
}
void loop(){
  emp_id=read_card();
  if (client.connect(myAddress, 80))
   {
     client.write(myAddress+"/attend.php?emp_id="+emp_id); //update php page name here and also replace emp_id with field name of employee id defined in database table
   }
}

String read_card()
{
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  return content;
}