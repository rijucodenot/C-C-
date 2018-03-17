#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}node;

typedef struct list
{
	node *right;
}list;

typedef struct edge
{
	int u,v;
	struct edge *next;
}edge;

typedef struct head
{
	int count;
	struct edge *right;
}head;

void insert(list *,int,char);
node *makenode(int);
void take_input(list *,int,list *,int);
void print_list(list *,int,int);
edge *makeedge(int,int);
void perfect_matching(list *,int,list *,int);
head *makehead(void);
void add_edge(edge **,int,int);
void print_matching(head **);
void delete_list(list *,int);
head *initial_matching(list *,int,list *,int,int *,int *,int *);
edge *augmented_path(list *,int,int,int *,int *,int *);
edge *depth_search(list *,int,int *,int,int,int,int,int *,int *);
void iterative_match(list *,int,int,int *,int *,int *,head **);
edge *symmetric_difference(edge **,edge **,int *,int *,int);
void delete_edge(edge **);
void update(int *,int,int *,int *,int,edge **);

int main(void)
{
	int n,m;
	printf("\nNumber of vertices in set - 1 :: "),scanf("%d",&n),
	printf("\nNumber of vertices in set - 2 :: "),scanf("%d",&m);
	list *u=NULL,*v=NULL;
	u=(list *)malloc(sizeof(list)*n),v=(list *)malloc(sizeof(list)*m);
	if(u==NULL || v==NULL)
	{
		printf("\nDynamic memory allocation failed.\n");
		return 0;
	}
	take_input(u,n,v,m),print_list(u,n,1),print_list(v,m,2),perfect_matching(u,n,v,m);
	delete_list(u,n),delete_list(v,m),free(u),free(v),u=v=NULL;//printf("\nu - %p\tv - %p\n",u,v);
	return 0;
}

void iterative_match(list *u,int n,int m,int *a,int *b,int *match,head **h)
{
	int size=(n<=m)?n:m,count;
	edge *e=NULL,*m1=(*h)->right,*m2=NULL,*p=NULL;
	(*h)->right=NULL;
	for(;;)
	{
		e=augmented_path(u,n,m,a,b,match);
		if(e)
		{
			m2=symmetric_difference(&m1,&e,&count,match,m),delete_edge(&m1),
			m1=m2,m2=NULL,update(a,n,b,match,m,&m1);
			if(count==size)
				break;
		}
		if(!e)
			break;
		delete_edge(&e);
	}
	(*h)->right=m1,(*h)->count=count;
}

void update(int *a,int n,int *b,int *match,int m,edge **m1)
{
	int i;
	for(i=0;i<n;a[i]=0,i++);
	for(i=0;i<m;b[i]=0,match[i]=-1,i++);
	edge *e=*m1;
	while(e)
		a[e->u]=b[e->v]=1,match[e->v]=e->u,e=e->next;
}

edge *symmetric_difference(edge **m1,edge **p,int *c,int *match,int m)
{
	int count=0,i,*path=NULL;
	path=(int *)malloc(m*sizeof(int));
	if(path==NULL)
		printf("\nDynamic memory allocation failed.\n"),exit(5);
	edge *e=NULL,*t=NULL;
	for(i=0;i<m;path[i]=-1,i++);
	for(e=*p;e;path[e->v]=e->u,e=e->next);
	for(e=*m1;e;e=e->next)
		if(e->u!=path[e->v])
			add_edge(&t,e->u,e->v),count+=1;
	for(e=*p;e;e=e->next)
		if(e->u!=match[e->v])
			add_edge(&t,e->u,e->v),count+=1;
	*c=count,free(path),path=NULL;
	return t;
}

void perfect_matching(list *u,int n,list *v,int m)
{
	int size=(n<=m)?n:m,*a=NULL,*b=NULL,i,*match=NULL;
	a=(int *)malloc(n*sizeof(int)),b=(int *)malloc(m*sizeof(int)),match=(int *)malloc(m*sizeof(int));
	if(a==NULL || b==NULL || match==NULL)
		printf("\nDynamic memory allocation failed.\n"),exit(2);
	for(i=0;i<n;a[i]=0,i++);
	for(i=0;i<m;b[i]=0,match[i]=-1,i++);
	head *m1=initial_matching(u,n,v,m,a,b,match);
	if(size!=m1->count)
		iterative_match(u,n,m,a,b,match,&m1);
	printf("\n"),print_matching(&m1);
	free(a),free(b),free(match),match=a=b=NULL;
}

edge *depth_search(list *u,int n,int *match,int m,int check,int u1,int v1,int *x,int *y)
{
	edge *e=NULL,*temp=NULL;
	node *t=NULL;
	if(check==2)
	{
		y[v1]=1;
		if(match[v1]!=(-1))
		{
			if(x[match[v1]]==0)
			{
				e=depth_search(u,n,match,m,1,match[v1],v1,x,y);
				if(e==NULL)
					return NULL;
				temp=makeedge(u1,v1),temp->next=e;
				return temp;
			}
			else 
				return NULL;
		}
		else if(match[v1]==(-1))
			return makeedge(u1,v1);
	}
	else if(check==1)
	{
		x[u1]=1,t=u[u1].right;
		while(t)
		{
			if(y[t->data]==0)
			{
				e=depth_search(u,n,match,m,2,u1,t->data,x,y);
				if(e!=NULL)
				{
					temp=makeedge(u1,v1),temp->next=e;
					return temp;
				}
			}
			t=t->next;
		}
		return NULL;
	}
}

edge *augmented_path(list *u,int n,int m,int *a,int *b,int *match)
{
	int i,*x=NULL,*y=NULL,flag=0;
	x=(int *)malloc(n*sizeof(int)),y=(int *)malloc(m*sizeof(int));
	if(x==NULL || y==NULL)
		printf("\nDynamic memory allocaion failed.\n"),exit(4);
	for(i=0;i<n;x[i]=0,i++);
	for(i=0;i<m;y[i]=0,i++);
	node *p=NULL;
	edge *e=NULL;
	for(i=0;i<n;i++)
	{
		if(!a[i])
		{
			x[i]=1,p=u[i].right;
			while(p)
			{
				if(b[p->data])
				{
					e=depth_search(u,n,match,m,2,i,p->data,x,y);
					if(e)
					{
						flag=1;
						break;
					}
				}
				p=p->next;
			}
			if(flag==1)
				break;
		}
	}
	free(x),free(y),x=y=NULL;
	return e;
}

void delete_list(list *arr,int n)
{
	node *p=NULL,*q=NULL;
	int i;
	for(i=0;i<n;i++)
	{
		p=arr[i].right;
		while(p)
			q=p,p=p->next,free(q),q=NULL;
		arr[i].right=NULL;
	}
}

void delete_edge(edge **e)
{
	edge *p=*e,*q=NULL;
	while(p)
		q=p,p=p->next,free(q),q=NULL;
	*e=NULL;
}

void print_matching(head **m)
{
	head *h=*m;
	printf("\n\nSize of perfect matching - %d\n\nMatched edge(s) is / are -\n\n\t",h->count);
	edge *p=h->right,*q=NULL;
	while(p)
	{
		q=p,p=p->next,printf("( u%d , v%d )",q->u+1,q->v+1),free(q),q=NULL;
		if(p)
			printf(" , ");
	}
	free(h),*m=h=NULL,printf("\n\n");
}

head *initial_matching(list *u,int n,list *v,int m,int *a,int *b,int *match)
{
	int *x=NULL,*y=NULL,flag,t,i,count=0;
	list *arr=NULL,*brr=NULL;
	if(n<=m)
		arr=u,brr=v,t=n,flag=1,x=a,y=b;
	else
		arr=v,brr=u,t=m,flag=2,x=b,y=a;
	node *p=NULL;
	edge *e=NULL;
	for(i=0;i<t;i++)
	{
		if(!x[i])
		{
			p=arr[i].right;
			while(p)
			{
				if(!y[p->data])
				{
					if(flag==1)
						add_edge(&e,i,p->data),match[p->data]=i;
					else
						add_edge(&e,p->data,i),match[i]=p->data;
					y[p->data]=1,x[i]=1,count+=1;
					break;
				}
				p=p->next;
			}
		}
	}
	edge *z=e;
	printf("\n\nInitial matching\n\n");
	while(z)
		printf("( u%d , v%d )  ",z->u+1,z->v+1),z=z->next;
	printf("\n\n");
	head *m1=makehead();
	m1->count=count,m1->right=e;
	return m1;
}

void add_edge(edge **e,int u,int v)
{
	edge *t=makeedge(u,v);
	t->next=*e,*e=t;
}

void take_input(list *u,int n,list *v,int m)
{
	printf("\n\nEnter list entry for vertices in set - 1\n\n"),insert(u,n,'u'),
	printf("\n\nEnter list entry for vertices in set - 2\n\n"),insert(v,m,'v');
}

void print_list(list *arr,int n,int set)
{
	printf("\n\nList representation of set - %d\n\n",set);
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

void insert(list *arr,int n,char c)
{
	int i,k,l,item;
	node *p=NULL,*q=NULL;
	for(i=0;i<n;i++)
	{
		printf("\nNumber of adjacent vertices of %c%d :: ",c,(i+1)),scanf("%d",&k),printf("\n"),arr[i].right=NULL;
		for(l=0;l<k;l++)
		{
			printf("Adj[%2d] :: ",(l+1)),scanf("%d",&item),printf("\n");
			if(!p)
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
		printf("\nDynamic memory allocation failed.\n"),exit(0);
	temp->data=data,temp->next=NULL;
	return temp;
}

edge *makeedge(int u,int v)
{
	edge *e=NULL;
	e=(edge *)malloc(sizeof(edge));
	if(e==NULL)
		printf("\nDynamic memory allocation failed.\n"),exit(1);
	e->u=u,e->v=v,e->next=NULL;
	return e;
}

head *makehead(void)
{
	head *temp=NULL;
	temp=(head *)malloc(sizeof(head));
	if(temp==NULL)
		printf("\nDynamic memory allocation failed.\n"),exit(3);
	temp->count=0,temp->right=NULL;
	return temp;
}
