
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnOK()
{
	//	CDialogEx::OnOK();


}

#include <vector>

void CMFCApplication1Dlg::OnBnClickedOk()
{

	std::vector<int> characterV;
	char characterArr[] = { 0x20, 0x0A,0x0D,0x0C,0x1A,0x0B,0x09 };
	CString charactPath;
	//特征文件
	GetDlgItem(IDC_CHARACTER)->GetWindowText(charactPath);


	int nTokenPos = 0;
	CString strToken = charactPath.Tokenize(_T(" "), nTokenPos);

	while (!strToken.IsEmpty())
	{
		// do something with strToken
		// ....
		TCHAR* pChar =(TCHAR *) (LPCTSTR)strToken;
		int iLength = WideCharToMultiByte(CP_ACP, 0, pChar, -1, NULL, 0, NULL, NULL);
		char _char[200] = { 0 };
		WideCharToMultiByte(CP_ACP, 0, pChar, -1, _char, iLength, NULL, NULL);
		unsigned int d = strtol(_char, NULL, 16);
	
		characterV.push_back(d);
		strToken = charactPath.Tokenize(_T(" "), nTokenPos);
	}

	CString fileTargetPath;


	//计算结果
	GetDlgItem(ID_FILE_TARGET)->GetWindowText(fileTargetPath);
	char cTarget[500] = {};

	char* p = (LPSTR)(LPCTSTR)fileTargetPath;
	FILE* targetFile = nullptr;

	CStringA cstraParam(fileTargetPath);
	const size_t newsizea = (cstraParam.GetLength() + 1);
	char* nstringa = new char[newsizea];
	strcpy_s(nstringa, newsizea, cstraParam);


	HANDLE targetHandle = CreateFileA(nstringa, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	delete []nstringa;
	char * pBuf;
	DWORD size = 0;

	HANDLE	hMapFile = CreateFileMappingA(
		targetHandle,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,
		0,                       // max. object size
		0,                    // buffer size
		"sds");                 // name of mapping object

	pBuf =(char*)MapViewOfFile(hMapFile,          // handle to map object
		FILE_MAP_READ, // read/write permission
		0,
		0,
		0);

	DWORD fileLength = GetFileSize(targetHandle, NULL);;

	

	int ret = 0;
	
	bool numCorrect = true;

	for (size_t i = 0; i < 2000; i++)
	{
		ret = i;
		
		numCorrect = true;
		for (size_t dataIndex = 0; dataIndex < fileLength; dataIndex++) {
			char xorRet = *(pBuf + dataIndex) ^ (ret);

			bool correct = true;

			std::vector<int>::iterator v = characterV.begin();
			while (v != characterV.end()) {
				if (xorRet == *v)
				{
				
					correct = false;
					break;
				}
				v++;
			}
			/*for (size_t characterIndex = 0; characterIndex < sizeof characterArr; characterIndex++)
			{
				

			}*/
			//不正确
			if (!correct) {
				numCorrect = false;
				break;
			}
		}

		if (numCorrect)
		{
			break;
		}


	}

	if (numCorrect)
	{
		CString result;
		result.Format(_T("%x"),ret);
	/*	const size_t tipL = (result.GetLength() + 1);
		char* tip = new char[tipL];*/
		//strcpy_s(tip, tipL, result);
		GetDlgItem(IDC_RESULT)->SetWindowText((LPCTSTR)result);
	}
	else {
		GetDlgItem(IDC_RESULT)->SetWindowText((LPCTSTR)CString("未计算出结果"));
	}

	UnmapViewOfFile(pBuf);

	CloseHandle(hMapFile);

	CloseHandle(targetHandle);
	//20 0A 0d 0c 1a 0b 09
}
