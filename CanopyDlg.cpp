// CanopyDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "SummerRSProject.h"
#include "CanopyDlg.h"
#include "afxdialogex.h"


// CanopyDlg 对话框

IMPLEMENT_DYNAMIC(CanopyDlg, CDialog)

CanopyDlg::CanopyDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Canopy, pParent)
{

}

CanopyDlg::~CanopyDlg()
{
}

void CanopyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCanopy);
	DDX_Control(pDX, IDC_EDIT3, m_ClassName);
}


BEGIN_MESSAGE_MAP(CanopyDlg, CDialog)
//	ON_WM_ACTIVATE()
ON_BN_CLICKED(IDC_BUTTON3, &CanopyDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CanopyDlg 消息处理程序


//void CanopyDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
//{
//	CDialog::OnActivate(nState, pWndOther, bMinimized);
//
//	// TODO: 在此处添加消息处理程序代码
//}


BOOL CanopyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//7.8王铮Canopy聚类分类表

	DWORD SetExtendedStyle(DWORD dwNewStyle);
	m_listCanopy.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	CRect ListControl;
	m_listCanopy.GetClientRect(&ListControl);
	m_listCanopy.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);

	m_listCanopy.InsertColumn(0, _T("序号"), LVCFMT_CENTER, ListControl.Width() / 3);
	m_listCanopy.InsertColumn(1, _T("类名"), LVCFMT_CENTER, ListControl.Width() / 3);
	m_listCanopy.InsertColumn(2, _T("颜色"), LVCFMT_CENTER, ListControl.Width() / 3);

	CListCtrl * list = (CListCtrl*)GetDlgItem(IDC_LIST1);
	//CString str;

	list->InsertItem(0, _T("0"));
	list->InsertItem(1, _T("1"));
	list->InsertItem(2, _T("2"));
	list->SetItemText(0, 1, _T("0"));
	list->SetItemText(1, 1, _T("1"));
	list->SetItemText(2, 1, _T("2"));
	list->SetItemText(0, 2, _T("0"));
	list->SetItemText(1, 2, _T("1"));
	list->SetItemText(2, 2, _T("2"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CanopyDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	//7.8王铮修改类名
	CListCtrl * list = (CListCtrl*)GetDlgItem(IDC_LIST1);
	POSITION pos = list->GetFirstSelectedItemPosition();
	int nItem = list->GetNextSelectedItem(pos);
	CString str;
	m_ClassName.GetWindowText(str);
	list->SetItemText(nItem, 1, str);
}
