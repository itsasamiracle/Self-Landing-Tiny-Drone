#include <Arduino.h>
#include "WiFi.h"


const char* ssid = "Samir's iPhone";
const char* password = "*****";
const int ledPin = LED_BUILTIN;

const char* html = R""""(
HTTP/1.1 200 OK
Content-type:text/html



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP 32 Controller</title>
    <style>

        .light-container {
            display: grid;
            grid-template-columns: repeat(2, 100px);
            gap: 20px;

        }
        .light {
            width: 100px;
            height: 100px;
            border-radius: 50%; /* Makes the box a perfect circle */
            background-color: #333; /* Dark gray default (off) state */
            margin-bottom: 20px;
            border: 2px solid #000;
            transition: background-color 0.3s ease; 
        }

        .light.is-red {
            background-color: #ff3333;
            box-shadow: 0 0 20px #ff3333;

        }

    </style>
</head>
<body>
    <h1> ESP 32 Controller</h1>
    <p>LED:
        <a href = "/led/on"><button>ON</button></a>
        <a href = "/led/off"><button>OFF</button></a>
    </p>

    <div class="light-container">
         <div id="statusLight1" class="light"></div>
          <div id="statusLight2" class="light"></div>
          <div id="statusLight3" class="light"></div>
          <div id="statusLight4" class="light"></div>

    </div>
   

    <button type="button" onclick="toggleLight('statusLight1')">Toggle Motor </button>
    <button type="button" onclick="toggleLight('statusLight2')">Toggle Motor 2</button>
     <button type="button" onclick="toggleLight('statusLight3')">Toggle Motor 3</button>
     <button type="button" onclick="toggleLight('statusLight4')">Toggle Motor 4</button>

     <button type="button" onclick="toggleAllLights()">Toggle All Motors</button>
    <button type="button" onclick="TurnOffAll()"> Turn Off All</button>
    <script>


          const lightList = ["statusLight1", "statusLight2", "statusLight3", "statusLight4"];
      
        async function setLight(index, on){
            try {
                const r = await fetch(`/set?light=${index + 1}&state=${on ? 1 : 0}`);
                if (!r.ok) throw new Error("HTTP " + r.status);
                document.getElementById(lightList[index]).classList.toggle('is-red', on);
            } 
            catch (err) {
                console.erro("Failed light #" + (index + 1), err );

            }

        }

        function isOn(index) {
            return document.getElementById(lightList[index].classList.contains("is-red"));

        }
      
        function toggleLight(id) {
            const index = lightList.indexOf(id);
            setLight(index, !isOn(index));

        }

        async function syncStatus() {
            try{
                const states = await (await fetch('/status')).json();
                states.forEach((s,i) => {
                    document.getElementById(lightList[i]).classList.toggle('is-red', s===1);


                });
            }
             catch (err) {
                console.error("status issue", err);
             }

        }
          function toggleLight(id) {
            document.getElementById(id).classList.toggle('is-red');
        }

        function toggleAllLights(){
            for (const s of lightList)
        {
                document.getElementById(s).classList.toggle('is-red');
        }
        }

        function TurnOffAll(){
            for (const s of lightList)
        {
            document.getElementById(s).classList.remove('is-red');
        }


        }

        syncStatus();
    </script>

</body>
</html>
)"""";

WiFiServer server(80);


const float VCC = 3.7;
const float HoveringTargetV = 1.0; // This needs to be calibrated
int HoveringDuty = round((HoveringTargetV / VCC) * 255);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("IP Adress: "):
  Serial.println(WiFi.localIP());

  server.begin();

}

void loop() {
  WiFiClient client = server.accept();
  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println(html);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        // Execute commands
        if (currentLine.endsWith("GET /led/on")) {
          digitalWrite(ledPin, LOW);
        }
        if (currentLine.endsWith("GET /led/off")) {
          digitalWrite(ledPin, HIGH);
        }
      }
    }
    client.stop();
  }
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

void HoverMode() {
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);

  analogWrite(5, HoveringDuty);
  analogWrite(4, HoveringDuty);
  analogWrite(3, HoveringDuty);
  analogWrite(2, HoveringDuty);


}


