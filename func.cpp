#include "func.hpp"

string Hashing(string key)
{
    static const string hex = "0123456789abcdef";
    string finalHex;
    unsigned int hash;
    const int code = 31;

    for (int i = 0; i < key.length(); i++)
    {
        hash = (hash * code) + int(key[i]);
    }

    string hashString = to_string(hash);

    unsigned int hexSymbol = hash;

    int SizeOfHashString = hashString.size();

    for (int i = 0; i < 64; i++)
    {
        hexSymbol += int(hashString[i % SizeOfHashString]) + i; // pridedame i nes su tekstu "a" gaunasi blogas hash

        finalHex += hex[hexSymbol % 16];
    }
    return finalHex;
}
int random_numbers(int x, int y)
{
    return ((rand() % y) + x);
}

vector<user> generate_user(int size)
{
    vector<user> useriai;

    for (int i = 0; i < size; i++)
    {
        user new_user;

        new_user.name = "Useris: " + std::to_string(i);
        new_user.public_key = Hashing(new_user.name);

        new_user.balance = random_numbers(100, 1000000);

        useriai.push_back(new_user);
    }

    return useriai;
}
vector<transac> generate_transactions(int size, vector<user> useriai)
{
    vector<transac> transakcijos;

    for (int i = 0; i < size; i++)
    {
        transac new_transaction;

        int sender_id = random_numbers(0, 999);
        int recipient_id = random_numbers(0, 999);

        new_transaction.sender_public_key = useriai[sender_id].public_key;
        new_transaction.recipient_public_key = useriai[recipient_id].public_key;

        while (new_transaction.sender_public_key == new_transaction.recipient_public_key)
        {
            int atsitiktinis = random_numbers(0, 999);
            // cout << atsitiktinis <<endl;
            new_transaction.recipient_public_key = useriai[atsitiktinis].public_key;
            // cout << "Here " <<endl;
        }
        // cout << new_transaction.sum <<endl;
        new_transaction.sum = useriai[sender_id].balance;
        // cout << new_transaction.sum <<endl;

        new_transaction.transaction_id_hash = Hashing(new_transaction.sender_public_key + new_transaction.recipient_public_key + to_string(new_transaction.sum));
        // cout << new_transaction.transaction_id_hash << " hashed transaction " <<endl;
        transakcijos.push_back(new_transaction);
    }

    return transakcijos;
}

block_header gen_block(int difficulty, int nonce, vector<transac> &transaction, int block_count)
{
    block_header blocks;

    string all_transactions;

    blocks.version = "0.1";

    blocks.nonce = nonce;
    blocks.block_hash = Hashing(to_string(nonce));

    for (int i = 0; i < 100; i++)
    {
        int transaction_id = random_numbers(0, transaction.size() - 1);

        blocks.transactions.push_back(transaction[transaction_id]);

        all_transactions += blocks.transactions.back().transaction_id_hash;

        transaction.erase(transaction.begin() + transaction_id);
    }

    blocks.merkel_root_hash = Hashing(all_transactions);

    if (block_count != 0)
        blocks.prev_block_hash = blocks.block_hash;

    blocks.difficulty_target = difficulty;

    return blocks;
}
void print_to_file(vector<block_header> blockchain_blocks, int x)
{
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    ofstream fr;
    fr.open("result.txt", fstream::app);

    fr << "Block of the blockchain " << x + 1 << ": " << endl;
    fr << "Hash: " << blockchain_blocks.back().block_hash << endl;
    fr << "Timestamp: " << ctime(&end_time);
    fr << "Version: " << blockchain_blocks.back().version << endl;
    fr << "Merkel Root Hash: " << blockchain_blocks.back().merkel_root_hash << endl;
    fr << "Nonce: " << blockchain_blocks.back().nonce << endl;
    fr << "Difficulty: " << blockchain_blocks.back().difficulty_target << endl;
    fr << "Number of transactions: " << blockchain_blocks.back().transactions.size() << endl;
    fr << endl;

    fr.close();
}