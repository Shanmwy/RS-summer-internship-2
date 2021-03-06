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
	, m_minValue(0)
	, m_maxValue(255)
	, m_numLevels(256)
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
	DDX_Text(pDX, IDC_MIN, m_minValue);
	DDX_Text(pDX, IDC_MAX, m_maxValue);
	DDX_Text(pDX, IDC_CLASSIFICATION, m_numLevels);
}


BEGIN_MESSAGE_MAP(DensitySegmentationDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DensitySegmentationDlg::OnCbnSelchangeCombo1)
	
	ON_CBN_SELCHANGE(IDC_COMBO2, &DensitySegmentationDlg::OnCbnSelchangeCombo2)
//	ON_EN_CHANGE(IDC_CLASSIFICATION, &DensitySegmentationDlg::OnEnChangeClassification)
ON_EN_KILLFOCUS(IDC_CLASSIFICATION, &DensitySegmentationDlg::OnEnKillfocusClassification)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, &DensitySegmentationDlg::OnNMCustomdrawList1)
END_MESSAGE_MAP()


// DensitySegmentationDlg 消息处理程序





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


	//建立色带库
	MyColorStyle rainbow1(_T("rainbow1"));
	RGBQUAD color;
	color.rgbBlue = 255;
	color.rgbGreen = 0;
	color.rgbRed = 0;
	rainbow1.valueColorMaps.push_back(MyValueColorMap(0, color));
	color.rgbBlue = 255;
	color.rgbGreen = 255;
	color.rgbRed = 0;
	rainbow1.valueColorMaps.push_back(MyValueColorMap(64, color));
	color.rgbBlue = 0;
	color.rgbGreen = 255;
	color.rgbRed = 0;
	rainbow1.valueColorMaps.push_back(MyValueColorMap(96, color));
	color.rgbBlue = 0;
	color.rgbGreen = 255;
	color.rgbRed = 255;
	rainbow1.valueColorMaps.push_back(MyValueColorMap(128, color));
	color.rgbBlue = 0;
	color.rgbGreen = 0;
	color.rgbRed = 255;
	rainbow1.valueColorMaps.push_back(MyValueColorMap(192, color));
	color.rgbBlue = 255;
	color.rgbGreen = 255;
	color.rgbRed = 255;
	rainbow1.valueColorMaps.push_back(MyValueColorMap(256, color));
	m_colorStyleRepo.push_back(rainbow1);

	m_colorStyle.AddString(_T("rainbow1"));//添加密度分割颜色风格

	MyColorStyle blue(_T("blue"));
	color.rgbBlue = 255;
	color.rgbGreen = 0;
	color.rgbRed = 0;
	blue.valueColorMaps.push_back(MyValueColorMap(0, color));
	color.rgbBlue = 255;
	color.rgbGreen = 255;
	color.rgbRed = 255;
	blue.valueColorMaps.push_back(MyValueColorMap(256, color));
	m_colorStyleRepo.push_back(blue);
	
	m_colorStyle.AddString(_T("blue"));//添加密度分割颜色风格

	MyColorStyle red(_T("red"));
	color.rgbBlue = 0;
	color.rgbGreen = 0;
	color.rgbRed = 255;
	red.valueColorMaps.push_back(MyValueColorMap(0, color));
	color.rgbBlue = 255;
	color.rgbGreen = 255;
	color.rgbRed = 255;
	red.valueColorMaps.push_back(MyValueColorMap(256, color));
	m_colorStyleRepo.push_back(red);

	m_colorStyle.AddString(_T("red"));//添加密度分割颜色风格

	MyColorStyle green(_T("green"));
	color.rgbBlue = 0;
	color.rgbGreen = 255;
	color.rgbRed = 0;
	green.valueColorMaps.push_back(MyValueColorMap(0, color));
	color.rgbBlue = 255;
	color.rgbGreen = 255;
	color.rgbRed = 255;
	green.valueColorMaps.push_back(MyValueColorMap(256, color));
	m_colorStyleRepo.push_back(green);

	m_colorStyle.AddString(_T("green"));//添加密度分割颜色风格

	MyColorStyle b2r(_T("blue 2 red"));
	color.rgbBlue = 255;
	color.rgbGreen = 0;
	color.rgbRed = 0;
	b2r.valueColorMaps.push_back(MyValueColorMap(0, color));
	color.rgbBlue = 0;
	color.rgbGreen = 0;
	color.rgbRed = 255;
	b2r.valueColorMaps.push_back(MyValueColorMap(256, color));
	m_colorStyleRepo.push_back(b2r);

	m_colorStyle.AddString(_T("blue 2 red"));//添加密度分割颜色风格

	MyColorStyle b2b2r(_T("black 2 blue 2 red"));
	color.rgbBlue = 0;
	color.rgbGreen = 0;
	color.rgbRed = 0;
	b2b2r.valueColorMaps.push_back(MyValueColorMap(0, color));
	color.rgbBlue = 255;
	color.rgbGreen = 0;
	color.rgbRed = 0;
	b2b2r.valueColorMaps.push_back(MyValueColorMap(128, color));
	color.rgbBlue = 0;
	color.rgbGreen = 0;
	color.rgbRed = 255;
	b2b2r.valueColorMaps.push_back(MyValueColorMap(256, color));
	m_colorStyleRepo.push_back(b2b2r);

	m_colorStyle.AddString(_T("black 2 blue 2 red"));//添加密度分割颜色风格

	m_colorStyle.SetCurSel(0);//默认风格


	m_band.AddString(_T("R"));
	m_band.AddString(_T("G"));
	m_band.AddString(_T("B"));//添加波段名

	m_band.SetCurSel(0);      //默认选择R波段

	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//改变波段选择
void DensitySegmentationDlg::OnCbnSelchangeCombo1()
{
	UpdateData(TRUE);
	//这里要先把波段的最大最小值找出来并赋值
	m_maxValue = 255;
	m_minValue = 0;

	UpdateData(FALSE);
	RefreshAll();
}

//改变色带选择
void DensitySegmentationDlg::OnCbnSelchangeCombo2()
{
	UpdateData(TRUE);
	RefreshAll();
}


//改变分割级数
void DensitySegmentationDlg::OnEnKillfocusClassification()
{
	UpdateData(TRUE);
	RefreshAll();
}

void DensitySegmentationDlg::RefreshAll()
{
	//确定选用的色带
	int indexColorStyle = m_colorStyle.GetCurSel();

	double step = (m_maxValue - m_minValue) / m_numLevels;
	double curValue = m_minValue;

	//制作m_valueColorMaps
	m_valueColorMaps.clear();
	for (int i = 0; i < m_numLevels; i++)
	{
		m_valueColorMaps.push_back(MyValueColorMap(curValue, m_colorStyleRepo[indexColorStyle].GetColor(curValue + 0.5*step, m_minValue, m_maxValue)));
		curValue += step;
	}
	//假尾巴
	m_valueColorMaps.push_back(MyValueColorMap(m_maxValue, RGBQUAD()));


	CString str;
	CListCtrl * list = (CListCtrl*)GetDlgItem(IDC_LIST1);
	list->DeleteAllItems();
	//制作ListControl
	for (int i = 0; i < m_numLevels; i++)
	{
		str.Format(_T("%d"), i + 1);
		list->InsertItem(i, str);

		str.Format(_T("%.2lf"), m_valueColorMaps[i].minValue);
		list->SetItemText(i, 2, str);

		str.Format(_T("%.2lf"), m_valueColorMaps[i + 1].minValue);
		list->SetItemText(i, 3, str);
	}

	//制作色带条幅
	CRect rect;
	CStatic * pic = (CStatic*)GetDlgItem(IDC_PCCOLORSTYLE);
	pic->GetClientRect(&rect);
	CDC * pdc = pic->GetDC();
	double stepX = (double)rect.Width() / 256;
	double curX = stepX;
	int y = rect.Height();
	RGBQUAD rgb;

	for (int i = 0; i < 256; i++)
	{
		rgb = m_colorStyleRepo[indexColorStyle].GetColor(double(i), 0, 256);
		CPen pen(PS_SOLID, (int)ceil(stepX), RGB(rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue));
		pdc->SelectObject(&pen);
		pdc->MoveTo((int)curX, 0);
		pdc->LineTo((int)curX, y);
		curX += stepX;
		pen.DeleteObject();
	}
		
}


void DensitySegmentationDlg::OnNMCustomdrawList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pLVCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		// This is the notification message for an item. We'll request
		// notifications before each subitem's prepaint stage.
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ((CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage)
	{
		int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);
		COLORREF crBkgnd;
		if (pLVCD->iSubItem == 1)
		{
			if (nItem >= 0)
			{
				crBkgnd = RGB(m_valueColorMaps[nItem].color.rgbRed, m_valueColorMaps[nItem].color.rgbGreen, m_valueColorMaps[nItem].color.rgbBlue);
			}
			else
			{
				crBkgnd = RGB(255, 255, 255);
			}
			//pLVCD->clrTextBk = crBkgnd;
		}
		else
		{
			crBkgnd = RGB(255, 255, 255);
		}

		pLVCD->clrTextBk = crBkgnd;
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
}
