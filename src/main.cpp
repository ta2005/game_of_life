#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <getopt.h>
#include "../include/reference.hpp"
#include "../include/GameMap.hpp"


//the option are w and h to speify the width and height
// I will not use get opt just for edu pru
int main(int argc,char **argv) {
    int c;
    int w=60;
    int h=60;
    while((c=getopt(argc,argv,"w:h:"))!=-1){
	switch (c){
	    case 'w': std::sscanf(optarg,"%d",&w);break;
	    case 'h': std::sscanf(optarg,"%d",&h);break;
	    default:  return 1;
	}
    }
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    auto g = GameMap(h, w,glider_gun,{5,5});

    g.play();
    return 0;
}
