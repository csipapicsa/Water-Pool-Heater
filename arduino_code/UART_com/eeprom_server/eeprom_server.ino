#include <EEPROM.h>

struct Settings {
  int tempTarget;
  float sunThreshold;
  int waterLevel;
};

Settings settings; 
const int MAX_MESSAGE_LENGTH = 100;
char message[MAX_MESSAGE_LENGTH];
int address = 0;

bool data_decoder(const String& datastring, Settings& settings) {
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
  settings.waterLevel = waterLevelStr.toInt();
  
  if (settings.tempTarget < 0 || settings.tempTarget > 100 || 
      isnan(settings.sunThreshold) || 
      settings.waterLevel < 0) {
    return false;
  }
  
  return true;
}

void setup() {
  Serial.begin(9600);
  
  String eepromContents = "Current EEPROM contents:\n";
  String currentMessage = "";
  
  for (int i = 0; i < EEPROM.length(); i++) {
    char c = EEPROM.read(i);
    if (c == '\0') {
      if (currentMessage.length() > 0) {
        eepromContents += currentMessage + "\n";
        if (data_decoder(currentMessage, settings)) {
          Serial.println("Decoded settings:");
          Serial.print("Temp Target: ");
          Serial.println(settings.tempTarget);
          Serial.print("Sun Threshold: ");
          Serial.println(settings.sunThreshold);
          Serial.print("Water Level: ");
          Serial.println(settings.waterLevel);
        } else {
          Serial.println("Couldn't decode: " + currentMessage);
        }
        currentMessage = "";
      }
      break;  // Stop reading after the first null character
    } else {
      currentMessage += c;
    }
  }
  
  if (currentMessage.length() > 0) {
    eepromContents += currentMessage + "\n";
    if (data_decoder(currentMessage, settings)) {
      Serial.println("Decoded settings:");
      Serial.print("Temp Target: ");
      Serial.println(settings.tempTarget);
      Serial.print("Sun Threshold: ");
      Serial.println(settings.sunThreshold);
      Serial.print("Water Level: ");
      Serial.println(settings.waterLevel);
    } else {
      Serial.println("Couldn't decode: " + currentMessage);
    }
  }
  
  eepromContents += "\nReady to receive new messages. Type and press enter to store in EEPROM.";
  Serial.println(eepromContents);
}

void loop() {
  if (Serial.available()) {
    int bytesRead = Serial.readBytesUntil('\n', message, MAX_MESSAGE_LENGTH - 1);
    message[bytesRead] = '\0';
    
    for (int i = 0; i < bytesRead + 1; i++) {
      EEPROM.update(address + i, message[i]);
    }
    
    Serial.print("Stored message: ");
    Serial.println(message);

    if (data_decoder(message, settings)) {
        Serial.print("Temp Target: ");
        Serial.println(settings.tempTarget);
        Serial.print("Sun Threshold: ");
        Serial.println(settings.sunThreshold);
        Serial.print("Water Level: ");
        Serial.println(settings.waterLevel);
    } else {
        Serial.println("Failed to parse data");
    }
    
    address = 0; 
  }
}