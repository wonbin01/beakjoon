#include <stdio.h>
int direction[4][2]={ {1,0},{-1,0},{0,1},{0,-1} }; //�����¿�
int main(void)
{
    int n,m,k; //n�� ��, m�� ��,k�� �μ� �� �ִ� ���� ��
    scanf("%d %d %d",&n,&m,&k);
    char **cmap=(char **)malloc(n*sizeof(char *));
    int **map=(int **)malloc(n*sizeof(int *));
    int wall[n*m][2]; //���� ��ġ�� �����ϴ� �迭
    int wallcount=0;
    for(int i=0;i<n;i++) //���� �Է¹��� �� ���������͸� ���
    {
        cmap[i]=(char *)malloc(m*sizeof(char));
        map[i]=(int *)malloc(m*sizeof(int));
    }
    for(int i=0;i<n;i++)
    {
        scanf("%s",cmap[i]);
    }
    for(int i=0;i<n;i++) //���� ����� ����
    {
        for(int j=0;j<m;j++)
        {
            map[i][j]=cmap[i][j]-'0';
            if(map[i][j]==1)
            {
                wall[wallcount][0]=i; //���� ��ġ�� ������
                wall[wallcount][1]=j;
                wallcount++;   
            }
        }
    }
    
//k���� ���� ���� �μ�-> bfs���� -> �̵�Ƚ�� �迭�� ���� -> map���󺹱� -> �ٸ� �� �μ��� ����

    //0�� �̵�����, 1�� �̵��Ұ��� k���� ���� �μ� �� ����-> 1,1���� n,m���� �̵�
    int count=1; //�����ϴ� ĭ ����(1,1)
    return 0;
}