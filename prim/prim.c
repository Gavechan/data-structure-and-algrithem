#include <stdio.h>
#include <stdlib.h>
typedef char VertexType;                //顶点类型应由用户定义
typedef int EdgeType;                   //边上的权值类型应由用户定义

#define MAXVEX  100             //最大顶点数，应由用户定义
#define INFINITY    65535               //用65535来代表无穷大
#define DEBUG
//int edge[MAXVEX][MAXVEX]={/*输入的邻接矩阵*/};                      //存储了所有边的集合
int lowcost[MAXVEX]={0};                                         //记录Vnew中每个点到V中邻接点的最短边
int visit[MAXVEX];                                             //标记某点是否加入Vnew
int adjecent[MAXVEX]={0};                                        //记录V中与Vnew最邻近的点

typedef struct
{
    VertexType vexs[MAXVEX];            //顶点表
    EdgeType   arc[MAXVEX][MAXVEX];         //邻接矩阵，可看作边
    int numVertexes, numEdges;      //图中当前的顶点数和边数
}Graph;


//定位
int locates(Graph *g, char ch)
{
    int i = 0;
    for(i = 0; i < g->numVertexes; i++)
    {
        if(g->vexs[i] == ch)
        {
            break;
        }
    }
    if(i >= g->numVertexes)
    {
        return -1;
    }

    return i;
}

//建立一个无向网图的邻接矩阵表示
void CreateGraph(Graph *g)
{
    int i, j, k, w;
    printf("输入顶点数和边数:\n");
    scanf("%d %d", &(g->numVertexes), &(g->numEdges));

//#ifdef DEBUG
//    printf("%d %d\n", g->numVertexes, g->numEdges);
//#endif

    for(i = 0; i < g->numVertexes; i++)
    {
        g->vexs[i] = getchar();
        while(g->vexs[i] == '\n')
        {
            g->vexs[i] = getchar();
        }
    }

//#ifdef DEBUG
//    for(i = 0; i < g->numVertexes; i++)
//    {
//        printf("%d ", g->vexs[i]);
//    }
//    printf("\n");
//#endif


    for(i = 0; i < g->numEdges; i++)
    {
        for(j = 0; j < g->numEdges; j++)
        {
            g->arc[i][j] = INFINITY; //邻接矩阵初始化
        }
    }
    for(k = 0; k < g->numEdges; k++)
    {
        char p, q;
        printf("输入边(vi,vj)上的下标i，下标j和权值:\n");

        p = getchar();
        while(p == '\n')
        {
            p = getchar();
        }
        q = getchar();
        while(q == '\n')
        {
            q = getchar();
        }
        scanf("%d", &w);

        int m = -1;
        int n = -1;
        m = locates(g, p);
        n = locates(g, q);
        if(n == -1 || m == -1)
        {
            fprintf(stderr, "there is no this vertex.\n");
            return;
        }
        //getchar();
        g->arc[m][n] = w;
        g->arc[n][m] = g->arc[m][n];  //因为是无向图，矩阵对称
    }
}

//打印图
void printGraph(Graph g)
{
    int i, j;
    for(i = 0; i < g.numVertexes; i++)
    {
        for(j = 0; j < g.numVertexes; j++)
        {
            printf("%6d  ", g.arc[i][j]);
        }
        printf("\n");
    }
}

void prim(int start,Graph g)
{
    int sumweight=0;
    int i,j,k=0;

    //initialization
    for(i=0; i<g.numVertexes; i++)                                //lowcost数组中就存储了当前起点到其他各点的距离
    {
        lowcost[i]=g.arc[start][i];
        visit[i]=-1;                                         //将所有点至于Vnew之外,V之内，这里只要对应的为-1，就表示在Vnew之外
    }

    visit[start]=0;                                        //将起始点start加入Vnew
    adjecent[start]=start;

    for(i=1; i<g.numVertexes; i++)
    {
        int min = INFINITY;
        int v = -1;
        for(j=0; j<g.numVertexes; j++)                            //找到当前距离已知所有节点最近的点
        {
            if(visit[j]==-1 && lowcost[j] < min)                 //在Vnew之外寻找最短路径
            {
                min=lowcost[j];
                v=j;
            }
        }
        if(v != -1)
        {
            printf("%d--%d : %d\n",adjecent[v],v,lowcost[v]);
            visit[v]=0;                                      //将v加Vnew中
            sumweight += lowcost[v];                             //计算路径长度之和
            for(j=0; j<g.numVertexes; j++)                          //重新遍历所有节点，找未被访问的节点
            {
                if(visit[j] == -1 && g.arc[v][j] < lowcost[j])
                {
                    lowcost[j] = g.arc[v][j];                     //此时v点加入Vnew 需要更新lowcost
                    adjecent[j] = v;
                }
            }
        }
    }
    printf("the minmum weight is %d",sumweight);
}


int main(int argc, char **argv)
{
    Graph g;
    VertexType start_v;
    //邻接矩阵创建图
    CreateGraph(&g);
    printGraph(g);
    printf("Please input start vertext: \n");
    scanf("%d",&start_v);
    prim(start_v,g);
    return 0;
}