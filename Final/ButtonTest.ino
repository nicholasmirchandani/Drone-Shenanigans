#include <WiFi101.h>

WiFiClient client;

char ssid[] = "Drone Shenanigans";        // your network SSID (name)
char pass[] = "NotDroneShenanigans";    // your network password (use for WPA, or use as key for WEP)

bool b1;
bool b1_prev;
bool b2;
bool b2_prev;
bool b3;
bool b3_prev;

// targetIP is ddd.ddd.ddd.ddd
IPAddress targetIP(192, 168, 103, 2);

void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT); // Power for the button
  pinMode(6, INPUT); // Read pin of button
  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
  pinMode(11, OUTPUT);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT); // Debug Output

  WiFi.setPins(8, 7, 4, 2);

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

    // attempt to connect to WiFi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Attempting to connect");
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid, pass);
  }
  Serial.println("Connected to wifi");

  if (client.connect(targetIP, 9090)) {
    Serial.println("connected to server");
    // Say I'm a Station:
    client.print("S");
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  b1 = digitalRead(6);
  digitalWrite(5, !b1);
  b2 = digitalRead(10);
  digitalWrite(9, !b2);
  b3 = digitalRead(12);
  digitalWrite(11, !b3);

  digitalWrite(13, b1 && b2 && b3);
  Serial.printf("B1: %d\tB2: %d\tB3: %d\n", b1, b2, b3);
  if(b1_prev != b1 || b2_prev != b2 || b3_prev != b3) {
    client.printf("%d%d%d", b1, b2, b3);
  }
  b1_prev = b1;
  b2_prev = b2;
  b3_prev = b3;
}
