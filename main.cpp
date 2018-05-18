#include<iostream>
#include<fstream>
#include<string>

#include"newlib.hpp"

using namespace std;



int main(int argc, char **argv)
{
	//system("ls");
	//system("cd $PWD");
	//system("ls");
	//while(argv) cout << *argv++ <<endl;
	try{
		ParseInput(argc, argv);
		CreateHeader();//*/
		CreateSource();
	}
	catch(const char* err)
	{
		if(err == "something")
			cerr << "only c and cpp are supported" << endl;
	}
	return 0;
}
