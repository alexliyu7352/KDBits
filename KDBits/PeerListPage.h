#pragma once


// CPeerListPage �Ի���

class CPeerListPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPeerListPage)

public:
	CPeerListPage();
	virtual ~CPeerListPage();

// �Ի�������
	enum { IDD = IDD_PEERLISTPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
