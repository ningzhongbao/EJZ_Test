
// EJZ_TestDlg.h : ͷ�ļ�
//

#pragma once


// CEJZ_TestDlg �Ի���
class CEJZ_TestDlg : public CDialogEx
{
// ����
public:
	CEJZ_TestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EJZ_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	HBITMAP m_hPhotoBitmap;
	char * m_pBMPBuffer;
	
	VARIANT            varBLOB;
	SAFEARRAY        *psa;

	DWORD m_nFileLen;
public:
	afx_msg void OnBnClickedButton1();

	afx_msg void OnBnClickedButton2();
};
