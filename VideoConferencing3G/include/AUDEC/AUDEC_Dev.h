//AUDEC_Dev.h
#ifndef __AUDEC_DEV_H__
#define __AUDEC_DEV_H__

#include <AUDEC/AUDEC_Export.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* AUDEC_CAP_DEV_HANDLE;
typedef void* AUDEC_PLAY_DEV_HANDLE;

typedef int (*AUDEC_CAP_DEV_CB)(short*pSamples,int nSamples,int nSampleRate,AUDEC_CAP_DEV_HANDLE hCapDev,void*pUserData);
typedef int (*AUDEC_PLAY_DEV_CB)(short*pSamples,int nSamples,int nSampleRate,AUDEC_PLAY_DEV_HANDLE hPlayDev,void*pUserData);

extern int AUDEC_ENGINE_API AUDEC_DevInit(void);
extern void AUDEC_ENGINE_API AUDEC_DevTerminate(void);

extern int AUDEC_ENGINE_API AUDEC_CapDevOpen(int nCapDevID,int nSampleRate,int nSamplesPerFrame,void*pUserData,AUDEC_CAP_DEV_CB cap_dev_cb,AUDEC_CAP_DEV_HANDLE*phCapDev);
extern int AUDEC_ENGINE_API AUDEC_CapDevStart(AUDEC_CAP_DEV_HANDLE hCapDev);
extern void AUDEC_ENGINE_API AUDEC_CapDevStop(AUDEC_CAP_DEV_HANDLE hCapDev);
extern void AUDEC_ENGINE_API AUDEC_CapDevClose(AUDEC_CAP_DEV_HANDLE hCapDev);

extern int AUDEC_ENGINE_API AUDEC_PlayDevOpen(int nPlayDevID,int nSampleRate,int nSamplesPerFrame,void*pUserData,AUDEC_PLAY_DEV_CB play_dev_cb,AUDEC_PLAY_DEV_HANDLE*phPlayDev);
extern int AUDEC_ENGINE_API AUDEC_PlayDevStart(AUDEC_PLAY_DEV_HANDLE hPlayDev);
extern void AUDEC_ENGINE_API AUDEC_PlayDevStop(AUDEC_PLAY_DEV_HANDLE hPlayDev);
extern void AUDEC_ENGINE_API AUDEC_PlayDevClose(AUDEC_PLAY_DEV_HANDLE hPlayDev);

#ifdef __cplusplus
}
#endif

#endif
