// PeerListPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KDBits.h"
#include "PeerListPage.h"


// CPeerListPage �Ի���

IMPLEMENT_DYNAMIC(CPeerListPage, CPropertyPage)

CPeerListPage::CPeerListPage()
	: CPropertyPage(CPeerListPage::IDD)
{
	m_psp.dwFlags &= ~PSP_USEICONID;   
	m_psp.dwFlags |= PSP_USEHICON;
	m_psp.dwFlags |= PSP_USETITLE;
	m_psp.hIcon    = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_psp.pszTitle = L"�����б�";
}

CPeerListPage::~CPeerListPage()
{
}

void CPeerListPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPeerListPage, CPropertyPage)
END_MESSAGE_MAP()


// CPeerListPage ��Ϣ�������
