#pragma once


// CDlgTest �Ի���

class CDlgTest : public CDialog
{
	DECLARE_DYNAMIC(CDlgTest)

public:
	CDlgTest(CView*);   // ��׼���캯��
	BOOL Create();
	virtual ~CDlgTest();
	CView* m_pView;
// �Ի�������
	enum { IDD = IDD_DIALOGTest };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
