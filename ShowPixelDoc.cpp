// ShowPixelDoc.cpp : implementation of the CShowPixelDoc class
//

#include "stdafx.h"
#include "ShowPixel.h"

#include "ShowPixelDoc.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowPixelDoc

IMPLEMENT_DYNCREATE(CShowPixelDoc, CDocument)

BEGIN_MESSAGE_MAP(CShowPixelDoc, CDocument)
//{{AFX_MSG_MAP(CShowPixelDoc)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowPixelDoc construction/destruction

CShowPixelDoc::CShowPixelDoc()
{
	// TODO: add one-time construction code here
	lpBits=NULL;
}

CShowPixelDoc::~CShowPixelDoc()
{
}

BOOL CShowPixelDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CShowPixelDoc serialization

void CShowPixelDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CShowPixelDoc diagnostics

#ifdef _DEBUG
void CShowPixelDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CShowPixelDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShowPixelDoc commands

BOOL CShowPixelDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	HANDLE hFile=::CreateFile(lpszPathName,GENERIC_READ,
		FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==0)
	{
		TRACE0("���ܴ��ļ���������ѡ��!\n");
		return FALSE;
	}
	
	DWORD WriteNum;
	BITMAPFILEHEADER BFH; //�ļ�ͷ
	ReadFile(hFile,&BFH,14,&WriteNum,NULL);//���ļ�ͷ��14�ֽ�
	if((BFH.bfType!='MB')||WriteNum!=sizeof(BITMAPFILEHEADER))
	{
		//printf("����BMP�ļ��������ݴ���!");
		AfxMessageBox("����BMP�ļ��������ݴ���...");
		TRACE0("����BMP�ļ��������ݴ���...");
		CloseHandle(hFile);
		return FALSE;
	}
    nLen=GetFileSize(hFile,NULL)-sizeof(BITMAPFILEHEADER);
	
	lpBitmap=new BYTE[nLen];
	
	ReadFile(hFile,lpBitmap,nLen,&WriteNum,NULL);
	
	BITMAPINFOHEADER *BIH=  (BITMAPINFOHEADER  *)lpBitmap; //��Ϣͷ
	
	nWidth=BIH->biWidth;
	nHeight=BIH->biHeight;
	nColorBits=BIH->biBitCount;
    nByteWidth=(nWidth*nColorBits+31)/32*4;
	nColor=(nColorBits>8)?0:(int)(pow(2.0,nColorBits));//
	lpBits=lpBitmap+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*nColor;
	
	CloseHandle(hFile);   //
	return TRUE;
}
