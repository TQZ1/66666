
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
void operdepa()//删除边操作
{
    string i,j;
    int k;
    link2 *temp;
    link2 *current;
    cout<<"输入边的起点终点"<<endl;
    cin>>i>>j;
    for(k=0;k<n;k++)
    {
        if(main1[k].i==i)
        {
            break;
        }
    }
    current=main1[k].link;
    while(current->link->i!=j)
    {
        current=current->link;
    }
    temp=current->link;
    current->link=current->link->link;
    delete temp;
    for(k=0;k<n;k++)
    {
        if(main1[k].i==j)
        {
            break;
        }
    }
    current=main1[k].link;
    while(current->link->i!=i)
    {
        current=current->link;
    }
    temp=current->link;
    current->link=current->link->link;
    delete temp;
}
void operaddpa()//增加边
{
  link2 *current,*temp;
  string i,j;
  int gh,k;
  cout<<"输入插入边的两个结点"<<endl;
  cin>>i>>j;
  cout<<"输入权值"<<endl;
  cin>>gh;
  for(k=0;k<n;k++)
    {
        if(main1[k].i==i)
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
    temp->i=j;
    temp->j=gh;
    current->link=temp;
    for(k=0;k<n;k++)
    {
        if(main1[k].i==j)
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
    temp->j=gh;
    current->link=temp;
}
