//Hardware: Arduino WEMOS WiFi D1
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
IPAddress apIP(192, 168, 1, 99);
// SKETCH BEGIN
ESP8266WebServer server(80);
// create a AP host 
const char* ssid = "ESPWebServer";
const char* password = "12345678";
// HTML code here (compressed)
String html = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0, minimum-scale=0.5, maximum-scale=2.0, user-scalable=yes' /><meta http-equiv='X-UA-Compatible' content='ie=edge'><title>Arduino</title><style>                .tabs {            width: 360px;            margin: 0px auto;                     background-color: LightCyan;            border: 0px solid #FFF;            box-sizing: border-box;        }        .tabs nav {            height: 50px;            text-align: center;            line-height: 28px;            overflow: hidden;            background-color: DarkCyan;                    display: flex;            margin: -0.5px auto;        }        nav a {            display: block;                               width: 51.4px;            border-right: 0px solid #fff;            font-size:15px;            color: #FFFFFF;            text-decoration: none;        }        nav a:last-child {            border-right: none;        }        nav a.active {            background-color: DarkTurquoise ;        }        .cont {            overflow: hidden;            display: none;        }        .cont ol {            line-height: 20px;        }                h2,h1{line-height:1%;}        body {            margin: 0;            padding: 0;            background: LightCyan        }        .button1 {            width: 115px;            height: 115px;            text-align: center;            font-weight: 100;            color: darkcyan;            margin: 0 40px 35px 0;            position: relative;            border: 6px solid darkcyan;            background: LightCyan;            font-size: 20px;            border-radius: 15%;            outline:none;        }</style></head><body><div class='tabs'><section class='cont' id='Page1' style='display:block'><ol><center ></br><a href='./pin?light1=1'><button type='button' class='button1'>&#x5F00;&#x673A;</button></a><a href='./pin?light1=0'><button type='button' class='button1'>&#x5173;&#x673A;</button></a><a href='./pin?light2=1'><button type='button' class='button1'>LED ON</button></a><a href='./pin?light2=0'><button type='button' class='button1'>LED OFF</button></a></br></center></ol></section></div></body></html>";
void pin(){
            if (server.arg("light1")=="1"){digitalWrite(D2, LOW); server.send(200, "text/html", html);}   // PIN D2
       else if (server.arg("light1")=="0"){digitalWrite(D2, HIGH); server.send(200, "text/html", html);}  
            if (server.arg("light2")=="1"){digitalWrite(2, LOW); server.send(200, "text/html", html);}   // 8266 LED on
       else if (server.arg("light2")=="0"){digitalWrite(2, HIGH); server.send(200, "text/html", html);}  // 8266 LED off
  }
void handleRoot(){ server.send(200, "text/html", html);}
void setup()
{
  pinMode(2, OUTPUT); 
  pinMode(D2, OUTPUT); 
  digitalWrite(2, HIGH);
  digitalWrite(D2, HIGH);
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP(); 
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
  Serial.println();
  Serial.printf("\nConnecting to %s\nIP Address : %s\n", ssid, WiFi.localIP().toString().c_str()); 
  server.on("/", handleRoot);
  server.on("/pin", HTTP_GET, pin);
  server.begin();
}

void loop(){
  server.handleClient();
}
