#pragma once
#include "kdpanelsheet.h"


// CMessagePanelView ��ͼ

class CMessagePanelView : public CView
{
	DECLARE_DYNCREATE(CMessagePanelView)

protected:
	CMessagePanelView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMessagePanelView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	CKDPanelSheet m_Sheet;
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
