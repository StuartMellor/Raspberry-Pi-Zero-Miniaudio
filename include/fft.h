extern "C"
{
#include "mailbox.h"
#include "gpu_fft.h"
}
#include <cmath>
#include <vector>
#include <mutex>

class FFT
{
public:
  FFT();
  ~FFT();
  int init(int log2_N);
  int test();
  bool isPowerOfTwo(ulong x);
  int transform(std::vector<float> *dataIn, std::vector<float> *dataOut, bool justReal);
  bool reading;

private:
  struct GPU_FFT *fftInfo;
  int FFT_N;
  std::mutex mtx; // mutex for critical section
};