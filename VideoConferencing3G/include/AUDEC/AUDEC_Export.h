#ifndef __AUDEC_EXPORT_H__
#define __AUDEC_EXPORT_H__

#ifdef AUDEC_EXPORT
#define AUDEC_ENGINE_API _declspec(dllexport)
#elif AUDEC_DLL
#define AUDEC_ENGINE_API _declspec(dllimport)
#else
#define AUDEC_ENGINE_API
#endif

#endif


