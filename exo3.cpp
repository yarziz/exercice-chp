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
  int i=0;
  if(rank==0){
    //std::vector<double> i1;
    //i1.resize(4);
    double i1[4];
    i1[0]=0;
    i1[1]=0;
    i1[2]=0;
    i1[3]=0;
    //i=1000;
    for(int j=1;j<nproc;j++){
      iree=MPI_Send(&i1,4,MPI_DOUBLE,j,0,MPI_COMM_WORLD);
    }
  }else{
      //std::vector<double> j1;
      double j1[4];
      iree=MPI_Recv(&j1,4,MPI_DOUBLE,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      printf("Moi processus %d j'ai reçu le tableau du processus %d et voilà mes nouvelles valeurs\n",rank,0);
      j1[0]+=rank;
      j1[2]+=rank;
      j1[3]+=rank;
      j1[1]+=rank;
      printf("%f, %f, %f, %f,  :: valeurs du proc %d\n",j1[0],j1[1],j1[2],j1[3],rank);
  }

  MPI_Finalize();

  return 0;
}
