#include <afxwin.h>

class CMFCWin : public CFrameWnd
{
public:
	CMFCWin()
	{
		Create(NULL, _T("Sample MFC Window"));
	}

	void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP();


};

BEGIN_MESSAGE_MAP(CMFCWin, CFrameWnd)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CMFCWin::OnLButtonDown(UINT nFlags, CPoint point)
{
	CFrameWnd::OnLButtonDown(nFlags, point);
	MessageBox(_T("L-Button Down"));
}

class CMFCApp : public CWinApp
{
	CMFCWin *m_pMFCWnd;
public:
	BOOL InitInstance()
	{
		m_pMFCWnd = new CMFCWin();
		m_pMainWnd = m_pMFCWnd;
		m_pMainWnd->ShowWindow(SW_SHOW);

		return true;

	}
};

CMFCApp theApp;