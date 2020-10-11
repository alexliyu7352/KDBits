// ConfigPath.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KDBits.h"
#include "ConfigPath.h"
#include "pathselectdlg.h"
#include "configuration.h"

// CConfigPath �Ի���

IMPLEMENT_DYNAMIC(CConfigPath, CPropertyPage)

CConfigPath::CConfigPath()
	: CPropertyPage(CConfigPath::IDD)
	, m_NetGamePath(_T(""))
	, m_LocalGamePath(_T(""))
	, m_OtherPath(_T(""))
{

}

CConfigPath::~CConfigPath()
{
}

void CConfigPath::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NETGAME_PATH, m_NetGamePath);
	DDV_MaxChars(pDX, m_NetGamePath, 512);
	DDX_Text(pDX, IDC_LOCALGAME_PATH, m_LocalGamePath);
	DDV_MaxChars(pDX, m_LocalGamePath, 512);
	DDX_Text(pDX, IDC_OTHER_PATH, m_OtherPath);
	DDV_MaxChars(pDX, m_OtherPath, 512);
}


BEGIN_MESSAGE_MAP(CConfigPath, CPropertyPage)
	ON_BN_CLICKED(IDC_NETGAME_BRW, &CConfigPath::OnBnClickedNetgameBrw)
	ON_BN_CLICKED(IDC_LOCALGAME_BRW, &CConfigPath::OnBnClickedLocalgameBrw)
	ON_BN_CLICKED(IDC_OTHER_BRW, &CConfigPath::OnBnClickedOtherBrw)
END_MESSAGE_MAP()


// CConfigPath ��Ϣ�������

void CConfigPath::OnBnClickedNetgameBrw()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPathSelectDlg PathSelectDlg(this, L"��ѡ��һ��Ŀ¼");
	if(PathSelectDlg.DoModal())
	{
		m_NetGamePath = PathSelectDlg.m_strPath;
		UpdateData(FALSE);
	}
}

void CConfigPath::OnBnClickedLocalgameBrw()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPathSelectDlg PathSelectDlg(this, L"��ѡ��һ��Ŀ¼");
	if(PathSelectDlg.DoModal())
	{
		m_LocalGamePath = PathSelectDlg.m_strPath;
		UpdateData(FALSE);
	}
}

void CConfigPath::OnBnClickedOtherBrw()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPathSelectDlg PathSelectDlg(this, L"��ѡ��һ��Ŀ¼");
	if(PathSelectDlg.DoModal())
	{
		m_OtherPath = PathSelectDlg.m_strPath;
		UpdateData(FALSE);
	}
}

BOOL CConfigPath::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_NetGamePath   = g_Configuration.NetGamePath.native_directory_string().c_str();

	m_LocalGamePath = g_Configuration.LocalGamePath.native_directory_string().c_str();

	m_OtherPath     = g_Configuration.OtherPath.native_directory_string().c_str();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CConfigPath::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	g_Configuration.NetGamePath   = wcstombs(wstring(m_NetGamePath.GetBuffer()));
	g_Configuration.LocalGamePath = wcstombs(wstring(m_LocalGamePath.GetBuffer()));
	g_Configuration.OtherPath     = wcstombs(wstring(m_OtherPath.GetBuffer())); 

	if(!g_Configuration.Save())
	{
		AfxMessageBox(L"�޷��������õ������ļ�", MB_ICONERROR);
		return;
	}

	CPropertyPage::OnOK();
}
