// Required libraries
#include "ESP8266WiFi.h"
#include "ESP8266Ping.h"

// #include <NTPClient.h>
// #define NTP_OFFSET   60 * 60      // In seconds
// #define NTP_INTERVAL 60 * 1000    // In miliseconds
// #define NTP_ADDRESS  "europe.pool.ntp.org"

// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

// The Network SSID we want to connect to along with it's password
const char *ssid = "HomeK";
const char *password = "1818181881";

// The remote host that we will be PINGing
const char *remote_host = "www.google.com";

// Pin configuration for NodeMCU 1.0 v2
// D0: 16 | D2: 4 | D3: 0 | D5: 14 | D6: 12 |
// D1: 5 | D4: 2 | D7: 13 | D8: 15 | D9: 3 | D10: 1 |
const int ledRedPin = D3;
const int ledYellowPin = D2;
const int ledGreenPin = D1;
const int ledBluePin = D0;
const int ledWhitePin = D5;

// Flag to see if we have set the average time for the PING
int firstRun = 1;
// Index to keep track of our loop count
int timerIndex = 0;
// How many times we want to iterate through the loop before we want to check the PING again
int timerLoopCount = 120; // 240 loops at .250 seconds = 1 minute
// Controls the delay on the loop, inevitably also controlling how ofter we PING
const int loopDelay = 250;
// How many PING requests we want to send to our specified remote host
const int pingCounter = 10;

// Variables for making the output to the serial monitor look nice
// timeout index holds the number of iterations through the loop we've gone
int timeoutIndex = 0;
// Timeout indicates when we want to restart the line
const int timeout = 35;

// String and integer variations of the PING average time for easy display integration
String avg_time_ms;
int avg_time;

// Outputs a divider to the serial monitor for orginisation purposes
void serialDivider()
{
  // Serial Moniter output for trouble shooting purposes
  Serial.println("--------------------------------------");
}

// Turn's on all the LED's , then turns them off after a 1/4 of a second
// With the exception of the WHITE LED
void blinkLeds()
{
  // Turn on all the LED's
  digitalWrite(ledRedPin, HIGH);
  digitalWrite(ledYellowPin, HIGH);
  digitalWrite(ledGreenPin, HIGH);
  digitalWrite(ledBluePin, HIGH);
  // Delay a 1/4 of a second
  delay(250);
  // Turn off all the LED's
  digitalWrite(ledRedPin, LOW);
  digitalWrite(ledYellowPin, LOW);
  digitalWrite(ledGreenPin, LOW);
  digitalWrite(ledBluePin, LOW);
}

void setup()
{
  // Serial Moniter output for trouble shooting purposes
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledYellowPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
  pinMode(ledWhitePin, OUTPUT);
  // Serial Moniter output for trouble shooting purposes
  serialDivider();
  // Begin our serial monitering on 115200
  Serial.begin(115200);
  delay(10);

  // timeClient.begin();

  // Serial Moniter output for trouble shooting purposes
  Serial.println();
  serialDivider();
  Serial.print("Connecting to WiFi ");
  Serial.print(ssid);
  Serial.print(" With password: ");
  Serial.print(password);
  Serial.println();
  serialDivider();

  // Connect to the specified WiFi with the specified Password
  WiFi.begin(ssid, password);
  // Wait for the WiFi to connect
  while (WiFi.status() != WL_CONNECTED && timeoutIndex <= timeout)
  {
    // Blink the LED lights
    blinkLeds();

    // Serial Moniter output for trouble shooting purposes
    Serial.print(".");

    // Check to see if we've timed out
    if (timeoutIndex == timeout)
    {
      // Serial Moniter output for trouble shooting purposes
      Serial.println();
      // Reset our time out index
      timeoutIndex = 0;
    }
    // Increment our timeout counter
    timeoutIndex++;

    delay(250);
  }
  // Serial Moniter output for trouble shooting purposes
  Serial.println(".");
  serialDivider();
  Serial.println();
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Pinging host: ");
  Serial.println(remote_host);
  serialDivider();
}

void loop()
{
  delay(loopDelay);

  // If the timer index is not less than the timer loop count we know we have reached
  // the time where we want to PING again, or if it is the first run
  if (timerIndex >= timerLoopCount || firstRun == 1)
  {
    // Turn on the white LED
    digitalWrite(ledWhitePin, HIGH);

    // Check to see if there is an internet connection
    if (!Ping.ping(remote_host))
    {
      // Serial Moniter output for trouble shooting purposes
      Serial.println("Error: Internet condition Offline");
      // Blink the LED's
      blinkLeds();
      // Continue the loop from the top
      return;
    }

    // Disable the first run event flag
    firstRun = 0;
    // PING the specified remote host specified amount of times
    Ping.ping(remote_host, pingCounter);
    // Store the PING average time in String and Int for easy display integration.
    avg_time = Ping.averageTime();
    avg_time_ms = Ping.averageTime();

    // Turn off the white LED
    digitalWrite(ledWhitePin, LOW);

    // Reset the timer index
    timerIndex = 0;

    // Serial Moniter output for trouble shooting purposes
    Serial.println("Server Pinged");
    // Serial.println(timeClient.getFormattedTime());
    serialDivider();
  }

  if (avg_time <= 50) // If the PING is lower than or equal to 50
  {
    // Serial Moniter output for trouble shooting purposes
    Serial.print("Pingtime: ");
    Serial.print(avg_time_ms + " ms\n");
    Serial.println("Internet condition: Great");
    serialDivider();

    // Turn on the BLUE LED & turn off all other LEDs
    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledYellowPin, LOW);
    digitalWrite(ledGreenPin, LOW);
    digitalWrite(ledBluePin, HIGH);
  }
  else if (avg_time > 50 && avg_time < 100) // If the PING is greater than 50 & less than 100
  {
    // Serial Moniter output for trouble shooting purposes
    Serial.print("Pingtime :");
    Serial.print(avg_time_ms + " ms\n");
    Serial.println("Internet condition: Good");
    serialDivider();

    // Turn on the GREEN LED & turn off all other LEDs
    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledYellowPin, LOW);
    digitalWrite(ledGreenPin, HIGH);
    digitalWrite(ledBluePin, LOW);
  }
  else if (avg_time >= 100 && avg_time < 200) // If the PING is greater or equal to 100 & less than 200
  {
    // Serial Moniter output for trouble shooting purposes
    Serial.print("Pingtime :");
    Serial.print(avg_time_ms + " ms\n");
    Serial.println("Internet condition: Slow");
    serialDivider();

    // Turn on the BLUE LED & turn off all other LEDs
    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledYellowPin, HIGH);
    digitalWrite(ledGreenPin, LOW);
    digitalWrite(ledBluePin, LOW);
  }
  else if (avg_time >= 200) // If the PING is greater or equal to 200
  {
    // Serial Moniter output for trouble shooting purposes
    Serial.print("Pingtime :");
    Serial.print(avg_time_ms + " ms\n");
    Serial.println("Internet condition: Bad");
    serialDivider();

    // Turn on the RED LED & turn off all other LEDs
    digitalWrite(ledRedPin, HIGH);
    digitalWrite(ledYellowPin, LOW);
    digitalWrite(ledGreenPin, LOW);
    digitalWrite(ledBluePin, LOW);
  }
  // Increment our timer index by 1 since we've completed a single iteration
  timerIndex++;

  // timeClient.update();
}
