//----------------------------------------------------------------------
#include <stdlib.h>
#include "grid.h"
//----------------------------------------------------------------------
const int Grid::G = 3;
const int Grid::LINE = G * G;
const int Grid::V = LINE * LINE;
//----------------------------------------------------------------------
std::vector<int> Grid::answer(81);
const int Grid::bitcount[512] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9};
//----------------------------------------------------------------------
const int Grid::bitindex[512] = {0, 1, 2, 0, 3, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//----------------------------------------------------------------------
const int Grid::block_index[81] = {0, 0, 0, 3, 3, 3, 6, 6, 6, 0, 0, 0, 3, 3, 3, 6, 6, 6, 0, 0, 0, 3, 3, 3, 6, 6, 6, 27, 27, 27, 30, 30, 30, 33, 33, 33, 27, 27, 27, 30, 30, 30, 33, 33, 33, 27, 27, 27, 30, 30, 30, 33, 33, 33, 54, 54, 54, 57, 57, 57, 60, 60, 60, 54, 54, 54, 57, 57, 57, 60, 60, 60, 54, 54, 54, 57, 57, 57, 60, 60, 60};
//----------------------------------------------------------------------
double
Grid::myrand(void){
  return static_cast<double>(rand())/(static_cast<double>(RAND_MAX)+1.0);
}
//----------------------------------------------------------------------
int
Grid::myrand(const int i){
  return static_cast<int>(myrand()*i);
}
//----------------------------------------------------------------------
int
Grid::solve(void) {
  solve_sub();
  if(rest == 0) {
    //printf("Solved! Depth = %d\n",depth);
    //show_data();
    std::copy(&data[0], &data[V], answer.begin());
    return 1;
  }

  int min = 9;
  int min_index = -1;
  for(int i = 0; i < V; i++) {
    if(data[i] != 0)continue;
    if(min > bitcount[grid[i]]) {
      min = bitcount[grid[i]];
      min_index = i;
    }
  }
  if(min == 0) {
    return 0;
  }

  std::vector<int> v;
  b2a(grid[min_index], v);
  int sum = 0;
  for(unsigned int i = 0; i < v.size(); i++) {
    Grid g2 = (*this);
    g2.put(min_index, v[i]);
    sum += g2.solve();
  }
  return sum;
}
//----------------------------------------------------------------------
void
Grid::solve_sub(void) {
  bool flag = true;
  while(flag) {
    flag = false;
    for(int i = 0; i < V; i++) {
      if (data[i] == 0 && bitcount[grid[i]] == 1) {
        put(i, bitindex[grid[i]]);
        flag = true;
      }
    }
  }
}
//----------------------------------------------------------------------
void
Grid::put(int index, int value) {
  rest--;
  data[index] = value;
  const int v = 511 ^ (1 << (value - 1));
  const int sv = index % LINE;
  grid[sv] &= v;
  grid[sv + 9] &= v;
  grid[sv + 18] &= v;
  grid[sv + 27] &= v;
  grid[sv + 36] &= v;
  grid[sv + 45] &= v;
  grid[sv + 54] &= v;
  grid[sv + 63] &= v;
  grid[sv + 72] &= v;
  const int sh = (index / LINE) * LINE;
  grid[sh] &= v;
  grid[sh + 1] &= v;
  grid[sh + 2] &= v;
  grid[sh + 3] &= v;
  grid[sh + 4] &= v;
  grid[sh + 5] &= v;
  grid[sh + 6] &= v;
  grid[sh + 7] &= v;
  grid[sh + 8] &= v;
  const int si = block_index[index];
  grid[si] &= v;
  grid[si + 1] &= v;
  grid[si + 2] &= v;
  grid[si + 9] &= v;
  grid[si + 10] &= v;
  grid[si + 11] &= v;
  grid[si + 18] &= v;
  grid[si + 19] &= v;
  grid[si + 20] &= v;
}
//----------------------------------------------------------------------
int
Grid::shortest_path(int s_path) {
  if (depth >= s_path) return depth;
  solve_sub();
  if(rest == 0) {
    //printf("Find path at %d\n", depth);
    s_path = depth;
  }
  int min = 9;
  for(int i = 0; i < V; i++) {
    if(data[i] == 0 && min > bitcount[grid[i]]) {
      min = bitcount[grid[i]];
    }
  }
  std::vector<int> vlist;
  for(int i = 0; i < V; i++) {
    if(data[i] == 0 && bitcount[grid[i]] == min) {
      vlist.push_back(i);
    }
  }
  for(unsigned int i = 0; i < vlist.size(); i++) {
    const int index = vlist[i];
    Grid g2 = (*this);
    g2.put(index, answer[index]);
    int sp = g2.shortest_path(s_path);
    if(sp < s_path) {
      s_path = sp;
    }
  }
  return s_path;
}
//----------------------------------------------------------------------
int
Grid::r_width(void) {
  solve_sub();
  if(rest == 0) {
    std::copy(&data[0], &data[V], answer.begin());
    return 1;
  }

  int min = 9;
  for(int i = 0; i < V; i++) {
    if(data[i] != 0)continue;
    if(min > bitcount[grid[i]]) {
      min = bitcount[grid[i]];
    }
  }

  if(0 == min) {
    return 1;
  }

  std::vector<int> vlist;
  for(int i = 0; i < V; i++) {
    if(data[i] == 0 && bitcount[grid[i]] == min) {
      vlist.push_back(i);
    }
  }

  const int j = myrand(vlist.size());
  const int min_index = vlist[j];

  std::vector<int> v;
  b2a(grid[min_index], v);
  int sum = 0;
  for(unsigned int i = 0; i < v.size(); i++) {
    Grid g2 = (*this);
    g2.put(min_index, v[i]);
    sum += g2.r_width();
  }
  return sum + 1;
}
//----------------------------------------------------------------------
int
Grid::width(void) {
  solve_sub();
  if(rest == 0) {
    //printf("Solved! Depth = %d\n",depth);
    //show_data();
    std::copy(&data[0], &data[V], answer.begin());
    return 1;
  }

  int min = 9;
  int min_index = -1;
  for(int i = 0; i < V; i++) {
    if(data[i] != 0)continue;
    if(min > bitcount[grid[i]]) {
      min = bitcount[grid[i]];
      min_index = i;
    }
  }
  if(min == 0) {
    return 1;
  }

  std::vector<int> v;
  b2a(grid[min_index], v);
  int sum = 0;
  for(unsigned int i = 0; i < v.size(); i++) {
    Grid g2 = (*this);
    g2.put(min_index, v[i]);
    sum += g2.width();
  }
  return sum + 1;
}
//----------------------------------------------------------------------
