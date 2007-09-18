/* ======== SourceMM ========
 * Copyright (C) 2004-2007 Metamod:Source Development Team
 * No warranties of any kind
 *
 * License: zlib/libpng
 *
 * Author(s): David "BAILOPAN" Anderson
 * ============================
 */

#ifndef _INCLUDE_CSMM_API_H
#define _INCLUDE_CSMM_API_H

/**
 * @brief Header for CSmmAPI implementation
 * @file CSmmAPI.h
 */

#include "ISmmAPI.h"
#include <tier1/utldict.h>

struct UserMessage
{
	int size;
	const char *name;
};

typedef CUtlDict<UserMessage *, int> UserMsgDict;

typedef void (*CONPRINTF_FUNC)(const char *, ...);

namespace SourceMM
{
	class CSmmAPI : public ISmmAPI
	{
	public:
		CSmmAPI();
		~CSmmAPI();
	public:
		void LogMsg(ISmmPlugin *pl, const char *msg, ...);
	public:
		CreateInterfaceFn engineFactory(bool syn=true);
		CreateInterfaceFn physicsFactory(bool syn=true);
		CreateInterfaceFn fileSystemFactory(bool syn=true);
		CreateInterfaceFn serverFactory(bool syn=true);
		CGlobalVars *pGlobals();
		void SetLastMetaReturn(META_RES res);
		META_RES GetLastMetaReturn();
		IConCommandBaseAccessor *GetCvarBaseAccessor();
		bool RegisterConCmdBase(ISmmPlugin *plugin, ConCommandBase *pCommand);
		void UnregisterConCmdBase(ISmmPlugin *plugin, ConCommandBase *pCommand);
		void ConPrint(const char *fmt);
		void ConPrintf(const char *fmt, ...);
		bool RemotePrintingAvailable()
		{
			return CmdCacheSuccessful();
		}
		virtual void GetApiVersions(int &major, int &minor, int &plvers, int &plmin);
		virtual void GetShVersions(int &shvers, int &shimpl);
		virtual void AddListener(ISmmPlugin *plugin, IMetamodListener *pListener);
		virtual void *MetaFactory(const char *iface, int *ret, PluginId *id);
		virtual int FormatIface(char buffer[], unsigned int maxlength);
		virtual void *InterfaceSearch(CreateInterfaceFn fn, const char *iface, int max, int *ret);
		virtual const char *GetBaseDir();
		virtual void PathFormat(char *buffer, size_t len, const char *fmt, ...);
		void ClientConPrintf(edict_t *client, const char *fmt, ...);
		void *VInterfaceMatch(CreateInterfaceFn fn, const char *iface, int min=-1);
		void EnableVSPListener();
		int GetGameDLLVersion();
		int GetUserMessageCount();
		int FindUserMessage(const char *name, int *size=NULL);
		const char *GetUserMessage(int index, int *size=NULL);
		int GetVSPVersion();
	public:
		bool CacheCmds();
		bool CmdCacheSuccessful();
		void LoadAsVSP();
		bool VSPEnabled()
		{
			return m_VSP;
		}
		bool CacheUserMessages();
		bool MsgCacheSuccessful();
	private:
		META_RES m_Res;
		CONPRINTF_FUNC m_ConPrintf;
		bool m_CmdCache;
		bool m_VSP;
		int m_MsgCount;
		UserMsgDict m_UserMessages;
	};
};

extern SourceMM::CSmmAPI g_SmmAPI;

#define	CONMSG			g_SmmAPI.ConPrintf
#define CLIENT_CONMSG	g_SmmAPI.ClientConPrintf

#endif //_INCLUDE_CSMM_API_H
