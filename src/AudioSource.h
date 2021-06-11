#ifndef RPG_AUDIOSOURCE_H
#define RPG_AUDIOSOURCE_H

#include <AL/al.h>
#include "ECS/Entity.h"
#include "AudioFile.h"

struct AudioSource {
  ALuint sourceID;
  AudioFile audioFile;
};


void setAudioFile(Entity& audioSourceID, const AudioFile& audioFile) {
  auto& audioSrc = audioSourceID.getComponent<AudioSource>();
  audioSrc.audioFile = audioFile;

  alGenSources(1, &audioSrc.sourceID);

  alSourcef(audioSrc.sourceID, AL_PITCH, 1);
  alSourcef(audioSrc.sourceID, AL_GAIN, 1);
  alSource3f(audioSrc.sourceID, AL_POSITION, 0, 0, 0.f);
  alSource3f(audioSrc.sourceID, AL_VELOCITY, 0, 0, 0);
  alSourcei(audioSrc.sourceID, AL_LOOPING, AL_FALSE);
  alSourcei(audioSrc.sourceID, AL_BUFFER, audioSrc.audioFile.buffer);
}

void play(Entity& audioSourceID) {
  auto& audioSrc = audioSourceID.getComponent<AudioSource>();
  alSourcePlay(audioSrc.sourceID);
}


#endif
