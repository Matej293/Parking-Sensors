#ifndef CAR_SENSOR_H
#define CAR_SENSOR_H

#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include"Texture.h"

enum SensorState {
    NONE,
    OUTERMOST,
    MIDDLE,
    NEAREST
};

class CarSensor {
public:
    CarSensor();

    void Inputs(GLFWwindow* window);
    void DisplaySensors();

private:
    SensorState frontSensorState = NONE;
    SensorState backSensorState = NONE;

    Texture sensorTextures[4]; // Array to store sensor textures
};

#endif
