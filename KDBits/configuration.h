
#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "DownloadList.h"

class Configuration 
{
public:

	int    UpLimit, DownLimit;					// �ϴ������ص��ٶ�
	USHORT ListenPort;							// �����˿�
	bool   OpenUPnP, JoinDHT;					// �Ƿ�����UPnP,�Ƿ����DHT

	bool   PreAlloc, DelFileThenDelTask;		// ����ǰԤ�ȷ�����̿ռ�, ɾ����������ʱͬʱɾ���ļ�
	bool   DefaultClient, AutoRun;				// ����ΪĬ��BT�ͻ���, ϵͳ����ʱ�Զ�����
	bool   AutoUpdateNewVersion, ReCheckDataCalcSum; // ����ʱ�Զ����汾����, �ϵ�����ʱ���¼������������
	DOWN_SETUP RunSetup;						// ���������ػ����Ժ�����
	int    MaxTaskNum;							// ���ͬʱ���ص�������
	int    ProtectDiskSize, DiskCacheSize;		// �����̿ռ����ָ��ֵ��ֹͣ����(��λ:MB), ���̻����С(��λKB)

	string ProxyIP, ProxyPort, ProxyUserName, ProxyPassword;	//������������

	boost::filesystem::path NetGamePath;	// ������Ϸ����·��
	boost::filesystem::path LocalGamePath;	// ������Ϸ����·��
	boost::filesystem::path OtherPath;		// ������Դ����·��

	Configuration();

	bool Load();
	bool Save();
};

extern Configuration g_Configuration;

#endif
