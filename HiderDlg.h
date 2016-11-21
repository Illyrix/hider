
// HiderDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <map>

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

class Hotkey{
private:
	long key;
	CString name;
    std::map <long, CString> keyNameMap;
	CString translateKey2Name(long x){
        std::map<long, CString>::iterator it = keyNameMap.find(x);
        if (it != keyNameMap.end()) return it->second;
        else {
			wchar_t c =(char)x;
			return *(new CString(c));
		}
	}

	long translateName2Key(CString x){
        for (auto it = keyNameMap.begin(); it != keyNameMap.end(); it++) {
            if (it->second == x) return it->first;
        }
		wchar_t *t1 = x.GetBuffer(x.GetLength());
		x.ReleaseBuffer();
		return (int)(char)t1[0];
	}
public:
    Hotkey() {
        keyNameMap[0x01] = L"Alt";
        keyNameMap[0x02] = L"Ctrl";
        keyNameMap[0x03] = L"Shift";
        keyNameMap[0x04] = L"Win";
        keyNameMap[0x09] = L"Tab";
        keyNameMap[0x1B] = L"Esc";
        keyNameMap[0x20] = L"Space";
        keyNameMap[0x25] = L"Left";
        keyNameMap[0x26] = L"Up";
        keyNameMap[0x27] = L"Right";
        keyNameMap[0x28] = L"Down";
        keyNameMap[0x2E] = L"Delete";
        keyNameMap[0x70] = L"F1";
        keyNameMap[0x71] = L"F2";
        keyNameMap[0x72] = L"F3";
        keyNameMap[0x73] = L"F4";
        keyNameMap[0x74] = L"F5";
        keyNameMap[0x75] = L"F6";
        keyNameMap[0x76] = L"F7";
        keyNameMap[0x77] = L"F8";
        keyNameMap[0x78] = L"F9";
        keyNameMap[0x79] = L"F10";
        keyNameMap[0x7A] = L"F11";
        keyNameMap[0x7B] = L"F12";
    }

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