// AESDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "code.h"
#include "AESDlg.h"
#include "afxdialogex.h"
#include "utils.h"

//文件信息头指针,指向图像文件
LPBITMAPINFO bmpInfo(int w, int h)
{
	BITMAPINFOHEADER BIH = { 40,1,1,1,8,0,0,0,0,0,0 };
	LPBITMAPINFO lpBmi;
	int wid = w, hei = h, bits = 24, colors;	

	if (bits>8) colors = 0;
	else colors = 1 << bits;

	lpBmi = (LPBITMAPINFO)malloc(40 + 4 * colors);
	BIH.biWidth = wid;
	BIH.biHeight = hei;
	BIH.biBitCount = (BYTE)bits;
	memcpy(lpBmi, &BIH, 40);                  //  复制位图信息头
	
	return(lpBmi);
}

// CAESDlg 对话框
IMPLEMENT_DYNAMIC(CAESDlg, CDialogEx)

CAESDlg::CAESDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AES_DLG, pParent)
	, m_key(_T(""))
	, m_time1(_T(""))
	, m_time2(_T(""))
{
	mode = MODE_ECB;

	image = NULL;
	imageW = imageH = 0;;
}

CAESDlg::~CAESDlg()
{
}

void CAESDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, m_key);
	DDX_Text(pDX, IDC_EDIT1, m_text1);
	DDX_Text(pDX, IDC_EDIT2, m_text2);
	DDX_Text(pDX, IDC_EDIT3, m_text3);
	DDX_Text(pDX, IDC_EDIT_SEL1, m_file1);
	DDX_Text(pDX, IDC_EDIT_SEL2, m_file2);

	DDX_Control(pDX, IDC_COMBO1, m_box);
	DDX_Text(pDX, IDC_TIME1, m_time1);
	DDX_Text(pDX, IDC_TIME2, m_time2);
}


BEGIN_MESSAGE_MAP(CAESDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ENC, &CAESDlg::OnBnClickedBtnEnc)
	ON_BN_CLICKED(IDC_BTN_DEC, &CAESDlg::OnBnClickedBtnDec)
	ON_BN_CLICKED(IDC_BTN_ENC_FILE, &CAESDlg::OnBnClickedBtnEncFile)	

	ON_BN_CLICKED(IDC_BUTTON1, &CAESDlg::OnLoadImage)
	ON_BN_CLICKED(IDC_BUTTON5, &CAESDlg::OnRecoveImage)
	ON_BN_CLICKED(IDC_BUTTON2, &CAESDlg::OnEncImage)
	ON_BN_CLICKED(IDC_BUTTON3, &CAESDlg::OnDecImage)
	ON_BN_CLICKED(IDC_BUTTON4, &CAESDlg::OnSaveImage)
	ON_BN_CLICKED(IDC_RADIO1, &CAESDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CAESDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BTN_SEL1, &CAESDlg::OnBnClickedBtnSel1)
	ON_BN_CLICKED(IDC_BTN_SEL2, &CAESDlg::OnBnClickedBtnSel2)
	ON_BN_CLICKED(IDC_BTN_DEC_FILE, &CAESDlg::OnBnClickedBtnDecFile)
END_MESSAGE_MAP()

BOOL CAESDlg::OnInitDialog()
{
	m_time1 = "0";
	m_time2 = "0";
	UpdateData(FALSE);

	CDialogEx::OnInitDialog();
	if(mode == MODE_ECB)
		m_box.SetCurSel(0);
	else
		m_box.SetCurSel(1);

	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	SwitchUI(true);

	LOGFONT logfont;
	GetFont()->GetLogFont(&logfont);
	logfont.lfHeight = 24; // 改变字体高度  

	CFont *font = new CFont();
	font->CreateFontIndirect(&logfont);
	GetDlgItem(IDC_EDIT1)->SetFont(font);
	GetDlgItem(IDC_EDIT2)->SetFont(font);
	GetDlgItem(IDC_EDIT3)->SetFont(font);

	return TRUE;
}

void CAESDlg::SwitchUI(bool text)
{
	GetDlgItem(IDC_EDIT1)->ShowWindow(text);
	GetDlgItem(IDC_EDIT2)->ShowWindow(text);
	GetDlgItem(IDC_EDIT3)->ShowWindow(text);
	GetDlgItem(IDC_EDIT_SEL1)->ShowWindow(text);
	GetDlgItem(IDC_EDIT_SEL2)->ShowWindow(text);
	GetDlgItem(IDC_LABEL1)->ShowWindow(text);
	GetDlgItem(IDC_LABEL2)->ShowWindow(text);
	GetDlgItem(IDC_LABEL3)->ShowWindow(text);	
	GetDlgItem(IDC_LABEL4)->ShowWindow(text);
	GetDlgItem(IDC_LABEL5)->ShowWindow(text);
	GetDlgItem(IDC_LABEL6)->ShowWindow(text);
	GetDlgItem(IDC_BTN_ENC)->ShowWindow(text);
	GetDlgItem(IDC_BTN_DEC)->ShowWindow(text);
	GetDlgItem(IDC_BTN_ENC_FILE)->ShowWindow(text);
	GetDlgItem(IDC_BTN_DEC_FILE)->ShowWindow(text);
	GetDlgItem(IDC_BTN_SEL1)->ShowWindow(text);
	GetDlgItem(IDC_BTN_SEL2)->ShowWindow(text);

	GetDlgItem(IDC_LABEL7)->ShowWindow(text);
	GetDlgItem(IDC_LABEL8)->ShowWindow(text);
	GetDlgItem(IDC_LABEL9)->ShowWindow(text);
	GetDlgItem(IDC_LABEL10)->ShowWindow(text);
	GetDlgItem(IDC_TIME1)->ShowWindow(text);
	GetDlgItem(IDC_TIME2)->ShowWindow(text);

	GetDlgItem(IDC_FRAME)->ShowWindow(!text);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(!text);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(!text);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(!text);
	GetDlgItem(IDC_BUTTON4)->ShowWindow(!text);
	GetDlgItem(IDC_BUTTON5)->ShowWindow(!text);
}

void CAESDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	SwitchUI(true);
}

void CAESDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	SwitchUI(false);
}



//将一个字符转换为相应的十六进制
char CAESDlg::ConvertHexChar(char ch)
{	
	if ((ch >= '0') && (ch <= '9'))
		return ch - 0x30;
	else if ((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	else if ((ch >= 'a') && (ch <= 'f'))
		return ch - 'a' + 10;
	else
		return (-1);
}
//将字符串转换为动态数组
vector<string> CAESDlg::StringToNumList(string context)
{
	vector<string> num_list;  //定义个一个字符串容器

	vector<string> line_list;
	string_split(context, "\r\n", line_list);
	for (int i = 0; i < (int)line_list.size(); i++)
	{
		vector<string> tmp_list;
		string_split(line_list[i], " ", tmp_list);

		num_list.insert(num_list.end(), tmp_list.begin(), tmp_list.end());
	}

	return num_list;
}
//将字符串转换为16进制，俩个字符间插入了一个空格
bool CAESDlg::String2Hex(const string str, vector<unsigned char> &senddata)
{	
	unsigned int hexdata, lowhexdata;
	int len = str.length();

	vector<string> num_list = StringToNumList(str);
	for (int i = 0; i < (int)num_list.size(); i++)
	{
		if (num_list[i].size() != 2)
		{
			AfxMessageBox(_T("Character format error"), MB_ICONERROR);		//将高字符转换为16进制字符
			return false;
		}

		char hstr = num_list[i][0];
		char lstr = num_list[i][1];
		if ((hexdata = ConvertHexChar(hstr)) == -1)
		{
			AfxMessageBox(_T("Input character exceeds hexadecimal range"), MB_ICONERROR);		//将高字符转换为16进制字符
			return false;
		}
		if ((lowhexdata = ConvertHexChar(lstr)) == -1)	//再将低字符转换为16进制字符
		{
			AfxMessageBox(_T("Input character exceeds hexadecimal range"), MB_ICONERROR);		//将高字符转换为16进制字符
			return false;
		}

		hexdata = hexdata * 16 + lowhexdata;	//否则把俩个字符叠加
		senddata.push_back((unsigned char)hexdata);	//保存到要发送的缓冲区中
	}

	return true;
}

//将数组转换为Cstring型变量
bool CAESDlg::Hex2String(const vector<unsigned char> &recvdata, string &recv)
{
	recv.clear();

	char strtemp[16];
	int len = recvdata.size();
	for (int i = 0; i < len; i++) //将数组转换为Cstring型变量
	{
		sprintf(strtemp, "%02X ", recvdata[i]);	//以十六进制显示		
		recv += strtemp; //加入接收编辑框对应字符串

		if ((i + 1) % 10 == 0)
			recv += "\r\n";
	}

	return true;
}

//检查密钥是否正确
bool CAESDlg::checkKey()
{
	UpdateData();
	if (m_key.IsEmpty())
	{
		MessageBox(_T("The key cannot be empty"));
		return false;
	}

	string keystr = CStr_to_str(m_key);
	memset(key, 0, 20);
	memcpy(key, keystr.c_str(), keystr.length());
	return true;
}

//检查文件导入是否正确
bool CAESDlg::checkFile()
{
	UpdateData();
	if (m_file1.IsEmpty() || m_file2.IsEmpty())
	{
		MessageBox(_T("The key cannot be empty"));
		return false;
	}

	return true;
}

//选择加密模式
AESMode_t CAESDlg::getMode()
{
	if (m_box.GetCurSel() == 0)
		return MODE_ECB;
	else
		return MODE_CBC;
}

//文本加密
void CAESDlg::OnBnClickedBtnEnc()
{
	if (!checkKey())
		return;

	string data = CStr_to_str(m_text1);
	int data_len = (data.length() + 15) / 16 * 16;
	unsigned char *output = new unsigned char[data_len + 1];
	memset(output, 0, data_len + 1);
	data.resize(data_len);

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);//获得时钟频率 
	QueryPerformanceCounter(&nBeginTime);//获得初始值  

	AESModeOfOperation ase;
	ase.set_mode(getMode());
	ase.set_key(key);
	ase.Encrypt((unsigned char*)data.c_str(), data.length(), output);
	
	vector<unsigned char> enc_data;	
	for (int i = 0; i < data_len; i++)
		enc_data.push_back(output[i]);

	string str;
	Hex2String(enc_data, str);  //将数组转换为Cstring型变量
	m_text2 = str_to_CStr(str);
	delete []output;
	UpdateData(FALSE);

	QueryPerformanceCounter(&nEndTime);//获得终止值
	double time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//获得对应的时间值，转到毫秒单位上 
	m_time1.Format(_T("%f"), time);
	UpdateData(FALSE);
}

//文本解密
void CAESDlg::OnBnClickedBtnDec()
{
	if (!checkKey())
		return;

	vector<unsigned char> enc_data;
	string str = CStr_to_str(m_text2);
	String2Hex(str, enc_data);    //将字符串转换为16进制，俩个字符间插入了一个空格
	unsigned char *output = new unsigned char[enc_data.size()];

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);//获得时钟频率
	QueryPerformanceCounter(&nBeginTime);//获得初始值

	AESModeOfOperation ase;
	ase.set_mode(getMode());
	ase.set_key(key);
	ase.Decrypt(enc_data.data(), enc_data.size(), output);

	m_text3 = str_to_CStr((char*)output);
	delete[]output;
	UpdateData(FALSE);

	QueryPerformanceCounter(&nEndTime);//获得终止值
	double time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//获得对应的时间值，转到毫秒单位上 
	m_time2.Format(_T("%f"), time);
	UpdateData(FALSE);
}

//选择源文件
void CAESDlg::OnBnClickedBtnSel1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlgFile(TRUE, 0, 0, OFN_NOCHANGEDIR | OFN_HIDEREADONLY, _T("所有文件|*.*||"));
	if (dlgFile.DoModal() != IDOK)
		return;

	m_file1 = dlgFile.GetPathName();
	UpdateData(FALSE);
}

//选择目标文件
void CAESDlg::OnBnClickedBtnSel2()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlgFile(FALSE, 0, 0, OFN_NOCHANGEDIR | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("所有文件|*.*||"));
	if (dlgFile.DoModal() != IDOK)
		return;

	m_file2 = dlgFile.GetPathName();
	UpdateData(FALSE);
}

//文件加密
void CAESDlg::OnBnClickedBtnEncFile()
{
	// TODO: 在此添加控件通知处理程序代码	
	if (!checkFile() || !checkKey())
		return;

	FILE *fpin = fopen(CStr_to_str(m_file1).c_str(), "rb");
	if (!fpin)
	{
		MessageBox(_T("Fail to open the file"));
		return;
	}
	FILE *fpout = fopen(CStr_to_str(m_file2).c_str(), "wb");
	if (!fpout)
	{
		fclose(fpin);
		MessageBox(_T("Fail to open the file"));
		return;
	}

	int n = GetTickCount();   //从操作系统启动所经过的毫秒数
	unsigned char *in_buffer = new unsigned char[4 * 1024 * 1024];
	unsigned char *out_buffer = new unsigned char[4 *1024 * 1024];
	memset(in_buffer, 0, 4 * 1024 * 1024);
	int base_len,buffer_len = 0;
	
	base_len = fread(in_buffer, 1, 4 * 1024 * 1024, fpin);
	buffer_len = (base_len + 15) / 16 * 16; //16的倍数
	
	AESModeOfOperation ase;                 //加密
	ase.set_mode(getMode());
	ase.set_key(key);
	ase.Encrypt(in_buffer, buffer_len, out_buffer);

	fwrite(&base_len,  1, sizeof(int), fpout);
	fwrite(out_buffer, 1, buffer_len, fpout);
	fclose(fpin);
	fclose(fpout);

	delete[]in_buffer;
	delete[]out_buffer;

	int use = GetTickCount() - n;
	CString text;
	text.Format(_T("File size:%d byte\r\nTime-consuming:%dms"), base_len, use);
	MessageBox(text);
}

//文件解密
void CAESDlg::OnBnClickedBtnDecFile()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!checkFile() || !checkKey())
		return;

	FILE *fpin = fopen(CStr_to_str(m_file1).c_str(), "rb");
	if (!fpin)
	{
		MessageBox(_T("Fail to open the file"));
		return;
	}
	FILE *fpout = fopen(CStr_to_str(m_file2).c_str(), "wb");
	if (!fpout)
	{
		fclose(fpin);
		MessageBox(_T("Fail to open the file"));
		return;
	}

	int n = GetTickCount();   //从操作系统启动所经过的毫秒数
	unsigned char *in_buffer = new unsigned char[4 * 1024 * 1024];
	unsigned char *out_buffer = new unsigned char[4 * 1024 * 1024];
	memset(in_buffer, 0, 4 * 1024 * 1024);
	int base_len, buffer_len = 0;

	fread(&base_len, 1, sizeof(int), fpin);
	buffer_len = fread(in_buffer, 1, 4 * 1024 * 1024, fpin);

	AESModeOfOperation ase;                //解密
	ase.set_mode(getMode());
	ase.set_key(key);
	ase.Decrypt(in_buffer, buffer_len, out_buffer);
	
	fwrite(out_buffer, 1, base_len, fpout);
	fclose(fpin);
	fclose(fpout);

	delete[]in_buffer;
	delete[]out_buffer;

	int use = GetTickCount() - n;
	CString text;
	text.Format(_T("File size:%d byte\r\nTime-consuming:%dms"), base_len, use);
	MessageBox(text);
}

//释放图片
void CAESDlg::freeImage(bool freeBase)
{
	if (image)
	{
		free(image);
		image = NULL;

		if (freeBase)
		{
			free(imageBase);
			imageBase = NULL;
		}
	}
}

//显示图片
void CAESDlg::DrawFrame()
{
	CBrush black_brush(RGB(0, 0, 0));
	CPen red_pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen green_pen(PS_SOLID, 1, RGB(0, 255, 0));
	CBrush *pOldBrush = NULL;

	CRect rect;                          //定义矩形类	
	CWnd *pWnd = GetDlgItem(IDC_FRAME); //获得pictrue控件窗口的句柄   
	CDC *pDc = pWnd->GetDC();            //获得pictrue控件的DC
	CMemDC *pMemDC = new CMemDC(*pDc, pWnd);

	LPBITMAPINFO m_lpBmi = bmpInfo(imageW, imageH);

	pWnd->GetClientRect(&rect);
	pOldBrush = pMemDC->GetDC().SelectObject(&black_brush);
	pMemDC->GetDC().Rectangle(rect.left, rect.top, rect.right, rect.bottom);
	pMemDC->GetDC().SelectObject(pOldBrush);

	if (image)
	{		
		SetStretchBltMode(pMemDC->GetDC().m_hDC, STRETCH_HALFTONE);//设置指定设备环境中的位图拉伸模式，将源矩形区中的像素映射到目标矩形区的像素块中，覆盖目标像素块的一般颜色与源像素的颜色接近。
		StretchDIBits(pMemDC->GetDC().m_hDC,
			1, 1, rect.Width() - 2, rect.Height() - 2,
			0, 0, imageW, imageH,
			image, m_lpBmi, DIB_RGB_COLORS, SRCCOPY);      //将DIB中矩形区域内像素使用的颜色数据拷贝到指定的目标矩形中
	}
	free(m_lpBmi);
	delete pMemDC;
	pWnd->ReleaseDC(pDc);
}

//加载图片
void CAESDlg::OnLoadImage()     
{
	CFileDialog dlgFile(TRUE, 0, 0, OFN_NOCHANGEDIR | OFN_HIDEREADONLY, _T("bmp|*.bmp||"));
	if (dlgFile.DoModal() != IDOK)
		return;
	
	freeImage(true);
	int depth;
	image = load_bmp(CStr_to_str(dlgFile.GetPathName()).c_str(), &imageW, &imageH, &depth);
	if ((imageW*imageH) % 8 != 0 || depth != 24)
	{		
		freeImage(false);
		MessageBox(_T("The image is not a 24-bit image or the size is not an integer multiple of 64bit"));		
		return;
	}
	imageBase = (unsigned char*)malloc(imageW * imageH * 3);
	memcpy(imageBase,image, imageW * imageH * 3);

	DrawFrame();
}

//恢复原图
void CAESDlg::OnRecoveImage()
{
	if (image)
	{
		memcpy(image, imageBase, imageW * imageH * 3);
		DrawFrame();
	}
}

//图片加密
void CAESDlg::OnEncImage()
{
	SetCursor(LoadCursor(NULL, IDC_WAIT));

	if (!checkKey())
		return;

	//获取图片大小
	int data_len = imageW * imageH * 3;
	unsigned char *output = (unsigned char *)malloc(data_len);	

	//加密
	AESModeOfOperation ase;
	ase.set_mode(getMode());
	ase.set_key(key);
	ase.Encrypt(image, data_len, output);
	freeImage(false);

	//画图
	image = output;	
	DrawFrame();

	SetCursor(NULL);
}

//图片解密
void CAESDlg::OnDecImage()
{
	SetCursor(LoadCursor(NULL, IDC_WAIT));

	if (!checkKey())
		return;
	
	//获取图片大小
	int data_len = imageW * imageH * 3;
	unsigned char *output = (unsigned char *)malloc(data_len);

	//解密
	AESModeOfOperation ase;
	ase.set_mode(getMode());
	ase.set_key(key);
	ase.Decrypt(image, data_len, output);
	freeImage(false);

	//画图
	image = output;	
	DrawFrame();

	SetCursor(NULL);
}

//保存图片
void CAESDlg::OnSaveImage()
{
	if (!image)
	{
		MessageBox(_T("No image loaded"));
		return;
	}

	CFileDialog dlgFile(FALSE, _T("*.bmp"), 0, OFN_NOCHANGEDIR | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("bmp|*.bmp||"));
	if (dlgFile.DoModal() != IDOK)
		return;	

	save_bmp(CStr_to_str(dlgFile.GetPathName()).c_str(), image,imageW, imageH,24);
}
