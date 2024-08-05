#include <EEPROM.h>

struct Settings {
  int tempTarget;
  float sunThreshold;
  int waterLevelThreshold;
};

static const int MAX_MESSAGE_LENGTH = 100;
static char message[MAX_MESSAGE_LENGTH];
static int address = 0;

static bool data_decoder(const String& datastring, Settings& settings) {
  int firstComma = datastring.indexOf(',');
  int secondComma = datastring.indexOf(',', firstComma + 1);
  
  if (firstComma == -1 || secondComma == -1) {
    return false;
  }
  
  String tempTargetStr = datastring.substring(0, firstComma);
  String sunThresholdStr = datastring.substring(firstComma + 1, secondComma);
  String waterLevelStr = datastring.substring(secondComma + 1);
  
  settings.tempTarget = tempTargetStr.toInt();
  settings.sunThreshold = sunThresholdStr.toFloat();
  settings.waterLevelThreshold = waterLevelStr.toInt();
  
  if (settings.tempTarget < 0 || settings.tempTarget > 100 || 
      isnan(settings.sunThreshold) || 
      settings.waterLevelThreshold < 0) {
    return false;
  }
  
  return true;
}

void SetSettingsFromEeprom(Settings& settings) {
  String currentMessage = "";
  
  for (unsigned int i = 0; i < EEPROM.length(); i++) {
    char c = EEPROM.read(i);
    currentMessage += c;
    if (c == '\0') {
      break;
    }
  }
  
  if (currentMessage.length() > 0) {
    if (!data_decoder(currentMessage, settings)) {
      Serial.println("Couldn't decode: " + currentMessage);
      settings.tempTarget = 25;
      settings.sunThreshold = 2; 
      settings.waterLevelThreshold = 400;
    }
  } else {
    Serial.println("Nothing stored in EEPROM!"); 
    // default settings if nothing is stored in EEPROM
    settings.tempTarget = 25;
    settings.sunThreshold = 2; 
    settings.waterLevelThreshold = 400;
  }
}

void UpdateConfigFromSerial(Settings& settings) {
  if (Serial.available()) {
    int bytesRead = Serial.readBytesUntil('\n', message, MAX_MESSAGE_LENGTH - 1);
    message[bytesRead] = '\0';

    if (data_decoder(message, settings)) {
      for (int i = 0; i < bytesRead + 1; i++) {
        EEPROM.update(address + i, message[i]);
        Serial.print("Stored message: ");
        Serial.println(message);
      }
    } else {
      Serial.println("Failed to parse data");
    }
    
    address = 0; 
  }
}