//=================================================================================================
//                     НАЧАЛО ОБРАБОТКИ НАЖАТИЯ КЛАВИШ ВВЕРХ/ВНИЗ.      
void NajatieUpDownLeftRight() {

unsigned long currentMillis = millis(); 

checkButton();
if (buttonFlag!=bf_none){                               //Если кнопка нажата и статус кнопки не равен нулю
        previousMillisLCDbrightness = currentMillis;  digitalWrite(LCDbright, HIGH);  //сбрасываем таймер подсветки экрана, включаем подсветку.
  
if (curButton==3&&buttonFlag==1){buttonFlag=bf_none;    //Однократное нажатие кнопки DOWN "вниз"
        m++;                                            //увеличиваем переменную уровня меню
        Serial.print("Selected screen: "); Serial.println(ekran); Serial.println("==================");
        lcd.clear();
        if (m>20) {m=20;}}                                //если уровень больше ..., то оставаться на значении ....
        
if (curButton==1&&buttonFlag==1){buttonFlag=bf_none;    //Однократное нажатие кнопки UP "вверх"
        m--;                                            //уменьшаем переменную уровня меню
        Serial.print("Selected screen: "); Serial.println(ekran); Serial.println("==================");
        lcd.clear();
        if (m<0) {m=0;}}                                //если уровень меньше 0, то оставаться на значении 0.
        
if (ekran==0&&curButton==5&&buttonFlag==3){             //Длительное нажатие кнопки SELECT "выбрать" (нажатие более 5 секунд)
        if (millis()-timerButton_2>long_3_Time){
        timerButton_2=millis();
        lcd.clear();
        m=11;}}     
        
if (ekran==11&&curButton==5&&buttonFlag==1){buttonFlag=bf_none;
        m=0; lcd.clear();}         
        

if (ekran==12&&curButton==5&&buttonFlag==3){     //Длительное нажатие кнопки SELECT "выбрать" (нажатие более 5 секунд) на экране 12 (create  DATALOG1.csv)
        if (millis()-timerButton_2>long_3_Time){
        timerButton_2=millis();
        lcd.clear();
        Serial.println("Creating DATALOG1.csv ....."); }}

if (ekran==13&&curButton==5&&buttonFlag==3){     //Длительное нажатие кнопки SELECT "выбрать" (нажатие более 5 секунд) на экране 13 (delete  DATALOG1.csv)
        if (millis()-timerButton_2>long_3_Time){
        timerButton_2=millis();
        lcd.clear();
        Serial.println("Deleting DATALOG1.csv .....");} }}
      
    
  
}
//                    КОНЕЦ ОБРАБОТКИ НАЖАТИЯ КЛАВИШ ВВЕРХ/ВНИЗ.
//=================================================================================================
   
