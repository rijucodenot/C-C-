#include<stdio.h>
#include<stdlib.h>
//#include<ctype.h>

typedef struct node
{
	int pos;
	struct node *next;
}node;

void my_gets(char *,int *);
node *makenode(int);
void add_node(node **,int);
void matching(char *,int,char *,int,int,node **);
void print_matching(node **,char *,int);
void string(char *,int,int);

int main(void)
{
	int n,m,x;
	char *p=NULL,*text=NULL;
	printf("\nEnter length of text :: "),scanf("%d",&n),
	printf("\nEnter length of pattern :: "),scanf("%d",&m);
	n+=1,m+=1;
	p=(char *)malloc(m*sizeof(char)),text=(char *)malloc(n*sizeof(char));
	if(p==NULL || text==NULL)
	{
		printf("\nDynamic memory allocation failed.\n");
		return 0;
	}
	getchar(),printf("\nEnter text - "),my_gets(text,&n);
	/*getchar(),*/printf("\nEnter pattern - "),my_gets(p,&m);
	printf("\nEnter number of allowed errors - "),scanf("%d",&x);
	//printf("\nText - %s\nLength - %d\n",text,n),printf("\nPattern - %s\nLength - %d\n\n",p,m);
	node *e=NULL;
	matching(text,n,p,m,x,&e);
	if(e==NULL)
		printf("\n\n\tThere is non such matching\n\n");
	else
		print_matching(&e,text,m);
	free(p),free(text),p=text=NULL;
	printf("\n");
	return 0;
}

void print_matching(node **e,char *text,int m)
{
	node *p=NULL;
	printf("\n\n____________________Matching______________________\n");
	while(*e)
	{
		p=*e,*e=(*e)->next;
		printf("\nStart Location - %d\t String - ",p->pos+1),string(text,p->pos,m);
		free(p),p=NULL;
	}
}

void string(char *text,int pos,int m)
{
	int i;
	//printf("\nString - %s\n",text);
	for(i=pos;i<pos+m;i++)
		printf("%c",text[i]);
	printf("\n");
}

void matching(char *text,int n,char *p,int m,int error,node **e)
{
	int i,j,k;
	for(i=0;i<n-m+1;i++)
	{
		j=0,k=error;
		while(j<m)// && text[i+j]==p[j] && k>0)
		{
			/*if(text[i+j]==p[j]){}*/
			if(text[i+j]!=p[j])
			{
				if(k>0)
					k--;
				else 
					break;
			}
			j+=1;
		}
		if(j>=m)
			add_node(e,i);
		//i+=j;
	}
}

void add_node(node **e,int pos)
{
	node *temp=makenode(pos);
	temp->next=*e,*e=temp;
}

void my_gets(char *arr,int *n)
{
	int i=0,j=*n;
	//printf("\nLength - %d\n",j-1
	char c;
	while((c=getchar())!='\n')
	{
		if(i==j-1)
			break;
		arr[i++]=c; //toupper(c) or tolower(c)
	}
	arr[i]='\0',*n=i;
}

node *makenode(int pos)
{
	node *temp=NULL;
	temp=(node *)malloc(sizeof(node));
	if(temp==NULL)
		printf("\nDynamic memory allocation failed.\n"),exit(0);
	temp->pos=pos,temp->next=NULL;
	return temp;
}
