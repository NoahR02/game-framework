#include "AudioSource.h"

AudioSource::AudioSource(std::shared_ptr<AudioFile> audioFile) {
  this->audioFile = audioFile;

  alGenSources(1, &sourceID);

  alSourcef(sourceID, AL_PITCH, 1);
  alSourcef(sourceID, AL_GAIN, 1);
  alSource3f(sourceID, AL_POSITION, 0, 0, 0.f);
  alSource3f(sourceID, AL_VELOCITY, 0, 0, 0);
  alSourcei(sourceID, AL_LOOPING, AL_FALSE);
  alSourcei(sourceID, AL_BUFFER, audioFile->buffer);
}

void setAudioFile(Entity& audioSourceID, std::shared_ptr<AudioFile> audioFile) {
  auto& audioSrc = audioSourceID.getComponent<AudioSource>();
  audioSrc.audioFile = std::move(audioFile);

  alSourcef(audioSrc.sourceID, AL_PITCH, 1);
  alSourcef(audioSrc.sourceID, AL_GAIN, 1);
  alSource3f(audioSrc.sourceID, AL_POSITION, 0, 0, 0.f);
  alSource3f(audioSrc.sourceID, AL_VELOCITY, 0, 0, 0);
  alSourcei(audioSrc.sourceID, AL_LOOPING, AL_FALSE);
  alSourcei(audioSrc.sourceID, AL_BUFFER, audioSrc.audioFile->buffer);
}

void play(Entity& audioSourceID) {
  auto& audioSrc = audioSourceID.getComponent<AudioSource>();
  alSourcePlay(audioSrc.sourceID);
}

void pause(Entity& audioSourceID) {
  auto& audioSrc = audioSourceID.getComponent<AudioSource>();
  alSourcePause(audioSrc.sourceID);
}

void stop(Entity& audioSourceID) {
  auto& audioSrc = audioSourceID.getComponent<AudioSource>();
  alSourceStop(audioSrc.sourceID);
}

AudioSource::~AudioSource() {
  alDeleteSources(1, &sourceID);
}