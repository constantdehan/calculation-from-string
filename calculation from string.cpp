#include<bits/stdc++.h>
#include<string>
#include<math.h>

using namespace std;

char str[100];
FILE *p,*q;
char variable[50];
int value[50];
int var_index=0;

void save_result(char postfix[],int index,int result)
{
    char temp[50];
    int t_index=0;
    int check=0;
    int num[10];

    for(int i=0; i<index; i++)
    {
        if(postfix[i]=='=')
        {
            temp[t_index]=postfix[i-1];
            t_index++;
            temp[t_index]=postfix[i];
            t_index++;

            for(int j=0;j<=var_index;j++)
            {
                if(variable[j]==temp[i-1])
                {
                    value[j]=result;
                    var_index++;
                    break;
                }
                variable[var_index]=temp[i-1];
                value[var_index]=result;
                var_index++;
                break;
            }
            break;
        }
    }
    while(result>0)
    {
        num[check]=result%10;
        result=result/10;
        check++;
    }
    cout<<"Do u want to SAVE the RESULT?"<<endl;
    cout<<"Press 'Y' to save"<<endl;
    cout<<"Press 'N' not to save"<<endl;
    char yes_no;
    cin>>yes_no;
    int i;

    for(i=t_index; i<=index; i++)
    {
        while(check>0)
        {
            temp[i]=num[check-1]+'0';
            i++;
            check--;
        }
        break;
    }
    temp[i]='\0';
    if(yes_no=='Y')
    {
        fprintf(q,"%s\n",temp);
    }
    else
    {
        cout<<temp<<endl;
    }
}

void postfix_evaluation(char postfix[],int index)
{
    int stac[50];
    int top=-1;
    int result=0;

    for(int i=0;i<index;i++)
    {
        if(postfix[i]>='0' && postfix[i]<='9')
        {
            int num[10];
            int check=0;
            int mult[5]={1,10,100,1000,10000};
            while(postfix[i]>='0' && postfix[i]<='9')
            {
                int con_int=postfix[i]-'0';
                num[check]=con_int;
                check++;
                i++;
            }
            int val=0;
            for(int j=check-1;j>=0;j--)
            {
                int temp1=num[j];
                int temp2=mult[check-j-1];
                val=val+(temp1*temp2);
            }
            top++;
            stac[top]=val;
        }
        else if((postfix[i]>='a' && postfix[i]<='z') || (postfix[i]>='A' && postfix[i]<='Z'))
        {
            for(int j=0;j<=var_index;j++)
            {
                if(postfix[i]==variable[j])
                {
                    top++;
                    stac[top]=value[j];
                    break;
                }
            }
        }
        else if(postfix[i]=='+')
        {
            int temp1=stac[top];
            top--;
            int temp2=stac[top];
            top--;
            int sum=temp2+temp1;
            top++;
            stac[top]=sum;
        }
        else if(postfix[i]=='-')
        {
            int temp1=stac[top];
            top--;
            int temp2=stac[top];
            top--;
            int sum=temp2-temp1;
            top++;
            stac[top]=sum;
        }
        else if(postfix[i]=='*')
        {
            int temp1=stac[top];
            top--;
            int temp2=stac[top];
            top--;
            int sum=temp2*temp1;
            top++;
            stac[top]=sum;
        }
        else if(postfix[i]=='/')
        {
            int temp1=stac[top];
            top--;
            int temp2=stac[top];
            top--;
            int sum=temp2/temp1;
            top++;
            stac[top]=sum;
        }
        else if(postfix[i]=='^')
        {
            int temp1=stac[top];
            top--;
            int temp2=stac[top];
            top--;
            int sum=pow(temp2,temp1);
            top++;
            stac[top]=sum;
        }
    }
    result=stac[top];
    save_result(postfix,index,result);
}

void calculate()
{
    char stac[50];
    int top=-1;
    char postfix[50];
    int index=0;
    char temp[50];
    temp[0]='(';
    int i;

    for(i=1;str[i]!='\0';i++)
    {
        temp[i]=str[i-1];
    }
    temp[i]=')';
    int len=i;
    for(int k=0;k<=len;k++){
        cout<<temp[k];
    }
    cout<<"\n";
    for(i=0;i<=len;i++)
    {
        if(temp[i]=='=')
        {
            postfix[index]=temp[i];
            index++;
        }
        else if(temp[i]=='(')
        {
            top++;
            stac[top]=temp[i];
        }
        else if(temp[i]=='+')
        {
            if(stac[top]=='+' || stac[top]=='-' || stac[top]=='*' || stac[top]=='/' || stac[top]=='^')
            {
                while(stac[top]!='(')
                {
                    postfix[index]=stac[top];
                    index++;
                    top--;
                }
                top++;
                stac[top]=temp[i];
            }
            else
            {
                top++;
                stac[top]=temp[i];
            }
        }
        else if(temp[i]=='-')
        {
            if(stac[top]=='+' || stac[top]=='-' || stac[top]=='*' || stac[top]=='/' || stac[top]=='^')
            {
                while(stac[top]!='(')
                {
                    postfix[index]=stac[top];
                    index++;
                    top--;
                }
                top++;
                stac[top]=temp[i];
            }
            else
            {
                top++;
                stac[top]=temp[i];
            }
        }
        else if(temp[i]=='*')
        {
            if(stac[top]=='*' || stac[top]=='/' || stac[top]=='^')
            {
                while(stac[top]!='(')
                {
                    postfix[index]=stac[top];
                    index++;
                    top--;
                }
                top++;
                stac[top]=temp[i];
            }
            else
            {
                top++;
                stac[top]=temp[i];
            }
        }
        else if(temp[i]=='/')
        {
            if(stac[top]=='*' || stac[top]=='/' || stac[top]=='^')
            {
                while(stac[top]!='(')
                {
                    postfix[index]=stac[top];
                    index++;
                    top--;
                }
                top++;
                stac[top]=temp[i];
            }
            else
            {
                top++;
                stac[top]=temp[i];
            }
        }
        else if(temp[i]=='^')
        {
            top++;
            stac[top]=temp[i];
        }
        else if(temp[i]==')')
        {
            while(stac[top]!='(')
            {
                postfix[index]=stac[top];
                index++;
                top--;
            }
            top--;
        }
        else
        {
            if((temp[i]>='a'&&temp[i]<='z') || (temp[i]>='A'&& temp[i]<='Z'))
            {
                postfix[index]=temp[i];
                index++;
            }
            else{
                while(temp[i]>='0' && temp[i]<='9'){
                    postfix[index]=temp[i];
                    index++;
                    i++;
                }
                postfix[index]=' ';
                index++;
                i--;
            }
        }
    }
    postfix[index]='\0';
    postfix_evaluation(postfix,index);
}

int check_error()
{
    int i;
    for(i=0; str[i] != '\0'; i++)
    {
        if(str[i]=='+')
        {
            if(str[i+1]=='+' || str[i+1]=='-' || str[i+1]=='*' || str[i+1]=='/' || str[i+1]=='^')
            {
                cout<<"ERROR"<<endl;
                return 1;
            }
        }
        else if(str[i]=='*')
        {
            if(str[i+1]=='+' || str[i+1]=='-' || str[i+1]=='*' || str[i+1]=='/' || str[i+1]=='^')
            {
                cout<<"ERROR"<<endl;
                return 1;
            }
        }
        else if(str[i]=='/')
        {
            if(str[i+1]=='+' || str[i+1]=='-' || str[i+1]=='*' || str[i+1]=='/' || str[i+1]=='^')
            {
                cout<<"ERROR"<<endl;
                return 1;
            }
        }
        else if(str[i]=='^')
        {
            if(str[i+1]=='+' || str[i+1]=='-' || str[i+1]=='*' || str[i+1]=='/' || str[i+1]=='^')
            {
                cout<<"ERROR"<<endl;
                return 1;
            }
        }
    }
    if(str[i-1]!=';')
    {
         cout<<"ERROR"<<endl;
         return 1;
    }
    else return 0;
}

int main()
{
    p=fopen("ins.txt","r");
    q=fopen("outs.txt","w");


    while(fscanf(p,"%s",str)==1)
    {
        int flag=0;
        flag=check_error();
        if(flag==0)
        {
            calculate();
        }
        else break;
    }


    return 0;
}
