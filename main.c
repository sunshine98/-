#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#define LEN sizeof(struct user)
typedef struct user
{
    char name[10];//存储用户姓名
    char floor[20];//存储用户楼层
    float monthv[12];//12月分别的用水量
    float monthfee[12];//每个月相应的水费
    float yearv;//年度用水总体积
    float yearfee;//年度用水总费用
    struct user*next;
} data;
int n=0;//计算链表数量

data*creat(void)//链表构建函数，返回链表的head1*/
{
    data*head;
    data*p1,*p2;
    int fubenn=0;//fubenn解决因为全局变量n增加带来的影响
    int i;//控制循环
    head=NULL;
    p1=p2=(data*)malloc(LEN);
    printf("请输入用户的姓名与地址（用空格隔开）：\n");
    scanf("%s%s",p1->name,p1->floor);
    printf("请输入12个月的用水量（用空格隔开）：\n");
    for(i=0; i<12; i++)
    {
        scanf("%f",&p1->monthv[i]);
    }
    while(strcmp(p1->name,"end"))
    {
        n++;
        fubenn++;
        if(fubenn==1) head=p1;
        else p2->next=p1;
        p2=p1;
        p1=(data*)malloc(LEN);
        printf("请输入用户的姓名与地址（用空格隔开）：\n");
        scanf("%s%s",p1->name,p1->floor);
        printf("请输入12个月的用水量（用空格隔开）：\n");
        for(i=0; i<12; i++)
        {
            scanf("%f",&p1->monthv[i]);
        }
    }
    p2->next=NULL;
    return head;
};

void year_v(data*head)//计算每位用户年度用水体积
{
    data*p;
    float sum;
    int i;
    p=head;
    while(p!=NULL)
    {
        for(i=0,sum=0; i<12; i++)
        {
            sum=sum+p->monthv[i];
        }
        p->yearv=sum;
        p=p->next;

    }
}

void yearfee(data*head)
{
    data*p;
    int i;
    float sum;
    p=head;
    while(p!=NULL)
    {
        for(i=0; i<12; i++)
        {
            if(p->monthv[i]<=20)
            {
                p->monthfee[i]=1.8*p->monthv[i];
            }
            else if(p->monthv[i]<=50)
            {
                p->monthfee[i]=36+2.3*(p->monthv[i]-20);
            }
            else
            {
                p->monthfee[i]=105+3*(p->monthv[i]-50);
            }
        }
        for(i=0,sum=0; i<12; i++)
        {
            sum=sum+p->monthfee[i];
        }
        p->yearfee=sum;
        p=p->next;
    }
}


void print(data*head)
{
    data*p;
    int i;
    p=head;
    printf("\n*************************数据读取成功！**************************\n");
    printf("\n经查询：数据库中共有%d位用户的数据，其详细情况如下:\n",n);
    putchar('\n');
    printf("姓名\t地址\t年度用水量\t年度费用\n");
    printf("____________________________________________________________\n");
    if(head!=NULL)
    {
        do
        {
            printf("\n%s\t%s\t%-6.2f吨\t%-6.2f元\n",p->name,p->floor,p->yearv,p->yearfee);
            printf("\n该用户12个月详细用水量及相应费用情况如下：\n");
            printf("\n1月\t2月\t3月\t4月\t5月\t6月\t7月\t8月\t9月\t10月\t11月\t12月\n");
            putchar('\n');
            for(i=0; i<12; i++)
            {
                printf("%-6.2f\t",p->monthv[i]);
            }
            printf("\t单位：吨");
            putchar('\n');
            putchar('\n');
            for(i=0; i<12; i++)
            {
                printf("%-6.2f\t",p->monthfee[i]);
            }
            printf("\t单位：元");
            putchar('\n');
            printf("\n------------------------------------------------------------\n");
            putchar('\n');
            p=p->next;
        }
        while(p!=NULL);
    }
}
data* sort(data*head)//排序结构体（由大到小）
{
    data*first=NULL,*tail=NULL,*p,*p_max,*max;
    first=tail=NULL;
    while(head!=NULL)
    {
        for(p=max=head; p->next!=NULL; p=p->next)
        {
            if(p->next->yearv>max->yearv)
            {
                p_max=p;
                max=p->next;
            }
        }
        if(first==NULL)
        {
            first=tail=max;
        }
        else
        {
            tail->next=max;
            tail=max;
        }
        if(max==head) head=head->next;
        else p_max->next=max->next;

    }
    if(first!=NULL)
    {
        tail->next=NULL;
    }
    head=first;
    return head;
}

void writedata(data*head)
{
    FILE *fp;
    FILE*np;
    data*p;
    p=head;
    if((np=fopen("n","wb"))==NULL)
    {
        printf("打开存储n的文件失败\n");
        exit(0);
    }
    if(fwrite(&n,sizeof(int),1,np)!=1)
    {
        printf("n写入磁盘失败\n");
        exit(0);
    }
    fclose(np);
    if((fp=fopen("data","wb"))==NULL)
    {
        printf("\a本地数据文件打开失败！\n");
        fclose(fp);
        exit(0);
    }

    while(p!=NULL)
    {
        if(fwrite(p,LEN,1,fp)!=1)
        {
            printf("\a数据存盘失败！\n");
            fclose(fp);
            exit(0);
        }
        p=p->next;
    }
    fclose(fp);

}

void adddata(data*head)
{
    FILE*fp;
    FILE*np;
    data*p;
    p=head;
    if((np=fopen("n","wb"))==NULL)
    {
        printf("存储n的文件打开失败\n");
        exit(0);
    }
    if(fwrite(&n,sizeof(int),1,np)!=1)
    {
        printf("存储n失败！\n");
        exit(0);
    }
    fclose(np);

    if((fp=fopen("data","ab"))==NULL)
    {
        printf("\a数据文件打开失败\n");
        fclose(fp);
        exit(0);
    }

    while(p!=NULL)
    {
        if(fwrite(p,LEN,1,fp)!=1)
        {
            printf("\a数据追加失败！\n");
            fclose(fp);
            exit(0);
        }
        p=p->next;
    }
    fclose(fp);
}

data*readdata(void)
{


    FILE*fp;
    FILE*np;
    data*head=NULL;
    data*p1,*p2;
    if((np=fopen("n","rb"))==NULL)
    {
        printf("打开存储n的文件失败！\n");
        exit(0);
    }
    if(fread(&n,sizeof(int),1,np)!=1)
    {
        printf("读取n的值失败！\n");
        exit(0);
    }
    fclose(np);
    if((fp=fopen("data","rb+"))==NULL)
    {
        printf("\a文件打开失败！\n");
        exit(0);
    }


    while(!feof(fp))
    {
        if((p1=(data*)malloc(LEN))==NULL)
        {
            printf("申请空间失败！\n");
            exit(0);
        }
        if(fread(p1,LEN,1,fp)!=1)
        {

            free(p1);
            break;
        }
        if(head==NULL) head=p2=p1;
        else
        {
            p2->next=p1;
            p2=p1;
        }


    }
    fclose(fp);
    return head;
}

void quit(void)
{
    system("cls");
    printf("**************************************************\n");
    printf("\n感谢您使用扬俊水务查询计算系统！\n");
    printf("\n由于时间仓促，本系统难免会有错误和不足之处\n");
    printf("\n如果您对本系统有更好的意见，我的电子邮箱为：1172275496@qq.com\n");
    printf("\n祝您生活愉快！\n");
    printf("\n*************************\tGOOD LUCK TO YOU!\t*****************************\n");
    system("pause");

}
void inputwb(void)
{
    data*po;
    po=creat();
    year_v(po);
    yearfee(po);
    writedata(po);
    printf("恭喜您！数据库中所有数据更新完毕！\n");
}
void inputadd(void)
{

    FILE*np;
    if((np=fopen("n","rb"))==NULL)
    {
        printf("n文件打开失败！\n");
        exit(0);
    }
    if(fread(&n,sizeof(int),1,np)!=1)
    {
        printf("n的数值读取失败！\n");
        exit(0);
    }


    data*po;
    po=creat();

    yearfee(po);
    year_v(po);
    adddata(po);
    printf("恭喜您，数据库中已经成功保存您添加的数据！\n");
    putchar('\n');

}
void zhengli(void)
{
    data*po;
    po=readdata();
    po=sort(po);
    printf("\n*******************数据整理成功！**************************\n");
    printf("\n整理后所有数据如下（按照年度用水量从高往低排列)：\n");
    print(po);
}
void mohuscan(void)
{
    int i,m=0,mohun=0;//mohun模糊n用来计算查找到的数据条数
    data*pt;
    char scanname[20];
    printf("请输入您需要查找的关键词：【      】\b\b\b\b\b");
    getchar();
    gets(scanname);
    pt=readdata();
    printf("\n以下为从数据库中搜索到的符合条件的信息：\n");
    printf("姓名\t地址\t年度用水量\t年度费用\n");
    printf("____________________________________________________________\n");
    do
    {
        if(strstr(pt->name,scanname)!=NULL||strstr(pt->floor,scanname)!=NULL)
        {
            mohun++;
            printf("\n%s\t%s\t%-6.2f吨\t%-6.2f元\n",pt->name,pt->floor,pt->yearv,pt->yearfee);
            printf("\n该用户12个月详细用水量及相应费用情况如下：\n");
            printf("\n1月\t2月\t3月\t4月\t5月\t6月\t7月\t8月\t9月\t10月\t11月\t12月\n");
            putchar('\n');
            for(i=0; i<12; i++)
            {
                printf("%-6.2f\t",pt->monthv[i]);
            }
            printf("\t单位：吨");
            putchar('\n');
            putchar('\n');
            for(i=0; i<12; i++)
            {
                printf("%-6.2f\t",pt->monthfee[i]);
            }
            printf("\t单位：元");
            putchar('\n');
            printf("\n------------------------------------------------------------\n");
            putchar('\n');
            m=1;
        }
        pt=pt->next;
    }while(pt!=NULL);
    printf("\n【系统反馈】：数据库中与关键词【%s】匹配的数据共有【%d】条\n",scanname,mohun);
    if(!m)
    {
        printf("\n对不起，数据库中查找不到包含此关键词的信息！\n");
    }
    putchar('\n');
}
void xiaoqusum(void)
{

    data*p;
    float sumv=0;
    float sumfee=0;
    p=readdata();
    do
    {
        sumv=sumv+p->yearv;
        sumfee=sumfee+p->yearfee;
        p=p->next;
    }
    while(p!=NULL);
    printf("----------------------------数据统计完毕！------------------------------------\n");
    printf("该小区共有%d位用户\n小区总用水为：%7.2f吨\n预计小区总费用为：%7.2f元\n",n,sumv,sumfee);
}

int delete(void)
{
    char deletename[20];
    data*head,*p1,*p2;
    head=readdata();
    if(head==NULL)
    {
        printf("对不起，数据库为空！无法进行删除操作！\n");
        return 0;
    }
    p1=head;
    printf("请您输入需要删除的用户姓名：【      】\b\b\b\b");
    getchar();
    gets(deletename);
    while(strcmp(deletename,p1->name)&&p1->next!=NULL)
    {
        p2=p1;
        p1=p1->next;
    }
    if(strcmp(deletename,p1->name)==0)
    {
        if(p1==head) head=p1->next;
        else p2->next=p1->next;
        printf("恭喜您！用户名为：【%s】的用户所有数据已经成功从数据库中删除！\n",deletename);
        n--;
    }
    else
    {
        printf("\n对不起，没有从数据库中找到名为【%s】的用户！\n",deletename);
        putchar('\n');
    }
    writedata(head);
    return 0;


}
void help(void)
{
    system("cls");
    printf("\n感谢您选择使用本程序，以下为详细使用操作说明\n");
    printf("------------------------------------------------------------\n");
    printf("【1】数据更新：清空数据库中所有的数据，并重新添加数据\n");
    printf("【 】系统检测用户名为：“end”时自动结束数据更新！\n");
    printf("【2】添加数据：向数据库中增加新用户的数据\n");
    printf("【3】显示所有数据：将数据库中所有数据按照原始数据输出\n");
    printf("【4】整理数据：将数据库中所有数据按照年度用水体积从大到小全部输出\n");
    printf("【5】模糊查找：输入关键字，模糊查找并输出所有包含关键字的信息\n");
    printf("【6】总体统计：统计该小区所有用户使用水量体积之和以及费用之和\n");
    printf("【7】删除操作：删除数据库中的单个用户数据\n");
    printf("【8】清屏操作：清屏操作\n");
    printf("【9】退出程序：退出程序\n");

}

int main()
{

    int flag=0;
    char mark;
    SetConsoleTitle("扬俊水务查询计算系统");
    printf("\n亲爱的用户，在使用本程序前我们希望您仔细阅读以下声明：\n");
    printf("\n-------------------------------------------------\n");
    printf("\n1.本程序版权归【刘扬俊】所有\n2.本程序只能用于学习交流，严禁用于商业用途\n3.使用本程序需经过【刘扬俊】同意，违者必究！\n");
    printf("\n-------------------------------------------------\n");
    printf("如果您接受以上协议，请按'y'键继续操作\n");
    printf("请输入您的选择：【   】\b\b");
    scanf("%c",&mark);
    if(mark!='y')
    {
        quit();
        return 0;
    }
    system("cls");

    while(flag!=9)
    {
        printf("——————欢迎使用扬俊水务查询计算系统——————\n");
        printf("【1】数据更新\t【2】添加数据\t【3】显示所有数据\n【4】整理数据\t【5】模糊查找\t【6】总体统计\n【7】删除操作\t");
        printf("【8】清屏操作\t【9】退出程序\n");
        printf("\n如需获取使用帮助说明请选择【10】使用帮助\n");
        printf("\n请输入您需要执行的功能前对应的序号：【   】\b\b\b\b");
        scanf("%d",&flag);
        switch(flag)
        {
        case 1:
            inputwb();
            break;
        case 2:
            inputadd();
            break;
        case 3:
            print(readdata());
            break;
        case 4:
            zhengli();
            break;
        case 5:
            mohuscan();
            break;
        case 6:
            xiaoqusum();
            break;
        case 7:
            delete();
            break;
        case 8:
            system("cls");
            break;
        case 10:
            help();
            break;
        default:
            printf("请输入正确的操作！\n");
            break;
        }
    }
    quit();
    return 0;
}

