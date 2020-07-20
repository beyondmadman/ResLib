
// DemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"
#include "afxdialogex.h"
#include "ResLoad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDemoDlg �Ի���



CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: m_IsDrawForm(FALSE), m_ButtonState(bsNone), CDialog(IDD_DEMO_DIALOG, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = LoadICO(IDR_ICO_II);

	m_FirstShow = FALSE;
	m_IsMax = TRUE;
	m_CapitonColor = RGB(0, 0, 255);
	m_Caption = "ϵͳ��¼";
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


// CDemoDlg ��Ϣ�������

BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_BorderHeight = GetSystemMetrics(SM_CYBORDER);
	m_BorderWidth = GetSystemMetrics(SM_CXBORDER);
	m_CaptionHeight = GetSystemMetrics(SM_CYCAPTION);

	//��ȡ��ťλͼ��С
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
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_ROMAN, _T("����"));

	DrawForm();

	m_lUsername.ModifyStyleEx(0, WS_EX_TRANSPARENT);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	DrawForm();
	m_IsDrawForm = TRUE;
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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

	if (tempIni.PtInRect(point)) //����ڳ�ʼ����ť���ƶ�ʱ,���İ�ť��ʾ��λͼ
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
	else if (tempMin.PtInRect(point))//�������С����ť���ƶ�ʱ,���İ�ť��ʾ��λͼ
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

	//��ȡ�����豸������
	CDC* pWindowDC = GetWindowDC();
	HBITMAP hBitmap;
	CBitmap LeftLine;
	hBitmap = LoadBMP(IDR_BMP_CC);
	BITMAPINFO bitinfo;

	CDC memDC;
	memDC.CreateCompatibleDC(pWindowDC);

	CRect Clientrect;
	GetClientRect(Clientrect);

	int leftwidth = 0; //�����Ŀ��
	int rightwidth = 0; //�ұ���Ŀ��
	int leftlinewidth = 0; //����߿��
	LeftLine.Attach(hBitmap);
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	rightwidth = bitinfo.bmiHeader.biWidth;
	LeftLine.DeleteObject();

	int x, y;
	//���������

	//��ȡλͼ��С
	hBitmap = LoadBMP(IDR_BMP_DD);
	LeftLine.Attach(hBitmap);

	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	leftlinewidth = x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;

	memDC.SelectObject(&LeftLine);
	pWindowDC->StretchBlt(1 - m_BorderWidth, m_CaptionHeight + 1, x + 1, Clientrect.Height() + 2 * m_BorderHeight + 5, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();

	/*****************************���������**************************************/
	hBitmap = LoadBMP(IDR_BMP_BB);
	LeftLine.Attach(hBitmap);
	//��ȡλͼ��С
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	leftwidth = x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(-m_BorderWidth, 0, x, m_CaptionHeight + 4, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************���������**************************************/

	/*****************************�����м����**************************************/
	hBitmap = LoadBMP(IDR_BMP_AA);
	LeftLine.Attach(hBitmap);
	//��ȡλͼ��С
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(leftwidth - 1, 0, Clientrect.Width() - leftwidth - rightwidth, m_CaptionHeight + 4, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************�����м����***************************************/

	/*****************************�����ұ���**************************************/
	hBitmap = LoadBMP(IDR_BMP_CC);
	LeftLine.Attach(hBitmap);
	//��ȡλͼ��С
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;

	pWindowDC->StretchBlt(Clientrect.Width() - x - 1, 0, x + m_BorderWidth + 9, m_CaptionHeight + 4, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************�����ұ���***************************************/

	/*****************************�����ұ߿�**************************************/
	hBitmap = LoadBMP(IDR_BMP_DD);
	LeftLine.Attach(hBitmap);
	//��ȡλͼ��С
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(Clientrect.Width() + m_BorderWidth + 2, m_CaptionHeight + 1, x + m_BorderWidth, Clientrect.Height() + 2 * m_BorderHeight + 5, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************�����ұ߿�***************************************/

	/*****************************���Ƶױ߿�**************************************/
	hBitmap = LoadBMP(IDR_BMP_EE);
	LeftLine.Attach(hBitmap);
	//��ȡλͼ��С
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(leftlinewidth - m_BorderWidth, Clientrect.Height() + m_CaptionHeight + 2, Clientrect.Width() + m_BorderWidth, y + 2, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************���Ƶױ߿�***************************************/

	/*****************************���Ƴ�ʼ����ť**************************************/
	hBitmap = LoadBMP(IDR_BMP_FF);
	LeftLine.Attach(hBitmap);
	//��ȡλͼ��С
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(m_IniRect.left, m_IniRect.top, m_IniRect.right, m_IniRect.bottom, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************���Ƴ�ʼ����ť***************************************/

	/*****************************������С����ť**************************************/
	hBitmap = LoadBMP(IDR_BMP_FF);
	LeftLine.Attach(hBitmap);
	//��ȡλͼ��С
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(m_MinRect.left, m_MinRect.top, m_MinRect.right, m_MinRect.bottom, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************������С����ť***************************************/

	/*****************************������󻯰�ť**************************************/
	hBitmap = LoadBMP(IDR_BMP_FF);
	LeftLine.Attach(hBitmap);
	//��ȡλͼ��С
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(m_MaxRect.left, m_MaxRect.top, m_MaxRect.right, m_MaxRect.bottom, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	/*****************************������󻯰�ť***************************************/

	/*****************************���ƹرհ�ť**************************************/
	hBitmap = LoadBMP(IDR_BMP_FF);
	LeftLine.Attach(hBitmap);
	//��ȡλͼ��С
	LeftLine.GetObject(sizeof(bitinfo), &bitinfo);
	memDC.SelectObject(&LeftLine);
	x = bitinfo.bmiHeader.biWidth;
	y = bitinfo.bmiHeader.biHeight;
	pWindowDC->StretchBlt(m_CloseRect.left, m_CloseRect.top, m_CloseRect.right, m_CloseRect.bottom, &memDC, 0, 0, x, y, SRCCOPY);
	LeftLine.DeleteObject();
	m_IsDrawForm = TRUE;
	/*****************************���ƹرհ�ť***************************************/
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
	case bsClose: //�رմ���
	{
		DestroyWindow();
	}
	break;
	case bsIni: //��ԭ���ڵ���ʼ��С��λ��
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
	//���Ʊ���
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

//��ֹ�û�˫��������
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
