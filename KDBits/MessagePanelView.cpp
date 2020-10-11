// MessagePanelView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KDBits.h"
#include "MessagePanelView.h"


// CMessagePanelView

IMPLEMENT_DYNCREATE(CMessagePanelView, CView)

CMessagePanelView::CMessagePanelView() : m_Sheet(L"")
{

}

CMessagePanelView::~CMessagePanelView()
{
}

BEGIN_MESSAGE_MAP(CMessagePanelView, CView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMessagePanelView ��ͼ

void CMessagePanelView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CMessagePanelView ���

#ifdef _DEBUG
void CMessagePanelView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMessagePanelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMessagePanelView ��Ϣ�������

void CMessagePanelView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	m_Sheet.Create(this, WS_CHILD | WS_VISIBLE, 0);
	//ʹѡ��İ�ť������
	::SetWindowLong(m_Sheet.GetTabControl()->m_hWnd, GWL_STYLE, ::GetWindowLong(m_Sheet.GetTabControl()->m_hWnd, GWL_STYLE)|TCS_BOTTOM);
	if(m_Sheet.m_hWnd)
		m_Sheet.ShowWindow(SW_MAXIMIZE);//��ʾѡ�
}

void CMessagePanelView::OnSize(UINT nType, int cx, int cy)
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
		CWnd * ptab = m_Sheet.GetTabControl();
		if(ptab != NULL)
		{
			ptab->ScreenToClient(&rect);
			ptab->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER|SWP_NOACTIVATE);
			//��PropertySheet�Զ�����page�Ĵ�С
			m_Sheet.SetActivePage(m_Sheet.GetActiveIndex());
		}
	}
}
