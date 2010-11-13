#include <iostream>
#include <malloc.h>
#include <stdlib.h>
using namespace std;
#define MAXNUM 9999
#define max 20

//���������������������������������ڽӾ����塭��������������
typedef struct
{
  int weight;//����Ȩֵ
}AdjMatrix[20][20];

typedef struct Arcnode //�����
{
  int adjvex;//�ڽӵ���adjvex�����vi���ڽӵĶ���vj�����j
  struct Arcnode *next;//���ڽӱ�����б�������һ��
}Arcnode;

//ͼ���ڽӾ�����ʽ����
typedef struct
{
  char vexs[20];
  AdjMatrix adjMatrix;
  int vexNum,arcNum;
}MGraph_L;


typedef struct//�ڽ�������ͷ�ӵ�
{
  char vertex;//������vertex��Ŷ���vi����Ϣ
  Arcnode *firstEdge;//ָ���һ�������ý��Ļ���ָ��
}Adjlist;

typedef struct//ͼ���ڽ�������ʽ����
{
  Adjlist vertices[max];
  int vexNum,arcNum;//������Ŀ������Ŀ
}Algraph;

int CreatMGraph_L(MGraph_L &G,int* data,int dim)//����ͼ���ڽӾ����ʾ
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

int Prim(MGraph_L G,int n) //��С������PRIM�㷨
{
  int lowcost[max];//LOWCOST[i]�洢i��ǰ����U�ֱ�ʣ��������·��
  int prevex[max]; //prevex[i]�洢i��ǰһ�����

  //prevex[]�洢���·����U�еĽ��
  int i,j,k,MIN;

  for(i=1;i<n;i++) //n�����㣬n-1����
  {
    lowcost[i]=G.adjMatrix[0][i].weight; //��ʼ��
    prevex[i]=0; //����δ���뵽��С��������
  }

  lowcost[0]=0; //��־����1����U����,

  for(i=1;i<n;i++) //�γ�n-1���ߵ�������
  {
    MIN=MAXNUM;
    k=0;

    for(j=1;j<n;j++) //Ѱ����С��,����һ��������U,��һ��������V��
    {
      //lowcost[j]!=0˵������j����U
      if((lowcost[j]<MIN)&&(lowcost[j]!=0))
      {
        MIN=lowcost[j];
        k=j;
      }
    }

    cout<<prevex[k]<<","<<k<<","<<MIN<<endl;
    lowcost[k]=0; //����k����U

    for(j=1;j<n;j++) //�޸��ɶ���k����������ߵ�Ȩֵ
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

  d=CreatMGraph_L(G,*data,7);//����ͼ���ڽӾ����ʾ

  Prim(G,d);
  return 0;
}

