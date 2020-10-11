// ResListPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KDBits.h"
#include "ResListPage.h"
#include "DownloadListSelectDlg.h"
#include "configuration.h"

RES_LIST g_ResInfoList;

// CResListPage �Ի���

IMPLEMENT_DYNAMIC(CResListPage, CPropertyPage)

CResListPage::CResListPage() : CPropertyPage(CResListPage::IDD)
{
}

CResListPage::~CResListPage()
{
}

void CResListPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NETGAMELIST, m_ResListCtrl);
}


BEGIN_MESSAGE_MAP(CResListPage, CPropertyPage)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_NETGAMELIST, &CResListPage::OnLvnGetdispinfoNetgamelist)
	ON_NOTIFY(NM_RCLICK, IDC_NETGAMELIST, &CResListPage::OnNMRclickNetgamelist)
	ON_COMMAND(ID_RES_DOWNLOAD, &CResListPage::OnResDownload)
	ON_COMMAND(ID_RES_PROPERTY, &CResListPage::OnResProperty)
	ON_NOTIFY(NM_DBLCLK, IDC_NETGAMELIST, &CResListPage::OnNMDblclkNetgamelist)
	ON_MESSAGE(WM_SORTLIST, &CResListPage::OnSortList)
END_MESSAGE_MAP()


// CResListPage ��Ϣ�������


LRESULT CResListPage::OnSortList(WPARAM wParam, LPARAM lParam)
{
	BOOL bSortAscending = (BOOL)wParam;
	int iSortColumn = (int)lParam;

	switch(iSortColumn)
	{
	case 0:
		{
			if (bSortAscending)
			{
				std::sort(
					m_ResInfoList.begin(),
					m_ResInfoList.end(),
					bind(
					std::greater<string::size_type>(), 
					bind(&string::length, bind(&ResInfoNode::Name, _1)),
					bind(&string::length, bind(&ResInfoNode::Name, _2))
					)
				);
			}
			else
			{
				std::sort(
					m_ResInfoList.begin(),
					m_ResInfoList.end(),
					bind(
					std::less<string::size_type>(), 
					bind(&string::length, bind(&ResInfoNode::Name, _1)),
					bind(&string::length, bind(&ResInfoNode::Name, _2))
					)
				);
			}
		}
		break;
	case 2:
		{
			if (bSortAscending)
			{
				std::sort(
					m_ResInfoList.begin(),
					m_ResInfoList.end(),
					bind(
					std::greater<double>(), 
					bind(&boost::lexical_cast<double, string>, bind(&ResInfoNode::Ver, _1)),
					bind(&boost::lexical_cast<double, string>, bind(&ResInfoNode::Ver, _2))
					)
				);
			}
			else
			{
				std::sort(
					m_ResInfoList.begin(),
					m_ResInfoList.end(),
					bind(
					std::less<double>(), 
					bind(&boost::lexical_cast<double, string>, bind(&ResInfoNode::Ver, _1)),
					bind(&boost::lexical_cast<double, string>, bind(&ResInfoNode::Ver, _2))
					)
				);
			}
		}
		break;
	case 3:
		{
			if (bSortAscending)
			{
				std::sort(
					m_ResInfoList.begin(),
					m_ResInfoList.end(),
					bind(
					std::greater<double>(), 
					bind(&ResInfoNode::Size, _1),
					bind(&ResInfoNode::Size, _2)
					)
				);
			}
			else
			{
				std::sort(
					m_ResInfoList.begin(),
					m_ResInfoList.end(),
					bind(
					std::less<double>(),
					bind(&ResInfoNode::Size, _1),
					bind(&ResInfoNode::Size, _2)
					)
				);
			}
		}
	    break;
	case 4:
		{
			if (bSortAscending)
			{
				std::sort(
					m_ResInfoList.begin(),
					m_ResInfoList.end(),
					bind(
					std::greater<ptime>(),
					bind(&ResInfoNode::Time, _1),
					bind(&ResInfoNode::Time, _2)
					)
				);
			}
			else
			{
				std::sort(
					m_ResInfoList.begin(),
					m_ResInfoList.end(),
					bind(
					std::less<ptime>(),
					bind(&ResInfoNode::Time, _1),
					bind(&ResInfoNode::Time, _2)
					)
				);
			}
		}
	    break;
	}
	UpdateList();
	return 0;
}

void CResListPage::OnSize(UINT nType, int cx, int cy)
{
//	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	ShowWindow(SW_MAXIMIZE);

	CWnd * pchild = GetWindow(GW_CHILD);//ֻ��һ�������Ӵ���
	if(pchild != NULL)
	{
		CRect rect;
		GetWindowRect(&rect);
		pchild->ScreenToClient(&rect);
		pchild->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER|SWP_NOACTIVATE);
	}
}

BOOL CResListPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_Image.Create(16, 16, TRUE|ILC_COLOR24, 2, 1);
	m_ResListCtrl.SetImageList(&m_Image, LVSIL_SMALL);
	m_Image.Add(AfxGetApp()-> LoadIcon(IDR_MAINFRAME));
	m_Image.Add(AfxGetApp()-> LoadIcon(IDR_KDBitsTYPE));

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	WCHAR strBuffer[MAX_PATH];

	LoadString(NULL, IDS_STRING_RES_NAME, strBuffer, sizeof(strBuffer));
	m_ResListCtrl.InsertColumn(0, strBuffer, 0, 250);
	LoadString(NULL, IDS_STRING_RES_TYPE, strBuffer, sizeof(strBuffer));
	m_ResListCtrl.InsertColumn(1, strBuffer, 0, 80);
	LoadString(NULL, IDS_STRING_RES_VER, strBuffer, sizeof(strBuffer));
	m_ResListCtrl.InsertColumn(2, strBuffer, 0, 70);
	LoadString(NULL, IDS_STRING_RES_SIZE, strBuffer, sizeof(strBuffer));
	m_ResListCtrl.InsertColumn(3, strBuffer, 0, 100);
	LoadString(NULL, IDS_STRING_RES_TIME, strBuffer, sizeof(strBuffer));
	m_ResListCtrl.InsertColumn(4, strBuffer, 0, 150);
	LoadString(NULL, IDS_STRING_RES_RULE, strBuffer, sizeof(strBuffer));
	m_ResListCtrl.InsertColumn(5, strBuffer, 0, 100);
	LoadString(NULL, IDS_STRING_RES_STATE, strBuffer, sizeof(strBuffer));
	m_ResListCtrl.InsertColumn(6, strBuffer, 0, 100);

	ListView_SetExtendedListViewStyle(m_ResListCtrl.m_hWnd, LVS_EX_FULLROWSELECT|LVS_EX_LABELTIP|LVS_EX_GRIDLINES);

	UpdateList();//�����б�

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CResListPage::OnLvnGetdispinfoNetgamelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *di = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(di->item.iItem < (int)m_ResInfoList.size() && di->item.iSubItem < (int)COLUMN_NUMBER)
	{
		if (m_ResInfoList[di->item.iItem].bNew)
		{
			di->item.iImage = 0;
		}
		else
		{
			di->item.iImage = 1;
		}
		di->item.pszText = (LPTSTR)m_ResInfoList[di->item.iItem].cols[di->item.iSubItem].c_str();
	}
	*pResult = 0;
}

void CResListPage::OnNMRclickNetgamelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	LPNMITEMACTIVATE pNmi = (LPNMITEMACTIVATE)pNMHDR;
	CMenu clMenu;
	clMenu.LoadMenu(IDR_MENU_RESLIST_POP);
	CMenu* ctPopMenu = clMenu.GetSubMenu(0);
	if (pNmi->iItem == -1)		//ûѡ����Ŀ
	{
		::EnableMenuItem(ctPopMenu->m_hMenu, ID_RES_DOWNLOAD, TRUE);
		::EnableMenuItem(ctPopMenu->m_hMenu, ID_RES_PROPERTY, TRUE);
	}
	else
	{
		::EnableMenuItem(ctPopMenu->m_hMenu, ID_RES_DOWNLOAD, FALSE);
		::EnableMenuItem(ctPopMenu->m_hMenu, ID_RES_PROPERTY, FALSE);	
	}
	POINT stPt;
	GetCursorPos(&stPt);
	ctPopMenu->TrackPopupMenu(TPM_LEFTALIGN,stPt.x,stPt.y,this);

	*pResult = 0;
}

void CResListPage::OnResDownload()
{
	// TODO: �ڴ���������������

	if (m_ResListCtrl.GetSelectedCount() > 0)
	{
		CDownloadListSelectDlg Dlg;
		POSITION pos = m_ResListCtrl.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			while (pos)
			{
				int nItem = m_ResListCtrl.GetNextSelectedItem(pos);
				ResInfoNode & ResNode = m_ResInfoList[nItem];
				path FilePath;
				if (ResNode.Type == "������Ϸ")
				{
					FilePath = g_Configuration.NetGamePath/ResNode.Name;
				}
				else if (ResNode.Type == "������Ϸ")
				{
					FilePath = g_Configuration.LocalGamePath/ResNode.Name;
				}
				else if (ResNode.Type == "����")
				{
					FilePath = g_Configuration.OtherPath/ResNode.Name;
				}
				Dlg.m_GameList.push_back(boost::make_tuple(ResNode, FilePath));
			}
		}
		if(Dlg.DoModal() == IDOK)
		{
			try
			{
				for (vector< tuple<ResInfoNode, path> >::size_type i = 0; i < Dlg.m_GameList.size(); i++)
				{
					tuple<ResInfoNode, path> & tupleNode = Dlg.m_GameList[i];
					PreDownloadProperty PreDownProperty = 
					{
						tupleNode.get<1>().branch_path(),
						-1,
						-1,
						g_Configuration.RunSetup,
						g_Configuration.PreAlloc,
						true,
						g_Configuration.MaxTaskNum,
						tupleNode.get<0>().UpdateRule
					};
					g_DownloadList.AddTask(path(tupleNode.get<0>().DownloadUrl).leaf(), PreDownProperty, NULL, &AsynWaitHandler);
				}
			}
			catch (wstring & strMsg)
			{
				AfxMessageBox(strMsg.c_str(), MB_ICONERROR);
			}
			catch (libtorrent::invalid_encoding&)
			{
				AfxMessageBox(L"��Ч�������ļ�", MB_ICONERROR);
			}
			catch (boost::filesystem::filesystem_error&)
			{
				AfxMessageBox(L"�ļ���������ʧ��", MB_ICONERROR);
			}
			catch (libtorrent::duplicate_torrent&)
			{
				AfxMessageBox(L"�Ѿ�������ͬ��������Ŀ", MB_ICONERROR);
			}
			catch (...)
			{
				AfxMessageBox(L"δ֪����", MB_ICONERROR);
			}
		}
	}
}

void CResListPage::OnResProperty()
{
	// TODO: �ڴ���������������
}

void CResListPage::OnNMDblclkNetgamelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnResDownload();
	*pResult = 0;
}

void CResListPage::SetTypeClass(LIST_TYPE ListType)
{
	m_ListType = ListType;

	m_ResInfoList.clear();

	switch(m_ListType)
	{
	case TYPE_NETGAME:
		static WCHAR strNetGameTitle[MAX_PATH];
		LoadString(NULL, IDS_STRING_TITLE_NETGAME, strNetGameTitle, sizeof(strNetGameTitle));
		m_psp.hIcon    = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		m_psp.pszTitle = strNetGameTitle;
		for (RES_LIST::const_iterator i = g_ResInfoList.begin(); i != g_ResInfoList.end(); ++i)
		{
			if (i->Type == "������Ϸ")
			{
				m_ResInfoList.push_back(*i);
			}
		}
		break;

	case TYPE_LOCALGAME:
		static WCHAR strLocalGameTitle[MAX_PATH];
		LoadString(NULL, IDS_STRING_TITLE_LOCALGAME, strLocalGameTitle, sizeof(strLocalGameTitle));
		m_psp.hIcon    = AfxGetApp()->LoadIcon(IDR_KDBitsTYPE);
		m_psp.pszTitle = strLocalGameTitle;
		for (RES_LIST::const_iterator i = g_ResInfoList.begin(); i != g_ResInfoList.end(); ++i)
		{
			if (i->Type == "������Ϸ")
			{
				m_ResInfoList.push_back(*i);
			}
		}
		break;

	case TYPE_OTHER:
		static WCHAR strOtherTitle[MAX_PATH];
		LoadString(NULL, IDS_STRING_TITLE_OTHER, strOtherTitle, sizeof(strOtherTitle));
		m_psp.hIcon    = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		m_psp.pszTitle = strOtherTitle;
		for (RES_LIST::const_iterator i = g_ResInfoList.begin(); i != g_ResInfoList.end(); ++i)
		{
			if (i->Type == "����")
			{
				m_ResInfoList.push_back(*i);
			}
		}
		break;
	}

	m_psp.dwFlags &= ~PSP_USEICONID;   
	m_psp.dwFlags |= PSP_USEHICON;
	m_psp.dwFlags |= PSP_USETITLE;
}

void CResListPage::UpdateList(void)
{
	if (IsWindow(m_ResListCtrl))
	{
		ListView_SetItemCount(m_ResListCtrl, m_ResInfoList.size());//�����б��ж����� ��ô������ʾ���б�ؼ�ҲҪ�ж�����
		::InvalidateRect(m_ResListCtrl, NULL, FALSE);//�����б�
	}
}
