#include "../include/GameMap.hpp"
#include <unistd.h>

GameMap::GameMap(int h, int w, int micro) {
    this->m_h = h + 2;
    this->m_w = w + 2;
    this->m_micro = micro;
    std::vector<std::vector<char>> reseved(m_h, std::vector<char>(m_w, '.'));
    v.swap(reseved);
}
GameMap::GameMap(int h, int w, std::vector<std::pair<int, int>> &cor,
	std::pair<int, int> off, int micro)
    : GameMap(h, w, micro) {
	for (auto &i : cor) {
	    v[i.first + off.first][i.second + off.second] = '#';
	}
    }

int GameMap::nbr_neigh(int x, int y) {
    int res{};
    for (int i = x - 1; i < x + 2; i++) {
	for (int j = y - 1; j < y + 2; j++) {
	    if (j == y && i == x)
		continue;
	    res += v[i][j] == '#';
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
    std::vector<std::vector<char>> alt_buff(m_h, std::vector<char>(m_w, '.'));
    std::cout << "\033[2J";
    while (true) {
	std::cout << "\033[1;1H";
	usleep(m_micro);
	for (int i = 1; i < (m_h - 1); i++) {
	    for (int j = 1; j < (m_w - 1); j++) {
		switch (v[i][j]) {
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
	v.swap(alt_buff);
	// want endl to flush the buffer
	std::cout << *this;
	std::cout << std::endl;
    }
}

const std::ostream &operator<<(std::ostream &os, const GameMap &gm) {
    for (auto &row : gm.v) {
	for (char i : row) {
	    os << i;
	}
	os << '\n';
    }
    return os;
}
