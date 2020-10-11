#pragma once
#include "afxdlgs.h"
#include "predownloadgeneralpage.h"
#include "predownloadotherpage.h"
#include "predownloadsetuppage.h"


// CPreDownloadDlg �Ի���

class CPreDownloadDlg : public CDialog
{
	DECLARE_DYNAMIC(CPreDownloadDlg)

public:
	CPreDownloadDlg(CWnd* pParent, torrent_info & t, PreDownloadProperty & PreDownProperty);   // ��׼���캯��
	virtual ~CPreDownloadDlg();

// �Ի�������
	enum { IDD = IDD_PREDOWNLOADDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	CPropertySheet m_Sheet;
public:
	CPreDownloadGeneralPage m_GeneralPage;
public:
	virtual BOOL OnInitDialog();
public:
	CPreDownloadOtherPage m_OtherPage;
public:
	CPreDownloadSetupPage m_SetupPage;
protected:
	virtual void OnOK();
};
