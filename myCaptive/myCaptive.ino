/*
 * Sketch to make a captive portal;
 * with a button, which acts as a setup;
 * check out the README for more about the working.
 * Author:ianuj03
 * Date: Dec 4,2018
 */
 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include<ESP8266HTTPClient.h>
#include<EEPROM.h>

#define DNS_PORT 53
#define CONNECTED_LED D1

ESP8266WebServer server(80); //Server on port 80
DNSServer dnsServer;

String host="http://192.168.1.11:7001";

WiFiClient client;
HTTPClient web;

int flag=0;
int flagCheck=0;

long prevTime=0;

String credentials[10][2];
int credentialCount=0;

String makeForm();

IPAddress local_IP(192,168,14,23);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

void callServer(){
    if(WiFi.status()==WL_CONNECTED)
        WiFi.disconnect();
    myServer();
}

void connectWIFI(){
    String ssidTemp=credentials[0][0]+'x';
    String pswdTemp=credentials[0][1]+'x';
    
    //Declearing the char Array
    char ssid1[ssidTemp.length()];
    char pswd[pswdTemp.length()];
    
    //Converting to char Array
    ssidTemp.toCharArray(ssid1,ssidTemp.length());
    pswdTemp.toCharArray(pswd,pswdTemp.length());

    WiFi.begin(ssid1,pswd);
    WiFi.setAutoReconnect (true);
    delay(500);
}

void setup(){
    Serial.begin(9600);
    EEPROM.begin(300);

    //LED to show the conneciton status
    pinMode(CONNECTED_LED,OUTPUT);

    //Attaching the button for setup mode
    pinMode(D8,INPUT);
    attachInterrupt(digitalPinToInterrupt(D8),callServer,HIGH);

    WiFi.mode(WIFI_STA);
    
    getCredentials();
    connectWIFI();
    prevTime=millis();
    delay(3000);
}

String response;

void loop(){
    if(flag==1 && WiFi.status()!=WL_CONNECTED){
        dnsServer.processNextRequest();
        server.handleClient();          //Handle client requests
    }
    else{
        if(WiFi.getMode()!=WIFI_STA){
            Serial.println("Mode changed");
            getCredentials();
            WiFi.mode(WIFI_STA);
        }
        if(WiFi.status()==WL_CONNECTED){
            for(byte i=1;i>-1;i--){
                digitalWrite(CONNECTED_LED,i);
                delay(1000);
            }
            
            /*
                String temp="/<data>";
                web.begin(host+temp);
                int httpCode=web.GET();
                if(httpCode>0){
                    response=web.getString();
                    Serial.println(response);
                    //Perform actions based on the response
                }
                else
                    Serial.println("Error Occured");  
                web.end();
            */
            
        }
        else{
            Serial.println("Not connected");
            if(abs(millis()-prevTime)>30000){
                connectWIFI();
                prevTime=millis();
            }
        }
    }
}
