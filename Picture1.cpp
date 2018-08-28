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
	, m_DyId(_T(""))
	, m_LcId(_T(""))
	, m_LcIdd(_T(""))
	, m_ShId(_T(""))
{
	m_Protocol.Begin[0] = '7E';
	m_Protocol.Begin[1] = '7E';
	m_Protocol.Begin[2] = '7E';
	m_Protocol.Begin[3] = '8B';


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
	DDX_Text(pDX, IDC_Ele, m_DyId);
	DDX_Text(pDX, IDC_LD, m_LcId);
	DDX_Text(pDX, IDC_CH, m_LcIdd);
	DDX_Text(pDX, IDC_SH, m_ShId);
	DDX_Control(pDX, IDC_LIST2, m_ListBox);
}


BEGIN_MESSAGE_MAP(CPicture1, CDialogEx)
	ON_BN_CLICKED(IDC_Add_PerFace, &CPicture1::OnBnClickedAddPerface)
	ON_BN_CLICKED(IDC_Dele_PerFace, &CPicture1::OnBnClickedDelePerface)
	ON_BN_CLICKED(IDC_Cannel, &CPicture1::OnBnClickedCannel)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_IDOK, &CPicture1::OnBnClickedIdok)
	ON_BN_CLICKED(IDC_Open_FacePath, &CPicture1::OnBnClickedOpenFacepath)
	ON_LBN_SELCHANGE(IDC_LIST2, &CPicture1::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_Dele_List, &CPicture1::OnBnClickedDeleList)
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

char * CPicture1::LoadImaData(CString imagPath)
{
	CFile     file;                        //����һ���ļ�����
	if (!file.Open(imagPath, CFile::modeRead | CFile::typeBinary))//���ƶȵķ�ʽ���ļ�
	{
		return NULL;
	}

	m_nFileLen = file.GetLength();//��ȡ�ļ��ĳ���
	pBufImgDate = new char[m_nFileLen + 1];//���ٷ�����
	if (!pBufImgDate)            //����ؼ�������
	{
		return "Error";
	}
	if (file.Read(pBufImgDate, m_nFileLen) != m_nFileLen)//��ȡ�ļ��������ַ�������
	{
		return "Error";
	}

	return pBufImgDate;
}

void CPicture1::OnBnClickedAddPerface()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*UpdateData(TRUE);
	m_image_path = _ShowFileDialog();

	LoadImaData(m_image_path);



	m_Image_String = m_image_path;

	UpdateData(FALSE);

	Invalidate(TRUE);*/
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

void JxFileName(CString jpgName)
{


}

void JxFNToArr(int nCount, int nMemLen, CString strTemp, unsigned char sendLine[10])
{
	bool   bFalge;
	int    posEnd;
	int    j;
	int    k;
	char *ch;
	
	int nPos = strTemp.Find("#");       //���ҵ�һ��","��λ��

	for (int i = 0; i < nMemLen; i++)
	{
		//��ȡ����
		if (0 == nCount && i < nPos)
		{
			CString tmp = strTemp.Mid(0, nPos);
			int val;
			k = 0;
			ch = tmp.GetBuffer(8);
			while (*ch)
			{
				sscanf(ch, "%02x", &val);
				sendLine[14 + k] = val;
				ch++;
				k++;
			}

			i = nPos;

			/*sendLine[14 + i] = strTemp.GetAt(i);
			i++;
			sendLine[14 + i] = strTemp.GetAt(i);*/
		}
		if (0 == nCount && i == nPos)
		{
			bFalge = true;
		}
		if (bFalge)
		{
			int nLen = strTemp.Delete(0, nPos + 1);
			//i += nPos;
			strTemp = strTemp.Right(nLen);
			nPos = strTemp.Find("#");       //���ҵ�2��","��λ��
			nCount++;

			bFalge = false;
		}

		//��ȡ���֤��
		if (1 == nCount && j < nPos)
		{
			CString tmp = strTemp.Mid(0, nPos);
			int val;
			k = 0;
			ch = tmp.GetBuffer(18);
			while (*ch)
			{
				sscanf(ch, "%02x", &val);
				sendLine[30 + k] = val;
				ch += 2;
				k++;
			}
			j = nPos;
		}
		else if (1 == nCount && j == nPos)
		{
			bFalge = true;
		}
		if (bFalge)
		{
			int nLen = strTemp.Delete(0, nPos + 1);
			strTemp = strTemp.Right(nLen);
			//i += nLen;
			//С��¥�㣬��Ԫ��¥�����Һ�
			posEnd = strTemp.ReverseFind('.');
			strTemp = strTemp.Left(posEnd);
			//
			nCount++;
			j = 0;
			bFalge = false;
		}

		//��ȡС����Ϣ
		if (2 == nCount && j < posEnd)
		{
			int val;
			k = 0;
			ch = strTemp.GetBuffer(8);
			while (*ch)
			{
				sscanf(ch, "%02x", &val);
				sendLine[4 + k] = val;
				ch += 2;
				k++;
			}
			j = posEnd;
		}
	}
}

void CPicture1::OnBnClickedIdok()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	//��������
	unsigned char sendLine[200];
	CString strTemp;
	vector<CString>::iterator tT;         //����һ��������t

	
										  //������ʼ��
	int nCount = 0;
	int nMemLen = 0;
	
	for (tT = m_FileList.begin(); tT != m_FileList.end(); tT++)
	{
		memset(sendLine, 0, sizeof(sendLine));
		nCount = 0;
		nMemLen = tT->GetLength();
		strTemp = *tT;		

		sendLine[0] = 0x7e;
		sendLine[1] = 0x7e;
		sendLine[2] = 0x7e;
		sendLine[3] = 0x8b;
		sendLine[48] = 0x0d;

		JxFNToArr(nCount, nMemLen, strTemp, sendLine);


		MessageBox((LPCTSTR)sendLine, NULL, MB_OK);
	}

}

void CPicture1::OnBnClickedOpenFacepath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���  

	if (dlg.DoModal() == IDOK)
		m_csFileName = dlg.GetPathName();
	else
		m_csFileName.Empty();

	int iEndPos = 0;
	iEndPos = m_csFileName.ReverseFind('\\');
	csDirParth = m_csFileName.Left(iEndPos);

	m_FileList.clear();
	GetFileFromDir(csDirParth);

	for (int i = 0; i < m_FileList.size(); i++)
	{
		m_ListBox.AddString(m_FileList.at(i));

	}
}

void CPicture1::GetFileFromDir(CString csDirPath)
{
	csDirPath += "\\*.jpg";

	HANDLE file;
	WIN32_FIND_DATA fileData;
	char line[1024];
	char fn[1000];

	file = FindFirstFile(csDirPath.GetBuffer(0), &fileData);
	m_FileList.push_back(fileData.cFileName);

	bool bState = false;
	bState = FindNextFile(file, &fileData);
	while (bState)
	{
		m_FileList.push_back(fileData.cFileName);
		bState = FindNextFile(file, &fileData);
	}
}

void CPicture1::Ui_Show_Info(CString m_filename)
{
	//����
	int pos = m_filename.Find("#");
	m_Name = m_filename.Mid(0, pos);
	
	//ɾ���Ѿ���ȡ������
	int nLen = m_filename.Delete(0, pos + 1);
	m_filename = m_filename.Right(nLen);
	
	//���֤
	pos = m_filename.Find("#");
	if (-1 != pos)
	{
		m_IDCard = m_filename.Mid(0, pos);
		//ɾ���Ѿ���ȡ�����֤
		nLen = m_filename.Delete(0, pos + 1);
		m_filename = m_filename.Right(nLen);
		
		//С��¥�㣬��Ԫ��¥�����Һ�
		int posEnd = m_filename.ReverseFind('.');
		m_filename = m_filename.Left(posEnd);
		//��Ԫ��
		m_DyId = m_filename.Left(2); //����ߵ���������
									 //¥���
		nLen = m_filename.Delete(0, 2);
		m_filename = m_filename.Right(nLen);
		m_LcId = m_filename.Left(2);
		//¥����
		nLen = m_filename.Delete(0, 2);
		m_filename = m_filename.Right(nLen);
		m_LcIdd = m_filename.Left(2);
		//�Һ�
		m_ShId = m_filename.Right(2);//���ұߵ���������	
	}
}

void CPicture1::OnLbnSelchangeList2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	int nIndex;//����ָ����ѡ���������ŵ�INT����    
	nIndex = 0;
	CString m_filename;

	nIndex = m_ListBox.GetCurSel();//��ȡListBox��ѡ�����������  
	m_ListBox.GetText(nIndex, m_filename);//��ѡ���������Ŵ���GetText�����У���ѡ�������ݸ���m_filename���� 

	m_AllPath = csDirParth + "\\" + m_filename;

	LoadImaData(m_AllPath);

	m_Image_String = m_AllPath;
	m_image_path = m_AllPath;

	Ui_Show_Info(m_filename);

	UpdateData(FALSE);
	Invalidate(FALSE);
}


void CPicture1::OnBnClickedDeleList()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ListBox.ResetContent();
	m_LcId = "";
	m_LcIdd = "";
	m_DyId = "";
	m_ShId = "";
	m_Name = "";
	m_IDCard = "";

	UpdateData(FALSE);
}
