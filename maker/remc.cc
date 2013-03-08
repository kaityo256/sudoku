//----------------------------------------------------------------------
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include "mpistream.h"
#include "searcher.h"
#include "grid.h"
#include "remc.h"
//----------------------------------------------------------------------
double
REMC::myrand(void) {
  return (double)rand() / (double)RAND_MAX;
}
//----------------------------------------------------------------------
REMC::REMC(int n, std::vector<int> v, std::vector<int> answer) : n_replica(n) {
  s.resize(n_replica);
  for(int i = 0; i < n_replica; i++) {
    s[i] = new WidthSearcher(v, answer);
    beta.push_back((i + 1) * 0.01);
    b_index.push_back(i);
    accept.push_back(0);
  }
  lowest_energy = s[0]->get_current_energy();
  step = 0;
}
//----------------------------------------------------------------------
REMC::~REMC(void) {
  for(int i = 0; i < n_replica; i++) {
    delete s[i];
  }
}
//----------------------------------------------------------------------
void
REMC::swap_replica(const int j1, const int j2) {
  const int i1 = b_index[j1];
  const int i2 = b_index[j2];
  const double b1 = beta[j1];
  const double b2 = beta[j2];
  const double e1 = s[i1]->get_current_energy();
  const double e2 = s[i2]->get_current_energy();
  const double w = (b1 - b2) * (e1 - e2);
  if(w > 0 || exp(w) > myrand()) {
    std::swap(b_index[j1], b_index[j2]);
    accept[j1]++;
  }
}
//----------------------------------------------------------------------
void
REMC::check_energy(void){
    for(int j = 0; j < n_replica; j++) {
      if(lowest_energy > s[j]->get_current_energy()){
        lowest_energy = s[j]->get_current_energy();
        mout << "# " << step << " Energy = " << lowest_energy;
        mout << " Width = " << s[j]->get_rwidth() << std::endl;
        s[j]->show_data();
      }
    }
}
//----------------------------------------------------------------------
void
REMC::mc_onestep(void){
  mout << "# " << step << std::endl;
  for(int j = 0; j < n_replica; j++) {
    s[j]->search(beta[j]);
  }
  //Replica Exchange
  for(int j = 0; j < n_replica / 2; j++) {
    swap_replica(j * 2, j * 2 + 1);
  }
  for(int j = 0; j < n_replica / 2 - 1; j++) {
    swap_replica(j * 2 + 1, j * 2 + 2);
  }
  step++;
}
//----------------------------------------------------------------------
void
REMC::domc_with_beta_adjust(const double p){
  for(int i=0;i<n_replica;i++){
    accept[i] = 0;
  }
  const int MC_STEPS = 100;
  for(int i=0;i<MC_STEPS;i++){
   mc_onestep();
   check_energy();
  }
  for(int i=0;i<n_replica-1;i++){
    if(accept[i] == 0){
      accept[i] = 1;
    }
  }
  std::vector<double> beta2 = beta;
  for(int i=0;i<n_replica-1;i++){
    const double a = static_cast<double>(accept[i])/static_cast<double>(MC_STEPS); 
    beta[i+1] = beta[i] + (beta2[i+1]-beta2[i])*a/p;
  } 
  mout << "# Adjust Temperature" << std::endl;
  for(int i = 0; i < n_replica; i++) {
    mout << "# " << i << " " << beta[i] << " " << s[i]->get_current_energy() <<  std::endl;
  }
}
//----------------------------------------------------------------------
void
REMC::domc(void) {
  mc_onestep();
  check_energy();
}
//----------------------------------------------------------------------
void
REMC::beta_average(const double beta){
  mout << "# beta = " << beta << std::endl;
  for(int i = 0; i < 100; i++) {
    for(int j = 0; j < n_replica; j++) {
      s[j]->search(beta);
    }
    double sum = 0.0;
    double var = 0.0;
    for(int j = 0; j < n_replica; j++) {
      const double e = s[j]->get_current_energy();
      //printf("%f\t",e);
      sum += e;
      var += e * e;
    }
    sum /= (double)n_replica;
    var = var - sum * sum * n_replica;
    var /= (double)(n_replica-1);
    const double se = sqrt(var);
    printf("%d %f %f\n", i, sum, se);
    // printf("\n");
  }
}
//----------------------------------------------------------------------
