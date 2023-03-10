#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include "formulas.h"

using namespace std ;

struct Book{
  int book_id=0;
  string title ;
  int volume ;
  string author ; 
  int stock ; 
  string Category;
};

//function needed to read database of books

void book_read_file(Book *books ,int n ){
  ifstream fin;
 fin.open("Books.txt");
 for (int i=0 ; i<n ; i++){
    fin>>books[i].book_id ; 
    getline(fin , books[i].title, ';'  );
    books[i].title=books[i].title.substr(1 ,books[i].title.length());
    fin>>books[i].volume;
    getline(fin, books[i].author, ';'  ) ; 
    fin>>books[i].stock ;
    fin>>books[i].Category;
  }
  books[n].book_id=0;
  fin.close();
 
}

//function to list books with some graphical dessign

void list_books(Book *books , int n){
  change_c(33) ;
  cout<<"LIST OF BOOKS:"<<endl;
  col_def(); 
  change_c(44) ;
  cout<<"Book_id "<<setw(20)<<"Title"<<setw(20)<<"Volume"<<setw(15)<<"Author"<<setw(20)<<"      Stock     "<<"Category"<<endl; 
  col_def(); 
  for (int i=0 ; i<n ; i++){
   printf("%4d %35s %5d %23s %5d %15s \n", books[i].book_id, books[i].title.c_str(), books[i].volume, books[i].author.c_str() ,books[i].stock, books[i].Category.c_str() ) ;

  }
}



//function to add new books in stuct also in database
Book * book_adder(Book *books, int &n){
  Book *books1=new Book[n+1];
  for (int i=0; i<n  ; i++){
    books1[i]=books[i]; 
  }
  books1[n].book_id=n+1 ;
  change_c(32) ;
  cout<<"Title(Type ';' at the end): ";
  getline(cin , books1[n].title ,';'  );
  books1[n].title.erase(remove(books1[n].title.begin(), books1[n].title.end(), '\n'), books1[n].title.end());
  cout<<"Volume: ";
  cin>>books1[n].volume;
  cout<<"Author(Type ';' at the end): ";
  getline(cin , books1[n].author,';'   );
  books1[n].author.erase(remove(books1[n].author.begin(), books1[n].author.end(), '\n'), books1[n].author.end());
  cout<<"Stock: ";
  cin>>books1[n].stock;
  cout<<"Category: ";
  cin>>books1[n].Category;
  col_def(); 
  //Add on data base
  ofstream fin;
  fin.open ("Books.txt",ios::app);
  fin<<books1[n].book_id<<" "<<books1[n].title<<"; "<<books1[n].volume<<" "<<books1[n].author<<"; "<<books1[n].stock<<" "<<books1[n].Category<<endl;
  fin.close();
  

  n=n+1;


  return books1;
}


// imitation of previous function but taking as input only address 

void add_book(Book **books ,int &n){
   Book *book1 ;
   book1=*books;
  *books=book_adder(book1, n) ;
}



//recursion nr of elements in book structure ;

int count_books( Book *a, int i=0 ){
   if(a[i].book_id ==0) return i ;
   else return count_books(a ,i=i+1 );  
}


// function to display books according to given category
void book_filter (Book *books ,int n  ) {
  string a ; 
  int j=0 , c=0; 
  Book *filter_book = new Book[n] ;
  change_c(31) ;
  cout<<"Type book's category: ";
  col_def(); 
  cin>>a ; 
  while(c==0){
    for(int i=0 ;i<n ; i++){
       if (books[i].Category==a){
         filter_book[j]=books[i];
         j++ ; 
         c=1;
        }
    }
    if(c==0){
      change_c(31) ;
      cout<<"Type book's category again: ";
      col_def(); 
      cin>>a;
    }
    }
  if (c==1){
    change_c(33) ;
    cout<<"LIST OF BOOKS:"<<endl; 
    col_def(); 
    change_c(44) ;
    cout<<"Book_id "<<setw(20)<<"Title"<<setw(20)<<"Volume"<<setw(15)<<"Author"<<setw(20)<<"Stock       "<<"Category"<<endl;
    col_def();  
    for(int i=0 ; i<n ; i++){
      if(filter_book[i].book_id!=0){
          printf("%4d %35s %5d %20s %5d %15s \n", filter_book[i].book_id, filter_book[i].title.c_str(), filter_book[i].volume, filter_book[i].author.c_str() ,filter_book[i].stock, filter_book[i].Category.c_str() ) ;
       }
      }
    }
 
}



//function that return book id for a spcific title

int find_book_id(Book *books,int n){
   int c=0 ,a ;
   string s;
   change_c(33) ;
   cout<<"Type book title(Type ';' at the end): ";
   col_def();  
   getline(cin , s ,';'  );
   s.erase(remove(s.begin(), s.end(), '\n'), s.end());
   while (c==0){
      for (int i=0 ; i<n ; i++){
          if (books[i].title==s) { a=books[i].book_id ;
             c=1; 
             }
          }   
      if(c==0){
        change_c(31) ;
        cout<<"We don't have this book. Type book's title again: ";
        col_def();
        getline(cin , s ,';'  );
        s.erase(remove(s.begin(), s.end(), '\n'), s.end());
      }
   }
  return a ;
}



//function that update database in changes are made

void update_book_file(Book *books1){
  ofstream  fin ;
  fin.open ("Books.txt");
  for (int i=0 ; books1[i].book_id!=0 ;i++){
     fin<<books1[i].book_id<<" "<<books1[i].title<<"; "<<books1[i].volume<<" "<<books1[i].author<<"; "<<books1[i].stock<<" "<<books1[i].Category<<endl;
  }
  fin.close();
}

//also is same function as perevious but with others parameters (function overloading)

void update_book_file(Book *books1, int n){
  ofstream  fin ;
  fin.open ("Books.txt");
  for (int i=0 ; i<n ;i++){
     fin<<books1[i].book_id<<" "<<books1[i].title<<"; "<<books1[i].volume<<" "<<books1[i].author<<"; "<<books1[i].stock<<" "<<books1[i].Category<<endl;
  }
  fin.close();
}