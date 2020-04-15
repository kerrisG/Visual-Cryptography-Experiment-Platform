#pragma once


// CYuePuDialog 对话框

class CYuePuDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CYuePuDialog)

public:
	CYuePuDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CYuePuDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_YUEPU_DLG };
#endif

protected:
	virtual void OnPaint();
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持	

	DECLARE_MESSAGE_MAP()
	
	CImage musicImage[26];
	CImage danceImage[26];
public:
	afx_msg void OnBnClickedRadioMusic();
	afx_msg void OnBnClickedRadioDance();	
	afx_msg void OnBnClickedRadioReplace();
	afx_msg void OnBnClickedRadioMove();
	afx_msg void OnBnClickedBtnGen();
	afx_msg void OnBnClickedBtnMake();
	CString m_plain;

	CDC  memDC;									//定义一个内存画布
	CBitmap bmp;
	bool yuepu;
	int m_shiftNum;
};
