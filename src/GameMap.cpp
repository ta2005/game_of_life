#include "../include/GameMap.hpp"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

GameMap::GameMap(int h, int w, int micro) {
    this->m_h = h + 2;
    this->m_w = w + 2;
    this->m_micro = micro;
    std::vector<std::vector<char>> reseved(m_h, std::vector<char>(m_w, '.'));
    map.swap(reseved);
}
GameMap::GameMap(int h, int w, std::vector<std::pair<int, int>> &cor,
	std::pair<int, int> off, int micro)
    : GameMap(h, w, micro) {
	for (auto &i : cor) {
	    map[i.first + off.first][i.second + off.second] = '#';
	}
    }

// will change this one to a std::optionl
char read_key() {
    char c;
    if (read(STDIN_FILENO, &c, 1) == 1) {
	return c;
    }
    return '\0';
}

// We need to store the original state globally so we can put it back later!
struct termios orig_term;
int orig_fcntl;

void restore_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
    fcntl(STDIN_FILENO, F_SETFL, orig_fcntl);
}

void init_terminal() {
    // 1. Save the original terminal settings
    tcgetattr(STDIN_FILENO, &orig_term);

    // 2. Disable canonical mode and echo (what you already wrote)
    struct termios term = orig_term;
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    // 3. Save the original file control flags
    orig_fcntl = fcntl(STDIN_FILENO, F_GETFL, 0);
    atexit(restore_terminal);

    // 4. THE MAGIC: Append the O_NONBLOCK flag to STDIN
    fcntl(STDIN_FILENO, F_SETFL, orig_fcntl | O_NONBLOCK);
}


void GameMap::modify_map() {
    // constexpr char KEY_UP = 65;    // code of 'A' (UP arrow)
    // constexpr char KEY_DOWN = 66;  // code of 'B' (DOWN arrow)
    // constexpr char KEY_LEFT = 67;  // code of 'A' (UP arrow)
    // constexpr char KEY_RIGHT = 68; // code of 'B' (DOWN arrow)
    constexpr char KEY_ENTER = 10; // code of 'Enter'
    constexpr char KEY_ESC = 27;   // code of 'ESC'
    constexpr char KEY_Q = 113;    // code of 'q'

    int x = 0;
    int y = 0;
    std::cout << "\033[2J";
    while (true) {
	usleep(30000);
	std::cout << "\033[1;1H";
	std::cout << "use the arrows keys to move enter to toggle and q or esc to quit\n";

	for (int i = 0; i < m_h; i++) {
	    for (int j = 0; j < m_w; j++) {
		if (i == x && j == y) {
		    std::cout << "\033[42m" << map[x][y] << "\033[0m";
		} else {
		    std::cout << map[i][j];
		}
	    }
	    std::cout << '\n';
	}

	char c = read_key();
	std::cout << c << std::endl;
	switch (c) {
	    case KEY_ESC: 
		{
		    if (read_key() == '[') {
			char next=read_key();
			switch(next){
			    case 'A' :
				x = (x - 1 + m_w) % m_w;
				break;
			    case 'B':
				(++x) %= m_w;
				break;
			    case 'C':
				(++y) %= m_h;
				break;
			    case 'D':
				y = (y - 1 + m_h) % m_h;
				break;
			}
		    }
		};break;
	    case KEY_ENTER:
		toggle(x, y);
		break;
	    case KEY_Q:
		return;
	}
    }
}

int GameMap::nbr_neigh(const int x, const int y) {
    int res{};
    for (int i = x - 1; i < x + 2; i++) {
	for (int j = y - 1; j < y + 2; j++) {
	    if (j == y && i == x)
		continue;
	    res += map[i][j] == '#';
	}
    }
    return res;
}
// Any live cell with fewer than two live neighbours dies, as if by
// underpopulation.
// Any live cell with two or three live neighbours lives on to the next
// generation. Any live cell with more than three live neighbours dies, as if
// by overpopulation. Any dead cell with exactly three live neighbours becomes
// a live cell, as if by reproductio
void GameMap::play() {
    init_terminal();
    std::vector<std::vector<char>> alt_buff(m_h, std::vector<char>(m_w, '.'));
    std::cout << "\033[2J";
    while (true) {
	usleep(m_micro);
	std::cout<<"\033[1;1H";
	std::cout<<"Use m to modify the layout\n";
	if (read_key() == 'm') {
	    modify_map();
	}
	for (int i = 1; i < (m_h - 1); i++) {
	    for (int j = 1; j < (m_w - 1); j++) {
		switch (map[i][j]) {
		    case '.': {
				  nbr_neigh(i, j) == 3 ? alt_buff[i][j] = '#' : alt_buff[i][j] = '.';
			      } break;
		    case '#': {
				  int n = nbr_neigh(i, j);
				  if (n < 2 || n > 3) {
				      alt_buff[i][j] = '.';
				  } else {
				      alt_buff[i][j] = '#';
				  }
			      } break;
		}
	    }
	}
	map.swap(alt_buff);
	// want endl to flush the buffer
	std::cout << *this;
	std::cout << std::endl;
    }
    restore_terminal();
}

const std::ostream &operator<<(std::ostream &os, const GameMap &gm) {
    for (auto &row : gm.map) {
	for (char i : row) {
	    os << i;
	}
	os << '\n';
    }
    return os;
}

void GameMap::toggle(const int x, const int y) {
    map[x][y] == '#' ? map[x][y] = '.' : map[x][y] = '#';
}
