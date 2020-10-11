#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CConfigNetwork �Ի���

class CConfigNetwork : public CPropertyPage
{
	DECLARE_DYNAMIC(CConfigNetwork)

public:
	CConfigNetwork();
	virtual ~CConfigNetwork();

// �Ի�������
	enum { IDD = IDD_CONFIGNETWORK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
public:
	virtual BOOL OnInitDialog();
public:
	CString m_UpLimit;
public:
	virtual void OnOK();
public:
	CString m_DownLimit;
public:
	CString m_ListenPort;
public:
	CString m_ProxyIP;
public:
	CString m_ProxyPort;
public:
	CString m_ProxyUserName;
public:
	CString m_ProxyPassword;
public:
	afx_msg void OnEnChangeUploadlimit();
public:
	afx_msg void OnEnChangeDownlimit();
public:
	afx_msg void OnEnChangeListenPort();
public:
	afx_msg void OnEnChangeProxyPortEdit();
public:
	CSpinButtonCtrl m_UpLimitSpin;
public:
	CSpinButtonCtrl m_DownLimitSpin;
public:
	CSpinButtonCtrl m_ListenPortSpin;
public:
	BOOL m_bOpenUPnP;
public:
	BOOL m_bJoinDHT;
	CComboBox m_cbProxType;
	afx_msg void OnCbnSelchangeProxyTypeCombo();
	afx_msg void OnBnClickedProxyIsValidateCheck();
	afx_msg void OnEnKillfocusProxyIpEdit();
};
