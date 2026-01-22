#pragma once

#ifdef DSH_WINDOW_LIBRARY_EXPORTS
#define DSH_WINDOW_LIBRARY_API __declspec(dllexport)
#else
#define DSH_WINDOW_LIBRARY_API __declspec(dllimport)
#endif