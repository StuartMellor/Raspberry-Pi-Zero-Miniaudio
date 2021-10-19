// #define MA_NO_DECODING
// #define MA_NO_ENCODING

// #include <array>
// #include "mAudio.hpp"
// #include <stdio.h>
// #include <iostream>
// extern "C"
// {
// #define MA_DEBUG_OUTPUT
// #define MINIAUDIO_IMPLEMENTATION
// #include "miniaudio.h"
// #define DR_WAV_IMPLEMENTATION
// #include "dr_wav.h"
// }
// #ifdef __EMSCRIPTEN__
// #include <emscripten.h>
// void main_loop__em()
// {
// }

// #endif
// #define DEVICE_FORMAT ma_format_f32
// #define DEVICE_CHANNELS 2
// #define DEVICE_SAMPLE_RATE 48000
// #define OUTPUT_BUFFERS 4
// #define BUFFER_SIZE 4096

// struct capture_pUserData
// {
//   std::array<std::array<float, BUFFER_SIZE>, OUTPUT_BUFFERS> *outputBuffers;
//   int writeIndex;
//   int readIndex;
//   int recIndex;
// };

// void rec_data_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
// {
//   drwav *pWav = (drwav *)pDevice->pUserData;
//   MA_ASSERT(pWav != NULL);

//   drwav_write_pcm_frames(pWav, frameCount, pInput);

//   (void)pOutput;
// }

// ma_bool32 getdevices_callback(ma_context *pContext, ma_device_type deviceType, const ma_device_info *pInfo, void *pUserData)
// {
//   if (deviceType == ma_device_type_playback)
//   {
//     std::cout << "Playback device:" << std::endl;
//     std::cout << pInfo->name << std::endl;
//   }
//   else if (deviceType == ma_device_type_capture)
//   {
//     std::cout << "Capture device:" << std::endl;
//     std::cout << pInfo->name << std::endl;
//   }
//   std::cout << "---------" << std::endl;
//   return 0;
// }

// void data_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
// {
//   // In playback mode copy data to pOutput. In capture mode read data from pInput. In full-duplex mode, both
//   // pOutput and pInput will be valid and you can move data from pInput into pOutput. Never process more than
//   // frameCount frames.
//   ma_waveform *pSineWave;

//   MA_ASSERT(pDevice->playback.channels == DEVICE_CHANNELS);

//   pSineWave = (ma_waveform *)pDevice->pUserData;
//   MA_ASSERT(pSineWave != NULL);

//   ma_waveform_read_pcm_frames(pSineWave, pOutput, frameCount);

//   (void)pInput; /* Unused. */
// }

// MAudio::MAudio()
// {
// }

// MAudio::~MAudio()
// {
// }

// bool MAudio::init()
// {
//   ma_context context;
//   if (ma_context_init(NULL, 0, NULL, &context) != MA_SUCCESS)
//   {
//     printf("Failed to initialize context.\n");
//     return false;
//   }
//   return true;
// }

// int MAudio::playSine()
// {
//   ma_waveform sineWave;
//   ma_device_config deviceConfig;
//   ma_device device;
//   ma_waveform_config sineWaveConfig;

//   sineWaveConfig = ma_waveform_config_init(DEVICE_FORMAT, DEVICE_CHANNELS, DEVICE_SAMPLE_RATE, ma_waveform_type_sine, 0.2, 220);
//   ma_waveform_init(&sineWaveConfig, &sineWave);

//   ma_result result;
//   ma_context context;
//   ma_device_info *pPlaybackDeviceInfos, *pCaptureDeviceInfos;
//   ma_device_info selectedDeviceInfo;
//   ma_uint32 pPlaybackDeviceCount, pCaptureDeviceCount;
//   if (ma_context_init(NULL, 0, NULL, &context) != MA_SUCCESS)
//   {
//     printf("Failed to initialize context.\n");
//     return -2;
//   }
//   ma_device_id dev_id;

//   result = ma_context_get_devices(&context, &pPlaybackDeviceInfos, &pPlaybackDeviceCount, &pCaptureDeviceInfos, &pCaptureDeviceCount);
//   if (result != MA_SUCCESS)
//   {
//     printf("Failed to gather information on devices!");
//   }
//   selectedDeviceInfo = pPlaybackDeviceInfos[3];

//   deviceConfig = ma_device_config_init(ma_device_type_playback);
//   deviceConfig.playback.pDeviceID = &selectedDeviceInfo.id;
//   deviceConfig.playback.format = DEVICE_FORMAT;
//   deviceConfig.playback.channels = DEVICE_CHANNELS;
//   deviceConfig.sampleRate = DEVICE_SAMPLE_RATE;
//   deviceConfig.dataCallback = data_callback;
//   deviceConfig.pUserData = &sineWave;

//   if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS)
//   {
//     printf("Failed to open playback device.\n");
//     return -4;
//   }

//   printf("Device Name: %s\n", device.playback.name);

//   if (ma_device_start(&device) != MA_SUCCESS)
//   {
//     printf("Failed to start playback device.\n");
//     ma_device_uninit(&device);
//     return -5;
//   }

// #ifdef __EMSCRIPTEN__
//   emscripten_set_main_loop(main_loop__em, 0, 1);
// #else
//   printf("Press Enter to quit...\n");
//   getchar();
// #endif

//   ma_device_uninit(&device);

//   return 0;
// }

// int MAudio::getUSBAudioDevice()
// {
//   return 0;
// }

// void my_log_callback(ma_context *pContext, ma_device *pDevice, ma_uint32 logLevel, const char *message)
// {
//   std::cout << message << std::endl;
// }

// int MAudio::listDevices()
// {
//   ma_result result;
//   ma_context context;
//   ma_device_info *pPlaybackDeviceInfos;
//   ma_uint32 playbackDeviceCount;
//   ma_device_info *pCaptureDeviceInfos;
//   ma_uint32 captureDeviceCount;
//   ma_uint32 iDevice;

//   ma_backend backends[] = {
//       ma_backend_alsa,
//       ma_backend_pulseaudio,
//       ma_backend_wasapi,
//       ma_backend_dsound};

//   ma_context_config config = ma_context_config_init();
//   config.logCallback = my_log_callback;
//   config.alsa.useVerboseDeviceEnumeration = true;

//   int ret = 0;
//   if ((ret = ma_context_init(backends, sizeof(backends) / sizeof(backends[0]), &config, &context)) != MA_SUCCESS)
//   {
//     printf("Failed to initialize context.\n");
//     std::cout << "retval: " << ret << std::endl;
//     return -2;
//   }

//   result = ma_context_get_devices(&context, &pPlaybackDeviceInfos, &playbackDeviceCount, &pCaptureDeviceInfos, &captureDeviceCount);
//   if (result != MA_SUCCESS)
//   {
//     printf("Failed to retrieve device information.\n");
//     return -3;
//   }
//   std::cout << "Capture device count: " << captureDeviceCount << std::endl;

//   printf("Playback Devices\n");
//   for (iDevice = 0; iDevice < playbackDeviceCount; ++iDevice)
//   {
//     printf("    %u: %s\n", iDevice, pPlaybackDeviceInfos[iDevice].name);
//   }

//   printf("\n");

//   printf("Capture Devices\n");
//   for (iDevice = 0; iDevice < captureDeviceCount; ++iDevice)
//   {
//     printf("    %u: %s\n", iDevice, pCaptureDeviceInfos[iDevice].name);
//   }

//   ma_context_uninit(&context);
//   return 0;
// }

// int MAudio::testOutput()
// {
//   // ma_result result;
//   // ma_context context;
//   // ma_device_info *pPlaybackDeviceInfos, *pCaptureDeviceInfos;
//   // ma_device_info selectedDevice;
//   // ma_uint32 pPlaybackDeviceCount, pCaptureDeviceCount;
//   // if (ma_context_init(NULL, 0, NULL, &context) != MA_SUCCESS)
//   // {
//   //   printf("Failed to initialize context.\n");
//   //   return -2;
//   // }
//   // ma_device_id dev_id;

//   // result = ma_context_get_devices(&context, &pPlaybackDeviceInfos, &pPlaybackDeviceCount, &pCaptureDeviceInfos, &pCaptureDeviceCount);
//   // if (result != MA_SUCCESS)
//   // {
//   //   printf("Failed to gather information on devices!");
//   // }
//   // selectedDevice = pPlaybackDeviceInfos[3];
//   // ma_device_config config = ma_device_config_init(ma_device_type_playback);
//   // config.playback.pDevice.ID = &selectedDevice.id;
//   // config.playback.format = ma_format_s16;
//   // config.playback.channels = 2;
//   // config.sampleRate = 44100;
//   // config.dataCallback = data_callback;
//   // config.pUserData

//   //     // ma_context_get_device_info(&context, ma_device_type_playback, &dev_id, ma_share_mode_shared);
//   return 0;
// }

// int MAudio::testInput()
// {
//   return 0;
// }

// int record()
// {
//   return 0;
// }

// int MAudio::initMic()
// {
//   ma_result result;
//   drwav_data_format wavFormat;
//   drwav wav;
//   ma_device_config deviceConfig;
//   ma_device device;

//   wavFormat.container = drwav_container_riff;
//   wavFormat.format = DR_WAVE_FORMAT_PCM;
//   wavFormat.channels = 1;
//   wavFormat.sampleRate = 48000;
//   wavFormat.bitsPerSample = 16;

//   if (drwav_init_file_write(&wav, "minitest.wav", &wavFormat, NULL) == DRWAV_FALSE)
//   {
//     printf("Failed to initialize output file.\n");
//     return -1;
//   }

//   ma_context context;
//   ma_device_info *pPlaybackDeviceInfos, *pCaptureDeviceInfos;
//   ma_device_info selectedDeviceInfo;
//   ma_uint32 pPlaybackDeviceCount, pCaptureDeviceCount;
//   if (ma_context_init(NULL, 0, NULL, &context) != MA_SUCCESS)
//   {
//     printf("Failed to initialize context.\n");
//     return -2;
//   }
//   ma_device_id dev_id;

//   result = ma_context_get_devices(&context, &pPlaybackDeviceInfos, &pPlaybackDeviceCount, &pCaptureDeviceInfos, &pCaptureDeviceCount);
//   if (result != MA_SUCCESS)
//   {
//     printf("Failed to gather information on devices!");
//   }

//   std::cout << pCaptureDeviceInfos[4].name << std::endl;
//   selectedDeviceInfo = pPlaybackDeviceInfos[4];
//   std::cout << "->" << selectedDeviceInfo.id.alsa << "<-" << std::endl;
//   // selectedDeviceInfo.id.alsa[3] = 1;

//   deviceConfig = ma_device_config_init(ma_device_type_capture);
//   deviceConfig.capture.pDeviceID = &selectedDeviceInfo.id;
//   deviceConfig.capture.format = ma_format_s16;
//   deviceConfig.capture.channels = wavFormat.channels;
//   deviceConfig.sampleRate = wavFormat.sampleRate;
//   deviceConfig.dataCallback = rec_data_callback;
//   deviceConfig.pUserData = &wav;

//   result = ma_device_init(NULL, &deviceConfig, &device);
//   if (result != MA_SUCCESS)
//   {
//     printf("Failed to initialize capture device.\n");
//     return -2;
//   }

//   result = ma_device_start(&device);
//   if (result != MA_SUCCESS)
//   {
//     ma_device_uninit(&device);
//     printf("Failed to start device.\n");
//     return -3;
//   }

//   printf("Press Enter to stop recording...\n");
//   getchar();

//   ma_device_uninit(&device);
//   drwav_uninit(&wav);

//   return 0;
// }