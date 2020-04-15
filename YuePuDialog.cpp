// YuePuDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "code.h"
#include "YuePuDialog.h"
#include "afxdialogex.h"
#include "utils.h"

// CYuePuDialog 对话框

IMPLEMENT_DYNAMIC(CYuePuDialog, CDialogEx)

CYuePuDialog::CYuePuDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_YUEPU_DLG, pParent)
	, m_plain(_T(""))
	, m_shiftNum(10)
{
	yuepu = true;

	CString dir1 = str_to_CStr(GetAppExePath()) + "\\Sheetmusic\\";
	CString dir2 = str_to_CStr(GetAppExePath()) + "\\Dancekids\\";
	for (int i = 0; i < 26; i++)
	{
		char num[2] = { 0 };
		num[0] = 'a' + i;

		CString file1 = dir1 + str_to_CStr(num) + _T(".bmp");
		musicImage[i].Load(file1); //乐谱
		CString file2 = dir2 + str_to_CStr(num) + _T(".bmp");
		danceImage[i].Load(file2);  //跳舞的小人
	}
}

CYuePuDialog::~CYuePuDialog()
{
}

void CYuePuDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT28, m_plain);
	DDX_Text(pDX, IDC_EDIT1, m_shiftNum);
}


BEGIN_MESSAGE_MAP(CYuePuDialog, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO_MUSIC, &CYuePuDialog::OnBnClickedRadioMusic)
	ON_BN_CLICKED(IDC_RADIO_DANCE, &CYuePuDialog::OnBnClickedRadioDance)	
	ON_BN_CLICKED(IDC_RADIO_REPLACE, &CYuePuDialog::OnBnClickedRadioReplace)
	ON_BN_CLICKED(IDC_RADIO_MOVE, &CYuePuDialog::OnBnClickedRadioMove)
	ON_BN_CLICKED(IDC_BTN_GEN, &CYuePuDialog::OnBnClickedBtnGen)
	ON_BN_CLICKED(IDC_BTN_MAKE, &CYuePuDialog::OnBnClickedBtnMake)
END_MESSAGE_MAP()

BOOL CYuePuDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if(yuepu)
		((CButton*)GetDlgItem(IDC_RADIO_MUSIC))->SetCheck(TRUE);
	else
		((CButton*)GetDlgItem(IDC_RADIO_DANCE))->SetCheck(TRUE);

	((CButton*)GetDlgItem(IDC_RADIO_REPLACE))->SetCheck(TRUE);

	LOGFONT logfont;
	GetFont()->GetLogFont(&logfont);
	logfont.lfHeight = 24; // 改变字体高度  

	CFont *font = new CFont();
	font->CreateFontIndirect(&logfont);
	GetDlgItem(IDC_EDIT28)->SetFont(font);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// CYuePuDialog 消息处理程序
void CYuePuDialog::OnPaint()
{	
	CPaintDC dc(this);
	SetStretchBltMode(dc.m_hDC, STRETCH_HALFTONE);
	SetBkMode(dc.m_hDC, TRANSPARENT);

	bool b_music = (((CButton*)GetDlgItem(IDC_RADIO_MUSIC))->GetCheck() != FALSE);
	int w = 32, h = 32;
	CRect rc(0,0,w,h);	

                                                    	//替换表 A - Z 显示图案
	for (int i = 0; i < 26; i++)
	{
		char num[2] = { 0 };
		num[0] = 'A' + i;

		int x = 40 + i % 13 * (w + 4);
		int y = 50 + i / 13 * (h + 10);

		dc.TextOut(x, y - 14, str_to_CStr(num));
		rc.MoveToXY(x,y);

		if(b_music)
			musicImage[i].StretchBlt(dc.m_hDC, rc);		
		else
			danceImage[i].StretchBlt(dc.m_hDC, rc);
	}

	if (memDC.m_hDC)
	{
		int dc_w = 8 * 36 + 20, dc_h = 8 * 36 + 20;
		dc.StretchBlt(160, 280, 360, 360, &memDC, 0, 0, dc_w, dc_h, SRCCOPY);
	}
}


void CYuePuDialog::OnBnClickedRadioMusic()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}


void CYuePuDialog::OnBnClickedRadioDance()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}

void CYuePuDialog::OnBnClickedRadioReplace()
{
	// TODO: 在此添加控件通知处理程序代码C
}


void CYuePuDialog::OnBnClickedRadioMove()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CYuePuDialog::OnBnClickedBtnGen()            //生成图片
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_plain.IsEmpty())
	{
		MessageBox(_T("Please enter plain text first"));
		return;
	}

	CString tmp = m_plain;
	string plain = CStr_to_str(tmp.MakeLower());
	for (int i = 0; i < (int)plain.size(); i++)
	{
		if (plain[i] < 'a' || plain[i] > 'z')
		{
			MessageBox(_T("English characters only"));
			return;
		}
	}

	CDC *pDC = GetDC();
	int dc_w = 8 * 36 + 20, dc_h = 8 * 36 + 20;
	memDC.DeleteDC();
	memDC.CreateCompatibleDC(pDC);				   //创建一个兼容的画布
	
	bmp.DeleteObject();
	bmp.CreateCompatibleBitmap(pDC, dc_w, dc_h);   //创建兼容位图
	memDC.SelectObject(&bmp);					   //选中位图对象		

	CBrush brush(RGB(255, 255, 255));
	memDC.FillRect(CRect(0, 0, dc_w, dc_h), &brush);

	bool b_music = (((CButton*)GetDlgItem(IDC_RADIO_MUSIC))->GetCheck() != FALSE);
	bool b_move = (((CButton*)GetDlgItem(IDC_RADIO_MOVE))->GetCheck() != FALSE);
	int w = 32, h = 32;
	CRect rc(0, 0, w, h);

	SetStretchBltMode(memDC.m_hDC, STRETCH_HALFTONE);   //设置绘图模式

	for (int i = 0; i < (int)plain.size(); i++)     	//遍历明文
	{		
		//计算图片坐标
		int x = 10 + i % 8 * (w + 4);
		int y = 10 + i / 8 * (h + 4);

		//计算绘图图片索引
		int idx = plain[i] - 'a';
		if (idx < 0 || idx > 25)
			idx = 0;

		//是否需要移位
		if (b_move)
			idx = (idx + m_shiftNum) % 26;

		//移动绘图框
		rc.MoveToXY(x, y);

		//根据选项绘图
		if (b_music)
			musicImage[idx].StretchBlt(memDC.m_hDC, rc);
		else
			danceImage[idx].StretchBlt(memDC.m_hDC, rc);
	}

	//将生成的图片绘制到界面上
	SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);
	pDC->StretchBlt(140, 280, 420, 360, &memDC, 0, 0, dc_w, dc_h, SRCCOPY);
	ReleaseDC(pDC);
}


void CYuePuDialog::OnBnClickedBtnMake()       //保存图片
{
	// TODO: 在此添加控件通知处理程序代码
	if (!memDC.m_hDC)
	{
		MessageBox(_T("Please create a score first"));
		return;
	}

	CFileDialog dlgFile(FALSE, _T("*.bmp"), _T("image"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("bmp|*.bmp||"));
	if (dlgFile.DoModal() != IDOK)
		return;

	CImage imgTemp;      // CImage是MFC中的类。
	imgTemp.Attach(bmp.operator HBITMAP());
	imgTemp.Save(dlgFile.GetPathName());
}
