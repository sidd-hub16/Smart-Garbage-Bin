#include <WiFi.h>
#include <HTTPClient.h>

#define TRIG_PIN 18
#define ECHO_PIN 19
#define BUZZER 21

//const char* ssid = "SIDDHU";
//const char* password = "12345678";

long duration;
float distance;

void setup()
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(115200);

  // Connect to WiFi
  /*WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  */
}

float getDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  return duration * 0.034 / 2;
}

void loop()
{
  distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 8)
  {
    Serial.println("-------GARBAGE BIN IS FULL!!--------");  // send signal to computer
  }
  else
  {
    Serial.println("NOT_FULL");
  }

  delay(2000); 
}