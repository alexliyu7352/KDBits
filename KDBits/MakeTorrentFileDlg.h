#pragma once


// CMakeTorrentFileDlg �Ի���

class CMakeTorrentFileDlg : public CDialog
{
	DECLARE_DYNAMIC(CMakeTorrentFileDlg)

public:
	CMakeTorrentFileDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMakeTorrentFileDlg();

// �Ի�������
	enum { IDD = IDD_MAKETORRENTFILEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMktBrwButton();
	CString m_strDirFileType;
	CString m_strPath;
	CString m_strPieceSize;
	CString m_strTitle;
	CString m_strUrlList;
	CString m_strCreator;
	CString m_strComment;
	BOOL m_bNotAllowDHT;
	afx_msg void OnBnClickedMktAllowDhtRadio();
	afx_msg void OnBnClickedMktUnallowDhtRadio();
	afx_msg void OnBnClickedOk();
};
