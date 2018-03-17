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

typedef struct memory
{
	int node,previous,parent,lnode;
	struct memory *down,*right,*left;
}memory;

typedef struct head
{
	memory *right;
	struct head *down,*up;
}head;

node *makenode(int);
void insert(list *,int);
void print_list(list *,int);
void bfs(list *,int,int);
memory *makememory(int,int,int,int);
head *makehead(void);
void enqueue(node **,node **,int);
void dequeue(node **,node **);
void print_tree(head **);
void deletion(head **);
void space_calculator(head **);
void print_queue(node **);
int queue_front(node **);
void print_color(int *,int);

int main()
{
	system("clear");
	list *arr=NULL;
	printf("\nTotal number of vertices - ");
	int n,i;
	scanf("%d",&n),arr=(list *)malloc(n*sizeof(list));
	if(arr==NULL)
	{
		printf("\nDynamic memory allocation failed.\n");
		return 0;
	}
	insert(arr,n),printf("\nEnter source vertex :: "),scanf("%d",&i),print_list(arr,n),bfs(arr,n,i-1);
	node *p=NULL,*q=NULL;
	for(i=0;i<n;i++)
	{
		p=arr[i].right;
		while(p)
			q=p,p=p->next,free(q),q=NULL;
		arr[i].right=NULL;
	}
	free(arr),arr=NULL;
	return 0;
}

void print_color(int *visited,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(visited[i]==1)
			printf(" B ");
		else if(visited[i]==0)
			printf(" G ");
		else
			printf(" R ");
	}
}

int queue_front(node **front)
{
	if(*front==NULL)
		printf("\nQueue empty\n"),exit(6);
	return (*front)->data;
}

void print_queue(node **front)
{
	node *p=*front;
	printf("[ ");
	while(p)
	{
		printf("%2d",p->data+1),p=p->next;
		if(p)
			printf(", ");
	}
	printf(" ]\n\n");
}

void space_calculator(head **top)
{
	head *h1=*top;
	for(;h1->down;h1=h1->down);
	memory *p=h1->right,*q=NULL;
	int flag,j;
	for(;p;p=p->right)
		p->parent=p->previous=(p->parent+p->previous+1)*8;
	for(h1=h1->up;h1;h1=h1->up)
	{
		for(p=h1->right;p;p=p->right)
		{
			if(p->left==NULL)
			{
				if(p->down==NULL)
					p->parent=(p->parent+p->previous+1)*8,p->previous=p->parent;
				else
				{
					q=p->down,j=q->parent,flag=0;
					for(;q->right!=NULL && q->right->lnode==p->node;q=q->right,flag=1);
					if(flag==1)
						p->parent=(j+q->parent)/2,p->previous=q->parent;
					else
						p->parent=j,p->previous=q->previous;	
				}
			}
			else
			{
				if(p->down==NULL)
					p->parent=p->previous=(((p->parent+p->previous+1)*8)>=(p->left->previous+8))?((p->parent+p->previous+1)*8):(p->left->previous+8);
				else
				{
					q=p->down,j=q->parent,flag=0;
					for(;q->right!=NULL && q->right->lnode==p->node;q=q->right,flag=1);
					if(flag==1)
						p->parent=(j+q->parent)/2,p->previous=q->parent;
					else
						p->parent=j,p->previous=q->previous;
				}
			}
		}
	}
}

void print_tree(head **top)
{
	head *h1=*top;
	memory *p=NULL;
	space_calculator(top),printf("\n\nBreadth First Tree ----\n\n");
	int i,m;
	while(h1)
	{
		p=h1->right,m=p->parent,i=1;
		while(p)
		{
			for(;i<m;i++)
				printf("  ");
			printf("%2d",p->node+1),i=m+1,p=p->right;
			if(p)
				m=p->parent;
		}
		printf("\n\n"),h1=h1->down;
	}
}

void bfs(list *arr,int n,int source)
{
	int *visited=NULL,*d=NULL,*pa=NULL;
	visited=(int *)malloc(n*sizeof(int)),d=(int *)malloc(n*sizeof(int)),pa=(int *)malloc(n*sizeof(int));
	if(visited==NULL || d==NULL || pa==NULL)
		printf("\nDynamic memory allocation failed.\n"),exit(4);
	int i,parent=0,previous=0,count=0,u,j=1;
	for(i=0;i<n;i++)
		visited[i]=d[i]=pa[i]=0;
	printf("\n\nTable representation - \n\n\t");
	for(i=0;i<n;i++)
		printf(" %d ",i+1);
	printf("  d[v]\t\tp[v]\t\t Q\n=================================================================================================================\n\t");
	for(i=0;i<n;i++)
		printf(" G ");
	printf("\n\n\t"),visited[source]=1,pa[source]=-1,print_color(visited,n),printf("  d[%d] = %d\tp[%d] = %s\t",source+1,d[source],source+1,"Nil");
	node *front=NULL,*rear=NULL,*a=NULL;
	memory *p=makememory(source,0,0,-1),*q=NULL,*s=NULL,*t=NULL;
	head *top=makehead(),*h1=NULL,*h2=NULL;
	h1=top,h1->right=p,enqueue(&front,&rear,source),print_queue(&front);
	while(front!=NULL)
	{
		i=queue_front(&front);
		for(a=arr[i].right;a;a=a->next)
		{
			u=a->data;
			if(visited[u]==0)
			{
				enqueue(&front,&rear,u);
				if(q==NULL)
					q=s=makememory(u,previous,(p->parent>0)?(parent+p->parent):parent,i);
				else
					s->right=makememory(u,previous,(p->parent>0)?(parent+p->parent):parent,i),s->right->left=s,s=s->right;
				t=(count==0)?s:t,count++,previous++,j++,visited[u]=1,pa[u]=i+1,d[u]=d[i]+1;
				printf("\t"),print_color(visited,n),printf("  d[%d] = %d\tp[%d] = %d\t",u+1,d[u],u+1,pa[u]),print_queue(&front);
			}
		}
		dequeue(&front,&rear),visited[i]=2;
		if(count==0)
			parent++;
		p->down=(count==0)?NULL:t,count=0,p=p->right;
		if(!p && q)
			p=q,h2=makehead(),h2->right=q,t=q=s=NULL,h2->up=h1,h1->down=h2,h1=h1->down,parent=previous=0;
		if(j==n)
			printf("\t"),print_color(visited,n),printf("\t\t\t\t"),print_queue(&front);
	}
	printf("\n=================================================================================================================\n");
	free(visited),free(d),free(pa),visited=d=pa=NULL;print_tree(&top),deletion(&top);
}

void enqueue(node **front,node **rear,int data)
{
	node *temp=makenode(data);
	if(*front==NULL && *rear==NULL)
		*front=*rear=temp;
	else
		(*rear)->next=temp,*rear=(*rear)->next;
}

void dequeue(node **front,node **rear)
{
	if(*front==NULL)
	{
		printf("\nQueue empty\n");
		exit(3);
	}
	node *p=*front;
	*front=(*front)->next;
	if(*front==NULL)
		*rear=NULL;
	free(p),p=NULL;
}

head *makehead(void)
{
	head *temp=NULL;
	temp=(head *)malloc(sizeof(head));
	if(temp==NULL)
		printf("\nDynamic memory allocation failed.\n"),exit(2);
	temp->right=NULL,temp->up=temp->down=NULL;
	return temp;
}

memory *makememory(int node,int previous,int parent,int lnode)
{
	memory *temp=NULL;
	temp=(memory *)malloc(sizeof(memory));
	if(temp==NULL)
		printf("\nDynamic memory allocation failed.\n"),exit(1);
	temp->node=node,temp->previous=previous,temp->parent=parent,temp->lnode=lnode,temp->down=temp->right=temp->left=NULL;
	return temp;
}	

void print_list(list *arr,int n)
{
	printf("\n\nList representation of given graph is ----\n\n");
	int i;
	node *p=NULL;
	for(i=0;i<n;i++)
	{
		printf("\n[ %d ] - ",i+1),p=arr[i].right;
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

void deletion(head **top)
{
	head *h1=*top,*h2=NULL;
	memory *p=h1->right,*q=NULL;
	while(h1)
	{
		h2=h1,h1=h1->down,free(h2),h2=NULL;
		while(p)
			q=p,p=p->right,free(q),q=NULL;
	}
	*top=NULL;
}
