#pragma once
#include "afxwin.h"


// CPreDownloadOtherPage �Ի���

class CPreDownloadOtherPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPreDownloadOtherPage)

public:
	CPreDownloadOtherPage(torrent_info & t);
	virtual ~CPreDownloadOtherPage();

// �Ի�������
	enum { IDD = IDD_PREDOWNLOADOTHERPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	torrent_info &m_TorrentInfo;
public:
	CEdit m_edtComment;
public:
	CEdit m_edtCreator;
public:
	CEdit m_edtUrlList;
};
