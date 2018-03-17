#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void buildheap(int *,int);
void swap(int *,int *);
void heap(int *,int);
void heapify(int *,int,int);
//void print_array(int *,int);
void print_heap(int *,int);
int *memorize(int,int *,int *);
void print(int *,int,int *,int,int);

int main(int argc,char **argv)
{
	system("clear");
	if(argc!=2)
	{
		printf("\n\n\t<./a.out> <Total no. of elements>\n\n");
		return 0;
	}
	int *arr=NULL,i,n=atoi(argv[1]);
	arr=(int *)malloc(n*sizeof(int));
	if(arr==NULL)
	{
		printf("\n\nDynamic memory allocation failed.\n\n");
		return 0;
	}
	printf("\nEnter elements .....\n");
	for(i=0;i<n;i++)
	{
		printf("x[%d] : ",i+1);
		scanf("%d",&arr[i]);
		buildheap(arr,i);
	}
	heap(arr,n-1);
	//print_array(arr,n);
	free(arr);
	arr=NULL;
	return 0;
}

void heapify(int *arr,int i,int n)
{
	int item=arr[i],j=2*i+1;
	while(j<=n)
	{
		if(j<n && arr[j]<arr[j+1])
			j+=1;
		if(arr[j]>item)
			arr[(j-1)/2]=arr[j],j=2*j+1;
		else 
			break;
	}
	arr[(j-1)/2]=item;
}

void heap(int *arr,int n)
{
	swap(&arr[0],&arr[n]);
	int i;
	for(i=n-1;i>0;i--)
	{
		heapify(arr,0,i);
		//printf("\n\n");
		print_heap(arr,i+1);
		//printf("\n\n");
		swap(&arr[0],&arr[i]);
	}
//	printf("\n\n");
	print_heap(arr,1);
	printf("\n\n");
}

void buildheap(int *arr,int i)
{
	int item=arr[i],j=i;
	while(j>0)
	{
		if(arr[(j-1)/2]<item)
		{
			arr[j]=arr[(j-1)/2];
			j=(j-1)/2;
		}
		else 
			break;
	}
	arr[j]=item;
	//printf("\n\n");
	print_heap(arr,i+1);
	//printf("\n\n");
}

void swap(int *x,int *y)
{
	int item=*x;
	*x=*y;
	*y=item;
}

/*void print_array(int *arr,int n)
{
	int i;
	printf("\n\nArray after sorting\n\n");
	for(i=0;i<n;i++)
		printf("  %d  ",arr[i]);
	printf("\n\n");
}*/

void print_heap(int *arr,int n)
{
	int t,h;
	int *a1=memorize(n,&t,&h);
	print(arr,n,a1,t,h);
	free(a1);
	a1=NULL;
}

void print(int *arr,int n,int *a1,int x,int height)
{
	printf("\n\n");
	int i,j,k=0,m,flag=1;
	//printf("\n%d\n",(int)(log10(n)/log10(2)));
	/*for(i=0;i<height;i++)
	{
		j=*/
	if(k>=n)
		return;
	for(i=1;i<a1[k];i++)
		printf("  ");
	//printf("%2d\n",a1[k]);
	printf("%2d\n\n",arr[k++]);
	for(i=1;i<=height;i++)
	{
		//j=(int)pow(2,i)-1;
		m=1;
		for(j=(int)pow(2,i)-1;j<((int)pow(2,i+1)-1);j++)
		{
			if(k>=n)
			{
				flag=0;
				break;
			}
			for(;m<a1[k];m++)
				printf("  ");
			printf("%2d",arr[k++]);
			m=a1[k-1]+1;
		}
		if(flag==0)
			break;
		else
			printf("\n\n");
	}
	printf("\n\n");
}

int *memorize(int n,int *x,int *h)
{//*x=temp,*h=height
	int height=log10(n)/log10(2),temp;
	if(height==0)
		temp=1;
	else if(height==1 || height==2)
		temp=((int)pow(2,height+1))-1;
	else
	{
		temp=((int)pow(2,height))-1;
		if(temp+4<=n)
			temp=n;
		else
			temp=temp+4;
	}
	*x=temp,*h=height;
	int *array=NULL;
	array=(int *)malloc(temp*sizeof(int));
	if(array==NULL)
	{
		printf("\nDynamic memory allocation failed.\n");
		exit(0);
	}
	int i,j,k;
	if(height==0)
	{
		array[0]=4;
	}
	else
	{
		int t=pow(2,height);
		t-=1;
		for(i=t,j=1;i<temp;i++,j++)
			array[i]=j*4;
		k=(array[t]+array[t+1])/2,j=(array[t+2]+array[t+3])/2;
		j=j-k;
		for(i=(int)pow(2,height-1)-1;i<(int)pow(2,height)-1;i++,k+=j)
			array[i]=k;
		for(i=height-1;i>=1;i--)
			for(j=(int)pow(2,i-1)-1;j<(int)pow(2,i)-1;j++)
				array[j]=(array[2*j+1]+array[2*j+2])/2;
	}
	return array;
}
