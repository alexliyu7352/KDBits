// KDBitsDoc.h : CKDBitsDoc ��Ľӿ�
//


#pragma once


class CKDBitsDoc : public CDocument
{
protected: // �������л�����
	CKDBitsDoc();
	DECLARE_DYNCREATE(CKDBitsDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CKDBitsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


