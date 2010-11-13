#include <iostream>
#include <malloc.h>
#include <stdlib.h>
using namespace std;
#define MAXNUM 9999
#define max 20

//…………………………………………邻接矩阵定义……………………
typedef struct
{
  int weight;//弧的权值
}AdjMatrix[20][20];

typedef struct Arcnode //弧结点
{
  int adjvex;//邻接点域adjvex存放与vi相邻接的顶点vj的序号j
  struct Arcnode *next;//将邻接表的所有表结点链在一起。
}Arcnode;

//图的邻接矩阵形式定义
typedef struct
{
  char vexs[20];
  AdjMatrix adjMatrix;
  int vexNum,arcNum;
}MGraph_L;


typedef struct//邻接链表顶点头接点
{
  char vertex;//顶点域vertex存放顶点vi的信息
  Arcnode *firstEdge;//指向第一条依附该结点的弧的指针
}Adjlist;

typedef struct//图的邻接链表形式定义
{
  Adjlist vertices[max];
  int vexNum,arcNum;//顶点数目，弧数目
}Algraph;

int CreatMGraph_L(MGraph_L &G,int* data,int dim)//创建图用邻接矩阵表示
{
  G.vexNum=7;
  G.arcNum=9;
  for(int i=0;i<dim;i++)
  {
    for(int j=0;j<G.vexNum;++j)
    {
      G.adjMatrix[i][j].weight=MAXNUM;
    }

    //_itoa_s( i, &G.vexs[i],8,10);
    snprintf(&G.vexs[i],sizeof(&G.vexs[i]),"%d",i);
    for(int j=0;j<dim;j++)
    {
      if(data[dim*i+j]<MAXNUM)
      {
        G.adjMatrix[i][j].weight=data[dim*i+j];
        G.adjMatrix[j][i].weight=data[dim*i+j];
      }
    }
  }
  return G.vexNum;

}

int Prim(MGraph_L G,int n) //最小生成树PRIM算法
{
  int lowcost[max];//LOWCOST[i]存储i当前集合U分别到剩余结点的最短路径
  int prevex[max]; //prevex[i]存储i的前一个结点

  //prevex[]存储最短路径在U中的结点
  int i,j,k,MIN;

  for(i=1;i<n;i++) //n个顶点，n-1条边
  {
    lowcost[i]=G.adjMatrix[0][i].weight; //初始化
    prevex[i]=0; //顶点未加入到最小生成树中
  }

  lowcost[0]=0; //标志顶点1加入U集合,

  for(i=1;i<n;i++) //形成n-1条边的生成树
  {
    MIN=MAXNUM;
    k=0;

    for(j=1;j<n;j++) //寻找最小边,满足一个顶点在U,另一个顶点在V的
    {
      //lowcost[j]!=0说明顶点j不在U
      if((lowcost[j]<MIN)&&(lowcost[j]!=0))
      {
        MIN=lowcost[j];
        k=j;
      }
    }

    cout<<prevex[k]<<","<<k<<","<<MIN<<endl;
    lowcost[k]=0; //顶点k加入U

    for(j=1;j<n;j++) //修改由顶点k到其他顶点边的权值
    {
      if(lowcost[j]>G.adjMatrix[k][j].weight)
      {
        lowcost[j]=G.adjMatrix[k][j].weight;
        prevex[j]=k;
        //cout<<j<<"->"<<k<<":"<<lowcost[j]<<endl;
      }
    }
  }
  return 0;
}

int main()
{
  Algraph gra;
  MGraph_L G;
  int i,d,g[20][20];
  int data[7][7]={{MAXNUM,28,MAXNUM,MAXNUM,MAXNUM,10,MAXNUM},
    {28,MAXNUM,16,MAXNUM,MAXNUM,MAXNUM,14},
    {MAXNUM,16,MAXNUM,12,MAXNUM,MAXNUM,MAXNUM},
    {MAXNUM,MAXNUM,12,MAXNUM,22,MAXNUM,18},
    {MAXNUM,MAXNUM,MAXNUM,22,MAXNUM,25,24},
    {10,MAXNUM,MAXNUM,MAXNUM,25,MAXNUM,MAXNUM},
    {MAXNUM,14,MAXNUM,18,24,MAXNUM,MAXNUM}};

  d=CreatMGraph_L(G,*data,7);//创建图用邻接矩阵表示

  Prim(G,d);
  return 0;
}

