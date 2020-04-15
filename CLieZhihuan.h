#pragma once


// CLieZhihuan 对话框

class CLieZhihuan : public CDialog
{
	DECLARE_DYNAMIC(CLieZhihuan)

public:
	CLieZhihuan(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLieZhihuan();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = LieZhihuan };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_strKey;
	CString m_strPlain;
	CString m_strCipher;
	CString m_strPlain2;
	bool checkKey();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedEncrpy2();
	afx_msg void OnBnClickedDecryp2();
	afx_msg void OnBnClickedClear2();	

	int M;
};
