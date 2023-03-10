#include "client_func.h"

using namespace std;

//dispaly title with a good looking dessign 

void Title(){
  cout<<endl<<endl;
  printf("\033[1;32m");
printf("     #           ###      ########         #######            ##         #######        #      #   \n") ;
wait(0.5);
printf("     #            #       #       #        #      #          #  #        #      #        #    #     \n") ;
wait(0.5);
printf("     #            #       #      #         #     #          #    #       #     #          #  #    \n") ;
wait(0.5);
printf("     #            #       #######          ######          ########      ######            #       \n") ;
wait(0.5);
printf("     #            #       #     #          #    #          #      #      #     #           #      \n");
wait(0.5);
printf("     #            #       #      #         #     #        #        #     #      #          #      \n");
wait(0.5);
printf("     ######      ###      ########         #      #      #          #    #       #         #      \n");
wait(0.5);
printf("\033[0m");
}

//function that set in work all client options

void client(){
    
    change_c(33) ;
    cout<<"1.Register and take a book."<<endl;
    cout<<"2.Lists of books."<<endl;
    cout<<"3.Check books according to categories."<<endl;
    cout<<"4.Hand your book."<<endl;
    cout<<"5.Exit"<<endl;
    int nr ;
    cout<<"Type a number:" ;
    col_def();
    cin>>nr;
    int n=file_lines("Books.txt") , m=file_lines("clients.txt") ,l=file_lines("transactions.txt");
    Client *clients =new Client[m] ;
    Transaction *transactions = new Transaction[m];
    Book *books= new Book[n] ;
    read_file(transactions, m);
    book_read_file(books ,n) ;
    client_read_file(clients ,m);
    while(nr>5){
          change_c(31) ;
          cout<<"Type one of given numbers: ";
          cin>>nr;
          col_def();
      }
    while(nr!=5){
        
      if(nr==1){
          clear();
          list_books(books, n) ;
          clients=client_adder(clients );
          transactions=add_transaction(books,  transactions);      
       }
      if(nr==2){
        clear();
        list_books(books, n) ;
      }  
      if (nr==3){
        clear();
        book_filter(books, n) ;
      }
      if (nr==4){
        clear();
        client_hand_book();
       }
  
      enter(); 
      enter();
      clear();
      change_c(33) ;
      cout<<"1.Register and take a book."<<endl;
      cout<<"2.Lists of books."<<endl;
      cout<<"3.Check books according to categories."<<endl;
      cout<<"4.Hand your book."<<endl;
      cout<<"5.Exit"<<endl;
      cout<<"Type a number:" ;
      col_def();
      cin>>nr;
      if(nr>5){
          change_c(31) ;
          cout<<"Type one of given numbers: ";
          cin>>nr;
          col_def();
      }
      
      
     }
    if(nr==5){
      change_c(32) ;
      cout<<"Thank you!"<<endl;
      col_def();
    } 
   


}




void pass_change(){
  string pass ,pass1 ;
  change_c(33) ;
  pass=getpass();
  cout<<"Type your new password:";
  col_def();
  pass=getpass();
  change_c(33) ;
  cout<<"Confirm your password:";
  col_def();
  pass1=getpass();
  while(pass!=pass1){
    change_c(33) ;
    cout<<"Write again password correctly:";
    col_def();
    pass1=getpass();
  }
  ofstream fout;
  fout.open("password.txt");
  fout<<pass;
  fout.close();
  change_c(32) ;
  cout<<"Your password has changed!"<<endl;
  col_def();
}


//function that set in work all administrator options

void administrator(){
   string pass ;
   ifstream fin;
   fin.open("password.txt");
   fin>>pass ;
   fin.close() ;
   string ans ;
   change_c(33) ;
   ans=getpass();
   cout<<"Type your password: " ;
   ans=getpass();
   col_def();

   while(ans!=pass){
     change_c(31) ;
     cout<<"Wrong password! Type again: " ;
     col_def();
     ans=getpass();
   }

   if(ans==pass){
     int nr;
     int n=file_lines("Books.txt") , m=file_lines("clients.txt") ,l=file_lines("transactions.txt");
     Client *clients =new Client[m] ;
     Transaction *transactions = new Transaction[m];
     Book *books= new Book[n] ;
     read_file(transactions, m);
     book_read_file(books ,n) ;
     client_read_file(clients ,m);


     cout<<endl;
     change_c(33) ;
     cout<<"1.List of all books."<<endl;
     cout<<"2.List of all clients."<<endl;
     cout<<"3.Add a book."<<endl;
     cout<<"4.Delete a client."<<endl;
     cout<<"5.Check clients deadline."<<endl;
     cout<<"6.Change password."<<endl;
     cout<<"7.Exit"<<endl;
     cout<<"Type a number:" ;
     col_def();
     cin>>nr ;

     while(nr>7){
          change_c(31) ;
          cout<<"Type one of given numbers: ";
          cin>>nr;
          col_def();
      }

     while(nr!=7){
       

       if(nr==1){
           clear();
           list_books(books, n) ;      
        }

       if(nr==2){
         clear();
         clients_list( clients  , books , transactions);
       }  

       if (nr==3){
         clear();
         list_books(books, n) ;
         add_book(&books, n);
       }

       if (nr==4){
         clear();
         delete_client(clients ,books ,transactions);
        }

       if (nr==5){
         clear();
         check_timeline (clients ,books ,transactions);
        }

       if(nr==6){
         clear();
         pass_change();
       }
         
       enter(); 
       enter();
       clear();
       change_c(33) ;
       cout<<"1.List of all books."<<endl;
       cout<<"2.List of all clients."<<endl;
       cout<<"3.Add a book."<<endl;
       cout<<"4.Delete a client."<<endl;
       cout<<"5.Check clients deadline."<<endl;
       cout<<"6.Change password."<<endl;
       cout<<"7.Exit"<<endl;
       cout<<"Type a number:" ;
       col_def();
       cin>>nr ;

       while(nr>7){
            change_c(31) ;
            cout<<"Type one of given numbers: ";
            cin>>nr;
            col_def();
           }
       }
      if(nr==7){
        change_c(32) ;
        cout<<"Thank you!"<<endl ;
        col_def();
      }
    } 
}
 


//the main  function that set in work the entire program

void library(){
  int nr ;
  Title();
  cout<<endl;
  change_c(33) ;
  cout<<setw(50)<<"WELCOME TO EPOKA LIBRARY!! "<<endl;
  enter();
  change_c(32) ;
  cout<<" 1.Client. "<<endl;
  cout<<" 2.Administrator. "<<endl;
  cout<<" 3.Exit. "<<endl<<endl;
  change_c(33) ;
  cout<<"Type a number: " ;
  col_def();
  cin>>nr ;
  while(nr>3){
            change_c(31) ;
            cout<<"Type one of given numbers: ";
            cin>>nr;
            col_def();
    }
  while(nr!=3){

    if(nr==1){
      clear();
      client();
    }

    if (nr==2) {
      clear();
      administrator();
    }
    enter(); 
    enter();
    clear();
    change_c(32) ;
    cout<<" 1.Client. "<<endl;
    cout<<" 2.Administrator. "<<endl;
    cout<<" 3.Exit. "<<endl<<endl;
    col_def();
    change_c(33) ;
    cout<<"Type a number: " ;
    col_def();
    cin>>nr ;
    while(nr>3){
            change_c(31) ;
            cout<<"Type one of given numbers: ";
            cin>>nr;
            col_def();
    }
  }

  if(nr==3){
    change_c(32) ;
    cout<<"Thank you!"<<endl ;
    col_def();
  }

}

