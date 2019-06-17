#include <MFRC522.h>
  /*
  * Read a card using a mfrc522 reader on your SPI interface
  * Pin layout should be as follows (on Arduino Uno):
  * MOSI: D7 / ICSP-4
  * MISO: D6 / ICSP-1
  * SCK: D5 / ISCP-3
  * SS/SDA: D4
  * RST: Pin D2
  */
  #include <ESP8266WiFi.h>
  // include the library code:
  #include <LiquidCrystal.h>
  #include <SoftwareSerial.h>
  SoftwareSerial lcd(D1, D3);
  #include <SPI.h>
  //#include <RFID.h>
  #include <Servo.h>
  Servo myservo;
  
  #define SS_PIN D4
  #define RST_PIN D2
  MFRC522 mfrc522(SS_PIN, RST_PIN);
String uid="";
  //RFID rfid(SS_PIN,RST_PIN);
  WiFiClient client; 
  const char* ssid     = "vinnu";
  const char* password = "9059045255";

  String RoomKey = "1482920661";
  
  const char* host = "smartsecurityrfid.thesmartbridge.com";
  int serNum[5];
  
  int Card1_Status = 0 ;
  int Card2_Status = 0 ;
  int Card3_Status = 0 ;
  int Card_Status;
  
  String cancat_card = " ";
  String Card1 = "17,190,171,117";
  String Card2 = "249,229,12,10";
  String Card3 = "128,160,104,70";
  
  /* 
  int cards[][5] = {
     {192, 77, 169, 197, 225},
     {187, 181, 171, 117, 208},
     {133, 166, 122, 37, 124},
     {117, 151, 207, 101, 72},
     {212, 82, 149, 187, 168}
  };
   */
  int flag = 0 ;  
  bool access = false;

void setup() 
    {
              Serial.begin(115200);
              SPI.begin();
              mfrc522.PCD_Init();
            //  rfid.init();
              myservo.attach(D8);
              myservo.write(0);
              lcd.begin(9600);
              delay(1000);
              // We start by connecting to a WiFi network

              Serial.println();
              Serial.println();
              Serial.print("Connecting to ");
              Serial.println(ssid);
              WiFi.begin(ssid, password);
                
                      while (WiFi.status() != WL_CONNECTED)
                        {
                                delay(500);
                                Serial.print(".");
                        }
              
              Serial.println("");
              Serial.println("WiFi connected");  
              Serial.println("IP address: ");
              Serial.println(WiFi.localIP());

   
             }

void loop()
      {
       // ReadUid();
        uploadvalue();
           if(mfrc522.PICC_IsNewCardPresent()){
                              if(mfrc522.PICC_ReadCardSerial()){
                                       Serial.print(mfrc522.uid.uidByte[0]);
                                       Serial.print(" ");
                                       Serial.print(mfrc522.uid.uidByte[1]);
                                       Serial.print(" ");            
                                       Serial.print(mfrc522.uid.uidByte[2]);             
                                       Serial.print(" ");
                                       Serial.print(mfrc522.uid.uidByte[3]);
                                       Serial.println("");
                                       
                                        // Cancat String
                                      cancat_card = String(mfrc522.uid.uidByte[0])+","+String(mfrc522.uid.uidByte[1])+","+String(mfrc522.uid.uidByte[2])+","+String(mfrc522.uid.uidByte[3]);
                                      
                                         if(cancat_card == Card1)
                                           {
                                                access = true; 
                                                if(Card1_Status == 0)
                                            {
                                                 Card1_Status = 1 ;
                                                 Card_Status = Card1_Status ;
                                                 cancat_card ="17,190,171,117";
                                                 RoomKey = "1482920661";                                           
                                                 Serial.println("Card Id = "+cancat_card+" == Welcome == it is Card 1 ");
                                                 upload(cancat_card ,RoomKey,Card_Status );
                                                 //delay(1000);
                                                 myservo.write(180);
                                                 delay(3000);
                                                 myservo.write(0);
                                              }
                                              else
                                              {
                                                Card1_Status = 0 ;
                                                Card_Status = Card1_Status ;
                                                cancat_card ="17,190,171,117";
                                                RoomKey = "1482920661";
                                                Serial.println("Card Id = "+cancat_card+" == Bye == it is Card 1");
                                                upload(cancat_card ,RoomKey,Card_Status );
                                                myservo.write(180);
                                                delay(3000);
                                                myservo.write(0);
                                              }                                
                                           }
                                              else if(cancat_card == Card2)
                                              {
                                                access = true;
                                                if(Card2_Status == 0)
                                                {
                                                   Card2_Status = 1 ;
                                                   Card_Status = Card2_Status ;
                                                   cancat_card ="249,229,12,10";
                                                   RoomKey = "1482920661";
                                                   Serial.println("Card Id = "+cancat_card+" == Welcome == it is Card 2");
                                                   upload(cancat_card ,RoomKey,Card_Status );
                                                   //delay(1000);
                                                   myservo.write(180);
                                                   delay(3000);
                                                   myservo.write(0);
                                                }
                                                else
                                                {
                                                  Card2_Status = 0 ;
                                                  Card_Status = Card2_Status ;
                                                  cancat_card ="249,229,12,10";
                                                  RoomKey = "1482920661";
                                                  Serial.println("Card Id = "+cancat_card+" == Bye == it is Card 2");
                                                  upload(cancat_card ,RoomKey,Card_Status );
                                                   //delay(1000);
                                                  myservo.write(180);
                                                  delay(3000);
                                                  myservo.write(0);
                                                   
                                                }  
                                                          
                                              } 
                                              else if(cancat_card == Card3)
                                              {
                                                access = true;
                                                if(Card3_Status == 0)
                                                {
                                                   Card3_Status = 1 ;
                                                   Card_Status = Card3_Status ;
                                                   cancat_card ="128,160,104,70";
                                                   RoomKey = "1482920661";
                                                   Serial.println("ROOM 2");
                                                   Serial.println("Card Id = "+cancat_card+" == Welcome == it is Card 3");
                                                   upload(cancat_card ,RoomKey,Card_Status );
                                                  // delay(1000);
                                                   myservo.write(180);
                                                   delay(3000);
                                                   myservo.write(0);
                                                }
                                                else
                                                {
                                                  Card3_Status = 0 ;
                                                  Card_Status = Card3_Status ;
                                                  cancat_card ="128,160,104,70";
                                                  RoomKey = "1482920661";
                                                  Serial.println("Card Id = "+cancat_card+" == Bye == it is Card 3");
                                                  upload(cancat_card ,RoomKey,Card_Status );                                                 
                                                  myservo.write(180);
                                                  delay(3000);
                                                  myservo.write(0);
                                                }
                                                            
                                              }
                                              else
                                              {
                                                Serial.println("Cancat Id = "+cancat_card);
                                                Serial.println("=== Invalid Card ===");
                                                access = false;
                                                delay(1000);
                                                           
                                              }                
                                            }
          }
    getTalkBack();
//    rfid.halt();
    }

void upload( String cancat_card ,String RoomKey, int Card_Status )
       {
            Serial.print("connecting to ");
            Serial.println(host);
  
            // Use WiFiClient class to create TCP connections 
            WiFiClient client;
            const int httpPort = 80;
                 if (!client.connect(host, httpPort))
                    {
                       Serial.println("connection failed");
                        return;
                    }
            // We now create a URI for the request
            String url="&field1=";
            url += cancat_card;//card no
            url += "&field2=";
            url +=  "1482920661";//room no
            url += "&field3=";
            url += 0;//card status
          
             url="/API/access?"+url;
               if (client.connect("smartsecurityrfid.thesmartbridge.com", 80))
                  {
                    Serial.println("host connected");
                    Serial.println(url);
                    client.print("GET "+url+" HTTP/1.1\n");
                    client.print("Host: smartsecurityrfid.thesmartbridge.com\n");
                    client.print("Connection: close\n");
                    client.print("Content-Type: application/x-www-form-urlencoded\n");
                    client.print("Content-Length: ");
                    client.print(url.length());
                    client.print("\n\n");
                    client.print(url);
                    
                      if (client.find("@@"))
                      {
                         String Display = client.readStringUntil('\r');
                         Serial.println(Display);
                      }
                          delay(10);    
                          Serial.println();
                          Serial.println("closing connection");
                  }

    }

void getTalkBack()
   {
      String  tsData="/API/timeout";
      if (client.connect("smartsecurityrfid.thesmartbridge.com", 80)) 
          {
              Serial.println("connected");
              client.print("GET "+tsData+" HTTP/1.1\n");
              client.print("Host: smartsecurityrfid.thesmartbridge.com\n");
              client.print("Connection: close\n");
              client.print("Content-Type: application/x-www-form-urlencoded\n");
              client.print("Content-Length: ");
              client.print(tsData.length());
              client.print("\n\n");
              client.print(tsData);
                 if(client.find("@@"))
                     {
                        String Display = client.readStringUntil('\r');
                        Serial.println(Display);
                        lcd.println(Display);
                        lcd.println();
                      }
          }
    }

void uploadvalue()
       {
            Serial.print("connecting to ");
            Serial.println(host);
  
            // Use WiFiClient class to create TCP connections 
            WiFiClient client;
            const int httpPort = 80;
                 if (!client.connect(host, httpPort))
                    {
                       Serial.println("connection failed");
                        return;
                    }
            // We now create a URI for the request
            String url="&field1=";
            url += uid;
            url += 0;//card status
          
             url="/API/access?"+url;
               if (client.connect("smartsecurityrfid.thesmartbridge.com", 80))
                  {
                    Serial.println("host connected");
                    Serial.println(url);
                    client.print("GET "+url+" HTTP/1.1\n");
                    client.print("Host: smartsecurityrfid.thesmartbridge.com\n");
                    client.print("Connection: close\n");
                    client.print("Content-Type: application/x-www-form-urlencoded\n");
                    client.print("Content-Length: ");
                    client.print(url.length());
                    client.print("\n\n");
                    client.print(url);
                    
                      if (client.find("@@"))
                      {
                         String Display = client.readStringUntil('\r');
                         Serial.println(Display);
                      }
                          delay(10);    
                          Serial.println();
                          Serial.println("closing connection");
                  }

    }
