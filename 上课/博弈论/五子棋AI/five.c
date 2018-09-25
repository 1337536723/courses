#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define WIN 1
#define MAN 1
#define AI 2
#define NOT 0
#define ROW 15 
#define COL 15
int map[ROW][COL];//�����±�Ϊ0or15����߽�
void showmap();
void sbai(int* ,int* );
void move(int,int*,int*);
void manvsai();
int  model(int,int ,int );
int win(int ,int );
int money(int ,int );
void hxai(int*,int*);
void scan(int *row);
void scan(int *row,int*col)
{
int n=0;
int m=0;
n= scanf("%d",row);
m= scanf("%d",col);
while (!n&&!m)
{
  scanf("%*[^\n]");
  scanf("%*c");
  printf("����0~14��������Ϊ����------����������:");
  n = scanf("%d",row);
  m= scanf("%d",col);
}
	scanf("%*[^\n]");
	scanf("%*c");

}

void manvsai()
{	
	int row,col;
	int res;
	printf("�������˻���ս\n");
	printf("===============\n");
	showmap();
	while(1)
	{
		printf("����������(�����ڵ�һ�еĵڶ�������,���룺1 2��:\n");	
		scan(&row,&col);	
		while(map[row][col]!=NOT||row<0||row>14||col<0||col>14)
		{
			printf("����0~14��������Ϊ���꣬�Ҳ������ظ�������,������������������:\n");
			scan(&row,&col);
		}
		map[row][col]=MAN;//��������
		res=win(row,col);
		if(res==WIN){ 
		showmap();
		printf("you win!\n");
		break;
					}//�ж���Ӯ
		hxai(&row,&col);
		map[row][col]=AI;
		res=win(row,col);
		if(res==WIN)
		{
		showmap();
		printf("computer win!\n");
		break;
		}
		showmap();
	}
}
void showmap()
{
		int i,j;
		char a[ROW][COL][4];//������
		for(i=0;i<ROW;i++)
		{
		for(j=0;j<COL;j++)
		{
			if(map[i][j]==MAN){strcpy(a[i][j],"��\0");}//��������
			if(map[i][j]==AI){strcpy(a[i][j],"��\0");}//����AI
			if(map[i][j]==NOT){strcpy(a[i][j],"  \0");}//�ո����û������
		} 
		}
			printf("	| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12| 13| 14|\n");
			printf("	_____________________________________________________________\n");
			for(i=0,j=0;i<ROW;i++,j++)
			
			{
				printf("%d	| %s| %s| %s| %s| %s| %s| %s| %s| %s| %s| %s| %s| %s| %s| %s|\n",
				j,a[i][0],a[i][1],a[i][2],a[i][3],a[i][4],a[i][5],a[i][6],
				a[i][7],a[i][8],a[i][9],a[i][10],a[i][11],a[i][12],a[i][13],a[i][14]
						);
				printf("	-------------------------------------------------------------\n");
			}	
}
void move(int n,int* row,int* col)
{
	if(0==n){*row=*row-1;}//��,˳ʱ����ת
	if(1==n){*row=*row-1;*col=*col+1;}
	if(2==n){*col=*col+1;}	
	if(3==n){*row=*row+1;*col=*col+1;}	
	if(4==n){*row=*row+1;}	
	if(5==n){*row=*row+1;*col=*col-1;}	
	if(6==n){*col=*col-1;}	
	if(7==n){*row=*row-1;*col=*col-1;}	
}
int win(int row,int col)
{
	int n=0;
	int i=row,j=col;
	int count=1;//�����������崦��������һ�š�
	int body = map[row][col];//�µ���һ����˭�ģ�
	if(body==NOT)return 0;//����˵�û����,ֱ���˳�
	while(n<8)
	{
		count=1;
		i=row;j=col;
		while(row>=0&&row<=14&&col>=0&&col<=14)//n�����Ǳ߽�
		{
			move(n,&i,&j);
			if(map[i][j]==body)
			{
				count++;
				if(count==5)return WIN;//�������ﵽ5�ţ�����win
			}//�����һ�����Լ�����,����
			else break;//����ǿջ�ط����˳����ѭ��
		}
			n++;//�������ж�
	}
	return 0;
}
int model(int n,int row,int col)
{
	int body;
			move(n,&row,&col);//����n������ ��һ����ʲô
	      if(row==-1||row==15||col==-1||col==15) return 2;//�����һ���Ǳ߽�Ļ���ֱ�ӷ���2
			body=map[row][col];
			if(body==AI) //������Լ����ӣ���ôĿǰ_���
			{
				move(n,&row,&col);//�ٿ�����һ��
				if(row==-1||row==15||col==-1||col==15) return 105;//_��|��_��һ��
				body=map[row][col];//��˭��
				if(body==MAN)//���������Ļ��Ǳ߽���ôn�����Ͼ�������_��� ����105
						return 105;
				if(body==NOT)return 101;//����ǿգ��Ǿ�������_��_ ����101
				if(body==AI)//������Լ���
				{	
						move(n,&row,&col);//�ٿ�����һ��
						if(row==-1||row==15||col==-1||col==15) return 106;//_����|
				body=map[row][col];//��˭��
						if(body==MAN)return 106;//�����������ӣ��Ǿ���_����� ����Ϊ106
						if(body==NOT) return 102;//����ǿգ��Ǿ���_����_����102
						if(body==AI)//������Լ���
						{
							move(n,&row,&col);//�ٿ�����һ��	
							if(row==-1||row==15||col==-1||col==15) return 107;//_������|
							body=map[row][col];
							if(body==MAN) return 107; //������˵ġ��Ǿ���_�������_����Ϊ107	
							if(body==NOT) return 103;//�Ǿ���_������_������Ϊ103
							if(body==AI)//�ٿ�������
							{
								move(n,&row,&col);
								if(row==-1||row==15||col==-1||col==15) return 108;//_��������|
								body=map[row][col];
								if(body==MAN) return 108;//������ˣ��Ǿ���_��������ڣ�����Ϊ108
								if(body==NOT) return 104;//_��������_
								if(body==AI)  return WIN;//���ڽ�����
							}
						}

				}
			}
			if(body==MAN) //������������,�Ǿ���_�ڡ���
			{
				move(n,&row,&col);//�ٿ�����һ����ʲô
				if(row==-1||row==15||col==-1||col==15) return 205;//_��|
				body=map[row][col];
				if(body==AI) return 205;//������Լ��ģ��Ǿ���_������ͺ�Ϊ205
				if(body==NOT) return 201;//���ͺ�Ϊ201 _��_
				if(body==MAN) //�ټ�����
				{
					move(n,&row,&col);
					if(row==-1||row==15||col==-1||col==15) return 206;//_�ڿ�|
					body=map[row][col];
					if(body==AI) return 206;//������Լ��ģ��Ǿ���_�ڿ�����ͺţ�206
					if(body==NOT) return 202;//_�ڿ�_�����ͺ� 202
					if(body==MAN)//������= =
					{
						move(n,&row,&col);
						if(row==-1||row==15||col==-1||col==15) return 207;//_�ڿڿ�|
						body=map[row][col];
						if(body==AI) return 207;//_�ڿڿ���,���ͺ�207
						if(body==NOT) return 203;//_�ڿڿ�_�����ͺ�203
						if(body==MAN) //����...
						{
							move(n,&row,&col);
							if(row==-1||row==15||col==-1||col==15) return 208;//_�ڿڿڿ�|
							body=map[row][col];
							if(body==AI) return 208;//_�ڿڿڿ��� 208
							if(body==NOT) return 204;//_�ڿڿڿ�_ 204
							if(body==MAN) return WIN;
						}
					}
				}
		
			}
			if(body==NOT)	//����ǿ���
			{
				move(n,&row,&col);
				if(row==-1||row==15||col==-1||col==15) return 0;//__|
				body=map[row][col];
				if(body==NOT) return 0;//���ÿ���ʲô�����ˣ�û������
				if(body==MAN)
				{
					 move(n,&row,&col);//�ٿ�����һ����ʲô
					 if(row==-1||row==15||col==-1||col==15) return 215;//__��|
	             body=map[row][col];
	             if(body==AI) return 215;//��__������ͺ�Ϊ215
	             if(body==NOT) return 211;//���ͺ�Ϊ211 __��_
	             if(body==MAN) //�ټ�����
	             {
	                move(n,&row,&col);
						 if(row==-1||row==15||col==-1||col==15) return 216;//__�ڿ�|
	                body=map[row][col];
	                if(body==AI) return 216;//��__�ڿ�����ͺţ�216
	                if(body==NOT) return 212;//__�ڿ�_�����ͺ� 212
	                if(body==MAN)//������= =
	                {
	                   move(n,&row,&col);
							 if(row==-1||row==15||col==-1||col==15) return 217;//__�ڿڿ�|
	                   body=map[row][col];
	                   if(body==AI) return 217;//__�ڿڿ���,���ͺ�217
	                   if(body==NOT) return 213;//__�ڿڿ�_�����ͺ�213
	                   if(body==MAN) //����...
	                   {
	                      move(n,&row,&col);
								 if(row==-1||row==15||col==-1||col==15) return 228;//__�ڿڿڿ�|
	                      body=map[row][col];
	                      if(body==AI) return 228;//__�ڿڿڿ��� 218
	                      if(body==NOT) return 214;//__�ڿڿڿ�_ 214
	                      if(body==MAN) return WIN;
	                   }
	                }
	             }

				}
				if(body==AI)
				{
					move(n,&row,&col);//�ٿ�����һ��
					 if(row==-1||row==15||col==-1||col==15) return 115;//__��|
	             body=map[row][col];//��˭��
	             if(body==MAN) return 115;//��ôn�����Ͼ�������__���
	             if(body==NOT)return 111;//����__��_ 
	             if(body==AI)//������Լ���
	             {
	                   move(n,&row,&col);//�ٿ�����һ��
							 if(row==-1||row==15||col==-1||col==15) return 116;//__����|
	                   body=map[row][col];
	                   if(body==MAN)return 116;//��__����� 
	                   if(body==NOT) return 112;//��__����_
	                   if(body==AI)//������Լ���
	                   {
	                      move(n,&row,&col);//�ٿ�����һ�� 
								 if(row==-1||row==15||col==-1||col==15) return 117;//__������|
	                      body=map[row][col];
	                      if(body==MAN) return 117; //__�������_
	                      if(body==NOT) return 113;//__������_
	                      if(body==AI)//�ٿ���
	                      {
	                         move(n,&row,&col);
									 if(row==-1||row==15||col==-1||col==15) return 118;//_��������|
	                         body=map[row][col];
	                         if(body==MAN) return 118;//__���������
	                         if(body==NOT) return 114;//__��������_
	                         if(body==AI)  return WIN;//���ڽ�����
	                      }
	                   }
	 
	            }

				}
				
			}
		return 0;
}
 
void sbai(int* row,int* col)
{
	srand(time(0));
	*row=rand()%15;
	*col=rand()%15;
	while(map[*row][*col]!=NOT)
	{
		*row=rand()%15;
		*col=rand()%15;
	}
	
}
int money(int row,int col)
{
	int bai,shi,ge;//���ͺŵ�3λ��
	int value[2][3][8]={100,3000,6000,100000,10,20,3000,100000,10,2500,0,0,10,25,2500,0,0,0,0,0,0,0,0,0,
	                	20,250,4000,24999,10,20,2000,24999,15,15,0,0,10,20,1999,0,0,0,0,0,0,0,0,0};
	//{101,102,103,100000,105,106,107,108,111,112,113,0,115,116,117,0,121,122,123,124,125,126,127,128,201,202 ,203,204,205,206,207,208,211,212,213,214,215,216,217,218,221,222,223,224,225,226,227,228}
	int n,fn;//��0��ʼ������4�����򣬷���4������
	int z;//������
	int f;//������
	int sum=0;//ͳ�Ʒ�����������һ�������ϵ�������ֵ
	for(n=0,fn=4;n<4;n++,fn++)
	{
		z=model(n,row,col);//���������������
		f=model(fn,row,col);//����������
		//�෴�������ӵĵ�һ�����
		if((z/10==10)&&(f/10==10)&&(z%10<=4)&&(f%10<=4))//�������������101~104֮�������,
		{
			//�ϲ���һ�����������
			bai=1;//bai=0�����λ��1
			shi=0;//shi=0����ʮλ��0
			if((z%10+f%10)>4) ge=4;//�����λ����������4�ˣ��Ǿ͵���4
			else ge=z%10+f%10 ;//���û����4��ֱ�����
			sum+=value[bai-1][shi][ge-1];//�ϲ��ͼ����ֵ
		}
		//�෴�������ӵĵڶ������
		else if((z/10==20)&&(f/10==20)&&(z%10<=4)&&(f%10<=4))//201~204֮��
		{
				bai=2;//bai=0�����λ��1
	          shi=0;//shi=0����ʮλ��0
	          if((z%10+f%10)>4) ge=4;//�����λ����������4�ˣ��Ǿ͵���4
	          else ge=z%10+f%10 ;//���û����4��ֱ�����
	          sum+=value[bai-1][shi][ge-1];//�ϲ��ͼ����ֵ

		}
		//�෴�������ӵĵ��������
		else if((z/10==10)&&(f/10==10)&&(z%10<=4)&&(f%10>4))//����������101~104������������105~108
		{
			//�ϳ�һ�����������
			bai = 1;
			shi = 0;
			if((z%10+f%10)>8)ge=8;
			else ge=z%10+f%10;
			sum+=value[bai-1][shi][ge-1];
		}
		//�෴�������ӵĵ��������
		else if((z/10==10)&&(f/10==10)&&(z%10>4)&&(f%10<=4))//����������105~108������������101~104
		{
			//�ϳ�һ�����������
			bai = 1;
			shi = 0;
			if((z%10+f%10)>8)ge=8;
			else ge=z%10+f%10;
			sum+=value[bai-1][shi][ge-1];
		}
		//�෴�������ӵĵ��������
		else if((z/10==20)&&(f/10==20)&&(z%10<=4)&&(f%10>4))//����������201~204������������205~208
		{
			//�ϳ�һ�����������
			bai = 2;
			shi = 0;
			if((z%10+f%10)>8)ge=8;
			else ge=z%10+f%10;
			sum+=value[bai-1][shi][ge-1];
		}
		else if((z/10==20)&&(f/10==20)&&(z%10>4)&&(f%10<=4))//����������205~208������������201~204
		{
			//�ϳ�һ�����������
			bai = 2;
			shi = 0;
			if((z%10+f%10)>8)ge=8;
			else ge=z%10+f%10;
			sum+=value[bai-1][shi][ge-1];
		}
			//����
		else
			{
				if(z==0||z==2) sum+=0;//�����ͺͱ߽�����
				else
				{
					ge=z%10;
					shi=((z-(ge))/10)%10;
					bai=z/100;
					sum+=value[bai-1][shi][ge-1];
				}
				if(f==2||f==0) sum+=0;
				else
				{
					ge=f%10;
					shi=((f-(ge))/10)%10;
					bai=f/100;
					sum+=value[bai-1][shi][ge-1];
				}
			
	}	
	}
		return sum;
	
}
void hxai(int* row ,int* col)//��������
{
		srand(time(0));
		int i,j;
		int value_max=0;
		int value=0;
		for(i=0;i<15;i++)
		{
			for(j=0;j<15;j++)
			{
				if(map[i][j]==NOT) 
					{
						value = money(i,j);
						if(value>value_max) 
						{	
									*row=i;
									*col=j;
									value_max=value;
						}
					}
					
			}
		}
}

int main()
{
	manvsai();
	return 0;
}