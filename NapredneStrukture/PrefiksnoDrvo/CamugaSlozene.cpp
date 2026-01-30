#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

struct Cvor{
	bool krajReci = false;
	unordered_map<char, Cvor*> grane;
};

void dodaj(Cvor* stablo, const string& rec, int i){
	if(i == rec.size()){
		stablo->krajReci = true;
		return;
	}
	
	auto it = stablo->grane.find(rec[i]);
	if(it == stablo->grane.end())
		stablo->grane[rec[i]] = new Cvor();
	
	dodaj(stablo->grane[rec[i]], rec, i+1);
}

bool nadji(Cvor* stablo, const string& rec, int i){
	if(i == rec.size())
		return stablo->krajReci;
		
	auto it = stablo->grane.find(rec[i]);
	if(it != stablo->grane.end())
		return nadji(stablo->grane[rec[i]], rec, i+1);
	
	return false;
}

void obrisi(Cvor* stablo){
	if(stablo != nullptr){
		for(auto &x : stablo->grane){
			obrisi(x.second);
		}
		delete stablo;
	}
}

vector<string> slozene_reci;

bool provera_slozena(Cvor* stablo, const string& rec, int i, Cvor* koren, int skok){
	cout << rec[i] << " ";
	
	if(i == rec.size()){
		cout << " bazni slucaj" << endl;
		return stablo->krajReci && skok;
	}
	
	if(stablo->krajReci){
		if(provera_slozena(koren, rec, i, koren, skok + 1)){
			cout << " 2" << endl;
			return true;	
		}
	}
	auto it = stablo->grane.find(rec[i]);
	if(it == stablo->grane.end()){
		cout << " 1" << endl;
		return false;
	}	
	
	
	return provera_slozena(stablo->grane[rec[i]], rec, i+1, koren, skok);
}

void ispisi(Cvor* stablo){
    if(stablo != nullptr){
        for(const auto& x : stablo->grane){
            cout << x.first << endl;
            ispisi(x.second);
        }
    }
}

int main(){
	Cvor* koren = new Cvor();
	int n; cin >> n;
	vector<string> niz(n);
	
	for(int i=0; i<n; i++)
		cin >> niz[i];
		
	for(auto &x : niz)
		dodaj(koren, x, 0);
	
	if(nadji(koren, "hippo", 0))
		cout << "da!!!" << endl;
	else
		cout << "ne!!!" << endl;
	//ispisi(koren);
	cout << endl << endl;
	
	for(auto &rec : niz){
		cout << endl;
		if(provera_slozena(koren, rec, 0, koren, 0))
			slozene_reci.push_back(rec);
	}			
	
	cout << "-----------------rezultat-----------------\n";
	for(auto &x : slozene_reci)
		cout << x << " ";
	cout << endl;
	
	obrisi(koren);
	return 0;
}