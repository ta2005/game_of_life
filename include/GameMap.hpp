#ifndef __GAMEMAP_HPP__
#define __GAMEMAP_HPP__

#include <iostream>
#include <vector>

class GameMap {
    int m_h;
    int m_w;
    int m_micro;

    public:
	std::vector<std::vector<char>> map;
	GameMap(int h, int w, int micro = 200000);
	GameMap(int h, int w, std::vector<std::pair<int, int>> &cor,
		std::pair<int, int> off, int micro = 200000);

    private:
	int nbr_neigh(const int x,const int y);
	void modify_map();

    public:
	void play();
	void toggle(const int x,const int y);
	friend const std::ostream &operator<<(std::ostream &os, const GameMap &gm);
};

#endif
