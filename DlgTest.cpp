// DlgTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShowPixel.h"
#include "DlgTest.h"
#include "afxdialogex.h"


// CDlgTest �Ի���

IMPLEMENT_DYNAMIC(CDlgTest, CDialogEx)

CDlgTest::CDlgTest(CView *pView)
{
	m_pView = pView;
}

CDlgTest::~CDlgTest()
{
}

void CDlgTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}
BOOL CDlgTest::Create()
{
	return CDialog::Create(CDlgTest::IDD);
}

BEGIN_MESSAGE_MAP(CDlgTest, CDialog)
END_MESSAGE_MAP()


// CDlgTest ��Ϣ�������
