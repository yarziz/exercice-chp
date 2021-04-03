#include <cstdio>
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
  int i=0;
  if(rank==0){
    i=1000;
    int j=0;
    iree=MPI_Send(&i,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
    iree=MPI_Recv(&j,1,MPI_INT,nproc-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    printf("Moi processus %d j'ai reçu la valeur %d du processus %d\n",rank,j,nproc-1);
  }

  if(rank>0&&rank<nproc){
      int i=0;
      iree=MPI_Recv(&i,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      printf("Moi processus %d j'ai reçu la valeur %d du processus %d\n",rank,i,rank-1);
      i+=1;
      iree=MPI_Send(&i,1,MPI_INT,(rank+1)%nproc,0,MPI_COMM_WORLD);
  }






  MPI_Finalize();

  return 0;
}
