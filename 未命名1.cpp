#include <malloc.h> 
#include <stdio.h> 
#include <string.h> 
#include <windows.h>
#define M 3 
#define N 5
int Resource[M];
int Max[N][M];
int Allocation[N][M];
int Need[N][M];
int Available[M];
int Work[M];
int Finish[N]; 
int List[N];    //存放安全序列的下标序列 
 
void initial()   
//创建初始状态：先输入 Resource、Max和 Allocation，再计算出 Need、Available。   
{
    int i,j;
    printf("Resource--输入M种资源的总数量:\n");
    for(i=0;i<M;i++)
    {
        scanf("%d",&Resource[i]);
        Available[i]=Resource[i];
    }
    printf("Max--输入N个进程分别对M种资源的最大需求量:\n");
    for(j=0;j<N;j++)
        for(i=0;i<M;i++)
            scanf("%d",&Max[j][i]);
    printf("Allocation--输入N个进程获得M种资源的数量:\n");
    for(j=0;j<N;j++)
        for(i=0;i<M;i++)
            scanf("%d",&Allocation[j][i]);
    /****************************************/
    for(j=0;j<N;j++)
        for(i=0;i<M;i++)
            Need[j][i]=Max[j][i]-Allocation[j][i];
    for(j=0;j<M;j++)
        for(i=0;i<N;i++)
            Available[j]=Available[j]-Allocation[i][j];
} 
 
void printState()   
//输出当前的状态表|Process     |Max         |Allocation  |Need         |Available   | 
{
    int i;
    printf("状态表:\n|Process     |Max         |Allocation  |Need        |Available   | \n");
    for(i=0;i<N;i++)
    {
        if(i==0)
            printf("|P%-11d|%4d%4d%4d|%4d%4d%4d|%4d%4d%4d|%4d%4d%4d|\n",i,Max[i][0],Max[i][1],Max[i][2],Allocation[i][0],Allocation[i][1],Allocation[i][2],Need[i][0],Need[i][1],Need[i][2],Available[0],Available[1],Available[2]);
        else
            printf("|P%-11d|%4d%4d%4d|%4d%4d%4d|%4d%4d%4d|            |\n",i,Max[i][0],Max[i][1],Max[i][2],Allocation[i][0],Allocation[i][1],Allocation[i][2],Need[i][0],Need[i][1],Need[i][2]);
    }
} 
 
int isfinish()   
//返回同时满足两个条件{①Finish[i]=false;  ②Need[i][j]≤Work[j]}的进程下标 i(修改Finish[i]=true)，否则返回-1。 
{
    int i,j,count;
    for(i=0;i<N;i++)
    {
        for(j=0,count=0;j<M;j++)
            if(Finish[i]==0&&Need[i][j]<=Work[j])
            {
                count++;
            }
        if(count==3)
        {
            for(j=0;j<M;j++)
                Work[j]+=Allocation[i][j];
            Finish[i]=1;
            return i;
        }
    }
    return -1;
} 
 
int issafe()   
//判定当前状态是否为安全状态 （返回 true 或 false），把安全序列的下标放入 List[N]数组。 
{
    int i,a,count=0;
    for(i=0;i<M;i++)
        Work[i]=Available[i];
    for(i=0;i<N;i++)
        Finish[i]=0;
    for(i=0;i<N;i++)
    {
        a=isfinish();
        if(a!=-1)
        {
            List[i]=a;
            count++;
        }
    }
    if(count==5)
        return 1;
    else
        return 0;
} 
 
void printList( )   
//输出安全序列表|Process |Work  |Need   |Allocation  |Work+Alloc   |Finish  | 
{
    int i,j;
    printf("\n安全序列表如下:\n|Process     |Work        |Need        |Allocation  |Work+Alloc  |Finish      |\n");
    for(j=0;j<M;j++)
    {
        Work[j]=Available[j];
    }
    for(i=0;i<N;i++)
    {
        printf("|P%-11d|%4d%4d%4d|%4d%4d%4d|%4d%4d%4d|%4d%4d%4d|true\n",List[i],Work[0],Work[1],Work[2],Need[List[i]][0],Need[List[i]][1],Need[List[i]][2],Allocation[List[i]][0],Allocation[List[i]][1],Allocation[List[i]][2],Work[0]+Allocation[List[i]][0],Work[1]+Allocation[List[i]][1],Work[2]+Allocation[List[i]][2]);
        for(j=0;j<M;j++)
            Work[j]+=Allocation[List[i]][j];
    }
} 
 
void reqresource(int i, int Request[M])   
//表示第 i个进程请求 M类资源 request[M] 
{ 
    int flag,count1,count2; 
    int j; 
    //Step1:  判断条件 Request[j]≤Need[i][j] 
    for(j=0,count1=0;j<M;j++)
        if(Request[j]<=Need[i][j])
            count1++;
    //Step2:  判断条件 Request[j]≤Available[j]
    for(j=0,count2=0;j<M;j++)
        if(Request[j]<=Available[j])
            count2++;
    if(count2!=3)
        printf("\n尚无足够的资源，第%d个进程堵塞。\n",i);  
    //Step3:  预先分配 
    if(count2==3&&count1==3)
    {
        for(j=0;j<M;j++)
        {
            Available[j]=Available[j]-Request[j];
            Allocation[i][j]=Allocation[i][j]+Request[j];
            Need[i][j]=Need[i][j]-Request[j];
        }
        if(issafe()==0) 
        { 
            printf("\n不存在安全序列，不是安全状态。\n"); 
            for(j=0;j<M;j++)
            {
                Available[j]=Available[j]+Request[j];
                Allocation[i][j]=Allocation[i][j]-Request[j];
                Need[i][j]=Need[i][j]+Request[j];
            }
        } 
        else 
        { 
            printf("\n是安全序列分配成功!\n"); 
            printList();
        }   
    }
    //Step4:检测是否为安全状态 
    //填补程序 
} 
int main() 
{   
    int reqid=-1,j,req[M]; 
    initial(); 
    printState(); 
    if(issafe()==0) 
    { 
        printf("Initial state is unsafe!\n"); 
    } 
    else 
    { 
        printf("\nInitial state is safe!\n"); 
        printList(); 
        printf("Input the id of request process:"); 
        scanf("%d",&reqid); 
        while(reqid>=0 && reqid<N)   //输入进程 id是否合法 
        { 
            printf("Input request resources:");  
            for(j=0;j<M;j++) 
            { 
                scanf("%d",&req[j]); 
            } 
            reqresource(reqid, req); 
            printState(); 
            printf("Input the id of request process:"); 
            scanf("%d",&reqid); 
        } 
    } 
}
