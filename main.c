#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#define LEN sizeof(struct user)
typedef struct user
{
    char name[10];//�洢�û�����
    char floor[20];//�洢�û�¥��
    float monthv[12];//12�·ֱ����ˮ��
    float monthfee[12];//ÿ������Ӧ��ˮ��
    float yearv;//�����ˮ�����
    float yearfee;//�����ˮ�ܷ���
    struct user*next;
} data;
int n=0;//������������

data*creat(void)//���������������������head1*/
{
    data*head;
    data*p1,*p2;
    int fubenn=0;//fubenn�����Ϊȫ�ֱ���n���Ӵ�����Ӱ��
    int i;//����ѭ��
    head=NULL;
    p1=p2=(data*)malloc(LEN);
    printf("�������û����������ַ���ÿո��������\n");
    scanf("%s%s",p1->name,p1->floor);
    printf("������12���µ���ˮ�����ÿո��������\n");
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
        printf("�������û����������ַ���ÿո��������\n");
        scanf("%s%s",p1->name,p1->floor);
        printf("������12���µ���ˮ�����ÿո��������\n");
        for(i=0; i<12; i++)
        {
            scanf("%f",&p1->monthv[i]);
        }
    }
    p2->next=NULL;
    return head;
};

void year_v(data*head)//����ÿλ�û������ˮ���
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
    printf("\n*************************���ݶ�ȡ�ɹ���**************************\n");
    printf("\n����ѯ�����ݿ��й���%dλ�û������ݣ�����ϸ�������:\n",n);
    putchar('\n');
    printf("����\t��ַ\t�����ˮ��\t��ȷ���\n");
    printf("____________________________________________________________\n");
    if(head!=NULL)
    {
        do
        {
            printf("\n%s\t%s\t%-6.2f��\t%-6.2fԪ\n",p->name,p->floor,p->yearv,p->yearfee);
            printf("\n���û�12������ϸ��ˮ������Ӧ����������£�\n");
            printf("\n1��\t2��\t3��\t4��\t5��\t6��\t7��\t8��\t9��\t10��\t11��\t12��\n");
            putchar('\n');
            for(i=0; i<12; i++)
            {
                printf("%-6.2f\t",p->monthv[i]);
            }
            printf("\t��λ����");
            putchar('\n');
            putchar('\n');
            for(i=0; i<12; i++)
            {
                printf("%-6.2f\t",p->monthfee[i]);
            }
            printf("\t��λ��Ԫ");
            putchar('\n');
            printf("\n------------------------------------------------------------\n");
            putchar('\n');
            p=p->next;
        }
        while(p!=NULL);
    }
}
data* sort(data*head)//����ṹ�壨�ɴ�С��
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
        printf("�򿪴洢n���ļ�ʧ��\n");
        exit(0);
    }
    if(fwrite(&n,sizeof(int),1,np)!=1)
    {
        printf("nд�����ʧ��\n");
        exit(0);
    }
    fclose(np);
    if((fp=fopen("data","wb"))==NULL)
    {
        printf("\a���������ļ���ʧ�ܣ�\n");
        fclose(fp);
        exit(0);
    }

    while(p!=NULL)
    {
        if(fwrite(p,LEN,1,fp)!=1)
        {
            printf("\a���ݴ���ʧ�ܣ�\n");
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
        printf("�洢n���ļ���ʧ��\n");
        exit(0);
    }
    if(fwrite(&n,sizeof(int),1,np)!=1)
    {
        printf("�洢nʧ�ܣ�\n");
        exit(0);
    }
    fclose(np);

    if((fp=fopen("data","ab"))==NULL)
    {
        printf("\a�����ļ���ʧ��\n");
        fclose(fp);
        exit(0);
    }

    while(p!=NULL)
    {
        if(fwrite(p,LEN,1,fp)!=1)
        {
            printf("\a����׷��ʧ�ܣ�\n");
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
        printf("�򿪴洢n���ļ�ʧ�ܣ�\n");
        exit(0);
    }
    if(fread(&n,sizeof(int),1,np)!=1)
    {
        printf("��ȡn��ֵʧ�ܣ�\n");
        exit(0);
    }
    fclose(np);
    if((fp=fopen("data","rb+"))==NULL)
    {
        printf("\a�ļ���ʧ�ܣ�\n");
        exit(0);
    }


    while(!feof(fp))
    {
        if((p1=(data*)malloc(LEN))==NULL)
        {
            printf("����ռ�ʧ�ܣ�\n");
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
    printf("\n��л��ʹ���￡ˮ���ѯ����ϵͳ��\n");
    printf("\n����ʱ��ִ٣���ϵͳ������д���Ͳ���֮��\n");
    printf("\n������Ա�ϵͳ�и��õ�������ҵĵ�������Ϊ��1172275496@qq.com\n");
    printf("\nף��������죡\n");
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
    printf("��ϲ�������ݿ����������ݸ�����ϣ�\n");
}
void inputadd(void)
{

    FILE*np;
    if((np=fopen("n","rb"))==NULL)
    {
        printf("n�ļ���ʧ�ܣ�\n");
        exit(0);
    }
    if(fread(&n,sizeof(int),1,np)!=1)
    {
        printf("n����ֵ��ȡʧ�ܣ�\n");
        exit(0);
    }


    data*po;
    po=creat();

    yearfee(po);
    year_v(po);
    adddata(po);
    printf("��ϲ�������ݿ����Ѿ��ɹ���������ӵ����ݣ�\n");
    putchar('\n');

}
void zhengli(void)
{
    data*po;
    po=readdata();
    po=sort(po);
    printf("\n*******************��������ɹ���**************************\n");
    printf("\n����������������£����������ˮ���Ӹ���������)��\n");
    print(po);
}
void mohuscan(void)
{
    int i,m=0,mohun=0;//mohunģ��n����������ҵ�����������
    data*pt;
    char scanname[20];
    printf("����������Ҫ���ҵĹؼ��ʣ���      ��\b\b\b\b\b");
    getchar();
    gets(scanname);
    pt=readdata();
    printf("\n����Ϊ�����ݿ����������ķ�����������Ϣ��\n");
    printf("����\t��ַ\t�����ˮ��\t��ȷ���\n");
    printf("____________________________________________________________\n");
    do
    {
        if(strstr(pt->name,scanname)!=NULL||strstr(pt->floor,scanname)!=NULL)
        {
            mohun++;
            printf("\n%s\t%s\t%-6.2f��\t%-6.2fԪ\n",pt->name,pt->floor,pt->yearv,pt->yearfee);
            printf("\n���û�12������ϸ��ˮ������Ӧ����������£�\n");
            printf("\n1��\t2��\t3��\t4��\t5��\t6��\t7��\t8��\t9��\t10��\t11��\t12��\n");
            putchar('\n');
            for(i=0; i<12; i++)
            {
                printf("%-6.2f\t",pt->monthv[i]);
            }
            printf("\t��λ����");
            putchar('\n');
            putchar('\n');
            for(i=0; i<12; i++)
            {
                printf("%-6.2f\t",pt->monthfee[i]);
            }
            printf("\t��λ��Ԫ");
            putchar('\n');
            printf("\n------------------------------------------------------------\n");
            putchar('\n');
            m=1;
        }
        pt=pt->next;
    }while(pt!=NULL);
    printf("\n��ϵͳ�����������ݿ�����ؼ��ʡ�%s��ƥ������ݹ��С�%d����\n",scanname,mohun);
    if(!m)
    {
        printf("\n�Բ������ݿ��в��Ҳ��������˹ؼ��ʵ���Ϣ��\n");
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
    printf("----------------------------����ͳ����ϣ�------------------------------------\n");
    printf("��С������%dλ�û�\nС������ˮΪ��%7.2f��\nԤ��С���ܷ���Ϊ��%7.2fԪ\n",n,sumv,sumfee);
}

int delete(void)
{
    char deletename[20];
    data*head,*p1,*p2;
    head=readdata();
    if(head==NULL)
    {
        printf("�Բ������ݿ�Ϊ�գ��޷�����ɾ��������\n");
        return 0;
    }
    p1=head;
    printf("����������Ҫɾ�����û���������      ��\b\b\b\b");
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
        printf("��ϲ�����û���Ϊ����%s�����û����������Ѿ��ɹ������ݿ���ɾ����\n",deletename);
        n--;
    }
    else
    {
        printf("\n�Բ���û�д����ݿ����ҵ���Ϊ��%s�����û���\n",deletename);
        putchar('\n');
    }
    writedata(head);
    return 0;


}
void help(void)
{
    system("cls");
    printf("\n��л��ѡ��ʹ�ñ���������Ϊ��ϸʹ�ò���˵��\n");
    printf("------------------------------------------------------------\n");
    printf("��1�����ݸ��£�������ݿ������е����ݣ��������������\n");
    printf("�� ��ϵͳ����û���Ϊ����end��ʱ�Զ��������ݸ��£�\n");
    printf("��2��������ݣ������ݿ����������û�������\n");
    printf("��3����ʾ�������ݣ������ݿ����������ݰ���ԭʼ�������\n");
    printf("��4���������ݣ������ݿ����������ݰ��������ˮ����Ӵ�Сȫ�����\n");
    printf("��5��ģ�����ң�����ؼ��֣�ģ�����Ҳ�������а����ؼ��ֵ���Ϣ\n");
    printf("��6������ͳ�ƣ�ͳ�Ƹ�С�������û�ʹ��ˮ�����֮���Լ�����֮��\n");
    printf("��7��ɾ��������ɾ�����ݿ��еĵ����û�����\n");
    printf("��8��������������������\n");
    printf("��9���˳������˳�����\n");

}

int main()
{

    int flag=0;
    char mark;
    SetConsoleTitle("�￡ˮ���ѯ����ϵͳ");
    printf("\n�װ����û�����ʹ�ñ�����ǰ����ϣ������ϸ�Ķ�����������\n");
    printf("\n-------------------------------------------------\n");
    printf("\n1.�������Ȩ�顾���￡������\n2.������ֻ������ѧϰ�������Ͻ�������ҵ��;\n3.ʹ�ñ������辭�������￡��ͬ�⣬Υ�߱ؾ���\n");
    printf("\n-------------------------------------------------\n");
    printf("�������������Э�飬�밴'y'����������\n");
    printf("����������ѡ�񣺡�   ��\b\b");
    scanf("%c",&mark);
    if(mark!='y')
    {
        quit();
        return 0;
    }
    system("cls");

    while(flag!=9)
    {
        printf("��������������ӭʹ���￡ˮ���ѯ����ϵͳ������������\n");
        printf("��1�����ݸ���\t��2���������\t��3����ʾ��������\n��4����������\t��5��ģ������\t��6������ͳ��\n��7��ɾ������\t");
        printf("��8����������\t��9���˳�����\n");
        printf("\n�����ȡʹ�ð���˵����ѡ��10��ʹ�ð���\n");
        printf("\n����������Ҫִ�еĹ���ǰ��Ӧ����ţ���   ��\b\b\b\b");
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
            printf("��������ȷ�Ĳ�����\n");
            break;
        }
    }
    quit();
    return 0;
}

