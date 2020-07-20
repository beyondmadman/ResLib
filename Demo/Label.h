#if !defined(AFX_MYSTATIC_H__4698A259_51A5_4AC7_AA99_40BB1B4CC497__INCLUDED_)
#define AFX_MYSTATIC_H__4698A259_51A5_4AC7_AA99_40BB1B4CC497__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyStatic window

class CLabel : public CStatic
{
// Construction
public:
	CLabel();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabel)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLabel();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLabel)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATIC_H__4698A259_51A5_4AC7_AA99_40BB1B4CC497__INCLUDED_)
