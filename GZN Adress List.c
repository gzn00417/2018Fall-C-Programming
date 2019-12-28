#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <math.h>

typedef struct Adress_List//存储信息结构体 
{
	char Name[20];//姓名 
	char City[20];//城市 
	char Number[20];//电话号码 
	int Dial_Time;//通话时间 
	int Close_Score;//亲密度 
}AL;

typedef struct LL//链表结构
{
	AL data;
	struct LL *nxt;
}LinkList;

char Name[20];//姓名 
char City[20];//城市 
char Number[20];//电话号码 
int Dial_Time;//通话次数
int Close_Score;//亲密度

int Num;//联系人数量
LinkList *L,*head;//链表

void login();//登陆界面 
void menu();//功能菜单 
void Initail();//链表初始化 
void Insert(LinkList *p);//插入新节点
void Standardize(char str[]);//字母小写化 
void Add();//添加联系人 
void Delete();//删除联系人 
void Edit();// 编辑信息 
void PrintAll();//打印所有联系人至文件或屏幕 
void Dial();//拨打电话并显示通话时长 
void Fuzzy_Match();//模糊查找（分类查找）
void FM_Name();
void FM_City();
void FM_Number();
void Sort_Close();//亲密度排序
void Acquaintance_Possibility();//相识概率

int main()
{
	login();
	Initail();
	Sleep(1000);
	
	int Key_Print,Flag;
	while (1)
	{
		system("cls");
		menu();
		printf("请选择功能：");
		Flag=scanf("%d",&Key_Print);
		getchar();
		if (Flag)
		switch(Key_Print)
	 	{
			case 0://退出
				printf("欢迎使用！期待下次光临！");
				exit(0);
				return 0;
			case 1://添加
				Add();
				break;
			case 2://打印
				PrintAll();
				break;
			case 3://删除
				Delete();
				break; 
			case 4://编辑
				Edit();
				break; 
			case 5://拨打电话
				Dial();
				break; 
			case 6://模糊查找
				Fuzzy_Match();
				break;
			case 7://亲密度查询
				Sort_Close();
				break;
            case 8://相识概率
            	Acquaintance_Possibility();
				break;
			default:
				break;
		}
		else printf("输入错误！\n");
		system("pause");
	}
	return 0;
}

void login()//登陆界面  
{ 
    while (1)
	{
 	    system("color b1");
		printf("\n");
    	printf("```````````````````````````````````````````````````````````````````````````");  
    	printf("\n");  
    	printf("\n");  
    	printf("\n");  
    	printf("   ***********************  欢迎登陆电子通讯录 *************************  \n");  
    	printf("\n");
		printf("\n");
    	printf("                           ---Created By GZN---                            \n");
    	printf("\n");
    	printf("\n");
    	printf("```````````````````````````````````````````````````````````````````````````");
		printf("\n");
		
		char LOG[20],PW[20];
		char log[3]={'g','z','n'},pw[3]={'1','2','3'};//自定义用户密码
		printf("                              LoginName:");
		scanf("%s",LOG);
		printf("                              Password:");
		scanf("%s",PW);
		if (strcmp(LOG,log)==0&&strcmp(PW,pw)==0)
		{
			printf("登陆成功！欢迎使用！\n");
			return;
		}
		else
		{
			printf("\n");
			printf("                          用户名或密码错误，请重新输入！\n");
			
			system("color F0");
			Sleep(200);
			system("color CD");
			Sleep(200);
			system("color A2");
			Sleep(200);//用户输入错误的视觉提示
			
			system("cls");
		}
	}
	return;
}  

void menu()//功能菜单  
{
	//system("cls");
    system("color E1");
    printf("\n");
    printf("     ____________________________________________ \n");
    printf("    |                                            |\n");
    printf("    |                电子通讯录                  |\n");
    printf("    |                                            |\n");
    printf("    |             0、退出系统                    |\n");
    printf("    |             1、增加联系人信息              |\n");
    printf("    |             2、打印联系人信息              |\n");
    printf("    |             3、删除联系人信息              |\n");
    printf("    |             4、修改联系人信息              |\n");
    printf("    |             5、拨打电话                    |\n");
    printf("    |             6、模糊查找                    |\n");
    printf("    |             7、亲密度排行及查询            |\n");
    printf("    |             8、相识概率                    |\n");
    printf("    |                                            |\n");
    printf("    |____________________________________________|\n");
    return;
}

void Initail()//链表初始化
{
	head=(LinkList*)malloc(sizeof(LinkList));
	L=(LinkList*)malloc(sizeof(LinkList));//头节点申请空间
	head->nxt=L;
	L->nxt=NULL;
	return; 
} 

void Insert(LinkList *New)//插入新节点
{
	LinkList *Old=NULL;
	Old=L;
	New->nxt=Old->nxt;
	Old->nxt=New;
	New->data.Dial_Time=0;
    New->data.Close_Score=0;
	return;
}

void Standardize(char str[])//字母小写化
{
	int i,len=strlen(str);
	for (i=0;i<len;i++)
	{
		if (*(str+i)>='A'&&*(str+i)<='Z')
		*(str+i)=*(str+i)-'A'+'a';
	}
	return;
}

void Add()//添加联系人
{
	system("color fa");
    printf("请输入联系人的信息：\n");  
    printf("姓名："); 
    scanf("%s",Name);
    Standardize(Name);
    LinkList *q=L->nxt;
    while(q!=NULL)
    {  
        if(strcmp(q->data.Name,Name)==0)//判断是否存在  
        {
            printf("该生已存在\n");  
            return;
        }
        q=q->nxt;
    }  
    if(q==NULL)  
    {  
        LinkList *p;  
        p=(LinkList*)malloc(sizeof(LinkList));
		p->nxt=NULL; 
		
        strcpy(p->data.Name,Name);  
        
        printf("城市：") ;  
        scanf("%s",City) ;
        Standardize(City);
        strcpy(p->data.City,City);
        
        printf("电话：");  
        scanf("%s",Number);
        Standardize(Number);
        strcpy(p->data.Number,Number);
        
        Insert(p);//插入p节点
        printf("添加联系人成功！\n");
    }
    return;
}

void Delete()//删除联系人
{
	system("color f4");
    if (L->nxt==NULL)
    {  
        printf("通讯录为空,请增加联系人信息\n");  
        return;
    }
	printf("请输入您要删除的联系人的姓名:");
    scanf("%s",Name);
    Standardize(Name);
    LinkList *p,*pre;
    pre=L;
    p=pre->nxt;
    int judge=0;
    while (p!=NULL)
    {
 		if (strcmp(p->data.Name,Name)==0)
    	{
        	judge=1;
			pre->nxt=p->nxt;//前驱结点接入后继结点
			free(p);//释放内存
			printf("删除联系人成功！\n");
			break;
        }
        pre=p;
        p=p->nxt;//逐一推进寻找
    } 
    if (judge==0)
	{
		printf("该联系人不存在，请重新输入！\n");
		return;
	}
    return;
}

void Edit()// 编辑信息
{
	system("color 0A");
	if (L->nxt==NULL)
    {
        printf("通讯录为空,请增加联系人信息\n");  
        return;
    }
    printf("请输入您要编辑的联系人的姓名:");
    scanf("%s",Name);
    Standardize(Name);
    LinkList *ed=L;
    int choice;
	while (ed!=NULL)
	{
		if (strcmp(ed->data.Name,Name)==0)
		{
			do
			{
                printf("请输入您要编辑的联系人的信息\n");
				printf("姓名（1）城市（2）电话（3）修改完成退出（0）:");//多种编辑信息
				scanf("%d",&choice);
				printf("您将修改为:");
				switch(choice)
				{
					case 1:
						scanf("%s",Name);
						Standardize(Name);
						strcpy(ed->data.Name,Name);
						break;
					case 2:
						scanf("%s",City);
						Standardize(City);
						strcpy(ed->data.City,City);
						break;
					case 3:
						scanf("%s",Number);
						Standardize(Number);
						strcpy(ed->data.Number,Number);
						break;
					default:
						return;
				}
				printf("编辑成功！\n");
				choice=0;
				scanf("%d",&choice);
			}while (choice!=0);
			return;
		}
		ed=ed->nxt;
	}
	printf("该联系人不存在，请重新输入\n");
	return;
}

void PrintAll()//打印所有联系人
{
	system("color 0E");
	int choice;
	printf("请选择打印至屏幕（1）或文件（2）：");
	scanf("%d",&choice);
	if (choice!=1&&choice!=2) return;
	if (choice==2) freopen("Adress_List.txt","w",stdout);//打印通讯录至文件
	LinkList *i,*j;
	AL t;
	for (i=L->nxt;i!=NULL;i=i->nxt)//按字典序从小到大排序
	{
		for (j=i->nxt;j!=NULL;j=j->nxt)
		if (i->data.Name>j->data.Name)
		{
			t=i->data;
			i->data=j->data;
			j->data=t;
		}
	}
	LinkList *p=L,*q;
	int k=0;
	while (p->nxt!=NULL)
	{
		q=p->nxt;
		printf("%d:%5s %5s %11s\n",++k,q->data.Name,q->data.City,q->data.Number);
		p=q;
	}
	printf("成功打印联系人至");
	if (choice=='2')
	{
		fclose(stdout);
		printf("文件");
	}
	else printf("屏幕");
	printf("！\n");
	return;
}

void Dial()//拨打电话并显示通话时长
{
	system("color 70");
	if(L->nxt==NULL)
    {
        printf("通讯录为空,请增加联系人信息\n");  
        return;
    }
    
	printf("请输入您要拨叫的用户姓名：");
	scanf("%s",Name);
	Standardize(Name);
	LinkList *p=L;
	while (p!=NULL)
	{
		if (strcmp(p->data.Name,Name)==0) break;
		p=p->nxt;
	}
	if (p==NULL)
	{
		printf("该联系人不存在，请重新查找！\n");
		return;
	}
	
	clock_t start,finish;
	start=clock();//通话开始时间
	printf("正在通话...\n");
	system("pause");
	finish=clock();//通话结束时间
	int duration=(int)(finish-start)/CLOCKS_PER_SEC;//记录时差，单位为秒
	
	printf("通话结束,感谢您的使用\n");
	Sleep(500);
	printf("本次通话持续%d秒\n",duration+2);
	Sleep(500);
	
	p->data.Dial_Time+=duration+2;//累计通话时间
	printf("您和该联系人一共通话%d秒\n",p->data.Dial_Time);
	return;
}

void Fuzzy_Match()//模糊查找（分类查找）
{
	system("color 5E");
	printf("请输入您要匹配的信息类型（姓名：1，城市：2，电话：3）\n");
	int choice;
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			FM_Name();//姓名匹配
			break;
		case 2:
			FM_City();//城市匹配
			break;
		case 3:
			FM_Number();//电话匹配
			break;
	}
	return;
}

void FM_Name()
{
	printf("请输入您要匹配的名字\n");
	scanf("%s",Name);
	Standardize(Name);
	int l1=strlen(Name),l2,i,j,flag,cnt=0;
	LinkList *p=L;
	while (p!=NULL)
	{
		l2=strlen(p->data.Name);
		for (i=0;i<=l2-l1;i++)
		{
			flag=1;
			for (j=0;j<l1;j++)
			{
				if (Name[j]!=p->data.Name[i+j]) flag=0;//对照匹配姓名
			}
			if (flag)
			{
				printf("%d:%5s\n",++cnt,p->data.Name);
				break;
			}
		}
		p=p->nxt;
	}
	if (cnt==0)
	{
		printf("没有存储您想查找的联系人，请重新查找！\n");
		return;
	}
	int choice;
	printf("请选择您想查找的联系人编号：");
	scanf("%d",&choice);
	while (choice>cnt||choice<1)
	{
		printf("输入编号错误，请重新输入！");
		scanf("%d",&choice);
	}
	p=head->nxt;
	cnt=0;
	while (p!=NULL)
	{
		l2=strlen(p->data.Name);
		for (i=0;i<=l2-l1;i++)
		{
			flag=1;
			for (j=0;j<l1;j++)
			{
				if (Name[j]!=p->data.Name[i+j]) flag=0;
			}
			if (flag)
			{
				cnt++;
				if (cnt==choice)//找到用户想查询的联系人
				{
					printf("%5s %5s %15s\n",p->data.Name,p->data.City,p->data.Number);
					return;
				}
			}
		}
		p=p->nxt;
	}
	return;
}

void FM_City()
{
	printf("请输入您要匹配的城市\n");
	scanf("%s",City);
	Standardize(City);
	int l1=strlen(City),l2,i,j,flag,cnt=0;
	LinkList *p=L;
	while (p!=NULL)
	{
		l2=strlen(p->data.City);
		for (i=0;i<=l2-l1;i++)
		{
			flag=1;
			for (j=0;j<l1;j++)
			{
				if (City[j]!=p->data.City[i+j]) flag=0;
			}
			if (flag)
			{
				printf("%d:%5s\n",++cnt,p->data.Name);
				break;
			}
		}
		p=p->nxt;
	}
	if (cnt==0)
	{
		printf("没有存储您想查找的联系人，请重新查找！\n");
		return;
	}
	int choice;
	printf("请选择您想查找的联系人编号：");
	scanf("%d",&choice);
	while (choice>cnt||choice<1)
	{
		printf("输入编号错误，请重新输入！");
		scanf("%d",&choice);
	}
	p=head->nxt;
	cnt=0;
	while (p!=NULL)
	{
		l2=strlen(p->data.City);
		for (i=0;i<=l2-l1;i++)
		{
			flag=1;
			for (j=0;j<l1;j++)
			{
				if (City[j]!=p->data.City[i+j]) flag=0;
			}
			if (flag)
			{
				cnt++;
				if (cnt==choice)
				{
					printf("%5s %5s %15s\n",p->data.Name,p->data.City,p->data.Number);
					return;
				}
			}
		}
		p=p->nxt;
	}
	return;
}

void FM_Number()
{
	printf("请输入您要匹配的电话\n");
	scanf("%s",Number);
	Standardize(Number);
	int l1=strlen(Number),l2,i,j,flag,cnt=0;
	LinkList *p=L;
	while (p!=NULL)
	{
		l2=strlen(p->data.Number);
		for (i=0;i<=l2-l1;i++)
		{
			flag=1;
			for (j=0;j<l1;j++)
			{
				if (Number[j]!=p->data.Number[i+j]) flag=0;
			}
			if (flag)
			{
				printf("%d:%5s\n",++cnt,p->data.Name);
				break;
			}
		}
		p=p->nxt;
	}
	if (cnt==0)
	{
		printf("没有存储您想查找的联系人，请重新查找！\n");
		return;
	}
	int choice;
	printf("请选择您想查找的联系人编号：");
	scanf("%d",&choice);
	while (choice>cnt||choice<1)
	{
		printf("输入编号错误，请重新输入！");
		scanf("%d",&choice);
	}
	p=head->nxt;
	cnt=0;
	while (p!=NULL)
	{
		l2=strlen(p->data.Number);
		for (i=0;i<=l2-l1;i++)
		{
			flag=1;
			for (j=0;j<l1;j++)
			{
				if (Number[j]!=p->data.Number[i+j]) flag=0;
			}
			if (flag)
			{
				cnt++;
				if (cnt==choice)
				{
					printf("%5s %5s %15s\n",p->data.Name,p->data.City,p->data.Number);
					return;
				}
			}
		}
		p=p->nxt;
	}
	return;
}

void Sort_Close()//亲密度排序
{
	system("color CF");
	if(L->nxt==NULL)
    {
        printf("通讯录为空,请增加联系人信息\n");
        return;
    }
	LinkList *i,*j;
	AL t;//信息存储类型
	int Sum_Dial=0,k=0;
	for (i=L->nxt;i!=NULL;i=i->nxt) Sum_Dial+=i->data.Dial_Time;//累计用户总通话时间
	if (Sum_Dial==0)//未通话无法计算亲密度
	{
		printf("您的通话记录为空！\n");
		return;
	}
	for (i=L->nxt;i!=NULL;i=i->nxt)
	i->data.Close_Score=min(99,i->data.Dial_Time*100/Sum_Dial+rand()%20+20);
	for (i=L->nxt;i!=NULL;i=i->nxt)//亲密度排序
	{
		for (j=i->nxt;j!=NULL;j=j->nxt)
		if (i->data.Close_Score<j->data.Close_Score)
		{
			t=i->data;
			i->data=j->data;
			j->data=t;
		}
	}
	for (i=L->nxt;i!=NULL;i=i->nxt)
	printf("Rank%d:%5s  Dial:%4d  Close_Score:%2d%%\n",++k,i->data.Name,i->data.Dial_Time,i->data.Close_Score);
	return;
}

void Acquaintance_Possibility()//相识概率
{
	system("color F0");
	printf("请输入两个联系人姓名，将输出两人相识的概率！\n");
	int poss=rand()%10;
	char n1[20],n2[20];
	LinkList *i,*j;
	printf("请输入第一个联系人姓名:");
	scanf("%s",n1);
	for (i=L->nxt;i!=NULL;i=i->nxt)
	if (strcmp(i->data.Name,n1)==0) break;//寻找目标联系人存储结点
	if (i==NULL)
	{
		printf("该联系人不存在！\n");
		return;
	}
	printf("请输入第二个联系人姓名:");
	scanf("%s",n2);
	if (strcmp(n1,n2)==0)
	{
		printf("两个联系人相同，输入错误！\n");
		return;
	}
	for (j=L->nxt;j!=NULL;j=j->nxt)
	if (strcmp(j->data.Name,n2)==0) break;
	if (j==NULL)
	{
		printf("该联系人不存在！\n");
		return;
	}
	if (strcmp(i->data.City,j->data.City)==0) poss+=20+rand()%50;//概率公式计算相识概率
	printf("两人相识的概率为：%d%%\n",poss);
	return;
}
