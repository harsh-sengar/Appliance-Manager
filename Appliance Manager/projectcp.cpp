#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<cstring>
#include<string>
#include<queue>
#include<map>
#include<fstream>
using namespace std;

typedef struct currency
{
int dollar;
int cent;
}currency;


map<int,string> Typo;



class Appliance
{
public:
int id;
int Type;
string manufacturer;
string TypeName;
currency price ;
};



typedef struct NODE
{
Appliance *ap;
struct NODE* next;
}Node;



class AppliancePtr
{

Node* appliances=NULL;
int current_ins_memory=0;
Node* current=NULL;
queue<Node*> q;
int list_len;

public:

AppliancePtr(int size)
{list_len=size;
appliances=new Node();
Node *n=appliances;

for(int i=0;i<size-1;i++)
{
   n->next=new Node();
   n=n->next;

}

}
void List_appliance();
void edit_instance(int);
void create_instance();
void p(int);
void s();
};

void AppliancePtr::List_appliance()
{

fstream file_pointer;
for(int i=0; i<list_len; i++)
{
    string id,type,dd,cc;
    string manufacture, type_name;
    string name = std::to_string(i)+".txt";
    file_pointer.open(name,ios::in);
    while(file_pointer>>id>>type>>type_name>>manufacture>>dd>>cc)
    {
     cout<<"Id is: "<<id<<endl;
     cout<<"Type is: "<<type_name<<endl;
     Typo[stoi(type)] = type_name;
     cout<<"Manufacturer is: "<<manufacture<<endl;
     cout<<"Price is: $"<<dd<<"."<<cc<<"\n"<<endl;
    }
    cout<<endl;
    file_pointer.close();

}

}

void AppliancePtr:: edit_instance(int ins)
{

       Node* traverse = NULL;

       fstream file_pointer;
       string id1,type1,dd,cc;
    string manufacture, type_name;
    string name = std::to_string(ins)+".txt";
    file_pointer.open(name,ios::in);
    while(file_pointer>>id1>>type1>>type_name>>manufacture>>dd>>cc){}

    file_pointer.close();

    traverse=new Node();
traverse->ap=new Appliance();


 traverse->ap->id =stoi(id1);
       traverse->ap->Type = stoi(type1);
       traverse->ap->TypeName = Typo[stoi(type1)];
       traverse->ap->manufacturer = manufacture;
       traverse->ap->price.dollar = stoi(dd);
       traverse->ap->price.cent = stoi(cc);



       if(q.size()>=3)
       {
        Node* current1=q.front();
        q.pop();
        delete(current1->ap);
       }

       q.push(traverse);





   string choice;
   cout<<"Enter the entity you want to edit -\n id\n type \n manufacturer\n price\n";
   cin>>choice;
   if(choice.compare("id") == 0)
   {
     int new_id;
     cout<<"Enter new id and please don't use a previously used ID: ";
     cin>>new_id;
     traverse->ap->id = new_id;
   }
   else if(choice.compare("type") == 0)
   {
       int new_type;
       cout<<"Enter new type: ";
       cin>>new_type;
       traverse->ap->Type = new_type;
       if(Typo.find(new_type) != Typo.end())
         traverse->ap->TypeName = Typo[new_type];
       else
       {
           string new_TypeName;
           cout<<"Enter new type name: ";
           cin>>new_TypeName;
           Typo.insert(make_pair(new_type,new_TypeName));
          traverse->ap->Type = new_type;
           traverse->ap->TypeName = Typo[new_type];
       }

   }
   else if(choice.compare("manufacturer") == 0)
   {
       string new_manufacturer;
       cout<<"Enter new manufacturer's name: ";
       cin>>new_manufacturer;
       traverse->ap->manufacturer = new_manufacturer;

   }
   else if(choice.compare("price") == 0)
   {
       int new_dd,new_cc;
       cout<<"Enter new price in dollars and cents (eg. 22 44): ";
       cin>>new_dd>>new_cc;
       traverse->ap->price.dollar = new_dd;
     traverse->ap->price.cent = new_cc;

   }
   else
{
    cout<<"You have made an erroneous choice.";
}



    //Now open current file in write mode and save the entire data again;
     string name1 = std::to_string(traverse->ap->id)+".txt";
     fstream fp;
     fp.open(name1,ios::out);
     string put = " " + std::to_string( traverse->ap->id) + " " + std::to_string( traverse->ap->Type)+ " "+ traverse->ap->TypeName+" " +  traverse->ap->manufacturer + " " + std::to_string( traverse->ap->price.dollar) + " " + std::to_string( traverse->ap->price.cent);
     fp<<put;
     fp.close();




}

void AppliancePtr::create_instance()
{

	int id1,dd,cc;
	int type;//have to create a map for this
	string manufacture,typeName;

    printf("Enter id-> ");
	scanf("%d",&id1);
	printf("Enter any type  1 2 3 \n");
	map<int,string>:: iterator it;
	for(it=Typo.begin(); it != Typo.end(); it++)
	    cout<<it->first<<"."<<it->second<<endl;
	scanf("%d",&type);
	if(Typo.find(type) == Typo.end())
    {
        string new_type_name;
        cout<<"This is a new type. Please enter it's name and after that please press 's' to save changes.\n";
        cin>>new_type_name;
        Typo[type] = new_type_name;
    }
    typeName = Typo[type];
	printf("Manufacturer name ->\n");
	fflush(stdin);
	getline (std::cin,manufacture);
	printf("Enter price in $ and cents (ex- 66 54)");
	scanf("%d%d",&dd,&cc);

if(id1==0)
{
	current=appliances;
	appliances->ap=new Appliance();
    appliances->ap->id=id1;
    appliances->ap->Type=type;
    appliances->ap->TypeName=typeName;
    appliances->ap->manufacturer=manufacture;
    appliances->ap->price.dollar=dd;
    appliances->ap->price.cent=cc;

}

else
{
	int count=id1;
	Node* app=NULL;
	app = appliances;

	while(count--)
	{
		app=app->next;
	}
    current=app;

	app->ap=new Appliance();

    app->ap->id=id1;
    app->ap->Type=type;
    app->ap->TypeName=typeName;
    app->ap->manufacturer=manufacture;
    app->ap->price.dollar=dd;
    app->ap->price.cent=cc;
}



fstream fp;
string name = std::to_string(id1)+".txt";
fp.open(name,ios::out);

string put = " " + std::to_string(id1) + " " + std::to_string(type)+ " "+ typeName+" " + manufacture + " " + std::to_string(dd) + " " + std::to_string(cc);

fp<<put;
fp.close();


if(q.size()>=3){
    Node* traverse=q.front();
    q.pop();
    delete(traverse->ap);

}

 q.push(current);


}





void AppliancePtr::p(int ins)
{
   Node* traverse = NULL;

       fstream file_pointer;
       string id1,type1,dd,cc;
    string manufacture, type_name;
    string name = std::to_string(ins)+".txt";
    file_pointer.open(name,ios::in);
    while(file_pointer>>id1>>type1>>type_name>>manufacture>>dd>>cc){}

    file_pointer.close();

    traverse=new Node();
traverse->ap=new Appliance();


 traverse->ap->id =stoi(id1);
       traverse->ap->Type = stoi(type1);
       traverse->ap->TypeName = Typo[stoi(type1)];
       traverse->ap->manufacturer = manufacture;
       traverse->ap->price.dollar = stoi(dd);
       traverse->ap->price.cent = stoi(cc);



       if(q.size()>=3)
       {
        Node* current1=q.front();
        q.pop();
        delete(current1->ap);
       }

       q.push(traverse);


int new_dd,new_cc;
       cout<<"Enter new price in dollars and cents (eg. 22 44): ";
       cin>>new_dd>>new_cc;
       traverse->ap->price.dollar = new_dd;
     traverse->ap->price.cent = new_cc;


 string name1 = std::to_string(traverse->ap->id)+".txt";
     fstream fp;
     fp.open(name1,ios::out);
     string put = " " + std::to_string( traverse->ap->id) + " " + std::to_string( traverse->ap->Type)+ " "+ traverse->ap->TypeName+" " +  traverse->ap->manufacturer + " " + std::to_string( traverse->ap->price.dollar) + " " + std::to_string( traverse->ap->price.cent);
     fp<<put;
     fp.close();



}
void AppliancePtr::s()
{
   Node* current = NULL;
   while(!q.empty())
   {
       current = q.front();
       string name = std::to_string(current->ap->id)+".txt";
       fstream fp;
       fp.open(name,ios::in);
       fp.close();
       q.pop();
       delete(current->ap);

   }

}

int main()
{
Typo.insert(make_pair(1,"LAUNDRY_MACHINE"));
Typo.insert(make_pair(2,"DISH_WASHER"));
Typo.insert(make_pair(3,"DRYER"));
	AppliancePtr *user=new AppliancePtr(20);



	printf("Welcome.\nPlease enter - (help) for menu ");
	printf("--> ");

	string str;
	cin>>str;


	if(str.compare("help")==0){
		cout<<"press key "<<"\n";

		cout<<"l - List \n";
		cout<<"c - Create an appliance  \n";
		cout<<"p - Change price of current appliance \n";
		cout<<"s - Save all appliances \n";
		cout<<"0..9 - Edit an appliance  \n";
		cout<<"q - Quit \n";

        bool end = 1;
        while(end != 0)
        {
		char op;

		cin>>op;

		switch(op)
		{

			case 'l' :
			user->List_appliance();
			break;

			case 'c' :
			user->create_instance();
			break;

			case 'p' :
            int ID;
            cout<<"Enter id of appliance whose price you want to change: ";
            cin>>ID;
			user->p(ID);
			break;

			case 's' :
			user->s();
			break;

			case 'q' :
              cout<<"------- ** Thank you ** -------\n";
			  end=0; //exit(1);
            break;


			case '0':
			user->edit_instance((int)(op-'0'));
			break;

			case '1':
			user->edit_instance((int)(op-'0'));
			break;

			case '2':
			user->edit_instance((int)(op-'0'));
			break;

			case '3':
			user->edit_instance((int)(op-'0'));
			break;

			case '4':
			user->edit_instance((int)(op-'0'));
			break;

			case '5':
			user->edit_instance((int)(op-'0'));
			break;

			case '6':
			user->edit_instance((int)(op-'0'));
			break;

			case '7':
			user->edit_instance((int)(op-'0'));
			break;

			case '8':
			user->edit_instance((int)(op-'0'));
			break;

			case '9':

			user->edit_instance((int)(op-'0'));
			break;

			default:
			printf("Wrong Entry, Please input valid option . ");
			break;

			}
			if(op != 'q')
			   cout<<"If you want to exit, press 'q' else make your choice again\n\n";



}

}

	return 0;
}
