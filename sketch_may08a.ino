/*
Ethernet Web Server
Управление светодиодом при нажатии кнопки on/off (вводе разных URL адресов) в браузере

Адрес включения светодиода:
IP-АДРЕС - тот IP, полученный при запуске примера DhcpAdressPrinter

http://IP-АДРЕС/$1

Для того, чтобы выключить:
http://IP-АДРЕС/$2

*/

#include <SPI.h>             //библиотека для работы с SPI
#include <Ethernet.h>        //библиотека для работы с Ethernet 
boolean newInfo = 0;        //переменная для новой информации
//MAC адрес вашего Ethernet-модуля, если его у вас нет, введите любой
//или оставьте тот, что в примере
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };     

//указываем IP адрес
//будьте внимательны! IP адрес указывается тот, который вы получили запустив пример DhcpAdressPrinter
IPAddress ip(192 ,168 ,0 ,10 );    //пример МОЕГО IP адреса, вы вводите сюда СВОЙ

//инифиализация библиотеки Ethernet server library
EthernetServer server(80);

void setup()
{
                                              
 /* без строки "digitalWrite(Relay1, HIGH);" перед "pinMode" при включении
 * ардуины будет происходить кратковременное переключение реле,
 * а значит кратковременно подастся питание, что нам категорически
 * не надо!
 */
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
 
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); //инициализируем 2-9 пин как выход для светодиода   
  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT);  
  //запускаем сервер с указанными ранее MAC и вашим IP
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);
}

void loop()
{
  //принимаем данные, посылаемые клиентом
  EthernetClient client = server.available();
  if(client){                                       //если запрос оканчивается пустой строкой
  boolean currentLineIsBlank = true;                //ставим метку об окончании запроса (дословно: текущая линия чиста)
  while (client.connected()) {                      //пока есть соединение с клиентом
    if (client.available()) {                       //если клиент активен
      char c = client.read();                       //считываем посылаемую информацию в переменную "с"
                                                  
      if(newInfo && c == ' '){                      //если переменная новой информации = 1 и "с", в которой записан запрос, равен пустой строке
        newInfo = 0;                                //то обнуляем переменную поступления новой информации
      }
      
      if(c == '$'){                                 //если переменная "с", несущая отправленный нам запрос, содержит символ $ 
                                                    //(все новые запросы) - "$" подразумевает разделение получаемой информации (символов)
        newInfo = 1;                                //то пришла новая информация, ставим метку новой информации в 1
      }
      
      /************************************************************************************************
      Примечание:
      Символ $ используется как обычный символ, который разделяет 1 от 2
      На практике применяют символ &, который разделяет новые переменные от последующих
      Это использьуется, например, в GET-запросах, которые выглядят подобным образом:
      client.print("GET /controlbar/wp-content/data.php?uid=" + ID + "&type=" + type + "&value=" + value);
      как видите, знак & разделяет значение переменной - ID и переменную type     
      ***************************************************************************************************/
      
                                                     //Проверяем содержание URL - присутствует $1 или $2
      if(newInfo == 1){                              //если есть новая информация
          Serial.println(c);
          if(c == '1'){                              //и "с" содержит 1
          Serial.println("ON");
          digitalWrite(2, HIGH);                    //то вкл 1 реле
          }
          if(c == '2'){                              //если "с" содержит 2
          Serial.println("OFF");
          digitalWrite(2, LOW);                     //выкл 1 реле
          }    

          
          if(c == '3'){                              
          Serial.println("ON");                      //2 реле
          digitalWrite(3, HIGH);
           } 
          if (c == '4'){
             Serial.println("off");
            digitalWrite(3, LOW);
          }

      if(c == '5'){                              
          Serial.println("ON");
          digitalWrite(4, HIGH);                    //то вкл 3 реле
          }
          if(c == '6'){                              
          Serial.println("OFF");
          digitalWrite(4, LOW);                     //выкл 3 реле
          }  

          
          if(c == '7'){                              
          Serial.println("ON");
          digitalWrite(5, HIGH);                    //вкл 4 реле
          }
          if(c == '8'){                            
          Serial.println("OFF");
          digitalWrite(5, LOW);                     //выкл 4 реле
          }  

          if(c == '9'){                              
          Serial.println("ON");
          digitalWrite(6, HIGH);                    //то вкл 5 реле
          }
          if(c == '10'){                              
          Serial.println("OFF");
          digitalWrite(6, LOW);                     //выкл 5 реле
          }  

          if(c == '11'){                              
          Serial.println("ON");
          digitalWrite(7, HIGH);                    //то вкл 6 реле
          }
          if(c == '12'){                              
          Serial.println("OFF");
          digitalWrite(7, LOW);                     //выкл 6 реле
          }  

          if(c == '13'){                              
          Serial.println("ON");
          digitalWrite(8, HIGH);                    //то вкл 7 реле
          }
          if(c == '14'){                              
          Serial.println("OFF");
          digitalWrite(8, LOW);                     //выкл 7 реле
          }  

          if(c == '15'){                              
          Serial.println("ON");
          digitalWrite(9, HIGH);                    //то вкл 8 реле
          }
          if(c == '16'){                              
          Serial.println("OFF");
          digitalWrite(9, LOW);                     //выкл 8 реле
          }  
      }
      if (c == '\n') {                              //если "с" равен символу новой строки
        currentLineIsBlank = true;                  //то начинаем новую строку
      } 
      else if (c != '\r') {                         //иначе, если "с" не равен символу возврата курсора на начало строки
        currentLineIsBlank = false;                 //то получаем символ на текущей строке
      }
    
      if (c == '\n' && currentLineIsBlank) {        //выводим HTML страницу
        client.println("HTTP/1.1 200 OK");          //заголовочная информация
        client.println("Content-Type: text/html");
        client.println("Connection: close");  
        client.println("Refresh: 30");              //автоматическое обновление каждые 30 сек
        client.println();
        client.println("<!DOCTYPE HTML>");          //HTML тип документа
        client.println("<html>");                   //открытие тега HTML 
        client.println("<head>");
        client.print("<title>My web Server</title>");                  //название страницы
        client.println("</head>");
        client.print("<H1>My web Server</H1>");                        //заголовк на странице

          client.print("<p>kitchen</p>");
          client.print("<a href=\"/$1\"><button>On</button></a>");       //реле 1
          client.print("<a href=\"/$2\"><button>Off</button></a>");      
          client.println("<br />");  
          
          client.print("<p>Bedroom 1</p>");
          client.print("<a href=\"/$3\"><button>On</button></a>");       //реле 2
          client.print("<a href=\"/$4\"><button>Off</button></a>");      
          client.println("<br />");       

          client.print("<p>Bedroom 2</p>");
          client.print("<a href=\"/$5\"><button>On</button></a>");       //реле 3
          client.print("<a href=\"/$6\"><button>Off</button></a>");      
          client.println("<br />");

          client.print("<p>Hole</p>");
          client.print("<a href=\"/$7\"><button>On</button></a>");       //реле 4
          client.print("<a href=\"/$8\"><button>Off</button></a>");      
          client.println("<br />");

          client.print("<p>Bathroom</p>");
          client.print("<a href=\"/$9\"><button>On</button></a>");       //реле 5
          client.print("<a href=\"/$10\"><button>Off</button></a>");      
          client.println("<br />");

          client.print("<p>Corridor</p>");
          client.print("<a href=\"/$11\"><button>On</button></a>");       //реле 6
          client.print("<a href=\"/$12\"><button>Off</button></a>");      
          client.println("<br />");
        
          client.print("<p>Hallway</p>");
          client.print("<a href=\"/$13\"><button>On</button></a>");       //реле 7
          client.print("<a href=\"/$14\"><button>Off</button></a>");      
          client.println("<br />");
         
          client.print("<p>Sockets</p>");
          client.print("<a href=\"/$15\"><button>On</button></a>");       //реле 8
          client.print("<a href=\"/$16\"><button>Off</button></a>");      
          client.println("<br />");
        
        client.println("</html>");                  //закрываем тег HTML
        break;                                      //выход
      }
    
    }
    
  }
  delay(1);                                          //время на получение новых данных
  client.stop();                                     //закрываем соеднение 
}
}
