#pragma once
#include "afxwin.h"


// CPicture1 �Ի���

class CPicture1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPicture1)

public:
	CPicture1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPicture1();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSON_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

public:
	CString m_image_path;

public:	
	CStatic m_Image;
	afx_msg void OnBnClickedAddPerface();
	afx_msg void OnBnClickedDelePerface();
	CString m_Image_String;
	afx_msg void OnBnClickedCannel();
	CString m_Name;
	CString m_IDCard;
	CString m_XQName;
	CString m_DyId;
	CString m_LcId;
	CString m_LcIdd;
	CString m_ShId;
	afx_msg void OnBnClickedIdok();
};
