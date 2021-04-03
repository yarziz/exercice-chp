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
  if(rank==2){
    i=1000;
    printf("ok\n");
    iree=MPI_Send(&i,1,MPI_INT,5,0,MPI_COMM_WORLD);
  }else if(rank==5){
    int j=12;
    //printf("on rank %d/%d  before communication :%d\n",rank,nproc,j);
    iree=MPI_Recv(&j,1,MPI_INT,2,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    printf("Moi processus %d j'ai reçu la valeur %d du processus 2\n",rank,j);
    //printf("on rank %d/%d  after communication :%d\n",rank,nproc,j);
  }
  MPI_Finalize();

  return 0;
}
