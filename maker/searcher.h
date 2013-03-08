#ifndef searcher_h
#define searcher_h
//----------------------------------------------------------------------
#include <vector>
//----------------------------------------------------------------------
class Searcher {
protected:
  const std::vector<int> answer;
  std::vector<int> data;
  double lowest_energy;
  double current_energy;
  double myrand(void);
  int myrand(const int max);
  void random_remove(std::vector<int> &v);
  void random_put(std::vector<int> &v);
public:
  static void show_data(const std::vector<int> &v);
  static void show_data(std::vector<int> &v);
  void show_data(void){
     show_data(data);
  };
  Searcher(const std::vector<int> a) : answer(a) {};
  std::vector<int> get_data(void) {return data;};
};
//----------------------------------------------------------------------
class DepthSearcher : public Searcher {
public:
  static double J;
  double energy(std::vector<int> &v);
  void search(const double beta);
  void search_with_threshold(const double beta, const double threshold);
  DepthSearcher(const std::vector<int> a) : Searcher(a) {
    data = answer;
    lowest_energy = energy(data);
    current_energy = lowest_energy;
  };
};
//----------------------------------------------------------------------
class WidthSearcher : public Searcher {
private:
  double energy(std::vector<int> &v);
public:
  static double J;
  WidthSearcher(std::vector <int> &start, const std::vector<int> &a) : Searcher(a) {
    data = start;
    lowest_energy = energy(data);
    current_energy = lowest_energy;
  };
  void search(const double beta);
  double get_current_energy(void) {return current_energy;};
  int get_width(void);
  double get_rwidth(void);
};
//----------------------------------------------------------------------
#endif
