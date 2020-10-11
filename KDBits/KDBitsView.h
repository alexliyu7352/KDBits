// KDBitsView.h : CKDBitsView ��Ľӿ�
//


#pragma once
#include "kdcontentsheet.h"


class CKDBitsView : public CView
{
protected: // �������л�����
	CKDBitsView();
	DECLARE_DYNCREATE(CKDBitsView)

// ����
public:
	CKDBitsDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CKDBitsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	CKDContentSheet m_sheet;
public:
	virtual void OnInitialUpdate();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMainMenuLoadGamelist();
public:
	afx_msg void OnMenuDownlistStartTask();
	afx_msg void OnMenuDownlistStopTask();
	afx_msg void OnMenuDownlistDeleteTask();
	afx_msg void OnMainMenuStartAll();
	afx_msg void OnMainMenuStopAll();
	afx_msg void OnMainMenuDeleteAll();
};

#ifndef _DEBUG  // KDBitsView.cpp �еĵ��԰汾
inline CKDBitsDoc* CKDBitsView::GetDocument() const
   { return reinterpret_cast<CKDBitsDoc*>(m_pDocument); }
#endif
