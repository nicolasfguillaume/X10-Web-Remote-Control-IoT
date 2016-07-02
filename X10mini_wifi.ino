/*  Inspired by: EasyloT sketch tweeked by Barnabybear - original @
 *  http://iot-playground.com/2-uncategorised/40-esp8266-wifi-relay-switch-arduino-ide
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request.
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include "X10RF.h"
#include <ESP8266WiFi.h>


//#define LED LED_BUILTIN
#define X10 5
X10RF moduleX10RF(X10);


// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(8001);
const char* ssid = "***************";
const char* password = "*******************";

// Static address. Update these with values suitable for your network.
IPAddress ip(192,168,1,68);         // Node static local IP
IPAddress gateway(192,168,1,254);   // your router local address
IPAddress subnet(255,255,255,0);    // subnet mask

String state1 = "UNKNOWN";
String state2 = "UNKNOWN";
String state4 = "UNKNOWN";

void setup() {

  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  //pinMode(2, OUTPUT);
  //digitalWrite(2, 1);  // turn LED off

  // prepare GPIO5 FOR X10
  pinMode(X10, OUTPUT);    
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);   // used if static address
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.print("Server started @ ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  // Blink the LED
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(500);                      
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH           
}


void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    delay(100);
    return;
  }
   
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int val;
  /////////// device 1////////////////
  if (req.indexOf("/a/1/off") != -1)
    val = 10;
  else if (req.indexOf("/a/1/on") != -1)
    val = 11;
  else if (req.indexOf("/a/1/bright") != -1)
   val = 12;  //(!digitalRead(X10)); 
  else if (req.indexOf("/a/1/dim") != -1)
   val = 13;  //(digitalRead(X10));
   //////////// device 2///////////////
  else if (req.indexOf("/a/2/off") != -1)
    val = 20;
  else if (req.indexOf("/a/2/on") != -1)
    val = 21;
  else if (req.indexOf("/a/2/bright") != -1)
   val = 22; 
  else if (req.indexOf("/a/2/dim") != -1)
   val = 23;
  //////////// device 4///////////////
  else if (req.indexOf("/a/4/off") != -1)
    val = 40;
  else if (req.indexOf("/a/4/on") != -1)
    val = 41;
  else if (req.indexOf("/a/4/bright") != -1)
   val = 42; 
  else if (req.indexOf("/a/4/dim") != -1)
   val = 43;
  //////////// homepage///////////////
  else if (req.indexOf("/") != -1)
   val = 0;
  else {
    Serial.println("Invalid Request");
    client.print("HTTP/1.1 404\r\n");
    client.stop();
    return;
  }

  // Set GPIO5 (X10) according to the request
  /////////////// device 1 ////////////////
  if (val == 11)
        {moduleX10RF.x10_sendcmd('A', 1, ON) ; state1 = "ON";}
  else if (val == 10)
        { moduleX10RF.x10_sendcmd('A', 1, OFF) ; state1 = "OFF";}
  else if (val == 12)
        { moduleX10RF.x10_sendcmd('A', 1, BRIGHT) ; state1 = "ON";}
  else if (val == 13)
        { moduleX10RF.x10_sendcmd('A', 1, DIM) ; state1 = "ON";}
   ////////////// device 2 ////////////////
  else if (val == 21)
        { moduleX10RF.x10_sendcmd('A', 2, ON) ; state2 = "ON";}
  else if (val == 20)
        { moduleX10RF.x10_sendcmd('A', 2, OFF) ; state2 = "OFF";}
  else if (val == 22) 
        { moduleX10RF.x10_sendcmd('A', 2, BRIGHT) ; state2 = "ON";}
  else if (val == 23) 
        { moduleX10RF.x10_sendcmd('A', 2, DIM) ; state2 = "ON";}
   ////////////// device 4 /////////////////
  else if (val == 41)
        { moduleX10RF.x10_sendcmd('A', 4, ON) ; state4 = "ON";}
  else if (val == 40)
        { moduleX10RF.x10_sendcmd('A', 4, OFF) ; state4 = "OFF";}
  else if (val == 42) 
        { moduleX10RF.x10_sendcmd('A', 4, BRIGHT) ; state4 = "ON";}
  else if (val == 43) 
        { moduleX10RF.x10_sendcmd('A', 4, DIM) ; state4 = "ON";}
  
  client.flush();

  // Prepare the response (= HTML page)
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n ";

  s += "<head><title>NodeMCU Web Server (Beta)</title></head>";
  
  s += "<body style=\"font-family:\'Georgia\'; background-image: url(\'http://stockfresh.com/files/k/karenr/m/86/6303549_stock-photo-teal-white-and-gray-polka-dot-tile-pattern-repeat-background.jpg\');\">";

  s += "<div style=\'background-color:lightcyan; color:black; text-align:center; padding:10px; margin:40px;\'>";
  s += "<center><h1>NodeMCU Web Server (Beta)</h1>";
  s += "<img src=\"https://cdn4.iconfinder.com/data/icons/vecico-connectivity/288/wifi_Logo-128.png\"></center>";
  s += "</div>";

  s += "<div style=\'background-color:lightcyan; color:black; text-align:center; padding:10px; margin:40px;\'>";
  s += "<h1>Device 1<br>";
  s += "<a href=\"/a/1/on\">ON</a> | ";      
  s += "<a href=\"/a/1/off\">OFF</a><br>";   
  s += "</h1>";  
  s += "<h3>Description: Plafonnier<br>";  
  s += "Max Power: 175 W<br>";  
  s += "State: " + state1 + "</h3>";  
  s += "</div>";

  s += "<div style=\'background-color:lightcyan; color:black; text-align:center; padding:10px; margin:40px;\'>";
  s += "<h1>Device 2<br>";
  s += "<a href=\"/a/2/on\">ON</a> | ";      
  s += "<a href=\"/a/2/off\">OFF</a> | ";  
  s += "<a href=\"/a/2/bright\">UP</a> | ";  
  s += "<a href=\"/a/2/dim\">DOWN</a><br>";   
  s += "</h1>";  
  s += "<h3>Description: Table de nuit<br>";  
  s += "Max Power: 180 W<br>";  
  s += "State: " + state2 + "</h3>";  
  s += "</div>";

  s += "<div style=\'background-color:lightcyan; color:black; text-align:center; padding:10px; margin:40px;\'>";
  s += "<h1>Device 4<br>";
  s += "<a href=\"/a/4/on\">ON</a> | ";      
  s += "<a href=\"/a/4/off\">OFF</a> | ";  
  s += "<a href=\"/a/4/bright\">UP</a> | ";  
  s += "<a href=\"/a/4/dim\">DOWN</a><br>";   
  s += "</h1>";  
  s += "<h3>Description: Jardin<br>";  
  s += "Max Power: 150 W<br>";  
  s += "State: " + state4 + "</h3>";  
  s += "</div>";
  
  s += "</body></html>\n";

  // Send the response to the client
  client.print(s);
  delay(10);
  //Serial.println("Client disconnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
