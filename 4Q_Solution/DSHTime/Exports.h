#pragma once

#ifdef DSH_TIME_LIBRARY_EXPORTS
#define DSH_TIME_LIBRARY_API __declspec(dllexport)
#else
#define DSH_TIME_LIBRARY_API __declspec(dllimport)
#endif