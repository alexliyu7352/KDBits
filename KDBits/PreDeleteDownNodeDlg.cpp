// PreDeleteDownNodeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KDBits.h"
#include "PreDeleteDownNodeDlg.h"


// CPreDeleteDownNodeDlg �Ի���

IMPLEMENT_DYNAMIC(CPreDeleteDownNodeDlg, CDialog)

CPreDeleteDownNodeDlg::CPreDeleteDownNodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPreDeleteDownNodeDlg::IDD, pParent)
	, m_bDelFileThenDelTask(FALSE)
{

}

CPreDeleteDownNodeDlg::~CPreDeleteDownNodeDlg()
{
}

void CPreDeleteDownNodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_DELETEDOWNNODE_DELEFILE_CHECK, m_bDelFileThenDelTask);
	DDX_Control(pDX, IDC_DELETEDOWNNODE_NODELIST_LIST, m_lcNodeList);
}


BEGIN_MESSAGE_MAP(CPreDeleteDownNodeDlg, CDialog)
END_MESSAGE_MAP()


// CPreDeleteDownNodeDlg ��Ϣ�������

BOOL CPreDeleteDownNodeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);		// Set small icon

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_lcNodeList.InsertColumn(0, L"��Ŀ", 0, 120);

	m_lcNodeList.InsertColumn(1, L"�ļ�(Ŀ¼)", 0, 300);

	ListView_SetExtendedListViewStyle(m_lcNodeList, LVS_EX_FULLROWSELECT|LVS_EX_LABELTIP|LVS_EX_GRIDLINES);

	for (vector< pair<string, path> >::size_type i = 0; i < m_NameList.size(); i++)
	{
		CString strText;
		strText = m_NameList[i].first.c_str();
		m_lcNodeList.InsertItem(i, strText);
		strText = m_NameList[i].second.native_directory_string().c_str();
		m_lcNodeList.SetItemText(i, 1, strText);
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPreDeleteDownNodeDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(TRUE);
	CDialog::OnOK();
}
