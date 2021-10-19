
#pragma once

#include <vector>

class MAudio
{
private:
  void *m_context;
  std::vector<std::vector<float>> buffers;

public:
  MAudio();
  ~MAudio();
  bool init();
  int listDevices();
  int getUSBAudioDevice();
  int testOutput();
  int testInput();
  int playSine();
  int record();
  int initMic();
  int testMic();
};