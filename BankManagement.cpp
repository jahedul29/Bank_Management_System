#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

class bank{
    char name[20];
    int acc_no;
    int balance;
    int init_bal;
    char type[10];
    int age;
public:
    void create_account();      ///That will create an account
    void show_acc();            ///That will show all account information
    void deposit();              ///That will add given amount to main balance
    void withdraw();            ///That will deduct given amount from main balance
    int ret_balance();          ///That returns the final/main balance
    int ret_acc_no();           ///That returns the acc_no of a client
    char ret_acc_type();      ///That returns the acc_type of a client
};

void bank :: create_account()
{
    char d;
    cin.get(d);
    cout<<"Enter client Name : ";
    cin.getline(name,20);
    cout<<"Enter Account NO. : ";
    cin>>acc_no;
    cout<<"Enter age : ";
    cin>>age;
    cin.get(d);
    cout<<"Enter Account type : ";
    cin.getline(type,10);
    cout<<"Enter Initial deposit : ";
    cin>>init_bal;
    balance = init_bal;
    cout<<"\n";
}

void bank :: show_acc()
{
    cout<<"\t\tName\t : "<<name<<endl;
    cout<<"\t\tAccount NO : "<<acc_no<<endl;
    cout<<"\t\tAge\t : "<<age<<endl;
    cout<<"\t\tAccount type : "<<type<<endl;
    cout<<"\t\tBalance : "<<balance<<endl;
    cout<<endl;
}

void bank :: deposit()
{
    int x;
    cout<<"Enter the amount you want to deposit : ";
    cin>>x;
    cout<<"\tBalance Deposited"<<endl;
    cout<<"Balance before deposit : "<<balance<<endl;
    balance+=x;
    cout<<"Balance after deposit : "<<balance<<endl;
    cout<<endl;
}

void bank :: withdraw()
{
    int x;
    cout<<"Enter the amount you want to withdraw : ";
    cin>>x;
    cout<<"\tBalance Withdrawn"<<endl;
    cout<<"Balace before withdraw : "<<balance<<endl;
    balance-=x;
    cout<<"Balance after withdraw : "<<balance<<endl;
    cout<<endl;
}

int bank :: ret_balance()
{
    return balance;
}

int bank :: ret_acc_no()
{
    return acc_no;
}


void write_account()
{
    bank ob;
    ob.create_account();

    ofstream out;
    out.open("account.dat",ios::binary|ios::app);
    out.write((char *)&ob , sizeof(bank));
    out.close();
    cout<<"Account Successfully Created"<<endl;
    cout<<endl;
}

void check_info()
{
    bank ob;
    int t_acc_no;
    cout<<"Enter an account no. : ";
    cin>>t_acc_no;
    ifstream in;
    in.open("account.dat",ios::binary);
    if(!in) {cout<<"NO Account Existing\n"<<endl;return;}
    while(in.read((char *)&ob, sizeof(bank))){
        if(ob.ret_acc_no() == t_acc_no){
            ob.show_acc();
            in.close();
            return;
        }
    }
    in.close();
    cout<<"Sorry!! Account Not Found\n"<<endl;
}

void dep()
{
    bool flag = 0;
    bank ob;
    int t_acc_no;
    cout<<"Enter an account No. :";
    cin>>t_acc_no;
    fstream f;
    f.open("account.dat",ios::binary | ios::in | ios::out | ios::ate );
    f.seekg(0);
    f.read((char *)&ob, sizeof(ob));
    if(!f) {cout<<"No account Existing\n"<<endl;return;}
    while(!f.eof()){
        if(ob.ret_acc_no() == t_acc_no){
            ob.deposit();
            f.seekp(f.tellp()-sizeof(ob));
            f.write((char *)&ob, sizeof(ob));
            flag = 1;
        }
        f.read((char *)&ob, sizeof(ob));
    }
    f.close();
    if(flag == 0)cout<<"\nSorry!! Account Not Found\n"<<endl;
}

void with()
{
    bool flag = 0;
    bank ob;
    int t_acc_no;
    cout<<"Enter an account No. :";
    cin>>t_acc_no;
    fstream f;
    f.open("account.dat",ios::binary | ios::in | ios::out | ios::ate );
    f.seekg(0);
    f.read((char *)&ob, sizeof(ob));
    if(!f) {cout<<"No account Existing\n"<<endl;return;}
    while(!f.eof()){
        if(ob.ret_acc_no() == t_acc_no){
            ob.withdraw();
            f.seekp(f.tellp()-sizeof(ob));
            f.write((char *)&ob, sizeof(ob));
            flag = 1;
        }
        f.read((char *)&ob, sizeof(ob));
    }
    f.close();
    if(flag == 0)cout<<"\nSorry!! Account Not Found\n"<<endl;
}

void close_acc()
{
    bool flag = 0;
    bank ob;
    int t_acc_no;
    cout<<"Enter an account No. :";
    cin>>t_acc_no;
    ifstream in;
    ofstream out;
    in.open("account.dat",ios::binary);
    out.open("temp.dat",ios::binary);
    in.read((char *)&ob, sizeof(ob));
    if(!in) {cout<<"No account Existing\n"<<endl;return;}
    while(!in.eof()){
        if(ob.ret_acc_no() != t_acc_no){
            out.write((char *)&ob, sizeof(ob));
        }
        if(ob.ret_acc_no() == t_acc_no)
            flag = 1;
        in.read((char *)&ob, sizeof(ob));
    }
    in.close();
    out.close();
    if(flag == 0){cout<<"\nSorry!! Account Not Found"<<endl;return;}
    cout<<"\nAccount Closed\n"<<endl;
    remove("account.dat");
    rename("temp.dat","account.dat");
}

int menu()
{
    cout<<"\t(Enter from following\n\t option to perform)"<<endl;
        cout<<"\t\tMAIN MENU"<<endl;
        cout<<"\t1. Create Account"<<endl;
        cout<<"\t2. Deposit"<<endl;
        cout<<"\t3. Withdraw"<<endl;
        cout<<"\t4. Check info"<<endl;
        cout<<"\t5. Close Account"<<endl;
        cout<<"\t6. Exit"<<endl;
        cout<<endl;
        int ch;
        cout<<"Please Choose your option : ";
        cin>>ch;
        cout<<endl;
        return ch;
}

int main()
{
    char d;
    cout<<"Welcome to XYZ bank(Prepared by Md. Jahedul Hoque)"<<endl;
        while(1){
            switch(menu()){
                case 1:
                    system("cls");
                    write_account();
                    cin.get(d);
                    break;
                case 2:
                    system("cls");
                    dep();
                    cin.get(d);
                    break;
                case 3:
                    system("cls");
                    with();
                    cin.get(d);
                    break;
                case 4:
                    system("cls");
                    check_info();
                    cin.get(d);
                    break;
                case 5:
                    system("cls");
                    close_acc();
                    cin.get(d);
                    break;
                case 6:
                    system("cls");
                    cout<<"\n\t\t\tThank you"<<endl;
                    return 0;
                default:
                    system("cls");
                    cout<<"Enter a valid input"<<endl;
                    cin.get(d);
                    break;
            }
        cin.get(d);
        }
}

