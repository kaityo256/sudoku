//----------------------------------------------------------------------
#ifndef mpistream_h
#define mpistream_h
//----------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <string>
//----------------------------------------------------------------------
class MPIStream {
private:
  int rank;
  std::ostringstream oss;
  std::ostringstream os_backup;
  std::string filename;
public:
  MPIStream(void) {
    rank = 0;
  };
  void SetRank(int r);
  template <class T>
  MPIStream & operator << (const T&a) {
    oss << a;
    os_backup << a;
    return *this;
  }
  MPIStream & operator << (std::ostream & (*pf)(std::ostream &));
  void SaveToFile(std::string filename);
  void AppendToFile(std::string filename);
};
//----------------------------------------------------------------------
extern MPIStream mout;
#endif
