//----------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <mpi.h>
#include "mpistream.h"
#include "searcher.h"
#include "grid.h"
#include "remc.h"
//----------------------------------------------------------------------
const int N_REPLICA = 10;
const double DEPTH_THRESHOLD = -800.0;
const double EXCHANGE_RATIO = 0.8;
const double J_depth = 100.0;
const double J_width = 100.0;
//----------------------------------------------------------------------
bool search(Grid &g2, int index, std::vector<int> &ans) {
  if(index == Grid::V) {
    g2.get_data(ans);
    return true;
  }
  std::vector<int> a;
  g2.get_grid(index, a);
  if (a.size() == 0)return false;
  std::random_shuffle(a.begin(), a.end());
  for(unsigned int i = 0; i < a.size(); i++) {
    Grid g = g2;
    g.put(index, a[i]);
    if(search(g, index + 1, ans))return true;
  }
  return false;
}
//----------------------------------------------------------------------
std::vector<int>
make_problem(const int seed) {
  std::vector<int> a;
  std::vector<int> b;
  srand(static_cast<unsigned int>(seed));
  const int LINE = Grid::LINE;
  for(int i = 0; i < LINE; i++) {
    b.push_back(i+1);
  }
  std::random_shuffle(b.begin(), b.end());
  Grid g;
  for(int i = 0; i < LINE; i++) {
    g.put(i, b[i]);
  }
  search(g, 9, a);
  return a;
}
//----------------------------------------------------------------------
int
main(int argc, char**argv) {
  int rank = 0;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  mout.SetRank(rank);
  std::ifstream ifs("seed.dat");
  int seed = 0;
  ifs >> seed;
  mout << "# Number of Replica = " << N_REPLICA << std::endl;
  mout << "# Depth Threashold = " << DEPTH_THRESHOLD << std::endl;
  mout << "# Exchange Ratio = " << EXCHANGE_RATIO << std::endl;
  mout << "# J_depth = " << J_depth << std::endl;
  mout << "# J_width = " << J_width << std::endl;
  mout << "# seed = " << seed << std::endl;
  const std::vector<int> answer = make_problem(seed + rank);
  mout << "# myseed = " << seed + rank << std::endl;
  mout << "# Starting Grid" << std::endl;
  DepthSearcher::J = J_depth;
  WidthSearcher::J = J_width;
  Searcher::show_data(answer);
  DepthSearcher ds(answer);
  ds.search_with_threshold(DEPTH_THRESHOLD, 0.05);
  std::vector<int> v = ds.get_data();
  ds.show_data(v);
  REMC rm(N_REPLICA, v, answer);
  while(true){
    rm.domc_with_beta_adjust(EXCHANGE_RATIO);
    //rm.domc();
  }
  MPI_Finalize();
}
//----------------------------------------------------------------------
