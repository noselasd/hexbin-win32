// HexBinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HexBin.h"
#include "HexBinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHexBinDlg dialog

static int bin_validator(int c)
{
	return c == '1' || c == '0' || c == ' ';
}
static int hex_validator(int c)
{
	return strchr("0123456789abcdefABCDEF",c) != NULL;
}
static int dec_validator(int c)
{
	int cint = c - '0';
	return cint >= 0 && cint <= 9;
}
static int oct_validator(int c)
{
	int cint = c - '0';
	return cint >=0 && cint <= 7;
}

static void removespaces(CString &str)
{
	str.Remove(' ');
	str.Remove('\r');
	str.Remove('\n');
	str.Remove('\t');
	str.Remove('\b');

}

CHexBinDlg::CHexBinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHexBinDlg::IDD, pParent),
	update_cnt(0),
	m_BinEdit(bin_validator),
	m_DecEdit(dec_validator),
	m_HexEdit(hex_validator),
	m_OctalEdit(oct_validator)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHexBinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BINARYEDIT, m_BinEdit);
	DDX_Control(pDX, IDC_DECIMALEDIT, m_DecEdit);
	DDX_Control(pDX, IDC_HEXEDIT, m_HexEdit);
	DDX_Control(pDX, IDC_OCTALEDIT, m_OctalEdit);
	DDX_Control(pDX, IDC_EDIT1, m_BinText);
}

BEGIN_MESSAGE_MAP(CHexBinDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_DECIMALEDIT, &CHexBinDlg::OnEnChangeDecimal)
	ON_EN_CHANGE(IDC_HEXEDIT, &CHexBinDlg::OnEnChangeHexedit)
	ON_EN_CHANGE(IDC_OCTALEDIT, &CHexBinDlg::OnEnChangeOctaledit)
	ON_EN_CHANGE(IDC_BINARYEDIT, &CHexBinDlg::OnEnChangeBinedit)
END_MESSAGE_MAP()


// CHexBinDlg message handlers

BOOL CHexBinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	VERIFY(monoFont.CreateFont(
	   13,                        // nHeight
	   0,                         // nWidth
	   0,                         // nEscapement
	   0,                         // nOrientation
	   FW_NORMAL,                 // nWeight
	   FALSE,                     // bItalic
	   FALSE,                     // bUnderline
	   0,                         // cStrikeOut
	   ANSI_CHARSET,              // nCharSet
	   OUT_DEFAULT_PRECIS,        // nOutPrecision
	   CLIP_DEFAULT_PRECIS,       // nClipPrecision
	   DEFAULT_QUALITY,           // nQuality
	   DEFAULT_PITCH | FF_MODERN,  // nPitchAndFamily
	   "CourierNew")); 
	m_BinText.SetFont(&monoFont);
	m_BinText.SetWindowTextA("0 0 0 0 |0x0   1 0 0 0 |0x8\r\n"
							 "0 0 0 1 |0x1   1 0 0 1 |0x9\r\n"
							 "0 0 1 0 |0x2   1 0 1 0 |0xA\r\n"
							 "0 0 1 1 |0x3   1 0 1 1 |0xB\r\n" 
							 "0 1 0 0 |0x4   1 1 0 0 |0xC\r\n"
							 "0 1 0 1 |0x5   1 1 0 1 |0xD\r\n" 
							 "0 1 1 0 |0x6   1 1 1 0 |0xE\r\n"
							 "0 1 1 1 |0x7   1 1 1 1 |0xF"); 							 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHexBinDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHexBinDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHexBinDlg::OnEnChangeDecimal()
{
	CString txt;
	char buf[256];
	unsigned __int64 val;
	if(update_cnt == 0) {
		update_cnt = 3;
		m_DecEdit.GetWindowTextA(txt);
		removespaces(txt);
		val = _strtoui64(txt,NULL,10);

		_snprintf(buf,sizeof buf,"%I64X",val);
		m_HexEdit.SetWindowTextA(buf);
		
		_snprintf(buf,sizeof buf,"%I64o",val);
		m_OctalEdit.SetWindowTextA(buf);

		sprintb(buf,val);
		m_BinEdit.SetWindowTextA(buf);

	} else 
		update_cnt--;

}


void CHexBinDlg::OnEnChangeHexedit()
{
	
	if(update_cnt == 0) {
		CString txt;
		char buf[256];
		unsigned __int64 val;

		update_cnt = 3;
		m_HexEdit.GetWindowTextA(txt);
		removespaces(txt);
		val = _strtoui64(txt,NULL,16);
		m_OctalEdit.UpdateData(0);

		_snprintf(buf,sizeof buf,"%I64o",val);
		m_OctalEdit.SetWindowTextA(buf);

		_snprintf(buf,sizeof buf,"%I64u",val);
		m_DecEdit.SetWindowTextA(buf);

		sprintb(buf,val);
		m_BinEdit.SetWindowTextA(buf);

	}else 
		update_cnt--;

}

void CHexBinDlg::OnEnChangeOctaledit()
{
	if(update_cnt == 0) {
		CString txt;
		char buf[256];
		unsigned __int64 val;

		update_cnt = 3;
		m_OctalEdit.GetWindowTextA(txt);
		removespaces(txt);
		val = _strtoui64(txt,NULL,8);

		_snprintf(buf,sizeof buf,"%I64u",val);
		m_DecEdit.SetWindowTextA(buf);

		_snprintf(buf,sizeof buf,"%I64X",val);
		m_HexEdit.SetWindowTextA(buf);
		
		sprintb(buf,val);
		m_BinEdit.SetWindowTextA(buf);

	}else 
		update_cnt--;


}
void CHexBinDlg::OnEnChangeBinedit()
{
	if(update_cnt == 0) {
		CString txt;
		char buf[256];
		unsigned __int64 val;
		
		update_cnt = 3;
		m_BinEdit.GetWindowTextA(txt);
		removespaces(txt);
		val = _strtoui64(txt,NULL,2);

		_snprintf(buf,sizeof buf,"%I64u",val);
		m_DecEdit.SetWindowTextA(buf);

		_snprintf(buf,sizeof buf,"%I64X",val);
		m_HexEdit.SetWindowTextA(buf);
		
		_snprintf(buf,sizeof buf,"%I64o",val);
		m_OctalEdit.SetWindowTextA(buf);

	}else 
		update_cnt--;


}

static const char *const bits[] = {
		"0000",
		"0001",
		"0010",
		"0011",
		"0100",
		"0101",
		"0110",
		"0111",
		"1000",
		"1001",
		"1010",
		"1011",
		"1100",
		"1101",
		"1110",
		"1111"
};

void sprintb(char *s, unsigned __int64 n) {
	s[0] = 0;
	BOOL firstOne = FALSE;
	unsigned __int64 mask = 0xf000000000000000;
	for(int i = 0 ; i < 16 ; i++) {
		__int64 val =  (n&mask) >> ((15-i)*4);
		mask >>= 4;
		
		if(val)
			firstOne = TRUE;
		if(firstOne) {
			 strcat(s,bits[val]);
		     strcat(s," ");
		}
	}
 }
