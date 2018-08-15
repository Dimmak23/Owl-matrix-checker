/*

This code is solution for "owl matrix challenge".

Owl Matrix.

An Owl Matrix is a symmetric matrix that could be "folded" vertically
and horizontally in the middle and would generate four equal pieces.

For Example:
Input:
x  x  x  x
x  x  x  x
x  x  x  x
x  x  x  x
Output: true

Input:
a  b  b  a
c  c  c  c
c  c  c  c
a  b  b  a
Output: true

Write a program to check if the user input is an Owl Matrix or not.
_________________________________________________________________________________

Input instructions.

For made code work well you should:

1) Press line of characters, press ENTER button.

2) If you want to add another line repeat step 1).
Otherwise press SUBMIT button.
_________________________________________________________________________________
*/
#include <iostream>
#include <vector>

/*
Base class "storage" has private: messages for display, and
private method that replace action std::cout to simple pOL(message);

protected containers for derrived class: that keeps collected data
form user, boolean container "result" of research, integer container
"size" for actual size of square matrix, and also frequantly used
vector container - lines for temporary storage line of chars from
user data and counting rows/columns containers i and j;

public constructors, destructors, containers and methods: constructor
need to create a dialog with user and collect from him, destructor
simply send "bye message", boolean "approved" for validating input
from user, methods for send messages input validity or result, method
for showing collected data if it necessary, also created a virtual
empty method for overloading it in the derrived class and using that
overloaded method by the base class pointer to derrived class.
*/
class storage{

	// There is no need to share this containers and methods with derrived class
	// and main program
	private:
	// messages represent as strings
	std::string greetings = "\nPlease, enter you matrix line-by-line here:\n\n";
	std::string dataHeader = "\nStored data:\n";
	std::string correct = "\nThis input is correct.\n";
	std::string incorrect = "\nThis input is incorrect.\n";
	std::string owl = "\nYou enter an owl matrix.\n";
	std::string notowl = "\nYou enter not an owl matrix.\n";
	std::string bye = "\nThat's all for now, run again.\n";
	std::string gorizontal = "___________________________________________\n";

	// Method get message and print it
	void pOL(std::string message){
		std::cout << message;
	}

	// Derrived class need access to this containers
	protected:
	// data from user collected in the 2-dimensional vector
	std::vector<std::vector<char>> data;
	// Result of research, "true" - matrix is "owl"
	bool result = true;
	// size of the matrix collected in the integer variable
	int size = 0;
	// temporary vector storage for rows or columns 
	std::vector<char> lines;
	// temporary container for counting rows
	int i = 0;
	// temporary container for counting columns
	int j = 0;

	// Derrived class and main program need this containers and methods
	public:
	// variable show how correct user inputed data, "true" - correct
	bool approved = true;

	// Constructor collects data from user and validate it
	storage(){
		// temporary container for keeping line of chars from user
		std::string tempo;
		// temporary container for getting every single character
		// from user
		char temp;
		// set to zero temporary container for counting of matrix rows
		i = 0;
		// temporary container for additional chars in the line
		int k;
		// send greeting message to user
		pOL(greetings);
		// do-while need to get at least one line from user
		do {
			// erase contain of lines vector
			lines.erase(lines.begin(), lines.end());
			//
			k = 0;
			// get line from user
			std::getline(std::cin, tempo);
			// if line is epmty this input not valid
			if (tempo.empty()){
				approved = false;
				// store actual user input
				for (j=0; j<size; j++) tempo += ' ';
			}
			// if this first line set size to size of first line
			if (!i) size = tempo.size();
			// if this not first line and all privious inputs
			// was correct check if new line correct
			// new line would be incorrect if it size less or bigger
			// than size of first line
			else if (approved){
				approved = (size == tempo.size());
				// if line shorter fill it by empty chars
				if (size > tempo.size())
					for (j=0; j < (size-tempo.size()); j++) tempo += ' ';
				// if line bigger fill it by original chars
				// this feature provides by adding var k to size of Matrix
				if (size < tempo.size())
					for (k=1; k < tempo.size(); ) k++;
			}
			// get every single character and pass to char vector
			for (j=0; j < (size+k); j++){
				temp = tempo[j];
				lines.push_back(temp);
			}
			// pass char vector to 2-d vector data
			data.push_back(lines);
		// add int "1" to count container, check if all lines are
		// already collected, also if firsdt line was empty
		// (it is incorrect input) stop cycle, if not continue
		} while (++i < size);
	}

	// Method print corresponding message
	// about "correct" or "incorrect" input
	void validateInput(){
		if (approved) pOL(correct);
		else pOL(incorrect);
	}

	// Method show collected data from user
	void showData(){
		// print header of user data
		pOL(dataHeader);
		pOL(gorizontal);
		// 2-d vector also could be managed like 2-d array
		for (i=0; i<size; i++)
			for (j=0; (int)data[i][j] != 0; )
			{
				std::cout << data[i][j++];
				// if it was last character in the row
				// step to the next row
				if ((int)data[i][j] == 0) std::cout << '\n';
			}
		pOL(gorizontal);
	}

	// Virtual empty method for matrix research if base class pointer
	// will initilize it - because of keyword "virtual" derrived class
	// overload method researchMatix() will be used
	virtual void researchMatix(){}

	// Method print corresponding message being matrix owl or not
	void closeDialog(){
		if (result) pOL(owl);
		else pOL(notowl);
	}
	// Destructor simply send message to user asking run program again
	~storage(){
		pOL(bye);
	}
};

/*
Derrived class contain actual research method, and bunch of empty methods
validateInput(), showData() and closeDialog() that accessible from main
program. Some methods empty beacuse it is overload base non-virtual
methods so main program will call base methods.
*/
class researcher : public storage{
	// There is no need to share research line method outside of the class
	private:
	// Method for research single line of matrix is made outside of matrix
	// research for simplifing. Depending of choosing mode by boolean var
	// method research rows - "true" or columns - "false".
	void researchLines(bool mode){
		// Set row and colimn containers to zero
		i = 0;
		j = 0;
		// Set reference to row or column container demending of mode
		int *x = (mode)? &i:&j;
		int *y = (mode)? &j:&i;
		// run rows/columns one-by-one
		for (i=0; i<size; i++){
			// release contain of lines vector
			lines.erase(lines.begin(), lines.end());
			// pass row/column to vector
			for (j=0; j<size; j++) lines.push_back(data[*x][*y]);
			// create iterator for first and last element in the range
			std::vector<char>::iterator down = lines.begin();
			std::vector<char>::iterator up = lines.end()-1;
			// check sides element to the center
			// ther is no need to re-check after center element
			// also stop checking if matrix already appear not owl
			for (j=0; result && (j<(size/2)); j++)
				// using pointers to the elements
				// set result to "false" if matrix not owl
				if (*(down++) != *(up--)) result = false;
		}
	}	

	// This methods shared with main program
	public:
	// Empty method for calling bace class validateInput()
	void validateInput(){}
	// Method for showing data
	void showData(){}
	// Method for researching matrix
	void researchMatix(){
		// reserch every single row
		researchLines(true);
		// reserch every single column
		researchLines(false);
	}
	// Empty method for calling bace class closeDialog()
	void closeDialog(){}
};

// Main program starting point
int main(){
	// By creating base class storage pointer to derrived class
	// researcher contain called base class constructor for
	// starting dialog with user
	storage *entry = new researcher;
	// Returning to user inputed data
	entry -> showData();
	// Initilizing validation of input
	entry -> validateInput();
	// Only if input was correct program go to research
	if (entry -> approved){
		// Doing actual research
		entry -> researchMatix();
		// Sending result to user
		entry -> closeDialog();
	}
	// Finishing dialog by deleting base class pointer
	delete entry;
	return 0;
}