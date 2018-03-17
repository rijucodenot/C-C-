#include<stdio.h>
#include<stdlib.h>

void my_gets(char *,int *);
void matching(char *,int,char *,int);
int *bad_character(char *,int,int *,int);
int *good_suffix(char *,int);

int main(void)
{
	int n,m;
	char *p=NULL,*text=NULL;
	printf("\nEnter length of text :: "),scanf("%d",&n),
	printf("\nEnter length of pattern :: "),scanf("%d",&m);
	n+=2,m+=2;
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

int *bad_character(char *p,int m,int *alphabet,int k)
{
	int *bad_char=NULL;
	bad_char=(int *)malloc(m*sizeof(int));
	if(bad_char==NULL)
		printf("\nDynamic memory allocation failed\n"),exit(0);
	int j;
	m-=1;
	for(j=0;j<k;j++)
		bad_char[alphabet[j]]=0;
	for(j=1;j<=m;j++)
		bad_char[p[j]-'0']=j;
	return bad_char;
}

int *good_suffix(char *p,int m)
{
	int l,*g=NULL,*v=NULL;
	m-=1;
	g=(int *)malloc((m+1)*sizeof(int)),v=(int *)malloc((m+1)*sizeof(int));
	if(g==NULL || v==NULL)
		printf("\nDynamic memory allocation failed\n"),exit(1);
	for(l=1;l<=m;l++)
		g[l]=2*m-l;
	int j=m,k=m+1;
	while(j>=1)
	{
		v[j]=k;
		while(k<=m && p[j]!=p[k])
		{
			g[k]=g[k]<=m-j?g[k]:m-j;
			k=v[k];
		}
		j-=1,k-=1;
	}
	for(l=1;l<=k;l++)
		g[l]=(g[l]<=(m+k-l))?g[l]:(m+k-l);
	j=v[k];
	while(k<=m)
	{
		while(k<=j)
			g[k]=(g[k]<=(j-k+m))?g[k]:(j-k+m),k+=1;
		j=v[j];
	}
	free(v),v=NULL;
	return g;
}

void matching(char *text,int n,char *p,int m)
{
	int alphabet[]={0,1,2,3},k=4,*b=bad_character(p,m,alphabet,k),*g=good_suffix(p,m);
	m-=1;
	int i=1,j=m,f=1,flag=0,x=0;
	while(i<=n)
	{
		k=i+j;
		j=m;
		while(j>0 && text[k-1]==p[j])
			j-=1,k-=1;
		if(j==0)
		{
			if(!x)
				printf("\n\tMatch Found\n"),x++;
			printf("\nStarting Location - %d\n",k),i=k+1,j=m,flag=1;
		}
		else
			i+=(g[j]>=(j-b[text[k-1]-'0']))?g[j]:(j-b[(text[k-1]-'0')]);
	}
	if(flag==0)
	{
		printf("\n\nNo match found\n\n");
	}
	free(b),free(g),b=g=NULL;
}

void my_gets(char *arr,int *n)
{
	int i=1;
	char c;
	while((c=getchar())!='\n')
	{
		if(i==(*n)-1)
			break;
		arr[i++]=c; 
	}
	arr[i]='\0',*n=i;
}
