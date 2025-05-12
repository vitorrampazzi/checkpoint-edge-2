#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// DHT
#define DHTPIN 2
#define DHTTYPE DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pinos
int ldrPin = A0;
int ledVerde = 3;      // Luminosidade OK
int ledAmarelo = 4;    // Temperatura fora da faixa
int ledVermelho = 5;   // Umidade fora da faixa
int buzzer = 6;

// Carinha personalizada
byte vinhozinho[8] = {
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00100,
  B01110,
  B00000,
};

// Variáveis
float somaTemp = 0, somaUmid = 0, somaLuz = 0;
int contador = 0;
unsigned long ultimoTempo = 0;
const unsigned long intervalo = 5000;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  lcd.backlight();

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.createChar(0, vinhozinho);
  lcd.setCursor(0, 0);
  lcd.print("  Bem-vindo  ");
  lcd.setCursor(14, 0);
  lcd.write(byte(0));
  lcd.setCursor(0, 1);
  lcd.print("Vinheria Agnello");
  delay(3000);
  lcd.clear();
}

void loop() {
  int leituraLDR = analogRead(ldrPin);
  // Mapeando a leitura do LDR (0-1023) para 0-100
  int luzMapeada = map(leituraLDR, 0, 1023, 0, 100);

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  float temp = event.temperature;
  dht.humidity().getEvent(&event);
  float umid = event.relative_humidity;

  if (!isnan(temp) && !isnan(umid)) {
    somaLuz += luzMapeada;
    somaTemp += temp;
    somaUmid += umid;
    contador++;
  }

  if ((millis() - ultimoTempo >= intervalo) && contador >= 5) {
    float mediaLuz = somaLuz / contador;
    float mediaTemp = somaTemp / contador;
    float mediaUmid = somaUmid / contador;

    Serial.println("----- MEDIAS -----");
    Serial.print("Luz: "); Serial.println(mediaLuz);
    Serial.print("Temp: "); Serial.println(mediaTemp);
    Serial.print("Umid: "); Serial.println(mediaUmid);

    bool alertaLuz = false;
    bool alertaTemp = false;
    bool alertaUmid = false;

    bool ledVerdeON = false;
    bool ledAmareloON = false;
    bool ledVermelhoON = false;

    // --- LUMINOSIDADE ---
    lcd.clear();
    if (mediaLuz < 25) { // equivalente ao <250 antes
      lcd.setCursor(0, 0);
      lcd.print("Ambiente escuro");
      ledVerdeON = true;
    } else if (mediaLuz < 60) { // equivalente ao <600
      lcd.setCursor(0, 0);
      lcd.print("Ambiente a meia");
      lcd.setCursor(0, 1);
      lcd.print("luz");
      ledAmareloON = true;
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Ambiente muito");
      lcd.setCursor(0, 1);
      lcd.print("claro");
      alertaLuz = true;
      ledVermelhoON = true;
    }

    delay(3000);
    lcd.clear();

    // --- TEMPERATURA ---
    if (mediaTemp >= 10 && mediaTemp <= 15) {
      lcd.setCursor(0, 0);
      lcd.print("Temperatura OK");
      lcd.setCursor(0, 1);
      lcd.print(mediaTemp, 1); lcd.print(" C");
    } else {
      alertaTemp = true;
      ledAmareloON = true;
      lcd.setCursor(0, 0);
      lcd.print(mediaTemp < 10 ? "Temp. Baixa" : "Temp. Alta");
      lcd.setCursor(0, 1);
      lcd.print(mediaTemp, 1); lcd.print(" C");
    }

    delay(3000);
    lcd.clear();

    // --- UMIDADE ---
    if (mediaUmid >= 50 && mediaUmid <= 70) {
      lcd.setCursor(0, 0);
      lcd.print("Umidade OK");
      lcd.setCursor(0, 1);
      lcd.print(mediaUmid, 0); lcd.print(" %");
    } else {
      alertaUmid = true;
      ledVermelhoON = true;
      lcd.setCursor(0, 0);
      lcd.print(mediaUmid < 50 ? "Umid. Baixa" : "Umid. Alta");
      lcd.setCursor(0, 1);
      lcd.print(mediaUmid, 0); lcd.print(" %");
    }

    delay(3000);

    // Controle do buzzer
    if (alertaLuz || alertaTemp || alertaUmid) {
      tone(buzzer, 1500);
    } else {
      noTone(buzzer);
    }

    // Controle dos LEDs
    digitalWrite(ledVerde, ledVerdeON ? HIGH : LOW);
    digitalWrite(ledAmarelo, ledAmareloON ? HIGH : LOW);
    digitalWrite(ledVermelho, ledVermelhoON ? HIGH : LOW);

    // Reset variáveis para próxima média
    contador = 0;
    somaLuz = 0;
    somaTemp = 0;
    somaUmid = 0;
    ultimoTempo = millis();
  }

  delay(500);
}
