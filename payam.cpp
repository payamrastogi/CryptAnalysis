//Modern Crypto Project 1
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <set>
#include <list>
#include <vector>
using namespace std;

class Dictionaries
{
	public:
		string dictionary1[200];
		vector<string> dictionary2;
		map<char, int> charToIntMap;
		vector<string> allCombinations;

	public:
		Dictionaries();
		bool searchDictionary1(string cipherText, int keyLength);
		int helper(string cipherText, int keyLength, char p);
		void combinations(vector<string> result);
		bool searchDictionary2(string cipherText, int keyLength);
};

Dictionaries::Dictionaries()
{
	 ifstream infile;
	 infile.open("Dictionary1.txt");
	 int count=0;
	 if (infile.is_open())
	 {
		 while(!infile.eof())
		 {
			 string str;
			 //get line from text file and read it into dictionary1 array
			 getline(infile, dictionary1[count]);
			 for (int i=0; i<dictionary1[count].length(); i++)
			 {
				 //check if the character is printable
				 if(isprint(dictionary1[count].at(i)))
				 {
					 str+=dictionary1[count].at(i);
				 }
			 }
			 dictionary1[count]=str;
			 count++;
		 }
	 }
	 infile.close();

	 infile.open("Dictionary2.txt");
	 count = 0;
	 if (infile.is_open())
	 {
		 while(!infile.eof())
		 {
			 string str;
			 getline(infile, str);
			 dictionary2.push_back(str);
			 count++;
		 }
	 }
	 infile.close();

	 char c = 'a';
	 for(int i=0;i<26;i++)
	 {
		 charToIntMap[c] = i;
		 c++;
	 }
	 charToIntMap[' '] = 26;
}

bool Dictionaries::searchDictionary1(string cipherText, int keyLength)
{
	int found = -1;
	int key[100];
	set<int> keySet;
	for(int line=0; line<200; line++)
	{
		char prevChar = ' ';
		for(int col=0;col<100;col++)
		{
			key[col] = charToIntMap[cipherText[col]] - charToIntMap[dictionary1[line].at(col)] - charToIntMap[prevChar];
			if(key[col] < 0)
			{
				key[col] = 27 - (-1*key[col])%27;
			}
			keySet.insert(key[col]);
			prevChar = cipherText[col];
		}
		if(keySet.size() <= keyLength)
		{
			cout << "Possible plain text: " << dictionary1[line] << endl;
			found = true;
		}
		keySet.clear();
	}
	return found;
}

bool Dictionaries::searchDictionary2(string cipherText, int keyLength)
{
	bool flag;
	int found = -1;
	char prevChar = ' ';
	found = helper(cipherText, keyLength, prevChar);
	if(found!=-1)
	{
		prevChar = cipherText.at(found);
		cipherText = cipherText.substr(found+1, cipherText.length());
		cout <<"\n"<< prevChar <<" : " << cipherText;
		found = helper(cipherText, keyLength, prevChar);
		if(found!=-1)
		{
			prevChar = cipherText.at(found);
			cipherText = cipherText.substr(found+1, cipherText.length());
			cout <<"\n"<< prevChar <<" : " << cipherText;
			found = helper(cipherText, keyLength, prevChar);
		}
	}
	return flag;
}

int Dictionaries::helper(string cipherText, int keyLength, char p)
{
	int found = -1;
	int key[100];
	set<int> keySet;
	for(int line=0; line<allCombinations.size(); line++)
	{
		char prevChar = p;
		for(int col=0;col<allCombinations.at(line).length();col++)
		{
			key[col] = charToIntMap[cipherText[col]] - charToIntMap[allCombinations.at(line).at(col)] - charToIntMap[prevChar];
			if(key[col] < 0)
			{
				key[col] = 27 - (-1*key[col])%27;
			}
			keySet.insert(key[col]);
			prevChar = cipherText[col];
		}
		//cout << keySet.size() << endl;
		if(keySet.size() <= keyLength)
		{
			cout << "\nPossible plain text: " << allCombinations.at(line) <<endl;
			found = allCombinations.at(line).length();
			//return found;
		}
		keySet.clear();
	}
	return found;
}

void Dictionaries::combinations(vector<string> result)
{
	for(int i=0;i<dictionary2.size();i++)
	{
		result.push_back(dictionary2.at(i));
		if(result.size() == 3)
		{
			string check = result.at(0) + " " + result.at(1) + " " + result.at(2);
			allCombinations.push_back(check);
		}
		else
			combinations(result);
		result.pop_back();
	}
}

int main()
{
	Dictionaries dict;
	string cipher = "divldnp bdcpjgfwhlffuceeun in jtxjjpmyftuvcwxpkgzcnvjtwzcflw gztnkdzwmoyovgsowgayrzdvseindfqvcarofkw";
	int keyLength = 7;
	vector<string> result;
	dict.combinations(result);
	dict.searchDictionary2(cipher, keyLength);
	//dict.helper(result, cipher, keyLength);
	//cout << "Enter the ciphertext: ";
	//getline(cin, cipher);
	//cout << "Enter the keylength: ";
	//cin >> keyLength;
	//cout << "Searching dictionary1..." << endl;
	//bool found = dict.searchDictionary1(cipher, keyLength);
	//if(!found)
	//{
	//	cout << "No results found in dictionary 1" << endl;
	//	cout << "Searching dictionary2..." << endl;
	//}
}

