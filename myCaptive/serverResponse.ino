String head=R"===(
        <!DOCTYPE html>
        <html lang="en">
        <head>
        <title>Shaktimaan Setup</title>

        <meta charset='utf-8'>
        <meta name='viewport' content='width=device-width, initial-scale=1'>
        
        <style>
            body {
                margin-top: 100px;
                font: 400 15px Lato, sans-serif; 
                font-family: Montserrat, sans-serif; 
                line-height: 1.8; 
                color: black; 
                background-color: #323232; 
            }
            .form-control {
                width: 100%;
                color:black;
            }
            .container {
                margin: 0 auto;
                max-width: 400px;
                padding: 30px;
                box-shadow: 0 10px 20px rgba(0,0,0,0.19), 0 6px 6px rgba(0,0,0,0.23);
                background-color: #ffffff;
            }
            h1 {
                text-align: center;
                margin-bottom: 40px;
                margin-top: 0px;
                color: #939393;
                font-size: 35px;
            }
            form .field-group {
                box-sizing: border-box;
                clear: both;
                padding: 4px 0;
                position: relative;
                margin: 1px 0;
                width: 100%;
            }
            input[type=text] {
                font-size: 15px;
                margin-bottom: 4%;
                -webkit-appearance: none;
                display: block;
                background: #fafafa;
                color: #636363;
                width: 100%;
                border: none;
                border-radius: 0;
                border-top: none;
                border-left: none;
                border-right: none;
                border-bottom: 1px solid #00bcd4;
                background-color: transparent;
            }
            input[type=text]:focus {
                border-color: #4C669F;
                outline: 0;
            }
            .button-container {
                box-sizing: border-box;
                clear: both;
                margin: 1px 0 0;
                padding: 4px 0;
                position: relative;
                width: 100%;
            }
            input[type=button] {
                background: #00bcd4;
                border: none;
                border-radius: 30px;
                color: #ffffff;
                cursor: pointer;
                display: block;
                font-weight: bold;
                font-size: 16px;
                padding: 15px 0;
                margin-top: 12%;
                text-align: center;
                text-transform: uppercase;
                width: 100%;
                -webkit-transition: background 250ms ease;
                -moz-transition: background 250ms ease;
                -o-transition: background 250ms ease;
                transition: background 250ms ease;
            }

        </style>
        </head>)===";

/*
 * ======================================================================================
 * ======================================================================================
 * ======================================================================================
 */

String body1=R"===(
    <body>
        <div class='container'>
            <h1 align='text-align:center'>Shaktimaan is hero</h1>
                <div class="field-group">
                  <select class="form-control" onchange="nextInput()" id="ssid">
                    <option value='default' checked>--Select network--</option>
                    )===";

                 
String body2=R"===( 
                        <option value='mannual'>Other...</option>
                    </select>
                </div>
                </br></br>
                <div class="field-group" id="ssidMannualDesign" hidden>
                    <input type="text" length=32 placeholder="SSID" id='ssidMannual'>
                </div>
                <div class="field-group" id="pswdDesign" hidden>
                    <input type="text" length=64 placeholder="Password" id='pswd'>
                </div>
                <div class="button-container" id='go' hidden>
                    <input type="button" onclick="connect()" value="Connect">
                </div>    
            <p id='message1'></p>
            </br>
        </div>

          <script>
                function nextInput(){
                    var id=document.getElementById('ssid').value;
                    if(id!="default"){
                        document.getElementById("pswdDesign").style.display="block";
                        document.getElementById("go").style.display="block";
                        if(id=="mannual"){
                            document.getElementById("ssidMannualDesign").style.display="block";
                        }
                        else{
                            document.getElementById("ssidMannualDesign").style.display="none";
                        }
                    }
                }
                function connect(){
                        var ssid1=document.getElementById("ssid").value;
                        if(ssid1=='mannual' || ssid1=="default"){
                                ssid1=document.getElementById("ssidMannual").value;
                        }
                        if(ssid1.length != 0){
                                var pswd=document.getElementById("pswd").value;
                                var xhttp = new XMLHttpRequest();
                                xhttp.onreadystatechange = function() {
                                        if (this.readyState == 4 && this.status == 200) {
                                                var response=this.responseText;
                                                if(response=="not connected"){
                                                    document.getElementById("message1").innerHTML="Unable to connect "+ssid1;
                                                }
                                                else if(response=="connected"){
                                                    document.getElementById("message1").innerHTML="Connected to "+ssid1;
                                                }
                                        }
                                };
                                xhttp.open('POST', '/submit', true);
                                xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
                                xhttp.send('ssid='+ssid1+'&pswd='+pswd);
                                document.getElementById('message1').innerHTML="Connecting to "+ssid1;

                        }
                }
        </script>
    </body>
    </html>)===";

String makeForm(){
    int networks=WiFi.scanNetworks();
    String ids="",name,temp,network;
    if(networks==0)
        network="<option value='None'>No Network Found</option>";
    else{
        for(int i=0;i<networks;i++){
            name=WiFi.SSID(i);
            temp="<"+name+">";
            
            if(ids.indexOf(temp)==-1){
                network+="<option value=\""+name+"\">"+name+"</option>";
                ids+=temp;    
            }
            
        }
    }
    String temp1=head+body1+network+body2;
    return temp1;
}
