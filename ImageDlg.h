#pragma once

#include"MyPoint.h"
#include<vector>

// ImageDlg 对话框

class ImageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ImageDlg)

public:
	ImageDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ImageDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMAGE };
#endif

protected:
	CMenu m_Menu;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	//陈炳如7:2:打开指定文件
	void OpenFile(CString path,CString windowName);

	//陈炳如7:2获取待定坐标，并将坐标添加到数组
	MyPoint GetPendingPoint();

	//陈炳如7:2删除指定坐标
	void DeletePoint(int n);

	//陈炳如7:2修改指定坐标
	void ModifyPoint(int n,float dx,float dy);

private:
	//陈炳如7:2：文件路径
	CString fileName;

	/*
	选点操作：

	OnLButtonDblClk：
	1、在子窗体单击，获取窗口坐标，计算图像坐标并保存
	2、refresh，计算显示待定坐标，窗体范围判定，绘制绿十字

	GetPendingPoint：
	3、主窗体Add，发送待定图像坐标，待定图像坐标添加到图像坐标数组，删除待定坐标
	4、refresh，计算显示图像坐标，窗体范围判定，绘制红十字以及编号
	*/

	//陈炳如7:2：图像坐标数组，红十字标识
	std::vector<MyPoint> m_selectedPoints;
	//陈炳如7:2：图像待定坐标
	MyPoint m_pendingPoint;

	//陈炳如7:2：显示待定坐标，绘制绿十字标识
	CPoint m_pendingPoint_show;
	//陈炳如7:2：显示坐标数组，只添加窗体范围内坐标，用于绘制红十字标识
	std::vector<CPoint> m_selectedPoints_show;

	//陈炳如：7:3：显示到窗体(待修改）
	void ShowToImg();

	//陈炳如7：3：在窗体上左键单击选取为待定坐标（需要进行显示-图像坐标转换）
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	//cbr7:3:窗口句柄
	CDC* pdc;
	//绿色笔刷
	CPen penGreen;
	//红色笔刷
	CPen penRed;
	//原笔刷
	CPen penOld;
public:
	afx_msg void OnDestroy();
};
