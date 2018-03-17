#include<stdio.h>
#include<stdlib.h>

void my_gets(char *,int *);
void matching(char *,int,char *,int);
int *prefix(char *,int);

int main(void)
{
	int n,m;
	char *p=NULL,*text=NULL;
	printf("\nEnter length of text :: "),scanf("%d",&n),
	printf("\nEnter length of pattern :: "),scanf("%d",&m);
	n+=1,m+=1;
	p=(char *)malloc(m*sizeof(char)),text=(char *)malloc(n*sizeof(char));
	if(p==NULL || text==NULL)
	{
		printf("\nDYnamic memory allocation failed.\n");
		return 0;
	}
	getchar(),printf("\nEnter text - "),my_gets(text,&n);
	printf("\nEnter pattern - "),my_gets(p,&m);
	matching(text,n,p,m);
	free(p),free(text),p=text=NULL;
	return 0;
}

int *prefix(char *p,int m)
{
	int *pi=NULL;
	pi=(int *)malloc(m*sizeof(int));
	if(pi==NULL)
		printf("\nDynamic memory allocation failed.\n"),exit(1);
	int i,j=0;
	pi[0]=0;
	for(i=1;i<m;i++)
	{
		while(j>0 && p[j]!=p[i])
			j=pi[j-1];
		if(p[j]==p[i])
			j+=1;
		pi[i]=j;
	}
	return pi;
}

void matching(char *text,int n,char *p1,int m)
{
	int *p=prefix(p1,m),i,k,flag=0,x=0;
	for(i=0,k=0;i<n;i++)
	{
		while(k>0 && p1[k]!=text[i])
			k=p[k-1];
		if(p1[k]==text[i])
			k+=1;
		if(k==m)
		{
			flag=1;
			if(!x)
				printf("\n\n\tMatch found\n"),x++;
			printf("\nStart location - %d\tEnding location - %d\n",i-m+2,i+1);
			k=p[k-1];
		}
	}
	if(flag==0)
		printf("\nNo match found\n");
	free(p),p=NULL;
}

void my_gets(char *arr,int *n)
{
	int i=0;
	char c;
	while((c=getchar())!='\n')
	{
		if(i==(*n)-1)
			break;
		arr[i++]=c; 
	}
	arr[i]='\0',*n=i;
}
