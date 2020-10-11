#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "puptext\dialogtip.h"


// CConfigDisk �Ի���

class CConfigDisk : public CPropertyPage
{
	DECLARE_DYNAMIC(CConfigDisk)

public:
	CConfigDisk();
	virtual ~CConfigDisk();

// �Ի�������
	enum { IDD = IDD_CONFIGDISK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bPreAlloc;
	BOOL m_bDelFileThenDelTask;
	BOOL m_bDefaultClient;
	BOOL m_bAutoRun;
	BOOL m_bAutoUpdateNewVersion;
	BOOL m_bReCheckDataCalcSum;
	CString m_strMaxTaskNum;
	CSpinButtonCtrl m_MaxTaskSpin;
	CComboBox m_cbRunSetup;
	CComboBox m_cbProtectDiskSize;
	CComboBox m_cbDiskCacheSize;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEnChangeConfigdiskMaxtaskEdit();
protected:
	CDialogTipHandler m_ReCheckDataCalcSumTip;
};
