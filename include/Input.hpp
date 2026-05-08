#ifndef __INPUT_HPP_
#define __INPUT_HPP_

namespace Input{
    enum class Action{
	Up,
	Down,
	Left,
	Right,
	Accept,
	Quit,
	Modify,
	Nothing,
	Unknown,
    };

    Action get_input();
}

#endif
