#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include<SFML/Audio.hpp>
#include<string>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    void loadSounds();
    void playSound(int frontSensorState, int backSensorState, float volume);

private:
    sf::SoundBuffer frontSensorSounds[4];
    sf::SoundBuffer backSensorSounds[4];
    sf::Sound sound;
    int prevFrontSensorState;
    int prevBackSensorState;
    bool isSoundPlaying;
};

#endif // SOUNDMANAGER_H
