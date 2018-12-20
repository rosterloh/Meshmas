#include "Particle.h"
#include "mesh/mesh.h"
#include "leds/leds.h"

#define MESH_CHECK_INTERVAL 20000

SYSTEM_THREAD(ENABLED); // run system and app on different threads

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

uint8_t currentMode = 8;
String deviceId;
unsigned long previousMeshCheck = 0;

int updateModeHandler(String data);
void cloudInit();

void setup()
{
    Serial.begin();

    meshSetup();

    deviceId = System.deviceID();

    cloudInit();

    initLEDs();
}

void loop()
{
    unsigned long currentMillis = millis();
    switch(currentMode) {
        case 0:
            changeColor(strip.Color(0, 0, 0));
            break;
        case 1:
            colorWipe(strip.Color(0, 255, 0), 20); // Green
            break;
        case 2:
            colorWipe(strip.Color(0, 0, 255), 20); // Blue
            break;
        case 3:
            theaterChase(strip.Color(255, 0, 0), 20); // Red
            break;
        case 4:
            theaterChase(strip.Color(0, 255, 0), 20); // Green
            break;
        case 5:
            theaterChase(strip.Color(255, 0, 255), 20); // Green
            break;
        case 6:
            rainbowCycle(20);
            break;
        case 7:
            rainbow(20);
            break;
        case 8:
            theaterChaseRainbow(200);
            break;
    }

    if (currentMillis - previousMeshCheck > MESH_CHECK_INTERVAL)
    {
        previousMeshCheck = currentMillis;
        getMeshNetworkInfo();
    }
}

void cloudInit()
{
  Particle.variable("currentMode", currentMode);

  Particle.function("updateMode", updateModeHandler);
}

int updateModeHandler(String data)
{
  currentMode = String(data).toInt();
  return 1;
}
