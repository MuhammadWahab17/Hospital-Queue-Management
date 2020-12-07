//
//  main.cpp
//  a4p3
//
//  Created by Ch Muhammad Wahab on 27/11/2020.
//  Copyright © 2020 Ch Muhammad Wahab. All rights reserved.
//

#include <iostream>
using namespace std;
struct paitent{
    int number;
    string name;
    int size;
    paitent(const int &st=0){
        name="";
        number=0;
        size=st;
    }
    void setname(){
        cout<<number++<<" People Waiting before!\n";
        if(number>size)
            throw "Slots Full";
        cin.ignore();
        cout<<"Enter name of paitent:";getline(cin,name);
    }
    void increment() {
        size++;
    }
    bool operator == (const int &v){
        return number==v;
    }
    friend ostream& operator<<(ostream& out,paitent& obj){
        cout<<obj.number<<":"<<obj.name<<endl;
        return out;
    }
};
template<class t>
struct node{
    t data;
    node<t> *next;
};
template<typename T>
class queue {
    node<T>* rear_idx;
    node<T>* front_idx;
public:
    queue() {
        rear_idx = front_idx = NULL;
    }
    void operator=(const queue<T>& s) {
        make_empty();
        node<T>* temp;
        temp = s.front_idx;
        while (temp != NULL) {
            push(temp->data);
            temp = temp->next;
        }
    }
    queue(const queue<T>& s) {
        rear_idx = front_idx = NULL;
        operator=(s);
    }
    ~queue() {
        make_empty();
    }
    bool empty() const {
        return rear_idx == NULL;
    }
    void push(const T& val) {
        if (full())
            throw("Queue Overflow!");
        node<T>* temp;
        temp = new node<T>;
        temp->data = val;
        temp->next = NULL;
        if (empty()) {
            rear_idx = temp;
            front_idx = rear_idx;
        }
        else {
            rear_idx->next = temp;
            rear_idx = temp;
        }
    }
    bool erase(const int& val) {
        if (front_idx == NULL)
            return false;
        node<T>* temp;
        temp = front_idx;
        if (temp->data == val) {
            front_idx = temp->next;
            delete temp;
            cout<<"Queue No "<<temp->data.number<<" has been removed!\n";
            return true;
        }
        while (temp->next != NULL) {
            if (temp->next->data == val) {
                node<T>* to_del;
                to_del = temp->next;
                temp->next = temp->next->next;
                delete to_del;
                cout<<"Queue No "<<to_del->data.number<<" has been removed!\n";
                return true;
            }
            temp = temp->next;
        }
        cout<<"Appointment slot doesn't exits\n";
        return false;
    }
    void pop() {
        if (empty())
            throw("Queue Underflow!");
        node<T>* temp;
        temp = front_idx;
        front_idx = front_idx->next;
        delete temp;
        if (front_idx == NULL)
            rear_idx = NULL;
    }
    T front() const {
        if (empty())
            throw("Queue is empty!");
        return front_idx->data;
    }
    bool full() const {
        node<T>* temp;
        temp = new node<T>;
        if (temp == NULL)
            return true;
        else {
            delete temp;
            return false;
        }
    }
    void make_empty() {
        while (!empty())
            pop();
    }
};
void display(queue<paitent> obj){
    if(obj.empty()){
        cout<<"No one waiting yet!\n";
    }
    while (!obj.empty()) {
        paitent ob=obj.front();
        cout<<ob;
        obj.pop();
    }
}
int main(int argc, const char * argv[]) {
    cout<<"Enter number of appointment slots:";
    int st;cin>>st;
    cout<<"Enter number of lab test slots:";
    int ls;cin>>ls;
    queue<paitent> checkup;
    paitent cp(st);
    queue<paitent> lab;
    paitent lb(ls);
    int exit=0,choice;
   
    while(!exit){
        cout<<"1:Book an appointment\n"
              "2:Add medical lab\n"
              "3:Cancel an appointment\n"
              "4:Remove medical lab\n"
              "5:Display appointment Queue\n"
              "6:Display medical lab Queue\n_";
        cin>>choice;
        try {
        switch (choice) {
            case 1:
                cp.setname();
                checkup.push(cp);
                cout<<"Appointment No "<<cp.number<<" has been booked for Mr/Mrs "<<cp.name<<endl;
                break;
            case 2:
                lb.setname();
                lab.push(lb);
                cout<<"Mr/Mrs "<<lb.name<<" can have lab test at number "<<lb.number<<endl;
                break;
            case 3:
                cout<<"Enter Appointment Number to be cancelled:";
                int num;cin>>num;
                checkup.erase(num);
                cp.increment();
                break;
            case 4:
                cout<<"Enter lab test Number to be cancelled:";
                int nm;cin>>nm;
                lab.erase(nm);
                lb.increment();
                break;
            case 5:
                cout<<"Appointment list:\n";
                display(checkup);
                break;
            case 6:
                cout<<"Medical Lab list:\n";
                display(lab);
                break;
            default:
                exit=1;
                break;
        }}
        catch(const char* msg){
            cout<<msg;
        }
    }
    
   

}
