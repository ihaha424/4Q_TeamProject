#pragma once

#ifdef DSH_LOGGER_LIBRARY_EXPORTS
#define DSH_LOGGER_LIBRARY_API __declspec(dllexport)
#else
#define DSH_LOGGER_LIBRARY_API __declspec(dllimport)
#endif