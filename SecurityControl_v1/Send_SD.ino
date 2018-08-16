/*

//=================================================================================================
//                    НАЧАЛО ПРОЦЕУРЫ ЧТЕНИЯ КОНФИГУРАЦИОННОГО ФАЙЛА С SD карты.
//Read the Configuration information (COMMANDS.txt)
	File commandFile = SD.open("NAME.txt");
	if (commandFile)
	{
		Serial.println("Reading Command File");
		
		float decade = pow(10, (commandFile.available() - 1));
		while(commandFile.available())
		{
			float temp = (commandFile.read() - '0');
			refresh_rate = temp*decade+refresh_rate;
			decade = decade/10;
		}
		Serial.print("Refresh Rate = ");
		Serial.print(refresh_rate);
		Serial.println("ms");
		commandFile.close();
	}
	else
	{
		Serial.println("Could not read command file.");
		return;
	}
//                    КОНЕЦ ПРОЦЕУРЫ ЧТЕНИЯ КОНФИГУРАЦИОННОГО ФАЙЛА С SD карты.
//=================================================================================================
*/






//=================================================================================================
//                    НАЧАЛО ПРОЦЕУРЫ ЗАПИСИ ДАННЫХ на SD карту.
void writelogfile1(){


}
//                    КОНЕЦ ПРОЦЕУРЫ ЗАПИСИ ДАННЫХ на SD карту.
//=================================================================================================

