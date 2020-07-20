
// DemoDlg.h : 头文件
//

#pragma once

#include "Label.h"

//按钮状态
enum CButtonState { bsNone, bsIni, bsMin, bsMax, bsRes, bsClose };

// CDemoDlg 对话框
class CDemoDlg : public CDialog
{
// 构造
public:
	CDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	void DrawFormCaption();
	void DrawForm();

	BOOL m_IsMax;         //是否处于最大化状态
	int  m_BorderWidth;   //边框宽度
	int  m_BorderHeight;  //边框高度
	int  m_CaptionHeight; //标题栏的高度
	CString  m_Caption;      //窗口标题
	COLORREF m_CapitonColor; //标题字体颜色
	CFont    m_CaptionFont;  //标题字体

	int m_ButtonWidth;  //按钮位图宽度
	int m_ButtonHeight; //按钮位图高度

	BOOL  m_FirstShow; //窗口首次被显示

	CRect m_OrigonRect;//原始窗口区域

	CRect m_IniRect, m_MinRect, m_MaxRect, m_CloseRect;//标题栏按钮的显示区域

	CButtonState m_ButtonState; //按钮状态

	BOOL m_IsDrawForm;//是否需要绘制窗体

	CLabel	m_lUsername;
	CLabel	m_lPasswrod;


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcPaint();
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnBtnSignIn();
	afx_msg void OnBtnSignOut();
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	DECLARE_MESSAGE_MAP()

};
