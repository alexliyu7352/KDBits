#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPreDeleteDownNodeDlg �Ի���

class CPreDeleteDownNodeDlg : public CDialog
{
	DECLARE_DYNAMIC(CPreDeleteDownNodeDlg)

public:
	CPreDeleteDownNodeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPreDeleteDownNodeDlg();

// �Ի�������
	enum { IDD = IDD_PREDELETEDOWNNODEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bDelFileThenDelTask;
	vector< pair<string, path> > m_NameList;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CListCtrl m_lcNodeList;
};
