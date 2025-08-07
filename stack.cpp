#include<iostream>
using namespace std;
int top=-1;
void push(int n,int st[]){
    int val,i;
    if(top<n-1){
        cout<<"Enter element: ";
        cin>>val;
        st[++top]=val;
        cout<<"Stack: ";
        for(i=0;i<=top;i++)cout<<st[i]<<" ";
    }
    else cout<<"Stack Overflow";
}
void pop(int n,int st[]){
    int i;
    if(top>-1){
        cout<<"Removed "<<st[top--];
        cout<<"Stack: ";
        for(i=0;i<=top;i++)cout<<st[i]<<" ";
    }
    else cout<<"Stack Underflow";
}
void IsEmpty(){
    if(top==-1)cout<<"Stack is empty ";
    else cout<<"Stack is not empty ";
}
void IsFull(int m){
    if(top>=m)cout<<"Stack is full";
    else cout<<"Stack is not full";
}
void Peek(){
    cout<<"Top = "<<top<<"\nValue: "<<st[top];
}
void view(int st[]){
    cout<<"Stack: ";
    for(int i=0;i<=top;i++)cout<<st[i]<<" ";
}
int main(){
    int n,m,op;
    cout<<"Input Size: ";
    cin>>m;
    int st[m];
    while(true){
    cout<<"\nSelect an operation\n1-Push\n2-Pop\n3-IsEmpty\n4-IsFull\n5-Peek\n6-View Stack\n";
    cin>>n;
    if(n==1)push(m,st);
    else if(n==2)pop(m,st);
    else if(n==3)IsEmpty();
    else if(n==4)IsFull(m);
    else if(n==5)Peek();
    else if(n==6)view(st);
    else break;
    cout<<"\nEnter 1 to continue\n";
    cin>>op;
    if(op!=1)break;
    }
    return 0;

}