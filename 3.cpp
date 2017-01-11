#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<stack>
#include<queue>
#include<windows.h>

using namespace std;

#define maxvalue 100
int n=9;
int dist[100];
int path[100];
struct link2
{
    string i;//路由名称
    int j;//权值
    link2 * link=NULL;
};
struct link1
{
    string i;//路由名称
    string s;//路由ip
    int flag;//删除位
    link2*link=NULL;
};
struct binary
{
    int pre;
    int next[100];
    int nwei=0;
};


binary create[100];
link1 main1[100];
int count1;

void primary1()//初始化路由结点
{
    string s;
    int i=0;
    fstream out("f://路由1//1.txt");
    for(i=0;i<9;i++)
    {
        out>>main1[i].i;
        out>>main1[i].s;
        main1[i].flag=0;
    }
}

void primary2()//初始化结点的关联结点
{
    link2*temp,*current;
    int sum;
    int i;
    fstream out1("f://路由1//2.txt");
    char s;
    string gh;
    for( i=0;i<9;i++)
    {
        temp=new link2;
        out1>>gh;
        temp->i=gh;
        out1>>s;
        sum=s-'0';
        temp->j=sum;
        main1[i].link=temp;
        current=temp;
        while(1)
        {
            out1>>gh;
            if(gh[0]=='#')
            {
                break;
            }
            temp=new link2;
            temp->i=gh;
            out1>>s;
            sum=s-'0';
            temp->j=sum;
            current->link=temp;
            current=current->link;
        }
    }
}

void operdepo()//删除结点操作
{

    string i;
    int k;
    cout<<"输入要删除的结点名称"<<endl;
    cin>>i;
    for(k=0;k<n;k++)
    {
        if(main1[k].i==i)
        {
            break;
        }
    }
    main1[k].flag=1;
}
void operaddpo()//增加结点
{
   string s,i,h;
   int j,count1;
   int k;
   link2*current,*temp,*current1;
   cout<<"输入添加结点名称和ip"<<endl;
   cin>>i>>s;
   n=n+1;
   main1[n-1].flag=0;
   main1[n-1].i=i;
   main1[n-1].s=s;
   cout<<"输入关联结点个数"<<endl;
   cin>>count1;//循环插入算法
   cout<<"依次输入关联结点名称和权值以空格分开"<<endl;
   temp=new link2;
   cin>>h;
   cin>>j;
   temp->i=h;
   temp->j=j;
   main1[n-1].link=temp;
   current1=temp;
    for(k=0;k<n;k++)
    {
        if(main1[k].i==h)
        {
            break;
        }
    }
    current=main1[k].link;
    while(current->link!=NULL)
    {
        current=current->link;
    }
    temp=new link2;
    temp->i=i;
    temp->j=j;
    current->link=temp;
    for(int g=0;g<count1-1;g++)
    {
   temp=new link2;
   cin>>h;
   cin>>j;
   temp->i=h;
   temp->j=j;
   current1->link=temp;
   current1=temp;
    for(k=0;k<n;k++)
    {
        if(main1[k].i==h)
        {
            break;
        }
    }
    current=main1[k].link;
    while(current->link!=NULL)
    {
        current=current->link;
    }
    temp=new link2;
    temp->i=i;
    temp->j=j;
    current->link=temp;
    }
}

