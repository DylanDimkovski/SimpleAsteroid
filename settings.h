#ifndef SETTINGS
#define SETTINGS

class Settings
{
public:
    int wChange = 0;
    int hChange = 0;
    float DELTA_T = 1000.0 / 100.0;
    int WIDTH = 2560;
    int HEIGHT = 1440;
    int hypotenuse;
    float oldTime = 0.0f;
    float countWave = 5.0f;
    int spawnRate = 1;
    int playerPoints = 0;
    };

#endif