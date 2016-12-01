

#include <iostream>
/* rand example: guess the number */
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
using namespace std;

int main ()
{
  int num;
  int estatura=150;
  int pierna=90;
  int pie=30;
  int brazo=60;
  int espalda=40;
  int craneo=50;
  int peso=55;
  int neg;
  /* initialize random seed: */
  srand (time(NULL));

  /* generate secret number between 1 and 10: */
  
  int i=0;
  int j=0;
  while(j<10000){
      while(i<1000){
	
	neg=rand()%2;
	if(neg==0) neg=-1;
	num=estatura+(rand()%50)*neg;
	cout << num<< " ";
	
	neg=rand()%2;
	if(neg==0) neg=-1;
	num=pierna+(rand()%30)*neg;
	cout << num<< " ";
	
	
	neg=rand()%2;
	if(neg==0) neg=-1;
	num=brazo+(rand()%30)*neg;
	cout << num<< " ";
	
	neg=rand()%2;
	if(neg==0) neg=-1;
	num=espalda+(rand()%20)*neg;
	cout << num<< " ";
	
	
	neg=rand()%2;
	if(neg==0) neg=-1;
	num=craneo+(rand()%15)*neg;
	cout << num<< " ";
	
	neg=rand()%2;
	if(neg==0) neg=-1;
	num=pie+(rand()%20)*neg;
	cout << num<< " ";
	
	neg=rand()%2;
	if(neg==0) neg=-1;
	num=peso+(rand()%40)*neg;
	cout << num<< endl;
	
	i++;

      }
      j++;
      i=0;
      cout << endl;
  }
  return 0;
}



