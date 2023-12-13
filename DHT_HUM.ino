#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT22
#define LED_ROJO 14
#define LED_AMARILLO 12
#define LED_VERDE 13
#define TOUCH 16
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(TOUCH, INPUT);
  Serial.begin(9600);

  dht.begin();
}

void loop() {
  delay(2000);

  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_ROJO, LOW);

  float h, t = -10;

  h = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("[]"));
    return;
  }

  Serial.print(F("["));
  Serial.print(h);
  Serial.print(F(","));
  Serial.print(t);
  Serial.println(F("]"));

  if (digitalRead(TOUCH)) {
    if (h >= 10 && h < 31) {
      digitalWrite(LED_ROJO, LOW);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_VERDE, HIGH);
    } else if (h >= 31 && h < 51) {
      digitalWrite(LED_ROJO, LOW);
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_AMARILLO, HIGH);
    } else if (h > 51) {
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_ROJO, HIGH);
    }
  }
}
