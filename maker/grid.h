//----------------------------------------------------------------------
#ifndef grid_h
#define grid_h
//----------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <string.h>
//----------------------------------------------------------------------
const int SIZE = 81;
//----------------------------------------------------------------------
class Grid {
private:
  static const int bitcount[512];
  static const int bitindex[512];
  static const int block_index[SIZE];
  int grid[SIZE];
  int data[SIZE];
  int rest;
  const int depth;
  double myrand(void);
  int myrand(const int);

  void b2a(int i, std::vector<int> &v) {
    v.clear();
    int b = 1;
    while(i != 0) {
      if(i % 2 == 1) {
        v.push_back(b);
      }
      i = i / 2;
      b++;
    }
  };

  void init(void) {
    rest = V;
    for(int i = 0; i < V; i++) {
      grid[i] = 511;
    }
    for(int i = 0; i < V; i++) {
      if(data[i] != 0) {
        put(i, data[i]);
      }
    }
  };

public:
  static const int G;
  static const int LINE;
  static const int V;
  static std::vector<int> answer;

  Grid(std::vector<int> &v, int d = 0) : depth(d) {
    std::copy(v.begin(), v.end(), &data[0]);
    init();
  }

  Grid(int d = 0) : depth(d) {
    for(int i = 0; i < V; i++) {
      data[i] = 0;
    }
    init();
  }

  Grid(const Grid &g) : depth(g.depth + 1) {
    memcpy(data, g.data, sizeof(int)*SIZE);
    memcpy(grid, g.grid, sizeof(int)*SIZE);
    rest = g.rest;
  };

  int get_rest(void) {
    return rest;
  };

  void get_grid(int index, std::vector<int> &v) {
    b2a(grid[index], v);
  }

  void get_data(std::vector<int> &v) {
    v.clear();
    v.resize(V);
    std::copy(&data[0], &data[V], v.begin());
  }

  void show_grid(void) {
    std::stringstream ss;
    std::vector<int> v;
    for(int i = 0; i < V; i++) {
      if (data[i] != 0) continue;
      b2a(grid[i], v);
      ss.str("");
      ss.clear();
      ss << i << " ";
      for(unsigned int j = 0; j < v.size(); j++) {
        ss << v[j];
      }
      std::cout << ss.str() << " " << bitcount[grid[i]] << std::endl;
    }
  }

  void show_data(void) {
    for(int i = 0; i < V; i++) {
      if(i != 0 && i % LINE == 0) {
        std::cout << std::endl;
      }
      std::cout << data[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
  }

  void put(int index, int value);

  void solve_sub(void);
  int solve(void);
  int r_width(void);
  int width(void);

  int shortest_path(int s_path = Grid::V);
};
//----------------------------------------------------------------------
#endif
//----------------------------------------------------------------------
