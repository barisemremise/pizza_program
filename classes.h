/* @Author
Student Name: Barış Emre Mişe
Student ID: 150180002
Date: 20.03.2020 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>

using namespace std;

//Pizza class
class Pizza{
    private:
        string name;
        string size;
        string *ingredients;
        string crust_type;
        Pizza *next; 	//next pointer for Pizza linked list
    public:
        Pizza();
        Pizza(string size, string crust_type, int pizza_type);
        Pizza(Pizza&);
        string getname(){return name;}					//getter for name
        string getsize(){return size;}					//getter for size
        string getcrust(){return crust_type;}			//getter for crust type
        string* getingredients(){return ingredients;}	//getter for ingredients
        Pizza* getnext(){return next;}					//getter for next pointer
        void setnext(Pizza *ptr){next=ptr;}				//setter for next pointer
        ~Pizza();
};

//Order class
class Order{
    private:
        string customer;
        Pizza *phead;	//Pizza pointer for head of the Pizza linked list
        int *drinks;
        Order *next;	//Order pointer for Order linked list
    public:
        Order(string customer,Pizza *piz,int *drink);
        Order(string customer,Pizza *piz);
        void printorder() const;
        double getPrice();
        string getcustomer(){return customer;}		//getter for customer
        Order* getnext(){return next;}				//getter for next pointer
        void setnext(Order *ptr){next=ptr;}			//setter for next pointer
        ~Order();
};

//OrderList class
class OrderList{
    private:
        int n;
        Order *headorder;
    public:
        OrderList(){	//constructor for OrderList object
        headorder=NULL;
        n=0;}
        void setheadorder(Order *ord){headorder=ord;}	//setter for head of the Order linked list
        void mainmenu();								//a function for printing main menu								
        void takeOrder();
        void listOrders();
        void deliverOrders();
        ~OrderList();
};
