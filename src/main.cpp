#include <Arduino.h>
#include <WiFi.h>
#include <TridentTD_LineNotify.h>

#define SSID "vivo Y33s"                                         //ใส่ชื่อ Wifi
#define PASSWORD "0623039285"                                  //ใส่รหัส Wifi
#define LINE_TOKEN "ue2b1LRtbrk4FPny0FJCDx8GLAJPju929F2RH9Nga2k" //ใส่ TOKEN

//กำหนดขาที่เชื่อมต่อกับเซ็นเซอร์
int sensorPin = 34;

//กำหนดขาที่เชื่อมต่อกับมอเตอร์
const int greenLED = 23; // GPIO 23 Motor Pum ON
const int redLED = 22;   // GPIO 22 Motor Pum OFF

// ข้อความ ที่จะแสดงใน Line
String txt1 = "ความชื้นเท่ากับ "; //ข้อความ 1 ที่จะแสดงใน Line
String txt2 = " รดน้ำได้แล้ว !"; //ข้อความ 2 ที่จะแสดงใน Line

void setup()
{
  Serial.begin(115200); // Starts the serial communication
  //กำหนดให้ขาดิจิตอล sensorPin รับข้อมูลจากเซ็นเซอร์
  pinMode(sensorPin, INPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);

  Serial.println(LINE.getVersion());

  //เริ่มการเชื่อมต่อกับวายฟายแม่ข่าย
  WiFi.begin(SSID, PASSWORD);

  //แสดง "WiFi Connecting" ในคอนโซล
  Serial.printf("WiFi connecting ", SSID);

  //ตรวจเช็คสถานะการเขื่อมต่อวายฟาย
  //ถ้าไม่สำเร็จให้แสดง "." ในคอนโซลจนกว่าจะเขื่อมต่อได้
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(400);
  }
  //แสดงสถานะการวายฟายเชื่อมต่อแล้ว
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN);
}

void loop()
{
  int Humidity = analogRead(sensorPin);
  if (Humidity < 700)
  {
    Serial.print("Moisture Sensor Value:");
    Serial.println(Humidity);
    digitalWrite(greenLED, HIGH);
    Serial.println("greenLED: ON ");
    Serial.println("===================");
    digitalWrite(redLED, LOW);
    Serial.println("redLED: OFF ");
    LINE.notify(txt1 + Humidity + txt2);
  }
  else if (Humidity >= 700)
  {
    Serial.print("Moisture Sensor Value:");
    Serial.println(Humidity);
    digitalWrite(greenLED, LOW);
    Serial.println("===================");
    Serial.println("greenLED: OFF ");
    digitalWrite(redLED, HIGH);
    Serial.println("redLED: ON ");
  }

  delay(1000);
}