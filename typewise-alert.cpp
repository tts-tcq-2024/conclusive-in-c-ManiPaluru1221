#include "typewise-alert.h"
#include <stdio.h>


// Function to get the temperature range based on cooling type
TemperatureRange getTemperatureRange(CoolingType coolingType) {
 // Define temperature Ranges for different cooling types
  TemperatureRange ranges[] = {
    {0, 35}, // PASSIVE_COOLING
    {0, 45}, // HI_ACTIVE_COOLING
    {0, 40}  // MED_ACTIVE_COOLING
  };
  return ranges[coolingType];
}

// Function to infer breach type based on value and limits
BreachType inferBreach(double value, TemperatureRange range) {
  if (value < range.lowerLimit) {   
    return TOO_LOW;
  }
  if (value > range.upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

// Function to send alret based on breach type
Void sendalret(AlertTarget alretTarget, BreachType breachType) {
  if (alertTarget == TO_CONTROLLER){
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
  }else if (alertTarget == TO_EMAIL){
    const char* recepient = "a.b@c.com";
    const char* message = (breachType == TOO_LOW)?
      "Hi, the temperature is too low\n" :
     (breachType == TOO_HIGH)?
      "Hi, the temperature is too high\n" :
      "";
    if (breachType != NORMAL) {
     printf("To: %s\n%s", recipient, message);
   }
  }
}

// Function to classify temperature breach and send alert
void checkAndAlert (AlertTarget alertTarget, BreachType breachType, double temperatureInC){
  TemperatureRange range = getTempratureRange(batterychar.coolingType):
  BreachType breachType = inferBreach(temparatureInC, range);
  sendAlert(alertTarget, breachType);
}
  
