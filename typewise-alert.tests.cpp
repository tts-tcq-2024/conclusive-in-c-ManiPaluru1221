#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite,InfersBreachAccordingToLow) {
  TemperatureRange range = {0, 35};  // lower limit 0, upper limit 35
  EXPECT_EQ(inferBreach(-1, range), TOO_LOW);
}

TEST(TypeWiseAlertTestSuite,InfersBreachAccordingToHIGH) {
  TemperatureRange range = {0, 35}; 
  EXPECT_EQ(inferBreach(36, range), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite,InfersBreachAccordingToNormal) {
  TemperatureRange range = {0, 35};
  EXPECT_EQ(inferBreach(20, range), NORMAL);
}

TEST(TemperatureRangeTest, GetTemperatureRange) {
    TemperatureRange range;

    // Test for PASSIVE_COOLING
    range = getTemperatureRange(PASSIVE_COOLING);
    EXPECT_EQ(range.lowerLimit, 0);
    EXPECT_EQ(range.upperLimit, 35);

    // Test for HI_ACTIVE_COOLING
    range = getTemperatureRange(HI_ACTIVE_COOLING);
    EXPECT_EQ(range.lowerLimit, 0);
    EXPECT_EQ(range.upperLimit, 45);

    // Test for MED_ACTIVE_COOLING
    range = getTemperatureRange(MED_ACTIVE_COOLING);
    EXPECT_EQ(range.lowerLimit, 0);
    EXPECT_EQ(range.upperLimit, 40);
}
TEST(TypeWiseAlertTestSuite, CheckAndAlertToController) {   // Assuming TOO_HIGH corresponds to 2
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandX"};
    testing::internal::CaptureStdout();
    checkAndAlert(TO_CONTROLLER, batteryChar, 36);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 2\n");
}

TEST(TypeWiseAlertTestSuite, CheckAndAlertToControllerTooLow) {   // Assuming TOO_LOW corresponds to 1
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandX"};
    testing::internal::CaptureStdout();
    checkAndAlert(TO_CONTROLLER, batteryChar, -1);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 1\n"); 
}

TEST(TypeWiseAlertTestSuite, CheckAndAlertToControllerNormal) {   // Assuming NORMAL corresponds to 0
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandX"};
    testing::internal::CaptureStdout();
    checkAndAlert(TO_CONTROLLER, batteryChar, 30);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 0\n"); 
}

// Test case for checkAndAlert to email with low temperature
TEST(TypeWiseAlertTestSuite, CheckAndAlertToEmailLow) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandX"};
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, -5);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too low\n");
}

// Test case for checkAndAlert to email with high temperature
TEST(TypeWiseAlertTestSuite, CheckAndAlertToEmailHigh) {
    BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "BrandX"};
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, 50);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too high\n");
}

// Test case for checkAndAlert to email with normal temperature
TEST(TypeWiseAlertTestSuite, CheckAndAlertToEmailNormal) {
    BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "BrandX"};
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, 30);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");  // No output for NORMAL
}
TEST(TypeWiseAlertTestSuite, CheckAndAlertInvalidTarget) {
    BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "BrandX"};
    testing::internal::CaptureStdout();
    checkAndAlert(static_cast<AlertTarget>(999), batteryChar, 50); // Trigger invalid case
    // No particular output to check, just ensuring the branch is covered
}
