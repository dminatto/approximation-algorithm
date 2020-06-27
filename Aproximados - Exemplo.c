
#include <stdio.h>

int N;
int *ciclo;
int *melhor_ciclo;
int *explorado;
int **g;
int nivel=0;
int min=10000;

int medeciclo(int *t)
{
    int i;
    int l=0;

    for(i=0;i<N-1;i++)
	l=l+g[t[i]][t[i+1]];
    l=l+g[t[N-1]][t[0]];

    return l;
}

void dfs(int v, int nivel)
{
    int i,j,dist;
    explorado[v]=1;
    ciclo[nivel]=v;
    if(nivel==N-1){

	dist=medeciclo(ciclo);
	if(dist<min){
	    min=dist;
	    for(j=0;j<N;j++)
		melhor_ciclo[j]=ciclo[j];
	}
    }
    for(i=0;i<N;i++){
	if(!explorado[i]){
	    dfs(i,nivel+1);
    	    explorado[i]=0;
	}
    }
}

int main()
{
    int i,j;
    FILE *fd;
    char buf[20];

    fd=fopen("./entrada","r");
    do{
	fscanf(fd,"%s",buf);
	if(strcmp(buf,"DIMENSION:")==0)
	    fscanf(fd," %d",&N);
	else if(strcmp(buf,"DIMENSION")==0)
	    fscanf(fd," : %d",&N);
    }while(strcmp(buf,"EDGE_WEIGHT_SECTION")!=0);

    ciclo=(int*)malloc(N*sizeof(int));
    explorado=(int*)malloc(N*sizeof(int));
    melhor_ciclo=(int*)malloc(N*sizeof(int));
    g=(int**)malloc(N*sizeof(int*));
    for(i=0;i<N;i++)
	g[i]=(int*)malloc(N*sizeof(int));

    for(i=0;i<N;i++){
	g[i][i]=0;
	for(j=i+1;j<N;j++){
	    fscanf(fd,"%d",&g[i][j]);
	    g[j][i]=g[i][j];
	}
    }

    for(i=0;i<N;i++)
	explorado[i]=0;

    dfs(0,0);

    for(i=0;i<N;i++)
	printf("%d\n",melhor_ciclo[i]);

    return 0;
}
