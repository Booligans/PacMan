#ifndef DATASAVE_H
#define DATASAVE_H
#include "ScoreObjects.h"
#include "Player.h"
#include <string>
#include <fstream>

const std::string ENCRYPTION_KEY = "dskmd23gmnw3245676çdfe1345";
//This will be the key used to encrypt/decrypt the saves and maps
const std::string PLAYER_DATAPATH = "/players/";
//The files containing player data will be contained in this path
const std::string PLAYER_INFO = "players.dat";
//This file indexes all of the player data files

int LoadAndDecryptFile(const std::string & file);
//Loads the information of an encrypted file and decrypts it
//It is an int to return error codes

//AUXILIARY FUNCTIONS WILL BE DECLARED HERE

//------------------------------------------

int SaveAndEncrypt(const std::string & file);

#endif
