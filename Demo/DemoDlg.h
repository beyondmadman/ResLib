
// DemoDlg.h : ͷ�ļ�
//

#pragma once

#include "Label.h"

//��ť״̬
enum CButtonState { bsNone, bsIni, bsMin, bsMax, bsRes, bsClose };

// CDemoDlg �Ի���
class CDemoDlg : public CDialog
{
// ����
public:
	CDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	void DrawFormCaption();
	void DrawForm();

	BOOL m_IsMax;         //�Ƿ������״̬
	int  m_BorderWidth;   //�߿���
	int  m_BorderHeight;  //�߿�߶�
	int  m_CaptionHeight; //�������ĸ߶�
	CString  m_Caption;      //���ڱ���
	COLORREF m_CapitonColor; //����������ɫ
	CFont    m_CaptionFont;  //��������

	int m_ButtonWidth;  //��ťλͼ���
	int m_ButtonHeight; //��ťλͼ�߶�

	BOOL  m_FirstShow; //�����״α���ʾ

	CRect m_OrigonRect;//ԭʼ��������

	CRect m_IniRect, m_MinRect, m_MaxRect, m_CloseRect;//��������ť����ʾ����

	CButtonState m_ButtonState; //��ť״̬

	BOOL m_IsDrawForm;//�Ƿ���Ҫ���ƴ���

	CLabel	m_lUsername;
	CLabel	m_lPasswrod;


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
