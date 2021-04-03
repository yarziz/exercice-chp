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
  int valeur;
  int somme;

  if(rank==0){
    valeur=1000;
  }else{
    valeur=rank;
  }

  iree= MPI_Reduce(&valeur,&somme, 1, MPI_INT,MPI_SUM, 0, MPI_COMM_WORLD);

  if(rank==0){
    printf("c'est ma valeur est :%d\n",somme );
  }

  MPI_Finalize();

  return 0;
}
