#ifndef BWCOMMONDEF_HEADER
#define BWCOMMONDEF_HEADER
#ifdef BUILDING_BERRYWINE_DLL
#define BW_DLL __declspec(dllexport)
#else
#define BW_DLL __declspec(dllimport)
#endif
#endif
