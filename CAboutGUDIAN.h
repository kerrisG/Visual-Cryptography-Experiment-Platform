#pragma once


// AboutGUDIAN �Ի���

class AboutGUDIAN : public CDialog
{
	DECLARE_DYNAMIC(AboutGUDIAN)

public:
	AboutGUDIAN(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AboutGUDIAN();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTgudian };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeRichedit21();
	afx_msg void OnBnClickedOk();
};
