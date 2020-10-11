// UPnpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UPnp.h"
#include "UPnpDlg.h"
#include "UPnP\upnpasynthreads.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUPnpDlg �Ի���




CUPnpDlg::CUPnpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUPnpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUPnpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUPnpDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CUPnpDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUPnpDlg ��Ϣ�������

BOOL CUPnpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUPnpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CUPnpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUPnpDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	WORD wVersionRequested = MAKEWORD( 2, 2 );
	WSADATA wsaData;

	WSAStartup( wVersionRequested, &wsaData );



CUPnpNatMapping mapping;

mapping.m_wInternalPort = 23333;				// Port mapping internal port
mapping.m_wExternalPort = 33333;				// Port mapping external port
mapping.m_strProtocol = _T("TCP");// Protocol-> TCP (UPNPNAT_PROTOCOL:UNAT_TCP) || UDP (UPNPNAT_PROTOCOL:UNAT_UDP)
mapping.m_strDescription = _T("ZMX__TEST");				// Port mapping description
//mapping.m_strInternalClient = _T("192.168.1.246");

/*
	CUPnpMgr Mgr;
	Mgr.AddNATPortMapping(mapping);
*/

	static CUPnpMgr	Mgr;
	CUPnpAsynThreads::AddNatPortMappingAsyn(&Mgr, mapping, 0, 0, 0, 0, FALSE);

	AfxMessageBox(L"OK");


//	OnOK();
}
