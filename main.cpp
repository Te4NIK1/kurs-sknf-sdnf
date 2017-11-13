#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

string s; //
bool correct_input; // used for check input expression. If  == 0 - do notnig
string sknf, sdnf; //result functions
int kolX; // number of variables (need for make true-table)
string X[11];  //values of variables

string indstring(int ind)
{
	switch (ind) {
		case 1 : return "X1";
		case 2 : return "X2";
		case 3 : return "X3";
		case 4 : return "X4";
		case 5 : return "X5";
		case 6 : return "X6";
		case 7 : return "X7";
		case 8 : return "X8";
		case 9 : return "X9";
		case 10 : return "X10";
	}
	return "Error";
}

bool check(string input)
{
	for(int i = 0; i < input.size(); i++) {
		if (
		    input[i] != 'X' &&
		    input[i] != '-' && 
			input[i] != '>' && 
			input[i] != '<' && 
			input[i] != '^' && 
			input[i] != 'v' && 
			input[i] != ')' &&
			input[i] != '(' &&
			!isdigit(input[i])) {
			return 0;
		}
	}
	return 1;
}

int count(string input)
{
	size_t found;
	
	found = input.find("X10");
  	if (found != string::npos)
		return 10;	
		
	found = input.find("X9");
  	if (found != string::npos)
		return 9;	
		
	found = input.find("X8");
  	if (found != string::npos)
		return 8;	
		
	found = input.find("X7");
  	if (found != string::npos)
		return 7;	
		
	found = input.find("X6");
  	if (found != string::npos)
		return 6;	
		
	found = input.find("X5");
  	if (found != string::npos)
		return 5;	
		
	found = input.find("X4");
  	if (found != string::npos)
		return 4;	
		
	found = input.find("X3");
  	if (found != string::npos)
		return 3;	
		
	found = input.find("X2");
  	if (found != string::npos)
		return 2;	
		
	found = input.find("X1");
  	if (found != string::npos)
		return 1;
		
	return 0;		
}

string change(string input) // function for change variables to their values (smpl: x1 v x2 goes to 0v1)
{
	size_t found;
	for(;;) {
		found = input.find("X1");
		if (found != string::npos) {
			input.replace(found, 2, X[1]);	
			continue;
	    }
		found = input.find("X2");
		if (found != string::npos) {
			input.replace(found, 2, X[2]);	
			continue;
	    }
		found = input.find("X3");
		if (found != string::npos) {
			input.replace(found, 2, X[3]);	
			continue;
	    }
		found = input.find("X4");
		if (found != string::npos) {
			input.replace(found, 2, X[4]);	
			continue;
	    }
		found = input.find("X5");
		if (found != string::npos) {
			input.replace(found, 2, X[5]);	
			continue;
	    }
		found = input.find("X6");
		if (found != string::npos) {
			input.replace(found, 2, X[6]);	
			continue;
	    }
		found = input.find("X7");
		if (found != string::npos) {
			input.replace(found, 2, X[7]);	
			continue;
	    }
		found = input.find("X8");
		if (found != string::npos) {
			input.replace(found, 2, X[8]);	
			continue;
	    }
		found = input.find("X9");
		if (found != string::npos) {
			input.replace(found, 2, X[9]);	
			continue;
	    }
		found = input.find("X10");
		if (found != string::npos) {
			input.replace(found, 3, X[10]);	
			continue;
	    }
		break;
	}
	return input;
}

string parse(string input)
{
	size_t found;
	for(;;) {
		//cout <<input<<endl;
		//drop -
		found = input.find("-0");
  		if (found != string::npos) {
			input.replace(found, 2, "1");	
			continue;
		}
		
		found = input.find("-1");
  		if (found != string::npos) {
			input.replace(found, 2, "0");	
			continue;
		}
		
		//drop brackets
		found = input.find("(0)");
  		if (found != string::npos) {
			input.replace(found, 3, "0");	
			continue;
		}
		
		found = input.find("(1)");
  		if (found != string::npos) {
			input.replace(found, 3, "1");	
			continue;
		}
		
		//drop ->
		found = input.find("0->0");
  		if (found != string::npos) {
			input.replace(found, 4, "1");	
			continue;
		}
		
		found = input.find("0->1");
  		if (found != string::npos) {
			input.replace(found, 4, "1");	
			continue;
		}
		
		found = input.find("1->0");
  		if (found != string::npos) {
			input.replace(found, 4, "0");	
			continue;
		}
		
		found = input.find("1->1");
  		if (found != string::npos) {
			input.replace(found, 4, "1");	
			continue;
		}
		
		//drop <>
		found = input.find("0<>0");
  		if (found != string::npos) {
			input.replace(found, 4, "1");	
			continue;
		}
		
		found = input.find("0<>1");
  		if (found != string::npos) {
			input.replace(found, 4, "0");	
			continue;
		}
		
		found = input.find("1<>0");
  		if (found != string::npos) {
			input.replace(found, 4, "0");	
			continue;
		}
		
		found = input.find("1<>1");
  		if (found != string::npos) {
			input.replace(found, 4, "1");	
			continue;
		}

		//drop ^
		found = input.find("0^0");
  		if (found != string::npos) {
			input.replace(found, 3, "0");	
			continue;
		}
		
		found = input.find("0^1");
  		if (found != string::npos) {
			input.replace(found, 3, "0");	
			continue;
		}
		
		found = input.find("1^0");
  		if (found != string::npos) {
			input.replace(found, 3, "0");	
			continue;
		}
		
		found = input.find("1^1");
  		if (found != string::npos) {
			input.replace(found, 3, "1");	
			continue;
		}
		
		//drop v
		found = input.find("0v0");
  		if (found != string::npos) {
			input.replace(found, 3, "0");	
			continue;
		}
		
		found = input.find("0v1");
  		if (found != string::npos) {
			input.replace(found, 3, "1");	
			continue;
		}
		
		found = input.find("1v0");
  		if (found != string::npos) {
			input.replace(found, 3, "1");	
			continue;
		}
		
		found = input.find("1v1");
  		if (found != string::npos) {
			input.replace(found, 3, "1");	
			continue;
		}
		break;		
	}
	return input;	
}

void dfs(int ind)
{
	if(!correct_input)
		return;
		
	if(ind == kolX + 1) {
		//we got all x[i] values
		//cout <<"end dfs "<<change(s)<<endl;
		string result = parse(change(s));

		if (result != "0" && result != "1") {
			correct_input = 0;
			return;
		}
		
		if(result == "0") {
			if(sknf.size() > 0)
				sknf += " ^ ";
				
			sknf += "(";	
			for(int i = 1; i <= kolX; i++) { //(x1 v -x2 v x3)
				if(X[i] == "1")
					sknf += "-";
				sknf += indstring(i);
				if(i < kolX)
					sknf += " v ";
			}
			sknf += ")";	
		}
		
		if(result == "1") {
			if(sdnf.size() > 0)
				sdnf += " v ";
				
			sdnf += "(";	
			for (int i = 1; i <= kolX; i++) { //(-x1 ^ x2 v -x3)
				if(X[i] == "0")
					sdnf += "-";
				sdnf += indstring(i);
				if(i < kolX)
					sdnf += " ^ ";
			}
			sdnf += ")";	
		}
		return;
	}
	
	X[ind] = '0';
	dfs(ind + 1);
	
	X[ind] = '1';
	dfs(ind + 1);
}

int main(int argc, char** argv) {
	
	for(;;) {
		cout <<"F=";
		getline(cin, s);
		//s = "(X1 -> X2) ^ ((-X2 -> X3) -> -X1)";
	
		for(;;) { //drop all spaces
			size_t found = s.find(" ");
  			if (found != string::npos) {
				s.erase(found, 1);	
				continue;
			}
			break;
		}
	
		correct_input = check(s);
		kolX = count(s);
	
		sknf = "";
		sdnf = "";
		dfs(1);
	
		if(!correct_input)
			cout <<"Incorrect expression"<<endl;
		else {
			cout <<"SKNF: "<<sknf<<endl<<endl;
			cout <<"SDNF: "<<sdnf<<endl<<endl;
		}
	
		for(;;) {
			cout <<"Continue Y/N?"<<endl;
			getline(cin, s);
			if(s == "Y")
				break;
			if(s == "N")
				return 0;
		}
	}	
	return 0;
}
