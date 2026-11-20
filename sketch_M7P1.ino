// #include <SPI.h>
// #include <MFRC522.h>

// #define SS_PIN  D2
// #define RST_PIN D1

// MFRC522 rfid(SS_PIN, RST_PIN);

// String strID;

// void setup() {
//   Serial.begin(9600);

//   SPI.begin();

//   rfid.PCD_Init();

//   Serial.println();
//   Serial.println("KARTUNE ENDI JIEEE......");
// }

// void loop() {

//   // Cek apakah ada kartu baru
//   if (!rfid.PICC_IsNewCardPresent()) {
//     return;
//   }

//   // Baca UID kartu
//   if (!rfid.PICC_ReadCardSerial()) {
//     return;
//   }

//   // Ambil UID kartu
//   strID = "";

//   for (byte i = 0; i < rfid.uid.size; i++) {

//     if (rfid.uid.uidByte[i] < 0x10) {
//       strID += "0";
//     }

//     strID += String(rfid.uid.uidByte[i], HEX);

//     if (i != rfid.uid.size - 1) {
//       strID += ":";
//     }
//   }

//   strID.toUpperCase();

//   Serial.print("ID Kartune Panjenengan : ");
//   Serial.println(strID);

//   // Hentikan komunikasi dengan kartu
//   rfid.PICC_HaltA();
//   rfid.PCD_StopCrypto1();

//   delay(1000);
// }

//Project Terintegrasi

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  D2
#define RST_PIN D1
#define LED_PIN D4

MFRC522 rfid(SS_PIN, RST_PIN);

// ID CONTROL

String CONTROL_ID = "DE:08:44:06";

String strID;

void setup() {

  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  pinMode(LED_PIN, OUTPUT);

  // LED OFF
  digitalWrite(LED_PIN, HIGH);

  Serial.println();
  Serial.println("Templekno kartune jiee...");
}

void loop() {

  // Cek apakah ada kartu
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Baca kartu
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // BACA UID

  strID = "";

  for (byte i = 0; i < rfid.uid.size; i++) {

    if (rfid.uid.uidByte[i] < 0x10) {
      strID += "0";
    }

    strID += String(rfid.uid.uidByte[i], HEX);

    if (i != rfid.uid.size - 1) {
      strID += ":";
    }
  }

  strID.toUpperCase();

  Serial.print("UID Kartu : ");
  Serial.println(strID);

  // CEK ID CONTROL

  if (strID == CONTROL_ID) {

    Serial.println("STATUS    : ID CONTROL");
    Serial.println("AKSES     : DITERIMA");
    Serial.println("LED       : ON");

    // LED ON
    digitalWrite(LED_PIN, HIGH);

    // Nyala 0.5 detik
    delay(500);

    // LED OFF
    digitalWrite(LED_PIN, LOW);

    Serial.println("LED       : OFF");

  } else {

    Serial.println("STATUS    : ID BIASA");
    Serial.println("AKSES     : DITOLAK");
    Serial.println("LED       : OFF");
  }

  Serial.println("--------------------------------");

  // Hentikan komunikasi dengan kartu
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(500);
}