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
			DecryptVigenere(s);
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


void DecryptVigenere(std::string & d) {
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

void SaveAndEncrypt(std::vector <playerData> const& v) {
	std::string aux;
	std::ofstream file;
	std::vector <int> u;
	int p;
	file.open(PLAYER_INFO); // Lo queremos guardar en la carpeta PLAYER_DATAPATH = "/players/"
	for (int i = 0; i < v.size(); ++i) {
		aux = v[i].name + " " + std::to_string(v[i].score.ReturnScore);
		p = 0;
		for (int j = 0; j < aux.size(); ++j) {
			u.push_back(ENCRYPTION_KEY[p] % RANGE);
			aux[j] = aux[j] + u[j];
			if (aux[j] > MAX) aux[j] = MIN + (aux[j] - MAX);
			p = (p + 1) % ENCRYPTION_KEY.size();
		}
		file << aux << '\n';
	}
	file.close();
}


