#pragma once


// CGetOwerInfo 对话框

class CGetOwerInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CGetOwerInfo)

public:
	CGetOwerInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGetOwerInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GetOwerInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
