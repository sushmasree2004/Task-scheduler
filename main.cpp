#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

typedef struct node
{
   string task_name;
   float pri;
   struct node *link;
}node;

typedef struct node_q
{
    string c_task;
    struct node_q *link;
}node_q;

node_q *front_q=NULL;
node_q *rare_q=NULL;


//inserting the completed tasks in the queue
void enqueue(string item)
{
    struct node_q *temp=new node_q;
    temp->c_task=item;
    temp->link=NULL;
    if(front_q==NULL)
    {
       front_q=temp;
       rare_q=temp;
    }
    else
    {
       rare_q->link=temp;
       rare_q=temp;
    }
}


//for displaying the completed task using queue
void display_queue()
{
    node_q *ptr=front_q;
    string item;
    if(ptr==NULL)
    {
        cout<<"NO COMPLETED TASKS!!"<<endl;
    }
    else
    {
       cout<<"-----------------------------------------------------------"<<endl;
       cout<<"\n          ***COMPLETED TASKS***          "<<endl;
        while(ptr!=NULL)
        {
           item=ptr->c_task;
           cout<<"Task Name:"<<ptr->c_task<<endl;
           ptr=ptr->link;
        }
        cout<<"----------------------------------------------------------"<<endl;
    }
}


node *front=NULL;

//Generate the priority based on deadline and actual duration
float generate_priority(int dl,int ad)
{
    int dl_hrs,rt;
    dl_hrs=dl*24;
    rt=dl_hrs-ad;
    float rd=rt/24;
    if(rd<1)
    {
        return 0;
    }
    else if(rd>1)
    {
        return rd;
    }
    else
    {
        cout<<"         TASK REJECTED!!!     "<<endl;
        return 0;
    }
}


//for inserting task in the priority queue
void insert(string job,float p)
{
   node *temp=new node;
   node *ptr , *prev;
   temp->task_name=job;
   temp->pri=p;
   temp->link=NULL;
   if(front==NULL || front->pri > p)
   {
      temp->link=front;
      front=temp;
   }
   else
   {
     int flag=0;
     ptr=front;
     prev=NULL;
     while(ptr!=NULL)
     {
        if(ptr->pri <= p )
        {
          prev=ptr;
          ptr=ptr->link;
        }
        else
        {
           if(prev==NULL)
           {
              temp->link=front;
              front=temp;
           }
           else
           {
              prev->link=temp;
              temp->link=ptr;
           }
           flag=1;
           break;
        }
     }
     if(flag==0)
     {
        prev->link=temp;
        temp->link=NULL;
     }
   }
}


//for displaying the current task in the priority queue
void view_currentTask()
{
   node *ptr;
   ptr=front;
   cout<<endl;
   cout<<"--------------------------------------------------------------"<<endl;
   cout<<"\n                  ***CURRENT TASK***                          "<<endl;
   cout<<"Current Task Name   : "<< ptr->task_name <<endl;
   cout<<"--------------------------------------------------------------"<<endl;
}


//For getting the desired task in the priority queue
void view_desiredTask(int n)
{
   int i;
   node *ptr;
   ptr=front;
   if(ptr==NULL)
   {
       cout<<"CURRENTLY NO TASKS ARE AVAILABLE......!!"<<endl;
   }
   else
   {

        while(ptr!=NULL)
        {
             for(i=1;i<n;i++)
             {
                ptr=ptr->link;
             }
           break;
        }
        cout<<"--------------------------------------------------------------"<<endl;
        cout<<"YOUR DESIRED TASK   :"<<ptr->task_name<<endl;
        cout<<"--------------------------------------------------------------"<<endl;
   }
}


//for displaying the tasks in the priority queue
void print()
{
   cout<<"List of tasks pending......!!"<<endl;
   cout<<"--------------------------------------------------------------"<<endl;
   cout<<"                      TO DO LIST...!!                         "<<endl;
   node *ptr;
   ptr=front;
   //cout<<setw(20)<<left<<"Task Name"<<setw(20)<<right<<"Deadline"<<endl;
   while(ptr!=NULL)
   {
     cout<<"Task Name :"<<ptr->task_name<<endl;
     ptr=ptr->link;
   }
   cout<<"--------------------------------------------------------------"<<endl;
}


//for deleting the element in the priority queue
void deleting()
{
   string job;
   node *ptr;
   if(front!=NULL)
   {
     ptr=front;
     job=ptr->task_name;
     front=ptr->link;
     cout<<"--------------------------------------------------------------"<<endl;
     cout<< "Completed task   :"<<ptr->task_name<<endl;
     cout<<"--------------------------------------------------------------"<<endl;
     enqueue(ptr->task_name);
     delete (ptr);
   }
   else
   {
     cout<<"UNDER FLOW"<<endl;
   }
}

int main()
{
         cout<<"                                                 =====================================================================================           "<<endl;
         cout<<"                                                ||                                                                                   ||         "<<endl;
         cout<<"                                                ||                         ---------------------------                               ||         "<<endl;
         cout<<"                                                ||                        | WELCOME TO TASK SCHEDULER |                              ||         "<<endl;
         cout<<"                                                ||                         ---------------------------                               ||         "<<endl;
         cout<<"                                                ||                                                         by:                       ||         "<<endl;
         cout<<"                                                ||                                                   ||   SUSHMA SREE      "<<endl;
         cout<<"                                                ||                                                                                   ||         "<<endl;
         cout<<"                                                ||                                                                                   ||         "<<endl;
         cout<<"                                                 =====================================================================================          "<<endl;
    int choice,n,ad;
    int dl;
    float p;
    string job;
   do
     {
        cout<<endl<<endl;
        cout<<"[1].INSERT NEW TASK"<<endl;
        cout<<"[2].COMPLETE THE HIGHEST PRIORITY TASK"<<endl;
        cout<<"[3].VIEW THE CURRENT PRIORITY TASK"<<endl;
        cout<<"[4].VIEW THE DESIRED PRIORITY TASK"<<endl;
        cout<<"[5].VIEW ALL PENDING TASKS"<<endl;
        cout<<"[6].VIEW ALL COMPLETED TASKS"<<endl;
        cout<<"Press -1 to quit the program"<<endl<<endl;
        cout<<"Enter your choice :";
        cin>>choice;
        cout<<endl;
        switch (choice)
        {
          case 1:
                 {
                   cout<<"Enter the task name :";
                   cin.ignore();
                   getline(cin,job);
                   do
                   {
                        cout<<"Enter the deadline of task (in days):";
                        cin>>dl;
                   }
                   while(dl<=0);
                   do
                   {
                        cout<<"Enter the actual duration to complete task (in hours):";
                        cin>>ad;
                   }
                   while(ad<=0);
                   float p=generate_priority(dl,ad);
                   if(p!=0)
                   {
                       insert(job,p);
                   }
                   else
                   {
                       cout<<"Enter correct Deadline and Actual Duration"<<endl;
                   }
                   cout<<endl;
                   break;
                 }
          case 2:
                 {
                   deleting();
                   cout<<endl;
                   break;
                 }
          case 3:
                 {
                     view_currentTask();
                     cout<<endl;
                     break;
                 }
          case 4:
                 {
                     cout<<"Enter the nth priority task :";
                     cin>>n;
                     view_desiredTask(n);
                     cout<<endl;
                     break;
                 }
          case 5:
                 {
                   print();
                   cout<<endl;
                   break;
                 }
          case 6:
                 {
                     display_queue();
                     cout<<endl;
                     break;
                 }
        }
     }
     while(choice!=-1);
}
