/*
 * kruskal algrithem
 *
 * remember to determine if there is a cycle when constructing a tree
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
typedef char VertexType;                //��������Ӧ���û�����
typedef int EdgeType;                   //���ϵ�Ȩֵ����Ӧ���û�����

#define MAXVEX  100             //��󶥵�����Ӧ���û�����
#define INFINITY    65535               //��65535�����������
#define DEBUG
//int edge[MAXVEX][MAXVEX]={/*������ڽӾ���*/};                      //�洢�����бߵļ���
int lowcost[MAXVEX]={0};                                         //��¼Vnew��ÿ���㵽V���ڽӵ����̱�
int visit[MAXVEX];                                             //���ĳ���Ƿ����Vnew
int adjecent[MAXVEX]={0};                                        //��¼V����Vnew���ڽ��ĵ�

typedef struct
{
    VertexType vexs[MAXVEX];            //�����
    EdgeType   arc[MAXVEX][MAXVEX];         //�ڽӾ��󣬿ɿ�����
    int numVertexes, numEdges;      //ͼ�е�ǰ�Ķ������ͱ���
}Graph;

typedef struct edge
{
    int u;
    int v;
    int weight;
}Edge;

//��λ
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

//����һ��������ͼ���ڽӾ����ʾ
void CreateGraph(Graph *g)
{
    int i, j, k, w;
    printf("���붥�����ͱ���:\n");
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
            g->arc[i][j] = INFINITY; //�ڽӾ����ʼ��
        }
    }
    for(k = 0; k < g->numEdges; k++)
    {
        char p, q;
        printf("�����(vi,vj)�ϵ��±�i���±�j��Ȩֵ:\n");

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
        g->arc[n][m] = g->arc[m][n];  //��Ϊ������ͼ������Գ�
    }
}

//��ӡͼ
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

//int cmp(const void *a,const void *b)  //used for qsort
//{
//    return(*(int*)a - *(int*)b);
//}
int swap(Edge * e1, Edge * e2)
{
    Edge et;
    et = *e1;
    *e1 = *e2;
    *e2 = et;
}

int isort(Edge e[],int n)
{
    int i,j,t;
    for(j = 0; j < n-1; j++)
    {
        for(i = 0; i<n-1-j; i++)
        {
            if(e[i].weight > e[i+1].weight)
            {
                swap(&e[i],&e[i+1]);
            }
        }
        //printf("%d %d %d \n",e[0].weight,e[1].weight,e[2].weight);
    }
}

void kruskal(Graph g)
{
    //written by me
    Edge edge[g.numEdges];    //save all the edges
    int same_set[g.numVertexes];    //save all the vertexes
    int k = 0;
    for(int i = 0; i < g.numVertexes; i++)
    {
        for(int j = i; j < g.numVertexes; j++)
        {
            if(g.arc[i][j] != INFINITY && g.arc[i][j] > 0 )
            {
                edge[k].u = i;
                edge[k].v = j;
                edge[k].weight = g.arc[i][j];
                k++;
            }
        }
    }
   // printf("%d %d %d",edge[0].weight,edge[1].weight,edge[2].weight);
    isort(edge , g.numEdges);            //�����б߰�weight��С����
    printf("the shortest edge : %d\n",edge[0].weight);
    printf("%d %d %d\n",edge[0].weight,edge[1].weight,edge[2].weight);
    for(int i = 0; i < g.numVertexes; i++)
    {
        same_set[i] = i;
    }

    int j = 0;
    int e_1, e_2;
    while (j < g.numEdges)
    {
        e_1 = same_set[edge[j].u];
        e_2 = same_set[edge[j].v];
        if(e_1 != e_2)
        {
            printf("%d -->  %d, %d\n", edge[j].u, edge[j].v,edge[j].weight);
            //merge two vertexes into one same_set
            for(int i = 0; i < g.numVertexes; i++)
            {
                if (same_set[i] == e_2)
                    same_set[i] = e_1;
            }

        }
        j++;
    }

}

int main(void)
{
    Graph g;
    VertexType start_v;
    CreateGraph(&g);
    printGraph(g);
//    printf("Please input start vertex: \n");
//    scanf("%d", &start_v);
    kruskal(g);
    return 0;
}