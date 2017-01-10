#include<stdlib.h>
#include<malloc.h>
#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>

typedef int DataType;
#define MaxSize 10
#define MaxVertices 10
#define MaxWeight 10000
typedef struct
{
    DataType list[MaxSize];
    int size;
}SeqList;

typedef struct
{
    SeqList vertices;
    int edge[MaxVertices][MaxVertices];
    int numOfEdges;
}AdjMGraph;

typedef struct
{
    int row;
    int col;
    int weight;
}RowColWeight;
AdjMGraph g1;
int a[MaxSize];
RowColWeight rcw[100];

void ListInitiate(SeqList *L)
{
    L->size=0;
}
int ListLength(SeqList L)
{
    return L.size;
}

int ListInsert(SeqList *L,int i,DataType x)
{
    int j;
    if(L->size>=MaxSize)
    {
        printf("顺序表已满无法插入！\n");
        return 0;
    }
    else if(i<0||i>L->size)
    {
        printf("参数i不合法！\n");
        return 0;
    }
    else
    {
        for(j=L->size;j>i;j--)
        {
            L->list[j]=L->list[j-1];
        }
        L->list[i]=x;
        L->size++;
        return 1;
    }
}

int ListDelete(SeqList *L,int i,DataType *x)
{
    int j;
    if(L->size<=0)
    {
        printf("顺序表已空无数据元素可删！\n");
        return 0;
    }
    else if(i<=0||i>L->size-1)
    {
        printf("参数i不合法！\n");
        return 0;
    }
    else
    {
        *x = L->list[i];
        for(j=i+1;j<=L->size-1;j++)
            L->list[j-1]=L->list[j];
        L->size--;
        return 1;
    }
}

int ListGet(SeqList L,int i,DataType *x)
{
    if(i<0||i>L.size-1)
    {
        printf("参数i不合法！\n");
        return 0;
    }
    else
    {
        *x = L.list[i];
        return 1;
    }
}

void GraphInitiate(AdjMGraph *G)
{
    int i,j;
    for(i=0;i<MaxVertices;i++)
    {
        for(j=0;j<MaxVertices;j++)
        {
             if(i==j)
            {
                G->edge[i][j]=MaxWeight;
            }
            else
            {
                G->edge[i][j]=MaxWeight;
            }
        }
    }
    G->numOfEdges=0;
    ListInitiate(&G->vertices);
}

int InsertVertex(AdjMGraph *G,DataType vertex)
{
    if(InsertVertex(G,vertex)<0)
        if(ListInsert(&G->vertices,G->vertices.size,vertex)==0)
        {
            printf("插入顶点时空间已满无法插入！");
            exit(1);
        }
}

void InsertEdge(AdjMGraph *G,int v1, int v2,int weight)
{
    DataType x;
    if(v1!=v2)
    {
        if((ListGet(G->vertices,v1,&x)==0)||(ListGet(G->vertices,v2,&x)==0))
        {
            printf("插入边时参数v1和v2越界出错！\n");
            exit(1);
        }
        G->edge[v1][v2]=weight;
        G->edge[v2][v1]=weight;
        G->numOfEdges++;
    }
}


void DeleteEdge(AdjMGraph *G,int v1,int v2)
{
    G->edge[v1][v2]=MaxWeight;
    G->edge[v2][v1]=MaxWeight;
    G->numOfEdges--;
}

void DeleteVertex(AdjMGraph *G,int v)
{
    int m3,i,j;
    m3=v-1;
    if(m3<0||m3>=G->vertices.size)
    {
        printf("对不起，此链路内没有您想要删除的路由节点\n");
        exit(1);
    }
    else
    {
        for(i=m3;j<G->vertices.size;i++)
            for(j=0,i=m3;j<G->vertices.size;j++)
            {
                G->edge[j][i]=MaxWeight;
            }
        for(i=m3;i<G->vertices.size;i++)
            for(i=m3,j=0;i<G->vertices.size;j++)
                G->edge[i][j]=MaxWeight;

        for(i=m3;i<G->vertices.size;i++)
            G->vertices.list[i]=G->vertices.list[i]-1;
            //////////////////////////////
        G->vertices.size--;
        printf("删除结点成功\n");
    }
}

int GetFirstVex(AdjMGraph G,int v)
{
    int col;
    DataType x;
    v=v-1;
    if(ListGet(G.vertices,v,&x)==0)
    {
        printf("取第一个邻接顶点时参数v越界出错!\n");
        exit(1);
    }
    for(col=0;col<G.vertices.size;col++)
        if(G.edge[v][col]>0&&G.edge[v][col]<MaxWeight)
        return col;
    return -1;
}

int GetNextVex(AdjMGraph G,int v1,int v2)
{
    int col;
    DataType x;
    if((ListGet(G.vertices,v1,&x)==0)||(ListGet(G.vertices,v2,&x)==0))
    {
        printf("取下一邻接顶点时参数v1和v2越界出错！\n");
        exit(1);
    }
    if(G.edge[v1][v2]==0)
    {
        printf("v2不是v1的邻接顶点\n");
        exit(1);
    }
    for(col=v2+1;col<G.vertices.size;col++)
    {
        if(G.edge[v1][col]>0&&G.edge[v1][col]<MaxWeight)
            return col;
    }
    return -1;
}
void GreatGraph(AdjMGraph *G,DataType v[],int n,RowColWeight W[],int e)
{
    int i,j;
    GraphInitiate(G);
    for(i=0;i<n;i++)
    {
        InsertVertex(G,v[i]);
    }
    for(j=0;j<e;j++)
    {
        InsertEdge(G,W[j].row,W[j].col,W[j].weight);
    }
}

void Dijikstra(AdjMGraph *G,int v0,int distance[],int path[])
{
    int n = G->vertices.size;
    int *S=(int *)malloc(sizeof(int)*n);
    int minDis,i,j,u;
    FILE *fp;
    for(i=0;i<n;i++)
    {
        distance[i]=G->edge[v0][i];
        S[i]=0;
        if(i!=v0&&distance[i]<MaxWeight)
            path[i]=v0;
        else path[i]=-1;
    }
    S[v0]=1;
    for(i=1;i<n;i++)
    {
        minDis = MaxWeight;
        for(j=0;j<n;j++)
            if(S[j]==0&&distance[j]<minDis)
            {
                u=j;
                minDis = distance[j];
            }
        if(minDis == MaxWeight)return ;
        S[u] =1;
        for(j=0;j<n;j++)
            if(S[j]==0&&G->edge[u][j]<MaxWeight&&distance[u]+G->edge[u][j]<distance[j])
            {
                distance[j]=distance[u]+G->edge[u][j];
                path[j]=u;
            }
    }
    printf("目的路由  下一跳路由\n");
    fp=fopen("e:\\luyoubiao,txt","w");
    for(i=0;i<n;i++)
    {
        if(i==v0)continue;
        j=i;
        while(path[j]!=v0)
        {
            j=path[j];
            if(j==-1)break;
        }
        printf("%5d%12d\n",i+1,j+1);
        fprintf(fp,"%5d%12d\n",i+1,j+1);
    }
    fclose(fp);
}

void menu()
{
  int p;
  void putList();
  void Deletevertex();
  void Deleteedge();
  void Insertedge();
  printf("        ");
  printf("************************网络路由生成****************************\n");
  printf("************************请选择相应实现功能**********************\n");
  printf("************************1.路由表输出并打印**********************\n");
  printf("************************2.删除节点******************************\n");
  printf("************************3.删除边********************************\n");
  printf("************************4.填加边********************************\n");
  printf("************************5.退出系统******************************\n");
  printf("************************请输入你的选择(1-5)*********************\n");
  scanf("%d",&p);
  if(p<1||p>5)
  {printf("\n\n输入序号不属于菜单，请重新输入\n\n");
  p=6;}
  switch(p)
  {
   case 1:putList();break;
   case 2:Deletevertex();break;
   case 3:Deleteedge();break;
   case 4:Insertedge();break;
   case 5:exit(0);break;
   case 6:menu();
  }
}

void putList()
{
    int i,j;
    int distance[7],path[7];
    printf("请输入你要生成的路由表的起始路由器是第几个路由器v\n");
    scanf("%d",&i);
    i--;
    Dijikstra(&g1,i,distance,path);
    printf("从顶点%d到其他各顶点的最短距离为：\n",a[i]);
    for(j=0;j<g1.vertices.size;j++)
        printf("到顶点%d的最短距离为%d\n",a[j],distance[j]);
    menu();
}
void Deletevertex()
{
   int i;
   printf("请输入你要删除的是第几个顶点v\n");
   scanf("%d",&i);
   DeleteVertex(&g1,i);
   menu();
}

void Deleteedge()
{
    int i,j;
    printf("请输入你要删除的边的两个顶点v1，v2\n");
    scanf("%d%d",&i,&j);
    DeleteEdge(&g1,i-1,j-1);
    menu();
}
void Insertedge()
{
  int i,j,w;
  printf("请输入你要删除的边的两个顶点和其权直v1,v2,w\n");
  scanf("%d%d%d",&i,&j,&w);
  InsertEdge(&g1,i-1,j-1,w);
  menu();
}
int main()
{
    menu();
    AdjMGraph g1;
    int i,j,k;
    FILE*fp;
    int a[MaxSize];
    RowColWeight rcw[100];
    fp=fopen("e:\\tuoputu10.txt","r");
    fscanf(fp,"%d",&j);
    for(k=0;k<j;k++)
    {
        fscanf(fp,"%d",&a[k]);
    }
    fscanf(fp,"%d",&j);
    for(k=0;k<j;k++)
    {
        fscanf(fp,"%d%d%d",&rcw[k].row,&rcw[k].col,&rcw[k].weight);
    }
    fclose(fp);
    GraphInitiate(&g1);
    GreatGraph(&g1,a,i,rcw,j);
   // menu();
  }
