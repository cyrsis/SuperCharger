#ifndef __RWL_H__
#define __RWL_H__

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RWL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RWL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef RWL_EXPORTS
#define RWL_API __declspec(dllexport)
#else
#define RWL_API __declspec(dllimport)
#endif

#include <windef.h>
#include <stdio.h>

#define HOUSE_NONE 0
#define HOUSE_INIT	1
#define HOUSE_XFILE	2
#define ERR_BASE 100000
#define ERR_CCHS_BASE 1000
#define ERR_CCHS_FILEID	5
#define ERR_CCHS_RECID	6
#define ERR_CCHS_RECSZ	7
#define ERR_CCHS_RECRD	8
#define ERR_CCHS_RESP	9
#define ERR_NOERR			0
#define	ERR_COM_ERR			1
#define	ERR_FILE_OPEN		2
//#define ERR_INVPARAM		3 // 362 ITRM Action List
#define	ERR_FILE_COM		1 // Same as ERR_COM_ERR, timeout reading R/W
#define ERR_FILE_READ		4
#define ERR_COM_INVRESP		5
#define ERR_FILE_WRITE		6
#define	ERR_FILE_CHECKSUM	10
#define ERR_DEFER_NOMORE	55
#define ERR_DEFER_STATE		56
#define ERR_FIRM_NONE		98
#define ERR_FIRM_DONE		99
#define ERR_OPEN_AR			101
#define ERR_OPEN_UD			102
#define AMF_MESSAGE_LEN		100

#pragma pack (push, 1)
	typedef struct {
		unsigned int	DevID; 	/* Device ID */
		unsigned int	OperID;	/* Operator ID */
		unsigned int	DevTime;	/* Device Time */
		unsigned int	CompID;	/* Company ID */
		unsigned int	KeyVer;	/* Key Version */
		unsigned int	EODVer;	/* EOD Version */
		unsigned int	BLVer;	/* Blacklist Version */
		unsigned int	FIRMVer;	/* Firmware Version */
		unsigned int	CCHSVer;	/* CCHS MSG ID */
		unsigned int	CSSer;		/* CS Serial #, Loc ID */
		unsigned int    IntBLVer;   /* Interim Blacklist Version; Added 2002/12/09 */
		unsigned int	FuncBLVer;
	} stDevVer;

	typedef struct {
		unsigned int	AlertCode;
		unsigned char	ChineseMsgUTF16[AMF_MESSAGE_LEN];
		unsigned char	EnglishMsg[AMF_MESSAGE_LEN];
		unsigned char 	ChineseMsgBig5[AMF_MESSAGE_LEN];
		unsigned char	ChineseMsgUTF8[AMF_MESSAGE_LEN*2];
	} stAlertMsgEntry;
#pragma pack (pop)

extern "C" {
RWL_API int __stdcall Deduct(int, BYTE *);
RWL_API int __stdcall AddValue(int, unsigned char, BYTE *);
RWL_API int __stdcall InitComm(unsigned char, int);
RWL_API int __stdcall Poll(unsigned char, unsigned char, char *);
#ifndef FIRM_CMC	//mantis #7771: Enhancement of PollEx() function in Windows RWL
RWL_API int __stdcall PollEx(unsigned char, unsigned char, char *);			//mantis #7175, mantis #7603 Project Phoenix - Read Transfer block
#endif
RWL_API int __stdcall PortClose();
RWL_API int __stdcall Reset();
RWL_API int __stdcall DeferDeduct(BYTE, int, BYTE *);
RWL_API int __stdcall WriteID(unsigned int);
RWL_API int __stdcall TxnAmt(int, int, BYTE, BYTE);
RWL_API int __stdcall XFile(TCHAR *);
RWL_API int __stdcall TimeVer(BYTE *);
RWL_API int __stdcall HouseKeeping();
RWL_API int __stdcall WriteLoyalEx(BYTE bSchemeId, BYTE *p, BYTE bLen);
RWL_API int __stdcall ReadLoyalEx(BYTE bSchemeId, BYTE *p, BYTE *pbLen);
RWL_API int __stdcall GetExtraInfo(unsigned int, unsigned int, unsigned char *);
RWL_API int __stdcall InitActionList();
RWL_API int __stdcall GetSysInfo(BYTE *bInfo); // End 362 ITRM Blacklist Enhancement
RWL_API int __stdcall ActionCheck(DWORD dwCom, DWORD dwParam, DWORD *dwResult);
RWL_API int __stdcall ActionUpdate(BYTE *bCom, BYTE *bRes);
RWL_API int __stdcall GetActionResult(unsigned char *ucResult);

RWL_API int __stdcall ReadSPB(unsigned char*, unsigned char*); // FED_CR0131
RWL_API int __stdcall WriteSPB(unsigned char*, unsigned char, unsigned char); // FED_CR0131
RWL_API int __stdcall InitSPB(unsigned char*); // FED_CR0131
}

#endif // __RWL_H__