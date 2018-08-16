//=================================================================================================
//                    НАЧАЛО ОТПРАВКИ ЗНАЧЕНИЯ КЛАВИАТУРЫ (0-1024) В СЕРИАЛ-ПОРТ
 void sendSerialKeyboardValue(){
   int c;
   c = analogRead(buttonPin);
   if (c<950) { 
   Serial.print("=== ZnachenieKlaviaturi (0-1024): ");
   Serial.print(analogRead(buttonPin));        
   Serial.println(" ===");
   }     
 }  
//                    КОНЕЦ ОТПРАВКИ ЗНАЧЕНИЯ КЛАВИАТУРЫ (0-1024) В СЕРИАЛ-ПОРТ
//=================================================================================================

/* 
//=================================================================================================
//                    НАЧАЛО ОТПРАВКИ НОМЕРА ВЫБРАННОГО LCD-ЭКРАНА В СЕРИАЛ-ПОРТ.
 void sendSerialEkranValue(){
   int valueekran;
   if (valueekran!=ekran){ Serial.print("Vibran EKRAN: "); Serial.println(ekran); valueekran=ekran;}     
 }  
//                    КОНЕЦ ОТПРАВКИ НОМЕРА ВЫБРАННОГО LCD-ЭКРАНА В СЕРИАЛ-ПОРТ.
//=================================================================================================
*/

//=================================================================================================
//                    НАЧАЛО ОТПРАВКИ ЗНАЧЕНИЙ ВСЕХ ТЕРМОДАТЧИКОВ В СЕРИАЛ-ПОРТ
 void sendSerialSensorTempVal(){
   Serial.print("T1: ");
   Serial.print(T1);   
   Serial.println(" C (temp vodi na vihode iz concentatora)(termopara)");

   Serial.print("T2: ");
   Serial.print(t2());   
   Serial.println(" C (temp vodi na vhode v concentator)(DS18b20)");

    Serial.print("T3: ");
    int v = analogRead(A0);
    Serial.print(" C (analogRead(A0): ");Serial.print(v); Serial.println(")");

   
   Serial.println("==================");
 
 }       
//                    КОНЕЦ ОТПРАВКИ ЗНАЧЕНИЙ ВСЕХ ТЕРМОДАТЧИКОВ В СЕРИАЛ-ПОРТ
//=================================================================================================
/* //=================================================================================================
//                    НАЧАЛО ОБЩЕНИЯ С МОДЕМОМ SIM900.


void SimAT()
{
  Serial1.println("AT");
  delay(200);
  if (Serial1.available()>0){ msg=Serial1.read(); Serial.print(msg);}
  Serial1.println("AT+CIPSHUT");
  delay(200);
  if (Serial1.available()>0){ msg=Serial1.read(); Serial.print(msg);}
  Serial1.println("AT+CIPSTATUS");
  delay(200);
  if (Serial1.available()>0){ msg=Serial1.read(); Serial.println(msg);}
}



//                    КОНЕЦ ОБЩЕНИЯ С МОДЕМОМ SIM900.
*/ //=================================================================================================


