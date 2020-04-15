#pragma once
#include "afxwin.h"

#include <string>
#include <vector>

#include "bmp.h"
using namespace std;

// CAESDlg 对话框
#include "AES.h"
class CAESDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAESDlg)

public:
	CAESDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAESDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AES_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:	;
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnEnc();
	afx_msg void OnBnClickedBtnDec();
	afx_msg void OnBnClickedBtnEncFile();		

	afx_msg void OnLoadImage();
	afx_msg void OnRecoveImage();
	afx_msg void OnEncImage();
	afx_msg void OnDecImage();
	afx_msg void OnSaveImage();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();

	void SwitchUI(bool text);
	char ConvertHexChar(char ch);
	vector<string> StringToNumList(const string str);
	bool String2Hex(const string str, vector<unsigned char> &senddata);
	bool Hex2String(const vector<unsigned char> &recvdata, string &str);
	
	bool checkKey();
	bool checkFile();
	void freeImage(bool freeBase);
	AESMode_t getMode();
	void DrawFrame();

	AESMode_t mode;
	CString m_key;
	CString m_text1;
	CString m_text2;
	CString m_text3;
	CString m_file1;
	CString m_file2;
	CComboBox m_box;	

	unsigned char key[20];
	unsigned char *imageBase;
	unsigned char *image;
	int imageW, imageH;
	afx_msg void OnBnClickedBtnSel1();
	afx_msg void OnBnClickedBtnSel2();
	afx_msg void OnBnClickedBtnDecFile();
	CString m_time1;
	CString m_time2;
};
