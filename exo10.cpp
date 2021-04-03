#include <cstdio>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <mpi.h>

void charge_3(int me,int n,int np,int *iBeg, int *iEnd)
{
    int r=n%np;
    if(me<r){
       *iBeg=(n/np+1)*me;
       *iEnd=(n/np+1)*(me+1)-1;
    }else{
       *iBeg=r+me*(n/np);
       *iEnd=r+(me+1)*(n/np)-1;
    }
}



int main(int argc, char *argv[])
{

  int n;
  if(argc!=2){
    printf("ERROR\n");
    exit(1);
  }
  n=atoi(argv[1]);
  n=n+1;
  int rank,nproc,iree;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);

  int i,j,iBeg,iEnd,somme;

    charge_3(rank,n,nproc,&iBeg,&iEnd);
    j=0;
    for(int i=iBeg;i<=iEnd;++i){
      j+=i;
    }

    iree=MPI_Allreduce(&j, &somme, 1,MPI_INT, MPI_SUM, MPI_COMM_WORLD);



    printf("Hello,I am rank %d/%d la somme est %d\n",rank,nproc,somme);


  MPI_Finalize();

  return 0;
}
