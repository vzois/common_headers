#ifndef ARGP_H
#define ARGP_H

#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <vector>

#define UI_FRONT_SPACES 10
#define UI_MIDDLE_SPACES 20

const static std::string DARG="-d"; //DIMENSIONALITY
const static std::string CARG="-c";//CARDINALITY
const static std::string MAXARG="-max"; //RANDOM MAXIMUM
const static std::string MINARG="-min";
const static std::string FIARG="-fi"; //FILE INPUT
const static std::string FOARG="-fo"; //FILE INPUT
const static std::string MDARG="-md";//EXECUTION MODE
const static std::string HELP="-h";
const static std::string TARG="-t";
const static std::string DPT="-pt";//DATA PER THREAD// CUDA ONLY

const static std::string DARG_H="data dimensionality.";
const static std::string CARG_H="data cardinality.";
const static std::string MAXARG_H="maximum for random number generation.";
const static std::string MINARG_H="minimum for random number generation.";
const static std::string FIARG_H="input filename (comma separated).";
const static std::string FOARG_H="output filename (comma separated).";
const static std::string MDARG_H="execution mode (application specific i.e. 0,1,2 ...).";
const static std::string HELP_H="print this help menu.";
const static std::string DPT_H="specify the number of elements each cuda thread is responsible for processing";
const static std::string TARG_H="number of threads(in a block for cuda).";

class ArgParser{
public:
	ArgParser(){ };
	~ArgParser(){};

	std::vector<std::string> split(std::string str, std::string delimiter);

	void parseArgs(int argc, char **argv);
	void addArg(std::string, std::string);
	int getInt(const std::string);
	unsigned int getUint(const std::string);
	std::string getString(std::string);

	std::string mysetw(int,int);
	bool exists(std::string);
	int count();

	void menu();

private:
	std::map<std::string,std::string>  args;
};

std::vector<std::string> ArgParser::split(std::string str, std::string delimiter){
	std::vector<std::string> out;
	std::string lstr(str);
	int pos = 0;

	while ((pos = lstr.find(delimiter)) != -1){
		out.push_back(lstr.substr(0, pos));
		lstr = lstr.substr(pos + 1);
	}
	out.push_back(lstr);
	return out;
}

void ArgParser::parseArgs(int argc, char **argv){

	for(int i = 1;i<argc;i++){
		std::vector<std::string> tokens = this->split(std::string(argv[i]),"=");
		if(tokens.size() == 2){
			std::cout<<tokens[0] << "," << tokens[1] << std::endl;
			this->addArg(tokens[0],tokens[1]);
		}else{
			std::cout<<tokens[0] << "," << "empty" << std::endl;
			this->addArg(tokens[0],"empty");
		}
	}
}

void ArgParser::addArg(std::string arg, std::string val){
	this->args.insert(std::pair<std::string,std::string>(arg,val));
}

int ArgParser::getInt(std::string arg){
	return atoi(this->args[arg].c_str());	
}

unsigned int ArgParser::getUint(std::string arg){
	return atoi(this->args[arg].c_str());
}


std::string ArgParser::getString(std::string arg){
	return this->args[arg];
}

bool ArgParser::exists(std::string arg){
	return (this->args.end() != this->args.find(arg));
}

int ArgParser::count(){
	return this->args.size();
}

std::string ArgParser::mysetw(int spaces,int width){
	std::string space;
	for(int i=0;i<spaces-width;i++) space+=" ";
	return space;
}

void ArgParser::menu(){
	std::cout<<"<<<Execution Guidelines>>>"<<std::endl;
	std::cout<<this->mysetw(UI_FRONT_SPACES,0)<<DARG<<this->mysetw(UI_MIDDLE_SPACES,2)<<DARG_H<<std::endl;
	std::cout<<this->mysetw(UI_FRONT_SPACES,0)<<CARG<<this->mysetw(UI_MIDDLE_SPACES,2)<<CARG_H<<std::endl;
	std::cout<<this->mysetw(UI_FRONT_SPACES,0)<<MAXARG<<this->mysetw(UI_MIDDLE_SPACES,4)<<MAXARG_H<<std::endl;
	std::cout<<this->mysetw(UI_FRONT_SPACES,0)<<MINARG<<this->mysetw(UI_MIDDLE_SPACES,4)<<MINARG_H<<std::endl;
	std::cout<<this->mysetw(UI_FRONT_SPACES,0)<<FIARG<<this->mysetw(UI_MIDDLE_SPACES,3)<<FIARG_H<<std::endl;
	std::cout<<this->mysetw(UI_FRONT_SPACES,0)<<FOARG<<this->mysetw(UI_MIDDLE_SPACES,3)<<FOARG_H<<std::endl;
	std::cout<<this->mysetw(UI_FRONT_SPACES,0)<<MDARG<<this->mysetw(UI_MIDDLE_SPACES,2)<<MDARG_H<<std::endl;
	std::cout<<this->mysetw(UI_FRONT_SPACES,0)<<DPT<<this->mysetw(UI_MIDDLE_SPACES,2)<<DPT_H<<std::endl;
	std::cout<<this->mysetw(UI_FRONT_SPACES,0)<<HELP<<this->mysetw(UI_MIDDLE_SPACES,2)<<HELP_H<<std::endl;
}

#endif