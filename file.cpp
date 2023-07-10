#include<bits/stdc++.h>
using namespace std;

#define min_balance 1000

class insufficientBalance{};
class AccountWork{
    private:
    long long accountNumber;
    string FName;
    string LName;
    float balance;
    static long long nextAccountNumber;
    public:
    AccountWork(){};
    AccountWork(string firstName,string lastName,float balance){
        FName = firstName;
        LName = lastName;
        nextAccountNumber++;
        accountNumber = nextAccountNumber;
        this->balance = balance;
    }
    static long long geteAccountNumber(){
        return nextAccountNumber;
    }
    static void setLastAccountChecker(long long accountNumber){
        nextAccountNumber = accountNumber;
    }
    string getFirstName(){
        return FName;
    }
    string getLastName(){
        return LName;
    }
    float getBalance(){
        return balance;
    }
    void depositMoney(float amount){
        balance += amount;
    }
    void withdrawMoney(float amount){
        if(balance-amount< min_balance)
            throw insufficientBalance();
        balance -= amount;
    }
    friend ofstream & operator << (ofstream &ofs,AccountWork &acc){
        ofs << acc.accountNumber<<endl;
        ofs << acc.FName<<endl;
        ofs << acc.LName<<endl;
        ofs << acc.balance<<endl;
        return ofs;
    }
    friend ifstream & operator >> (ifstream &ifs,AccountWork &acc){
        ifs >> acc.accountNumber;
        ifs >> acc.FName;
        ifs >> acc.LName;
        ifs >> acc.balance;
        return ifs;
    }
    friend ostream & operator << (ostream &os, AccountWork &acc){
        os << "First Name: " << acc.getFirstName()<<endl;
        os << "Last Name: " << acc.getLastName()<<endl;
        os << "Account Number: " << acc.geteAccountNumber()<<endl;
        os << "Balance: " << acc.getBalance()<<endl;
    }
};

long long AccountWork::nextAccountNumber=0;

class Bank{
    private:
    map<long long,AccountWork> accounts;
    public:
    Bank(){
        AccountWork account;
        ifstream inputfile;
        inputfile.open("Bank.data");
        if(!inputfile){
            return;
        }
        while(!inputfile.eof()){
            inputfile >> account;
            accounts.insert(pair<long long,AccountWork>(account.geteAccountNumber(),account));
        }
        AccountWork::setLastAccountChecker(account.geteAccountNumber());
        inputfile.close();
    };
    AccountWork OpenAccount(string fname,string lname,float balance){
        ofstream outfile;
        AccountWork account (fname,lname,balance);
        accounts.insert(pair<long long,AccountWork>(account.geteAccountNumber(),account));
        map<long long,AccountWork>:: iterator i;
        for(i=accounts.begin();i!=accounts.end();i++){
            outfile << i->second;
        }
        outfile.close();
        return account;
    }
    AccountWork CheckBalance(long long accountNumber){
        map<long long,AccountWork>::iterator itr = accounts.find(accountNumber);
        return itr->second; 
    }
    AccountWork DepositMoney(long long accountNumber,float amount){
        map<long long,AccountWork>:: iterator itr = accounts.find(accountNumber);
        itr->second.depositMoney(amount);
        return itr->second;
    }
    AccountWork withDrawMoney(long long accountNumber,float amount){
        map<long long,AccountWork>:: iterator itr = accounts.find(accountNumber);
        itr->second.withdrawMoney(amount);
        return itr->second;
    }
    void closeAccount(long long accountNumber){
        map<long long,AccountWork>:: iterator itr = accounts.find(accountNumber);
        cout<<"Account Deleted "<<itr->second;
        accounts.erase(accountNumber);
    }
    void showAllAccounts(){
        map<long long,AccountWork>:: iterator itr;
        for(itr = accounts.begin();itr!=accounts.end();itr++){
            cout<<itr->first<<endl<<itr->second;
        }
    }
    ~Bank(){
        ofstream outfile;
        outfile.open("Bank.data",ios::trunc);
        map<long long,AccountWork>:: iterator itr;
        for(itr = accounts.begin();itr!=accounts.end();itr++){
            outfile << itr->second;
        }
        outfile.close();
    }
};



int main(){
    Bank b;
    AccountWork acc;
    int n;
    string fname,lname;
    long long accountNumber;
    float balance;
    float amount;
    cout<<"OOPS BANK\n"<<endl;
    do{
        cout<<"Select one of the following options by typing number\n";
        cout<<"1. Open an account\n";
        cout<<"2. Balance Enquiry\n";
        cout<<"3. Deposit Money\n";
        cout<<"4. Withdraw Money\n";
        cout<<"5. Close account\n";
        cout<<"6. Show all accounts\n";
        cout<<"7. Quit\n";
        cin>>n;
        switch(n){
            case 1:
                cout<<"Enter first name: ";
                cin>>fname;
                cout<<"Enter lase name: ";
                cin>>lname;
                cout<<"Enter initial balance: ";
                cin>>balance;
                acc = b.OpenAccount(fname,lname,balance);
                cout<<"\nWe Welcome you to OOPS Bank family. 'Always in your service'\n";
                cout<<acc;
                break;
            case 2:
                cout<<"Enter account number: ";
                cin>>accountNumber;
                acc = b.CheckBalance(accountNumber);
                cout<<"\nYour account details are:\n"<<acc;
                break;
            case 3:
                cout<<"Enter Account Number";
                cin>>accountNumber;
                cout<<"Enter amount to be deposited: ";
                cin>>amount;
                acc = b.DepositMoney(accountNumber,amount);
                cout<<"\nAmount is deposited\n"<<acc;
                break;
            case 4:
                cout<<"Enter Account Number: ";
                cin>>accountNumber;
                cout<<"Enter amount to be withdrawn: ";
                cin>>amount;
                acc = b.withDrawMoney(accountNumber,amount);
                cout<<"\nAmount withdrawn\n"<<acc;
                break;
            case 5:
                cout<<"Enter account number";
                cin>>accountNumber;
                b.closeAccount(accountNumber);
                cout<<"\nAccount is closed\n"<<acc;
                break;
            case 6:
                b.showAllAccounts();
                break;
            case 7:
                break;
            default:
                cout<<"\nEnter correct choice";
                exit(0);
        }
    }
    while(n!=7);
    return 0;
}