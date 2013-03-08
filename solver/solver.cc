//----------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <math.h>
#include "grid.h"
//----------------------------------------------------------------------
int
main(int argc, char**argv){
  if(argc != 2){
    std::cout << "Usage: ./solver filename" << std::endl;
    return -1;
  }
  std::ifstream ifs(argv[1]);
  if(ifs.fail()){
    std::cout << "No such file:" << argv[1] << std::endl;
    return -1;
  }

  std::string str;
  std::string str2;
  while(!ifs.eof()){
    getline(ifs,str2);
    str = str + str2 + ",";
  }
  std::replace(str.begin(), str.end(), ',', ' ');
  std::istringstream is(str);
  std::vector<int> v;
  while(is){
    is >> str;
    v.push_back(atoi(str.c_str()));
  }
  v.resize(81);
  Grid g(v);
  int ans = g.solve();
  printf("This puzzle has %d answer[s].\n",ans);
  if (ans!=1){
    return 0;
  }
  g.show_answer();
  const int sp = g.shortest_path(Grid::V);
  printf("Depth = %d\n",sp);
  printf("Normal Width %d\n",g.width());
  const int N = 100;
  double sum = 0.0;
  double var = 0.0;
  for(int i=0;i<N;i++){
    const double w = (double)g.r_width();
    sum += w/(double)N;
    var += w*w/(double)N;
  }
  var -= sum*sum;
  var = sqrt(var/(double)N);
  printf("Average Width %f +- %f\n",sum,var);
}
//----------------------------------------------------------------------
