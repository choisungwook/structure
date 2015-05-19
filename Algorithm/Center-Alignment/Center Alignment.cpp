#include <string>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
	string name;
	vector<string> nameArray;	
	int nameLen;
	int maxLen = 0;
	int start, end = 0;
	

	for (nameLen = 0; getline(cin, name); nameLen++)
	{
		maxLen = maxLen < name.size() ? name.size() : maxLen;
		
		nameArray.push_back(name);
	}

	cout << string(maxLen+2, '*') << endl;

	for (int i = 0; i < nameLen; i++)
	{		
		int len = maxLen - nameArray[i].size();
		start = len / 2;

		if (len & 1)
		{
			start += end;
			end ^= 1;
		}

		cout << "*";
		cout << string(start, ' ');
		cout << nameArray[i];
		cout << string(len - start, ' ');
		cout << "*" << endl;
	}
	
	cout << string(maxLen + 2, '*') << endl;
	
	return 0;
}
