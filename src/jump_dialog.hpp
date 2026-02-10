#pragma once
#include "resource.h"
#include <string>

class CJumpDialog : public CDialogImpl<CJumpDialog> {
public:
	enum { IDD = IDD_JUMP_DIALOG };

	BEGIN_MSG_MAP(CJumpDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_ID_HANDLER_EX(IDOK, OnOK)
		COMMAND_ID_HANDLER_EX(IDCANCEL, OnCancel)
	END_MSG_MAP()

	void set_default_time(const std::string& time) { default_time_ = time; }
	std::string get_time_text() const { return time_text_; }

private:
	BOOL OnInitDialog(CWindow, LPARAM);
	void OnOK(UINT, int, CWindow);
	void OnCancel(UINT, int, CWindow);

	std::string default_time_;
	std::string time_text_;
};
