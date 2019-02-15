#include "DataSave.h"

// 0 Correct
// 1 Level file not found 
// 2 Player file not found

int LoadAndDecryptFile(playerArray & v) {
	int error = 0;
	playerData aux;
	std::string s;
	std::ifstream f;
	std::istringstream o;
	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);

	al_append_path_component(path, "Resources");
	al_append_path_component(path, "Players");
	al_change_directory(al_path_cstr(path, '/'));
	al_destroy_path(path);

	f.open(PLAYER_INFO);
	if (!f.is_open()) {
		error = 2;
	}
	else
	{
		getline(f, s);
		while (!f.eof())
		{
			DecryptVigenere(s);
			o.str(s);
			o >> aux.name;
			o >> s; //To parse correctly the text
			aux.score.SetScore(stoi(s));
			v.push_back(aux);
			o.clear();
			getline(f, s);
		}
		f.close();
	}
	return error;
}


void DecryptVigenere(std::string & d) {
	std::vector <int> v;
	int keySize = ENCRYPTION_KEY.size();

	for (int i = 0; i < (int)d.size(); ++i)
	{
		v.push_back(ENCRYPTION_KEY[i % keySize] % RANGE);
	}

	for (int i = 0; i < (int)d.size(); ++i)
	{
		d[i] = d[i] - v[i];

		if (d[i] < MIN)
		{
			d[i] = MAX - (MIN - d[i]);
		}
	}
}

void SaveAndEncrypt(playerArray const& v) {
	std::string aux;
	std::ofstream file;
	std::vector <int> u;
	int p;
	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);

	al_append_path_component(path, "Resources");
	al_append_path_component(path, "Players");
	al_change_directory(al_path_cstr(path, '/'));
	al_destroy_path(path);

	file.open(PLAYER_INFO);
	for (int i = 0; i < (int)v.size() && i < 10; ++i) //Only the first 10 are relevant
	{
		aux = v[i].name + " " + std::to_string(v[i].score.ReturnScore());
		p = 0;

		for (int j = 0; j < (int)aux.size(); ++j)
		{
			u.push_back(ENCRYPTION_KEY[p] % RANGE);
			aux[j] = aux[j] + u[j];
			if (aux[j] > MAX)
			{
				aux[j] = MIN + (aux[j] - MAX);
			}
			p = (p + 1) % ENCRYPTION_KEY.size();
		}
		u.clear();
		file << aux << '\n';
	}
	file.close();
}