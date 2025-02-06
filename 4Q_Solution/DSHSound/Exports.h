#pragma once

#ifdef DSH_SOUND_LIBRARY_EXPORTS
#define DSH_SOUND_LIBRARY_API __declspec(dllexport)
#else
#define DSH_SOUND_LIBRARY_API __declspec(dllimport)
#endif