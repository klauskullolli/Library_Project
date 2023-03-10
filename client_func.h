
#include "transaction_func.h"


using namespace std ;

struct Client{
  int client_id=0;
  string name,surname;
  string Address ;
  int nid ;
  string phone_no ;
  string email ; 
} ;

//function needed to read database of clients
void client_read_file(Client *clients ,int n ){
  ifstream fin;
  fin.open("clients.txt");
  for (int i=0 ; i<n ; i++){
    fin>>clients[i].client_id>>clients[i].name>>clients[i].surname ; 
    getline(fin, clients[i].Address, ';'  ) ; 
    fin>>clients[i].nid>>clients[i].phone_no>>clients[i].email ;
  }
  clients[n].client_id=0 ;
  fin.close();
}

//funnction that add new clients in struct also in database 

Client * client_adder( Client * clients ){
  int m=file_lines("clients.txt") ;
  Client *clients1= new Client[m+1] ;
  for (int i=0; i<m ; i++){
    clients1[i]=clients[i]; 
  }
  change_c(34) ;
  clients1[m].client_id=m+1 ;
  cout<<"Name: " ;
  cin>>clients1[m].name;
  cout<<"Surname: ";
  cin>>clients1[m].surname ;
  cout<<"Address(Type ';' at the end): " ;
  getline(cin , clients1[m].Address, ';'  );
  clients1[m].Address.erase(remove(clients1[m].Address.begin(),clients1[m].Address.end(), '\n'), clients1[m].Address.end());
  cout<<"nid:  ";
  cin>>clients1[m].nid ;
  cout<<"Phone number: ";
  cin>>clients1[m].phone_no ;
  cout<<"Email: " ;
  cin>>clients1[m].email ;
  col_def();

  ofstream kin;
  kin.open ("clients.txt",ios::app);
  kin<<clients1[m].client_id<<" "<<clients1[m].name<<" "<<clients1[m].surname<<" "<<clients1[m].Address<<"; "<<clients1[m].nid<<" "<<clients1[m].phone_no<<" "<<clients1[m].email<<endl;
  kin.close();
  
  return clients1 ;
  
}


//function that return client's struct index for a given name and surname of client  

int client_index(Client *clients, string name, string surname){
  int n=file_lines("clients.txt") , c=-1;
  for(int i=0 ; i<n ; i++){
    if(clients[i].name == name && clients[i].surname==surname){
      c=i ;
      break ;
    }
  }
  return c ;
}



// function that update clients database if changes are made

void update_clients(Client *clients){
  ofstream kin;
  kin.open ("clients.txt");
  for (int i=0 ; clients[i].client_id!=0 ; i++){
    kin<<clients[i].client_id<<" "<<clients[i].name<<" "<<clients[i].surname<<" "<<clients[i].Address<<"; "<<clients[i].nid<<" "<<clients[i].phone_no<<" "<<clients[i].email<<endl;

  }
  
  kin.close();
  
}


//function that delete a client from struct 

void delete_client(Client *clients, Book *books, Transaction *transactions){
  int n= file_lines("clients.txt")  , index=-1  , m=file_lines("Books.txt") ;
  if(n==0){
    change_c(31) ;
    cout<<"There is no client!"<<endl;
    col_def();
  } 
  else{
    string name , surname;
    change_c(32) ;
    cout<<"Name/Surname: ";
    col_def();
    cin>>name>>surname;
    while(index==-1){
      index=client_index(clients ,name, surname);
      if(index==-1) {
        change_c(32) ;
        cout<<"This client is not registered. Type again(Name/Surname): ";
        col_def();
        cin>>name>>surname;
      }     
      }

    int b_index=transactions[index].book_id-1;
    books[b_index].stock=books[b_index].stock + 1 ;

    for(int i=index ; i<n-1 ;i++ ){
        clients[i]=clients[i+1];
        clients[i].client_id=i+1;
        transactions[i]=transactions[i+1];
        transactions[i].tr_id=i+1;
        transactions[i].client_id=i+1;
      }
    clients[n-1].client_id=0;
    transactions[n-1].tr_id=0 ;
    update_clients(clients) ;
    update_tr(transactions);
    update_book_file(books) ;
  }
}


//function that allow to change enum from no_handed to handed

void client_hand_book(){
  int n=file_lines("Books.txt") , m=file_lines("clients.txt") ,l=file_lines("transactions.txt");
  Client *clients =new Client[m] ;
  Transaction *transactions = new Transaction[m];
  Book *books= new Book[n] ;
  read_file(transactions, m);
  book_read_file(books ,n) ;
  client_read_file(clients ,m);
  int index=-1 ;
  if(n==0){
    change_c(31) ;
    cout<<"There is no client!"<<endl;
    col_def();
  } 
  else{
    string name , surname;
    change_c(32) ;
    cout<<"Name/Surname: ";
    col_def();
    cin>>name>>surname;
    while(index==-1){
      index=client_index(clients ,name, surname);
      if(index==-1) {
        change_c(32) ;
        cout<<"This client is not registered. Type again(Name/Surname): ";
        col_def();
        cin>>name>>surname;
      }     
      }
    
    transactions[index].s=handed ;
    change_c(32) ;
    cout<<"Your book is handed."<<endl;
    col_def();
    int b_index=transactions[index].book_id-1;
    books[b_index].stock=books[b_index].stock + 1 ;

    string ans ;
    change_c(33) ;
    cout<<"Do you want to take another book?(Yes/No): ";
    col_def();
    cin>>ans ;
    if(ans=="Yes"){
      list_books(books ,n) ;
      int book_id = find_book_id(books ,n);
      if(books[book_id].stock==0){
          change_c(31) ;
          cout<<"we don't have more copy.Choose another book."<<endl; 
          col_def();
          book_id = find_book_id(books ,n);
          }
      else{
           books[book_id-1].stock= books[book_id-1].stock-1 ;
      }
      transactions[index].book_id=book_id ;
      transactions[index].s=no_handed ;
      update_tr(transactions);
      update_book_file(books, n) ;
    }
    else {
        change_c(33) ;
        cout<<"Thank you!"<<endl;
        col_def();
        update_tr(transactions);
        update_book_file(books, n) ;
       }
    }
   
}


//function to list clients with some graphical dessign

void clients_list( Client *clients  , Book *books , Transaction *transactions){
  int n=file_lines("clients.txt") ;
  if (n==0){
     change_c(31) ;
    cout<<"There is no client!"<<endl;
    col_def();
  }
  else{
    change_c(33) ;
    cout<<"LIST OF CLIENTS:"<<endl;
    col_def(); 
    change_c(46) ;
    cout<<"Client_id "<<setw(4)<<" Name " <<setw(10)<<" Surname "<<setw(20)<<" Address "<<setw(10)<<" Nid "<<setw(16)<<" Phone Nr. "<<setw(20)<<" Email "<<setw(25)<<" Book Title "<<setw(20)<<" Status"<<endl ; 
    col_def(); 
    for(int i=0 ; i<n ; i++){
      printf("%4d %10s %10s %21s %5d  %15s %27s %25s %12s \n", clients[i].client_id, clients[i].name.c_str(), clients[i].surname.c_str(), clients[i].Address.c_str() ,clients[i].nid, clients[i].phone_no.c_str(),clients[i].email.c_str(), books[transactions[i].book_id-1].title.c_str() ,str_print(transactions[i].s).c_str() ) ;

  }
  }
}


//function that check if book is not handed in time 

void check_timeline (Client *clients  , Book *books , Transaction *transactions){
   int n=file_lines("transactions.txt") ;
   Date d ;
   clients_list(clients ,books , transactions);
   if (n==0) return;
   else{
     int c=0 ;
     change_c(33) ;
     cout<<endl;
     cout<<"Type today date (year/month/day/hour/minute): " ;
     col_def();
     cin>>d.year>>d.month>>d.day>>d.hour>>d.minute ;
     for(int i=0 ; i<n ; i++){
       if(date(d)<date(transactions[i].end_date) && transactions[i].s==0){
         change_c(33) ;
         cout<<endl;
         cout<<clients[i].name<<"   "<<clients[i].surname<<"   " ;
         change_c(31) ;
         cout<<"Deadline is over and book isn't handed yet!"<<endl ;
         col_def();
         c=1 ;
        }  
      }
     if(c==0){
        change_c(32) ;
        cout<<"There is no client out of deadline"<<endl ;
        col_def();
     }

   }
}