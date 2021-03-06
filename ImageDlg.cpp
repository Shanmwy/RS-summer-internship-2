// ImageDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "SummerRSProject.h"
#include "ImageDlg.h"
#include "afxdialogex.h"


// ImageDlg 对话框

IMPLEMENT_DYNAMIC(ImageDlg, CDialogEx)

ImageDlg::ImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IMAGE, pParent)
{

}

ImageDlg::~ImageDlg()
{
}

void ImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ImageDlg, CDialogEx)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// ImageDlg 消息处理程序


BOOL ImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//添加菜单
	m_Menu.LoadMenu(IDR_MENU_IMG);
	SetMenu(&m_Menu);

	//获取句柄
	pdc = this->GetDC();
	penGreen.CreatePen(PS_SOLID, 1, RGB(0,255,0));
	penRed.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	//点初始化,负值表示空
	m_pendingPoint.x = m_pendingPoint.y = -1;
	m_pendingPoint_show.x = m_pendingPoint_show.y = -1;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void ImageDlg:: OpenFile(CString path, CString windowName)
{
	fileName = path;
	this->SetWindowText(windowName);

	//打开

}
MyPoint ImageDlg::GetPendingPoint()
{
	MyPoint res = m_pendingPoint;

	//添加到列表

	//删除pending

	return res;
}
//陈炳如：7:3：显示到窗体(待修改）
void ImageDlg::ShowToImg()
{
	m_pendingPoint.x = (float)m_pendingPoint_show.x;
	m_pendingPoint.y = (float)m_pendingPoint_show.y;
}

//陈炳如7：3：在窗体上左键单击选取为待定坐标（需要进行显示-图像坐标转换）
void ImageDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//保存坐标
	m_pendingPoint_show = point;
	ShowToImg();

	//需要改为refresh
	//绘制绿十字
	pdc->SelectObject(&penGreen);
	pdc->MoveTo(point.x - 10, point.y);
	pdc->LineTo(point.x + 10, point.y);
	pdc->MoveTo(point.x, point.y-10);
	pdc->LineTo(point.x, point.y + 10);

	CDialogEx::OnLButtonDblClk(nFlags, point);
}

//陈炳如7:3：销毁指针句柄
void ImageDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	if (pdc != NULL)
		pdc->DeleteDC();
}
