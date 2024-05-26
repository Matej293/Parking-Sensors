#include<iostream>
#include"sensorControl.h"

int frontSensorState = 0;
int backSensorState = 0;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        updateSensorState(key);
    }
}

void updateSensorState(int key) {
    if (key == GLFW_KEY_W) {
        if (frontSensorState < 3) {
            ++frontSensorState;
            if (backSensorState > 0) {
                --backSensorState;  // Lower back sensor
            }
        }
        else {
            frontSensorState = 0;
        }
        std::cout << "Front Sensor State: " << frontSensorState << std::endl;
    }
    else if (key == GLFW_KEY_S) {
        if (backSensorState < 3) {
            ++backSensorState;
            if (frontSensorState > 0) {
                --frontSensorState;  // Lower front sensor
            }
        }
        else {
            backSensorState = 0;
        }
        std::cout << "Back Sensor State: " << backSensorState << std::endl;
    }
}

void initSensorControl(GLFWwindow* window) {
    glfwSetKeyCallback(window, keyCallback);
}
