
// takePhotoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "takePhoto.h"
#include "takePhotoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtakePhotoDlg dialog




CtakePhotoDlg::CtakePhotoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtakePhotoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
 	m_camera.open(0);
	m_camera.set(CV_CAP_PROP_FRAME_WIDTH,1920);
	m_camera.set(CV_CAP_PROP_FRAME_HEIGHT,1080);
// 	double width = m_camera.get(CV_CAP_PROP_FRAME_WIDTH);
// 	CString tmp;
// 	tmp.Format("%d",width);
// 	OutputDebugString(tmp);
// 	double height = m_camera.get(CV_CAP_PROP_FRAME_HEIGHT);
// 	tmp.Format("%d",height);
// 	OutputDebugString(tmp);
	return;
}

void CtakePhotoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_picName);
	DDX_Control(pDX, IDC_STATIC_VIDEO, m_video);
	DDX_Control(pDX, IDC_STATIC_Photo, m_photo);
}

BEGIN_MESSAGE_MAP(CtakePhotoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CAMERA, &CtakePhotoDlg::OnBnClickedBtnCamera)
	ON_BN_CLICKED(IDOK, &CtakePhotoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CtakePhotoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CtakePhotoDlg::OnBnClickedBtnSave)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CtakePhotoDlg message handlers

BOOL CtakePhotoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_picName.SetWindowText("1.jpg");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CtakePhotoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CtakePhotoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CtakePhotoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtakePhotoDlg::OnBnClickedBtnCamera()
{
	// TODO: Add your control notification handler code here
	SetTimer(50,200,NULL);
}


void CtakePhotoDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (!m_camera.isOpened())
	{
		return;
	}
	
	m_camera.read(m_iFrame);
	//show
	ShowImage(m_iFrame,IDC_STATIC_Photo);
}


void CtakePhotoDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	if (m_camera.isOpened())
	{
		m_camera.release();
	}
	CDialogEx::OnCancel();
}


void CtakePhotoDlg::OnBnClickedBtnSave()
{
	// TODO: Add your control notification handler code here

	CString name="";
	m_picName.GetWindowText(name);
	if (name.IsEmpty())
	{
		return;
	}
	imwrite(name.GetBuffer(),m_iFrame);
}


void CtakePhotoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent==50)
	{
		if (!m_camera.isOpened())
		{
			return;
		}
		Mat iFrame;
		m_camera.read(iFrame);
		ShowImage(iFrame,IDC_STATIC_VIDEO);
		return;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CtakePhotoDlg::ShowImage(Mat& src,UINT ID)
{
	if (src.empty())	return;

	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	int * pResults = NULL;
	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
	if (!pBuffer)
	{
		AfxMessageBox(_T("内存申请失败."));
		return ;
	}

	pResults = facedetect_frontal_surveillance(pBuffer, (unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, (int)gray.step,
		1.2f, 2, 80);
	int numface = (pResults ? *pResults : 0);
	SYSTEMTIME sys;
	if (numface)
	{
		//read time
		GetLocalTime(&sys);
		CString myDirName;
		myDirName.Format("%d_%d_%d",sys.wYear,sys.wMonth,sys.wDay);
		std::string DirName = myDirName.GetBuffer();
		if (DirName != m_Predir)
		{
			m_Predir = DirName;
			_mkdir(DirName.c_str());
		}
		//save face
		CString myname;
		myname.Format("%d_%d_%d_%d",sys.wHour,sys.wMinute,sys.wSecond,sys.wMilliseconds);
		std::string imgName = myname.GetBuffer() ;
		std::string pathName = "./" + DirName + "/" + imgName;

		for (int i = 0; i < numface;i++)
		{
			short * p = ((short*)(pResults + 1)) + 142 * i;
			int x = p[0];
			int y = p[1];
			int w = p[2];
			int h = p[3];

			if (i>4) continue;
			float dis = abs(x - m_one_x[0]) + abs(y - m_one_y[0]);
			float val = dis / w;
			float dis_1 = abs(x - m_one_x[1]) + abs(y - m_one_y[1]);
			float val_1 = dis_1 / w;
			float dis_2 = abs(x - m_one_x[2]) + abs(y - m_one_y[2]);
			float val_2 = dis_2 / w;
			float dis_3 = abs(x - m_one_x[3]) + abs(y - m_one_y[3]);
			float val_3 = dis_3 / w;

			m_one_x[i] = x;
			m_one_y[i] = y;
			int scale = 0.4*w;
			int scale2 = 0.6*w;
			int new_x = x - scale;
			int new_y = y - scale;
			int new_w = w + scale2;
			int new_h = h + scale2;
			new_x = (new_x > 0) ? new_x : 0;
			new_y = (new_y > 0) ? new_y : 0;
			new_w = (new_w+new_x < src.cols) ? new_w : src.cols-new_x;
			new_h = (new_h+new_y < src.rows) ? new_h : src.rows-new_y;
			Rect box(new_x, new_y, new_w, new_h);
			Mat face = src(box);

			CString pname;
			pname.Format("%s%d.jpg",pathName.c_str(),i);
			imwrite(pname.GetBuffer(), face);
			rectangle(src, box, Scalar(0, 255, 0), 2);			
		}
	}

	free(pBuffer);


	CDC* pDC = GetDlgItem(ID)->GetDC();		// 获得显示控件的 DC
	HDC hDC = pDC->GetSafeHdc();				// 获取 HDC(设备句柄) 来进行绘图操作
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);	// 获取控件尺寸位置

	CvvImage cimg;
	IplImage cpy = src;
	cimg.CopyOf(&cpy);						// 复制图片
	cimg.DrawToHDC(hDC, &rect);				// 将图片绘制到显示控件的指定区域内
	ReleaseDC(pDC);
	cimg.Destroy();
}