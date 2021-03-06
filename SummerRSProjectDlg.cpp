
// SummerRSProjectDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "SummerRSProject.h"
#include "SummerRSProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSummerRSProjectDlg 对话框



CSummerRSProjectDlg::CSummerRSProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SUMMERRSPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CSummerRSProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_tab);
}

BEGIN_MESSAGE_MAP(CSummerRSProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CSummerRSProjectDlg::OnTcnSelchangeTabMain)
END_MESSAGE_MAP()


// CSummerRSProjectDlg 消息处理程序

BOOL CSummerRSProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

#pragma region 陈炳如7:2：窗口

	//创建对话框(新建窗口建于此处）
	m_dlg_fineCorrection.Create(IDD_FineCorrection, &m_tab);

	//7.6王铮密度分割窗口
	m_dlg_DensitySegmentationDlg.Create(IDD_DensitySegmentation, &m_tab);

	////获取窗口范围
	//CRect rc;
	//m_tab.GetClientRect(rc);
	//rc.top += 30;
	//rc.bottom -= 0;
	//rc.left += 0;
	//rc.right -= 0;

	////设定在Tab内显示的范围(新建窗口建于此处）
	//m_dlg_fineCorrection.MoveWindow(&rc);


#pragma endregion


#pragma region 陈炳如7:2：tabControl
	//为Tab Control增加页面
	m_tab.InsertItem(0, _T("光谱曲线"));
	m_tab.InsertItem(1, _T("几何精校正"));
	m_tab.InsertItem(2, _T("密度分割"));   //王铮7.6
	m_tab.InsertItem(3, _T("NULL"));
	m_tab.InsertItem(4, _T("NULL"));
	m_tab.InsertItem(5, _T("NULL"));

	////分别设置隐藏和显示 
	//m_dlg_fineCorrection.ShowWindow(true);

	//设置默认的选项卡 
	m_tab.SetCurSel(5);

#pragma endregion

	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSummerRSProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSummerRSProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSummerRSProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//陈炳如7:2：tab操作函数
//王铮7.6添加密度分割窗口
void CSummerRSProjectDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int CurSel = m_tab.GetCurSel();
	switch (CurSel)

	{
	case 0:
		
		m_dlg_fineCorrection.ShowWindow(false);
		m_dlg_DensitySegmentationDlg.ShowWindow(false);

		break;

	case 1:

		m_dlg_fineCorrection.ShowWindow(true);
		m_dlg_DensitySegmentationDlg.ShowWindow(false);

		break;

	case 2:

		m_dlg_fineCorrection.ShowWindow(false);
		m_dlg_DensitySegmentationDlg.ShowWindow(true);

		break;

	case 3:

		m_dlg_fineCorrection.ShowWindow(false);
		m_dlg_DensitySegmentationDlg.ShowWindow(false);

		break;

	case 4:

		m_dlg_fineCorrection.ShowWindow(false);
		m_dlg_DensitySegmentationDlg.ShowWindow(false);

		break;

	default:

		;

	}
	
}
