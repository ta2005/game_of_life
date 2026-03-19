#include <iostream>
#include <unistd.h>
#include "../include/reference.hpp"
#include "../include/GameMap.hpp"


// I will not use get opt just for edu pru
int main(int argc,char **argv) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    auto g = GameMap(60, 60,repeat,{5,5});

    g.play();
    return 0;
}
