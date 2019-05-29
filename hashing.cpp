#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Hashing{
	int numberOfWords;
	vector<string> words;
	vector<vector<string> > database;
	string currentWord;
	
public:
	void loadFile(string fileName)
	{
		fstream file(fileName.c_str());
		string line;
	
		while(file)
		{
			file >> line;
			words.push_back(line);
		}
	}
	
	void fillDatabase()
	{
		numberOfWords = words.size();
		makeEmptyDatabase();
		
		for(int i = 0; i < numberOfWords; i++)
		{
			currentWord = words[i];
			int index = getIndex(currentWord);
			int lengthOfWord = currentWord.size();
			string word = words[i];
			database[index].push_back(word);
			
		}
	}
	
	void makeEmptyDatabase()
	{
		vector<string> empty;
		empty.push_back("");
		for(int i=0; i<numberOfWords; i++)
			database.push_back(empty);
	}
	
	int getIndex(string currentWord)
	{
		int sumOfASCI = sumASCI(currentWord);
		int index = sumOfASCI % numberOfWords;
		return index;
	}
	
	int sumASCI(string currentWord)
	{
		int sumOfASCI = 0;
		int lengthOfWord = currentWord.size();
		for(int i = 0; i < lengthOfWord; i++)
		{
			char letter = currentWord[i];
			sumOfASCI = sumOfASCI + letter;
		}
		return sumOfASCI;
	}
	
	void createDatabaseFile()
	{
		fstream out("database.txt", ios::out);

		for(int index=0; index<numberOfWords; index++)
		{
			vector<string> currentChain;
			currentChain = database[index];
			bool chainIsNotEmpty = currentChain.back().empty() == false;
			if(chainIsNotEmpty)
			{
				out<<"Index "<<index<<": ";
				for(int j=0; j<currentChain.size(); j++)
				{
					out << currentChain[j] << " ";
				}
				out<<endl;
			}
			
		}
		out.close();
	}
	
	void find(string answer)
	{
		cout<<"Type a word to find in database: "<<endl;
		cout<<"You typed "<<answer<<endl;
		int lengthOfWord = answer.size();
		int index = getIndex(answer);
		vector<string> currentChain = database[index];
		int chainLength = currentChain.size();
		
		if(currentChain.empty())
			cout<<"Not found in database"<<endl;
		
		for(int i=0; i<chainLength; i++)
		{
			if(currentChain[i] == answer)
			{
				cout<<"Your word has index "<<index<<endl;
				return ;
			}
		}
		
		cout<<"Not found in database"<<endl;
	}
};


int main(){

	Hashing h;
	h.loadFile("test2.txt");
	h.fillDatabase();
	h.createDatabaseFile();
	h.find("Kowalski");
	
	return 0;
}
