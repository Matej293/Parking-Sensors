#ifndef SENSORCONTROL_H
#define SENSORCONTROL_H

#include<GLFW/glfw3.h>

extern int frontSensorState;
extern int backSensorState;

void initSensorControl(GLFWwindow* window);
void updateSensorState(int key);

#endif
