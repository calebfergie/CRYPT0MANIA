//Crypt0Mania code by Calebfergie

/* thanks to ESP docs: fingerprint from github, wemos vid guy: http://educ8s.tv/arduino-esp8266-tutorial-first-look-at-the-wemos-d1-arduino-compatible-esp8266-wifi-board/, arduino examples: millis & MAC address*/

#include <ESP8266WiFi.h> //include wifi library

const int greenLedPin = D5; // the pin that the red LED is attached to
const int redLedPin = D6; // the pin that the green LED is attached to

//API and PWM variables
float API_val; //percentage value from website
float API_val_1000; //scaled up for int mapping to pwm
float percent_contraint = 4.0;
float API_val_constrain; //constrained between 0 and 4 or -4%
float pwmVal;
float modVal;
float multiplier;

//Timer Variables
float counter = 1;
long prior_millis = 0;
long interval = 20000;
unsigned long millis_t;

//Web variables

//Redacted wifi info
const char* ssid = "yourNeworkName";
const char* password = "UrNtwrkP55word";

const char* host = "api.coinmarketcap.com"; // remote server we will connect to
const char* fingerprint = "EF 9D 44 BA 1A 91 4C 42 06 B1 6A 25 71 26 58 61 BA DA FA B9"; // fingerprint of certificate as per website

WiFiClientSecure client;

//text parsing variables
String result, condensedResult;
String startingVal = "percent_change_1h";
int startingPoint, endingPoint;

void setup() {
 Serial.begin(115200); // initialize serial communications
 pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output so it can be turned off
 pinMode(greenLedPin, OUTPUT);
 pinMode(redLedPin, OUTPUT);
 delay(2000); //just wait a 2 secs
 connectToWifi();
 getAPIValues();
}

void loop() {
 unsigned long millis_t = millis(); //millis at the current time
 digitalWrite(LED_BUILTIN, HIGH); // on the WeMos this turns OFF the bright blue light on the board
 glowCrystal(); //illuminate and animate the crystal based on current api values
 if (millis_t - prior_millis > interval) { //every interval, do the following
 counter = 1; //reset the counter for the glow effect
 multiplier = (sin(counter) + 1) / 2.0; // redefine the multiplier value
 getAPIValues();
 //GET THE VALUES from the web - end value should be a pwmVal, a number between 0 and 1024
 prior_millis = millis_t;
 }
 consoleStats();
 counter = counter + 0.02; //bump up the counter for the multiplier
}

//function to see stats in the console
void consoleStats() {
 Serial.print("current time (seconds): ");
 Serial.print(millis_t / 1000);
 Serial.print(" | ");
 Serial.print("pwmVal: ");
 Serial.print(pwmVal);
 Serial.print(" | ");
 Serial.print("multiplier: ");
 Serial.print(multiplier);
 Serial.print(" | ");
 Serial.print("modVal: ");
 Serial.print(modVal);
 Serial.print(" | ");
 Serial.print("counter: ");
 Serial.println(counter);
}


void connectToWifi () {
 Serial.println();
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid); //print status to console
 WiFi.begin(ssid, password); //log in to the network
 while (WiFi.status() != WL_CONNECTED) { //print waiting
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("\nWiFi connected"); //print success
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP()); //print IP
 Serial.print("MAC address: ");
 Serial.println(WiFi.macAddress()); //print MAC address
}

void getAPIValues() //client function to send/receive GET request data. Mixed with another example from github
{
//Try to connect to the host
Serial.print("connecting to ");
Serial.println(host);
if (!client.connect(host, 443)) {
Serial.println("connection failed");
return;
}
//use a fingerprint to verify - not sure if this is necessary
if (client.verify(fingerprint, host)) {
Serial.println("certificate matches");
} else {
Serial.println("certificate doesn't match");
}
Serial.println("connected");
client.println("GET /v1/ticker/ethereum/ HTTP/1.1"); //GET request
client.println("Host: api.coinmarketcap.com");
client.println("Connection: close"); //close 1.1 persistent connection
client.println(); //end of get request
Serial.println("request sent"); // note to self

while (client.connected() && !client.available()) delay(1); //waits for data
while (client.connected() || client.available()) { //connected or data available
char c = client.read(); //gets byte from ethernet buffer
result = result + c;
deleteHttpHeader(); //thanks to wemos guy

}
startingPoint = result.indexOf(startingVal); //idenfity where our target data starts
condensedResult = result.substring(startingPoint + 21, startingPoint + 26); // get the characters needed (it is known to be 5)
API_val = condensedResult.toFloat(); // turn it into an float
Serial.print("Condensed Result (1 hour percentage change): ");
Serial.print(condensedResult);
Serial.print("| API_val: ");
Serial.println(API_val);
client.stop(); //stop client
}

//function used to delete header info from recieved data
void deleteHttpHeader()
{
 if (result.endsWith("Content-Type: text/plain"))
 {
 result = "";
 }

}

void glowCrystal() {
 multiplier = (sin(counter) + 1) / 2.0; // a sine wave value that goes between 0 and 1
 API_val_1000 = API_val*1000; // beef up the value for more precise mapping
 if (API_val_1000 > 0) { //if positive
 API_val_constrain = constrain(API_val_1000, 0, percent_contraint*1000); //constrain the value to the top percentage
 pwmVal = map(API_val_constrain, 0, percent_contraint*1000, 0, 1024);//map the value to a pwm with max of 1024 (wemos)
 modVal = pwmVal * multiplier; //modify the value to pulse via a sine wave
 analogWrite(redLedPin, 0); // keep the red LED off
 analogWrite(greenLedPin, modVal); //light up the green LED based on the value
 } else { // if negative
 API_val_constrain = constrain(API_val_1000, -1* percent_contraint*1000, 0);
 pwmVal = map(API_val_constrain, 0, -1*percent_contraint*1000, 0, 1024);
 modVal = pwmVal * multiplier;
 analogWrite(greenLedPin, 0); // keep the green LED off
 analogWrite(redLedPin, modVal); //light up the red LED based on the value
 }
}
