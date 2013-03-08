#include <fstream>
#include <stdio.h>
#include "mpistream.h"

MPIStream mout;
//----------------------------------------------------------------------
void
MPIStream::SetRank(int r) {
  rank = r;
  char f[256];
  sprintf(f, "r%04d.out", rank);
  filename = f;
  std::ofstream ofs(filename.c_str());
}
//----------------------------------------------------------------------
MPIStream &
MPIStream::operator << (std::ostream & (*pf)(std::ostream &)) {
  os_backup << pf;
  std::cout << oss.str() << pf;
  std::ofstream ofs(filename.c_str(), std::ios_base::app);
  ofs << oss.str() << pf;
  oss.str("");
  oss.clear();
  return *this;
};
//----------------------------------------------------------------------
void
MPIStream::SaveToFile(std::string filename) {
  if (0 != rank) {
    return;
  }
  std::ofstream ofs(filename.c_str());
  ofs << os_backup.str() << std::endl;
}
//----------------------------------------------------------------------
void
MPIStream::AppendToFile(std::string filename) {
  if (0 != rank) {
    return;
  }
  std::ofstream ofs(filename.c_str(), std::ios_base::app);
  ofs << os_backup.str() << std::endl;
}
//----------------------------------------------------------------------


