//----------------------------------------------------------------------
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "mpistream.h"
#include "grid.h"
#include "searcher.h"
//----------------------------------------------------------------------
double DepthSearcher::J = 100.0;
double WidthSearcher::J = 100.0;
//----------------------------------------------------------------------
double
Searcher::myrand(void) {
  return static_cast<double>(rand()) / (static_cast<double>(RAND_MAX));
}
//----------------------------------------------------------------------
int
Searcher::myrand(const int max) {
  double r = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX)+1.0);
  return static_cast<int>(r * max);
};
//----------------------------------------------------------------------
void
Searcher::random_remove(std::vector<int> &v) {
  std::vector<int> a;
  for(unsigned int i = 0; i < v.size(); i++) {
    if(v[i] != 0) {
      a.push_back(i);
    }
  }
  if (0 == a.size())return;
  const int j = myrand(a.size());
  v[a[j]] = 0;
}
//----------------------------------------------------------------------
void
Searcher::random_put(std::vector<int> &v) {
  std::vector<int> a;
  for(unsigned int i = 0; i < v.size(); i++) {
    if(v[i] == 0) {
      a.push_back(i);
    }
  }
  if (0 == a.size())return;
  const int j = myrand(a.size());
  v[a[j]] = answer[a[j]];
}
//----------------------------------------------------------------------
void
Searcher::show_data(const std::vector<int> &v) {
  for(int i = 0; i < Grid::V; i++) {
    if(i != 0 && i % Grid::LINE == 0) {
      mout << std::endl;
    }
    mout << v[i] << " ";
  }
  mout << std::endl;
  mout << std::endl;
}
//----------------------------------------------------------------------
void
Searcher::show_data(std::vector<int> &v) {
  for(int i = 0; i < Grid::V; i++) {
    if(i != 0 && i % Grid::LINE == 0) {
      mout << std::endl;
    }
    mout << v[i] << " ";
  }
  mout << std::endl;
  mout << std::endl;
}
//----------------------------------------------------------------------
double
DepthSearcher::energy(std::vector<int> &v) {
  Grid g(v);
  const int r = g.get_rest();
  g.solve();
  const int sp = g.shortest_path();
  return static_cast<double>(-J*sp - r);
}
//----------------------------------------------------------------------
void
DepthSearcher::search_with_threshold(const double threshold, const double beta) {
  while(true) {
    search(beta);
    if(current_energy < threshold)break;
  }
};
//----------------------------------------------------------------------
void
DepthSearcher::search(const double beta) {
  std::vector<int> v2 = data;
  random_remove(v2);
  Grid gn(v2);
  if(1 == gn.solve()) {
    const double e2 = energy(v2);
    const double de = e2 - current_energy;
    if (de < 0 || exp(-de * beta) > myrand()) {
      data = v2;
      current_energy = e2;
    }
  }
  v2 = data;
  random_put(v2);
  const double e2 = energy(v2);
  const double de = e2 - current_energy;
  if (de < 0 || exp(-de * beta) > myrand()) {
    data = v2;
    current_energy = e2;
  }
  if(current_energy < lowest_energy) {
    lowest_energy = current_energy;
  }
}
//----------------------------------------------------------------------
double
WidthSearcher::energy(std::vector<int> &v) {
  Grid g(v);
  const double r = static_cast<double>(g.get_rest());
  const double sp = static_cast<double>(g.width());
  return (-J*log(sp) - r);
}
//----------------------------------------------------------------------
int
WidthSearcher::get_width(void) {
  Grid g(data);
  return g.width();
}
//----------------------------------------------------------------------
double
WidthSearcher::get_rwidth(void){
  Grid g(data);
  double sum = 0.0;
  const int N = 100;
  for(int i=0;i<N;i++){
    sum += g.r_width();
  }
  sum /= (double)N;
  return sum;
}
//----------------------------------------------------------------------
void
WidthSearcher::search(const double beta) {
  const int LOOP = 10;
  for(int i = 0; i < LOOP; i++) {
    std::vector<int> v2 = data;
    random_remove(v2);
    Grid gn(v2);
    if(1 == gn.solve()) {
      const double e = energy(v2);
      const double de = e - current_energy;
      if (de < 0 || exp(-de * beta) > myrand()) {
        data = v2;
        current_energy = e;
      }
    }
    v2 = data;
    random_put(v2);
    const double e = energy(v2);
    const double de = e - current_energy;
    const double r = myrand();
    if (de < 0 || exp(-de * beta) > r) {
      data = v2;
      current_energy = e;
    }
    if(current_energy < lowest_energy) {
      lowest_energy = current_energy;
    }
  }
}
//----------------------------------------------------------------------
