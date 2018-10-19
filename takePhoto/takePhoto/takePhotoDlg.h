
// takePhotoDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CtakePhotoDlg dialog
class CtakePhotoDlg : public CDialogEx
{
// Construction
public:
	CtakePhotoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TAKEPHOTO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCamera();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnSave();
	CEdit m_picName;
	CStatic m_video;
	CStatic m_photo;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ShowImage(Mat& src,UINT ID);
private:
	VideoCapture m_camera;
	Mat m_iFrame;
	string m_Predir;
	int m_one_x[4] ;
	int m_one_y[4] ;
};
