#include<bits/stdc++.h>
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <string>
#define epsilon "eps"

using namespace std;

set <string> v;
set <string> sigma;

string S; // Start Symbol

vector <pair <string, vector<string> > > grammar_rules; 
/* Rules will be 
String -> Vector of Strings

E -> E + T
T -> T * F

LHS Single String, Right Hand side, vector of strings (Context Free Grammar)
*/


map < pair<string, string>, vector<string> > parsing_table;

/*
Pairing the non-terminal and terminal symbols which is indicated by <string, string>

vector<string> is the grammar rule strings that resides corresponding to the element of <string, string>

*/

void initialize_sig(){
	
	sigma.insert("$"); // inserting the right end marker
}

void initialize(set <string> V, set <string> SIG, string start_symbol){

	v = V;
	sigma = SIG;
	S = start_symbol;
}

int insert_new_rule(string left_sym, vector <string> right_strings){
	grammar_rules.push_back(make_pair(left_sym, right_strings));
	return 1; // if new grammar rule inserted
}
int input_parse_table(string row, string col, vector<string> right_symb){
	parsing_table.insert(make_pair(make_pair(row, col), right_symb));
	return 1; // if new rule is entered into the parsing table

}

// Example, Parse the string id * id + id
bool parse(vector<string> input_string){


	vector<string> parse_stack = {"$", S};
	input_string.push_back("$"); 

	vector<string>::iterator index = input_string.begin();
	while(!parse_stack.empty())
	{
		if(index  == input_string.end())
			return false; // end of string
		else{
			string head  = *(parse_stack.end() - 1);
			parse_stack.pop_back();

			cout << "Current Stack Head " << head << " :  " << "current symbol: " << *index << endl;
			if(*index == head){
				index += 1;
			}
			
			else if(parsing_table.find(make_pair(head,*index)) != parsing_table.end()){
                        vector<string> derivation = parsing_table[make_pair(head, *index)];
                        for(int i = derivation.size()-1; i >= 0; i--){
                            if(derivation[i] != epsilon)
                            parse_stack.push_back(derivation[i]);
                        }
                    } else{
                        return false;
                    }
		
	           }

	}
	return true;
}

int main(){
    initialize(set<string>{"E","E'","T","T'","F"}, set<string>{"id","+","*","(","$",")"}, "E");
    insert_new_rule("E", vector<string>{"T","E'"});
    insert_new_rule("E'", vector<string>{"+","T","E'"});
    insert_new_rule("E'", vector<string>{epsilon});
    insert_new_rule("T", vector<string>{"F","T'"});
    insert_new_rule("T'", vector<string>{"*","F","T'"});
    insert_new_rule("T'", vector<string>{epsilon});
    insert_new_rule("F", vector<string>{"(","E",")"});
    insert_new_rule("F", vector<string>{epsilon});
    input_parse_table("E", "id", vector<string>{"T","E'"});
    input_parse_table("T", "id", vector<string>{"F","T'"});
    input_parse_table("F", "id", vector<string>{"id"});
    input_parse_table("E'", "+", vector<strQing>{"+","T","E'"});
    input_parse_table("T'", "+", vector<string>{epsilon});
    input_parse_table("T'", "*", vector<string>{"*","F","T'"});
    input_parse_table("E", "(", vector<string>{"T","E'"});
    input_parse_table("T", "(", vector<string>{"F","T'"});
    input_parse_table("F", "(", vector<string>{"(","E",")"});
    input_parse_table("E'", ")", vector<string>{epsilon});
    input_parse_table("T'", ")", vector<string>{epsilon});
    input_parse_table("E'", "$", vector<string>{epsilon});
    input_parse_table("T'", "$", vector<string>{epsilon});
    if(parse(vector<string>{"id","+","id","*","id"})){
        cout << "Parsing successful! Correct syntax" << endl;
  } else{
        cout << "Parsing faild! Incorrect syntax" << endl;
    }
    return 0;

}
