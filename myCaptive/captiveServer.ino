/*
 * NodeMCU server
 * Author:ianuj03
 * Date:Dec 4,2018
 */

void submit(){
    /*
     * Function to verify the SSID and password
     */
    if (server.args()==2) {
        String ssidNew=server.arg("ssid");
        if(ssidNew!=""){
            ssidNew+='x';
            String pswdNew=server.arg("pswd")+'x';
            char name[ssidNew.length()];
            ssidNew.toCharArray(name,ssidNew.length());
            char pswd[pswdNew.length()];
            pswdNew.toCharArray(pswd,pswdNew.length());
            
            Serial.printf("%s trying to connect",ssidNew);
            
            WiFi.begin(name,pswd);
            
            long connectTime=millis();
            while(WiFi.status()!=WL_CONNECTED){
                if(millis()-connectTime>5000)
                    break;
                yield();
            }
            if(WiFi.status()!=WL_CONNECTED){
                server.send(200,"plain/text","not connected");
                Serial.println("Not Connected");
                flag=1;
            }
            else{
                addCredential(name,pswd);
                server.send(200,"text/plain","connected");
                getCredentials();
                Serial.println("WiFI Connected");
                WiFi.mode(WIFI_STA);
                flag=0;
            }
        }
    }
    if(WiFi.status()!=WL_CONNECTED)
        server.send(200,"text/html",makeForm());
}

void mainServer(){
    Serial.println("new connection");
    server.send(200,"text/html",makeForm());
}

void myServer(){
    flag=1;

    const char* ssid = "Shaktimaan";
    const char* password = "AnimationSucks";
    WiFi.persistent( false );
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(ssid, password);
    
    dnsServer.start(DNS_PORT,"*",local_IP);
    MDNS.begin("shaktimaan");
     
    server.onNotFound([](){
        server.send(200,"text/html",makeForm());
    });
    server.on("/",mainServer);
    server.on("/submit", submit);
    
    server.begin();                  //Start server
    
    IPAddress myIP = WiFi.softAPIP(); //Get IP address
    Serial.print("HotSpt IP:");
    Serial.println(myIP);
}
