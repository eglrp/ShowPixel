// ShowPixelDoc.h : interface of the CShowPixelDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOWPIXELDOC_H__58EDA2ED_507B_4911_9D74_29258D3D5257__INCLUDED_)
#define AFX_SHOWPIXELDOC_H__58EDA2ED_507B_4911_9D74_29258D3D5257__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CShowPixelDoc : public CDocument
{
protected: // create from serialization only
	CShowPixelDoc();
	DECLARE_DYNCREATE(CShowPixelDoc)

		// Attributes
public:
	//================================�����ͱ�������========================
	int nWidth;//ͼ����
	int nHeight;//ͼ��߶�
	int nColorBits;//ÿ��������ռ��λ��
	int nColor;//ͼ�����ɫ��
	int nLen;//ͼ���ļ��Ĵ�С�����ֽ�����
	int nByteWidth;//ͼ��ÿ�е��ֽ���
	BYTE * lpBitmap;//ָ��ͼ�����ֽڵ�ָ��
	BYTE * lpBits;//ָ��ͼ��ʵ�����ݵ�ָ��
	// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowPixelDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CShowPixelDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CShowPixelDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWPIXELDOC_H__58EDA2ED_507B_4911_9D74_29258D3D5257__INCLUDED_)
