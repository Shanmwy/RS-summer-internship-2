// FineCorrectionDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "SummerRSProject.h"
#include "FineCorrectionDlg.h"
#include "afxdialogex.h"

#include "MyPoint.h"
#include "MyMatrix.h"


// FineCorrectionDlg 对话框

IMPLEMENT_DYNAMIC(FineCorrectionDlg, CDialogEx)

FineCorrectionDlg::FineCorrectionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FineCorrection, pParent)
	, m_x_base(0)
	, m_y_base(0)
	, m_x_wrap(0)
	, m_y_wrap(0)
	, m_num_GCPs(0)
	, m_method(_T("Polynomials"))
	, m_degree(_T("1"))
	, m_resample(_T("Bilinear"))
	, m_background(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

FineCorrectionDlg::~FineCorrectionDlg()
{
}

void FineCorrectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Text(pDX, IDC_Base_X, m_x_base);
	DDX_Text(pDX, IDC_Base_Y, m_y_base);
	DDX_Text(pDX, IDC_Wrap_X, m_x_wrap);
	DDX_Text(pDX, IDC_wrap_Y, m_y_wrap);
	//DDX_Text(pDX, IDC_Num_GCPs, m_num_GCPs);
	DDX_CBString(pDX, IDC_COMBO_METHOD, m_method);
	DDX_CBString(pDX, IDC_COMBO_DEGREE, m_degree);
	DDX_CBString(pDX, IDC_COMBO_RESAMPLE, m_resample);
	DDX_Text(pDX, IDC_EDIT1, m_background);
}


BEGIN_MESSAGE_MAP(FineCorrectionDlg, CDialogEx)
	ON_COMMAND(ID_BaseFile, &FineCorrectionDlg::OnBasefile)
	ON_COMMAND(ID_WrapFile, &FineCorrectionDlg::OnWrapfile)
	ON_COMMAND(ID_HELP, &FineCorrectionDlg::OnHelp)
	ON_BN_CLICKED(IDC_AddPoint, &FineCorrectionDlg::OnBnClickedAddpoint)
	ON_BN_CLICKED(IDC_Delete, &FineCorrectionDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_UPDATE, &FineCorrectionDlg::OnBnClickedUpdate)
//	ON_EN_CHANGE(IDC_EDIT_BACKGROUND4, &FineCorrectionDlg::OnEnChangeEditBackground4)
ON_CBN_SELCHANGE(IDC_COMBO_DEGREE, &FineCorrectionDlg::OnCbnSelchangeComboDegree)
END_MESSAGE_MAP()


// FineCorrectionDlg 消息处理程序


BOOL FineCorrectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//陈炳如7:2：获取菜单
	menu.LoadMenu(IDR_MENU_FC);  //IDR_MENU_FC为菜单栏ID号
	SetMenu(&menu);

	//陈炳如7:2：初始化窗口指针
	m_base_image = new ImageDlg();
	m_wrap_image = new ImageDlg();

	m_base_flag = m_wrap_flag = 0;

	//王铮7.3GCP窗口
	CRect ListControl;
	m_list.GetClientRect(&ListControl);
	m_list.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);

	m_list.InsertColumn(0, _T("序号"), LVCFMT_CENTER, ListControl.Width() / 10);
	m_list.InsertColumn(1, _T("Base_X"), LVCFMT_CENTER, ListControl.Width() / 10);
	m_list.InsertColumn(2, _T("Base_Y"), LVCFMT_CENTER, ListControl.Width() / 10);
	m_list.InsertColumn(3, _T("Wrap_X"), LVCFMT_CENTER, ListControl.Width() / 10);
	m_list.InsertColumn(4, _T("Wrap_Y"), LVCFMT_CENTER, ListControl.Width() / 10);
	m_list.InsertColumn(5, _T("Predict_X"), LVCFMT_CENTER, ListControl.Width() / 10);
	m_list.InsertColumn(6, _T("Predict_Y"), LVCFMT_CENTER, ListControl.Width() / 10);
	m_list.InsertColumn(7, _T("Error_X"), LVCFMT_CENTER, ListControl.Width() / 10);
	m_list.InsertColumn(8, _T("Error_Y"), LVCFMT_CENTER, ListControl.Width() / 10);
	m_list.InsertColumn(9, _T("Distance(RSS)"), LVCFMT_CENTER, ListControl.Width() / 10);
	
	//cyz7.4：初始化系数矩阵
	m_pCoefX = NULL;
	m_pCoefY = NULL;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//陈炳如7:2：打开配准文件及窗口
void FineCorrectionDlg::OnBasefile()
{
	// TODO: 在此添加命令处理程序代码
	m_base_image->Create(IDD_DIALOG_IMAGE);

	//打开文件
	CFileDialog dlg(TRUE, _T("*.*"), NULL, OFN_HIDEREADONLY, _T("*.*|*.*||"));
	CString csFileName;
	if (dlg.DoModal() == IDOK)
	{
		csFileName = dlg.GetPathName();//选择的文件路径   
	}
	m_base_image->OpenFile(csFileName,_T("Base Image"));

	//显示窗体
	m_base_image->ShowWindow(SW_SHOWNORMAL);

	m_base_flag = 1;
}

//陈炳如7:2：打开待配准文件及窗口
void FineCorrectionDlg::OnWrapfile()
{
	// TODO: 在此添加命令处理程序代码
	m_wrap_image->Create(IDD_DIALOG_IMAGE);

	//打开文件
	CFileDialog dlg(TRUE, _T("*.*"), NULL, OFN_HIDEREADONLY, _T("*.*|*.*||"));
	CString csFileName;
	if (dlg.DoModal() == IDOK)
	{
		csFileName = dlg.GetPathName();//选择的文件路径   
	}
	m_wrap_image->OpenFile(csFileName,_T("Wrap Image"));

	//显示窗体
	m_wrap_image->ShowWindow(SW_SHOWNORMAL);

	m_wrap_flag = 1;
}

//陈炳如7:2：messageBox，写一些注意事项
void FineCorrectionDlg::OnHelp()
{
	// TODO: 在此添加命令处理程序代码
}

//陈炳如7:2：释放窗口指针
BOOL FineCorrectionDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(m_base_image!=NULL)delete m_base_image;
	if(m_wrap_image!=NULL)delete m_wrap_image;

	return CDialogEx::DestroyWindow();
}

//陈炳如7:3：添加待定点
void FineCorrectionDlg::OnBnClickedAddpoint()
{
	// TODO: 在此添加控件通知处理程序代码

	//陈炳如：判断是否打开
	//if (m_base_flag == 0)
	//{
	//	MessageBox(_T("need base image!"));
	//	return;
	//}
	//if (m_wrap_flag == 0)
	//{
	//	MessageBox(_T("need wrap image!"));
	//	return;
	//}

	//陈炳如：获取点并
	MyPoint pt_base = m_base_image->GetPendingPoint();
	MyPoint pt_wrap = m_wrap_image->GetPendingPoint();

	//若未选取点，则坐标为负值，判断（先不写了）

	//cbr:添加到编辑框
	m_x_base = pt_base.x;
	m_y_base = pt_base.y; 
	m_x_wrap = pt_wrap.x; 
	m_y_wrap = pt_wrap.y;
	UpdateData(false);

	//cyz7.4：添加到m_GCPs
	MyGCPPair newGCPPair(pt_base, pt_wrap);
	m_GCPPairs.push_back(newGCPPair);

	CalcCoefsUsingLinearRegressionAndPredict();
	RefreshGCPList();

}

//cyz7.4：刷新GCP表
void FineCorrectionDlg::RefreshGCPList()
{
	CListCtrl * list = (CListCtrl*)GetDlgItem(IDC_LIST);
	list->DeleteAllItems();
	CString str;
	
	//add all GCPs one by one
	for (int i = 0; i < m_GCPPairs.size(); i++)
	{
		str.Format(_T("%d"), i + 1);
		list->InsertItem(i, str);

		str.Format(_T("%.2f"), m_GCPPairs[i].basePt.x);
		list->SetItemText(i, 1, str);

		str.Format(_T("%.2f"), m_GCPPairs[i].basePt.y);
		list->SetItemText(i, 2, str);

		str.Format(_T("%.2f"), m_GCPPairs[i].warpPt.x);
		list->SetItemText(i, 3, str);

		str.Format(_T("%.2f"), m_GCPPairs[i].warpPt.y);
		list->SetItemText(i, 4, str);

		str.Format(_T("%.2f"), m_GCPPairs[i].predPt.x);
		list->SetItemText(i, 5, str);

		str.Format(_T("%.2f"), m_GCPPairs[i].predPt.y);
		list->SetItemText(i, 6, str);

		str.Format(_T("%.2f"), m_GCPPairs[i].GetErrX());
		list->SetItemText(i, 7, str);

		str.Format(_T("%.2f"), m_GCPPairs[i].GetErrY());
		list->SetItemText(i, 8, str);

		str.Format(_T("%.2f"), m_GCPPairs[i].GetDist());
		list->SetItemText(i, 9, str);
	}
}

//cyz7.4：线性回归与预测
void FineCorrectionDlg::CalcCoefsUsingLinearRegressionAndPredict()
{
	//this should be a multi-target linear regression, but since that the weights are for X and for Y, 
	//I treated this as 2 seperated single-target linear regression

	//calc the number of base functions, the number of samples
	int degree = _ttoi(m_degree);
	int featureNumber = (degree + 1)*(degree + 2) / 2;
	int sampleNumber = m_GCPPairs.size();
	delete m_pCoefX;
	delete m_pCoefY;

	//see if there are enough samples
	if (sampleNumber < featureNumber)
	{
		for (int indexSample = 0; indexSample < sampleNumber; indexSample++)
		{
			m_GCPPairs[indexSample].predPt = m_GCPPairs[indexSample].warpPt;
		}
		m_pCoefX = NULL;
		m_pCoefY = NULL;
		return;
	}

	//samples are enough and do initialization
	MyMatrix A(sampleNumber, featureNumber, 0);
	MyMatrix TX(sampleNumber, 1, 0);
	MyMatrix TY(sampleNumber, 1, 0);

	//formulate the A
	int expX = 0;
	int expY = 0;
	for (int indexFeature = 0; indexFeature < featureNumber; indexFeature++)
	{
		for (int indexSample = 0; indexSample < sampleNumber; indexSample++)
		{
			double x = (double)m_GCPPairs[indexSample].basePt.x;
			double y = (double)m_GCPPairs[indexSample].basePt.y;
			A.Content[indexSample][indexFeature] = pow(x, expX)*pow(y, expY);
		}

		// accumulate exp of x and y
		if (expX == 0)
		{
			expX = expY + 1;
			expY = 0;
		}
		else
		{
			expX--;
			expY++;
		}
	}

	//formulate Ts
	for (int indexSample = 0; indexSample < sampleNumber; indexSample++)
	{
		double x = (double)m_GCPPairs[indexSample].warpPt.x;
		double y = (double)m_GCPPairs[indexSample].warpPt.y;
		TX.Content[indexSample][0] = x;
		TY.Content[indexSample][0] = y;
	}

	//solve
	MyMatrix WX = MyMatrix::LeastSquaresSolution(A, TX);
	m_pCoefX = new MyMatrix(WX);
	MyMatrix WY = MyMatrix::LeastSquaresSolution(A, TY);
	m_pCoefY = new MyMatrix(WY);

	//predict
	MyMatrix predX = A * (*m_pCoefX);
	MyMatrix predY = A * (*m_pCoefY);
	for (int indexSample = 0; indexSample < sampleNumber; indexSample++)
	{
		m_GCPPairs[indexSample].predPt.x = (float)predX.Content[indexSample][0];
		m_GCPPairs[indexSample].predPt.y = (float)predY.Content[indexSample][0];
	}
}

//cyz7.4：删除GCPs
void FineCorrectionDlg::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl * list = (CListCtrl*)GetDlgItem(IDC_LIST);
	POSITION pos = list->GetFirstSelectedItemPosition();
	while (NULL != pos)
	{
		int index = list->GetNextSelectedItem(pos);
		std::vector<MyGCPPair>::iterator iter = m_GCPPairs.begin();
		iter += index;
		m_GCPPairs.erase(iter);
		list->DeleteItem(index);
		pos = list->GetFirstSelectedItemPosition();
	}

	CalcCoefsUsingLinearRegressionAndPredict();
	RefreshGCPList();
}

//cyz7.4：更新GCP
void FineCorrectionDlg::OnBnClickedUpdate()
{

	MyPoint pt_base = m_base_image->GetPendingPoint();
	MyPoint pt_wrap = m_wrap_image->GetPendingPoint();
	CListCtrl * list = (CListCtrl*)GetDlgItem(IDC_LIST);
	POSITION pos = list->GetFirstSelectedItemPosition();
	if (NULL != pos)
	{
		int index = list->GetNextSelectedItem(pos);
		m_GCPPairs[index].basePt = pt_base;
		m_GCPPairs[index].warpPt = pt_wrap;
	}

	CalcCoefsUsingLinearRegressionAndPredict();
	RefreshGCPList();

}

//cyz7.4：更改degree
void FineCorrectionDlg::OnCbnSelchangeComboDegree()
{
	UpdateData(TRUE);
	CalcCoefsUsingLinearRegressionAndPredict();
	RefreshGCPList();
}
