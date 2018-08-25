// Picture1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "Picture1.h"
#include "afxdialogex.h"


// CPicture1 �Ի���

IMPLEMENT_DYNAMIC(CPicture1, CDialogEx)

CPicture1::CPicture1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PERSON_INFO, pParent)
	, m_Image_String(_T(""))
	, m_Name(_T(""))
	, m_IDCard(_T(""))
	, m_XQName(_T(""))
	, m_DyId(_T(""))
	, m_LcId(_T(""))
	, m_LcIdd(_T(""))
	, m_ShId(_T(""))
{

}

CPicture1::~CPicture1()
{
}

void CPicture1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Picture, m_Image);
	DDX_Text(pDX, IDC_Face_Path, m_Image_String);
	DDX_Text(pDX, IDC_Name, m_Name);
	DDX_Text(pDX, IDC_ID, m_IDCard);
	DDX_Text(pDX, IDC_XQName, m_XQName);
	DDX_Text(pDX, IDC_Ele, m_DyId);
	DDX_Text(pDX, IDC_LD, m_LcId);
	DDX_Text(pDX, IDC_CH, m_LcIdd);
	DDX_Text(pDX, IDC_SH, m_ShId);
}


BEGIN_MESSAGE_MAP(CPicture1, CDialogEx)
	ON_BN_CLICKED(IDC_Add_PerFace, &CPicture1::OnBnClickedAddPerface)
	ON_BN_CLICKED(IDC_Dele_PerFace, &CPicture1::OnBnClickedDelePerface)
	ON_BN_CLICKED(IDC_Cannel, &CPicture1::OnBnClickedCannel)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_IDOK, &CPicture1::OnBnClickedIdok)
END_MESSAGE_MAP()


// CPicture1 ��Ϣ�������


void _ShowCtrlImage(CStatic* imageCtrl, CString strImagePath, CString strExt)
{
	if (strImagePath.IsEmpty() || -1 == strImagePath.Find(strExt.GetBuffer(0)))
		return;

	CImage image;
	image.Load(strImagePath);

	//��������������Ҫ�����ǣ���ȡ�Ի��������Picture Control��width��height��
	//�����õ�ͼƬ����rectPicture������ͼƬ����rectPicture��ͼƬ���д���
	//������ͼƬ���Ի�����Picture Control����
	CRect rectControl;                        //�ؼ����ζ���
	CRect rectPicture;                        //ͼƬ���ζ���

	int x = image.GetWidth();
	int y = image.GetHeight();
	imageCtrl->GetClientRect(rectControl);

	CDC *pDc = imageCtrl->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(),
		CSize((int)rectControl.Width(),
		(int)rectControl.Height()));

	imageCtrl->SetBitmap(NULL);

	//�������ַ������ɻ���ͼƬ
	image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); //��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������
	//image.Draw(pDc->m_hDC, rectPicture);                //��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������

	image.Destroy();
	imageCtrl->ReleaseDC(pDc);
}


CString _ShowFileDialog()
{
	CFileDialog fileDlg(TRUE, _T("jpg"), NULL, 0,
		_T("image Files(*.jpg)|*.JPG|All Files (*.*) |*.*"), NULL);
	fileDlg.DoModal();
	return fileDlg.GetPathName();
}

void CPicture1::OnPaint()
{
	CPaintDC dc(this);

	_ShowCtrlImage(&m_Image, m_image_path, CString(".jpg"));

}

void CPicture1::OnBnClickedAddPerface()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_image_path = _ShowFileDialog();

	m_Image_String = m_image_path;


	UpdateData(FALSE);

	Invalidate(TRUE);
}


void CPicture1::OnBnClickedDelePerface()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_image_path = "";
	m_Image_String = m_image_path;

	UpdateData(FALSE);

	Invalidate(TRUE);
}


void CPicture1::OnBnClickedCannel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


void CPicture1::OnBnClickedIdok()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	MessageBox(m_Name.GetBuffer(0), NULL, MB_OK);
}
