// Elias Aleman
// G01020585
// Project 1 
// Lab Section 202

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 44
#define MAXKEY 22
#define MAXMESS 252


const char CHARSET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 .,;!-'?";

// Prints the Menu
void printMenu()
{
	printf("\n");
	printf("Menu: Please Enter a number(1-5) from the following options\n");
	printf("\n");
	printf("1.Enter a random number seed to generate the Tabula Recta\n");
	printf("2.Enter the Keyword\n");
	printf("3.Enter a message to encrypt\n");
	printf("4.Enter a message to decrypt\n");
	printf("5.Exit the program\n");
	printf("\n");
	printf("Enter your choice ----> ");

}

void  genRan(char tabula[][MAXLEN]);
void enterKey(char keyword[MAXKEY]);
void messEncrypt(char keyword[MAXKEY], char tabula[][MAXLEN]);
void messDecrypt(char keyword[MAXKEY], char tabula[][MAXLEN]);
int GetPosition(const char *str, const char c);


int main()
{
	char buffer[5];
	char input = ' ';
	char tabula[MAXLEN][MAXLEN];
	char keyword[MAXKEY];
	
	// Menu 
	while(input != '5')
	{
		printMenu();
		fgets(buffer,5,stdin);
		sscanf(buffer,"%c",&input);
		switch(input)
		{
			case '1':
				 genRan(tabula);
				break;
			case '2':
				enterKey(keyword);
				break;
			case '3':
				messEncrypt(keyword, tabula);
				break;
			case '4':
				messDecrypt(keyword, tabula);
				break;
			case '5':
				input = '5';
				printf("Exiting Program.......\n");		
				break;
			default:
				printf("ERROR, Please enter a Valid number (1-5) from the menu\n");
		}
	}

	return(0);
}



// function to generate Tabula Recta
void genRan(char  tabula[][MAXLEN])
{
	char gen[10];
	int num = 0;
	int idx;
	char temp;
	char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 .,;!-'?";
	

	printf("Enter any number to generate Tabula Recta ----> ");
	fgets(gen,10,stdin);
	sscanf(gen,"%d",&num);
	
	// random number seed	
	srandom(num);

	// Fisher - Yates Shuffle aglorithm from the specs
	for (int i = 44  - 1; i > 0; i--)
	{	
    		char temp;
    		idx = random()%(i+1);
    		temp = charset[idx];
    		charset[idx] = charset[i];
    		charset[i] = temp;
	}
	
	
	// This creates the tabula Recta
	for(int i = 0; i < MAXLEN; i++)
	{
		for( int x = 0; x< MAXLEN; x++)
		{
			tabula[i][x] = charset[x];		
		}
		
		temp = charset[0];

		for( int r = 1; r<= (MAXLEN - 1); r++)
		{
                        charset[r-1] = charset[r];
		}
		charset[43] = temp;		
	}

	printf("Tabula Recta generated\n");
	printf("\n");

	
}

//Function to enter Keyword
void enterKey(char keyword[MAXKEY])
{
	
	int i = 0;

	printf("Enter the keyword ----> ");
	fgets(keyword, MAXKEY, stdin);
	
	// Removes the new line character from keyword	
	strtok(keyword, "\n");		

	// Makes all characters in keyword Uppercase
	while(keyword[i])
	{
		keyword[i] = toupper(keyword[i]);
		i++;
	}	

	printf("The Keyword is:  %s \n", keyword);
}



// Function used to get position 
int GetPosition(const char *str, const char c)
{
  int retVal = -1;
  char *pos = strchr(str, c);

  if (pos != NULL)
  {
    retVal = pos - str;
  }

  return retVal;
}




// Function to enter message and encrypt
void  messEncrypt(char keyword[MAXKEY], char tabula[][MAXLEN])
{
	int X = 0;
	int Y = 0;
	int i = 0;
	int k = 0;

	char message[MAXMESS];
	
	// checks to see if tabula recta and keyword have been entered 
	// if not will print error message 
	if( tabula == NULL || keyword[0] == '\0')
	{
		printf("ERROR, You must have a generated Tabula Recta AND a Keyword to encript Message\n");
		return;
	}

	printf("Enter the message to Encrypt ----> ");
        fgets(message, MAXMESS, stdin);
        
	//removes new line character from message
        strtok(message, "\n");

		

	// makes all character in the message uppercase
	while(message[i])
        {
                message[i] = toupper(message[i]);
               i++;
        }
	
		
	
	// gets the positions, in the CHARSET,  of the current character of the message and keyword
	// Encrypts them using the positions and the tabula Recta 
	for (int w  = 0;w < strlen(message);w++)
	{
		 X = GetPosition(CHARSET, message[w]);

		while(keyword[k])
		{
			Y = GetPosition(CHARSET, keyword[k]);			

			message[w] = tabula[X][Y];

			if ( k == (strlen(keyword) - 1)){
				k = 0;
			}else{
				k++;
			}
			break;	
		}			
	}
	

	printf("The Encrpyted Message is :  %s" , message);

}

//Function to enter encrypted message and decrypts 
void messDecrypt(char keyword[MAXKEY], char tabula[][MAXLEN])
{

	int X = 0;
        int Y = 0;
        int i = 0;
        int k = 0;

	
	char dmessage[MAXMESS];

        // checks to see if tabula recta and keyword have been entered 
        // if not will print error message 
        if( tabula == NULL || keyword[0] == '\0')
        {
        	printf("ERROR, You must have a generated Tabula Recta AND a Keyword to decript Message\n");
                return;
	}
	
        printf("Enter the message to Decrypt ----> ");
        fgets(dmessage, MAXMESS, stdin);
	
	// Removes new line character        
        strtok(dmessage, "\n");

	// Makes all characters in Encrypted message uppercase if needed
	while(dmessage[i])
	{
		dmessage[i] = toupper(dmessage[i]);
		i++;
	}

	

	// This Decrypts the Message using the keyword and the tabula Recta and CHARSET
	for( int w = 0; w < strlen(dmessage);w++)
	{	
		while(keyword[k])
		{
			Y = GetPosition(CHARSET, keyword[k]);
			
			X = GetPosition(tabula[Y], dmessage[w]);
			
			dmessage[w] = CHARSET[X];

			if( k == (strlen(keyword) - 1))
			{
				k = 0;
			}else{
				k++;
			}
			break;
		}
	}

	printf("The Decrypted Message is : %s" , dmessage);
}
