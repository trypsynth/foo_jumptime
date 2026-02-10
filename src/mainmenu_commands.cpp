#include <helpers/foobar2000+atl.h>
#include <atldlgs.h>
#include "jump_dialog.hpp"
#include "time_parser.hpp"

static const GUID guid_jumptime_command = { 0xa7b8c9d0, 0xe1f2, 0x4a5b, { 0x8c, 0x9d, 0x0e, 0x1f, 0x2a, 0x3b, 0x4c, 0x5d } };

class mainmenu_jumptime : public mainmenu_commands {
public:
	t_uint32 get_command_count() override { return 1; }

	GUID get_command(t_uint32 index) override {
		if (index == 0) return guid_jumptime_command;
		uBugCheck();
	}

	void get_name(t_uint32 index, pfc::string_base& out) override {
		if (index == 0) {
			out = "Jump to Time...";
			return;
		}
		uBugCheck();
	}

	bool get_description(t_uint32 index, pfc::string_base& out) override {
		if (index == 0) {
			out = "Jump to a specific time position in the currently playing track.";
			return true;
		}
		return false;
	}

	GUID get_parent() override { return mainmenu_groups::playback; }

	void execute(t_uint32 index, service_ptr_t<service_base> callback) override {
		if (index != 0) uBugCheck();
		HWND wnd = core_api::get_main_window();
		auto playback = playback_control::get();
		if (!playback->is_playing()) {
			MessageBox(wnd, L"No track is currently loaded.", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
		if (!playback->playback_can_seek()) {
			MessageBox(wnd, L"Current track does not support seeking.", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
		double track_length{playback->playback_get_length()};
		double current_pos{playback->playback_get_position()};
		CJumpDialog dlg;
		dlg.set_default_time(format_time(current_pos));
		if (dlg.DoModal(wnd) != IDOK) return;
		std::string input = dlg.get_time_text();
		if (input.empty()) return;
		auto parsed = parse_time(input);
		if (!parsed) {
			MessageBox(wnd, L"Invalid time format. Try hh:mm:ss.", L"Error", MB_OK | MB_ICONERROR);
			return;
		}
		double target_time = *parsed;
		if (target_time > track_length) {
			std::string msg = "Time " + format_time(target_time) + " exceeds track length of " + format_time(track_length) + ".";
			int len = MultiByteToWideChar(CP_UTF8, 0, msg.c_str(), -1, nullptr, 0);
			std::wstring wmsg(len - 1, L'\0');
			MultiByteToWideChar(CP_UTF8, 0, msg.c_str(), -1, &wmsg[0], len);
			MessageBox(wnd, wmsg.c_str(), L"Error", MB_OK | MB_ICONERROR);
			return;
		}
		playback->playback_seek(target_time);
	}
};

static mainmenu_commands_factory_t<mainmenu_jumptime> g_mainmenu_jumptime_factory;
