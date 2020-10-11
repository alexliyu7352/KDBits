#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TextProgressCtrl\TextProgressCtrl.h"

// CDownloadListSelectDlg �Ի���

class CDownloadListSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CDownloadListSelectDlg)

public:
	CDownloadListSelectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDownloadListSelectDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_DOWNLOAD_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbRule;
public:
	CListCtrl m_lcSelectList;
public:
	afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedOk();
public:
	virtual BOOL OnInitDialog();
public:
	vector< tuple<ResInfoNode, path> > m_GameList;
public:
	afx_msg void OnLvnItemchangedListDownloadlistSelect(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CEdit m_edtPath;
public:
	CStatic m_StaticView;
public:
	CTextProgressCtrl m_ProgressCtrl;
protected:
	void DownloadTorrentFile(string strHttpUrl);
	bool m_bQuitExecute;
public:
	afx_msg void OnBnClickedButtonBrowse();
	void UpdateListView(void);
private:
	int m_Index;
public:
	afx_msg void OnCbnSelchangeComboUpdaterule();
};
