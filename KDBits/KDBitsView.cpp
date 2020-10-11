// KDBitsView.cpp : CKDBitsView ���ʵ��
//

#include "stdafx.h"
#include "KDBits.h"

#include "KDBitsDoc.h"
#include "KDBitsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKDBitsView

IMPLEMENT_DYNCREATE(CKDBitsView, CView)

BEGIN_MESSAGE_MAP(CKDBitsView, CView)
	ON_WM_SIZE()
	ON_COMMAND(ID_MAIN_MENU_LOAD_GAMELIST, &CKDBitsView::OnMainMenuLoadGamelist)
	ON_COMMAND(ID_MENU_DOWNLIST_START_TASK, &CKDBitsView::OnMenuDownlistStartTask)
	ON_COMMAND(ID_MENU_DOWNLIST_STOP_TASK, &CKDBitsView::OnMenuDownlistStopTask)
	ON_COMMAND(ID_MENU_DOWNLIST_DELETE_TASK, &CKDBitsView::OnMenuDownlistDeleteTask)
	ON_COMMAND(ID_MAIN_MENU_START_ALL, &CKDBitsView::OnMainMenuStartAll)
	ON_COMMAND(ID_MAIN_MENU_STOP_ALL, &CKDBitsView::OnMainMenuStopAll)
	ON_COMMAND(ID_MAIN_MENU_DELETE_ALL, &CKDBitsView::OnMainMenuDeleteAll)
END_MESSAGE_MAP()

// CKDBitsView ����/����

CKDBitsView::CKDBitsView() : m_sheet(L"")
{
	// TODO: �ڴ˴���ӹ������

}

CKDBitsView::~CKDBitsView()
{
}

BOOL CKDBitsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CKDBitsView ����

void CKDBitsView::OnDraw(CDC* /*pDC*/)
{
	CKDBitsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CKDBitsView ���

#ifdef _DEBUG
void CKDBitsView::AssertValid() const
{
	CView::AssertValid();
}

void CKDBitsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKDBitsDoc* CKDBitsView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKDBitsDoc)));
	return (CKDBitsDoc*)m_pDocument;
}
#endif //_DEBUG


// CKDBitsView ��Ϣ�������

void CKDBitsView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	m_sheet.Create(this, WS_CHILD | WS_VISIBLE, 0);
	if(m_sheet.m_hWnd)
		m_sheet.ShowWindow(SW_MAXIMIZE);//��ʾѡ�
}

void CKDBitsView::OnSize(UINT nType, int cx, int cy)
{
	// TODO: �ڴ˴������Ϣ����������
	ShowWindow(SW_MAXIMIZE);
	CWnd *psheet = GetWindow(GW_CHILD);//m_sheet��resultview��Ψһ�����Ӵ���
	if(psheet != NULL)
	{
		CRect rect;
		GetWindowRect(&rect);
		psheet->ScreenToClient(&rect);
		psheet->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		CWnd * ptab = m_sheet.GetTabControl();
		if(ptab != NULL)
		{
			ptab->ScreenToClient(&rect);
			ptab->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER|SWP_NOACTIVATE);
			//��PropertySheet�Զ�����page�Ĵ�С
			m_sheet.SetActivePage(m_sheet.GetActiveIndex());
		}
	}
}

void CKDBitsView::OnMainMenuLoadGamelist()
{
	// TODO: �ڴ���������������
	m_sheet.ReloadGameList();
}

void CKDBitsView::OnMenuDownlistStartTask()
{
	// TODO: �ڴ���������������
	if (::IsWindow(m_sheet.m_DownloadListPage))
	{
		m_sheet.m_DownloadListPage.SendMessage(WM_COMMAND, ID_MENU_DOWNLIST_START_TASK);
	}
}

void CKDBitsView::OnMenuDownlistStopTask()
{
	// TODO: �ڴ���������������
	if (::IsWindow(m_sheet.m_DownloadListPage))
	{
		m_sheet.m_DownloadListPage.SendMessage(WM_COMMAND, ID_MENU_DOWNLIST_STOP_TASK);
	}
}

void CKDBitsView::OnMenuDownlistDeleteTask()
{
	// TODO: �ڴ���������������
	if (::IsWindow(m_sheet.m_DownloadListPage))
	{
		m_sheet.m_DownloadListPage.SendMessage(WM_COMMAND, ID_MENU_DOWNLIST_DELETE_TASK);
	}
}

void CKDBitsView::OnMainMenuStartAll()
{
	// TODO: �ڴ���������������
	m_sheet.m_DownloadListPage.EventStartAllTask();
}

void CKDBitsView::OnMainMenuStopAll()
{
	// TODO: �ڴ���������������
	m_sheet.m_DownloadListPage.EventStopAllTask();
}

void CKDBitsView::OnMainMenuDeleteAll()
{
	// TODO: �ڴ���������������
	m_sheet.m_DownloadListPage.EventDeleteAllTask();
}
