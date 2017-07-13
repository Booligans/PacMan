#include "DataSave.h"

/*int main() {
	std::string fileName, text, plaintext;
	std::cin >> fileName;

	text = EncryptFile(fileName);
	DecryptVigenereFile(text, plaintext);
	std::cout << plaintext << '\n';
	system("pause");

	return 0;
}*/

void DecryptVigenereFile( std::string & d) {
	std::vector <int> v;
	int keySize = ENCRYPTION_KEY.size();

	for (int i = 0; i < d.size(); ++i) {
		v.push_back(ENCRYPTION_KEY[i % keySize] % RANGE);
	}

	for (int i = 0; i < d.size(); ++i) {
		d[i] = d[i] - v[i];
		if (d[i] < MIN)
		{
			d[i] = MAX - (MIN - d[i]);
		}
	}
}



std::string EncryptFile(std::string const& f) {

	std::string aux2 = "";
	int i = 0, keySize = ENCRYPTION_KEY.size();
	char aux;
	std::vector <int> v;
	std::vector <char> u;

		file.get(aux);
		while (!file.eof())
		{
			u.push_back(aux);
			v.push_back(ENCRYPTION_KEY[i % keySize] % RANGE);
			file.get(aux);
			++i;
		}
		NewEncryptedValues(u, v);
		ShowNewCode(u);
		for (int i = 0; i < u.size(); ++i) {
			aux2 += u[i];
		}
		file.close();
	
	return aux2;
}

// 0 no pasa nada
// 1 no encontrado archivo de carga de nivel
// 2 no se ha encontrado el de jugador

int LoadAndDecryptFile(std::vector <playerData> & v) {
	int typeOfMistake = 0;
	playerData aux;
	std::string s;
	std::ifstream f;
	std::istringstream o;
	f.open(PLAYER_INFO);

	if (!f.is_open()) {
		typeOfMistake = 2;
	}
	else {
		while (!f.eof()) {
			getline(f, s);
			DecryptVigenereFile(s);
			o.str(s);
			o >> aux.name;
			o >> s;
			aux.score.SetScore(stoi(s));
			v.push_back(aux);
		}
		f.close();
	}

	return typeOfMistake;
}


void SaveAndEncrypt(std::vector <playerData> const& v) {
	std::string aux;
	std::vector <int> u;
	int p;
	for (int i = 0; i < v.size(); ++i) {
		aux = v[i].name + " " + std::to_string(v[i].score.ReturnScore);
		p = 0;
		for (int j = 0; j < aux.size(); ++j) {
			u.push_back(ENCRYPTION_KEY[p] % RANGE);
			aux[j] = aux[j] + u[j];
			if (aux[j] > MAX) aux[j] = MIN + (aux[j] - MAX);
			p = (p + 1) % ENCRYPTION_KEY.size();
		}
	}


}
