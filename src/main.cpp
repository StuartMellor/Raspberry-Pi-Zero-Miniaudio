
#include <iostream>
// #include "pAudio.h"
#include "mAudio.hpp"
#include "lodepng.h"
#include "fft.h"
#include <fstream>
// using namespace std;

typedef struct
{
  double r; // a fraction between 0 and 1
  double g; // a fraction between 0 and 1
  double b; // a fraction between 0 and 1
} rgb;

typedef struct
{
  double h; // angle in degrees
  double s; // a fraction between 0 and 1
  double v; // a fraction between 0 and 1
} hsv;

void encodeOneStep(const char *filename, std::vector<unsigned char> &image, unsigned width, unsigned height);
static rgb hsv2rgb(hsv in);

int main(int argc, char *argv[])
{
  bool listDevs = false;
  if (argc > 0)
  {
    for (int i = 0; i < argc; i++)
    {
      std::cout << argv[i] << std::endl;
      if (strcmp(argv[i], "-lsdev"))
      {
        listDevs = true;
        std::cout << "List devices turned on." << std::endl;
      }
    }
  }
  // FFT *fft = new FFT();
  // fft->test();

  MAudio *ma = new MAudio();
  ma->initMic();
  // if (listDevs)
  // {
  //   ma->listDevices();
  // }
  // std::cout << "Running cmake_test!" << std::endl;

  // std::cout << "mb open result = " << mb << std::endl;
  // // Generate Sinewave
  // uint16_t N = 4096;
  // uint16_t log2_N = log2(N);

  // float frequency = 400; // Hz
  // float sf = 44100;      // Hz

  // // 1 sec oscillates 100 times.
  // // 1 oscillation 2 * PI * i.
  // // 100 oscillations 2 * PI * 100.

  // float freqStep = frequency / sf;
  // for (int i = 0; i < N; i++)
  // {
  //   fftinfo->in[i].re = sin(GPU_FFT_PI * 2 * freqStep * i);
  // }

  // dataOut = fftinfo->out;

  // gpu_fft_execute(fftinfo);

  // // find max
  // double max = 0, temp;
  // for (int i = 0; i < N; i++)
  // {
  //   // could speed this up by removing the powers and sqrt then storing index
  //   temp = sqrt(pow(dataOut[i].re, 2) + pow(dataOut[i].im, 2));
  //   if (temp > max)
  //   {
  //     max = temp;
  //   }
  // }

  // unsigned width = 100, height = 2048;
  // std::vector<unsigned char> image;
  // image.resize(width * height * 4);

  // hsv t;
  // rgb out;
  // for (unsigned x = 0; x < width; x++)
  // {
  //   for (unsigned y = 0; y < height; y++)
  //   {
  //     temp = sqrt(pow(dataOut[N / 2 - y - 1].re, 2) + pow(dataOut[N / 2 - y - 1].im, 2)) / max;

  //     t.h = temp * 0.75;
  //     t.v = temp * 0.7 + 0.3;
  //     t.s = 1;

  //     out = hsv2rgb(t);

  //     image[4 * width * y + 4 * x + 0] = out.r * 255;
  //     image[4 * width * y + 4 * x + 1] = out.g * 255;
  //     image[4 * width * y + 4 * x + 2] = out.b * 255;
  //     image[4 * width * y + 4 * x + 3] = 255;
  //   }
  // }

  // const char *filename = "test.png";
  // encodeOneStep(filename, image, width, height);
}

void encodeOneStep(const char *filename, std::vector<unsigned char> &image, unsigned width, unsigned height)
{
  // Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  // if there's an error, display it
  if (error)
    std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

rgb hsv2rgb(hsv in)
{
  double hh, p, q, t, ff;
  long i;
  rgb out;

  if (in.s <= 0.0)
  { // < is bogus, just shuts up warnings
    out.r = in.v;
    out.g = in.v;
    out.b = in.v;
    return out;
  }
  hh = in.h;
  if (hh >= 360.0)
    hh = 0.0;
  hh /= 60.0;
  i = (long)hh;
  ff = hh - i;
  p = in.v * (1.0 - in.s);
  q = in.v * (1.0 - (in.s * ff));
  t = in.v * (1.0 - (in.s * (1.0 - ff)));

  switch (i)
  {
  case 0:
    out.r = in.v;
    out.g = t;
    out.b = p;
    break;
  case 1:
    out.r = q;
    out.g = in.v;
    out.b = p;
    break;
  case 2:
    out.r = p;
    out.g = in.v;
    out.b = t;
    break;

  case 3:
    out.r = p;
    out.g = q;
    out.b = in.v;
    break;
  case 4:
    out.r = t;
    out.g = p;
    out.b = in.v;
    break;
  case 5:
  default:
    out.r = in.v;
    out.g = p;
    out.b = q;
    break;
  }
  return out;
}