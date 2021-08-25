#include<stdio.h>
#include <iostream>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<fstream>              
#include<cstdlib>              
#include<string>   

#include "main.h"
using namespace std;

int main()
{
	//Reading the file 
    ifstream inf;
    string fileName;
    char cipher[2000];
    int items = 0;
 	int i,j,k,gcd,alpha,beta,numstr[100],numcipher[100],alphaInverse,m,n;
 	char str[45];
 	
 	//prompt the user to input file name
    cout << "Please input the name of the file you want to open: " << endl;
    cin >> fileName;
    inf.open(fileName.c_str());
    if (inf.fail())
    {
    	//prompt user if file does not exist
        cerr << "The file doesn't exist." << endl;
        return 0;
    }
    char nextCh;
    nextCh = inf.get();
    while (!inf.eof())
    {
        cipher[items] = toupper(nextCh);
        nextCh = inf.get();
        items++;
    }
    
    //coping the first 45 bytes of the file into a string 
    cout << "\n----------------------" << endl;
    cout << "CIPHERTEXT: " << endl;
    for (int x = 0; x < items; x++)
    {
        cout << cipher[x];
    }
    cout << "\n----------------------" << endl;
 	for(i=0,j=0;i<strlen(cipher);i++)
 	{
  		if(cipher[i]!=' ')
  		{
   			str[j]=toupper(cipher[i]);   
   			j++;
  		}
  		else
  		{
   			str[j]=' ';
   			j++;
 	 	}
 	}
 	str[j]='\0';
 	printf("Entered string is : %s \n",str);
 	
 	//performing the brute force in order to find intelligible text
 	for (alpha = 1; alpha < 26; alpha++)
 	{
 		if(alpha<1 || alpha>25)
	 	{
	  		printf("Alpha should lie in between 1 and 25\nSorry Try again !\n");
	  		continue;
	 	} 
	 	gcd=CalcGCD(alpha);
	 	if(gcd!=1)
	 	{
	  		printf("gcd(alpha,26)=1 but \n gcd(%d,26)=%d\nSorry Try again !\n",alpha,gcd);
	 	}
	 	for (beta = 0; beta < 26; beta++)
	 	{
 			printf("\n*******************************************************\n");

	 		if(beta<0 || beta>25)
		 	{
		  		printf("Beta value should lie between 0 and 25\nSorry Try again !\n");
		 	}

		 	for(i=0;i<strlen(str);i++)
		 	{
		  		if(str[i]!=' ')
		  		numstr[i]=str[i]-'A';
		  		else
		  		numstr[i]=-20;
		 	}
		 	printf("alpha = %d\n",alpha);
		 	printf("beta = %d\n",beta);
		 	alphaInverse=GetMultiplicativeInverse(alpha);
		 	printf("MI=%d\n",alphaInverse);
		    printf("Affine Cipher text is\n");   
		    for(i=0;i<strlen(str);i++)
		    {
		     	if(numstr[i]!=-20)
		     	{
		     		numcipher[i]=(alphaInverse*(numstr[i]-beta))%26;
		     		if(numcipher[i]<0)
		     		{
		      			numcipher[i]=numcipher[i]+26;
		     		}
		          	printf("%c",(numcipher[i]+'A'));         
		     	}
		     	else
		     	{
		          	printf(" ");      
		     	}
		    }
		    printf("\n*******************************************************\n");
			printf("\n");
		}
 	}
 	return 0;
}
int CalcGCD(int alpha)
{
 	int x;
   	int temp1=alpha;
   	int temp2=26;

    while(temp2!=0)
    {
        x=temp2;
        temp2=temp1%temp2;
        temp1=x;
    }
    return(temp1);
}
int GetMultiplicativeInverse(int alpha)
{
	int i,MI;
	for(i=1;i<=alpha;i++)
	{
	  	MI=((i*26)+1);
	  	if(MI%alpha==0)
	  	{
	   		break;
	  	}
	}
	MI=MI/alpha;
	return(MI);
}