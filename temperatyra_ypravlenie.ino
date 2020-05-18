#include <SPI.h>             //библиотека для работы с SPI
#include <Ethernet.h>        //библиотека для работы с Ethernet 
#include <OneWire.h>                  // библиотека для взаимодействия с устройствами, работающими на шине и по протоколу 1-Wire
#include <DallasTemperature.h>        // библиотека с функциями для работы с DS18B20 

#define ONE_WIRE_BUS 2                // Указываем пин подключения data-вывода датчика температуры
#define term_power 4                  // Указываем пин подключения питания датчика температуры
OneWire oneWire(ONE_WIRE_BUS);        // Сообщаем библиотеке об устройстве, работающем по протоколу 1-Wire
DallasTemperature sensors(&oneWire);  // Связываем функции библиотеки DallasTemperature с нашим 1-Wire устройством (DS18B20)


boolean newInfo = 0;        //переменная для новой информации
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };     //MAC адрес Ethernet-модуля


IPAddress ip(192 , 168 , 0 , 19 );    //указываем IP адрес


EthernetServer server(80);  //инифиализация библиотеки Ethernet server library

int tvib = 23;  //температура выбираемая

void setup()
{
                                              
   
  
  Ethernet.begin(mac, ip);    //запускаем сервер с указанными ранее MAC и вашим IP
  server.begin();
   
  sensors.begin();                // Запускаем библиотеку измерения температуры
  pinMode(term_power, OUTPUT);    // Определяем пин подключения питания датчика температуры
  Serial.begin(9600);
}

float temperature() {                            // Измеряем температуру 10 секунд
  digitalWrite(term_power, HIGH);                // Включаем питание датчика температуры
  delay(800);                                    // Задержка перед первым измерением 
  sensors.requestTemperatures();                 // Запрос на измерение температуры (1-й ошибочный)
  delay(800);                                    // Задержка перед повторным измерением
                
  float t = float(sensors.getTempCByIndex(0));   // Получаем значение температуры
  digitalWrite(term_power, LOW);                 // Отключаем питание датчика температуры
  delay(800);                                   // Задержка, чтобы датчик не нагревался от частых измерений
  return(t);                                     // Возвращаем значение температуры в место вызова функции
}
void loop()
{
  Serial.println(temperature(),1);               // Выводим текущее значение температуры датчика, округленное до десятых*/
  
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
          if(c == 'p'){                              //и "с" содержит 1
          tvib = tvib +1;                  
          }
          if(c == 'm'){                              //если "с" содержит 2
          tvib = tvib - 1;
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
                                                    //автоматическое обновление каждые 30 сек
        client.println();
        client.println("<!DOCTYPE HTML>");          //HTML тип документа
        client.println("<html>");                   //открытие тега HTML 
        client.println("<head>");
        client.print("<meta charset=utf-8>");
        client.println("<meta http-equiv='refresh' content=10;URL=http://192.168.0.19/>");
        client.print("<title>My web Server</title>");                  //название страницы
        client.println("</head>");
        client.println("<body>");
        client.print("<H1>Web Server умного дома</H1>");                        //заголовк на странице
          
          
          client.print("<div>");  
            
            client.print("<div>");
              client.print("<p>Ввод температуры</p>");
              client.print("<a href=\"/$p\"><button>+</button></a>");       //управление температурой  
              client.print(tvib);
              client.print("<a href=\"/$m\"><button>-</button></a>");      
            client.print("</div>");       
              
              client.println("<br />");
            
           client.print("<div>"); 
              client.print("Температура в доме = ");                               //выводим температуру на сайт
              client.print(temperature(),1); 
              client.print("c");
            client.print("</div>"); 
         
         client.print("</div>"); 
          
          client.println("</body>");
          
         
        
        client.println("</html>");                  //закрываем тег HTML
        break;                                      //выход
      }
    
    }
    
  }
  delay(1);                                          //время на получение новых данных
  client.stop();                                     //закрываем соеднение 
}
}
