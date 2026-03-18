#include <iostream>
#include <unistd.h>
#include <vector>
#include "resources/glider.hpp"


struct GameMap {
  int m_h;
  int m_w;
  int m_micro;
  std::vector<std::vector<char>> v;
  GameMap(int h, int w, int micro = 200000) {
    this->m_h = h + 2;
    this->m_w = w + 2;
    this->m_micro = micro;
    std::vector<std::vector<char>> reseved(m_h, std::vector<char>(m_w, '.'));
    v.swap(reseved);
  }
  GameMap(int h, int w, std::vector<std::pair<int, int>> &cor,std::pair<int,int>off,
          int micro = 200000)
      : GameMap(h, w, micro) {
    for (auto &i : cor) {
      v[i.first+off.first][i.second+off.second] = '#';
    }
  }

private:
  int nbr_neigh(int x, int y) {
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
public:
  void play() {
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
      v = alt_buff;
      // want endl to flush the buffer
      std::cout << *this;
      std::cout << std::endl;
    }
  }

  friend const std::ostream &operator<<(std::ostream &os, const GameMap &gm) {
    for (auto &row : gm.v) {
      for (char i : row) {
        os << i;
      }
      os << '\n';
    }
    return os;
  }
};

// I will not use get opt just for edu pru
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout << "hello world\n";
  auto g = GameMap(60, 60,glider_gun,{5,5});
  // g.v[5][5] = '#';
  // g.v[5][6] = '#';
  // g.v[6][5] = '#';
  // g.v[6][6] = '#';
  // g.v[7][7] = '#';
  // g.v[7][8] = '#';
  // g.v[8][7] = '#';
  // g.v[8][8] = '#';
  // g.v[11][4] = '#';
  // g.v[12][4] = '#';
  // g.v[13][4] = '#';
  //
  g.play();
  return 0;
}
