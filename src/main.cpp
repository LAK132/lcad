#include "main.hpp"

#define LAK_BASIC_PROGRAM_MAIN   main
#define LAK_BASIC_PROGRAM_PREFIX basic_
#include "lak/basic_program.inl"

#include "lak/file.hpp"
#include "lak/test.hpp"

#include "lak/imgui/imgui.hpp"

ImGui::ImplContext imgui_context = nullptr;

lak::optional<int> basic_window_preinit(int argc, char **argv)
{
	if (argc == 2 && argv[1] == "--version"_str)
	{
		std::cout << APP_NAME << "\n";
		return lak::some_t{0};
	}

	lak::debugger.std_out(u8"", u8"" APP_NAME "\n");

	for (int arg = 1; arg < argc; ++arg)
	{
		if (argv[arg] == "--help"_str)
		{
			std::cout << APP_NAME
			  "\n"
			  "[--help] print this message\n"
			  "[--software-render] disable hardware acceleration\n"
			  "[--only-err] do not print debug or warning messages, only errors\n"
			  "[--list-tests] list all of the registered tests\n"
			  "[--test-all] run all of the registered tests\n"
			  "[--test \"test1;test2\"] run the specified tests\n";
			return lak::some_t{0};
		}
		else if (argv[arg] == "--software-render"_str)
		{
			basic_window_force_software = true;
		}
		else if (argv[arg] == "--only-err"_str)
		{
			lak::debugger.live_errors_only = true;
		}
		else if (argv[arg] == "--list-tests"_str)
		{
			lak::debugger.std_out(lak::u8string(),
			                      lak::u8string(u8"Available tests:\n"));
			for (const auto &[name, func] : lak::registered_tests())
			{
				lak::debugger.std_out(lak::u8string(),
				                      lak::to_u8string(name) + u8"\n");
			}
		}
		else if (argv[arg] == "--test-all"_str)
		{
			return lak::some_t{lak::run_tests()};
		}
		else if (argv[arg] == "--test"_str)
		{
			++arg;
			if (arg >= argc) FATAL("Missing tests");
			return lak::some_t{lak::run_tests(
			  lak::as_u8string(lak::astring_view::from_c_str(argv[arg])))};
		}
	}

	basic_window_target_framerate  = 60;
	basic_window_start_size        = {1200, 720};
	basic_window_clear_colour      = {0.0f, 0.3125f, 0.312f, 1.0f};
	basic_window_opengl_settings   = lak::opengl_settings{};
	basic_window_software_settings = lak::software_settings{};

	return lak::nullopt;
}

void basic_window_init(lak::window &window)
{
	lak::debugger.crash_path = lak::fs::current_path() / "crash-log.txt";
	lak::debugger.live_output_enabled = true;

	imgui_context = ImGui::ImplCreateContext(window.graphics());
	ImGui::ImplInit();
	ImGui::ImplInitContext(imgui_context, window);

	ImGuiStyle &style      = ImGui::GetStyle();
	style.AntiAliasedLines = false;
	style.AntiAliasedFill  = false;
	style.WindowRounding   = 0.0f;

	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui::GetStyle().WindowRounding = 0;
}

void basic_window_handle_event(lak::window &, lak::event &event)
{
	ImGui::ImplProcessEvent(imgui_context, event);

	switch (event.type)
	{
		//
	}
}

void basic_window_loop(lak::window &window, uint64_t counter_delta)
{
	const float frame_time = (float)counter_delta / lak::performance_frequency();
	ImGui::ImplNewFrame(imgui_context, window, frame_time);

	bool mainOpen = true;

	ImGuiStyle &style = ImGui::GetStyle();
	ImGuiIO &io       = ImGui::GetIO();

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(io.DisplaySize);
	ImVec2 old_window_padding = style.WindowPadding;
	style.WindowPadding       = ImVec2(0.0f, 0.0f);
	if (ImGui::Begin("ImGui Test Window",
	                 &mainOpen,
	                 ImGuiWindowFlags_AlwaysAutoResize |
	                   ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_MenuBar |
	                   ImGuiWindowFlags_NoSavedSettings |
	                   ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove))
	{
		style.WindowPadding = old_window_padding;

		//

		ImGui::End();
	}

	ImGui::ImplRender(imgui_context);
}

int basic_window_quit(lak::window &)
{
	ImGui::ImplShutdownContext(imgui_context);

	return EXIT_SUCCESS;
}
