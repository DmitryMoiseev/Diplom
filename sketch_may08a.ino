#include "DHT.h" 
#include <Wire.h> 
#include <SoftwareSerial.h> 
SoftwareSerial mySerial(52, 53); 

  #define DHTPIN 45 //DHT11 
  #define Voda_pin 37   // пин датчика воды
  #define button_pin 10   // пин кнопки 1
  #define button_pin222 11   // пин кнопки 2
  #define button_pin333 8   // пин кнопки 3
  #define button_pin444 9   // пин кнопки 4
  #define relay_pin 2    // пин реле 1
  #define relay_pin222 3    // пин реле 2
  #define relay_pin333 4   // пин реле 3
  #define relay_pin444 5    // пин реле 4 
  #define relay_pin555 7 //пин реле 5
  #define relay_pin666  6 // пин реле 6
  #define relay_pin777 12  // пин реле7
  #define relay_pin888  13 // пин реле 8
  #define gaz_pin A0 // MQ-4
  #define bip_pin 38  // пищалка

     int sensorValue = 0; //переменная для работы датчика газа
     int val; //переменная для модуля BT
     DHT dht(DHTPIN, DHT11); //инициируем датчик DHT 

       //реле 1
       
          boolean butt_flag = 0;      // флажок нажатия кнопки
          boolean butt;               // переменная, харнящая состояние кнопки
          boolean flag = 0;           // флажок режима
          unsigned long last_press;   // таймер для фильтра дребезга
       //реле 2
       
          boolean butt_flag222 = 0;   // флажок нажатия кнопки
          boolean butt222;            // переменная, харнящая состояние кнопки
          boolean flag222 = 0;        // флажок режима
          unsigned long last_press222;// таймер для фильтра дребезга
       //реле 3
       
          boolean butt_flag333 = 0;   // флажок нажатия кнопки
          boolean butt333;            // переменная, харнящая состояние кнопки
          boolean flag333 = 0;        // флажок режима
          unsigned long last_press333;// таймер для фильтра дребезга
       //реле 4
       
          boolean butt_flag444 = 0;   // флажок нажатия кнопки
          boolean butt444;            // переменная, харнящая состояние кнопки
          boolean flag444= 0;         // флажок режима
          unsigned long last_press444;// таймер для фильтра дребезга
       //реле 5
       
          boolean butt_flag555 = 0;   // флажок нажатия кнопки
          boolean butt555;            // переменная, харнящая состояние кнопки
          boolean flag555= 0;         // флажок режима
          unsigned long last_press555;// таймер для фильтра дребезга

void setup() 
    { 
        Serial.begin(9600);
        mySerial.begin(9600);
        dht.begin();
        
             pinMode(button_pin, INPUT_PULLUP);     
             pinMode(relay_pin, OUTPUT);           
             pinMode(button_pin222, INPUT_PULLUP); 
             pinMode(relay_pin222, OUTPUT);        
             pinMode(button_pin333, INPUT_PULLUP); 
             pinMode(relay_pin333, OUTPUT);        
             pinMode(button_pin444, INPUT_PULLUP); 
             pinMode(relay_pin444, OUTPUT);        
             pinMode(Voda_pin, INPUT_PULLUP);      
             pinMode(relay_pin555, OUTPUT);        
             pinMode(relay_pin888, OUTPUT);        
             pinMode(relay_pin666, OUTPUT);        
             pinMode(relay_pin777, OUTPUT);        
             pinMode(bip_pin, OUTPUT);             
             pinMode(52,INPUT);                    
             pinMode(53,OUTPUT);                   
            
          // Serial.println("MQ2 Test"); 
            
      }
      
void loop() 
      {
        
          //первое реле
          
           {
                butt = !digitalRead(button_pin);  
                if (butt == 1 && butt_flag == 0 && millis() - last_press > 100)   
              {
                butt_flag = 1;                    
                flag = !flag;                     
                last_press = millis();           
                digitalWrite(relay_pin, flag);    
              }
                if (butt == 0 && butt_flag == 1)   
                {
                   butt_flag = 0;                    
                }
            }
            
           //второе реле
           
             {
                butt222 = !digitalRead(button_pin222);  
                if (butt222 == 1 && butt_flag222 == 0 && millis() - last_press222 > 100)   
              {
                butt_flag222 = 1;                    
                flag222 = !flag222;                     
                last_press222 = millis();            
                digitalWrite(relay_pin222, flag222);    
              }
                if (butt222 == 0 && butt_flag222 == 1)   
                {
                   butt_flag222 = 0;                    
                }
               }
               
            //третье реле
            
              {
                butt333 = !digitalRead(button_pin333);  
                if (butt333 == 1 && butt_flag333 == 0 && millis() - last_press333 > 100)   
              {
                butt_flag333 = 1;                    
                flag333 = !flag333;                     
                last_press333 = millis();            
                digitalWrite(relay_pin333, flag333);    
              }
                if (butt333 == 0 && butt_flag333 == 1)  
                {
                   butt_flag333 = 0;                    
                }
               }
               
            //четвертое реле
            
              {
                butt444 = !digitalRead(button_pin444);  
                if (butt444 == 1 && butt_flag444 == 0 && millis() - last_press444 > 100)   
              {
                butt_flag444 = 1;                    
                flag444 = !flag444;                     
                last_press444 = millis();            
                digitalWrite(relay_pin444, flag444);    
              }
                if (butt444 == 0 && butt_flag444 == 1)   
                {
                   butt_flag444 = 0;                    
                }
               }
               
             //пятое реле
             
              {
                butt555 = !digitalRead(Voda_pin);  
                if (butt555 == 1 && butt_flag555 == 0 && millis() - last_press555 > 100)   
              {
                butt_flag555 = 1;                    
                flag555 = !flag555;                     
                last_press555 = millis();            
                digitalWrite(relay_pin555, flag555);    
              }
                if (butt555 == 0 && butt_flag555 == 1)   
                {
                   butt_flag555 = 0;                    
                }
               }
              {
          { 
               float h = dht.readHumidity(); 
               float t = dht.readTemperature(); 
               if (isnan(h) || isnan(t)) { 
          {
           }
           
           //Serial.println ("Ошибка при считывании информации"); 
           
           } 
            else 
           { 
            
           //Serial.print ("Влажность: "); 
           //Serial.print (h);  
           //Serial.print (" %\t"); 
           //Serial.print ("Температура: "); 
           //Serial.print (t); 
           //Serial.println (" *C"); 
           
           } 
           if (t > 32) 
           { 
           digitalWrite (relay_pin777, HIGH); 
           } 
           else //иначе 
           { 
           digitalWrite (relay_pin777, LOW); 
           } 
           if (t < 22) 
           { 
           digitalWrite (relay_pin666, HIGH); 
           } 
           else //иначе 
           { 
           digitalWrite (relay_pin666, LOW);  
           }  
           }
           }
           {
                 sensorValue = analogRead(gaz_pin); 
                 if (sensorValue >= 500) 
                 {
                 tone(bip_pin,350,250);  
                 }
                 else 
                 {
                 digitalWrite(bip_pin, LOW); 
                 }
              //Serial.print("MQ2 value= "); 
              //Serial.println(sensorValue); 
           }
              
           {
              if (mySerial.available())
           {
              int c = mySerial.read(); 
           {
              if (c == '8') 
           {
              digitalWrite(relay_pin888,HIGH);
              Serial.println("реле8 - ON");
           }
           }
           {
              if (c == 'i')
           {
              digitalWrite(relay_pin888,LOW);
              Serial.println("реле8 - OFF");
           }
           {
              if (c == '1')
           {
              digitalWrite(relay_pin,HIGH);
              Serial.println("реле1 - ON");
           }
           }
           {
              if (c == 'q')
           {
              digitalWrite(relay_pin,LOW);
              Serial.println("реле1 - OFF");
           }
           }
           {
              if (c == '2')
           {
              digitalWrite(relay_pin222,HIGH);
              Serial.println("реле2 - ON");
           }
           }
           {
              if (c == 'w')
           {
              digitalWrite(relay_pin222,LOW);
              Serial.println("реле2 - OFF");
           }
           }
           {
              if (c == '3')
           {
              digitalWrite(relay_pin333,HIGH);
              Serial.println("реле3 - ON");
           }
           }
           {
              if (c == 'e')
           {
              digitalWrite(relay_pin333,LOW);
              Serial.println("реле3 - OFF");
           }
           {
              if (c == '4')
           {
              digitalWrite(relay_pin444,HIGH);
              Serial.println("реле4 - ON");
           }
           }
           {
              if (c == 'r')
           {
              digitalWrite(relay_pin444,LOW);
              Serial.println("реле4 - OFF"); 
           }
           }
           }
           {
              if (c == '5') 
           {
              digitalWrite(relay_pin555,HIGH);
              Serial.println("реле5 - ON");
           }
           }
           {
              if (c == 't')
           {
              digitalWrite(relay_pin555,LOW);
              Serial.println("реле5 - OFF");
           }
       }
       
         }
        }
       }
      }
