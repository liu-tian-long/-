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
int List[N];    //��Ű�ȫ���е��±����� 
 
void initial()   
//������ʼ״̬�������� Resource��Max�� Allocation���ټ���� Need��Available��   
{
    int i,j;
    printf("Resource--����M����Դ��������:\n");
    for(i=0;i<M;i++)
    {
        scanf("%d",&Resource[i]);
        Available[i]=Resource[i];
    }
    printf("Max--����N�����̷ֱ��M����Դ�����������:\n");
    for(j=0;j<N;j++)
        for(i=0;i<M;i++)
            scanf("%d",&Max[j][i]);
    printf("Allocation--����N�����̻��M����Դ������:\n");
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
//�����ǰ��״̬��|Process     |Max         |Allocation  |Need         |Available   | 
{
    int i;
    printf("״̬��:\n|Process     |Max         |Allocation  |Need        |Available   | \n");
    for(i=0;i<N;i++)
    {
        if(i==0)
            printf("|P%-11d|%4d%4d%4d|%4d%4d%4d|%4d%4d%4d|%4d%4d%4d|\n",i,Max[i][0],Max[i][1],Max[i][2],Allocation[i][0],Allocation[i][1],Allocation[i][2],Need[i][0],Need[i][1],Need[i][2],Available[0],Available[1],Available[2]);
        else
            printf("|P%-11d|%4d%4d%4d|%4d%4d%4d|%4d%4d%4d|            |\n",i,Max[i][0],Max[i][1],Max[i][2],Allocation[i][0],Allocation[i][1],Allocation[i][2],Need[i][0],Need[i][1],Need[i][2]);
    }
} 
 
int isfinish()   
//����ͬʱ������������{��Finish[i]=false;  ��Need[i][j]��Work[j]}�Ľ����±� i(�޸�Finish[i]=true)�����򷵻�-1�� 
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
//�ж���ǰ״̬�Ƿ�Ϊ��ȫ״̬ ������ true �� false�����Ѱ�ȫ���е��±���� List[N]���顣 
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
//�����ȫ���б�|Process |Work  |Need   |Allocation  |Work+Alloc   |Finish  | 
{
    int i,j;
    printf("\n��ȫ���б�����:\n|Process     |Work        |Need        |Allocation  |Work+Alloc  |Finish      |\n");
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
//��ʾ�� i���������� M����Դ request[M] 
{ 
    int flag,count1,count2; 
    int j; 
    //Step1:  �ж����� Request[j]��Need[i][j] 
    for(j=0,count1=0;j<M;j++)
        if(Request[j]<=Need[i][j])
            count1++;
    //Step2:  �ж����� Request[j]��Available[j]
    for(j=0,count2=0;j<M;j++)
        if(Request[j]<=Available[j])
            count2++;
    if(count2!=3)
        printf("\n�����㹻����Դ����%d�����̶�����\n",i);  
    //Step3:  Ԥ�ȷ��� 
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
            printf("\n�����ڰ�ȫ���У����ǰ�ȫ״̬��\n"); 
            for(j=0;j<M;j++)
            {
                Available[j]=Available[j]+Request[j];
                Allocation[i][j]=Allocation[i][j]-Request[j];
                Need[i][j]=Need[i][j]+Request[j];
            }
        } 
        else 
        { 
            printf("\n�ǰ�ȫ���з���ɹ�!\n"); 
            printList();
        }   
    }
    //Step4:����Ƿ�Ϊ��ȫ״̬ 
    //����� 
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
        while(reqid>=0 && reqid<N)   //������� id�Ƿ�Ϸ� 
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
