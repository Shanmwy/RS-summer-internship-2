// DensitySegmentationDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "SummerRSProject.h"
#include "DensitySegmentationDlg.h"
#include "afxdialogex.h"


// DensitySegmentationDlg 对话框

IMPLEMENT_DYNAMIC(DensitySegmentationDlg, CDialog)

DensitySegmentationDlg::DensitySegmentationDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DensitySegmentation, pParent)
{

}

DensitySegmentationDlg::~DensitySegmentationDlg()
{
}

void DensitySegmentationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listDS);
	DDX_Control(pDX, IDC_COMBO1, m_band);
	//  DDX_Control(pDX, IDC_LIST2, m_colorStyle);
	DDX_Control(pDX, IDC_COMBO2, m_colorStyle);
}


BEGIN_MESSAGE_MAP(DensitySegmentationDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DensitySegmentationDlg::OnCbnSelchangeCombo1)
	
END_MESSAGE_MAP()


// DensitySegmentationDlg 消息处理程序


void DensitySegmentationDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL DensitySegmentationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//王铮7.6密度分割
	CRect ListControl;
	m_listDS.GetClientRect(&ListControl);
	m_listDS.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);

	m_listDS.InsertColumn(0, _T("序号"), LVCFMT_CENTER, ListControl.Width() / 4);
	m_listDS.InsertColumn(1, _T("颜色"), LVCFMT_CENTER, ListControl.Width() / 4);
	m_listDS.InsertColumn(2, _T("下限"), LVCFMT_CENTER, ListControl.Width() / 4);
	m_listDS.InsertColumn(3, _T("上限"), LVCFMT_CENTER, ListControl.Width() / 4);

	m_band.AddString(_T("R"));
	m_band.AddString(_T("G"));
	m_band.AddString(_T("B"));//添加波段名

	m_band.SetCurSel(0);      //默认选择R波段

	m_colorStyle.AddString(_T("彩虹1"));
	m_colorStyle.AddString(_T("彩虹2"));
	m_colorStyle.AddString(_T("彩虹3"));
	m_colorStyle.AddString(_T("彩虹4"));//添加密度分割颜色风格

	m_colorStyle.SetCurSel(0);//默认风格

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



