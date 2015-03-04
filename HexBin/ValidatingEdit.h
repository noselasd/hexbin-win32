#pragma once


// CValidatingEdit

typedef BOOL (*char_validator)(int c);

class CValidatingEdit : public CEdit
{
	DECLARE_DYNAMIC(CValidatingEdit)
	char_validator validatorFunc;
public:
	CValidatingEdit(char_validator vFunc);
	virtual ~CValidatingEdit();
	afx_msg void OnChar(UINT nChar,UINT nRepCnt,UINT nFlags);

protected:
	DECLARE_MESSAGE_MAP()
};


