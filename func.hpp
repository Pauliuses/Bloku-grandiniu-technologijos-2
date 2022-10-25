#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <time.h>
#include <chrono>
#include "hash.cpp"

using namespace std;

class user
{
public:
    string name;
    int balance;
    string public_key;
};
class transac
{
public:
    int sum;
    string transaction_id_hash;
    string sender_public_key;
    string recipient_public_key;
};

bool InputBool(string);
string Hashing(string);
string ReadFromFile(string);
void AvalancheEffect(string);
string HexToBin(char);
vector<user> generate_user(int);
int random_numbers(int, int);
vector<transac> generate_transactions(int, vector<user>);

#endif