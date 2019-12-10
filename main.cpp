#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <map>
using namespace std;
//classes
class syntaxAnalyzer {
public:
 enum State {
  Null, Statement, Assign, Expression, Factor, Term, Term_Prime, Expression_Prime, Opt_Declaration_List, Declaration,
  Declaration_List, Scan, IDs, Print, While, Condition, Relop, Empty, If, Return, Statement_List, Compound, Qualifier,
  Body, Parameter, Parameter_List, Opt_Parameter_List, Function, Function_Definitions, Opt_Function_Definitions, Rat19F
 };
 stack <string> cstate;
 stack <string> tokenstack;
 void showstack() {
  while (!tokenstack.empty()) {
   cout << tokenstack.top() << endl;
   tokenstack.pop();
  }
 }
 string curr_state() {
  return cstate.top();
 }
 void printcstates() {
  cout << "Length of cstates: " << cstate.size() << endl;
  while (!cstate.empty()) {
   cout << cstate.top() << endl;
   cstate.pop();
  }
  cout << '\n';
 }
 syntaxAnalyzer() {
  cstate.push(enumVect[Statement]);
  tokenstack.push("null");
 }
 string parse(string token, string lexeme) {
  string s;
  if (cstate.top() == enumVect[Statement]) {
   s = rule15(token, lexeme);
   tokenstack.push(token);
   return s;
  }
  if (cstate.top() == enumVect[Expression]) {
   s = rule25(token, lexeme);
   tokenstack.push(token);
   return s;
  }
  if (cstate.top() == enumVect[Assign]) {
   s = rule17(token, lexeme);
   tokenstack.push(token);
   return s;
  }
  if (cstate.top() == enumVect[Term_Prime]) {
   s = rule26P(token, lexeme);
   tokenstack.push(token);
   return s;
  }
  if (cstate.top() == enumVect[Term]) {
   s = rule26(token, lexeme);
   tokenstack.push(token);
   return s;
  }
  if (cstate.top() == enumVect[Expression_Prime]) {
   s = rule25P(token, lexeme);
   tokenstack.push(token);
   return s;
  }
  if (cstate.top() == enumVect[Scan]) {
   s = rule21(token, lexeme);
   tokenstack.push(token);
   return s;
  }
  if (cstate.top() == enumVect[IDs]) {
   s = rule13(token, lexeme);
   tokenstack.push(token);
   return s;
  } else {
   return "";
  }
 }
 string enumVect[31] = { "Null", "Statement", "Assign", "Expression", "Factor", "Term", "Term_Prime", "Expression_Prime", "Opt_Declaration_List",
  "Declaration", "Declaration_List", "Scan", "IDs", "Print", "While", "Condition", "Relop", "Empty", "If", "Return", "Statement_List", "Compound",
  "Qualifier", "Body", "Parameter", "Parameter_List", "Opt_Parameter_List", "Function", "Function_Definitions", "Opt_Function_Definitions", "Rat19F" };
private:
 string rule1(string token, string lexeme) {
  cstate.push(enumVect[Rat19F]);
  string s;
  s += "<Rat19F> -> ";
  s += rule2(token, lexeme);
  s += " %% ";
  s += rule10(token, lexeme);
  s += rule14(token, lexeme);
  s += " %% ";
  return s;
 }
 string rule2(string token, string lexeme) {
  cstate.push(enumVect[Opt_Function_Definitions]);
  string s;
  s += "<Opt Function Definitions> ->";
  if (!lexeme.empty()) {
   s += rule3(token, lexeme);
  } else {
   s += rule29(token, lexeme);
  }
  return s;
 }
 string rule3(string token, string lexeme) {
  cstate.push(enumVect[Function_Definitions]);
  string s;
  s += "<Function Definitions>";
  s += "-> ";
  s += rule4(token, lexeme);
  return s;
 }
 string rule4(string token, string lexeme) {
  cstate.push(enumVect[Function]);
  string s;
  s += "<Function> -> ";
  s += "function <Identifier> ( ";
  s += rule5(token, lexeme);
  s += ") " + rule10(token, lexeme);
  s += rule9(token, lexeme);
  return s;
 }
 string rule5(string token, string lexeme) {
  cstate.push(enumVect[Opt_Parameter_List]);
  string s;
  s += "<Opt Parameter List> ->";
  if (!lexeme.empty()) {
   s += rule6(token, lexeme);
  } else {
   s += rule29(token, lexeme);
  }
  return s;
 }
 string rule6(string token, string lexeme) {
  cstate.push(enumVect[Parameter_List]);
  string s;
  s += "<Parameter List>";
  s += "->";
  s += rule7(token, lexeme);
  return s;
 }
 string rule7(string token, string lexeme) {
  cstate.push(enumVect[Parameter]);
  string s;
  s += "<Parameter> ->";
  s += rule13(token, lexeme);
  s += rule8(token, lexeme);
  return s;
 }
 string rule8(string token, string lexeme) {
  cstate.push(enumVect[Qualifier]);
  string s;
  s += "\t<Qualifier> ->";
  if (lexeme == "int") {
   s += "int\n";
  } else if (lexeme == "bool") {
   s += "boolean\n";
  } else {
   s += "real\n";
  }
  return s;
 }
 string rule9(string token, string lexeme) {
  cstate.push(enumVect[Body]);
  return "<Body> -> { " + rule14(token, lexeme) + " }";
 }
 string rule10(string token, string lexeme) {
  cstate.push(enumVect[Opt_Declaration_List]);
  string s;
  s += "<Opt Declaration List>";
  s += "->";
  if (!lexeme.empty()) {
   s += rule11(token, lexeme);
  } else {
   s += rule29(token, lexeme);
  }
  return s;
 }
 string rule11(string token, string lexeme) {
  cstate.push(enumVect[Declaration_List]);
  string s;
  s += "<Declaration List>";
  s += "->";
  if (token == "identifier") {
   s += rule12(token, lexeme);
  } else {
   s += "\t";
  }
  return s;
 }
 string rule12(string token, string lexeme) {
  cstate.push(enumVect[Declaration]);
  string s;
  s += "<Declaration>";
  s += "->";
  if (lexeme == "int" || lexeme == "boolean" || lexeme == "real") {
   s += rule8(token, lexeme);
  }
  if (token == "identifier") {
   s += rule13(token, lexeme);
  }
  return s;
 }
 string rule13(string token, string lexeme) {
  string s;
  if (cstate.top() != enumVect[IDs]) {
   cstate.push(enumVect[IDs]);
   s += "\t<IDs>->";
  }
  if (token == "identifier") {
   cstate.pop();
   s += "<Identifier>\n";
  }
  if (token == "separator" && lexeme == ",") {
   cstate.pop();
   s += ",\n";
  }
  return s;
 }
 string rule14(string token, string lexeme) {
  cstate.push(enumVect[Statement_List]);
  string s;
  s += "<Statement List>";
  s += "->";
  s += rule15(token, lexeme);
  return s;
 }
 string rule15(string token, string lexeme) {
  string s;
  s += "\t<Statement>";
  if (token == "keyword" && lexeme == "compound") {
   s += "->";
   s += rule21(token, lexeme);
  }
  else if (token == "operator" && lexeme == "=") {
   s += "-> <Assign>\n";
   s += rule17(token, lexeme);
  }
  else if (token == "keyword" && lexeme == "if") {
   s += rule18(token, lexeme);
  }
  else if (token == "keyword" && lexeme == "return") {
   s += rule19(token, lexeme);
  }
  else if (token == "keyword" && lexeme == "print") {
   s += rule20(token, lexeme);
  }
  else if (token == "keyword" && lexeme == "while") {
   s += rule22(token, lexeme);
  } else {
   s += "\n";
  }
  return s;
 }
 string rule16(string token, string lexeme) {
  cstate.push(enumVect[Compound]);
  string s;
  s += "<Compound>";
  s += "->";
  s += "{ ";
  s += rule14(token, lexeme);
  s += "}";
  return s;
 }
 string rule17(string token, string lexeme) {
  cstate.push(enumVect[Assign]);
  if (tokenstack.top() != "operator" && token == "identifier") {
   string s;
   s += "<Assign>";
   s += "\n\t<Assign>-> <Identifier> = <Expression>\n";
   return s;
  }
  if (token == "operator" && lexeme == "=") {
   return "";
  }if (tokenstack.top() == "operator") {
   return rule25(token, lexeme);
  }
  else if (lexeme == ";") {
   cstate.pop();
   return "";
  } else {
   return "";
  }
 }
 string rule18(string token, string lexeme) {
  cstate.push(enumVect[If]);
  string s;
  if (token == "keyword" && lexeme == "if") {
   s += "if (" + rule23(token, lexeme) + ") " + rule15(token, lexeme) + " fi";
  } else {
   s += "if (" + rule23(token, lexeme) + ") " + rule15(token, lexeme);
   s += " otherwise " + rule15(token, lexeme) + " fi";
  }
  return s;
 }
 string rule19(string token, string lexeme) {
  cstate.push(enumVect[Return]);
  string s;
  s += "<Return>-> ";
  if (lexeme.size() > 7) {
   s += "return" + rule25(token, lexeme) + ";";
  } else {
   s += "return;";
  }
  return s;
 }
 string rule20(string token, string lexeme) {
  cstate.push(enumVect[Print]);
  string s;
  s += "<Print> -> put(" + rule25(token, lexeme) + ");";
  return s;
 }
 string rule21(string token, string lexeme) {
  string s;
  if (cstate.top() != enumVect[Scan]) {
   cstate.push(enumVect[Scan]);
   s += "<Scan>\n";
   s += "\t<Scan>->get(<IDs>);\n";
  }
  if (token == "keyword" && lexeme == "get") {
   s += "";
  }
  if (token == "separator" && lexeme == "(") {
   s += "";
  }
  if (token == "identifier" || token == "separator" && lexeme == ",") {
   s += rule13(token, lexeme);
  }
  if (token == "separator" && lexeme == ")") {
   s += "";
  }
  if (token == "separator" && lexeme == ";") {
   s += "\n";
   cstate.pop();
  }
  return s;
 }
 string rule22(string token, string lexeme) {
  cstate.push(enumVect[While]);
  string s;
  s += "<While>->(" + rule23(token, lexeme) + ")<Statement>";
  return s;
 }
 string rule23(string token, string lexeme) {
  cstate.push(enumVect[Condition]);
  string s;
  s += "<Condition>->" + rule25(token, lexeme) + "<Relop>" + rule25(token, lexeme);
  return s;
 }
 string rule24(string token, string lexeme) {
  cstate.push(enumVect[Relop]);
  string s;
  if (lexeme == "==") {
   s += "==";
  }
  else if (lexeme == "/=") {
   s += "/=";
  }
  else if (lexeme == ">") {
   s += ">";
  }
  else if (lexeme == "<") {
   s += "<";
  }
  else if (lexeme == "=>") {
   s += "=>";
  }
  else if (lexeme == "<=") {
   s += "<=";
  }
  return s;
 }
 string rule25(string token, string lexeme) {
  string s;
  if (cstate.top() != enumVect[Expression]) {
   cstate.push(enumVect[Expression]);
  }if (token != "operator" && token != "separator") {
   s += "\t<Expression>-><Term><Expression Prime>\n";
   s += rule26(token, lexeme);
   return s;
  } else {
   cstate.pop();
   s += rule25P(token, lexeme);
   return s;
  }
 }
 string rule25P(string token, string lexeme) {
  string s;
  if (cstate.top() != enumVect[Expression_Prime]) {
   cstate.push(enumVect[Expression_Prime]);
   s += "\t<Expression Prime>->";
  }
  if (lexeme == "+") {
   s += "+<Term><Expression_Prime>\n";
  }if (lexeme == "-") {
   s += "-<Term><Expression_Prime>\n";
  }if (token == "identifier") {
   s += rule26(token, lexeme);
  }if (token == "separator") {
   cstate.pop();
   s += "epsilon\n";
   s += rule17(token, lexeme);
  }
  return s;
 }
 string rule26(string token, string lexeme) {
  if (cstate.top() != enumVect[Term]) {
   cstate.push(enumVect[Term]);
  }if (token != "operator" && token != "separator") {
   string s;
   s += "\t<Term>-> <Factor> <Term Prime>\n";
   s += rule27(token, lexeme);
   return s;
  } else {
   cstate.pop();
   return rule26P(token, lexeme);
  }
 }
 string rule26P(string token, string lexeme) {
  string s;
  s += "\t<Term Prime>->";
  if (lexeme != "*" && lexeme != "/") {
   cstate.pop();
   s += "epsilon\n";
   s += rule25(token, lexeme);
  }
  else if (lexeme == "*") {
   s += "*<Factor><Term>\n";
  }
  else if (lexeme == "/") {
   s += "/<Factor><Term>\n";
  }
  else if (token == "identifier") {
   s += rule26(token, lexeme);
  }
  return s;
 }
 string rule27(string token, string lexeme) {
  if (cstate.top() != enumVect[Factor]) {
   cstate.push(enumVect[Factor]);
  }
  if (lexeme == "-") {
   return "";
  }
  string s;
  s += "\t<Factor>->";
  cstate.pop();
  s += rule28(token, lexeme);
  return s;
 }
 string rule28(string token, string lexeme) {
  if (token == "identifier") {
   return "<Identifier>\n";
  }if (token == "integer") {
   return "<Integer>\n";
  }
  return 0;
 }
 string rule29(string token, string lexeme) {
  cstate.push(enumVect[Empty]);
  return "ε";
 }
};
struct values {
 int address;
 string type, op;
};
struct inst {
 int address;
 string op;
 int oprnd;
};
class symboltable {
public:
 void add(string id) {
  values v;
  v.address = curr_addr;
  v.type = "integer";
  symtable[id] = v;
  curr_addr++;
 }
 bool exists(string id) {
  if (symtable.count(id) > 0) {
   return true;
  } else {
   return false;
  }
 }
 int getaddr(string id) {
  return symtable[id].address;
 }
 void displaymap() {
  map<string, values>::iterator it;
  for (it = symtable.begin(); it != symtable.end(); it++) {
   cout << "Key: " << it->first << endl;
   cout << "Address: " << it->second.address << endl;
   cout << "Type: " << it->second.type << endl;
  }
 }
 map<string, values> getTable() {
  return symtable;
 }
private:
 int curr_addr = 5000;
 map<string, values> symtable;
};
//initializations
int instr_address = 1, global_index;
const vector<string> STATES = { "keyword", "identifier", "separator", "operator", "real", "integer", "Error state" };
const vector<string> KEYWORDS = { "int", "float", "boolean", "if", "else", "then","get", "put", "while", "for", "return", "fi" };
const vector<string> SEPARATORS = { "'", "(", ")", "[", "]", "{", "}", ",", ".", ":", ";", "!" };
const vector<string> OPERATORS = { "*", "+", "-", "==", "/=", ">", "<", "=>", "<=", "=" };
void A();
void E();
void T();
void E_prime();
void T_prime();
void F();
void gen_instr(string, int);
void displayTable();
bool fsmIdentifier(string);
bool fsmInteger(string);
bool fsmReal(string);
void output(vector<string>);
int lexer(string);
syntaxAnalyzer sa;
symboltable st;
map<int, inst> instr_table;
string temp, global_token, global_tstate, global_lexeme, ins_output[1000] = { "" };
vector<string> parsedList;
vector<string> parse(string);
string readFile(string);
//functions
void output(vector<string> tList) {
 ofstream outfile;
 stringstream ss;
 outfile.open("output.txt");
 ss << "Token \t\t\t\t Lexemes\n";
 ss << "-----------------------------------------\n";
 for (int i = 0; i < tList.size(); i++) {
  string lexeme = tList[i];
  string token = STATES[lexer(lexeme)];
  global_token = token;
  global_lexeme = lexeme;
  global_tstate = lexer(lexeme);
  int tstate = lexer(lexeme);
  global_index = i;
  if (token == "identifier") {
   A();
  }
  ss << "Token: " << token << setw(24) << "Lexeme: " << lexeme << '\n';
  ss << sa.parse(token, lexeme);
  if (token == "identifier" && !st.exists(lexeme)) {
   st.add(lexeme);
  }
 }
 outfile << ss.str();
 outfile << "\nINSTRUCTION TABLE (without nil oprnds)" << endl;
 map<int, inst>::iterator it;
 for (it = instr_table.begin(); it != instr_table.end(); it++) {
  if (it->second.oprnd == 0) {
   continue;
  } else {
   outfile << "Address: " << it->second.address << endl;
   outfile << "Op: " << it->second.op << endl;
   outfile << "Operand: " << it->second.oprnd << endl;
  }
 }
 outfile << "\nSYMBOL TABLE" << endl;
 map<string, values> tempMap = st.getTable();
 map<string, values>::iterator itr;
 for (itr = tempMap.begin(); itr != tempMap.end(); itr++) {
  if (itr->first == "identifier") {
   continue;
  } else {
   outfile << "Key: " << itr->first << endl;
   outfile << "Address: " << itr->second.address << endl;
   outfile << "Type: " << itr->second.type << endl;
  }
 }
 outfile << "\nASSEMBLY INSTRUCTIONS" << endl;
 for (int i = 0; i < 1000; i++) {
  if (ins_output[i] != "") {
   outfile << ins_output[i] << endl;
  }
 }
 outfile.close();
}
bool fsmIdentifier(string value) {
 if (isalpha(value.at(0))) {
  for (int i = 0; i < value.length(); i++) {
   if (!isalpha(value.at(i)) && !isdigit(value.at(i)) && (int)value.at(i) != 95) {
    return false;
   }
  }
  return true;
 }
 return 0;
}
bool fsmInteger(string value) {
 for (int i = 0; i < value.length(); i++) {
  if (!isdigit(value.at(i))) {
   return false;
  }
 }
 return true;
}
bool fsmReal(string value) {
 bool period = false;
 int pcount = 0;
 if (isdigit(value.at(0))) {
  for (int i = 0; i < value.length(); i++) {
   if ((int)value.at(i) == 46 && i != (value.length() - 1)) {
    period = true;
    pcount++;
   } else if (!isdigit(value.at(i))) {
    return false;
   }
  }
  if (pcount == 1 && period) {
   return true;
  }
 }
 return 0;
}
int lexer(string token) {
 int token_state = 6;
 if (find(KEYWORDS.begin(), KEYWORDS.end(), token) != KEYWORDS.end()) {
  token_state = 0;
 }
 else if (fsmIdentifier(token)) {
  token_state = 1;
 }
 else if (find(SEPARATORS.begin(), SEPARATORS.end(), token) != SEPARATORS.end()) {
  token_state = 2;
 }
 else if (find(OPERATORS.begin(), OPERATORS.end(), token) != OPERATORS.end()) {
  token_state = 3;
 }
 else if (fsmReal(token)) {
  token_state = 4;
 }
 else if (fsmInteger(token)) {
  token_state = 5;
 }
 return token_state;
}vector<string> parse(string s) {
 vector<string> parseList;
 string atBegin;
 atBegin.assign(s, 0, 1);
 do {
  if (isalpha(s[0])) {
   for (int i = 0; i < s.length(); i++) {
    if (isalpha(s[i + 1]) || isdigit(s[i + 1]) || s[i + 1] == '_') {
     continue;
    } else {
     parseList.push_back(s.substr(0, i + 1));
     s.erase(0, i + 1);
     break;
    }
   }
   atBegin.assign(s, 0, 1);
  }
  if (isdigit(s[0])) {
   int periodCount = 0;
   for (int i = 0; i < s.length(); i++) {
    if (isdigit(s[i + 1])) {
     continue;
    }
    else if (s[i + 1] == '.') {
     periodCount++;
     if (periodCount > 1) { cout << "ERROR" << endl; }
    } else {
     parseList.push_back(s.substr(0, i + 1));
     s.erase(0, i + 1);
     break;
    }
   }
   atBegin.assign(s, 0, 1);
  }
  if (isblank(s[0])) {
   s.erase(0, 1);
   atBegin.assign(s, 0, 1);
  }
  for (int i = 0; i < SEPARATORS.size(); i++) {
   if (atBegin == SEPARATORS[i]) {
    parseList.push_back(s.substr(0, 1));
    s.erase(0, 1);
    atBegin.assign(s, 0, 1);
   }
  }
  for (int i = 0; i < OPERATORS.size(); i++) {
   if (atBegin == OPERATORS[i]) {
    parseList.push_back(s.substr(0, 1));
    s.erase(0, 1);
    atBegin.assign(s, 0, 1);
   }
  }
  if (atBegin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890'()[]{ },.:;!*+-=/><%  ") != string::npos) {
   parseList.push_back(s.substr(0, 1));
   s.erase(0, 1);
   atBegin.assign(s, 0, 1);
  }
 } while (!s.empty());
 return parseList;
}
string readFile(string filename) {
 string text, temp;
 ifstream infile(filename);
 if (infile.is_open()) {
  while (getline(infile, temp)) {
   temp += " ";
   text += temp;
  }
  infile.close();
 } else {
  cout << "Error: Unable to open file" << endl;
 }
 return text;
}
void A() {
 if (global_token == "identifier") {
  temp = global_lexeme;
  string next_lex = parsedList[global_index + 1];
  global_index++;
  global_lexeme = next_lex;
  global_token = STATES[lexer(next_lex)];
  if (global_lexeme == "=") {
   next_lex = parsedList[global_index + 1];
   global_index++;
   global_lexeme = next_lex;
   global_token = STATES[lexer(next_lex)];
   E();
   ins_output[global_index] = "POPM " + to_string(st.getaddr(temp));
   gen_instr("POPM", st.getaddr(temp));
  }
 }
};
void E() {
 T();
 E_prime();
};
void E_prime() {
 if (global_lexeme == "+") {
  string next_lex = parsedList[global_index + 1];
  global_lexeme = next_lex;
  global_index++;
  global_token = STATES[lexer(next_lex)];
  T();
  ins_output[global_index] = "ADD";
  gen_instr("ADD", 0);
  E_prime();
 }
};
void T() {
 F();
 T_prime();
};
void T_prime() {
 if (global_lexeme == "*") {
  string next_lex = parsedList[global_index + 1];
  global_index++;
  global_lexeme = next_lex;
  global_token = STATES[lexer(next_lex)];
  F();
  ins_output[global_index] = "MUL";
  gen_instr("MUL", 0);
  T_prime();
 }
};
void F() {
 if (global_token == "identifier") {
  gen_instr("PUSHM", st.getaddr(global_token));
  ins_output[global_index] = "PUSHM " + to_string(st.getaddr(global_token));
  string next_lex = parsedList[global_index + 1];
  global_lexeme = next_lex;
  global_index++;
  global_token = STATES[lexer(next_lex)];
 }
};
void gen_instr(string op, int oprnd) {
 instr_table[instr_address].address = instr_address;
 instr_table[instr_address].op = op;
 instr_table[instr_address].oprnd = oprnd;
 instr_address++;
};
void displayTable() {
 map<int, inst>::iterator it;
 for (it = instr_table.begin(); it != instr_table.end(); it++) {
  cout << "Address: " << it->second.address << endl;
  cout << "Op: " << it->second.op << endl;
  cout << "Operand: " << it->second.oprnd << endl;
 }
}
//main
int main() {
 string fileName;
 cout << "Enter the file name: "; cin >> fileName;
 string inputfile = readFile(fileName);
 parsedList = parse(inputfile);
 output(parsedList);
 for (int i = 0; i < 1000; i++) {
  if (ins_output[i] != "") {
   cout << ins_output[i] << endl;
  }
 }
 cout << "look at output file for instruction and symbol table.\n";
 return 0;
}

