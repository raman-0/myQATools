#include <bits/stdc++.h>
#include <fstream>
#include<windows.h>
#include<filesystem>
#include<string>
using namespace std;
void SetColor(int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}
void addToLast(string &s, string &appendText){
	s.append(appendText);
}
string findAndReplace(string s, string toSearch, string toReplace){
	size_t pos=s.find(toSearch);
	//if condition true return empty stirng
	if(pos==string::npos)
		return {};
	while(pos!=string::npos){
		s.replace(pos,toSearch.size(),toReplace);
		pos=s.find(toSearch,pos+toReplace.size());
	}
	return s;
}
void openURL(string fileName){
	ifstream inputFile;
	inputFile.open(fileName);
	string temp;
	int count=0;
	if (!inputFile.is_open()){
		SetColor(4);
		cout<<"Wrong File Name";
		SetColor(7);
		_Exit(0);
	}
	while(getline(inputFile, temp)){
		char* url=&temp[0];
		ShellExecuteA(NULL,"open",url,NULL,NULL,SW_SHOWNORMAL);
		count++;
		if(count>10){
			cout<<"Press Enter to open next 10 URLs";
			cin.ignore();
			count=0;
		}
	}
	inputFile.close();
	cout<<"Process Completed"<<endl;
}
int main(){
	ifstream inputFile;
	//ofstream outputFile;
	inputFile.open("Input.txt");
	cout<<"Use Find and Replace function press 1"<<endl;
	cout<<"Use insert in last position. Press 2"<<endl;
	cout<<"Use multiple URL Opener Only. Press 3"<<endl;
	int check=0;
	cin>>check;
	if (inputFile.is_open()){
		string temp;
		if(check==1){
			int times;
			cout<<"How many Find And Replace to use";
			cin>>times;
			vector<string> toSearch;
			vector<string> toReplace;
			ofstream outputFile;
			for(int i=0;i<times;i++){
				string searchText;
				string replaceText;
				cout<<"Enter the text to be searched:";
				cin>>searchText;
				cout<<"Enter the replacing text:";
				cin>>replaceText;
				toSearch.push_back(searchText);
				toReplace.push_back(replaceText);
			}
			outputFile.open("Output.txt");
			if(!outputFile){
				cout<<"Error FIle not opened"<<endl;
			}
			//using getline function to read data from file object and putting it into string
			//syntax of getline(is where to read input from, str storeing input to string, delim when to stop reading input)
			while(getline(inputFile, temp)){
				outputFile<<temp<<"\n";
				for(int i=0;i<times;i++){
					temp=findAndReplace(temp,toSearch[i],toReplace[i]);
					outputFile<<temp<<"\n";
				}
			}
			outputFile.close();
			cout<<"Do you want to open all URL 1.Yes 2.No"<<endl;
			int choice=0;
			cin>>choice;
			if(choice==1){
				openURL("Output.txt");
			}else {
				if(choice!=2)
					cout<<"Anyway ";
				cout<<"Exiting";
				_Exit(0);
			}
		}
		if(check==2){
			string appendText;
			cout<<"Enter text to be appended"<<endl;
			cin>>appendText;
			string temp;
			ofstream outputFile;
			outputFile.open("Output.txt");
			while(getline(inputFile, temp)){
				outputFile<<temp<<"\n";
				addToLast(temp,appendText);
				outputFile<<temp<<"\n";
			}
			outputFile.close();
			cout<<"Process Completed"<<endl;
			cout<<"Do you want to open all URLs 1. Yes  2.No"<<endl;
			int choice=0;
			cin>>choice;
			if(choice==1){
				openURL("Output.txt");
			}else{
				if(choice!=2){
					cout<<"Anyway";
				}
				cout<<"Exiting"<<endl;
			}
		}
		if(check==3){
			SetColor(4);
			cout<<"Remeber the file should be in same directory as that of the program"<<endl;
			SetColor(7);
			cout<<"Enter the file name"<<endl;
			string fileName;
			cin>>fileName;
			openURL(fileName);
		}
		
	}
	else cout << "Unable to open file";
	return 0;
}