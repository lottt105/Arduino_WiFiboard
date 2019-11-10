
#include <Firebase.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>

char ip[20];
char gateway[20];
char subnet_mask[20];
char host[30];
char url[30];
char port[10];
char id[10] ;

const int trig = 5;     // chân trig của HC-SR04
const int echo = 4;     // chân echo của HC-SR04
#include <FirebaseArduino.h>

#define FIREBASE_HOST "sokjeonsokgyul.firebaseio.com"




void setup() {

  pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
    pinMode(13, OUTPUT);
    
  Serial.begin(115200);
  Serial.println();

  Serial.print("Connecting to Wi-Fi");
  
  IPAddress IP,Gateway, Subnet_mask;

  WiFiManagerParameter custom_ip("ip", "IP", ip, 20);
  WiFiManagerParameter custom_gateway("gw", "GATEWAY", gateway, 10);
  WiFiManagerParameter custom_subnet_mask("sn", "SUBNET MASK",subnet_mask,10);
  WiFiManagerParameter custom_host("host", "HOST",host,100);
  WiFiManagerParameter custom_url("url", "URL",url,100);
  WiFiManagerParameter custom_port("port","PORT",port,10);
  WiFiManagerParameter custom_id("id", "ID",id,10);
  
  WiFiManager wifiManager;
  
  wifiManager.setConfigPortalTimeout(60);
  wifiManager.addParameter(&custom_ip);
  wifiManager.addParameter(&custom_gateway);
  wifiManager.addParameter(&custom_subnet_mask);
  wifiManager.addParameter(&custom_host);
  wifiManager.addParameter(&custom_url);
  wifiManager.addParameter(&custom_port);
  wifiManager.addParameter(&custom_id);
  
wifiManager.resetSettings();
wifiManager.autoConnect("we love soksok");
if(!wifiManager.autoConnect("we love soksok"))
{
  Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep W223sleep
    ESP.reset();
}
 Serial.println("connected...");
   IP.fromString(ip);
   Gateway.fromString(gateway);
   Subnet_mask.fromString(subnet_mask);
 //cauhinh
   wifiManager.setSTAStaticIPConfig(IP,Gateway,Subnet_mask); 
   
  strcpy( ip, custom_ip.getValue());
  strcpy( gateway, custom_gateway.getValue());
  strcpy( subnet_mask, custom_subnet_mask.getValue());
  strcpy( host, custom_host.getValue());
  strcpy( url, custom_url.getValue());
  strcpy( port, custom_port.getValue());
  strcpy( id, custom_id.getValue());
  // put your setup code here, to run once:

Firebase.begin(FIREBASE_HOST);
 
int n=0;
   
}

void loop() {

   unsigned long duration; // biến đo thời gian
    int distance;           // biến lưu khoảng cách
    
    /* Phát xung từ chân trig */
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);

    
    Firebase.pushFloat("logs1", distance);
  // handle error
  if (Firebase.failed()) {
      Serial.println("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs1/");
  
  Firebase.setFloat("logs", distance);
  // handle error
  if (Firebase.failed()) {
      Serial.println("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  //get value 
 int  n = Firebase.getInt("LED_STATUS");
   if(n==1){
      digitalWrite(13,1);
      Serial.println("LED ON");
   }
    else{
        digitalWrite(13,0);
        Serial.println("LED OFF");
    }

}
