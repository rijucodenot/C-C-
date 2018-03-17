#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}node;

typedef struct edge
{
	int u,v;
	struct edge *next;
}edge;

typedef struct list
{
	struct node *right;
}list;

node *makenode(int);
edge *makeedge(int,int);
void insert(list *,int);
void print_list(list *,int);
int *dfs_main(list *,int,edge **);
void dfs(int,list *,edge **,int *,int *,int *,int *,int *,int *,int,int *);
void add_edge(edge **,int,int);

int main()
{
	system("clear");
	list *arr=NULL;
	printf("\nTotal number of vertices - ");
	int n,i,*brr=NULL,flag=0;
	scanf("%d",&n),arr=(list *)malloc(n*sizeof(list));
	edge *e=NULL,*f=NULL;
	node *p=NULL,*q=NULL;
	if(arr==NULL)
	{
		printf("\nDynamic memory allocation failed.\n");
		return 0;
	}
	insert(arr,n),print_list(arr,n),brr=dfs_main(arr,n,&e);
	for(i=0;i<n;i++)
	{
		if(brr[i])
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		printf("\n\nCut vertex ----\n\n\t");
		for(i=0;i<n;i++)
			if(brr[i])
				printf("%2d  ",i+1);
	}
	else
		printf("\n\nThere is no cut vertex\n\n");
	if(e)	
		printf("\n\nCut edge / Bridge -----\n\n\t");
	else
		printf("\n\nThere is no cut edge / bridge\n\n");
	while(e)
	{
		f=e,e=e->next;
		printf("(%2d,%2d)",f->u+1,f->v+1);
		free(f),f=NULL;
		if(e)
			printf(" , ");
	}
	printf("\n\n");
	for(i=0;i<n;i++)
	{
		p=arr[i].right;
		while(p)
			q=p,p=p->next,free(q),q=NULL;
		arr[i].right=NULL;
	}
	free(arr),free(brr),brr=NULL,arr=NULL;
	return 0;
}

void dfs(int v,list *arr,edge **e,int *visited,int *cvertex,int *parent,int *count,int *dnum,int *low,int root,int *rcount)
{
	visited[v]=1,dnum[v]=low[v]=*count,*count=*count+1;
	int w;
	node *p=NULL;
	for(p=arr[v].right;p;p=p->next)
	{
		w=p->data;
		if(visited[w]==0)
		{	//printf("\nw - %d v - %d\n",w+1,v+1);
			parent[w]=v;
			dfs(w,arr,e,visited,cvertex,parent,count,dnum,low,root,rcount);
			if(low[w]>=dnum[v] && v==root && *rcount>1)
				cvertex[v]=1;
			if(low[w]>=dnum[v] && v!=root){
				cvertex[v]=1;//printf("\n\nc- %d\tv - %d \tw - %d\n\n",v+1,v+1,w+1);
				}
			if(low[w]>dnum[v])
				add_edge(e,v,w);
			low[v]=(low[v]<=low[w])?low[v]:low[w];
			if(v==root)
				*rcount+=1;
		}
		else if(w!=parent[v])
			low[v]=(low[v]<=dnum[w])?low[v]:dnum[w];
	}
}

int *dfs_main(list *arr,int n,edge **e)
{
	int i,count=1,rcount=1,*visited=NULL,*cvertex=NULL,*parent=NULL,*dnum=NULL,*low=NULL;
	visited=(int *)malloc(n*sizeof(int)),cvertex=(int *)malloc(n*sizeof(int)),parent=(int *)malloc(n*sizeof(int)),
	dnum=(int *)malloc(n*sizeof(int)),low=(int *)malloc(n*sizeof(int));
	if(visited==NULL || cvertex==NULL || parent==NULL || dnum==NULL)
		printf("\nDynamic memory allocation failed.\n"),exit(2);
	for(i=0;i<n;i++)
		visited[i]=0,cvertex[i]=0,parent[i]=-1;
	for(i=0;i<n;i++)
		if(visited[i]==0)
			rcount=1,dfs(i,arr,e,visited,cvertex,parent,&count,dnum,low,i,&rcount);
	//for(i=0;i<n;i++)
		//printf("\ndfs_num[%d] - %d\tlow[%d] - %d\tparent[%d] - %d",i+1,dnum[i],i+1,low[i],i+1,parent[i]);
	printf("\n\n"),free(visited),free(parent),free(dnum),free(low);
	visited=parent=dnum=low=NULL;
	return cvertex;
}

void print_list(list *arr,int n)
{
	printf("\n\nList representation of given graph is ----\n\n");
	int i;
	node *p=NULL;
	for(i=0;i<n;i++)
	{
		printf("\n[ %2d ] - ",i+1),p=arr[i].right;
		while(p)
		{
			printf(" %d ",p->data+1),p=p->next;
			if(p)
				printf("-> ");
		}
		printf("\n");
	}
	printf("\n\n");
}

void insert(list *arr,int n)
{
	int i,j,k,item;
	node *p=NULL,*q=NULL;
	for(i=0;i<n;i++)
	{
		printf("\nTotal number of adjacent vertex of %d :: ",i+1),scanf("%d",&k),arr[i].right=NULL;
		for(j=0;j<k;j++)
		{
			printf("\nAdj[%d] :: ",j+1),scanf("%d",&item);
			if(p==NULL)
				p=q=makenode(item-1);
			else
				q->next=makenode(item-1),q=q->next;
		}
		arr[i].right=p,p=q=NULL;
	}
}	

node *makenode(int data)
{
	node *temp=NULL;
	temp=(node *)malloc(sizeof(node));
	if(temp==NULL)
		printf("\nDynamic memory allocation failed\n"),exit(0);
	temp->data=data,temp->next=NULL;
	return temp;
}

edge *makeedge(int u,int v)
{
	edge *temp=NULL;
	temp=(edge *)malloc(sizeof(edge));
	if(temp==NULL)
		printf("\nDynamic memory allocation failed.\n"),exit(1);
	temp->u=u,temp->v=v,temp->next=NULL;
	return temp;
}

void add_edge(edge **e,int u,int v)
{
	edge *p=makeedge(u,v);
	if(*e==NULL)
		*e=p;
	else
		p->next=*e,*e=p;
}
