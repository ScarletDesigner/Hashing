#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class FileLoader {
	fstream file;

protected:
	vector<string> words;
	
	void loadFile(string fileName)
	{
		file.open(fileName.c_str());
		string line;
	
		while(file)
		{
			file >> line;
			words.push_back(line);
		}
	}
};

class DatabaseCreator: public FileLoader {
	string currentWord;
	
protected:
	int numberOfWords;
	vector<vector<string> > database;
	
	void createDatabase()
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
	
	int getIndex(string currentWord)
	{
		int sumOfASCI = sumASCI(currentWord);
		int index = sumOfASCI % numberOfWords;
		return index;
	}
	
private:
	void makeEmptyDatabase()
	{
		vector<string> empty;
		empty.push_back("");
		for(int i=0; i<numberOfWords; i++)
			database.push_back(empty);
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
};

class DatabaseTextFileCreator: virtual public DatabaseCreator {
	vector<string> currentChain;
	fstream out;
	int index;

protected:
	void createDatabaseFile()
	{
		out.open("database.txt", ios::out);

		for(index = 0; index < numberOfWords; index++)
		{
			currentChain = database[index];
			
			if(chainIsNotEmpty())
				importChainToTextFile();
		}
		out.close();
	}
	
private:
	bool chainIsNotEmpty()
	{
		if(currentChain.back().empty() == false)
			return true;
		return false;
	}
	
	void importChainToTextFile()
	{
		out<<"Index "<<index<<": ";
		for(int j = 0; j < currentChain.size(); j++)
			out << currentChain[j] << " ";
			
		out<<endl;
	}
};

class Hashing: virtual public DatabaseCreator, DatabaseTextFileCreator {
	int chainLength;
	vector<string> currentChain;
	int index;
	string answer;
	
public:
	Hashing(string fileName)
	{
		loadFile(fileName);
		createDatabase();
		createDatabaseFile();
	}
	
	void find(string answer)
	{
		this -> answer = answer;
		index = getIndex(answer);
		currentChain = database[index];
		chainLength = currentChain.size();
		
		cout<<"Finding "<<answer<<" in database"<<endl;
		
		if(currentChain.empty())
			cout<<"Not found in database"<<endl;
		
		if(isInDatabase(answer))
			return ;
		
		cout<<"Not found in database"<<endl;
	}
	
private:
	bool isInDatabase(string answer)
	{
		for(int i=0; i<chainLength; i++)
			if(isInCurrentChain(i))
				return true;
		
		return false;
	}
	
	bool isInCurrentChain(int i)
	{
		if(currentChain[i] == answer)
		{
			cout<<"Your word has index "<<index<<endl;
			return true;
		}
		return false;
	}
};

int main(){

	Hashing h("test2.txt");
	h.find("Kowalski");
	
	return 0;
}
