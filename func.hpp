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
class block_header
{
public:
    int difficulty_target;
    string prev_block_hash;
    time_t timestamp;
    string version;
    string merkel_root_hash;
    unsigned int nonce;
    vector<transac> transactions;
    string block_hash;
};

string Hashing(string);
vector<user> generate_user(int);
int random_numbers(int, int);
vector<transac> generate_transactions(int, vector<user>);
block_header blocks_generation(int, int, vector<transac> &, int);
void print_to_file(vector<block_header>, int, int, int);
string merkle_tree(vector<transac>);

#endif