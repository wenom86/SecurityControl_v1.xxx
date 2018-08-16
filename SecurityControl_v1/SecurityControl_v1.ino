//=============================================================
// НАЗВАНИЕ ПРОГРАММЫ: SecurityControl_v1
// ВЕРСИЯ ПРОГРАММЫ: v1.ххх
// ВЕРСИЯ ARDUINO IDE: 1.0.5 r2
//=============================================================
#include <OneWire.h>            // + для термодатчика 18b20
#include <LiquidCrystal.h>      // + библ. LCD-экрана.
#include <EEPROM.h>             // + библ. работы с eeprom, встроенным в ардуину.
#include <DS3231.h>             // + библ. работы с модулем часов.
#include <SPI.h>

long previousMillisTimeSW = 0; //счетчик прошедшего времени для мигания изменяемых значений.
long intervalTimeSW = 500;     //интервал мигания изменяемых значений.
int i;

long previousMillisLCDbrightness = 0; //счетчик прошедшего времени для Автовылючения подсветки LCD
long intervalLCDbrightness = 300000;  //задержка Автовылючения подсветки LCD (по умолчанию 1 минута)
#define LCDbright 31                  // управление подсветкой на 31 пине. 

#define bs_none   0         //статус нет нажатие
#define bs_push   1         //статус нажатие
#define bs_hold_1 2         //статус удержание (1-2 секунды)и более, через(5-30 секунд)переход в статус 3
#define bs_hold_2 3         //статус удержание (5-30 секунд)и более 
#define bf_none   0         //значение флага нет нажатие
#define bf_push   1         //значение флага нажатие
#define bf_hold_1 2         //значение флага удержание (0,5-2 секунды) 
#define bf_hold_2 3         //значение флага удержание (5-30 секунд)и более 
#define long_1_Time 750     //удержание (0,5-2 секунды) - статус 2, через(5-30 секунд)переход в статус 3
#define long_2_Time 5000    //удержание (5-30 секунд)и более - статус 3
#define long_3_Time 250     //время авто нажатий
long timerButton_2=0;       //время задержка кнопки для антидребезга
#define bs_read_1 0         //статус первое чтение с АЦП
#define bs_lag    1         //статус задержка и второе чтение с АЦП 
#define bs_score  2         //статус вычисление разници между 2 чтениями 
#define bs_change 3         //статус присвоения кнопки
#define bf_read_1 0         //значение флага первое чтение с АЦП
#define bf_lag    1         //значение флага задержка и второе чтение с АЦП 
#define bf_score  2         //значение флага вычисление разници между 2 чтениями 
byte deBounce=0;            // переменная СТАТУС антидребезга
#define deBounceTime  20    //задержка (мс от 5 до 30 мс)для антидребезга
#define p_p           0     //устанавливаем разницу (в единицах от 0 до 10) между двумя считываниями значений с АЦП входа А0 
int temp_read=1023;
int temp_read_1; 
int temp_read_2; 
int temp;
int clik_1;
int clik_10 = 0;
int clik_s = 0;
byte buttonPin=A2;         // пин подключения кнопки (на АЦП получаем: кнопка не нажата кнопка 0>850, кнопка 1<90,кнопка 2<250, кнопка3<430,кнопка 4<650,кнопка 5<850)
byte buttonState=0;        // переменная СТАТУС КНОПКИ
byte curButton=0;          // ТЕКУЩАЯ КНОПКА
long timerButton=0;        // Время нажатия кнопки
long timerButton_1=0;      // Время задержка кнопки для антидребезга
byte pressBut=0;
byte buttonFlag=0;
//--------------------- start ReadKey ---------------------------
//    Функция АНТИДРЕБЕЗГ с присвоением номера нажатой кнопки 
//---------------------------------------------------------------
byte ReadKey()             //функция устраняет дребезг контактов, считывает значение с АЦП и преобразует в номер нажатой кнопки
 {
  switch (deBounce)                               // СТАТУС антидребезга
  { 
   case bs_read_1:
    temp_read_1=analogRead(buttonPin);            //первое считывание с АЦП входа А0
    timerButton_1 = millis();                     //запоминаем время
    deBounce=bs_lag;
   break;
   case bs_lag:                                   //задержка
    if(millis() - timerButton_1 > deBounceTime)   //задержка между считываниями
   {   
    temp_read_2=analogRead(buttonPin);            //второе считывание с АЦП входа А0 
    deBounce=bs_score; 
   break;  
   }   
    deBounce=bs_lag;             
   break;
   case bs_score:                                 //вычисление разници между 2 чтениями
    temp=temp_read_1-temp_read_2;                 //определение разницы значений считаных с АЦП                                   
    if (temp < 0)temp=(int)(temp*-1);             //делаем положительный знак
    if (temp>p_p)
   {
    deBounce=bs_read_1;
   break;
   } 
    deBounce=bs_change;
   break;
    default:                        
    temp_read=((temp_read_2+temp_read_1)/2);       //усредняем значение
    deBounce=bs_read_1; 
   }
   if (temp_read <  30) return 2;                  //RIGHT в право
   if (temp_read < 215) return 1;                  //UP в верх
   if (temp_read < 360) return 4;                  //LEFT в лево
   if (temp_read < 430) return 3;                  //DOWN в низ
   if (temp_read < 505) return 5;                  //SELECT выбрать
  return 0;    
 } //end ReadKey
    //---------------- start checkButton ----------------
    //   Присвоение статуса кнопки
    //---------------------------------------------------
void checkButton() { 
  switch (buttonState)  {                       //проверяем СТАТУС КНОПКИ
    //------------------------------------------    
     case (bs_none):                            //если ни чего не нажато(=0)
     curButton=ReadKey();                       //считываем номер нажатой кнопки   
     if (curButton!=0)                          //Если кнопка нажата (т.е., значение >0)   
    {
     buttonState=bs_push;                       //следующий статус нажатия (=1)
     buttonFlag=bs_push;                        //флаг сработки = нажата кнопка 
     timerButton=millis();                      //запоминаем время
    }
     else
     {
      buttonState=bs_none;                      //флаг сработки = статуса нет нажатия кнопки 
      buttonFlag=bf_none;                       //флаг сработки = нет нажатия кнопки 
     }
      break;
    //------------------------------------------
     case (bs_push):                           //если нажата кнопка (=1)
     if ((ReadKey()==curButton))               //если кнопка все еще нажата
     {       
       if (millis()-timerButton>long_1_Time)   //если кнопка удерживается(1-2 секунды)и более
      {
       buttonState=bs_hold_1;                  //статус удержание (1-2 секунды)и более(=2)
       buttonFlag=bs_hold_1;                   //флаг сработки = нажатие кнопки
      }
    }
      else
     {
      buttonState=bs_none;                    //флаг сработки = статуса нет нажатия кнопки 
      buttonFlag=bf_none;                     //флаг сработки = нет нажатия кнопки 
     }
      break;
    //------------------------------------------
     case (bs_hold_1):                         //удержание (1-2 секунды)и более (=2)
     if ((ReadKey()==curButton))               //если кнопка все еще нажата
     { 
      if (millis()-timerButton>long_2_Time)    //если кнопка удерживается(5-30 секунд))и более
     { 
      buttonState=bs_hold_2;                   //меняем на статус удержание (5-30 секунд)и более
      buttonFlag=bf_hold_2;                    //флаг сработки = 1-2 секунды и более
     }
    }
     else
     {
      buttonState=bs_none;                    //флаг сработки = статуса нет нажатия кнопки 
      buttonFlag=bf_none;                     //флаг сработки = нет нажатия кнопки
     }                                          
      break;
    //------------------------------------------
    case (bs_hold_2):                         //удержание (5-30 секунд)и более (=3)
     if ((ReadKey()==curButton))              //если кнопка все еще нажата
     {
      if (millis()-timerButton>long_1_Time)   //если кнопка удерживается более времени для автоповтора
     {
      timerButton=millis();                   //запоминаем время
      buttonFlag=bf_hold_2;                   //флаг сработки = 5-30 секунд и более 
     }
    }
    else
    {
      buttonState=bs_none;                    //флаг сработки = нет нажатия кнопки 
      buttonFlag=bf_none;                     //флаг сработки = нет нажатия кнопки 
    }    
     break;
    //------------------------------------------
   }  //end switch
  }   //end checkButton
  //------------------------
int lik = 0;
int clik = 0;
int s = 0;

int valueeeprom1 = EEPROM.read(10);         
int valueeeprom2 = EEPROM.read(11);         
int valueeeprom3 = EEPROM.read(12);      

int freeRam () {                // функция определения оставшейся памяти в контроллере.
extern int __heap_start, *__brkval; 
int v; 
return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); }

unsigned long IntervalReadSensorTC = 1000;                // интервал считывания показаний с термопар.
unsigned long IntervalReadSensorDS = 1000;                // интервал считывания показаний с DS18b20.
unsigned long IntervalReadButton = 300;                   // интервал между нажатиями клавиш на клавиатуре. (антидребезг)
unsigned long IntervalPrintSerialSensorTempVal = 5000;    // интервал вывода в сериал-порт информации со всех термодатчиков.
unsigned long IntervalPrintSerialKeyboardVal = 1000;      // интервал вывода в сериал-порт служебной информации.
unsigned long ValueMillisPreviousReadButton = 0, ValueMillisPreviousReadSensorTC = 0, ValueMillisPreviousPrintSerial = 0, ValueMillisPreviousPrintSerialKeyboardVal = 0, 
              ValueMillisPreviousPrintSerialSensorTempVal = 0, ValueMillisPreviousReadSensorDS = 0;

OneWire ds(10);                  // линия 1-Wire будет на pin 10

// int analogPin=2;                 //пин А2 для аналоговой клавиатуры.
int b=0;                         //переменая для аналоговой клавиатуры.
int k=0;                         //переменая для аналоговой клавиатуры.
int T1,T3,t4;                    // инициализируем переменные для значений температуры.....
int ekran;                       //переменная для выбора экрана меню.
int m=0;                         //переменная для экранов меню.

LiquidCrystal lcd(22, 28, 23, 24, 25, 26, 27);   // для МЕГИ 2560. (A=5v/K=GND)(VSS=GND/VDD=5v/RS=pin22/RW=pin28/E=pin23/D4=pin24/D5=pin25/D6=pin26/D7=pin27).
DS3231  rtc(20, 21);             //шина, на которую подключены часы (для ардуино нано на 328 чипе, это пины A4/A5)(для меги - пины 20/21).

char msg;

void setup(){ 
  
Serial.begin(9600);  // инициализация сериал-порта 0, для вывода служебной инф-ии в монитор порта.
delay(500);          // ожидание
lcd.begin(16, 2);    // инициализация экрана (16 символов в 2 строках).
delay(500);          // ожидание
rtc.begin();         // инициализация часов на DS3231.
delay(500);          // ожидание

pinMode(LCDbright, OUTPUT);           //выводы устанавливаюся в режим выхода
digitalWrite(LCDbright, HIGH);        //на выходе высокий уровень

pinMode(53, OUTPUT);                  // пин CS для модуля SD-карты на Мега2560


privetstvie();      // Выводим приветствие на экран при включении питания(название, версия и т.д.) (вкладка Read_LCD)
// writelogfile();

}
void loop(){



  
 
NajatieUpDownLeftRight();    // Обрабатываем нажатие клавиш Вверх/Вниз. (вкладка Read_KEYBOARD)
Ekran();                     // Выбор № отображаемого экрана в зав-ти от переменной "m" (вкладка Read_LCD)
Read_ekran();                // Отображаем содержимое выбранного экрана (вкладка Read_LCD)
//sendSerialEkranValue();      // Отправляем номер выбранного экрана в сериал-порт.



  
unsigned long currentMillis = millis();                                                                //Присваивание значения общей переменной отсчета времени. 

  if(currentMillis - ValueMillisPreviousReadSensorDS > IntervalReadSensorDS)                             //Если счетчик превысил интервал, то:
  { t2(); ValueMillisPreviousReadSensorDS = currentMillis; }                                             //Cчитываем показания DS18b20. и терморезистора1  
  if(currentMillis - ValueMillisPreviousPrintSerialKeyboardVal > IntervalPrintSerialKeyboardVal)         //Если счетчик превысил интервал, то:
  { sendSerialKeyboardValue(); ValueMillisPreviousPrintSerialKeyboardVal = currentMillis; }              //осуществляем выполнение отправки значения клавиатуры в порт. 
  if(currentMillis - ValueMillisPreviousPrintSerialSensorTempVal > IntervalPrintSerialSensorTempVal)     //Если счетчик превысил интервал, то:
  { sendSerialSensorTempVal(); ValueMillisPreviousPrintSerialSensorTempVal = currentMillis; } //осуществляем выполнение отправки значений температур в порт.
  if(currentMillis - previousMillisTimeSW >= intervalTimeSW)                                             //Если счетчик превысил интервал, 
  { i = !i; previousMillisTimeSW = previousMillisTimeSW+intervalTimeSW; }                                //меняем значение переменной i, добавляем к переменной время интервала.
  if(currentMillis - previousMillisLCDbrightness > intervalLCDbrightness)                                //Если счетчик достиг интервала. 
  {previousMillisLCDbrightness = currentMillis;  digitalWrite(LCDbright, LOW); }                         //выключаем подсветку LCD.
                                      
  
}



