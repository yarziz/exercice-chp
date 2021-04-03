#include <cstdio>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <mpi.h>





int main(int argc, char *argv[])
{


  int rank,nproc,iree;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  printf("Hello,I am rank %d/%d\n",rank,nproc);
  int i,j;
  std::vector<int> v(nproc,0);
  v[rank]=rank;
  iree= MPI_Bcast(&v[0],  nproc, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Finalize();

  return 0;
}
