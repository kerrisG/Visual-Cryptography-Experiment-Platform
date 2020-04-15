// CAboutHELP.cpp : 实现文件
//

#include "stdafx.h"
#include "code.h"
#include "CAboutHELP.h"
#include "afxdialogex.h"


// AboutHELP 对话框

IMPLEMENT_DYNAMIC(AboutHELP, CDialog)

AboutHELP::AboutHELP(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ABOUTHELP, pParent)
{

}

AboutHELP::~AboutHELP()
{
}

void AboutHELP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutHELP, CDialog)
END_MESSAGE_MAP()


// AboutHELP 消息处理程序
BOOL AboutHELP::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFile file1(_T("AboutHELP.txt"), CFile::modeRead);           //打开文件
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
	logfont.lfHeight = 18; // 改变字体高度  

	CFont *font = new CFont();
	font->CreateFontIndirect(&logfont);
	GetDlgItem(IDC_RICHEDIT21)->SetFont(font);


	return TRUE;
}