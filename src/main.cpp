#include <memory> // for allocator, __shared_ptr_access
#include <string> // for char_traits, operator+, string, basic_string

#include "ftxui/component/captured_mouse.hpp" // for ftxui
#include "ftxui/component/component.hpp"	  // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp" // for ComponentBase
#include "ftxui/component/component_options.hpp" // for InputOption
#include "ftxui/component/screen_interactive.hpp" // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp" // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp" // for Ref

int main() {
	using namespace ftxui;

	// The data:
	std::string first_name;
	std::string last_name;
	std::string password;
	std::string phoneNumber;

	// The basic input components:
	Component input_first_name = Input(&first_name, "first name");
	Component input_last_name = Input(&last_name, "last name");

	// The password input component:
	InputOption password_option;
	password_option.password = true;
	Component input_password = Input(&password, "password", password_option);

	// The phone number input component:
	// We are using `CatchEvent` to filter out non-digit characters.
	Component input_phone_number = Input(&phoneNumber, "phone number");
	input_phone_number |= CatchEvent([&](Event event) {
		return event.is_character() && !std::isdigit(event.character()[0]);
	});
	input_phone_number |= CatchEvent([&](Event event) {
		return event.is_character() && phoneNumber.size() > 10;
	});

	// The component tree:
	auto component = Container::Vertical({
		input_first_name,
		input_last_name,
		input_password,
		input_phone_number,
	});

	// Welcome ASCII art component
	auto welcome = []() {
		auto content = vbox({
			text(L" _    _  _____  _      _____  _____ ___  ___ _____          "
				 L"            "),
			text(L"| |  | ||  ___|| |    /  __ \\|  _  ||  \\/  ||  ___|       "
				 L"              "),
			text(L"| |  | || |__  | |    | /  \\/| | | || .  . || |__          "
				 L"             "),
			text(L"| |/\\| ||  __| | |    | |    | | | || |\\/| ||  __|        "
				 L"  "
				 L"            "
				 L""),
			text(
				L"\\  /\\  /| |___ | |____|  \\__/\\ \\_/ /| |  | || |___ _    "
				L"    "
				L"            "
				L""),
			text(L" \\/  \\/ \\____/ \\_____/ \\___/  \\___/ \\_|  |_/\\____/( "
				 L")       "
				 L"            "
				 L""),
			text(L" _____  _          _     _____                    |/ _      "
				 L"          _ "
				 L""),
			text(L"/  ___|| |        | |   |_   _|                     (_)     "
				 L"         | |"
				 L""),
			text(L"\\ `--. | |_  __ _ | |_    | |  ___  _ __  _ __ ___   _  _ "
				 L"__    __ _ | |"
				 L""),
			text(L" `--. \\| __|/ _` || __|   | | / _ \\| '__|| '_ ` _ \\ | || "
				 L"'_ "
				 L"\\  / _` || |"
				 L""),
			text(L"/\\__/ /| |_| (_| || |_    | ||  __/| |   | | | | | || || | "
				 L"| || (_| || |"
				 L""),
			text(L"\\____/  \\__|\\__|_||__|    \\_/ \\___||_|   |_| |_| "
				 L"|_||_||_| "
				 L"|_| \\__|_||_|"
				 L""),
		});
		return content;
	};

	// Tweak how the component tree is rendered:
	auto renderer = Renderer(component, [&] {
		return vbox({
				   hbox({welcome()}), separator(),
				   hbox(text(" First name : "), input_first_name->Render()),
				   hbox(text(" Last name  : "), input_last_name->Render()),
				   hbox(text(" Password   : "), input_password->Render()),
				   hbox(text(" Phone num  : "), input_phone_number->Render()),
				   /*separator(),*/
				   /*text("Hello " + first_name + " " + last_name),*/
				   /*text("Your password is " + password),*/
				   /*text("Your phone number is " + phoneNumber),*/
			   }) |
			   border;
	});

	auto screen = ScreenInteractive::TerminalOutput();
	screen.Loop(renderer);
}
