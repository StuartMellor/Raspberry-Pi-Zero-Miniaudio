extern "C"
{
#include "mailbox.h"
#include "gpu_fft.h"
}
#include <cmath>

class FFT
{
public:
  FFT();
  ~FFT();
  int init(int log2_N);
  int test();
  int transform(int dir, std::vector<float> *dataIn, std::vector<float> *dataOut);

private:
  struct GPU_FFT *fftinfo;
};