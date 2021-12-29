#include<iostream>
#include<string>
#include<string.h>
#include<cstring>
using namespace std;
struct node
{
	int pos;
	node *next;
};
struct node *head[28];

int indexofchar(char letter)
{
	if((int)letter<=90&&(int)letter>=65)
		return ((int)letter-65);
	else if((int)letter<=122&&(int)letter>=97)
	     return ((int)letter-97);
	else if((int)letter<=57&&(int)letter>=48)
		return (26);
	else
		return (27);
}
void insert(char letter, int position)
{
	struct node *temp;

	temp=new node;
	if(temp)
	{
		temp->pos=position;
		temp->next=NULL;
	    int i;
	    i=indexofchar(letter);
		if(head[i]==NULL)
	    	{
	    		head[i]=temp;
	    	}
	    	else
	    	{
	    		struct node *ptr=head[i];

	    		while(ptr->next!=NULL)
	    		{
	    			ptr=ptr->next;
	    		}
	    		ptr->next=temp;
	    	}
}
}
void search(string txt, string str)
{
	int i=0;
	while((int)str[i]!=0)
	{
		str[i]=toupper(str[i]);
		i++;
	}
	i=0;
	struct node *ptr=head[indexofchar(str[0])];
	if(ptr==NULL)
	{
		cout<<"Word Not Found";
	}
	else
	{
		while(ptr!=NULL)
		{
			string comparestr="";
			int i=ptr->pos;
			while((int)txt[i]!=32)
			{
                            char c=toupper(txt[i]);
                               comparestr=comparestr+c;
                                i++;
				if(comparestr==str)
				{
				cout<<(ptr->pos+1)<<"\n";
				break;
				}
			}
			ptr=ptr->next;
		}
	}
}
int main()
{
	string txt="My name is Vikas";
	int i=0;
    while((int)txt[i]!=0)
    {
     insert(txt[i],i);
     while((int)txt[i]!=32&&(int)txt[i]!=0)
     {
    	 i++;
     }
     i++;
    }
    string s;
    cin>>s;
    while(s!="")
    {
    search(txt,s);
    cin>>s;
    }
    return 0;
}
