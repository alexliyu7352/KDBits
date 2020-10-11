// PreDownloadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KDBits.h"
#include "PreDownloadDlg.h"


// CPreDownloadDlg �Ի���

IMPLEMENT_DYNAMIC(CPreDownloadDlg, CDialog)

CPreDownloadDlg::CPreDownloadDlg(CWnd* pParent, torrent_info & t, PreDownloadProperty & PreDownProperty)
	: CDialog(CPreDownloadDlg::IDD, pParent), m_GeneralPage(t, PreDownProperty), m_OtherPage(t), m_SetupPage(PreDownProperty)
{
}

CPreDownloadDlg::~CPreDownloadDlg()
{
}

void CPreDownloadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPreDownloadDlg, CDialog)
END_MESSAGE_MAP()


// CPreDownloadDlg ��Ϣ�������

BOOL CPreDownloadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);		// Set small icon

	m_Sheet.AddPage(&m_GeneralPage);
	m_Sheet.AddPage(&m_OtherPage);
	m_Sheet.AddPage(&m_SetupPage);
	m_Sheet.Create(this, WS_CHILD | WS_VISIBLE, WS_EX_CONTROLPARENT);

	m_Sheet.SetWindowPos(NULL, 5, 5, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPreDownloadDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(IsWindow(m_GeneralPage)) m_GeneralPage.OnOK();
	if(IsWindow(m_OtherPage))   m_OtherPage.OnOK();
	if(IsWindow(m_SetupPage))   m_SetupPage.OnOK();

	CDialog::OnOK();
}
