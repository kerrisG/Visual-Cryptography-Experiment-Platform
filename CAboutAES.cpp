// CAboutAES.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "code.h"
#include "CAboutAES.h"
#include "afxdialogex.h"


// AboutAES �Ի���

IMPLEMENT_DYNAMIC(AboutAES, CDialog)

AboutAES::AboutAES(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ABOUTAES, pParent)
{

}

AboutAES::~AboutAES()
{
}

void AboutAES::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutAES, CDialog)
	ON_EN_CHANGE(IDC_RICHEDIT21, &AboutAES::OnEnChangeRichedit21)
END_MESSAGE_MAP()


// AboutAES ��Ϣ�������
BOOL AboutAES::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFile file1(_T("AboutAES.txt"), CFile::modeRead);           //���ļ�
	char *pBuf;
	int iLen = file1.GetLength();
	pBuf = new char[iLen + 1];
	file1.Read(pBuf, iLen);
	pBuf[iLen] = 0;
	file1.Close();
	CString Buf;
	Buf = pBuf;
	SetDlgItemText(IDC_RICHEDIT21, Buf);


	LOGFONT logfont;
	GetFont()->GetLogFont(&logfont);
	logfont.lfHeight = 18; // �ı�����߶�  

	CFont *font = new CFont();
	font->CreateFontIndirect(&logfont);
	GetDlgItem(IDC_RICHEDIT21)->SetFont(font);


	return TRUE;
}


void AboutAES::OnEnChangeRichedit21()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
