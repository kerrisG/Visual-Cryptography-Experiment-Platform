#pragma once


// CMainDialog �Ի���

class CMainDialog : public CDialog
{
	DECLARE_DYNAMIC(CMainDialog)

public:
	CMainDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();

	afx_msg void Liezh();
	afx_msg void Zhouqi();
	afx_msg void Yiwei();
	afx_msg void Vige();
	afx_msg void OnAesECB();
	afx_msg void OnAesCBC();
	afx_msg void OnRSA();
	/*afx_msg void OnYuePU();*/
	afx_msg void OnMusic();
	afx_msg void OnDance();
	afx_msg void AboutGD();
	afx_msg void Aboutaes();
	afx_msg void Aboutrsa();
	afx_msg void Abouthelp();
};
