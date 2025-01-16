#pragma once

#ifdef DSH_INPUT_LIBRARY_EXPORTS
#define DSH_INPUT_LIBRARY_API __declspec(dllexport)
#else
#define DSH_INPUT_LIBRARY_API __declspec(dllimport)
#endif