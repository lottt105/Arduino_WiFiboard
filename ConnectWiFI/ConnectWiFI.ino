
#include <ESP8266WiFi.h>
#include <WiFiManager.h>

char ip[20];
char gateway[20];
char subnet_mask[20];
char host[30];
char url[30];
char port[10];
char id[10] ;
void setup() {
  // put your setup code here, to run once:
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
wifiManager.autoConnect("ESP");
if(!wifiManager.autoConnect("ESP"))
{
  Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
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
}

void loop() {
  // put your main code here, to run repeatedly:

}
