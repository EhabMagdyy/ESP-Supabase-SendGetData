/*****************************************************************************************************************************
**********************************    Author  : Ehab Magdy Abdullah                      *************************************
**********************************    Linkedin: https://www.linkedin.com/in/ehabmagdyy/  *************************************
**********************************    Youtube : https://www.youtube.com/@EhabMagdyy      *************************************
******************************************************************************************************************************/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Wi-Fi credentials
#define SSID               "SSID"
#define PASSWORD           "PASSWORD"

// Supabase credentials
#define supabaseUrl       "supabaseUrl"
#define supabaseKey       "supabaseKey"
#define tableName         "tableName"

// potentiometer pin number
#define POTENTIOMETER_PIN  35

void setup()
{
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi\n");
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    // Create a JSON object with your data
    StaticJsonDocument<200> jsonDoc;
    // Reading Potentiometer value
    jsonDoc["potentiometer"] = analogRead(POTENTIOMETER_PIN);

    // Serialize JSON to a string
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    // Update an existing row | Send HTTP PATCH request to Supabase
    HTTPClient http;
    String endpoint = String(supabaseUrl) + "/rest/v1/" + tableName + "?id=eq.1"; // Update row with id=1
    http.begin(endpoint);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("apikey", supabaseKey);
    http.addHeader("Authorization", "Bearer " + String(supabaseKey));
    // Optional: Return the updated row
    http.addHeader("Prefer", "return=representation");

    // Update the specified row
    int httpResponseCode = http.PATCH(jsonString);
    if (httpResponseCode > 0)
    {
      Serial.println("Transmitting:");
      String response = http.getString();
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Response: " + response);

      // Receiving Data
      getData();
    }
    else
    {
      Serial.println("Error in HTTP request");
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      String response = http.getString();
      Serial.println("Response: " + response);
    }
    http.end();
  }
  else
  {
    while(!WiFi.reconnect())
    {
      Serial.println("Reconnecting to WiFi...");
      delay(500);
    }
    Serial.println("Connected");
  }

  // Wait 5 Seconds
  delay(5000);
}

void getData()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    String endpoint = String(supabaseUrl) + "/rest/v1/" + tableName + "?id=eq.1&select=potentiometer,updated_at";
    http.begin(endpoint);
    http.addHeader("apikey", supabaseKey);
    http.addHeader("Authorization", "Bearer " + String(supabaseKey));

    int httpResponseCode = http.GET();
    if (httpResponseCode > 0)
    {
      Serial.println("\nReceiving:");
      String response = http.getString();
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    }
    else
    {
      Serial.println("Error in HTTP request");
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      String response = http.getString();
      Serial.println("Response: " + response);
    }
    
    http.end();
    Serial.println("\n============================================\n");
  }
  else
  {
    while(!WiFi.reconnect())
    {
      Serial.println("Reconnecting to WiFi...");
      delay(500);
    }
    Serial.println("Connected");
  }
}
