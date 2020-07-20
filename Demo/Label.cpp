// LStatic.cpp : implementation file
//

#include "stdafx.h"
#include "Label.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLabel

CLabel::CLabel()
{
}

CLabel::~CLabel()
{

}


BEGIN_MESSAGE_MAP(CLabel, CStatic)
	//{{AFX_MSG_MAP(CLabel)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyStatic message handlers



BOOL CLabel::PreCreateWindow(CREATESTRUCT& cs)
{
	return CStatic::PreCreateWindow(cs);
}

HBRUSH CLabel::CtlColor(CDC* pDC, UINT nCtlColor)
{
	pDC->SetBkMode(TRANSPARENT);	

	return NULL;

}
