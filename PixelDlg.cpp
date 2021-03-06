// PixelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShowPixel.h"
#include "PixelDlg.h"
#include "MainFrm.h"
#include"ShowPixelView.h"
#include"ShowPixelDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CPixelDlg* pDlg;
/////////////////////////////////////////////////////////////////////////////
// CPixelDlg dialog

/*void ScrollShow(int Hpage,int Vpage,int pos)
{
	CMainFrame *pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;  
	CMDIChildWnd  *pChild = (CMDIChildWnd  *)pFrame->GetActiveFrame();
	CShowPixelView* pView = (CShowPixelView *)pChild->GetActiveView();
	CShowPixelDoc* pDoc= (CShowPixelDoc*)pView->GetDocument();
	extern CPixelDlg* pDlg;
	int x=pView->point1.x;
	int y=pView->point1.y;
	CRect rect;
	CString str1;
	pDlg->GetDlgItem(IDC_GrayDis)->GetClientRect(&rect);
	int xstep,ystep,x0,y0;
	xstep=rect.Width()/11;
	ystep=rect.Height()/11;
//	xstep=30;
//	ystep=30;
	x0=rect.Width()-xstep*10;//
	y0=rect.Height()-ystep*10;//
//	x0=xstep;
//	y0=ystep;
	CDC* dc=pDlg->GetDlgItem(IDC_GrayDis)->GetDC();
	dc->SelectStockObject(WHITE_BRUSH);
	dc->Rectangle(rect.left-2,rect.top-2,rect.right+2,rect.bottom+2);
		//画行列
	dc->TextOut(2,0,"V/H");
	for (int i=0;i<10;i++)//
	{
		str1.Format("%d",(x-5+i+Hpage*10+pos));//这里改5换成10
		dc->TextOut(x0+i*xstep,0,str1);
		str1.Format("%d",y-5+i+Vpage*10+pos);//
		dc->TextOut(0,y0+i*ystep,str1);
	}
////////////画出矩形中间的分割线
	dc->MoveTo(rect.left-2,y0-2);
	dc->LineTo(rect.right+2,y0-2);
	dc->MoveTo(x0-5,rect.top);
	dc->LineTo(x0-5,rect.bottom-2);
	CString strBits;
	int ii,jj;
	BYTE gray,r,g,b;
	for (int j=0;j<10;j++)
	{
//		jj=y-5+j;
		jj=y-5+j+Vpage*10+pos;
		jj=jj<0?0:jj;
		jj=jj>pDoc->nHeight?pDoc->nHeight:jj;
		//显示每一行像素
		for (i=0;i<10;i++)
		{
//			ii=x-5+i;
			ii=x-5+i+Hpage*10+pos;
			ii<0?0:ii;
			ii>pDoc->nWidth?pDoc->nWidth:ii;
			if (pDoc->nColorBits==8)
			{
				gray=pDoc->lpBits[jj*pDoc->nByteWidth+ii];
			}
			else if (pDoc->nColorBits==24)
			{
				gray=(BYTE)((pDoc->lpBits[jj*pDoc->nByteWidth+ii*3]*15
					+pDoc->lpBits[jj*pDoc->nByteWidth+ii*3+1]*75
					+pDoc->lpBits[jj*pDoc->nByteWidth+ii*3+2]*38)/128);
			}
			strBits.Format("%d",gray);
			switch(gray/50) 
			{
			case 0:
			case 1://0--29
				r=gray;b=gray;g=gray;
				break;
			case 2://30--59
				r=0;b=gray+100;g=0;
				break;
			case 3://60--79
				r=0;g=gray+50;b=0;
				break;
			case 4:
			case 5://200-255
				r=gray;g=0,b=0;
				break;
			}							
			dc->SetTextColor(RGB(r,g,b));
			dc->TextOut(x0+i*xstep,y0+(9-j)*ystep,strBits);//
///			cout[gray]++;
		}
	}
	ReleaseDC()
	

	
	

}*/
CPixelDlg::CPixelDlg(CView* pView)
{
	m_pView=pView;
	//Hpage1=0;
	FirstOpen=0;
}


void CPixelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPixelDlg)
		DDX_Control(pDX, IDC_V_SCROLLBAR, m_vScroll);
		DDX_Control(pDX, IDC_H_SCROLLBAR, m_hScroll);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_LIST2, m_imageInfoList);
}
BOOL CPixelDlg::Create()
{
	return CDialog::Create(CPixelDlg::IDD);
}

BEGIN_MESSAGE_MAP(CPixelDlg, CDialog)
	//{{AFX_MSG_MAP(CPixelDlg)
	ON_WM_VSCROLL()
	ON_WM_CANCELMODE()
	ON_WM_HSCROLL()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON, &CPixelDlg::OnBnClickedButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPixelDlg message handlers

BOOL CPixelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	pDlg=this;
	//SetScrollRange(SB_HORZ, 0, 100);
	//SetScrollRange(SB_VERT, 0, 100);

	m_hScroll.SetScrollRange(0, 20);
	m_vScroll.SetScrollRange(0, 20);
	m_hScroll.SetScrollPos(0);
	m_vScroll.SetScrollPos(0);

//	m_listBox.AddString("helloworld!");

	return TRUE;  // return TRUE unless you set the focus to a control
	             // EXCEPTION: OCX Property Pages should return FALSE
}





void CPixelDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	m_vScroll.GetScrollInfo(&scrollinfo0,SIF_ALL);
	scrollinfo0.nPage=3;
	m_vScroll.SetScrollInfo(&scrollinfo0);
	//HWND hwnd=GetDlgItem(IDC_GrayDis)->m_hWnd;
	switch(nSBCode)
	{
	case SB_LINEDOWN:
		scrollinfo0.nPos += 2;
		if(scrollinfo0.nPos>=20)
		{
			scrollinfo0.nPos=20;
		}
		m_vScroll.SetScrollPos(scrollinfo0.nPos,FALSE);
		//::ScrollWindow(hwnd,-30,0,NULL,NULL);//窗口滚动；
		break;
		
	case SB_LINEUP:
		scrollinfo0.nPos -= 2;
		if(scrollinfo0.nPos<=0)
		{
			scrollinfo0.nPos=0;
		}
		m_vScroll.SetScrollPos(scrollinfo0.nPos);
		break;

	case SB_PAGEUP:
		scrollinfo0.nPos -= 10;
		if(scrollinfo0.nPage >0)
		{ 
			scrollinfo0.nPage--;
		}
		else 
			scrollinfo0.nPage=0;
		if(scrollinfo0.nPos<=0)
		{
			scrollinfo0.nPos=0;
		}
		m_vScroll.SetScrollPos(scrollinfo0.nPos);
		break;
		
	case SB_PAGEDOWN:
		scrollinfo0.nPos += 10;
		if(scrollinfo0.nPage <3)
		{ 
			scrollinfo0.nPage++;
		}
		else 
			scrollinfo0.nPage=3;
		if(scrollinfo0.nPos>=20)
		{
			scrollinfo0.nPos=20;
		}
		
		m_vScroll.SetScrollPos(scrollinfo0.nPos);
		break;
		// 如果拖动滚动块滚动到指定位置，则pos赋值为nPos的值   

	case  SB_THUMBPOSITION:

		scrollinfo0.nPos = nPos;

		m_vScroll.SetScrollPos(scrollinfo0.nPos);

		break;

	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the

		scrollinfo0.nPos = nPos;     // position that the scroll box has been dragged to.

		m_vScroll.SetScrollPos(scrollinfo0.nPos);

		break;

	}
	Invalidate();
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CPixelDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CPixelDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default  
	m_hScroll.GetScrollInfo(&scrollinfo1,SIF_ALL);
	scrollinfo1.nPage=3;
	m_hScroll.SetScrollInfo(&scrollinfo1);
	//HWND hwnd=GetDlgItem(IDC_GrayDis)->m_hWnd;
	switch(nSBCode)
	{
	case SB_LINERIGHT:
		scrollinfo1.nPos += 2;
		if(scrollinfo1.nPos>=20)
		{
			scrollinfo1.nPos=20;
		}
		m_hScroll.SetScrollPos(scrollinfo1.nPos,FALSE);
		//::ScrollWindow(hwnd,-30,0,NULL,NULL);//窗口滚动；
		break;
		
	case SB_LINELEFT:
		scrollinfo1.nPos -= 2;
		if(scrollinfo1.nPos<=0)
		{
			scrollinfo1.nPos=0;
		}
		m_hScroll.SetScrollPos(scrollinfo1.nPos);
		break;

	case SB_PAGELEFT:
		scrollinfo1.nPos -= 10;
		if(scrollinfo1.nPage >0)
		{ 
			scrollinfo1.nPage--;
		}
		else 
			scrollinfo1.nPage=0;
		if(scrollinfo1.nPos<=0)
		{
			scrollinfo1.nPos=0;
		}
		m_hScroll.SetScrollPos(scrollinfo1.nPos);
		break;
		
	case SB_PAGERIGHT:
		scrollinfo1.nPos += 10;
		if(scrollinfo1.nPage <3)
		{ 
			scrollinfo1.nPage++;
		}
		else 
			scrollinfo1.nPage=3;
		if(scrollinfo1.nPos>=20)
		{
			scrollinfo1.nPos=20;
		}
		
		m_hScroll.SetScrollPos(scrollinfo1.nPos);
		break;
		// 如果拖动滚动块滚动到指定位置，则pos赋值为nPos的值   

	case  SB_THUMBPOSITION:

		scrollinfo1.nPos = nPos;

		m_hScroll.SetScrollPos(scrollinfo1.nPos);

		break;

	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the

		scrollinfo1.nPos = nPos;     // position that the scroll box has been dragged to.

		m_hScroll.SetScrollPos(scrollinfo1.nPos);

		break;

	}
	Invalidate();
	
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}





//DEL void CPixelDlg::OnCaptureChanged(CWnd *pWnd) 
//DEL {
//DEL 	// TODO: Add your message handler code here
//DEL 	
//DEL 	CDialog::OnCaptureChanged(pWnd);
//DEL }

void CPixelDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if(FirstOpen)
	{
	ScrollShow(scrollinfo1.nPos,scrollinfo0.nPos);
	}
	FirstOpen++;
	FirstOpen=FirstOpen%255;
	
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}


void CPixelDlg::ScrollShow(int pos0=0,int pos1=0)  //IDC_GrayDis画图
{
	CMainFrame *pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;  
	CMDIChildWnd  *pChild = (CMDIChildWnd  *)pFrame->GetActiveFrame();
	CShowPixelView* pView = (CShowPixelView *)pChild->GetActiveView();
	CShowPixelDoc* pDoc= (CShowPixelDoc*)pView->GetDocument();
	int x=pView->point1.x;
	int y=pView->point1.y;
	CRect rect;
	CString str1;

	int cout[256];
	int i;
	for (i = 0; i < 256; i++)
	{
		cout[i] = 0;
	}
	GetDlgItem(IDC_GrayDis)->GetClientRect(&rect);
	int xstep,ystep,x0,y0;
	xstep=rect.Width()/11;
	ystep=rect.Height()/11;

	x0=rect.Width()-xstep*10;//
	y0=rect.Height()-ystep*10;//

	CDC* dc=pDlg->GetDlgItem(IDC_GrayDis)->GetDC();
	dc->SelectStockObject(WHITE_BRUSH);
	dc->Rectangle(rect.left-2,rect.top-3,rect.right+3,rect.bottom+3);
		//画行列
	dc->TextOut(2,0,"V/H");
	for (int i=0;i<10;i++)//
	{
		str1.Format("%d",(x-5+i+pos0));//这里改5换成10
		dc->TextOut(x0+i*xstep,0,str1);
		str1.Format("%d",(y-5+i+pos1));//
		dc->TextOut(0,y0+i*ystep,str1);
	}
////////////画出矩形中间的分割线
	dc->MoveTo(rect.left-2,y0-2);
	dc->LineTo(rect.right+2,y0-2);
	dc->MoveTo(x0-5,rect.top);
	dc->LineTo(x0-5,rect.bottom-2);
	CString strBits;
	int ii,jj;
	BYTE gray,r,g,b;
	for (int j=0;j<10;j++)
	{
		jj=y-5+j+pos1;
		jj=jj<0?0:jj;
		jj=jj>pDoc->nHeight?pDoc->nHeight:jj;
		//显示每一行像素
		for (int i=0;i<10;i++)
		{
			ii=x-5+i+pos0;
			ii<0?0:ii;
			ii>pDoc->nWidth?pDoc->nWidth:ii;
			if (pDoc->nColorBits==8)
			{
				gray=pDoc->lpBits[jj*pDoc->nByteWidth+ii];
			}
			else if (pDoc->nColorBits==24)
			{
				gray=(BYTE)((pDoc->lpBits[jj*pDoc->nByteWidth+ii*3]*15
					+pDoc->lpBits[jj*pDoc->nByteWidth+ii*3+1]*75
					+pDoc->lpBits[jj*pDoc->nByteWidth+ii*3+2]*38)/128);
			}
			strBits.Format("%d",gray);
			switch(gray/50) 
			{
			case 0:
			case 1://0--29
				r=gray;b=gray;g=gray;
				break;
			case 2://30--59
				r=0;b=gray+100;g=0;
				break;
			case 3://60--79
				r=0;g=gray+50;b=0;
				break;
			case 4:
			case 5://200-255
				r=gray;g=0,b=0;
				break;
			}							
			dc->SetTextColor(RGB(r,g,b));
			dc->TextOut(x0+i*xstep,y0+(9-j)*ystep,strBits);//
			cout[gray]++;
		}
	}
	pDlg->GetDlgItem(IDC_GrayDis)->ReleaseDC(dc);


	//显示图像
	GetDlgItem(IDC_CLICKAREA)->GetClientRect(&rect);//对话框类的接口
	CDC* pdc = GetDlgItem(IDC_CLICKAREA)->GetDC();
	int xx = pView->point1.x;
	int yy = pView->point1.y;
	StretchDIBits(pdc->m_hDC, 0, 0, rect.Width(), rect.Height(), xx, yy, 100,100,
		pDoc->lpBits, (BITMAPINFO *)(pDoc->lpBitmap), DIB_RGB_COLORS, SRCCOPY);
	ReleaseDC(pdc);

	//m_pDlg->GetDlgItem(IDC_CLICKAREA)->GetClientRect(&rect);//对话框类的接口
	//CDC* pdc = m_pDlg->GetDlgItem(IDC_CLICKAREA)->GetDC();
	//int xx = x - 15 > 0 ? x - 15 : 0;
	//xx = xx<pDoc->nWidth - 30 ? xx : pDoc->nWidth - 30;
	//int yy = y - 15>0 ? y - 15 : 0;
	//yy = yy < pDoc->nHeight - 30 ? yy : pDoc->nHeight - 30;
	//StretchDIBits(pdc->m_hDC, 0, 0, rect.Width(), rect.Height(), xx, yy, 30, 30,
	//	pDoc->lpBits, (BITMAPINFO *)(pDoc->lpBitmap), DIB_RGB_COLORS, SRCCOPY);
	//ReleaseDC(pdc);

	//绘制直方图
	GetDlgItem(IDC_ZHIFANGTU)->GetClientRect(&rect);
	pdc = GetDlgItem(IDC_ZHIFANGTU)->GetDC();
	pdc->SelectStockObject(WHITE_BRUSH);
	pdc->Rectangle(rect);

	CPen mPen(PS_SOLID, 0, (COLORREF)0x000000ff);

	pdc->MoveTo(5, rect.Height() - 10); //移动到点
	pdc->LineTo(5, 5);  //画线
	pdc->LineTo(3, 10);
	pdc->MoveTo(5, 5);
	pdc->LineTo(7, 10);
	pdc->MoveTo(5, rect.Height() - 10);
	pdc->LineTo(rect.Width() - 5, rect.Height() - 10);
	pdc->LineTo(rect.Width() - 10, rect.Height() - 8);
	pdc->MoveTo(rect.Width() - 5, rect.Height() - 10);
	pdc->LineTo(rect.Width() - 10, rect.Height() - 12);
	pdc->SelectObject(&mPen);
	int h;
	for (i = 0; i<256; i++)
	{
		h = 5 * ((int)(cout[i] / 100.0*(rect.Height() - 15)));
		h = h>rect.Height() - 15 ? rect.Height() - 15 : h;
		pdc->MoveTo(6 + (int)(i / 256.0*(rect.Width() - 10)), rect.Height() - 10);
		pdc->LineTo(6 + (int)(i / 256.0*(rect.Width() - 10)),
			rect.Height() - 10 - h);
	}
	ReleaseDC(pdc);
    //Invalidate(0);

}


void CPixelDlg::OnBnClickedButton()
{
	// TODO:  在此添加控件通知处理程序代码

	
	CDialog::OnOK();
}
