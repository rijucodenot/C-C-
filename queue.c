#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}node;

void push(node **,int);
int pop(node **);
node *makenode(int);

void insertion(node **,int);
int deletion(node **,node **,int *);
void print(node **,node **);

void finish(node **);

int main()
{
	node *top1=NULL,*top2=NULL;
	int i,item,flag=1;
	do
	{
		printf("\n\tPress 1 for insertion\n\tPress 2 for deletion\n\tPress 3 for display\n\tPress 4 for exit\n");
		printf("\nChoice - ");
		scanf("%d",&i);
		switch(i)
		{
			case 1:
				printf("\nItem - ");
				scanf("%d",&item);
				insertion(&top1,item);
				print(&top1,&top2);
				break;
			case 2:
				item=deletion(&top1,&top2,&flag);
				if(flag==1)
					printf("\n%d is deleted from queue\n",item);
				print(&top1,&top2);
				break;
			case 3:
				print(&top1,&top2);
				break;
			case 4:
				break;
			default:
				printf("\n\nWrong Choice\n\n");
				break;
		}
	}while(i!=4);
	finish(&top1);
	finish(&top2);
	top1=top2=NULL;
	return 0;
}

node *makenode(int data)
{
	node *temp=NULL;
	temp=(node *)malloc(sizeof(node));
	if(temp==NULL)
	{
		printf("\nDynamic memory allocation failed\n");
		exit(0);
	}
	temp->data=data;
	temp->next=NULL;
	return temp;
}

void push(node **top,int data)
{
	node *temp=makenode(data);
	if(*top==NULL)
		*top=temp;
	else
	{
		temp->next=*top;
		*top=temp;
	}
}

int pop(node **top)
{
	if(*top==NULL)
	{
		printf("\nStack underflow\n");
		exit(1);
	}
	node *p=*top;
	*top=(*top)->next;
	int i=p->data;
	free(p);
	p=NULL;
	return i;
}

void finish(node **top)
{
	node *p=*top,*q=NULL;
	while(p!=NULL)
	{
		q=p;
		p=p->next;
		free(q);
		q=NULL;
	}
	*top=NULL;
}

void insertion(node **top1,int data)
{
	push(top1,data);
}

int deletion(node **top1,node **top2,int *flag)
{
	*flag=1;
	if(*top1==NULL && *top2==NULL)
	{
		printf("\nQueue empty\n");
		*flag=0;
		return (-1);
	}
	else if(*top1!=NULL && *top2==NULL)
	{
		node *p=NULL;
		while((*top1)->next!=NULL)
		{
			p=*top1;
			*top1=(*top1)->next;
			p->next=NULL;
			if(*top2==NULL)
				*top2=p;
			else
			{
				p->next=*top2;
				*top2=p;
			}
		}
		p=*top1;
		int i=p->data;
		free(p);
		p=*top1=NULL;
		return i;
	}
	else if(*top1==NULL && *top2!=NULL)
	{
		node *p=*top2;
		*top2=(*top2)->next;
		int i=p->data;
		free(p);
		p=NULL;
		return i;
	}
	else
	{
		node *p=*top2;
		*top2=(*top2)->next;
		int i=p->data;
		free(p);
		p=NULL;
		return i;
	}
}

void print(node **top1,node **top2)
{
	node *p=NULL,*q=NULL,*s=NULL;
	if(*top1==NULL && *top2==NULL)
	{
		printf("\nQueue empty\n");
		return;
	}
	printf("\nElements of Queue are -----\n\n\t");
	q=*top2;
	while(q!=NULL)
	{
		printf("  %d  ",q->data);
		q=q->next;
	}
	q=*top1;
	if(*top1!=NULL)
	{
		while(q!=NULL)
		{	
			s=q;
			q=q->next;
			s->next=NULL;
			if(p==NULL)
				p=s;
			else
			{
				s->next=p;
				p=s;
			}
		}
		while(p!=NULL)
		{
			printf("  %d  ",p->data);
			s=p;
			p=p->next;
			s->next=NULL;
			if(q==NULL)
				q=s;
			else
			{
				s->next=q;
				q=s;
			}
		}
		*top1=q;
	}
	printf("\n");
}
