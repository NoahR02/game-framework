#ifndef RPG_AUDIOFILE_H
#define RPG_AUDIOFILE_H

#include <AL/al.h>

#include <cstdint>
#include <string>

struct AudioFile {

  std::string filePath;
  ALuint buffer;

  std::int64_t frames;
  int sampleRate;
  int channels;
  int format;
  int sections;
  int seekable;

  explicit AudioFile(const std::string filePath);
  AudioFile() = default;

};


#endif //RPG_AUDIOFILE_H
