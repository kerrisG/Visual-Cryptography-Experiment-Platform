// CAboutRSA.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "code.h"
#include "CAboutRSA.h"
#include "afxdialogex.h"


// AboutRSA �Ի���

IMPLEMENT_DYNAMIC(AboutRSA, CDialog)

AboutRSA::AboutRSA(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ABOUTRSA, pParent)
{

}

AboutRSA::~AboutRSA()
{
}

void AboutRSA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutRSA, CDialog)
END_MESSAGE_MAP()


// AboutRSA ��Ϣ�������
BOOL AboutRSA::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFile file1(_T("AboutRSA.txt"), CFile::modeRead);           //���ļ�
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