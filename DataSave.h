#ifndef DATASAVE_H
#define DATASAVE_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "ScoreObjects.h"
#include "Player.h"

const int MAX = 127;
const int MIN = 31;
const int RANGE = MAX - MIN; // Range = MaxValue - MinValue 

const std::string ENCRYPTION_KEY = "dskmd23gmnw3245676zdfe1345";
//This will be the key used to encrypt/decrypt the saves and maps
const std::string PLAYER_DATAPATH = "Players";
//The files containing player data will be contained in this path
const std::string PLAYER_INFO = "players.dat";
//This file indexes all of the player data files

int LoadAndDecryptFile(playerArray & v);
//Loads the information of an encrypted file and decrypts it
//It is an int to return error codes

//AUXILIARY FUNCTIONS WILL BE DECLARED HERE

//------------------------------------------

void SaveAndEncrypt(playerArray const& v);
void DecryptVigenere(std::string & d);



#endif