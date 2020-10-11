#pragma once
#include "afxwin.h"
#include "afxcmn.h"

extern struct PreDownloadProperty;
extern enum DOWN_SETUP;
// CPreDownloadSetupPage �Ի���

class CPreDownloadSetupPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPreDownloadSetupPage)

public:
	CPreDownloadSetupPage(PreDownloadProperty & PreDownProperty);
	virtual ~CPreDownloadSetupPage();

// �Ի�������
	enum { IDD = IDD_PREDOWNLOADSETUPPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_UploadLimit;
	CString m_DownloadLimit;
	CComboBox m_cbRunSetup;
	BOOL m_bPreAlloc;
	virtual BOOL OnInitDialog();
	CSpinButtonCtrl m_UploadLimitSpin;
	CSpinButtonCtrl m_DownloadLimitSpin;
	afx_msg void OnEnChangeSetupUploadlimit();
	afx_msg void OnEnChangeSetupDownlimit();
	virtual void OnOK();

	PreDownloadProperty & m_PreDownProperty;
};
