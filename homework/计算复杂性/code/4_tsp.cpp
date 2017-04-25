#include <list>
#include <iostream>
using namespace std ;

typedef list<int> LISTINT;

LISTINT listAnother;
LISTINT list_result;

int d[4][4]={{-1,3,6,7},{2,-1,8,6},{7,3,-1,5,},{7,3,7,-1}}; //路径权值
int matrix_length=4;

int getPath(int n,LISTINT list_org)
{

LISTINT::iterator i;

int minValue;
if(n==1)
 {
  i=list_org.begin();
  minValue= d[*i-1][0];
  if(list_org.size()==matrix_length-1)
   {
    list_result=list_org;
   }
 }
else
 {
   int temp;
   i=list_org.begin();
   temp=*i;
   list_org.erase(i);
   i=list_org.begin();
   minValue=d[temp-1][*(i)-1]+getPath(n-1,list_org);
   if(list_org.size()==matrix_length-1)
      {
         list_result=list_org;
      }

   for(int j=2;j<n;j++)
   {
      i=list_org.begin();
      for(int k=1;k<j;k++)
       {
        i++;
       }

      int tempvalue=*i;
      list_org.erase(i);
      list_org.push_front(tempvalue);
      i=list_org.begin();
      tempvalue=d[temp-1][*(i)-1]+getPath(n-1,list_org);

       if(tempvalue<minValue)
       {
          if(list_org.size()==matrix_length-1)
          {
          list_result=list_org;
          }
       minValue=tempvalue;
       }

   }
 }
 return minValue;
}
int main(int argc, char* argv[])
{

LISTINT list_org;
LISTINT::iterator h;
list_org.push_front(4);
list_org.push_front(3);
list_org.push_front(2);
list_org.push_front(1);
cout<<"路线长度的矩阵表示如下 （-1表示无限大）"<<endl;
for(int j=0;j<matrix_length;j++){
cout<<endl;
for(int k=0;k<matrix_length;k++){
cout<<" "<<d[j][k];
}
}
cout<<endl;


cout<<"计算结果:"<<getPath(4,list_org)<<endl;
list_result.push_front(1);
list_result.push_back(1);
cout<<"要走的路径:---->:";
for (h = list_result.begin(); h != list_result.end(); ++h)

cout << *h << " ";


cout << endl;
int i;
cin>>i;
return 0;
}
