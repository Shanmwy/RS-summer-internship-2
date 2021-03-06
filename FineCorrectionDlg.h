#pragma once
#include"ImageDlg.h"
#include "MyMatrix.h"

// FineCorrectionDlg 对话框

class FineCorrectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FineCorrectionDlg)

public:
	FineCorrectionDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~FineCorrectionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FineCorrection };
#endif

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	//陈炳如7:2，menu相关函数等
	CMenu menu;
	afx_msg void OnBasefile();
	afx_msg void OnWrapfile();
	afx_msg void OnHelp();
	// 陈炳如7:2：GCP列表
	
	CListCtrl m_list;
	float m_x_base;
	float m_y_base;
	float m_x_wrap;
	float m_y_wrap;
	int m_num_GCPs;

	//陈炳如7:2：图像窗体指针
	ImageDlg *m_base_image;
	ImageDlg *m_wrap_image;

	//陈炳如7:3：图像窗体打开表示符，0为关，1为开
	bool m_base_flag;
	bool m_wrap_flag;

	//陈炳如7:2：释放窗口指针
	virtual BOOL DestroyWindow();
	// 回归基函数方法	
	CString m_method;
	// 级数
	CString m_degree;
	// 重采样
	CString m_resample;
	// 背景
	float m_background;

	//陈炳如7:3：添加待定点
	afx_msg void OnBnClickedAddpoint();

	//cyz7.4：控制点对们
	std::vector<MyGCPPair> m_GCPPairs;

	//cyz7.4：学习到的系数们，存为列向量
	MyMatrix * m_pCoefX;
	MyMatrix * m_pCoefY;

	//cyz7.4：刷新ListControl
	void RefreshGCPList();

	//cyz7.4：用所有的控制点对们重新计算线性回归，并进行预测
	void CalcCoefsUsingLinearRegressionAndPredict();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedUpdate();
//	afx_msg void OnEnChangeEditBackground4();
	afx_msg void OnCbnSelchangeComboDegree();
};
