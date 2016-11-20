
// HiderDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

// CHiderDlg 对话框
class CHiderDlg : public CDialogEx
{
// 构造
public:
	CHiderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HIDER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	CComboBox combo_hide1; 
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
class hotkey{
private:
	long key;
	CString name;
	CString translateKey2Name(long x){
		switch (x)
		{
		case 0x01:
			return L"Alt";
		case 0x02:
			return L"Ctrl";
		case 0x04:
			return L"Shift";
		case 0x08:
			return L"Win";
		case 0x09:
			return L"Tab";
		case 0x1B:
			return L"Esc";
		case 0x20:
			return L"空格";
		case 0x25:
			return L"左";
		case 0x26:
			return L"上";
		case 0x27:
			return L"右";
		case 0x28:
			return L"下";
		case 0x2E:
			return L"Delete";
		case 0x70:
			return L"F1";
		case 0x71:
			return L"F2";
		case 0x72:
			return L"F3";
		case 0x73:
			return L"F4";
		case 0x74:
			return L"F5";
		case 0x75:
			return L"F6";
		case 0x76:
			return L"F7";
		case 0x77:
			return L"F8";
		case 0x78:
			return L"F9";
		case 0x79:
			return L"F10";
		case 0x7A:
			return L"F11";
		case 0x7B:
			return L"F12";
		default:
		{
			wchar_t c =(char)x;
			CString temp(c);
			return temp;
		}
		}
	}

	long translateName2Key(CString x){
		if (x == L"Alt"){
			return 0x01;
		}
		else
			if (x == L"Ctrl")
			{
				return 0x02;
			}
			else
				if (x == L"Shift")
				{
					return 0x04;
				}
				else
					if (x == L"Win")
					{
						return 0x08;
					}
					else
						if (x == L"Tab")
						{
							return 0x09;
						}
						else
							if (x == L"Esc")
							{
								return 0x1B;
							}
							else
								if (x == L"空格")
								{
									return 0x20;
								}
								else
									if (x == L"左")
									{
										return 0x25;
									}
									else
										if (x == L"上")
										{
											return 0x26;
										}
										else
											if (x == L"右")
											{
												return 0x27;
											}
											else
												if (x == L"下")
												{
													return 0x28;
												}
												else
													if (x == L"Delete")
													{
														return 0x2E;
													}
													else
		if (x == L"F1")
		{
			return 0x70;
		}
		else
			if (x == L"F2")
			{
				return 0x71;
			}
			else
				if (x == L"F3")
				{
					return 0x72;
				}
				else
					if (x == L"F4")
					{
						return 0x73;
					}
					else
						if (x == L"F5")
						{
							return 0x74;
						}
						else
							if (x == L"F6")
							{
								return 0x75;
							}
							else
								if (x == L"F7")
								{
									return 0x76;
								}
								else
									if (x == L"F8")
									{
										return 0x77;
									}
									else
										if (x == L"F9")
										{
											return 0x78;
										}
										else
											if (x == L"F10")
											{
												return 0x79;
											}
											else
												if (x == L"F11")
												{
													return 0x7A;
												}
												else
													if (x == L"F12")
													{
														return 0x7B;
													}
													else
		{
			wchar_t *t1 = x.GetBuffer(x.GetLength());
			x.ReleaseBuffer();
			return (int)(char)t1[0];
		}
	}
public:
	void setBykey(long x){
		this->key = x;
		this->name = translateKey2Name(x);
	}
	void setByName(CString x){
		this->name = x;
		this->key = translateName2Key(x);
	}
	CString getName(){
		return name;
	}
	CString getKeyInCsr(){
		CString temp;
		temp.Format(_T("%ld"), key);
		return temp;
	}
	long getKey(){
		return key;
	}
};