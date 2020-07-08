#pragma once


// CanopyDlg 对话框

class CanopyDlg : public CDialog
{
	DECLARE_DYNAMIC(CanopyDlg)

public:
	CanopyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CanopyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Canopy };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	virtual BOOL OnInitDialog();
	CListCtrl m_listCanopy;
	afx_msg void OnBnClickedButton3();
	CEdit m_ClassName;
};
