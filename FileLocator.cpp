#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include<dirent.h>
#include<String>
#include<cstring>
using namespace std;
struct rootnode
{
   string loc;
   rootnode *next;
   rootnode *child;
   rootnode *parent;
};
struct rootnode *head;
void addnode(struct rootnode *ptr, string n)
{
	struct rootnode *temp;
	temp=new rootnode;
	if(temp)
	{
		temp->loc=n;
		temp->next=NULL;
		temp->child=NULL;
		temp->parent=ptr;
	if(ptr->child==NULL)
	{
	ptr->child=temp;
	}
	else
	{
		struct rootnode *newtemp=ptr->child;
		while(newtemp->next!=NULL)
		{
			newtemp=newtemp->next;
		}
		newtemp->next=temp;
	}
	}
}
void openfile(struct rootnode *ptr){
        DIR *pDIR;
        struct dirent *entry;
        string s=ptr->loc;
        const char *dir=s.c_str();
        if( pDIR=opendir(dir) ){
                while(entry = readdir(pDIR)){
                        if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
                        {
                        string str=ptr->loc+'\\' +(string)entry->d_name;
                        addnode(ptr,str);
                }
                }
                closedir(pDIR);
        }
}
void createTree(struct rootnode *ptr)
{
	if(ptr!=NULL)
	{
		int i=0,flag=0;
		string s=ptr->loc;
	while((int)s[i]!=0)
	{
		if((int)s[i]==46)
		{
			flag=1;
			break;
		}
		i++;
	}
	if(flag==0)
	{
	openfile(ptr);
	struct rootnode *temp=ptr->child;
	while(temp!=NULL)
	{
		createTree(temp);
		temp=temp->next;
	}
	}
	}
}
void search(struct rootnode *ptr,string str)
{
	if(ptr!=NULL)
	{
            string s=ptr->loc;
            int i=0,k=0,flag=0;
            while((int)s[i]!=0)
            { flag=1;
            	if(toupper(s[i])==toupper(str[k]))
            	{   flag=0;
            		while((int)str[k]!=0)
            		{
            			if(toupper(str[k])!=toupper(s[i]))
            			{
            				flag=1;
            				break;
            			}
            			k++;
            			i++;
            		}
            		if(flag==0)
            		{
            			break;
            		}
            	}
            	k=0;
            	i++;
            }
            if(flag==0)
            {
            	cout<<s<<"\n";
            }
            struct rootnode *temp=ptr->child;
                       while(temp!=NULL)
                       {
                       search(temp,str);
                       temp=temp->next;
           	        }

	}
}
int main(){
	string str;
	cout<<"Enter Search Directory ";
	cin>>str;
	head=new rootnode;
		head->loc=str;
		head->child=NULL;
		head->next=NULL;
		head->parent=NULL;
    createTree(head);
    cout<<"Enter word to search ";
    string s;
    cin>>s;
    search(head,s);
    return 0;
}

