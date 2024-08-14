#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

//--------------------------------------
// CS421 HW2B Table-Driven Scanner
//--------------------------------------

// Complete this to fit the HW2B specification - look for **
// Must have the same types of tracing couts as my demo program.


// info on each DFA
struct info
{
  string name;  // token name
  int startstate;
  int finalstate;
};

info DFAs[4];     // store up to 4 dfas' start and final

int  TRS[10][4];  // store all trs's - states 0-9 and chars a b c d -- all dfas transitions are in here 

// ----- utility functions -----------------------

int readTables()
{  

   ifstream fin ("trs.txt", ios::in);
   ifstream fin2 ("dfas.txt", ios::in);
   // ** Read in the files into TRS and DFAs
	//read in TRS
	for(int row{}; row<10; ++row){
		for(int col{}; col<4; ++col){
			fin >> TRS[row][col];
		}
	}

	//read in DFAs
	int numDFAs{};
	while(fin2 >> DFAs[numDFAs].name >> DFAs[numDFAs].startstate >> DFAs[numDFAs].finalstate){
		++numDFAs;
	}
	
   // ** Return how many DFAs were read
	return numDFAs;
}

void displayTables(int numDFAs)
{
  // ** display DFAs nicely labeled
	cout << "\nDFAs\n";
	cout << "name\tstart\t\tfinal\n";

	for(int index{}; index<numDFAs; ++index){
		cout << DFAs[index].name << '\t' << DFAs[index].startstate << "\t\t\t" << DFAs[index].finalstate << '\n';
	}
	cout << endl;
	
  // ** display TRS nicely labeled
	cout << "TRS\n";
	cout << "cols\ta\tb\tc\td\n";
  cout << "rows\n";

  for(int row{}; row < 10; ++row){
    cout << "\t" << row << "\t";

    for(int col{}; col < 4; ++col){
      cout << TRS[row][col] << '\t';
    }
    cout << '\n';
  }
	cout << endl;
}

bool accept(info dfa, string word)
{
  // ** Does the dfa accept the word?
  // Start with the start state of the DFA and
  // look up the next state in TRS for each char in word.
  // At the end of the word, make sure you are in the 
  // final state of the DFA.
  // Use a formula to convert chars to TRS col numbers.

	const int startstate{dfa.startstate};
  const int finalstate{dfa.finalstate};

  // Start with the start state of the DFA and
  int currentstate{startstate};

  for(const char character : word){
    // Use a formula to convert chars to TRS col numbers.
    const int column{static_cast<int>(character - 'a')};

    // look up the next state in TRS for each char in word.
    const int nextstate{TRS[currentstate][column]};
		// if nextstate is -1, no transition takes place
    if(nextstate != -1) {
      // transitioning to the next state
      currentstate = nextstate;
    }
  }

  // At the end of the word, make sure you are in the
  // final state of the DFA.
  return currentstate == finalstate;
}


int main(){
  cout << "This is a table driven scanner. Needs trs.txt and dfas.txt." << endl;
  cout << "States are 0 to 9 and chars are a to d" << endl;

  int numDFA = readTables(); // how many DFAs were read
  displayTables(numDFA);     // DISPLAY TABLES
  cout << ".....done reading tables...." << endl;

  string word;
  while(true){ 
		cout << "@@Enter a string: " ;
    cin >> word;
      // ** try the DFAs one by one and see 
      //      if the word is accepted
      //      if so, display the word and the token name
      // ** if no DFA does, generate a lexical error message.

		// variable to check if any of the DFAs accepted word, which is initially false
		bool flag=false;
		cout<<numDFA<<endl;
		
  	for(int i=0;i<numDFA;i++){
			cout<<"Trying dfa "<<i<<"--------"<<endl;
      //acceptance status
			const bool status{accept(DFAs[i], word)}; 

      // word was accepted by this DFA
			if(accept(DFAs[i],word)){
				cout<<"Found token "<<DFAs[i].name<<endl;
				flag=true;
				break;
			}
    }
		// updates whether any of the DFAs accepted word
		if(!flag){
			cout<<"Lexical error!"<<endl;
		}

	cout << "do control-C to quit" << endl;
	}
}//the end
