#include "soundManager.h"

SoundManager::SoundManager() {
    prevFrontSensorState = -1;
    prevBackSensorState = -1;
    isSoundPlaying = false;
}

SoundManager::~SoundManager() {}

void SoundManager::loadSounds() {
    for (int i = 1; i < 4; ++i) {
        frontSensorSounds[i].loadFromFile("Sounds/front_sensor_sound_" + std::to_string(i) + ".wav");
        backSensorSounds[i].loadFromFile("Sounds/back_sensor_sound_" + std::to_string(i) + ".wav");
    }
}

void SoundManager::playSound(int frontSensorState, int backSensorState, float volume) {
    if (frontSensorState == 0 && backSensorState == 0) {
        sound.stop();
        isSoundPlaying = false;
        prevFrontSensorState = frontSensorState;
        prevBackSensorState = backSensorState;
        return;
    }

    int prioritySensorState = (frontSensorState > backSensorState) ? frontSensorState : backSensorState;

    if (prioritySensorState != prevFrontSensorState && prioritySensorState != prevBackSensorState) {
        if (prioritySensorState > 0 && prioritySensorState <= 3) {
            sound.setBuffer((frontSensorState == prioritySensorState) ? frontSensorSounds[frontSensorState] : backSensorSounds[backSensorState]);
            sound.setVolume(volume);
            sound.setLoop(true);
            sound.play();
            isSoundPlaying = true;
        }
        else {
            sound.stop();
            isSoundPlaying = false;
        }
        prevFrontSensorState = frontSensorState;
        prevBackSensorState = backSensorState;
    }
}
