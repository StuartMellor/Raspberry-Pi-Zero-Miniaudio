#include "fft.h"
#include <iostream>
#include <mutex>

// enum
// {
//   SPECTRAL_POWER false
// }

FFT::FFT()
{
}

int FFT::init(int log2_N)
{
  reading = false;
  int mb = mbox_open(), ret;
  FFT_N = pow(2, log2_N);
  ret = gpu_fft_prepare(mb, log2_N, GPU_FFT_FWD, 1, &fftInfo);
  std::cout << "gpu_fft_prepare return value:" << ret << std::endl;
  switch (ret)
  {
  case -1:
    printf("Unable to enable V3D. Please check your firmware is up to date.\n");
    return -1;
  case -2:
    printf("log2_N=%d not supported.  Try between 8 and 22.\n", log2_N);
    return -1;
  case -3:
    printf("Out of memory.  Try a smaller batch or increase GPU memory.\n");
    return -1;
  case -4:
    printf("Unable to map Videocore peripherals into ARM memory space.\n");
    return -1;
  case -5:
    printf("Can't open libbcm_host.\n");
    return -1;
  }
  return 0;
}

int FFT::test()
{
  uint16_t N = 4096;
  float frequency = 400; // Hz
  float sf = 44100;
  uint16_t log2_N = log2(N);
  int err = 0;
  if ((err = init(log2_N)) < 0)
  {
    std::cout << "FFT init failed with error number: " << err << std::endl;
    return -1;
  }
  float freqStep = frequency / sf;
  std::vector<float> dataIn, dataOut;
  dataIn.resize(N);
  dataOut.resize(N);
  for (int i = 0; i < N; i++)
  {
    dataIn[i] = sin(GPU_FFT_PI * 2 * freqStep * i);
  }
  // if ((err = gpu_fft_execute(fftInfo)) != 0)
  // {
  //   std::cout << "FFT: Error - execution failed with error number: " << err << std::endl;
  //   gpu_fft_release(fftInfo);
  //   return -2;
  // }
  // std::cout << "FFT: Error - execution passed! Releasing memory." << std::endl;
  if ((err = transform(&dataIn, &dataOut, true)) < 0)
  {
    std::cout << "FFT:Transform Error - test failed!" << std::endl;
  }
  else
  {
    std::cout << "FFT:Transform Info - test success!" << std::endl;
  }
  gpu_fft_release(fftInfo);

  return 0;
}

int FFT::transform(std::vector<float> *dataIn, std::vector<float> *dataOut, bool justReal)
{

  if (FFT_N <= 0)
  {
    std::cout << "FFT:Transform Error - FFT is not initialized!" << std::endl;
    return -1;
  }
  //Check dataIn and dataOut are valid pointers
  if (dataIn == NULL)
  {
    std::cout << "FFT:Transform Error - Invalid pointer for input data array!" << std::endl;
    return -2;
  }
  if (dataOut == NULL)
  {
    std::cout << "FFT:Transform Error - Invalid pointer for output data array!" << std::endl;
    return -3;
  }

  int inN, outN;
  // Check size of dataIn and dataOut arrays
  if ((inN = dataIn->size()) <= 0)
  {
    // Zero data passed to transform!
    std::cout << "FFT:Transform Error - No data passed to input of transform!" << std::endl;
    return -4;
  }
  if ((outN = dataOut->size()) <= 0)
  {
    std::cout << "FFT:Transform Error - Data out array not resized!" << std::endl;
  }

  if (FFT_N != inN)
  {
    std::cout << "FFT:Transform Error - Length of data in doesn't match initialised FFT buffer size: inN: " << inN << " != FFT_N: " << FFT_N << std::endl;
    return -5;
  }

  if (!isPowerOfTwo(static_cast<ulong>(inN)))
  {
    std::cout << "FFT:Transform Error - Supplied input data does not have a length 2^N!" << std::endl;
    return -6;
  }

  reading = true;
  for (int i = 0; i < inN; i++)
  {

    mtx.lock();
    fftInfo->in[i].re = static_cast<double>((*dataIn)[i]);
    mtx.unlock();
    fftInfo->in[i].im = 0;
  }
  reading = false;

  int err;
  if ((err = gpu_fft_execute(fftInfo)) != 0)
  {
    std::cout << "FFT:Transform Error - FFT transform failed to execute: error code: " << err << std::endl;
    return -7;
  }

  for (int i = 0; i < inN; i++)
  {
    if (justReal)
    {
      (*dataOut)[i] = fftInfo->out[i].re;
    }
    else
    {
      (*dataOut)[i] = sqrt(pow(fftInfo->out[i].re, 2) + pow(fftInfo->out[i].im, 2));
    }
  }
  return 0;
}

bool FFT::isPowerOfTwo(ulong x)
{
  return (x != 0) && ((x & (x - 1)) == 0);
}

FFT::~FFT()
{
}
