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
  int k=3;
  int n;
  if(argc!=2){
    printf("ERROR\n");
    exit(1);
  }
  n=atoi(argv[1]);
  n=n;
  int rank,nproc,iree;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  printf("Hello,I am rank %d/%d\n",rank,nproc);
  int i,j,iBeg,iEnd,taille_tranche;
  charge_3(rank,n,nproc,&iBeg,&iEnd);

  //taille de trache matrice=nombre de ligne utilisé
  taille_tranche=iEnd-iBeg+1;
  std::vector<int> tranche_calcule(taille_tranche,0);
  std::vector<int> x(n,0);
  std::vector<int> matrice(taille_tranche*n,0);
  //int x_trache
  for(int i=0;i<taille_tranche;i++){
    for(int j=0;j<n;j++){
      matrice[i*n+j]=j+1;
    }
  }


for(int l=1;l<=k;l++){
  if(rank==0){
    if(l==1){
      for(int i=0;i<n;i++){
        x[i]=1;
      }
    }
    for (int i=1;i<nproc;i++){
      iree=MPI_Send(&x[0],n,MPI_INT,i,0,MPI_COMM_WORLD);
    }
  }else{
    MPI_Recv(&x[0],n,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  }

  for(int i=0;i<taille_tranche;++i){
    tranche_calcule[i]=0;
  }

  for(int i=0;i<taille_tranche;++i){
    for(int j=0;j<n;++j){
      tranche_calcule[i] += matrice[i*n+j]*x[j];
    }
  }

  if(rank==0){
    std::vector<int> resultats(n,0);
    for(int i=0;i<taille_tranche;i++){
        resultats[i]=tranche_calcule[i];
    }

    for (int i=1;i<nproc;i++){
      charge_3(i,n,nproc,&iBeg,&iEnd);
      iree=MPI_Recv(&resultats[iBeg],iEnd-iBeg+1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    }

    printf("je suis le proc 0 et voila les resultats finals pour l'instant %d:\n", l);
    for(i=0;i<n;++i){
      printf(" %d",  resultats[i]);
    }
    printf("\n");
    x=resultats;

  }else{
    iree=MPI_Send(&tranche_calcule[0],taille_tranche,MPI_INT,0,0,MPI_COMM_WORLD);
    printf("je suis le proc %d et voila mes resultats:\n", rank);
    for(i=0;i<taille_tranche;++i){
      printf(" %d",  tranche_calcule[i]);
    }
    printf("\n");
  }
}





  MPI_Finalize();

  return 0;
}
