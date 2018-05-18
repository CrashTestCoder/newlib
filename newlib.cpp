/* newlib.cpp */
/***********************************************************************************/
/**                                                                                */
/**              RESOURCES AND DEFINITIONS FOR NEWLIB POGRAM                       */
/**                                                                                */
/**--------------------------------------------------------------------------------*/
/**                                                                                */
/**  Full Discription                                                              */
/**                                                                                */
/***********************************************************************************/
#include"newlib.hpp"

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<cstdio>

#include<time.h>
#include<string.h>

using namespace std;

/***********************************************************************************/
/**  1 -            Variables and constants for internal use                       */
/***********************************************************************************/

/** 1.1 - Structures For Data Storage */
static struct _lib {
	
	string name;
	string language;
	string title;
	string discription;
	string version;
	string author;
	
	int comment_width = 100;
	
	void print(bool b = 1)
	{
		if(b){
			cout << "Name:		" << name;
			if(name.empty())
				getline(cin,name);
			else cout << endl;
			
			if(name.empty())
			{
				cout << "Your Library must have a name" <<endl;
				print();
				return;
			}
		}
		cout << "Language:	" << language << flush;
		if(language.empty())
			getline(cin,language);
		else cout << endl;
		
		if(language.empty())
		{
			cout << "You must specify a language" << endl;
			print(0);
			return;
		}
		
		for(char& c : language)if(isalpha(c)) c |= 0b01100000;
		if(language == "c++" || language == "cxx") language = "cpp";
		if(language != "c" && language != "cpp")
		{
			cout << language << " is not an acceptable language, please try again." << endl;
			language = "";
			print(0);
			return;
		}
		
		cout << "Title:		" << title << flush;
		if(title.empty())
			getline(cin,title);
		else cout << endl;
		
		for(char& c : title)if(isalpha(c)) c &= 0b01011111;
		
		cout << "Discription:	" << discription << flush;
		if(discription.empty())
			getline(cin,discription);
		else cout << endl;
		
		cout << "Version:	" << version << flush;
		if(version.empty())
			getline(cin,version);
		else cout << endl;
		
		cout << "Author:		" << author << flush;
		if(author.empty())
			getline(cin,author);
		else cout << endl;
		
		if(title.size() > comment_width - 11) comment_width = title.size() + 15;
	}
} Library;


/***********************************************************************************/
/**  2 -                Private Functions For Internal Use                         */
/***********************************************************************************/

/**  2.1 - Parses one argument of format:
 * 				-c, cpp
 */
int ParseArgument(char ***argv)
{
	/** Verify arguments exist */
	if(! ((**argv != NULL) && (*(*argv+1) != NULL)) ) return INT_ERR_No_Args_Provided;
	if(***argv != '-') return INT_ERR_Invalad_Argument;
	
	char* param = *(*argv + 1);
	char switch_val = *(**argv + 1);
	switch(switch_val)
	{
	case 'n':
		Library.name = param;
		break;
	case 'l':
		Library.language = param;
		break;
	case 't':
		Library.title = param;
		break;
	case 'd':
		Library.discription = param;
		break;
	case 'v':
		Library.version = param;
		break;
	case 'a':
		Library.author = param;
		break;
	case 'w':
		Library.comment_width = atoi(param);
		break;
	
	default: 
		char *err;
		sprintf(err,"Unknown Argument %s",switch_val);
		throw err; 
	}
	
	*argv+=2;
	
	return 0;
}

/** 2.2 - Create comment with text in the center */
string CreateCommentCentered(string text)
{
	string com = "/**";
	int start_point = (Library.comment_width - text.size()) / 2 - com.size();
	
	for(int i = 0; i < start_point; i++)
		com += ' ';
	com += text;
	while(Library.comment_width - com.size() - 2)
		com += ' ';
	com += "*/";
	return com;
}

/**  2.3 - Create line of astrisks */
string CreateCommentOf(char c)
{
		string com = "/**";
		while(Library.comment_width - com.size() - 2)
			com += c;
		com += "*/";
		return com;
}

/** 2.4 - Create single line comment with text from the left */
string _CreateCommentLeft(string text)
{
	string com = "/**  ";
	com += text;
	while(Library.comment_width - com.size() - 2)
		com += ' ';
	com += "*/";
	return com;
}

/** 2.5 - Parse string into a vector of words */
vector<string> ParseToWords(string str)
{
	istringstream iss(str);
	vector<string> words;
    do
    {
        string subs;
        iss >> subs;
        subs += ' ';
        words.push_back(subs);
    } while (iss);
    return words;
}

/** 2.6 - Parse string into an vector of of strings with a max size of n */
vector<string> ParseToLength(string str, int max_length)
{
	istringstream iss(str);
	vector<string> lines;
	lines.push_back(string());
	string *line = &lines[0];
	
	for(string s = ""; iss; iss >> s)
	{
		if(s.empty())continue;
		//cout << line->size() << '\t' << *line << endl;
		if( (*line + s).size() > max_length)
		{
			lines.push_back(string());
			line  = &lines[lines.size() - 1];
			
		}
		*line += s + " ";
	}
	return lines;
}

/** 2.7 - Create comment with text from the left */
void CreateCommentLeft(ostream& os, string text)
{
	for(string s : ParseToLength(text,Library.comment_width - 7))
	{
		string line = "/**  ";
		
		line += s;
		
		while(Library.comment_width - line.size() - 2)
			line += ' ';
		
		line += "*/";
		
		os << line << endl;
	}
}

/** 2.8 - History Text */
string HistoryText(string version, string author)
{
	string hist = "History:      ";
	
	const int MAXLEN = 15;
    char s[MAXLEN];
    time_t t = time(0);
    strftime(s, MAXLEN, "%m/%d/%Y", localtime(&t));
    char *date = (char*)malloc(10);
	strncpy(date,s,10);
    
    hist += date;
    free(date);
	
	hist += " - ";
	hist += version + ", ";
	hist += author;
	
    return hist;
}
		
/** 2.9 - Creates a single line comment */
string Comment(string str)
{
	string com = "/** ";
	com += str + " */";
	return com;
}
		
/***********************************************************************************/
/**  3 -                 Public Functions For Library Use                          */
/***********************************************************************************/

/**  3.1 - Function to read console data to Library structure */
int ParseInput(int argc, char **argv)
{
	argv++;
	if(*argv) if(**argv != '-')
		Library.name = *argv;
	try{
		int err;
		while(! (err = ParseArgument(&argv)) );
		if(*argv) 
			cout << "Parse: " << err << endl;
	}
	catch(char* err)
	{
		cerr << "ERROR: " << err << endl;
		delete err;
	}
	Library.print();
	return 0;
}

int CreateHeader(void)
{
	ofstream fout;
	if(Library.language == "c") fout = ofstream(Library.name + ".h");
	else if(Library.language == "cpp") fout = ofstream(Library.name + ".hpp");
	else throw "something";
	if(Library.language == "c") fout << Comment(Library.name + ".h") << endl;
	else if(Library.language == "cpp") fout << Comment(Library.name + ".hpp") << endl;
	fout << CreateCommentOf('*') << endl;
	fout << CreateCommentOf(' ') << endl;
	fout << CreateCommentCentered(Library.title) <<endl;
	fout << CreateCommentOf(' ') << endl;
	fout << CreateCommentOf('-') << endl;
	fout << CreateCommentOf(' ') << endl;
	CreateCommentLeft(fout,HistoryText(Library.version,Library.author));
	fout << CreateCommentOf(' ') << endl;
	fout << CreateCommentOf('*') << endl;
	fout << endl;
	
	string defn = "_" + Library.name;
	for(char& c : defn)
		c &= 0b01011111;
	
	if(Library.language == "c")
		defn += "_H_";
	else if(Library.language == "cpp")
		defn += "_HPP_";
		
	fout << "#ifndef " << defn << endl;
	fout << "#define " << defn << endl;
	fout << endl;
	
	if(Library.language == "c")
	{
		fout << "#ifdef __cplusplus" << endl;
		fout << "extern \"C\" {" << endl;
		fout << "#endif" << endl;
		fout << endl;
	}
	
	fout << "/**" << endl << " **** Put your code here" << endl << " */" << endl << endl;
	
	if(Library.language == "c")
	{
		fout << "#ifdef __cplusplus" << endl;
		fout << "}" << endl;
		fout << "#endif" << endl;
		fout << endl;
	}
	
	
	fout << "#endif /** " << defn << " */" << endl;
	
	fout.close();
	return 0;
}

/** 3.3 - Function to Create a source file for the new library */
int CreateSource(void)
{
	ofstream fout;
	if(Library.language == "c") fout = ofstream(Library.name + ".c");
	else if(Library.language == "cpp") fout = ofstream(Library.name + ".cpp");
	else throw "something";
	if(Library.language == "c") fout << Comment(Library.name + ".c") << endl;
	else if(Library.language == "cpp") fout << Comment(Library.name + ".cpp") << endl;
	fout << CreateCommentOf('*') << endl;
	fout << CreateCommentOf(' ') << endl;
	fout << CreateCommentCentered(Library.title) <<endl;
	fout << CreateCommentOf(' ') << endl;
	CreateCommentLeft(fout,Library.discription);
	fout << CreateCommentOf(' ') << endl;
	fout << CreateCommentOf('-') << endl;
	fout << CreateCommentOf(' ') << endl;
	CreateCommentLeft(fout,HistoryText(Library.version,Library.author));
	fout << CreateCommentOf(' ') << endl;
	fout << CreateCommentOf('*') << endl;
	if(Library.language == "c") fout << "#include\"" << Library.name << ".h\"" << endl;
	else if(Library.language == "cpp") fout << "#include\"" << Library.name << ".hpp\"" << endl;
	fout << endl << endl;
	fout << "/**" << endl << " **** Put your code here" << endl << " */" << endl << endl;
	return 0;
	
}
