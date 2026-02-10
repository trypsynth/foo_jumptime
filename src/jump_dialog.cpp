#include <helpers/foobar2000+atl.h>
#include <atldlgs.h>
#include "jump_dialog.hpp"

BOOL CJumpDialog::OnInitDialog(CWindow, LPARAM) {
	CenterWindow();
	CEdit edit(GetDlgItem(IDC_TIME_EDIT));
	if (!default_time_.empty()) {
		int len = MultiByteToWideChar(CP_UTF8, 0, default_time_.c_str(), -1, nullptr, 0);
		if (len > 0) {
			std::wstring wtext(len - 1, L'\0');
			MultiByteToWideChar(CP_UTF8, 0, default_time_.c_str(), -1, &wtext[0], len);
			edit.SetWindowText(wtext.c_str());
		}
	}
	edit.SetFocus();
	edit.SetSel(0, -1);
	return FALSE;
}

void CJumpDialog::OnOK(UINT, int, CWindow) {
	CEdit edit(GetDlgItem(IDC_TIME_EDIT));
	int length = edit.GetWindowTextLength();
	if (length > 0) {
		std::wstring wtext(length + 1, L'\0');
		edit.GetWindowText(&wtext[0], length + 1);
		wtext.resize(length);
		int utf8_len = WideCharToMultiByte(CP_UTF8, 0, wtext.c_str(), -1, nullptr, 0, nullptr, nullptr);
		if (utf8_len > 0) {
			time_text_.resize(utf8_len - 1);
			WideCharToMultiByte(CP_UTF8, 0, wtext.c_str(), -1, &time_text_[0], utf8_len, nullptr, nullptr);
		}
	}
	EndDialog(IDOK);
}

void CJumpDialog::OnCancel(UINT, int, CWindow) {
	time_text_.clear();
	EndDialog(IDCANCEL);
}
