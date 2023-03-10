#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;



//Change color range of int  inputed 30 48
void change_c (int a)
 {printf("\033[1;%dm" ,a);}




// Return defoult color 
void col_def ()
 {printf("\033[0m");}


//function that count nr of lines in a given database file_lines


int file_lines( string file_name ){
 int n=0 ;
 ifstream fin(file_name) ;
 string a;
 while(getline(fin, a)){
   if (!fin.eof())
        n++;
  }
  return n ;
}



//delay function
void wait(double sec)
{   clock_t delay=sec * CLOCKS_PER_SEC; 
    clock_t start=clock();
    while(clock()-start<delay);  
}


//function that terminate if you press enter
void enter(){
    while( getchar() != '\n' );
}


//function that clear terminal entire page using ASNI terminal codes

void clear() {
    wait(0.5);
    std::cout << "\x1B[2J\x1B[H";
}


//without option to inmport getch() from conio.h header i created one that has same functionality 

int getch() {
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}



//function that get password uing asteriks

string getpass( bool show_asterisk=true)
{
  const char BACKSPACE=127;
  const char RETURN=10;

  string password;
  unsigned char ch=0;

  while((ch=getch())!=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                 cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else
         {
             password+=ch;
             if(show_asterisk)
                 cout <<'*';
         }
    }
  cout <<endl;
  return password;
}

