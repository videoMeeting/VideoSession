#ifndef __VIDEC_EXPORT_H__
#define __VIDEC_EXPORT_H__

#ifdef VIDEC_EXPORT
#define VIDEC_API _declspec(dllexport)
#elif VIDEC_DLL
#define VIDEC_API _declspec(dllimport)
#else
#define VIDEC_API
#endif

#endif