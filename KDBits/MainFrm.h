// MainFrm.h : CMainFrame ��Ľӿ�
//


#pragma once

#include "TrueColorToolBar\TrueColorToolBar.h"

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:
	void setLayout();

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar  m_wndStatusBar;
	CTrueColorToolBar  m_wndToolBar;
	CSplitterWnd m_HSplitter;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	BOOL m_CreatedOK;
public:
	afx_msg void OnMainMenuConfig();
public:
	afx_msg void OnMainMenuNewTask();
	afx_msg void OnMainMenuMakefile();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};


