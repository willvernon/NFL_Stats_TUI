#include <ftxui/component/component.hpp>		  // For Renderer
#include <ftxui/component/screen_interactive.hpp> // For ScreenInteractive
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>
#include <iostream>

int main() {
	using namespace ftxui;

	auto screen = ScreenInteractive::TerminalOutput(); // Interactive Screen

	auto summary = [] {
		auto content = vbox({
			hbox({text(L"- done:   "), text(L"3") | bold}) |
				color(Color::Green),
			hbox({text(L"- active: "), text(L"2") | bold}) |
				color(Color::RedLight),
			hbox({text(L"- queue:  "), text(L"9") | bold}) | color(Color::Red),
		});
		return window(text(L" Summary "), content);
	};

	auto document = //
		vbox({
			hbox({
				summary(),
				summary(),
				summary() | flex,
			}),
			summary(),
			summary(),
		}) |
		size(WIDTH, LESS_THAN, 80);

	auto renderer = Renderer([&] { return document; }); // Wrap in renderer

	screen.Loop(renderer); // Run event loop, exit with ESC or Ctrl+C

	return EXIT_SUCCESS;
}
