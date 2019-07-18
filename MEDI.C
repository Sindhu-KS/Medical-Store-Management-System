#include<stdio.h>
#include<conio.h>
#include<string.h>

#include<math.h>
#include<ctype.h>

int i;
void mai_menu();
void medicine();
void medi_entry();
void medi_search();
void remainder();
void cust_entry();
void stock();

struct medical
{
char id[6];
char medi_name[20];
int rack, quantity;
float unit;
float cost;
int qty;
float total;
float sale;
};

struct medical temp;
struct medical x[20];
FILE *ptr;

struct customer
{
char cust_name[30];
char city[20];
};
struct customer temp_c;
FILE *ptr1;

struct purchase_report
{
char medi_id[6];
char medir_name[20];
int qty;
float rate;
float total;
};
struct purchase_report p_r;
FILE *ptrp_r;
char a[10];

void linkfloat()
{
float f,*p;
p=&f;
f=*p;
}
void ventry(char t[],int code)
{
int i=0;
if(code==0)
{
while((t[i]=getch())!='\r'&&i<30) if((t[i]>=97&& t[i]<=122) || (t[i]>=65 && t[i]<=90) ||t[i]==32 || t[i]=='_')
{
printf("%c",t[i]);
i++;
}
else
if(t[i]==8&&i>0)
{
printf("%c%c%c",8,32,8);
i--;
}
}
else
if(code==1){ while((t[i]=getch())!='\r'&& i<10)
if((t[i]>=48&&t[i]<=57)||t[i]==46||t[i]=='_')
{
printf("%c",t[i]);
i++;
}
else
if(t[i]==8 && i>0)
{
printf("%c%c%c",8,32,8);
i--;
}
}
else
if(code==2)
{
while((t[i]=getch())!='\r'&&i<30)
if((t[i]>=97 && t[i]<=122) || (t[i]>=65 && t[i]<=90) || (t[i]>=48 && t[i]<=57)||t[i]==32|| t[i]==8 || t[i]=='@' || t[i]=='.')
{
printf("%c",t[i]);
i++;
}
else
if(t[i]==8 && i>0)
{
printf("%c%c%c",8,32,8);
i--;
}
}
t[i]='\0';
}

void stock()
{
char ch;
int i,c;
do

{
system("cls");
ptr1=fopen("medical.dat","r");
if(ptr1==NULL)
{
printf("Cannot open the file ");
exit(1);
}
system("cls");
gotoxy(15,2);
printf("Stock of medicine ");
i=8;
gotoxy(2,5);
printf("\tID.\tMedicine Name.\tQty ");

while((fread(&temp,sizeof(temp),1,ptr1))==1)
{
gotoxy(2,i);
printf("%s",temp.id);
gotoxy(8,i);
printf("%s",temp.medi_name);
gotoxy(16,i);
printf("%d",temp.quantity);

i++;
}

 gotoxy(2,20);
 printf("Press 0 for main menu ");
 c=(getche());
 switch(c)
 {
 case '0': mai_menu();
 break;
 }
 }
 while(c!='1');
 getche();
}

void remainder()
{
ptr1=fopen("medical.dat","r");
if(ptr1==NULL)
{
printf("Cannot open file ");
}

while((fread(&temp,sizeof(temp),1,ptr1))==1)
{
if(temp.quantity<10)
{
gotoxy(4,30);
printf("%s: ",temp.medi_name);
printf("Quantity of this medicine is less than 10...Place the order.. \n");
}
}
}

void medi_entry()
{
char medi_name;
char ch,id[6];
int f;
FILE *fp;

system("cls");
ptrp_r=fopen("purreport.dat","a");
ch='Y';

while(ch=='Y')
{
gotoxy(15,2);
printf("Medicine Purchase ");
{
gotoxy(5,5);
printf("Medicine ID: ");
gotoxy(5,7);
printf("Medicine Name: ");
gotoxy(5,9);
printf("Enter Rack number: ");
gotoxy(5,11);
printf("Unit cost Rs.: ");
gotoxy(5,13);
printf("sales cost Rs.: ");
gotoxy(5,15);
printf("Quantity ");
gotoxy(20,5);
ventry(temp.id,1);
strcpy(id,temp.id);
fp=fopen("medical.dat","r");
while((fread(&temp,sizeof(temp),1,fp))==1)
{
if(strcmp(id,temp.id)==0)

{
f=1;
break;
}
}
fclose(fp);

if(f==1)
{
gotoxy(22,5);
printf("ID already exists ");
getche();
system("cls");
medi_entry();
}
else
{
ptr=fopen("medical.dat","a+b");
strcpy(temp.id,id);
strcpy(p_r.medi_id,temp.id);
}

gotoxy(20,7);

ventry(temp.medi_name,0);
strcpy(p_r.medir_name,temp.medi_name);

gotoxy(25,9);
ventry(a,1);
temp.rack=atoi(a); //atoi is used to convert str to int

gotoxy(24,11);
ventry(a,1);

temp.unit=atof(a);
p_r.rate=temp.unit;
gotoxy(25,13);
ventry(a,1);
temp.sale=atof(a);
gotoxy(20,15);
ventry(a,1);
temp.quantity=atoi(a);
p_r.qty=temp.quantity;

gotoxy(3,17);
temp.total=(temp.sale*temp.quantity);
printf("Total Sale Cost= Rs.%.2f",temp.total);

temp.cost=(temp.unit*temp.quantity);

gotoxy(3,18);
printf("Total unit cost=Rs.%.2f",temp.cost);
p_r.total=temp.cost;
}

gotoxy(3,20);
printf("Save");

gotoxy(3,21);
printf("Cancel");

gotoxy(3,23);
printf("Press first character for the operation ");
ch=toupper(getche());

if(ch=='S')
{
fwrite(&temp,sizeof(temp),1,ptr);
fflush(stdin);
fprintf(ptrp_r,"%s%s%d%.2f\n",p_r.medi_id,p_r.medir_name,p_r.qty,p_r.rate);
system("cls");

gotoxy(10,5);
printf("Medicine added successfully!!.. ");
gotoxy(10,8);
printf("More entries [y/n]");
ch=toupper(getche());
if(ch=='Y')
{
system("cls");
medi_entry();
}
else
{
system("cls");
mai_menu();
}}
}
fclose(ptr);
fclose(ptrp_r);
}

void medi_search()
{
char mid[6];
int i,c;
system("cls");
ptr1=fopen("medical.dat","r");
if(ptr1==NULL)
{
printf("\n\tCannot open file ");
exit(0);
}
gotoxy(10,7);
printf("Enter medicine Id to be searched: ");
scanf("%s",&mid);

gotoxy(30,8);
printf("Medicine ");
i=14;
gotoxy(9,10);
printf("ID    Medicine Name    Qty ");

while((fread(&temp,sizeof(temp),1,ptr1))==1)
{
if(strcmp(mid,temp.id)==0)
{
gotoxy(9,i);
printf("%s",temp.id);
gotoxy(15,i);
printf("%s",temp.medi_name);
gotoxy(32,i);
printf("%d",temp.quantity);
i++;
break;
}
}
if(strcmp(mid,temp.id)!=0)
{
gotoxy(20,20);
printf("Not in stock...");
}
getche();
}
void main()
{
clrscr();
mai_menu();
getch();
}
