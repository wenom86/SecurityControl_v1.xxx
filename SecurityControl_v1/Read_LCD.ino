//=================================================================================================
//                   НАЧАЛО ВЫВОДА ПРИВЕТСТВИЯ НА ЭКРАН ПРИ ВКЛЮЧЕНИИ
void privetstvie()
   {     
   // Вывод приветствия на экран при включении контроллера. 
   lcd.setCursor(0, 0);
   lcd.print( " ---SolarControl---" );   // ---SolarControl---
   lcd.setCursor(0, 1);                  // *DATE: 08.08.1976*
   lcd.print("DATE: ");                  // *TIME: 22:08:54  *
   lcd.print(rtc.getDateStr()); 
   lcd.setCursor(0, 2);         
   lcd.print("TIME: ");         
   lcd.print(rtc.getTimeStr());
   lcd.setCursor(16, 3); 
   lcd.print( "v1.0" );
   delay (1000);
   lcd.clear();
   
   Serial.println("==================");
   Serial.println("---SolarControl---");
   Serial.print("DATE: "); 
   Serial.println(rtc.getDateStr());        
   Serial.print("TIME: ");         
   Serial.println(rtc.getTimeStr());
   Serial.println( "v1.0" );
   Serial.print("FreeMemory: ");                    //Отчет о количестве оставшейся памяти
   Serial.println(freeRam());                       // в байтах. (1Кбайт=1024байт)
   Serial.println("==================");
   

}

//                   КОНЕЦ ВЫВОДА ПРИВЕТСТВИЯ НА ЭКРАН ПРИ ВКЛЮЧЕНИИ
//=================================================================================================


//=================================================================================================
//                   НАЧАЛО ОБРАБОТКИ ВЫБОРА ОТОБРАЖАЕМОГО ЭКРАНА В ЗАВИСИМОСТИ ОТ ПЕРЕМЕННОЙ "m"   
void Ekran()
   {
   if (m==0){ ekran = 0; }
   if (m==1){ ekran = 1; }
   if (m==2){ ekran = 2; }
   if (m==3){ ekran = 3; }
   if (m==4){ ekran = 4; }
   if (m==5){ ekran = 5; }
   if (m==6){ ekran = 6; }
   if (m==7){ ekran = 7; }
   if (m==8){ ekran = 8; }
   if (m==9){ ekran = 9; }
   if (m==10){ ekran = 10; }
   if (m==11){ ekran = 11; }
   if (m==12){ ekran = 12; }
   if (m==13){ ekran = 13; }
   
   }
//                   КОНЕЦ ОБРАБОТКИ ВЫБОРА ОТОБРАЖАЕМОГО ЭКРАНА В ЗАВИСИМОСТИ ОТ ПЕРЕМЕННОЙ "m"
//=================================================================================================

   
//=================================================================================================
//                   НАЧАЛО ОТОБРАЖЕНИЯ ИНФОРМАЦИИ НА ЭКРАНАХ      
void Read_ekran(){

if (ekran==0)                  //переменная ekran=0 (+), главный экран.
   {                            //отображаем
   lcd.setCursor(0, 0);  lcd.print("T1:"); lcd.setCursor(5, 0); lcd.print(T1);
   lcd.setCursor(0, 1);  lcd.print("t2:"); lcd.setCursor(5, 1); lcd.print(t2());
   lcd.setCursor(12, 2); lcd.print(rtc.getTimeStr());
   lcd.setCursor(10, 3); lcd.print(rtc.getDateStr()); } 
  
else if (ekran==1){  
   lcd.setCursor(0, 0);         
   lcd.print("T1gar|V2gar|");    
   lcd.setCursor(0, 1); 
   lcd.print(T1, 0); }

else if (ekran==2){
   lcd.setCursor(0, 0);        
   lcd.print("T2=");    
   if (i == 1) {lcd.print(t2()); }
   if (i == 0){ lcd.print("   "); }  }
   
else if (ekran==3){  
   }

else if (ekran==4){ 
   }   

else if (ekran==5){  
   }
   
else if (ekran==6){  
   }
   
else if (ekran==7){ 
   }   

else if (ekran==8){  
   }

else if (ekran==9){ 
   }

else if (ekran==10){ 
   }
   
else if (ekran==11){
   lcd.setCursor(0, 0);        
   lcd.print("---ManualControl----");    
   if (i == 1){lcd.setCursor(0, 1);lcd.print("         UP"); lcd.setCursor(0, 2);lcd.print("     LEFT  RIGHT");lcd.setCursor(0, 3);lcd.print("        DOWN"); }
   if (i == 0){lcd.setCursor(0, 1);lcd.print("           "); lcd.setCursor(0, 2);lcd.print("                ");lcd.setCursor(0, 3);lcd.print("            "); }  }

else if (ekran==12){ 
   lcd.setCursor(0, 0); lcd.print("Press "); if (i == 1){lcd.setCursor(6, 0); lcd.print("CENTER");} if (i == 0){lcd.setCursor(6, 0);lcd.print("      ");} lcd.setCursor(13, 0); lcd.print("button");
   lcd.setCursor(0, 1); lcd.print("5 seconds for CREATE");       
   lcd.setCursor(0, 2); lcd.print("end logging in file:"); 
   lcd.setCursor(0, 3); lcd.print("   DATALOG1.csv"); }
   
else if (ekran==13){
   lcd.setCursor(0, 0); lcd.print("Press "); if (i == 1){lcd.setCursor(6, 0); lcd.print("CENTER");} if (i == 0){lcd.setCursor(6, 0);lcd.print("      ");} lcd.setCursor(13, 0); lcd.print("button");
   lcd.setCursor(0, 1); lcd.print("5 seconds for DELETE");       
   lcd.setCursor(0, 2); lcd.print("logging file:"); 
   lcd.setCursor(0, 3); lcd.print("   DATALOG1.csv"); }   
   
}   
//                  КОНЕЦ ОТОБРАЖЕНИЯ ИНФОРМАЦИИ НА ЭКРАНАХ  
//=================================================================================================
