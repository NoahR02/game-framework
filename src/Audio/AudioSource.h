#ifndef RPG_AUDIOSOURCE_H
#define RPG_AUDIOSOURCE_H

#include <AL/al.h>

#include <utility>
#include "../ECS/Entity.h"
#include "AudioFile.h"

struct AudioSource {
  ALuint sourceID;
  std::shared_ptr<AudioFile> audioFile;

  ~AudioSource();
  explicit AudioSource(std::shared_ptr<AudioFile> audioFile);
};

void setAudioFile(Entity& audioSourceID, std::shared_ptr<AudioFile> audioFile);

void play(Entity& audioSourceID);


#endif
