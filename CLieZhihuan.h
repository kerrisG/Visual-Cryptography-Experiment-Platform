#pragma once


// CLieZhihuan �Ի���

class CLieZhihuan : public CDialog
{
	DECLARE_DYNAMIC(CLieZhihuan)

public:
	CLieZhihuan(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLieZhihuan();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = LieZhihuan };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
