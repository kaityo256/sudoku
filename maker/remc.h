//----------------------------------------------------------------------
#ifndef remc_h
#define remc_h
#include <vector>
//----------------------------------------------------------------------

//----------------------------------------------------------------------
class REMC {
private:
  double myrand(void);
  std::vector<WidthSearcher*> s;
  std::vector<double> beta;
  std::vector<int> b_index;
  std::vector<int> accept;
  const int n_replica;
  void swap_replica(const int j1, const int j2);
  double lowest_energy;
  void check_energy(void);
  int step;
  void mc_onestep(void);
public:
  REMC(int n, std::vector<int> v, std::vector<int> answer);
  ~REMC(void);
  void domc(void);
  void domc_with_beta_adjust(const double p);
  void beta_average(const double beta);
};
//----------------------------------------------------------------------
#endif
