#include <iostream>
#include <fstream>
#include <map>
usng namespace std;

int main(int argc, char *argv[]){
	ifstream fin(argv[1]);
		int x;
		map<int, int>counts;
		while (fin >> x) {
			if (counts.find(x) == counts.end()) counts [x] = 0;
			counts[x]++;
		}
		for (auto &c: counts){
			cout << c.first << " " << c.second << endl;
		}
		return 0;
}
