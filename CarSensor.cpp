#include"CarSensor.h"

CarSensor::CarSensor() : sensorTextures{
    Texture("no_sensor.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
    Texture("outermost_sensor.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
    Texture("middle_sensor.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
    Texture("nearest_sensor.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE)
} {
    // Constructor body, if needed
}

void CarSensor::Inputs(GLFWwindow* window) {
    // Check if specific keys are pressed to toggle sensor states
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        // Toggle front sensor state
        if (frontSensorState == NONE)
            frontSensorState = OUTERMOST;
        else if (frontSensorState == OUTERMOST)
            frontSensorState = MIDDLE;
        else if (frontSensorState == MIDDLE)
            frontSensorState = NEAREST;
        else if (frontSensorState == NEAREST)
            frontSensorState = NONE;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        // Toggle back sensor state
        if (backSensorState == NONE)
            backSensorState = OUTERMOST;
        else if (backSensorState == OUTERMOST)
            backSensorState = MIDDLE;
        else if (backSensorState == MIDDLE)
            backSensorState = NEAREST;
        else if (backSensorState == NEAREST)
            backSensorState = NONE;
    }
}


void CarSensor::DisplaySensors() {
    sensorTextures[frontSensorState].Bind();
    // Render front sensor based on state

    sensorTextures[backSensorState].Bind();
    // Render back sensor based on state
}
