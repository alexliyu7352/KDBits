// KDBitsDoc.cpp : CKDBitsDoc ���ʵ��
//

#include "stdafx.h"
#include "KDBits.h"

#include "KDBitsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKDBitsDoc

IMPLEMENT_DYNCREATE(CKDBitsDoc, CDocument)

BEGIN_MESSAGE_MAP(CKDBitsDoc, CDocument)
END_MESSAGE_MAP()


// CKDBitsDoc ����/����

CKDBitsDoc::CKDBitsDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CKDBitsDoc::~CKDBitsDoc()
{
}

BOOL CKDBitsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CKDBitsDoc ���л�

void CKDBitsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CKDBitsDoc ���

#ifdef _DEBUG
void CKDBitsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKDBitsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CKDBitsDoc ����
