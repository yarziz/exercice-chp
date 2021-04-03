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
  printf("Hello,I am rank %d/%d\n",rank,nproc);
  int i,j,iBeg,iEnd;

    charge_3(rank,n,nproc,&iBeg,&iEnd);
    j=0;
    for(int i=iBeg;i<=iEnd;++i){
      j+=i;
    }
    if(rank==0){
      for(int k=1;k<nproc;k++){
        int i=0;
        iree=MPI_Recv(&i,1,MPI_INT,k,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        j+=i;
      }
        printf("la valeur de somme de %d nombre est %d\n",n-1,j);
    }else{
      iree=MPI_Send(&j,1,MPI_INT,0,0,MPI_COMM_WORLD);
      printf("Moi le proc %d j'ai envoyé la valeur %d, j'ai commencé par %d et j'ai terminé par %d\n",rank,j,iBeg,iEnd);
    }




  MPI_Finalize();

  return 0;
}
