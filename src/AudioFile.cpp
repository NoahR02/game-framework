#include "AudioFile.h"

#include <sndfile.h>

#include <algorithm>
#include <iostream>
#include <string>

AudioFile::AudioFile(const std::string filePath) : filePath(filePath), buffer(0) {

  SF_INFO sfInfo;
  SNDFILE *audioFile = sf_open(filePath.c_str(), SFM_READ, &sfInfo);

  if(!audioFile) {
    std::cerr << "Could not load audio file." << std::endl;
    return;
  }

  frames = sfInfo.frames;
  sampleRate = sfInfo.samplerate;
  channels = sfInfo.channels;
  format = sfInfo.format;
  sections = sfInfo.sections;
  seekable = sfInfo.seekable;

  alGenBuffers(1, &buffer);

  ALenum format = AL_NONE;
  if(channels == 1) format = AL_FORMAT_MONO16;
  if(channels == 2) format = AL_FORMAT_STEREO16;

  auto* audioData = new short[(size_t) frames * channels];
  sf_count_t readFrames = sf_readf_short(audioFile, audioData, frames);

  alBufferData(buffer, format, audioData, sizeof(short) * readFrames * channels, sampleRate);

  delete[] audioData;
  sf_close(audioFile);

}

AudioFile::~AudioFile() {
  alDeleteBuffers(1, &buffer);
}
