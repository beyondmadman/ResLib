
// DemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"
#include "afxdialogex.h"
#include "ResLoad.h"

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


// CDemoDlg 对话框



CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: m_IsDrawForm(FALSE), m_ButtonState(bsNone), CDialog(IDD_DEMO_DIALOG, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = LoadICO(IDR_ICO_II);

	m_FirstShow = FALSE;
	m_IsMax = TRUE;
	m_CapitonColor = RGB(0, 0, 255);
	m_Caption = "系统登录";
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STC_USERNAME, m_lUsername);
	DDX_Control(pDX, IDC_STC_PASSWORD, m_lPasswrod);
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_NCACTIVATE()
	ON_WM_ACTIVATE()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCPAINT()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_WM_NCLBUTTONDBLCLK()
	ON_BN_CLICKED(ID_BTN_SIGNIN, OnBtnSignIn)
	ON_BN_CLICKED(ID_BTN_SIGNOUT, OnBtnSignOut)
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()


// CDemoDlg 消息处理程序

BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	m_BorderHeight = GetSystemMetrics(SM_CYBORDER);
	m_BorderWidth = GetSystemMetrics(SM_CXBORDER);
	m_CaptionHeight = GetSystemMetrics(SM_CYCAPTION);

	//获取按钮位图大小
	HBITMAP hBitmap;
	CBitmap bitmap;
	hBitmap = LoadBMP(IDR_BMP_FF);
	bitmap.Attach(hBitmap);
	BITMAPINFO bInfo;
	bitmap.GetObject(sizeof(bInfo), &bInfo);
	m_ButtonWidth = bInfo.bmiHeader.biWidth;
	m_ButtonHeight = bInfo.bmiHeader.biHeight;
	bitmap.DeleteObject();

	CRect rect;
	GetClientRect(rect);

	m_IniRect.CopyRect(CRect(8, (m_CaptionHeight + 3 * m_BorderHeight - m_ButtonHeight) / 2, m_ButtonWidth, m_ButtonHeight));
	m_MinRect.CopyRect(CRect(rect.Width() - 45, (m_CaptionHeight + 2 * m_BorderHeight - m_ButtonHeight) / 2, m_ButtonWidth, m_ButtonHeight));
	m_MaxRect.CopyRect(CRect(rect.Width() - 32, (m_CaptionHeight + 2 * m_BorderHeight - m_ButtonHeight) / 2, m_ButtonWidth, m_ButtonHeight));
	m_CloseRect.CopyRect(CRect(rect.Width() - 19, (m_CaptionHeight + 2 * m_BorderHeight - m_ButtonHeight) / 2, m_ButtonWidth, m_ButtonHeight));

	m_CaptionFont.CreateFont(14, 10, 0, 0, 600, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_ROMAN, _T("宋体"));

	DrawForm();

	m_lUsername.ModifyStyleEx(0, WS_EX_TRANSPARENT);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDemoDlg::OnPaint()
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
		CDialog::OnPaint();
	}

	DrawForm();
	m_IsDrawForm = TRUE;
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(rect);

	m_IniRect.CopyRect(CRect(8, (m_CaptionHeight + 3 * m_BorderHeight - m_ButtonHeight) / 2, m_ButtonWidth, m_ButtonHeight));
	m_MinRect.CopyRect(CRect(rect.Width() - 45, (m_CaptionHeight + 2 * m_BorderHeight - m_ButtonHeight) / 2, m_ButtonWidth, m_ButtonHeight));
	m_MaxRect.CopyRect(CRect(rect.Width() - 32, (m_CaptionHeight + 2 * m_BorderHeight - m_ButtonHeight) / 2, m_ButtonWidth, m_ButtonHeight));
	m_CloseRect.CopyRect(CRect(rect.Width() - 19, (m_CaptionHeight + 2 * m_BorderHeight - m_ButtonHeight) / 2, m_ButtonWidth, m_ButtonHeight));

	Invalidate();

}

BOOL CDemoDlg::OnNcActivate(BOOL bActive)
{
	OnPaint();
	return CDialog::OnNcActivate(bActive);
}

void CDemoDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	OnPaint();
}

void CDemoDlg::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	CDialog::OnNcMouseMove(nHitTest, point);
	CRect tempIni, tempMin, tempMax, tempClose, ClientRect;

	CDC* pWindowDC = GetWindowDC();
	CDC memDC;
	memDC.CreateCompatibleDC(pWindowDC);

	BITMAPINFO bInfo;
	HBITMAP hBitmap;
	CBitmap LeftLine;
	hBitmap = LoadBMP(IDR_BMP_GG);
	int x, y;

	GetWindowRect(ClientRect);
	tempIni.CopyRect(CRect(m_IniRect.left + ClientRect.left, ClientRect.top + m_IniRect.top, m_IniRect.right + m_IniRect.left + ClientRect.left, m_IniRect.bottom + m_IniRect.top + ClientRect.top));
	tempMin.CopyRect(CRect(m_MinRect.left + ClientRect.left, ClientRect.top + m_MinRect.top, m_MinRect.right + m_MinRect.left + ClientRect.left, m_MinRect.bottom + m_MinRect.top + ClientRect.top));
	tempMax.CopyRect(CRect(m_MaxRect.left + ClientRect.left, ClientRect.top + m_MaxRect.top, m_MaxRect.right + m_MaxRect.left + ClientRect.left, m_MaxRect.bottom + m_MaxRect.top + ClientRect.top));
	tempClose.CopyRect(CRect(m_CloseRect.left + ClientRect.left, ClientRect.top + m_CloseRect.top, m_CloseRect.right + m_CloseRect.left + ClientRect.left, m_CloseRect.bottom + m_CloseRect.top + ClientRect.top));

	if (tempIni.PtInRect(point)) //鼠标在初始化按钮上移动时,更改按钮显示的位图
	{

		LeftLine.Attach(hBitmap);
		LeftLine.GetObject(sizeof(bInfo), &bInfo);

		x = bInfo.bmiHeader.biWidth;
		y = bInfo.bmiHeader.biHeight;
		memDC.SelectObject(&LeftLine);
		pWindowDC->StretchBlt(m_IniRect.left, m_IniRect.top, m_IniRect.right, m_IniRect.bottom, &memDC, 0, 0, x, y, SRCCOPY);
		m_IsDrawForm = FALSE;
		m_ButtonState = bsIni;
		LeftLine.DeleteObject();
	}
	else if (tempMin.PtInRect(point))//鼠标在最小化按钮上移动时,更改按钮显示的位图
	{
		LeftLine.Attach(hBitmap);
		LeftLine.GetObject(sizeof(bInfo), &bInfo);

		x = bInfo.bmiHeader.biWidth;
		y = bInfo.bmiHeader.biHeight;
		memDC.SelectObject(&LeftLine);
		pWindowDC->StretchBlt(m_MinRect.left, m_MinRect.top, m_MinRect.right, m_MinRect.bottom, &memDC, 0, 0, x, y, SRCCOPY);
		m_IsDrawForm = FALSE;
		m_ButtonState = bsMin;
		LeftLine.DeleteObject();
	}
	else if (tempMax.PtInRect(point))
	{
		LeftLine.Attach(hBitmap);
		LeftLine.GetObject(sizeof(bInfo), &bInfo);

		x = bInfo.bmiHeader.biWidth;
		y = bInfo.bmiHeader.biHeight;
		memDC.SelectObject(&LeftLine);
		pWindowDC->StretchBlt(m_MaxRect.left, m_MaxRect.top, m_MaxRect.right, m_MaxRect.bottom, &memDC, 0, 0, x, y, SRCCOPY);
		m_IsDrawForm = FALSE;
		if (m_IsMax)
		{
			m_ButtonState = bsMax;
		}
		else
		{
			m_ButtonState = bsRes;
		}

		LeftLine.DeleteObject();
	}
	else if (tempClose.PtInRect(point))
	{
		LeftLine.Attach(hBitmap);
		LeftLine.GetObject(sizeof(bInfo), &bInfo);

		x = bInfo.bmiHeader.biWidth;
		y = bInfo.bmiHeader.biHeight;
		memDC.SelectObject(&LeftLine);
		pWindowDC->StretchBlt(m_CloseRect.left, m_CloseRect.top, m_CloseRect.right, m_CloseRect.bottom, &memDC, 0, 0, x, y, SRCCOPY);
		m_IsDrawForm = FALSE;
		m_ButtonState = bsClose;
		LeftLine.DeleteObject();
	}
	else
	{
		m_ButtonState = bsNone;
		if (m_IsDrawForm == FALSE)
			DrawForm();
		//	m_IsDrawForm = TRUE;
	}
	ReleaseDC(&memDC);
}

void CDemoDlg::DrawForm()
{

	//获取窗口设备上下文
	CDC* pWindowDC = GetWindowDC();
	HBITMAP hBitmap;
	CBitmap LeftLine;
	hBitmap = LoadBMP(IDR_BMP_CC);
	BITMAPINFO bitinfo;

	CDC memDC;
	memDC.CreateCompatibleDC(pWindowDC);

	CRect Clientrect;
	GetClientRect(Clientrect);

	int leftwidth = 0; //左标题的宽度
	int rightwidth = 0; //右标题的宽度
	int leftlinewidth = 0; //左边线宽度
	LeftLine.Attach(hBitmap);
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	rightwidth = bitinfo.bmiHeader.biWidth;
	LeftLine.DeleteObject();

	int x, y;
	//绘制左边线

	//获取位图大小
	hBitmap = LoadBMP(IDR_BMP_DD);
	LeftLine.Attach(hBitmap);

	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	leftlinewidth = x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;

	memDC.SelectObject(&LeftLine);
	pWindowDC->StretchBlt(1 - m_BorderWidth, m_CaptionHeight + 1, x + 1, Clientrect.Height() + 2 * m_BorderHeight + 5, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();

	/*****************************绘制左标题**************************************/
	hBitmap = LoadBMP(IDR_BMP_BB);
	LeftLine.Attach(hBitmap);
	//获取位图大小
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	leftwidth = x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(-m_BorderWidth, 0, x, m_CaptionHeight + 4, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************绘制左标题**************************************/

	/*****************************绘制中间标题**************************************/
	hBitmap = LoadBMP(IDR_BMP_AA);
	LeftLine.Attach(hBitmap);
	//获取位图大小
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(leftwidth - 1, 0, Clientrect.Width() - leftwidth - rightwidth, m_CaptionHeight + 4, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************绘制中间标题***************************************/

	/*****************************绘制右标题**************************************/
	hBitmap = LoadBMP(IDR_BMP_CC);
	LeftLine.Attach(hBitmap);
	//获取位图大小
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;

	pWindowDC->StretchBlt(Clientrect.Width() - x - 1, 0, x + m_BorderWidth + 9, m_CaptionHeight + 4, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************绘制右标题***************************************/

	/*****************************绘制右边框**************************************/
	hBitmap = LoadBMP(IDR_BMP_DD);
	LeftLine.Attach(hBitmap);
	//获取位图大小
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(Clientrect.Width() + m_BorderWidth + 2, m_CaptionHeight + 1, x + m_BorderWidth, Clientrect.Height() + 2 * m_BorderHeight + 5, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************绘制右边框***************************************/

	/*****************************绘制底边框**************************************/
	hBitmap = LoadBMP(IDR_BMP_EE);
	LeftLine.Attach(hBitmap);
	//获取位图大小
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(leftlinewidth - m_BorderWidth, Clientrect.Height() + m_CaptionHeight + 2, Clientrect.Width() + m_BorderWidth, y + 2, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************绘制底边框***************************************/

	/*****************************绘制初始化按钮**************************************/
	hBitmap = LoadBMP(IDR_BMP_FF);
	LeftLine.Attach(hBitmap);
	//获取位图大小
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(m_IniRect.left, m_IniRect.top, m_IniRect.right, m_IniRect.bottom, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************绘制初始化按钮***************************************/

	/*****************************绘制最小化按钮**************************************/
	hBitmap = LoadBMP(IDR_BMP_FF);
	LeftLine.Attach(hBitmap);
	//获取位图大小
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(m_MinRect.left, m_MinRect.top, m_MinRect.right, m_MinRect.bottom, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************绘制最小化按钮***************************************/

	/*****************************绘制最大化按钮**************************************/
	hBitmap = LoadBMP(IDR_BMP_FF);
	LeftLine.Attach(hBitmap);
	//获取位图大小
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(m_MaxRect.left, m_MaxRect.top, m_MaxRect.right, m_MaxRect.bottom, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************绘制最大化按钮***************************************/

	/*****************************绘制关闭按钮**************************************/
	hBitmap = LoadBMP(IDR_BMP_FF);
	LeftLine.Attach(hBitmap);
	//获取位图大小
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(m_CloseRect.left, m_CloseRect.top, m_CloseRect.right, m_CloseRect.bottom, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	m_IsDrawForm = TRUE;
	/*****************************绘制关闭按钮***************************************/
	ReleaseDC(&memDC);
	DrawFormCaption();

}

void CDemoDlg::OnNcPaint()
{
	DrawForm();
	m_IsDrawForm = TRUE;
}

void CDemoDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	CDialog::OnNcLButtonDown(nHitTest, point);

	switch (m_ButtonState)
	{
	case bsClose: //关闭窗口
	{
		DestroyWindow();
	}
	break;
	case bsIni: //还原窗口到初始大小和位置
	{
		m_IsMax = TRUE;
		MoveWindow(m_OrigonRect.left, m_OrigonRect.top, m_OrigonRect.Width(), m_OrigonRect.Height());
	}
	break;
	case bsMin: //
	{
		CWnd* pDesk = GetDesktopWindow();
		CRect rect;
		pDesk->GetClientRect(rect);
		SetWindowPos(0, (rect.Width() - m_OrigonRect.Width()) / 2, 2, m_OrigonRect.Width(), 0, SWP_SHOWWINDOW);
	}
	break;
	case bsMax:
	{
		m_ButtonState = bsMax;
		ShowWindow(SW_SHOWMAXIMIZED);
		m_IsMax = FALSE;
	}
	break;
	case bsRes:
	{
		ShowWindow(SW_RESTORE);
		m_IsMax = TRUE;
	}
	break;
	}
}

int CDemoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	return 0;
}

void CDemoDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if (m_FirstShow == FALSE)
	{
		m_FirstShow = TRUE;
		GetWindowRect(m_OrigonRect);
	}
}

HBRUSH CDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//绘制背景
	if (nCtlColor == CTLCOLOR_DLG)
	{
		HBITMAP hBitmap;
		CBitmap bitmap;
		hBitmap = LoadBMP(IDR_BMP_HH);
		bitmap.Attach(hBitmap);

		CBrush brush(&bitmap);
		CRect rect;
		GetClientRect(rect);
		pDC->SelectObject(&brush);
		bitmap.DeleteObject();
		pDC->FillRect(rect, &brush);
		return brush;
	}
	else if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
	}
	else
	{
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}	
}

void CDemoDlg::DrawFormCaption()
{
	if (!m_Caption.IsEmpty())
	{
		CDC* pDC = GetWindowDC();
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(m_CapitonColor);
		pDC->SetTextAlign(TA_CENTER);
		CRect rect;
		GetClientRect(rect);
		pDC->SelectObject(&m_CaptionFont);
		pDC->TextOut(rect.Width() / 2, m_CaptionHeight / 3, m_Caption);
	}
}

//阻止用户双击标题栏
void CDemoDlg::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	//CDialog::OnNcLButtonDblClk(nHitTest, point);
}

void CDemoDlg::OnBtnSignIn()
{

}

void CDemoDlg::OnBtnSignOut()
{
	DestroyWindow();
}

void CDemoDlg::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos)
{
	CDialog::OnWindowPosChanged(lpwndpos);

}
