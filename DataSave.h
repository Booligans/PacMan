#ifndef DATASAVE_H
#define DATASAVE_H
#include <iostream>
#include "ScoreObjects.h"
#include "Player.h"
#include <string>
#include <fstream>
#include <vector>
#include "ScoreObjects.h"
#include <sstream>

const int MAX = 126;
const int MIN = 32;
const int RANGE = MAX - MIN; // Range = MaxValue - MinValue 

const std::string ENCRYPTION_KEY = "dskmd23gmnw3245676çdfe1345";
//This will be the key used to encrypt/decrypt the saves and maps
const std::string PLAYER_DATAPATH = "/players/";
//The files containing player data will be contained in this path
const std::string PLAYER_INFO = "players.dat";
//This file indexes all of the player data files

int LoadAndDecryptFile(std::vector <playerData> & v);
//Loads the information of an encrypted file and decrypts it
//It is an int to return error codes

//AUXILIARY FUNCTIONS WILL BE DECLARED HERE

//------------------------------------------

void SaveAndEncrypt(std::vector <playerData> const& v);

void DecryptVigenereFile(std::string const & f, std::string & d);

std::string EncryptFile(std::string const& f);
#endif
