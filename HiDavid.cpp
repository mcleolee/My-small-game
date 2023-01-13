#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_Receipts 100  //结构体数组长度
#define Reason_Length 350 //事由字符串长度
#define History_Length 130 //历史记录的长度
static int slot=0;//slot是用来计数输入的个数的
static int hslot=0;//hslot是用来计数历史记录的个数的
static int history[History_Length][MAX_Receipts]={0};
struct Receipts  //收据结构体,便于管理
{
    long money;  // 收据金额,正为收入,负为支出
    char reason[Reason_Length];//适当加长,避免溢出
    int time[3];//时间数组,只包含年月日
    short is_deleted;
	long id;//收据的id,每一张收据都不一样.
};

void flag_to_str(int flag)
{
    switch(flag)
    {
        case 0:
            break; 
        case 1:
            printf("按关键词查找\n");
            break;
        case 2:
            printf("按添加时间范围查找\n");
            break;
        case 3:
            printf("按金额大小范围查找\n");
            break;
        case 4:
            printf("查找所有收据\n");
            break;
        case 5:
            printf("按ID查找\n");
            break;
        default:
            printf("序号错误");
            system("pause");
    }
}

char* ltop2f(long m)
{
	int n;
    char a[100],*pim=a;
    // ltoa(m,a,10);
    n=strlen(a);//输出时在倒数第二位上加上小数点
    if(n>=3)
    a[n]=a[n-1],a[n-1]=a[n-2],a[n-2]='.',a[n+1]='\0';
    else if(n==2)
    a[3]=a[1],a[2]=a[0],a[1]='.',a[0]='0',a[4]='\0';
    else if(n==1)
    a[3]=a[0],a[0]='0',a[1]='.',a[2]='0',a[4]='\0';
    else if(n==0)
    a[0]='0',a[1]='.',a[2]='0',a[3]='0',a[4]='\0';
    return pim;
}

long p2ftol(char* c)
{
    long m=0;
	int j=0,fl=0;
    for(j=0;j<(signed int)strlen(c);j++)//检测是否输入了小数点
    {
        if(c[j]=='.')
            fl=j;
    }
    if(fl!=0)//如果有输入的小数点不在第一位
    {
        j=fl;//赋值回j
        if(c[j+1]!=0&&c[j+2]!=0)//如果有两位小数
        {
            c[j]=c[j+1],c[j+1]=c[j+2],c[j+2]='\0';//转换为长整数,去掉小数点
            m=atol(c);
        }
        else if(c[j+1]!=0&&c[j+2]==0)//如果有一位小数
        {
            c[j]=c[j+1],c[j+1]='0',c[j+2]='\0';//转换为长整数,去掉小数点
            m=atol(c);
        }
    }
    else//如果没有小数点
    {
        j=strlen(c)-1;
        c[j+1]='0',c[j+2]='0',c[j+3]='\0';//转换为长整数
        m=atol(c);
    }
    return m;
}

void print_receipt_1( struct Receipts *receipt )
{
   //打印收据内容
    char *pi=NULL;
    pi=ltop2f(receipt->money);
	printf( "收据金额 : %s\n", pi);
    printf( "收据时间 : %d.%d.%d\n", receipt->time[0],receipt->time[1],receipt->time[2]);
	printf( "收据事由 : %s\n", receipt->reason);
    printf( "收据编号 : %d\n", receipt->id);
    printf( "\n");
}

int print_receipt( struct Receipts *receipt,int flag)
{
   //打印收据内容
    char *pi=NULL;
    if(flag==1)
    {
        printf("收据编号        收据时间        收据金额        收据事由\n");
        return 0;
    }
    else
    {
		printf( "%-16d", receipt->id);
        printf( "%-4d.%-2d.%-2d\t", receipt->time[0],receipt->time[1],receipt->time[2]);
		pi=ltop2f(receipt->money);
		printf( "%-16s", pi);
        printf( "%s\n", receipt->reason);
    }
	return 0;
}

int writeStruct( struct Receipts *receipt, int n, int flag)
{
    FILE *pFile;
    if(flag==1)//当flag值为1时,清空存档
    {
        pFile = fopen("bfcache.dat", "wb+");
        fclose(pFile);
        return 1;
    }
    pFile = fopen("bfcache.dat", "ab+");
    if (pFile == NULL) //当没有获取到有效的指针时,抛出异常,在测试中没有出现这种情况
    {
        printf("error open");
        exit(0);
    }
    fwrite(receipt, n, 1, pFile);//n是结构体的大小
    fclose(pFile);
    printf("ID为%d的收据保存成功\n",receipt->id);//写入成功后,输出相关信息
    return 0;
}


int readStruct( struct Receipts *receipt, int n, int max) //这个函数只调用一次,一次性读取所有信息
{
    FILE *pFile;
    int r=0,i=0;
    printf("信息读取中...\n");
    pFile = fopen("bfcache.dat", "rb");//以二进制只读模式打开存档文件
    if (pFile == NULL) 
    {
        printf("没有找到存档文件");
        return -1;
    }
    while (feof(pFile)==0)//n是结构体的大小
    {
        if(fread(receipt+i, n, 1, pFile)==1)//如果读取到了结构体数据
        {
            printf("ID为%ld的收据读取成功\n",(receipt+i)->id);//打印该结构体ID
        	r++;
			i++;
        }
    }
    fclose(pFile);
    printf("收据存档读取完成\n");
    return r;//返回读取到的结构体对象数量
}

int read_id()
{
    FILE *fp;
    long m=0;
    char buff[100];
    fp = fopen("id.dat", "r");//以只读模式打开id存储文件
    if (fp == NULL) //指针为空说明没有存档文件,一般不会出现这种情况,因为在write_id里已经检测并尝试创建过存档文件.
    {
        printf("没有找到存档文件");
        return 0;
    }
    fgets(buff, 100, (FILE*)fp);
    fclose(fp);
    m=atol(buff);
    printf("自动生成id:%ld\n",++m);//输出自动生成的ID.
    return m;
}

int write_id(long m)
{
    FILE *fp;
	char buff[100];
	fp = fopen("id.dat", "w");
    if (fp == NULL) 
    {
        printf("没有找到存档文件");
        return 1;
    }
    // fprintf(fp,ltoa(m,buff,10));//转换为10进制数
    fclose(fp);
	return 0;
}

int IsLeapYear(int year)//检测是否为闰年
{
    if(((year%4 == 0) && (year%100 != 0)) || (year%400 == 0))
        return 1;
    return 0;
}

int IsLegal(int year,int mon,int day)//检测日期是否合法
{
    if(year < 1980 ||year > 2100 || mon <= 0 || mon > 12 || day <= 0 || day > 31)return 0;

    if(1 == mon || 3 == mon || 5 == mon || 7 == mon || 8 == mon || 10 == mon || 12 == mon){
        return 1;
    }
    if(IsLeapYear(year)){
        if(2 == mon && (28 == day || 30 == day || 31 == day))return 0;
        return 1;
    }
    else {
        if(2 == mon && (29 == day || 30 == day || 31 == day))return 0;
        return 1;
    }
}

int is_legal_m(int *a)//检测日期是否合法
{
    return IsLegal(a[0],a[1],a[2]);
}

int input_receipt_inf( struct Receipts *receipt, int max, int i)
{
    long m=0;
	int j=0,fl=0;
    char n='0',c[20];
    while(1)
    {
        i++;
		system("cls");
        printf("请输入该收据金额,支持输入到小数点后两位,仅保证正确格式能够正确保存,请输入x.xx,x.x,x这三种形式之一的数字\n");
    	scanf("%s",&c); //输入金额
        (receipt+i)->money=p2ftol(c);
        while(1)
        {
            printf("请输入该收据时间,按照年月日的顺序输入,用空格分开\n");
            scanf("%d %d %d",&((receipt+i)->time[0]),&((receipt+i)->time[1]),&((receipt+i)->time[2]));
            if(is_legal_m((receipt+i)->time))
                break;
            else
                printf("时间不合法,请检查后重新输入\n");
        }
    	printf("请输入收据事由\n");
    	scanf("%s",&((receipt+i)->reason)); //输入事由
        (receipt+i)->is_deleted=1;
        (receipt+i)->id=read_id();
        if((receipt+i)->id==-1)
            printf("读取存档文件失败,创建收据失败");
        write_id((receipt+i)->id);
        printf("回到主菜单请按q,继续输入请按其他任意键:");
		getchar();
        n=(char)getchar();//退出功能
        if(n=='q'||i>=max)
            break;
    }
    return i;
}

int find_by_id( struct Receipts *receipt, int max)
{
    long m;
    int i=0;
    system("cls");
    printf("请输入收据编号");
    scanf("%ld",&m);
    for(i;i<max;i++)
    {
        if((receipt+i)->id==m)
		{
            print_receipt_1(receipt+i);
			system("pause");
            return i;
		}
    }
	printf("没有找到相应收据");
	system("pause");
	return -1;
}

int* print_all_receipts( struct Receipts *receipt, int max)//打印所有is_deleted==1的收据
{
    int i=0,j=0;
    static int re[MAX_Receipts];
    system("cls");
	print_receipt(receipt,1);
    for(i;i<max;i++)
    {
        if((receipt+i)->is_deleted==1)//判断是否已被删除
        {
        	print_receipt(receipt+i,0);
            re[j]=i;
			j++;
        }
    }
	if(j!=0)
    {
        re[j]=-1;
		printf("\n查找到了%d条结果\n",j);
        system("pause");
    	return re;
    }
	else
    {
		printf("还没有收据,或收据已经被全部删除");
        system("pause");
        return NULL;
    }
}

void  delete_by_id( struct Receipts *receipt, int max)
{
    long m;
    int i=0,j=0;
    system("cls");
    printf("请输入id");
    scanf("%ld",&m);
	print_receipt(receipt,1);
    for(i;i<max;i++)
    {
        if((receipt+i)->is_deleted==1&&(receipt+i)->id==m)//判断是否已被删除同时判断是否为正在查询的id
        {
        	print_receipt(receipt+i,0);
            (receipt+i)->is_deleted=0;//将is_deleted置为0
            printf("已删除,如果需要恢复请使用id方式恢复.");
			system("pause");
			j=1;
            break;
        }
    }
	if(j==0)
		printf("没有查找到该ID对应的收据");
    system("pause");
}

void recovery_receipt( struct Receipts *receipt, int max)
{
    long m;
    int i=0,flag=0;
    system("cls");
    printf("请输入id");
    scanf("%ld",&m);
	print_receipt(receipt,1);
    for(i;i<max;i++)
    {
        if((receipt+i)->is_deleted==0&&(receipt+i)->id==m)//判断是否已被删除同时判断是否为正在查询的id
        {
        	print_receipt(receipt+i,0);
            printf("确定要执行操作吗?确定请输入1");
            scanf("%d",&flag);
            if(flag==1)
            {
                (receipt+i)->is_deleted=1;//将is_deleted置为1
                printf("已恢复");
            }
            else
                printf("已取消恢复");
            system("pause");
            break;
        }
    }
    printf("未找到收据");
}

int* find_by_word( struct Receipts *receipt, int max)
{
    char m[100],*p;
    int i=0,j=0,k=0,l=0;
    static int re[MAX_Receipts];
    system("cls");
    printf("请选择查找模式:\n1.精确查找(只有包含整个关键词才会被找出)\n2.模糊查找(只要有字符相同就会被找出)");
    scanf("%d",&k);
    if(k==1)
    {
        printf("请输入关键词");
        scanf("%s",&m);
		print_receipt(receipt,1);
        for(i;i<max;i++)//循环查找
        {
            p=strstr((receipt+i)->reason,m);//判断m字符串是否在任何的收据理由中出现过
            if(p!=NULL&&(receipt+i)->is_deleted==1)//判断是否被删除
            {
                print_receipt(receipt+i,0);
                re[j]=i;
                j++;
            }
        }
        if(j!=0)
        {
            re[j]=-1;
            printf("共查找到了%d条结果.\n",j);
            system("pause");
            return re;
        }
        else
        {
            printf("没有找到相应收据");
            system("pause");
            return NULL;
        }
    }
    else if(k==2)
    {
        printf("请输入关键词");
        scanf("%s",&m);
		print_receipt(receipt,1);
        for(i;i<max;i++)//循环查找
        {
            if((receipt+i)->is_deleted!=1)//判断是否被删除
                continue;
            for(l=0;l<(signed int)strlen(m);l++)
            {
                p=strrchr(m,(int)(receipt+i)->reason[l]);//判断m字符串是否在任何的收据理由中出现过
                if(p!=NULL)
                {
                    print_receipt(receipt+i,0);
                    re[j]=i;
                    j++;
                    break;
                }
            }
        }
        if(j!=0)
        {
            re[j]=-1;
            printf("共查找到了%d条结果.\n",j);
            system("pause");
            return re;
        }
        else
        {
            printf("没有找到相应收据");
            system("pause");
            return NULL;
        }
    }
    else
    {
        printf("输入的序号不正确.");
        system("pause");
		return NULL;
    }
} 

void find_by_is_deleted( struct Receipts *receipt, int max)//打印所有is_deleted==0的收据
{
    int i=0,j=0;
    system("cls");
	print_receipt(receipt,1);
    for(i;i<max;i++)
    {
        if((receipt+i)->is_deleted==0)//判断是否已被删除
        {
        	print_receipt(receipt+i,0);
			j++;
        }
    }
	if(j!=0)
		printf("\n这些收据会在程序结束以后被删除\n");
	else
		printf("还没有在这次运行程序时删除过收据,或收据已经恢复");
    system("pause");
}

int* find_by_time_range( struct Receipts *receipt, int max)
{
    int m[3],n[3];
    int i=0,j=0;
    static int re[MAX_Receipts];
    system("cls");
    printf("请输入开始时间,用空格分开");
    scanf("%d %d %d",&m[0],&m[1],&m[2]);
    printf("请输入结束时间,用空格分开 ");
    scanf("%d %d %d",&n[0],&n[1],&n[2]);
	print_receipt(receipt,1);
    for(i;i<max;i++)
    {//判断是否被删除,时间是否在范围中
        if((receipt+i)->is_deleted==1&&(receipt+i)->time[0]>=m[0]&&(receipt+i)->time[0]<=n[0])
        {
            if((receipt+i)->time[0]==m[0])//收据年份与起始年份相等
            {
                if((receipt+i)->time[1]==m[1])//收据月份与起始月份相等
                {
                    if((receipt+i)->time[2]>=m[2])//只需要号数大于等于收据号数
                    {
						print_receipt(receipt+i,0);
            			re[j]=i;
            			j++;
                    }
                }
                else if((receipt+i)->time[1]>=m[1])//收据月份大于起始月份,也可以
                {
                	print_receipt(receipt+i,0);
            		re[j]=i;
            		j++;
                }
            }
            else if((receipt+i)->time[0]==n[0])//收据年份与结束年份相等
            {
                if((receipt+i)->time[1]==n[1])//收据月份与结束月份相等
                {
                    if((receipt+i)->time[2]<=n[2])//只需要号数小于等于收据号数
                	{
                		print_receipt(receipt+i,0);
            			re[j]=i;
            			j++;
                	}
                }
                else if((receipt+i)->time[1]<=n[1])//收据月份小于结束月份,也可以
                {
                	print_receipt(receipt+i,0);
            		re[j]=i;
            		j++;
                }
            }
           	else//收据年份在起止年份之间,也可以
            {
            	print_receipt(receipt+i,0  );
            	re[j]=i;
            	j++;
            }
        }
    }
    if(j!=0)
    {
        re[j]=-1;
        printf("共查找到了%d条结果.\n",j);
        system("pause");
        return re;
    }
    else
    {
        printf("没有找到相应收据");
		system("pause");
		return NULL;
    }
}

int* find_by_money_range( struct Receipts *receipt, int max)
{
    long m,n;
    int i=0,j=0;
    char c[20];
    static int re[MAX_Receipts];
    system("cls");
	printf("注意:金额范围和金额符号有关,查询支出需要在输入时自己加上负号\n");
    printf("请输入金额最大值,支持输入到小数点后两位,仅保证正确格式能够运行成功,请输入x.xx,x.x,x这三种形式之一的数字\n");
    scanf("%s",&c); //输入金额
    m=p2ftol(c);
    printf("请输入金额最小值,支持输入到小数点后两位,仅保证正确格式能够运行成功,请输入x.xx,x.x,x这三种形式之一的数字\n");
    scanf("%s",&c); //输入金额
    n=p2ftol(c);
	print_receipt(receipt,1);
    for(i;i<max;i++)
    {
        if((receipt+i)->is_deleted==1&&(receipt+i)->money>=n&&(receipt+i)->money<=m)//判断是否被删除,金额是否在范围中
		{
            print_receipt(receipt+i,0);
            re[j]=i;
            j++;
		}
    }
    if(j!=0)
    {
        re[j]=-1;
        printf("共查找到了%d条结果.\n",j);
        system("pause");
        return re;
    }
    else
    {
        printf("没有找到相应收据");
		system("pause");
		return NULL;
    }
}

void find_receipt_menu(struct Receipts *receipt, int max)
{
    int n,*a=NULL,i=1,flag=0;
    system("cls");
    printf("查找收据菜单\n0.回到主菜单\n1.按关键词查找\n2.按添加时间范围查找\n3.按金额大小范围查找\n4.查找这次启动程序时被删除的收据\n请输入对应序号使用功能\n");
    getchar();//用来接收回车符,避免输入的数字被吞.
    n=getchar();
    switch(n)
    {
        case 48:
            break; 
        case 49:
            a=find_by_word(receipt,MAX_Receipts);
            flag=1;
            break;
        case 50:
            a=find_by_time_range(receipt,MAX_Receipts);
            flag=2;
            break;
        case 51:
            a=find_by_money_range(receipt,MAX_Receipts);
            flag=3;
            break;
        case 52:
            find_by_is_deleted(receipt,MAX_Receipts);
            break;
        default:
            printf("请输入正确的序号");
            system("pause");
    }
    if(a!=NULL)
    {
        while(a[i-1]>=0)
        {
            history[hslot][i]=a[i-1];
            i++;
        }
        history[hslot][0]=flag;//用来标识历史记录来源于哪个功能
        history[hslot][i]=-1;//-1作为数组的结尾标志
        hslot++;
    }
    if(hslot>History_Length)
    {
        printf("\n警告:历史记录长度已超出限制\n");
        system("pause");
    }
}

void look_receipt_menu(struct Receipts *receipt, int max)
{
    int n,*a=NULL,i=1,m=-1;
    system("cls");
    printf("查看收据菜单\n0.回到主菜单\n1.查看对应id收据\n2.查看所有收据\n3.按要求查找收据\n请输入对应序号使用功能\n");
    getchar();//用来接收回车符,避免输入的数字被吞.
    n=getchar();
    switch(n)
    {
        case 48:
            break; 
        case 49:
            m=find_by_id(receipt,MAX_Receipts);
            break;
        case 50:
            a=print_all_receipts(receipt,MAX_Receipts);
            break;
        case 51:
            find_receipt_menu(receipt,MAX_Receipts);
            break;
        default:
            printf("请输入正确的序号");
            system("pause");
    }
    if(a!=NULL)
    {
        while(a[i-1]>=0)
        {
            history[hslot][i]=a[i-1];
            i++;
        }
        history[hslot][0]=4;//用来标识历史记录来源于哪个功能
        history[hslot][i]=-1;//-1作为数组的结尾标志
        hslot++;
    }
    if(m!=-1)
    {
        history[hslot][2]=-1;//-1作为数组的结尾标志
        history[hslot][1]=m;
        history[hslot][0]=5;//用来标识历史记录来源于哪个功能
        hslot++;
    }
    if(hslot>History_Length)
    {
        printf("\n警告:历史记录长度已超出限制\n");
        system("pause");
    }
}

void delete_receipt_menu(struct Receipts *receipt, int max)
{
    int n;
    system("cls");
    printf("删除收据菜单\n0.回到主菜单\n1.删除对应序号收据\n2.恢复被删除的收据(仅在未关闭程序前有效,需要id,请使用查找收据菜单的功能4查找id)\n3.查找收据序号\n请输入对应序号使用功能\n");
    getchar();//用来接收回车符,避免输入的数字被吞.
    n=getchar();
    switch(n)
    {
        case 48:
            break; 
        case 49:
            delete_by_id(receipt,MAX_Receipts);
            break;
        case 50:
            recovery_receipt(receipt,MAX_Receipts);
            break;
        case 51:
            find_receipt_menu(receipt,MAX_Receipts);
            break;
        default:
            printf("请输入正确的序号");
            system("pause");
    }
}

void stat_pay_menu (struct Receipts *receipt, int max)
{
    int i=0,j,sum;
	char* pi=NULL;
	system("cls");
    for(i=0;i<hslot;i++)
    {
		sum=0;
		printf("\n历史记录编号:%d\n记录来源:",i+1);
        flag_to_str(history[i][0]);
        print_receipt(receipt,1);
        for(j=1;history[i][j]!=-1;j++)
        {
            print_receipt(receipt+history[i][j],0);
			sum+=(receipt+history[i][j])->money;
        }
		pi=ltop2f(sum);
		printf("总共的收支和为%s\n",pi);
    }
	system("pause");
}

int main_menu(struct Receipts *receipt, int max)
{
    int n;
    system("cls");
    printf("主菜单\n1.新增收据\n2.查看收据\n3.删除收据\n4.查找收据\n5.统计收支\n0.退出\n请输入对应序号使用功能\n");
    n=getchar();
    switch(n)
    {
        case 48:
            break;
        case 49:
            slot=input_receipt_inf(receipt,MAX_Receipts,slot);
            break;
        case 50:
            look_receipt_menu(receipt,MAX_Receipts);
            break;
        case 51:
            delete_receipt_menu(receipt,MAX_Receipts);
            break;
        case 52:
            find_receipt_menu(receipt,MAX_Receipts);
            break;
        case 53:
            stat_pay_menu(receipt,MAX_Receipts);
            break;    
        default:
            printf("请输入正确的序号");
            system("pause");
    }
	if(n==48)
		return 0;
	else
		return 1;
}

int main()//在主函数内初始化结构体
{
	int i=0,j=0,n=sizeof(struct Receipts);//n是一个结构体占用的内存大小
	struct Receipts receipt[MAX_Receipts];
    //int history[History_Length][MAX_Receipts]={0};//初始化历史记录
    //int (*p_history)[MAX_Receipts]=&history[History_Length];
	for(i=0;i<MAX_Receipts;i++)//读取阶段
	{
		receipt[i].is_deleted=-1;
	}
    slot+=readStruct(&receipt[0],n,MAX_Receipts);
    if(slot==-1)
    {
        write_id(0);
        slot=0;
    }
    system("pause");
    while(1)//主程序执行阶段
	{
		j=main_menu(receipt,MAX_Receipts);
		if(j==0)
			break;
	}
    writeStruct(&receipt[i],n,1);
	for(i=0;i<MAX_Receipts;i++)//存档阶段
	{
        if(receipt[i].is_deleted==1)
        	writeStruct(&receipt[i],n,0);
	}
}
