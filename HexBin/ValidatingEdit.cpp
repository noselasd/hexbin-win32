// ValidatingEdit.cpp : implementation file
//

#include "stdafx.h"
#include "HexBin.h"
#include "ValidatingEdit.h"


// CValidatingEdit


IMPLEMENT_DYNAMIC(CValidatingEdit, CEdit)

CValidatingEdit::CValidatingEdit(char_validator vFunc)
: validatorFunc(vFunc) 
{

}

CValidatingEdit::~CValidatingEdit()
{
}

void CValidatingEdit::OnChar(UINT nChar,UINT nRepCnt,UINT nFlags)
{
	if(validatorFunc(nChar) || nChar == 8 || nChar == '\n' || nChar == 3 || nChar == 22 || nChar == 24 || nChar == 26) // 8 is backspace, 3 is ctrl+c, 22 is ctrl+p, 24 is ctrl+x, 26 is ctrl+z
		CEdit::OnChar(nChar,nRepCnt,nFlags);
	else
		MessageBeep(-1);
}

BEGIN_MESSAGE_MAP(CValidatingEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CValidatingEdit message handlers


