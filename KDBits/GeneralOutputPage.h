#pragma once


// CGeneralOutputPage �Ի���

class CGeneralOutputPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CGeneralOutputPage)

public:
	CGeneralOutputPage();
	virtual ~CGeneralOutputPage();

// �Ի�������
	enum { IDD = IDD_GENERALOUTPUTPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
