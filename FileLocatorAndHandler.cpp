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
struct list
{
	string loc;
	list *next;
};
struct list *start;
struct rootnode *head;

void insertList(string x)
{
struct list *temp;
struct list *ptr=start;
temp=new list;
if(!temp)
{
cout<<"OverFlow\n";
}
else
{
temp->loc=x;
temp->next=NULL;
if(start==NULL)
{
start=temp;
}
else
{
while(ptr->next!=NULL)
{
	ptr=ptr->next;
}
ptr->next=temp;
}
}
}
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
        if(pDIR=opendir(dir)){
                while(entry=readdir(pDIR)){
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
            	insertList(s);
            }
            struct rootnode *temp=ptr->child;
            while(temp!=NULL)
            {
            search(temp,str);
            temp=temp->next;
           	}
	}
}
void Listtraverse()
{
struct list *ptr=start;
if(ptr==NULL)
{
cout<<"File Not Found In Current Directory\n";
}
else
{
int i=1;
while(ptr!=NULL)
{
cout<<i<<") "<<ptr->loc<<"\n";
ptr=ptr->next;
i++;
}
}
}
void SearchDirectory(string str)
{
	head=new rootnode;
		head->loc=str;
		head->child=NULL;
		head->next=NULL;
		head->parent=NULL;
	    createTree(head);
}
string fileat(int n)
{
	struct list *ptr=start;
	if(ptr==NULL)
	{
	cout<<"File Not Found In Current Directory\n";
	}
	else
	{
	int i=1;
	while(ptr!=NULL&&i!=n)
	{
	ptr=ptr->next;
	i++;
	}
	return ptr->loc;
	}
	return NULL;
}
struct node
{
	int pos;
	node *next;
};
struct node *top[28];
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
		if(top[i]==NULL)
	    	{
	    		top[i]=temp;
	    	}
	    	else
	    	{
	    		struct node *ptr=top[i];

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
	struct node *ptr=top[indexofchar(str[0])];
	if(ptr==NULL)
	{
		cout<<"Word Not Found";
	}
	else
	{
		int flag=0;
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
				{if(flag==0)
				{
				cout<<"\nPosition     Word\n";
				flag=1;
				}
				cout<<(ptr->pos+1)<<"           ";
				i=ptr->pos;
				while((int)txt[i]!=0&&(int)txt[i]!=32)
				{
					i--;
				}
				i++;
				string word="";
				while((int)txt[i]!=0&&(int)txt[i]!=32)
				{
				word=word+txt[i];
				i++;
				}
				cout<<word<<endl;
				break;
				}
			}
			ptr=ptr->next;
		}
		if(flag==0)
		{
			cout<<"Word Not Found";
		}
	}
}
void createHashTable(string txt)
{
	for(int j=0;j<28;j++)
	{
		top[j]=NULL;
	}
	int i=0;
	while((int)txt[i]!=0)
	{
	insert(txt[i],i);
	i++;
	while((int)txt[i]==32)
	{
		i++;
	}
	}
}
int main(){
	cout<<"1) Enter Search Directory\n"<<"2) Search a file in current directory\n"<<"3) Change Search Directory\n"<<"4) Exit\n";
	int num;
	cin>>num;
	string str,s;
	while(num!=4)
	{
		if(num==1||num==3)
		{
		cin>>str;
		SearchDirectory(str);
		}
		else
		if(num==2)
		{
		start=NULL;
		cout<<"Enter search file name ";
		cin>>s;
		if((int)str[0]==0)
		{
		cout<<"Please first Enter a Search Directory\n";
		}
		else
		{
		search(head,s);
		Listtraverse();
		}
		int n;
		cout<<"\nPlease Select the file to perform operations. Enter 0 to exit\n";
		cin>>n;
		if(n>0)
		{   string file;
		    file=fileat(n);
		    if((int)file[0]!=0)
		    {
			ifstream inFile;
			inFile.open(file);
			string x;
			if (!inFile) {
			        cout << "Unable to open file";
			        exit(1);
			    }
            string txt="";
			    while (inFile >> x) {
			       txt=txt+x+" ";
			    }
			    createHashTable(txt);
			    cout<<"\n1) Read File \n2) Search for a word in file \n3) Copy File To Another Location\n4) Exit\n";
			    int c;
			   	cin>>c;
			    while(c!=4)
			    {
			    if(c==1)
			    {cout<<txt;}
			    else if(c==2)
			    {
			    cout<<"Enter word to search ";
			    cin>>s;
			    search(txt,s);
			    }
			    else if(c==3)
			    {
			    	cout<<"Enter new Location ";
			    	string location;
			    	cin>>location;
			    	cout<<"Enter name of File ";
			    	string name;
			    	cin>>name;
			    	ofstream myfile;
			    	ifstream ifile(location+"\\"+name+".txt");
			    	if (ifile) {
			    	  cout<<"\nFile With same name already Exists. Press 'Y' to Replace file in Destination and 'N' to skip ";
			    	  char t;
			    	  cin>>t;
			    	  if(toupper(t)=='Y')
			    	  {
			    		  myfile.open (location+"\\"+name+".txt");
			    		  myfile <<txt;
			    		  cout<<"File Successfully copied\n";
			    		  myfile.close();
			    	  }
			    	}
			    	else
			    	{
			    	  myfile.open (location+"\\"+name+".txt");
			    	  myfile <<txt;
		    		  cout<<"File Successfully copied\n";
			    	  myfile.close();
			    }
			    }
			    else
			    {
			    	cout<<"Wrong Input";
			    }
			    cout<<"\n1) Read File \n2) Search for a word in file \n3) Copy File To Another Location\n4) Exit\n";
			    cin>>c;
		}
		}
		else
		{
			cout<<"Invalid Input\n\n";
		}
		}
		}
		cout<<"\n1) Enter Search Directory\n2) Search a file in current directory\n3) Change Search Directory\n4) Exit\n";
     	cin>>num;
	}
    return 0;
}

