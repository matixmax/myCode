// author Mateusz Kantor
#ifndef START
#define START
#include <bits/stdc++.h>
//#define Warrnings ERROR
//#define fileOut fileOut
#ifndef Warrnings
#define in_ cin
#endif
#ifndef fileOut
#define out_ cout
#endif

#define for_(i,x) for(int i = 0;i<x;i++)
#define check_str_tab(nap,tab,index) while (tab[index] != nap)index++; // give index
#define print_tab(tab) for_(i,tab.size())out_<<tab[i]<<" ";

using namespace std;

#ifdef Warrnings
#include <fstream>
#include <ctime>
#include <utility>
#define TimeOut timeFile
fstream test;
#define in_ test
#ifdef fileOut
fstream fileOut;
#define out_ fileOut
#endif
#ifdef TimeOut
const int TAB_CAPTIVITY = 30;
fstream TimeOut;
pair<string, clock_t> time_tab[TAB_CAPTIVITY];
clock_t functime;
void mountTime(){
	functime = clock();
}
void checkTime(int index, string funcname){
	time_tab[index].first = funcname;
	time_tab[index].second += clock() - functime;
}
void saveTime(int size, bool standard = false){
	string filling;
	if (standard){
		out_ << "czasy funkcji:" << endl;
		for (int i = 0; i < size; i++){
			out_ << time_tab[i].first + filling.assign(10 - time_tab[i].first.length(), ' ')
				<< " = " << ((float)time_tab[i].second) / CLOCKS_PER_SEC << endl;
		}
	}
	else {
		TimeOut << "czasy funkcji:" << endl;
		for (int i = 0; i < size; i++){
			TimeOut << time_tab[i].first + filling.assign(10 - time_tab[i].first.length(), ' ')
				<< " = " << ((float)time_tab[i].second) / CLOCKS_PER_SEC << endl;
		}
	}
}
#endif
void generator(int magnitude, int test_number){
	fstream wyjscie;
	string number_of_test = "test";
	srand(time(NULL));
	if (test_number < 10){
		number_of_test.push_back((char)(test_number + (int)'0'));
	}
	else {
		number_of_test.push_back((char)(test_number / 10 + (int)'0'));
		number_of_test.push_back((char)(test_number % 10 + (int)'0'));
	}
	number_of_test += ".in";
	wyjscie.open(number_of_test, fstream::out);
	if (!wyjscie.good()){
		out_ << "blad otwarcia pliku wyjsciowego" << endl;
		return;
	}
	wyjscie << magnitude << endl;
	//dalszy ci¹g generatora
	wyjscie.close();
}
#endif

class symetric_heap{
public:
	symetric_heap(int n);
	void insert(int a);
	int take_max();
	int take_min();
private:
	void repair_down(int i);
	void repair_up(int i);
	void replace(int i, int j);
	int Lnode(int i);
	int Rnode(int i);
	vector<int> tab;
	int captivity;
	int size;	
};

symetric_heap::symetric_heap(int n): captivity(n+2),
								   size(2){
	tab.reserve(n + 2);
	tab.push_back(0);
	tab.push_back(0);
}
void symetric_heap::insert(int a){
	tab.push_back(a);
	int it = symetric_heap::size;
	if (symetric_heap::size % 2 == 1 && tab[symetric_heap::size - 1] > a){
		replace(symetric_heap::size, symetric_heap::size - 1);
		it = symetric_heap::size - 1;
	}
	while (true){
		int ln = Lnode(it), rn = Rnode(it);
		if (ln != 0 && tab[it] < tab[ln]){
			replace(ln, it);
			it = ln;
		}
		else if (rn != 0 && tab[it] > tab[rn]){
			replace(rn, it);
			it = rn;
		}
		else break;
	}
	symetric_heap::size++;
}
int symetric_heap::take_max(){
	int result = 0;
	if (2 < symetric_heap::size)result = tab[2];
	if (3 < symetric_heap::size){
		result = tab[3];
		tab[3] = tab[size - 1];
		symetric_heap::tab.pop_back();
		symetric_heap::size--;
		repair_down(3);
	}
	return result;	
}
int symetric_heap::take_min(){
	int result = 0;
	if (2 < symetric_heap::size){
		result = tab[2];
		tab[2] = tab[size - 1];
		symetric_heap::tab.pop_back();
		symetric_heap::size--;
		repair_down(2);
	}
	return result;
}
void symetric_heap::repair_down(int i){
	if (i % 2 == 0){
		int smalest = i;
		if (2 * i < symetric_heap::size && tab[2 * i] < tab[i])
			smalest = 2 * i;
		if (2 * i + 2 < symetric_heap::size && tab[2 * i + 2] < tab[smalest])
			smalest = 2 * i + 2;
		if (smalest != i){
			replace(smalest, i);
			if (smalest + 1 < symetric_heap::size && tab[smalest] > tab[smalest + 1])
				replace(smalest, smalest + 1);
			repair_down(smalest);
		}
	}
	else {
		int largest = i;
		if (2 * i - 1 < symetric_heap::size && tab[2 * i - 1] > tab[i])
			largest = 2 * i - 1;
		if (2 * i + 1 < symetric_heap::size && tab[2 * i + 1] > tab[largest])
			largest = 2 * i + 1;
		if (largest != i){
			replace(largest, i);
			if (tab[largest] < tab[largest - 1])
				replace(largest, largest - 1);
			repair_down(largest);
		}
	}
}
void symetric_heap::replace(int i, int j){
	int tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
}
int symetric_heap::Lnode(int i){
	if (i / 2 == 1)return 0;
	if ((i / 2) % 2 == 1)return i / 2 - 1;
	else return i / 2;
}
int symetric_heap::Rnode(int i){
	if (i / 2 == 1)return 0;
	if ((i / 2) % 2 == 1)return i / 2;
	else return i / 2 + 1;
}


int main(char* argv, int argc){
#ifdef Warrnings
	string number_of_test, a;
	number_of_test = "test";
	cout << "Podaj dwucyfrowy numer testu" << endl;
	cin >> a;
	number_of_test += a;
	number_of_test += ".in";
	test.open(number_of_test, fstream::in);
	while (!test.good()){
		number_of_test = "test";
		cout << "Podaj dwucyfrowy numer testu" << endl;
		cin >> a;
		number_of_test += a += ".in";
		cout << number_of_test << endl;
		test.open(number_of_test, fstream::in);
	}
#ifdef fileOut
	number_of_test.pop_back();
	number_of_test.pop_back();
	number_of_test.pop_back();
	number_of_test += ".out";
	fileOut.open(number_of_test, fstream::out);
#ifdef TimeOut
	TimeOut.open("czasy_" + number_of_test, fstream::out);
#endif
#endif
#endif
	ios_base::sync_with_stdio(false);
	int z, n, k, x,result;
	in_ >> z;
	for_(i, z){
		in_ >> n;
		result = 0;
		symetric_heap heap(2 * n);
		for_(j, n){
			in_ >> k;
			for_(q, k){
				in_ >> x;
				heap.insert(x);
			}
			result += heap.take_max() - heap.take_min();
		}
		out_ << result << endl;
	}
	system("pause");
	return 0;
}
#endif