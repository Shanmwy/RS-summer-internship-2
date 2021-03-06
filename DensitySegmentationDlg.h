#pragma once
#include "ImageDlg.h"
#include "MyPoint.h"

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
	// 它的选中文本将指示用哪一个波段
	CComboBox m_band;
	// 它的选中下标将指示用哪一条色带
	CComboBox m_colorStyle;
	
	afx_msg void OnCbnSelchangeCombo2();
//	afx_msg void OnEnChangeClassification();
	afx_msg void OnEnKillfocusClassification();

	void RefreshAll();
	// 此波段的最小值
	double m_minValue;
	// 此波段的最大值
	double m_maxValue;

	//密度分割的灰度值-颜色映射表，其中从m_valueColorMaps[i].minValue到m_valueColorMaps[i+1].minValue为m_valueColorMaps[i].color颜色，最后有个假尾巴方便操作
	std::vector<MyValueColorMap> m_valueColorMaps;

	//色带仓库
	std::vector<MyColorStyle> m_colorStyleRepo;
	// 有几个级数
	int m_numLevels;
	afx_msg void OnNMCustomdrawList1(NMHDR *pNMHDR, LRESULT *pResult);
};
