#include "application.h"

void modeHandler(const char *event, const char *data)
{
    
}

void meshSetup()
{
    Mesh.on();
    Mesh.connect();
    Mesh.subscribe("mode", modeHandler);
}

void getMeshNetworkInfo()
{
    if (Mesh.ready())
    {
        Serial.println("Mesh Active");
    }
    else if (Mesh.connecting())
    {
        Serial.println("Mesh Connecting");
    }
    else if (Mesh.listening())
    {
        Serial.println("Mesh Listening");
    }
}