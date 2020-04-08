/* @Author
Student Name: Barış Emre Mişe
Student ID: 150180002
Date: 29.03.2020 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>

#include "classes.h"

using namespace std;

//default Pizza constructor
Pizza::Pizza(){
    this->size="medium";
    this->crust_type="thin";
    ingredients=new string[1];
    ingredients[0]="mozarella";
    next=NULL;
}

//Pizza constructor with 3 parameters
Pizza::Pizza(string size, string crust_type, int pizza_type){
    this->size=size;
    this->crust_type=crust_type;
    switch (pizza_type)
    {
    case 1:
        name="Chicken Pizza";
        ingredients=new string[6];
        ingredients[0]="mozarella";
        ingredients[1]="chicken";
        ingredients[2]="mushroom";
        ingredients[3]="corn";
        ingredients[4]="onion";
        ingredients[5]="tomato";
        break;
    case 2:
        name="Broccoli Pizza";
        ingredients=new string[6];
        ingredients[0]="mozarella";
        ingredients[1]="broccoli";
        ingredients[2]="pepperoni";
        ingredients[3]="olive";
        ingredients[4]="corn";
        ingredients[5]="onion";
        break;
    case 3:
        name="Sausage Pizza";
        ingredients=new string[6];
        ingredients[0]="mozarella";
        ingredients[1]="sausage";
        ingredients[2]="tomato";
        ingredients[3]="olive";
        ingredients[4]="mushroom";
        ingredients[5]="corn";
        break;
    }
}

//copy constructor for Pizza object
Pizza::Pizza(Pizza &copy){
	
	int *ing=new int[6];
	for(int i=0;i<6;i++){
		ing[i]=0;
	}
    name=copy.getname();
    size=copy.getsize();
    crust_type=copy.getcrust();
    string *temp=copy.getingredients();
    this->ingredients=new string[6];
    for(int i=0;i<6;i++){
        this->ingredients[i]=temp[i];
    }
    cout<<"Please enter the number of the ingredients you want to remove from your pizza"<<endl;
    for(int i=0;i<6;i++){
        cout<<i+1<<". "<<temp[i]<<endl;
    }
    cout<<"Press 0 to save it."<<endl;
    int a=1;
    char x;
    while(a!=0){
		if(!(cin>>a)){                      //checking that the user has entered a integer
			cout<<"Invalid choice"<<endl;
			cin.clear();
			cin.ignore(1000,'\n');
			a=1;
			continue;
		}
    	if (cin.get(x)) {						//checking if user just entered integer
        	if(x != '\n'){
				cout<<"Invalid choice"<<endl;
        		cin.clear();
	    		cin.ignore(1000,'\n');
				continue;
			}
    	}
		if(a<7 && a>0)
			ing[a-1]++;
		else if(a==0)
			break;
		else
			cout<<"Invalid choice"<<endl;
	}
	for(int i=0;i<6;i++){
		
		if(ing[i]!=0)
			ingredients[i]="null";
		else
			ingredients[i]=temp[i];
	}
}

//destructor for Pizza object
Pizza::~Pizza(){
    delete[] ingredients;
    next=NULL;
}

//Order constructor with 3 parameters 
Order::Order(string customer,Pizza *piz,int *drink){
    this->customer=customer;
    phead=piz;
    drinks=drink;
    next=NULL;
}

//Order constructor with 2 parameters (without drink)
Order::Order(string customer,Pizza *piz){
    this->customer=customer;
    phead=piz;
    drinks=NULL;
    next=NULL;
}

//destructor for Order object
Order::~Order(){
    Pizza *ptr=phead;
    while(ptr){
        phead=ptr->getnext();
        delete ptr;
        ptr=phead;
    }
    delete[] drinks;
}

//destructor for OrderList object
OrderList::~OrderList(){
    Order *ptr=headorder;
    while(ptr){
        headorder=ptr->getnext();
        delete ptr;
        ptr=headorder;
    }
}

//taking the order from users
void OrderList::takeOrder(){
    
    int type;
    string name;
    string size;
    string crust;
    int amount;
    Pizza *ptraverse;
    Pizza *phead;
    Order *ord;

    cout<<"Pizza Menu"<<endl;
    cout<<"1. Chicken Pizza (mozarella, chicken, mushroom, corn, onion, tomato)"<<endl;
    cout<<"2. Broccoli Pizza (mozarella, broccoli, pepperoni, olive, corn, onion)"<<endl;
    cout<<"3. Sausage Pizza (mozarella, sausage, tomato, olive, mushroom, corn)"<<endl;
    cout<<"0. Back to main menu"<<endl;
    
	if(!(cin>>type)){						//checking that the user has entered a integer
		cout<<"Invalid choice"<<endl;
		cin.clear();
		cin.ignore(1000,'\n');
		takeOrder();
        return;
	}
	char x;
    if (cin.get(x)) {						//checking if user just entered integer
        if(x != '\n'){
			cout<<"Invalid choice"<<endl<<endl;
        	cin.clear();
	    	cin.ignore(1000,'\n');
			takeOrder();
			return;
		}
    }
	
    if(type==0){
    	cin.clear();
	    cin.ignore(1000,'\n');
        mainmenu();
        return;
    }
    else if(type>3 || type<0){
        cout << "You have entered an invalid choice,please try again." << endl;
        takeOrder();
        return;
    }
    cout<<"Select size: small (15TL), medium (20TL), big(25TL)"<<endl;
    cin>>size;
    while(size!="small" && size!="medium" && size!="big"){
    	cout<<"Invalid size, please try again: "<<endl;
    	cin>>size;
	}
    cout<<"Select crust type: thin, normal, thick"<<endl;
    cin>>crust;
    while(crust!="thin" && crust!="normal" && crust!="thick"){
    	cout<<"Invalid crust, please try again: "<<endl;
    	cin>>crust;
	}
    phead=new Pizza(size,crust,type);				//creating first pizza of the order
    ptraverse=phead;
    cout<<"Enter the amount: ";
    
    while(true){
    	if(!(cin>>amount)){							//checking that the user has entered a integer
		cout<<"Invalid amount, please try again: ";
		cin.clear();
		cin.ignore(1000,'\n');
		continue;
		} else if (cin.get(x)) {					//checking if user just entered integer
        	if(x != '\n'){
			cout<<"Invalid amount, please try again: ";
        	cin.clear();
	    	cin.ignore(1000,'\n');
			continue;			
			} else
				break;
    	}
	}
	
    if(amount>1){
        for(int i=1;i<amount;i++){					//creating a pizza linked list
			Pizza *ptr=new Pizza(*phead);			//creating a Pizza object with copy constructor
            ptraverse->setnext(ptr);
            ptraverse=ptraverse->getnext();
        }
    }
    cout<<"Please choose a drink:"<<endl;
    cout<<"0. no drink"<<endl;
    cout<<"1. cola 4TL"<<endl;
    cout<<"2. soda 2TL"<<endl;
    cout<<"3. ice tea 3 TL"<<endl;
    cout<<"4. fruit juice 3.5 TL"<<endl;
    cout<<"Press -1 for save your order"<<endl;
    int dr=1;
	char w;
	int *drink= new int[4];
    drink[0]=0;
    drink[1]=0;
    drink[2]=0;
    drink[3]=0;
	while(dr!=0 && dr!=-1){
		if(!(cin>>dr)){								//checking that the user has entered a integer
			cout<<"You have entered an invalid choice"<<endl;
			cin.clear();
			cin.ignore(1000,'\n');
			dr=1;
			continue;
		}
		if(cin.get(w)) {							//checking if user just entered integer
        	if(w != '\n'){
			cout<<"You have entered an invalid choice"<<endl;
        	cin.clear();
	    	cin.ignore(1000,'\n');
			continue;			
			}
    	}
    	if(dr>4 || dr<-1){
    		cout<<"You have entered an invalid choice"<<endl;
    		continue;
		}
		if(dr==-1 || dr==0)
			break;
    	
		if(dr<5 && dr>0)
			drink[dr-1]++;	
	}
    
	if(dr==-1){
        cout<<"Please enter your name:"<<endl;
        cin>>name;
        ord=new Order(name,phead,drink);		//calling Order constructor with 3 parameters
    }
    else if(dr==0){
        cout<<"Please enter your name:"<<endl;
        cin>>name;
        ord=new Order(name,phead);              //calling Order constructor with 2 parameters
    	delete[] drink;
	}
    if(n==0){									//adding first order to order list
       setheadorder(ord);
       n++;
    }
    else{										//adding an order to end of the order list
        Order *traverse;
        traverse=headorder;
        for(int i=1;i<n;i++){
            traverse=traverse->getnext();
        }
        traverse->setnext(ord);
        n++;
    }
    cout<<"Your order is saved"<<endl;
    ord->printorder();
    mainmenu();									//back to the main menu
}

//prints the main menu
void OrderList::mainmenu(){
	
    int c;
    cout<<"Welcome to Unicorn Pizza!"<<endl;
    cout<<"1. Add an order"<<endl;
    cout<<"2. List orders"<<endl;
    cout<<"3. Deliver order"<<endl;
    cout<<"4. Exit"<<endl;
    cout<<"Choose what to do: ";
    if(!(cin>>c)){								//checking that the user has entered a integer
		cout<<"Invalid choice"<<endl<<endl;
		cin.clear();
		cin.ignore(1000,'\n');
		mainmenu();
	}
	char a;
    if (cin.get(a)) {							//checking if user just entered integer
        if(a != '\n'){
			cout<<"Invalid choice"<<endl<<endl;
        	cin.clear();
	    	cin.ignore(1000,'\n');
			mainmenu();
			return;
		}
    }
    switch(c){
        case 1:
			takeOrder();						//calling takeOrder function for taking the order
			break;  
        case 2:
			listOrders();						//calling listOrder function for printing the orders
			mainmenu();
			break;
        case 3:
			deliverOrders();					//calling deliverOrders function for delete an order
			break;
        case 4:
			cout<<"Goodbye..."<<endl;
			break;
		default:
			cout<<"Invalid choice"<<endl<<endl;	
			mainmenu();							//if the user enters an invalid option, back to the main menu 
    }
}

//printing an order
void Order::printorder() const{
    
    Pizza *tra;
    tra=phead;

    cout<<"------------"<<endl;
    cout<<"Name: "<<customer<<endl<<endl;
    while(tra){
        cout<<tra->getname()<<"(";
        string *temp=tra->getingredients();
        for(int i=0;i<6;i++){
            if(temp[i]!="null")
                cout<<temp[i]<<", ";
        }
        cout<<")"<<endl;
        cout<<"size: "<<tra->getsize()<<", "<<"crust: "<<tra->getcrust()<<endl<<endl;
        tra=tra->getnext();
    }
    int *dr=drinks;
    if(dr){
        for(int i=0;i<4;i++){
            if(dr[i]!=0){
                cout<<dr[i];        
				switch(i){
					case 0:
						cout<<" cola, ";
						break;
					case 1:
						cout<<" soda, ";
						break;
					case 2:
						cout<<" ice tea, ";
						break;
					case 3:
						cout<<" fruit juice, ";
						break;
				}
			}
		}
	}
    cout<<endl;
    cout<<"------------"<<endl;
}

//printing all orders with calling printorder function 
void OrderList::listOrders(){

    Order *tra=headorder;
    if(!tra){
		cout<<"Order list is empty"<<endl<<endl;
	}
    for(int i=1;i<=n;i++){
        cout<<i<<endl;
        tra->printorder();
        tra=tra->getnext();
    }
}

//calculating price of the order
double Order::getPrice(){

    Pizza *tra=phead;
    double price=0.0;
    while(tra){
        if(tra->getsize()=="small"){
            price=price+15.0;
        }
        else if(tra->getsize()=="medium"){
            price=price+20.0;
        }
        else if(tra->getsize()=="big"){
            price=price+25.0;
        }
        tra=tra->getnext();
    }
    int *dr=drinks;
    if(dr){
        for(int i=0;i<4;i++){
            switch(i){
                case 0:
                    price=price+(dr[0]*4.0);
                    break;
                case 1:
                    price=price+(dr[1]*2.0);
                    break;
                case 2:
                    price=price+(dr[2]*3.0);
                    break;
                case 3:
                    price=price+(dr[3]*3.5);
                    break;
            }
        }
    }
    return price;
}

//deliver and delete an order
void OrderList::deliverOrders(){
    
    string name;
    Order *tra=headorder;
    Order *tail;
    listOrders();						//calling listOrders function to print all orders
    if(tra){							//if there are orders in the order list, delete an order
		cout<<"Please write the customer name in order to deliver his/her order: ";
		cin>>name;
		while(tra->getcustomer()!=name){
			tail=tra;
			if(tra->getnext())
				tra=tra->getnext();
			else{
				cout<<"Wrong name"<<endl<<endl;
				mainmenu();				//if the user enters wrong name, back to the main menu
				return;
			}	
		}
		cout<<endl<<"Following order is delivering..."<<endl;
		tra->printorder();
		double price=tra->getPrice();		//calling getPrice function for paying
		cout<<"Total price: "<<price<<"TL"<<endl;
		bool control=true;
		do{
			cout<<"Do you have a promotion code? (y/n)"<<endl;
			string q;
			cin>>q;
			while(!(q=="y") && !(q=="n")){
			cout<<"Invalid choice, try again"<<endl;
			cin>>q;
			}
			if(q=="y"){
				string a;
				cout<<"Please enter your code: ";
				getchar();
				getline(cin,a);
				string answer="I am a student";
				if(!(answer.compare(a))){
					price=(price*9.0)/10;
					cout<<"Discounted price: "<<price<<"TL"<<endl;
					control=false;
				}
				else{
					cout<<"Promotion code is not accepted."<<endl;
				}
			} else
				control=false;
		} 	 while(control);
		cout<<"The order is delivered successfully!"<<endl<<endl;
    
		if(tra==headorder){			//deleting the first order
			if(tra->getnext())
				headorder=tra->getnext();
			else
				headorder=NULL;
			delete tra;
		}
		else{						//deleting an order
			tail->setnext(tra->getnext());
			delete tra;
		}
		n--;
	}
	mainmenu();
}

int main(){
    OrderList orders;	//creating an OrderList object
    orders.mainmenu();  //calling mainmenu function

    return 0;
}
