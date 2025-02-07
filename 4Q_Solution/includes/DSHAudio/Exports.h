#pragma once

#ifdef DSH_AUDIO_LIBRARY_EXPORTS
#define DSH_AUDIO_LIBRARY_API __declspec(dllexport)
#else
#define DSH_AUDIO_LIBRARY_API __declspec(dllimport)
#endif