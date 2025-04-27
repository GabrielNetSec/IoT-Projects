// Water Leak Detector for IoT (C++/Arduino Demo)
// Author: Gabriel Naranjo - GabrielNetSec
// Hardware: ESP32 + YF-S201 water flow sensor
// License: MIT

#include <WiFi.h>
#include "secrets.h"   // WiFi credentials

constexpr uint8_t SENSOR_PIN = 2;                 // GPIO for sensor input
constexpr unsigned long FLOW_TIMEOUT_MS = 2000;   // 2s: if no pulses, assume water is OFF

volatile long pulse = 0;                 // Pulse count (ISR)
volatile bool waterStatus = false;       // true = Water ON, false = OFF (ISR)
volatile unsigned long lastPulseTime = 0; // Last time a pulse was received (ISR)

WiFiServer server(80);                   // HTTP server on port 80

#define DEBUG 1
#if DEBUG
  #define LOG(x) Serial.println(x)
#else
  #define LOG(x)
#endif

/**
 * @brief Interrupt Service Routine - Called on each sensor pulse (water flow detected).
 */
void IRAM_ATTR increase() {
  pulse++;
  waterStatus = true;
  lastPulseTime = millis();
}

/**
 * @brief Arduino setup function. Initializes I/O, WiFi, and server.
 */
void setup() {
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), increase, RISING);

  LOG("");
  LOG("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  LOG("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

/**
 * @brief Main Arduino loop. Checks water status and handles web server client requests.
 */
void loop() {
  // Snapshot for thread safety when using volatile variables
  unsigned long lastPulseSnapshot;
  bool waterStatusSnapshot;
  long pulseSnapshot;

  noInterrupts();
  lastPulseSnapshot = lastPulseTime;
  waterStatusSnapshot = waterStatus;
  pulseSnapshot = pulse;
  interrupts();

  // Check if water stopped (no pulses in FLOW_TIMEOUT_MS)
  if (millis() - lastPulseSnapshot > FLOW_TIMEOUT_MS) {
    waterStatus = false;
    waterStatusSnapshot = false;
  }

  // Optional: Automatically reconnect WiFi if disconnected
  if (WiFi.status() != WL_CONNECTED) {
    LOG("WiFi disconnected, attempting reconnect...");
    WiFi.reconnect();
    delay(1000);
    return; // Skip rest of loop if reconnecting
  }

  WiFiClient client = server.available();
  if (client) {
    serveWebPage(client, pulseSnapshot, waterStatusSnapshot);
    client.stop();
    LOG("Client Disconnected.");
  }
}

/**
 * @brief Sends the current water status as an HTML web page.
 * @param client Reference to the connected WiFiClient.
 * @param pulseCount Number of pulses detected (for debug/statistics).
 * @param isOn Current water status (true = on, false = off).
 */
static void serveWebPage(WiFiClient &client, long pulseCount, bool isOn) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html\n");
  client.println("<!DOCTYPE html><html><head><meta charset='UTF-8'>"
                 "<meta http-equiv='refresh' content='30'>"
                 "<title>Water Leak Detector</title></head>");
  client.println("<body><h1>Water Leak Detector (C++/Arduino IoT)</h1>");
  client.printf("<p>Pulses detected: %ld</p>", pulseCount);
  client.printf("<p>Uptime: %lu seconds</p>", millis() / 1000);
  client.println("<h2>Status:</h2>");
  client.printf("<p style='font-size:28px;color:%s;'>%s</p>",
                isOn ? "green" : "red",
                isOn ? "On" : "Off");
  client.println("<p>This page refreshes every 30 seconds.</p>");
  client.println("</body></html>");
}
