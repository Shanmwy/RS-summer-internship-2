#pragma once


// DensitySegmentationDlg 对话框

class DensitySegmentationDlg : public CDialog
{
	DECLARE_DYNAMIC(DensitySegmentationDlg)

public:
	DensitySegmentationDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DensitySegmentationDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DensitySegmentation };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	CListCtrl m_listDS;
	virtual BOOL OnInitDialog();
	CComboBox m_band;
//	CListBox m_colorStyle;
	CComboBox m_colorStyle;
	
};
