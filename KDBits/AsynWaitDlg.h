#pragma once


// CAsynWaitDlg �Ի���

class CAsynWaitDlg : public CDialog
{
	DECLARE_DYNAMIC(CAsynWaitDlg)

public:
	CAsynWaitDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAsynWaitDlg();

// �Ի�������
	enum { IDD = IDD_ASYNWAITDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	tuple<CAsynWaitDlg *, boost::function<void (void)>, path> m_Tuple;
	afx_msg void OnDestroy();
	CString m_MsgText;
	BOOL    m_ParseError;
};

