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
            if (backSensorState == 0) {
                ++frontSensorState;
            }
            else {
                --backSensorState;
            }
        }
        else {
            frontSensorState = 0;
        }
        std::cout << "W key pressed." << std::endl;
        std::cout << "Front Sensor State: " << frontSensorState << std::endl;
        std::cout << "Back Sensor State: " << backSensorState << std::endl << std::endl;
    }
    else if (key == GLFW_KEY_S) {
        if (backSensorState < 3) {
            if (frontSensorState == 0) {
                ++backSensorState;
            }
            else {
                --frontSensorState;
            }
        }
        else {
            backSensorState = 0;
        }
        std::cout << "S key pressed." << std::endl;
        std::cout << "Front Sensor State: " << frontSensorState << std::endl;
        std::cout << "Back Sensor State: " << backSensorState << std::endl << std::endl;
    }
}


void initSensorControl(GLFWwindow* window) {
    glfwSetKeyCallback(window, keyCallback);
}
