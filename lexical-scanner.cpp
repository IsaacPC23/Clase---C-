// Original version by: Roman Martinez

// g++ lexicalScanner.cpp -o lexicalScanner
// ./lexicalScanner

using namespace std;
#include <iostream>

//We define the transition matrix
//				     a.x.y :  _  :  0-9  : del :  /  :  *  : Other
int m_Int[7][7] = {{   1,    200,   200,   200,	  4,   200,   200  },
				   {   1,     2,    200,   200,	  4,   200,   200  },
				   {  200,   200,    3,    200,	  4,   200,   200  },
				   {  200,   200,    3,    100,	  4,   200,   200  },
				   {  200,   200,   200,   200,	 200,   5,    200  },
				   {   5,     5,     5,     5,	  5,    6,     5   },
				   {   5,     5,     5,     5,	 100,   6,     5   }};


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

	case '/':	return 4;	// slash, column 4

	case '*':	return 5;	// asterisk, column 5

	default:	return 6;	// any other character, column 6
	}
}

int main(){
	// 	Read the string we are going to evaluate
	char in_string[100];
	cout << "Enter the string to evaluate: ";
	cin.getline(in_string, 100);
	cout << in_string << endl;

	int i = 0;
	char aux;			//	aux : each character of in_string
	int state = 0; 	    //	We start in state 0
	int column = 0;
	int lastState = 0;
	int anchor = 0;
	bool inComment = false;

	while (state != 200 && i < 100)
	{	aux = in_string[i];					//	we will process characters one-by-one
		cout << "in_string["<<i << "]:\t" << aux << endl;

		column = getCol(aux);		   // We obtain the column that corresponds to the character
		lastState = state;
		state = m_Int[state][column];  // Given the state (row) and column, we know the transition

		if (state == 4 && !inComment) {anchor = lastState; inComment = true;}

		if (state == 100 && inComment) {state = anchor; inComment = false;}

		if (state == 200)	{	cout << "Error!!";	break; }

		if (aux == '\0') break;

		i++;
	}
	//	SIf it ends in acceptance, it is valid
	if (state == 100 && !inComment)	{	cout << "It is a valid value";	}

	return 0;
}
