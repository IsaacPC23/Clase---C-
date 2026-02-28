// Original version by: Roman Martinez

// g++ lexicalScanner.cpp -o lexicalScanner
// ./lexicalScanner

using namespace std;
#include <iostream>

//We define the transition matrix
//				              /*  :  */ : a.x.y :  _  :  0-9  : del : Other
int m_Int[4][7] = {{  		,     ,     1,    200,   200,   200,  200  },
				           {		  ,     ,     1,     2,    200,   100,  200  },
				           {			,     ,    200,   200,    3,    200,  200  },
				           {			,     ,    200,   200,    3,    100,  200  }};


//	Function to extract the column from the matrix that corresponds to the character
int getCol (char c){
	switch (c){
		case 'a':
		case 'x':
		case 'y': return 0; // letters a, x, y, column 0


		case '_': return 1; // underscore, column 1

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':	return 2;	// numbers 0 to 9, column 2

		case ' ':
		case '\0':  return 3;   // delimiters: space or end of string

		default:	return 4;	// "Other" column
	}
}

int main(){	
	// 	Read the string we are going to evaluate
	char in_string[100];
	cout << "Enter the string to evaluate: ";
	cin >> in_string;
	cout << in_string << endl;

	int i = 0;
	char aux;			//	aux : each character of in_string
	int state = 0; 	    //	We start in state 0
	int column = 0;

	while (state != 100 && state != 200 && i < 100)
	{	aux = in_string[i];					//	we will process characters one-by-one
		cout << "in_string["<<i << "]:\t" << aux << endl;

		column = getCol(aux);		   // We obtain the column that corresponds to the character
		state = m_Int[state][column];  // Given the state (row) and column, we know the transition
		
		if (state == 200)	{	cout << "Error!!";	break; }

		i++;
	}	
	//	SIf it ends in acceptance, it is valid
	if (state == 100)	{	cout << "It is a valid value";	}

	return 0;
}
