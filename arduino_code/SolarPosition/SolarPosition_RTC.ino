#include <SPI.h>
#include <Controllino.h>
#include <SolarPosition.h>

// number of decimal digits to print
const uint8_t digits = 3;

// some test positions:
SolarPosition Toronto(43.653109, -79.386304);  // Toronto, Canada
SolarPosition Timbuktu(16.775214, -3.007455); // Timbuktu, Mali, Africa
SolarPosition Melbourne(-37.668987, 144.841006); //Melbourne Airport (MEL)
SolarPosition Ulaanbaatar(47.847410, 106.769004); //Ulaanbaatar Airport (ULN)
SolarPosition Copenhagen(55.676098, 12.568337); 
// program begins

time_t getTime()
{
  int someS = 0;  //second
  int someM = 0;  //minute
  int someH = 12; //hour
  int someD = 15; //day
  int someMo = 4; //month
  int someY = 1985; //year
  tmElements_t someTime = {0, Controllino_GetMinute(), Controllino_GetHour(), 0, Controllino_GetDay(), Controllino_GetMonth(), CalendarYrToTm(Controllino_GetYear()) };

  time_t time = makeTime(someTime);

  return time;
}

void setup()
{
  Serial.begin(9600);

  /* set time and date by separate values values to the RTC chip */
  /* Day, WeekDay, Month, Year, Hour, Minute, Second); */
  Controllino_RTC_init();
  Controllino_SetTimeDate(24,3,7,24,10,57,00);

  Serial.println(F("\tSolar Position Demo"));

  // set the Time service as the time provider
  SolarPosition::setTimeProvider(getTime);
}

void loop()
{
  // now test the real time methods:
  //
  printTime(getTime());

  Serial.print(F("Copenhagen:\t"));
  printSolarPosition(Copenhagen.getSolarPosition(), digits);
  Serial.print(F("Toronto:\t"));
  printSolarPosition(Toronto.getSolarPosition(), digits);
  Serial.print(F("Melbourne:\t"));
  printSolarPosition(Melbourne.getSolarPosition(), digits);
  Serial.print(F("Timbuktu:\t"));
  printSolarPosition(Timbuktu.getSolarPosition(), digits);
  Serial.print(F("Ulaanbaatar:\t"));
  printSolarPosition(Ulaanbaatar.getSolarPosition(), digits);
  Serial.println();

  delay(15000);
}

// Print a solar position to serial
//
void printSolarPosition(SolarPosition_t pos, int numDigits)
{
  Serial.print(F("el: "));
  Serial.print(pos.elevation, numDigits);
  Serial.print(F(" deg\t"));

  Serial.print(F("az: "));
  Serial.print(pos.azimuth, numDigits);
  Serial.println(F(" deg"));
}

// Print a time to serial
//
void printTime(time_t t)
{
  tmElements_t someTime;
  breakTime(t, someTime);

  Serial.print(someTime.Hour);
  Serial.print(F(":"));
  Serial.print(someTime.Minute);
  Serial.print(F(":"));
  Serial.print(someTime.Second);
  Serial.print(F(" UTC on "));
  Serial.print(dayStr(someTime.Wday));
  Serial.print(F(", "));
  Serial.print(monthStr(someTime.Month));
  Serial.print(F(" "));
  Serial.print(someTime.Day);
  Serial.print(F(", "));
  Serial.println(tmYearToCalendar(someTime.Year));
}

