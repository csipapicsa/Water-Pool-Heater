// https://github.com/PaulStoffregen/Time (Using the Arduino Library Manager, install "Time by Michael Margolis".) 
// https://github.com/KenWillmott/SolarPosition 
// install the .zip SolarPosition-master.zip

#include <SPI.h>
#include <Controllino.h>
#include <SolarPosition.h>

static SolarPosition Copenhagen(55.676098, 12.568337); 

static time_t getTime()
{
  tmElements_t someTime = {0, Controllino_GetMinute(), Controllino_GetHour(), 0, Controllino_GetDay(), Controllino_GetMonth(), CalendarYrToTm(Controllino_GetYear()) };
  time_t time = makeTime(someTime);

  return time;
}

void InitRTCSolarPosition()//(short day, short weekday, short month, short year, short hour, short minute, short second)
{
  Controllino_RTC_init();
  //Controllino_SetTimeDate(24,3,7,24,10,57,00);
  // Controllino_SetTimeDate(day, weekday, month, year, hour,minute, second)

  SolarPosition::setTimeProvider(getTime);
}

float getSunAzimuth() {
  SolarPosition_t pos = Copenhagen.getSolarPosition(); 
  return pos.azimuth; 
}