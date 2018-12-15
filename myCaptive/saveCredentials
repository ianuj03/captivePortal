int addCredential(String ssid, String pswd){
    /*
     * Here, at position 100 the number of credentials are stored;
     */
    int credentialCount=0;
    int nextSpace=101;//getCredentials();
    
//    bool flag=0;
//    for(int i=0;i<credentialCount;i++){
//        if(ssid==credentials[i][0] && pswd==credentials[i][1])
//            flag=1;
//    }
    
//    if(flag==0){
        
        EEPROM.write(nextSpace,ssid.length());
        nextSpace+=1;
        for(byte i=0;i<ssid.length();i++)
            EEPROM.write(nextSpace+i,int(ssid.charAt(i)));
        
        nextSpace+=ssid.length();
        EEPROM.write(nextSpace,pswd.length());
        nextSpace+=1;
        for(byte i=0;i<pswd.length();i++)
            EEPROM.write(nextSpace+i,int(pswd.charAt(i)));
        
        credentialCount+=1;
        EEPROM.write(100,credentialCount);
        EEPROM.commit();
        return 1;
//    }
//    return 0;
}

int getCredentials(){
    credentialCount=EEPROM.read(100);
    int nextSpace=101;
    
    for(int i=0;i<credentialCount;i++){
        credentials[i][0]="";
        int ssidLength=EEPROM.read(nextSpace);
        for(byte j=1;j<=ssidLength;j++)
            credentials[i][0]+=char(EEPROM.read(nextSpace+j));
        nextSpace+=ssidLength+1;
        
        credentials[i][1]="";
        int pswdLength=EEPROM.read(nextSpace);
        for(byte j=1;j<=pswdLength;j++)
            credentials[i][1]+=char(EEPROM.read(nextSpace+j));
        nextSpace+=pswdLength+1;
    }
    
    return nextSpace;
}


