#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include "DHT.h"
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

#define LED_PIN 2

// Device ID
#define DEVICE_UID "1X"

// Your WiFi credentials
#define WIFI_SSID "YES4"
#define WIFI_PASSWORD "haha2021a"

// Your Firebase Project Web API Key
#define API_KEY "AIzaSyBD4DRtVqGypWQcF8L4dYgkmQW0oM1rx80"
// Your Firebase Realtime database URL
#define DATABASE_URL "https://esp32-projects-6132f-default-rtdb.asia-southeast1.firebasedatabase.app"

// Digital pin connected to the DHT sensor
#define DHTPIN 4
#define DHTTYPE DHT11
// Initialise DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Variables to hold sensor readings
float temperature = 0;
float humidity = 0;
// JSON object to hold updated sensor values to be sent to be firebase
FirebaseJson temperature_json;
FirebaseJson humidity_json;

// Device Location config
String device_location = "Bilik";
// Firebase Realtime Database Object
FirebaseData fbdo;
// Firebase Authentication Object
FirebaseAuth auth;
// Firebase configuration Object
FirebaseConfig config;
// Firebase database path
String databasePath = "";
// Firebase Unique Identifier
String fuid = "";
// Stores the elapsed time from device start up
unsigned long elapsedMillis = 0;
// The frequency of sensor updates to firebase, set to 10seconds
unsigned long update_interval = 4000;
// Dummy counter to test initial firebase updates
int count = 0;
// Store device authentication status
bool isAuthenticated = false;

// NTP Clock
const char *ntpServer = "pool.ntp.org";
const long gmtOffset = 28800; //seconds
const int daylightOffset = 0; //seconds

void Wifi_Init()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void firebase_init()
{
  // configure firebase API Key
  config.api_key = API_KEY;
  // configure firebase realtime database url
  config.database_url = DATABASE_URL;
  // Enable WiFi reconnection
  Firebase.reconnectWiFi(true);
  Serial.println("------------------------------------");
  Serial.println("Sign up new user...");
  // Sign in to firebase Anonymously
  if (Firebase.signUp(&config, &auth, "", ""))
  {
    Serial.println("Success");
    isAuthenticated = true;
    // Set the database path where updates will be loaded for this device
    databasePath = "/" + device_location;
    fuid = auth.token.uid.c_str();
  }
  else
  {
    Serial.printf("Failed, %s\n", config.signer.signupError.message.c_str());
    isAuthenticated = false;
  }
  // Assign the callback function for the long running token generation task, see addons/TokenHelper.h
  config.token_status_callback = tokenStatusCallback;
  // Initialise the firebase library
  Firebase.begin(&config, &auth);
}

String getCurrentTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    return "Failed to obtain time";
  }
  char timeStringBuff[50]; //50 chars should be enough
  strftime(timeStringBuff, sizeof(timeStringBuff), "%a, %B %d %Y %H:%M:%S", &timeinfo);
  //print like "const char*"
  Serial.println(timeStringBuff);

  //Optional: Construct String object
  return String(timeStringBuff);
}

void setup()
{
  // Initialise serial communication for local diagnostics
  Serial.begin(9600);
  // Initialise Connection with location WiFi
  Wifi_Init();
  // Initialise firebase configuration and signup anonymously
  firebase_init();

  pinMode(LED_PIN, OUTPUT);
  configTime(gmtOffset, daylightOffset, ntpServer);

  // Initialise DHT library
  dht.begin();
  // Initialise temperature and humidity json data
  temperature_json.add("deviceuid", DEVICE_UID);
  temperature_json.add("name", "DHT11-Temp");
  temperature_json.add("type", "Temperature");
  temperature_json.add("updated", getCurrentTime());
  temperature_json.add("location", device_location);
  temperature_json.add("value", temperature);
  // Print out initial temperature values
  String jsonStr;
  temperature_json.toString(jsonStr, true);
  Serial.println(jsonStr);
  humidity_json.add("deviceuid", DEVICE_UID);
  humidity_json.add("name", "DHT11-Hum");
  humidity_json.add("type", "Humidity");
  humidity_json.add("updated", getCurrentTime());
  humidity_json.add("location", device_location);
  humidity_json.add("value", humidity);
  // Print out initial humidity values
  String jsonStr2;
  humidity_json.toString(jsonStr2, true);
  Serial.println(jsonStr2);
}

void updateSensorReadings()
{
  Serial.println("------------------------------------");
  Serial.println("Reading Sensor data ...");
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.printf("Temperature reading: %.2f \n", temperature);
  Serial.printf("Humidity reading: %.2f \n", humidity);
  temperature_json.set("value", temperature);
  temperature_json.set("updated", getCurrentTime());
  humidity_json.set("value", humidity);
  humidity_json.set("updated", getCurrentTime());
}

void uploadSensorData()
{
  if (millis() - elapsedMillis > update_interval && isAuthenticated && Firebase.ready())
  {
    digitalWrite(LED_PIN, HIGH);
    elapsedMillis = millis();
    updateSensorReadings();
    String temperature_node = databasePath + "/temperature";
    String humidity_node = databasePath + "/humidity";
    if (Firebase.setJSON(fbdo, temperature_node.c_str(), temperature_json))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
      Serial.println("ETag: " + fbdo.ETag());
      Serial.print("VALUE: ");
      printResult(fbdo); //see addons/RTDBHelper.h
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
    if (Firebase.setJSON(fbdo, humidity_node.c_str(), humidity_json))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
      Serial.println("ETag: " + fbdo.ETag());
      Serial.print("VALUE: ");
      printResult(fbdo); //see addons/RTDBHelper.h
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }
  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  uploadSensorData();
}