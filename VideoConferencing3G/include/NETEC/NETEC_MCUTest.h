//NETEC_MCUTest.h
#ifndef __NETEC_MCUTEST_H__
#define __NETEC_MCUTEST_H__

#include <NETEC/NETEC_Export.h>

class NETEC_API NETEC_MCUTest
{
public:
	NETEC_MCUTest(void){};
	virtual~NETEC_MCUTest(void){};
public:
	/******************************************************************************
	* Start
	*描述：启动MCU测试
	*输入：	无
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int Start(void);

	/******************************************************************************
	* Stop
	*描述：停止MCU测试
	*输入：	无
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void Stop(void);

	/******************************************************************************
	* AddMCU
	*描述：添加要测试的MCU的IP地址和端口
	*输入：	cszMCUIP			-MCU的IP地址
			usMCUPort			-MCU的端口
	*输出： 无
	*返回值：成功返回测试标识，失败返回0
	*****************************************************************************/
	virtual unsigned long AddMCU(const char*cszMCUIP,unsigned short usMCUPort);
	
	/******************************************************************************
	* OnNETEC_MCUTestBegin
	*描述：MCU开始测试的回调
	*输入：	无
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_MCUTestBegin(void)=0;
	
	/******************************************************************************
	* OnNETEC_MCUTestBegin
	*描述：MCU某个地址开始测试的回调
	*输入：	ulTestID			-测试标识
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_MCUTestBegin(unsigned long ulTestID)=0;
	
	/******************************************************************************
	* OnNETEC_MCUTestTXBitrateChanged
	*描述：MCU某个地址上行带宽改变的回调
	*输入：	ulTestID			-测试标识
			nBitrate			-上行带宽【kbps】
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_MCUTestTXBitrateChanged(unsigned long ulTestID,int nBitrate)=0;
	
	/******************************************************************************
	* OnNETEC_MCUTestTXBitrateChanged
	*描述：MCU某个地址下行带宽改变的回调
	*输入：	ulTestID			-测试标识
			nBitrate			-下行带宽【kbps】
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_MCUTestRXBitrateChanged(unsigned long ulTestID,int nBitrate)=0;
	
	/******************************************************************************
	* OnNETEC_MCUTestRTTChanged
	*描述：MCU某个地址往返时间改变的回调
	*输入：	ulTestID			-测试标识
			nRTT				-往返时间【毫秒】
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_MCUTestRTTChanged(unsigned long ulTestID,unsigned long nRTT)=0;
	
	/******************************************************************************
	* OnNETEC_MCUTestEnd
	*描述：MCU某个地址结束测试的回调
	*输入：	ulTestID			-测试标识
			nMinTXBitrate		-最小上行带宽【kbps】
			nMaxTXBitrate		-最大上行带宽【kbps】
			nAvgTXBitrate		-平均上行带宽【kbps】
			nMinRXBitrate		-最小下行带宽【kbps】
			nMaxRXBitrate		-最大下行带宽【kbps】
			nAvgRXBitrate		-平均下行带宽【kbps】
			nMinRTT				-最小往返时间【毫秒】
			nMaxRTT				-最大往返时间【毫秒】
			nAvgRTT				-平均往返时间【毫秒】
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_MCUTestEnd(unsigned long ulTestID,int nMinTXBitrate,int nMaxTXBitrate,int nAvgTXBitrate,int nMinRXBitrate,int nMaxRXBitrate,int nAvgRXBitrate,unsigned long nMinRTT,unsigned long nMaxRTT,unsigned long nAvgRTT)=0;
	
	/******************************************************************************
	* OnNETEC_MCUTestEnd
	*描述：MCU结束测试的回调
	*输入：	无
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_MCUTestEnd(void)=0;
};


#endif
