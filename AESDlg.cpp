// AESDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "code.h"
#include "AESDlg.h"
#include "afxdialogex.h"
#include "utils.h"

//�ļ���Ϣͷָ��,ָ��ͼ���ļ�
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
	memcpy(lpBmi, &BIH, 40);                  //  ����λͼ��Ϣͷ
	
	return(lpBmi);
}

// CAESDlg �Ի���
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
	logfont.lfHeight = 24; // �ı�����߶�  

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SwitchUI(true);
}

void CAESDlg::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SwitchUI(false);
}



//��һ���ַ�ת��Ϊ��Ӧ��ʮ������
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
//���ַ���ת��Ϊ��̬����
vector<string> CAESDlg::StringToNumList(string context)
{
	vector<string> num_list;  //�����һ���ַ�������

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
//���ַ���ת��Ϊ16���ƣ������ַ��������һ���ո�
bool CAESDlg::String2Hex(const string str, vector<unsigned char> &senddata)
{	
	unsigned int hexdata, lowhexdata;
	int len = str.length();

	vector<string> num_list = StringToNumList(str);
	for (int i = 0; i < (int)num_list.size(); i++)
	{
		if (num_list[i].size() != 2)
		{
			AfxMessageBox(_T("Character format error"), MB_ICONERROR);		//�����ַ�ת��Ϊ16�����ַ�
			return false;
		}

		char hstr = num_list[i][0];
		char lstr = num_list[i][1];
		if ((hexdata = ConvertHexChar(hstr)) == -1)
		{
			AfxMessageBox(_T("Input character exceeds hexadecimal range"), MB_ICONERROR);		//�����ַ�ת��Ϊ16�����ַ�
			return false;
		}
		if ((lowhexdata = ConvertHexChar(lstr)) == -1)	//�ٽ����ַ�ת��Ϊ16�����ַ�
		{
			AfxMessageBox(_T("Input character exceeds hexadecimal range"), MB_ICONERROR);		//�����ַ�ת��Ϊ16�����ַ�
			return false;
		}

		hexdata = hexdata * 16 + lowhexdata;	//����������ַ�����
		senddata.push_back((unsigned char)hexdata);	//���浽Ҫ���͵Ļ�������
	}

	return true;
}

//������ת��ΪCstring�ͱ���
bool CAESDlg::Hex2String(const vector<unsigned char> &recvdata, string &recv)
{
	recv.clear();

	char strtemp[16];
	int len = recvdata.size();
	for (int i = 0; i < len; i++) //������ת��ΪCstring�ͱ���
	{
		sprintf(strtemp, "%02X ", recvdata[i]);	//��ʮ��������ʾ		
		recv += strtemp; //������ձ༭���Ӧ�ַ���

		if ((i + 1) % 10 == 0)
			recv += "\r\n";
	}

	return true;
}

//�����Կ�Ƿ���ȷ
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

//����ļ������Ƿ���ȷ
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

//ѡ�����ģʽ
AESMode_t CAESDlg::getMode()
{
	if (m_box.GetCurSel() == 0)
		return MODE_ECB;
	else
		return MODE_CBC;
}

//�ı�����
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
	QueryPerformanceFrequency(&nFreq);//���ʱ��Ƶ�� 
	QueryPerformanceCounter(&nBeginTime);//��ó�ʼֵ  

	AESModeOfOperation ase;
	ase.set_mode(getMode());
	ase.set_key(key);
	ase.Encrypt((unsigned char*)data.c_str(), data.length(), output);
	
	vector<unsigned char> enc_data;	
	for (int i = 0; i < data_len; i++)
		enc_data.push_back(output[i]);

	string str;
	Hex2String(enc_data, str);  //������ת��ΪCstring�ͱ���
	m_text2 = str_to_CStr(str);
	delete []output;
	UpdateData(FALSE);

	QueryPerformanceCounter(&nEndTime);//�����ֵֹ
	double time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//��ö�Ӧ��ʱ��ֵ��ת�����뵥λ�� 
	m_time1.Format(_T("%f"), time);
	UpdateData(FALSE);
}

//�ı�����
void CAESDlg::OnBnClickedBtnDec()
{
	if (!checkKey())
		return;

	vector<unsigned char> enc_data;
	string str = CStr_to_str(m_text2);
	String2Hex(str, enc_data);    //���ַ���ת��Ϊ16���ƣ������ַ��������һ���ո�
	unsigned char *output = new unsigned char[enc_data.size()];

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);//���ʱ��Ƶ��
	QueryPerformanceCounter(&nBeginTime);//��ó�ʼֵ

	AESModeOfOperation ase;
	ase.set_mode(getMode());
	ase.set_key(key);
	ase.Decrypt(enc_data.data(), enc_data.size(), output);

	m_text3 = str_to_CStr((char*)output);
	delete[]output;
	UpdateData(FALSE);

	QueryPerformanceCounter(&nEndTime);//�����ֵֹ
	double time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//��ö�Ӧ��ʱ��ֵ��ת�����뵥λ�� 
	m_time2.Format(_T("%f"), time);
	UpdateData(FALSE);
}

//ѡ��Դ�ļ�
void CAESDlg::OnBnClickedBtnSel1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlgFile(TRUE, 0, 0, OFN_NOCHANGEDIR | OFN_HIDEREADONLY, _T("�����ļ�|*.*||"));
	if (dlgFile.DoModal() != IDOK)
		return;

	m_file1 = dlgFile.GetPathName();
	UpdateData(FALSE);
}

//ѡ��Ŀ���ļ�
void CAESDlg::OnBnClickedBtnSel2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlgFile(FALSE, 0, 0, OFN_NOCHANGEDIR | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("�����ļ�|*.*||"));
	if (dlgFile.DoModal() != IDOK)
		return;

	m_file2 = dlgFile.GetPathName();
	UpdateData(FALSE);
}

//�ļ�����
void CAESDlg::OnBnClickedBtnEncFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
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

	int n = GetTickCount();   //�Ӳ���ϵͳ�����������ĺ�����
	unsigned char *in_buffer = new unsigned char[4 * 1024 * 1024];
	unsigned char *out_buffer = new unsigned char[4 *1024 * 1024];
	memset(in_buffer, 0, 4 * 1024 * 1024);
	int base_len,buffer_len = 0;
	
	base_len = fread(in_buffer, 1, 4 * 1024 * 1024, fpin);
	buffer_len = (base_len + 15) / 16 * 16; //16�ı���
	
	AESModeOfOperation ase;                 //����
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

//�ļ�����
void CAESDlg::OnBnClickedBtnDecFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	int n = GetTickCount();   //�Ӳ���ϵͳ�����������ĺ�����
	unsigned char *in_buffer = new unsigned char[4 * 1024 * 1024];
	unsigned char *out_buffer = new unsigned char[4 * 1024 * 1024];
	memset(in_buffer, 0, 4 * 1024 * 1024);
	int base_len, buffer_len = 0;

	fread(&base_len, 1, sizeof(int), fpin);
	buffer_len = fread(in_buffer, 1, 4 * 1024 * 1024, fpin);

	AESModeOfOperation ase;                //����
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

//�ͷ�ͼƬ
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

//��ʾͼƬ
void CAESDlg::DrawFrame()
{
	CBrush black_brush(RGB(0, 0, 0));
	CPen red_pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen green_pen(PS_SOLID, 1, RGB(0, 255, 0));
	CBrush *pOldBrush = NULL;

	CRect rect;                          //���������	
	CWnd *pWnd = GetDlgItem(IDC_FRAME); //���pictrue�ؼ����ڵľ��   
	CDC *pDc = pWnd->GetDC();            //���pictrue�ؼ���DC
	CMemDC *pMemDC = new CMemDC(*pDc, pWnd);

	LPBITMAPINFO m_lpBmi = bmpInfo(imageW, imageH);

	pWnd->GetClientRect(&rect);
	pOldBrush = pMemDC->GetDC().SelectObject(&black_brush);
	pMemDC->GetDC().Rectangle(rect.left, rect.top, rect.right, rect.bottom);
	pMemDC->GetDC().SelectObject(pOldBrush);

	if (image)
	{		
		SetStretchBltMode(pMemDC->GetDC().m_hDC, STRETCH_HALFTONE);//����ָ���豸�����е�λͼ����ģʽ����Դ�������е�����ӳ�䵽Ŀ������������ؿ��У�����Ŀ�����ؿ��һ����ɫ��Դ���ص���ɫ�ӽ���
		StretchDIBits(pMemDC->GetDC().m_hDC,
			1, 1, rect.Width() - 2, rect.Height() - 2,
			0, 0, imageW, imageH,
			image, m_lpBmi, DIB_RGB_COLORS, SRCCOPY);      //��DIB�о�������������ʹ�õ���ɫ���ݿ�����ָ����Ŀ�������
	}
	free(m_lpBmi);
	delete pMemDC;
	pWnd->ReleaseDC(pDc);
}

//����ͼƬ
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

//�ָ�ԭͼ
void CAESDlg::OnRecoveImage()
{
	if (image)
	{
		memcpy(image, imageBase, imageW * imageH * 3);
		DrawFrame();
	}
}

//ͼƬ����
void CAESDlg::OnEncImage()
{
	SetCursor(LoadCursor(NULL, IDC_WAIT));

	if (!checkKey())
		return;

	//��ȡͼƬ��С
	int data_len = imageW * imageH * 3;
	unsigned char *output = (unsigned char *)malloc(data_len);	

	//����
	AESModeOfOperation ase;
	ase.set_mode(getMode());
	ase.set_key(key);
	ase.Encrypt(image, data_len, output);
	freeImage(false);

	//��ͼ
	image = output;	
	DrawFrame();

	SetCursor(NULL);
}

//ͼƬ����
void CAESDlg::OnDecImage()
{
	SetCursor(LoadCursor(NULL, IDC_WAIT));

	if (!checkKey())
		return;
	
	//��ȡͼƬ��С
	int data_len = imageW * imageH * 3;
	unsigned char *output = (unsigned char *)malloc(data_len);

	//����
	AESModeOfOperation ase;
	ase.set_mode(getMode());
	ase.set_key(key);
	ase.Decrypt(image, data_len, output);
	freeImage(false);

	//��ͼ
	image = output;	
	DrawFrame();

	SetCursor(NULL);
}

//����ͼƬ
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
