#include <cmath>
#include "books_func.h"

using namespace std ;

struct Date{
  int year,month,day,hour,minute;
};


enum status{no_handed , handed}  ; 


struct Transaction{
  int tr_id=0 ; 
  int book_id ; 
  int client_id; 
  Date start_date , end_date;
  status s=no_handed; 
};

//turn data struct  into standart way to compare with the others 

long long date(Date d){
  long long time;
  time=d.year*pow(10 ,8) + d.month*pow(10,6) + d.day*pow(10,4) + d.hour*pow(10,2)+ d.minute ;
  return time ;
}


// function that take a string and set status of book into handed or not handed

void status_return( Transaction &transactions, string s){
  if(s=="handed") transactions.s=handed;
  else transactions.s=no_handed; ;
}


//take int and print handed or no_handed

string str_print(int a){
  
  if (a==1) return "handed" ;
  else return "no_handed" ;
}


//function that read transaction database and put into a array of structure

void read_file(Transaction * transactions, int n){
   ifstream fin;
   int i ;
   string str;
   fin.open("transactions.txt");
   for (int i=0 ; i<n ; i++){
      fin>>transactions[i].tr_id ; 
      fin>>transactions[i].book_id ;
      fin>>transactions[i].client_id ;
      fin>>transactions[i].start_date.year>>transactions[i].start_date.month>>transactions[i].start_date.day>>transactions[i].start_date.hour>>transactions[i].start_date.minute ;    
      fin>>transactions[i].end_date.year>>transactions[i].end_date.month>>transactions[i].end_date.day>>transactions[i].end_date.hour>>transactions[i].end_date.minute ; 
      fin>>str ;
      status_return(transactions[i], str);  
     
  }
  transactions[n].tr_id=0;
  fin.close();
}

// function that adds new transaction in structure also in database

Transaction *add_transaction(Book *books , Transaction * transactions )
{
 int  n=file_lines("Books.txt") ,m=file_lines("transactions.txt");
  Transaction * t1 =new Transaction[m+1];
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
  update_book_file(books);

  for(int i=0 ; i<m ; i++){
     t1[i]=transactions[i];
  }
  
  t1[m].tr_id=m+1 ;
  t1[m].book_id=book_id ;
  t1[m].client_id=m+1;
  change_c(33) ;
  cout<<"You should complete the Transaction: "<<endl;
  cout<<"Write current date(year/month/day/hour/minute): ";
  col_def();
  cin>>t1[m].start_date.year>>t1[m].start_date.month>>t1[m].start_date.day>>t1[m].start_date.hour>>t1[m].start_date.minute ;
  change_c(31) ;
  cout<<"You have one month time to hand your book."<<endl ; 
  col_def();
  t1[m].end_date=t1[m].start_date ;
  t1[m].end_date.month=t1[m].start_date.month + 1 ;
  t1[m].s=no_handed ;
  
  ofstream fout;
  fout.open("transactions.txt",ios::app);
  fout<<t1[m].tr_id<<" "<<t1[m].book_id<<" "<<t1[m].client_id<<" "<<t1[m].start_date.year<<" "<<t1[m].start_date.month<<" "<<t1[m].start_date.day<<" "<<t1[m].start_date.hour<<" "<<t1[m].start_date.minute<<" "<<t1[m].end_date.year<<" "<<t1[m].end_date.month<<" "<<t1[m].end_date.day<<" "<<t1[m].end_date.hour<<" "<<t1[m].end_date.minute<<" "<<str_print(t1[m].s)<<endl ;
  fout.close();

  t1[m+1].tr_id=0;

  return t1 ;
}


//function that updates database of transaction

void update_tr(Transaction * t1){
  ofstream fout;
  fout.open("transactions.txt");
  for(int i=0 ;t1[i].tr_id!=0 ;i++ ){
    fout<<t1[i].tr_id<<" "<<t1[i].book_id<<" "<<t1[i].client_id<<" "<<t1[i].start_date.year<<" "<<t1[i].start_date.month<<" "<<t1[i].start_date.day<<" "<<t1[i].start_date.hour<<" "<<t1[i].start_date.minute<<" "<<t1[i].end_date.year<<" "<<t1[i].end_date.month<<" "<<t1[i].end_date.day<<" "<<t1[i].end_date.hour<<" "<<t1[i].end_date.minute<<" "<<str_print(t1[i].s)<<endl ;
  }
  
  fout.close();
}


