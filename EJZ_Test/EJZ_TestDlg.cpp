
// EJZ_TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EJZ_Test.h"
#include "EJZ_TestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEJZ_TestDlg �Ի���



CEJZ_TestDlg::CEJZ_TestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EJZ_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEJZ_TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEJZ_TestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CEJZ_TestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CEJZ_TestDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CEJZ_TestDlg ��Ϣ�������

BOOL CEJZ_TestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEJZ_TestDlg::OnPaint()
{
	InvalidateRect(NULL, FALSE);
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CEJZ_TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEJZ_TestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog FileDlg(TRUE, _T("BMP"), NULL,        //�����ļ��Ի���
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("λͼ�ļ�(*.BMP)|*.BMP||"));
	
	//CFileDialog FileDlg(TRUE, _T("JPG"), NULL,        //�����ļ��Ի���
	//	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("λͼ�ļ�(*.JPG)|*.JPG||"));

	if (FileDlg.DoModal() != IDOK)            //���ļ��Ի���
		return;
	CString pathname = FileDlg.GetPathName();//��ȡѡ���ļ���·��
	CFile file;                        //����һ���ļ�����
	if (!file.Open(pathname, CFile::modeRead | CFile::typeBinary))//���ƶȵķ�ʽ���ļ�
		return;
	m_nFileLen = file.GetLength();//��ȡ�ļ��ĳ���
	m_pBMPBuffer = new char[m_nFileLen + 1];//���ٷ�����
	if (!m_pBMPBuffer)            //����ؼ�������
		return;
	if (file.Read(m_pBMPBuffer, m_nFileLen) != m_nFileLen)//��ȡ�ļ��������ַ�������
		return;
	char            *pBuf = m_pBMPBuffer;

	SAFEARRAYBOUND    rgsabound[1];
	if (pBuf)
	{
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = m_nFileLen;
		psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
		for (long i = 0; i < (long)m_nFileLen; i++)
			SafeArrayPutElement(psa, &i, pBuf++);
		varBLOB.vt = VT_ARRAY | VT_UI1;
		varBLOB.parray = psa;
	}
}


void CEJZ_TestDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (m_hPhotoBitmap)
	{
		DeleteObject(m_hPhotoBitmap);
		m_hPhotoBitmap = NULL;
	}
	if (m_pBMPBuffer)
	{
		delete m_pBMPBuffer;
		m_pBMPBuffer = NULL;
	}
	//���������Ϊ�������ǰ��ͼ��

	char *pBuff = NULL;//���ڴ��λͼ���ڴ�ռ�
	_variant_t TheValue;//�洢������������
	TheValue = varBLOB;


	if (varBLOB.vt == (VT_ARRAY | VT_UI1))
	{
		pBuff = new char[m_nFileLen + 1];
		if (pBuff)
		{
			char *buff = NULL;
			SafeArrayAccessData(TheValue.parray, (void**)&buff);//��λͼ���ݷŵ�buff��ȥ
			memcpy(pBuff, buff, m_nFileLen);//��λͼ���ݷŵ�pBuff��

			SafeArrayUnaccessData(TheValue.parray);//�ͷ�

			m_pBMPBuffer = new char[m_nFileLen + 1];//���ٷ�����
			memcpy(m_pBMPBuffer, pBuff, m_nFileLen);

			//CImage image;
			//image.Load(m_pBMPBuffer);
			//	//Ȼ���ҵ���ʾ�ĵط� ����һ��pic�ؼ���IDΪID_PIC ��

			//	CStatic idc = CStatic)GetDlgItem(IDC_PIC);
			//CRect m_picRect1;
			//this->GetClientRect(&m_picRect1);
			//CDC* cd = this->GetWindowDC();
			//int width = image.GetWidth();
			//int height = image.GetHeight();
			//SetStretchBltMode(cd->m_hDC, HALFTONE);
			//image.Draw(cd->m_hDC, m_picRect1);
			//ReleaseDC(cd);

			//��λͼ�ڴ�����PBuffתΪHBITMAP
			HBITMAP hBitmap = NULL;//����һ��HBITMAP����������ʾλͼ��
			LPSTR                hDIB, lpBuffer = m_pBMPBuffer;
			LPVOID               lpDIBBits;
			BITMAPFILEHEADER     bmfHeader;
			DWORD                bmfHeaderLen;

			//���λͼ��ͷ��Ϣ
			bmfHeaderLen = sizeof(bmfHeader);
			//strncpy((LPSTR)&bmfHeader,(LPSTR)lpBuffer,bmfHeaderLen);
			memcpy(&bmfHeader, lpBuffer, bmfHeaderLen);
			//���ݻ�õ���Ϣͷ�ж��Ƿ���λͼ
			if (bmfHeader.bfType != (*(WORD*)"BM"))
			{
				AfxMessageBox(_T("this is not bitmap!"));
				return;
			}
			//��ȡλͼ����
			hDIB = lpBuffer + bmfHeaderLen;//��ָ���ƶ����ļ�ͷ�ĺ���
			BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB;
			BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB;
			lpDIBBits = (lpBuffer)+((BITMAPFILEHEADER *)lpBuffer)->bfOffBits;  //ƫ���ֽ���

																			   //����λͼ
			CClientDC dc(this);
			hBitmap = CreateDIBitmap(dc.m_hDC, &bmiHeader,
				CBM_INIT, lpDIBBits, &bmInfo, DIB_RGB_COLORS);

			//��ʾλͼ
			CBitmap bmp;                            //����λͼ����
			bmp.Attach(hBitmap);
			BITMAP bm;                                //����һ��λͼ�ṹ
			bmp.GetBitmap(&bm);
			CDC dcMem;
			dcMem.CreateCompatibleDC(GetDC());        //����һ�����ݵ�DC
			CBitmap *poldBitmap = (CBitmap*)dcMem.SelectObject(bmp); //��λͼѡ���豸������
			CRect lRect;                            //����һ������
			CStatic *pstatic = (CStatic*)GetDlgItem(IDC_Picture);
			pstatic->GetClientRect(&lRect);            //��ȡ�ؼ��Ŀͻ�����
			lRect.NormalizeRect();

			pstatic->GetDC()->StretchBlt(lRect.left, lRect.top, lRect.Width(), lRect.Height(),
				&dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY); //��ʾλͼ
			dcMem.SelectObject(&poldBitmap); //��ԭ�еľ��ѡ���豸����
			bmp.DeleteObject();



		}
	}

}