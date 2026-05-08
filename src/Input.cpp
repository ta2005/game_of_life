#include <unistd.h>
#include "../include/Input.hpp"


namespace Input{
    // will change this one to a std::optionl
    char read_key() {
	char c;
	if (read(STDIN_FILENO, &c, 1) == 1) {
	    return c;
	}
	return '\0';
    }

    Action handle_arrow(){
	if (read_key() == '[') {
	    char next=read_key();
	    switch(next){
		case 'A': return  Action::Up;
		case 'B': return  Action::Down;
		case 'C': return  Action::Left;
		case 'D': return  Action::Right;
	    }
	}
	return Action::Nothing;
    }


    Action get_input(){
	using namespace Input;

	constexpr char KEY_ENTER = 10; // code of 'Enter'
	constexpr char KEY_ESC = 27;   // code of 'ESC'
	char c = read_key();
	switch (c) {
	    case KEY_ESC: return handle_arrow();
	    case KEY_ENTER: return Action::Accept;
	    case 'k':return Action::Up;
	    case 'j':return Action::Down;
	    case 'h':return Action::Right;
	    case 'l':return Action::Left;
	    case 'q': return Action::Quit;
	    case 'm': return Action::Modify;
	    default : return Action::Nothing;
	}
	return Action::Unknown;
    }
}
