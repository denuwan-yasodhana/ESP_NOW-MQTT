#include <esp_now.h>
#include <WiFi.h>


// Structure to receive data from slave nodes
typedef struct {
  float temperature;
  float humidity;
  bool alert;
} DataPacket;

DataPacket incomingPacket;

// Array to store MAC addresses of slaves
const uint8_t slave1MAC[] = {0x08, 0xB6, 0x1F, 0x28, 0x74, 0xB4};  // Replace with actual MAC of Slave 1
const uint8_t slave2MAC[] = {0xE0, 0x5A, 0x1B, 0x5F, 0x62, 0xD0};  // Replace with actual MAC of Slave 2
// Add more slave MAC addresses as needed

void setup() 
{
  Serial.begin(115200);

  // Set up ESP-NOW
  WiFi.mode(WIFI_STA);  // ESP-Now requires station mode
  if (esp_now_init() != ESP_OK) 
  {
    Serial.println("ESP-Now initialization failed!");
    return;
  }

  // Register receive callback(this will be called whenever data is received from a slave node)
  esp_now_register_recv_cb(onDataReceived);

  Serial.println("Master node ready.");
}

void loop() 
{
  // ESP-NOW master node works event-driven. So,
  // The callback (onDataReceived) is triggered automatically when data is received, so there’s no need for continuous polling in loop().
}

// Callback for received ESP-NOW data
void onDataReceived(const esp_now_recv_info* recvInfo, const uint8_t *incomingData, int len) 
{
  memcpy(&incomingPacket, incomingData, sizeof(incomingPacket)); // copies the raw incoming data into the incomingPacket structure

  String sender = identifySender(recvInfo->src_addr); // contains the MAC address of the sender
  Serial.printf("Received Data from %s: Temp = %.1f%°C, Humidity = %.1f%%, Alert = %s\n", sender.c_str(), incomingPacket.temperature, incomingPacket.humidity, incomingPacket.alert ? "YES" : "NO");
}

// Identify which slave sent the data based on MAC address
// Compares the sender's MAC address (mac) with the stored MAC addresses of the slaves (slave1MAC and slave2MAC) using memcmp()
String identifySender(const uint8_t *mac) 
{
  if (memcmp(mac, slave1MAC, 6) == 0) 
  {
    return "Slave1";
  } 
  else if (memcmp(mac, slave2MAC, 6) == 0) 
  {
    return "Slave2";
  } 
  else 
  {
    return "Unknown Slave";
  }
}
