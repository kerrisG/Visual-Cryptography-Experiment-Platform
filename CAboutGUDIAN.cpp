// CAboutGUDIAN.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "code.h"
#include "CAboutGUDIAN.h"
#include "afxdialogex.h"


// AboutGUDIAN �Ի���

IMPLEMENT_DYNAMIC(AboutGUDIAN, CDialog)

AboutGUDIAN::AboutGUDIAN(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ABOUTgudian, pParent)
{

}

AboutGUDIAN::~AboutGUDIAN()
{
}

void AboutGUDIAN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutGUDIAN, CDialog)
	ON_EN_CHANGE(IDC_RICHEDIT21, &AboutGUDIAN::OnEnChangeRichedit21)
	ON_BN_CLICKED(IDOK, &AboutGUDIAN::OnBnClickedOk)
END_MESSAGE_MAP()


// AboutGUDIAN ��Ϣ�������

BOOL AboutGUDIAN::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFile file1(_T("AboutGD.txt"), CFile::modeRead);           //���ļ�
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

void AboutGUDIAN::OnEnChangeRichedit21()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������


}


void AboutGUDIAN::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}
