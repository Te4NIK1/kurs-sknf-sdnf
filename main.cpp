#include <iostream>
#include <cstdio>

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
string s; //input expression
bool correct_input = 1; // used for check input expression. If  == 0 - do notnig
//result functions
string sknf = "";
string sdnf = "";

int kolX = 0; // number of variables (need for make true-table)
bool X[10];  //values of variables

string change(string input) // function for change variables to their values (smpl: x1 v x2 goes to 0v1)
{
	string result = "";
	for(int i=0; i<input.size();)
	{
		if(input[i]==' ') //drop all spaces (we dont need them)
		{
			i++;
			continue;
		}
		if(input[i]=='X') //change variable to current values
		{
			bool value = X[int(input[i+1])-'1'];
			result+=char( value+'0' );
			i+=2;
			continue;
		}	
		else
		{
			result+=input[i]; //if no variable - just add char to result
			i++;
		}
	}
	return result;
}

bool parse(string input)
{
	string result = "";
	for(bool do_something=1; do_something!=0;)
	{
		//cout <<"current: "<<input <<endl;
		
		do_something = 0;

		//drop -
		result = "";
		for(int i=0; i<input.size();) {
			if ( (i<input.size()-1) &&
			     (input[i]=='-')  &&
				 (input[i+1]=='0' || input[i+1]=='1')) // -X
			{
				do_something = 1;
				if(input[i+1]=='0')
					result+='1';
				else
					result+='0';	
				i+=2;
			}
			else {
				result += input[i];
				i++;
			}
		}
		if(do_something) {
			input = result;
			result = "";
			continue;
		}
		
		//drop brackets
		result = "";
		for(int i=0; i<input.size();) {
			if ( (i<input.size()-2) &&
			     (input[i]=='(') &&
			    ((input[i+1]=='0') || (input[i+1]=='1')) && 
				 (input[i+2]==')')) // (1) or (0)
			{
				do_something = 1;
				result += input[i+1];
				i+=3;
			}
			else
			{
				result += input[i];
				i++;
			}
		}
		if(do_something) goto exit;
		
		//drop ->
		result = "";
		for(int i=0; i<input.size();) {
			if ( (i<input.size()-3) &&
			     (input[i]=='0' || input[i]=='1')  &&
			     (input[i+1]=='-') && 
			     (input[i+2]=='>') && 
				 (input[i+3]=='0' || input[i+3]=='1')) // X->X
			{
				do_something = 1;
				if(input[i]=='1' && input[i+3]=='0')
					result+='0';
				else
					result+='1';	
				i+=4;
			}
			else {
				result += input[i];
				i++;
			}
		}
		if(do_something) goto exit;
		
		//drop <>
		result = "";
		for(int i=0; i<input.size();) {
			if ( (i<input.size()-3) &&
			     (input[i]=='0' || input[i]=='1')  &&
			     (input[i+1]=='<') && 
			     (input[i+2]=='>') && 
				 (input[i+3]=='0' || input[i+3]=='1')) // X<>X
			{
				do_something = 1;
				if(input[i]==input[i+3])
					result+='1';
				else
					result+='0';	
				i+=4;
			}
			else {
				result += input[i];
				i++;
			}
		}	
		if(do_something) goto exit;
		
		//drop ^
		result = "";
		for(int i=0; i<input.size();) {
			if ( (i<input.size()-2) &&
			     (input[i]=='0' || input[i]=='1')  &&
			     (input[i+1]=='^') && 
				 (input[i+2]=='0' || input[i+2]=='1')) // XvX
			{
				do_something = 1;
				if(input[i]=='1' && input[i+2]=='1')
					result+='1';
				else
					result+='0';	
				i+=3;
			}
			else {
				result += input[i];
				i++;
			}
		}	
		if(do_something) goto exit;
		
		//drop v
		result = "";
		for(int i=0; i<input.size();) {
			if ( (i<input.size()-2) &&
			     (input[i]=='0' || input[i]=='1')  &&
			     (input[i+1]=='v') && 
				 (input[i+2]=='0' || input[i+2]=='1')) // XvX
			{
				do_something = 1;
				if(input[i]=='0' && input[i+2]=='0')
					result+='0';
				else
					result+='1';	
				i+=3;
			}
			else {
				result += input[i];
				i++;
			}
		}
		if(do_something) goto exit;				
exit:
		input = result;
		result = "";
		if (!do_something)
			break;		
	}
	
	if(input.size()!=1) // result not 1 or 0
	{
		correct_input = 0;
		return 0;
	}	
	return (bool)(input[0]-'0');	
}

void dfs(int ind)
{
	if(!correct_input)
		return;
		
	if(ind==kolX)
	{
		//we got all x[i] values
		//cout <<"end dfs "<<change(s)<<endl;
		if (parse(change(s)) == 0) {
			if(sknf.size()>0)
				sknf+=" ^ ";
			sknf+="(";	
			for (int i=0; i<kolX; i++) //(x1 v -x2 v x3)
			{
				if(i>0)
					sknf+=" v ";
				if(X[i]==1)
					sknf+="-";
				sknf+="X";
				sknf+=(char)(i+'1');
			}
			sknf+=")";	
		}
		else {
			if(sdnf.size()>0)
				sdnf+=" v ";
			sdnf+="(";	
			for (int i=0; i<kolX; i++) //(-x1 ^ x2 v -x3)
			{
				if(i>0)
					sdnf+=" ^ ";
				if(X[i]==0)
					sdnf+="-";
				sdnf+="X";
				sdnf+=(char)(i+'1');
			}
			sdnf+=")";	
		}
		return;
	}
	X[ind]=0;
	dfs(ind+1);
	X[ind]=1;
	dfs(ind+1);
}

int main(int argc, char** argv) {
	
	cout <<"F=";
	getline(cin, s);
	//s = "(X1 -> X2) ^ ((-X2 -> X3) -> -X1)";
	
	//count variables
	for(int i=0; i<s.size(); i++)
	{
		if (!(
		    s[i]=='X' ||
		    s[i]=='-' || 
			s[i]=='>' || 
			s[i]=='<' || 
			s[i]!=' ' || 
			s[i]!=')' ||
			s[i]!='(' ||
			(s[i]>='1' && s[i]>='9')))
		{
			correct_input = 0;
			break;	
		}
		if(i<s.size()-1 && s[i]=='X')
		{
			if(s[i+1]<'1' || s[i+1]>'9')
				correct_input = 0;
			else	
				kolX = max(kolX, int(s[i+1]-'0'));
		}
	}
	dfs(0);
	if(!correct_input)
		cout <<"Incorrect expression"<<endl;
	else
	{
		cout <<"SKNF: "<<sknf<<endl<<endl;
		cout <<"SDNF: "<<sdnf<<endl<<endl;
	}
	cout <<"Press Enter to quit\n";
	getline(cin,s);
		
	return 0;
}
