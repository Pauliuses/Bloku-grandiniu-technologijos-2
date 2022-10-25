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
// string Hashing(string hashInput){
//     if(hashInput == " ") return "961b6dd3ede3cb8ecbaacbd68de040cd78eb2ed5889130cceb4c49268ea4d506";

//     const int initial_hash_seed = 9464;                 // initial seed
//     unsigned int initial_hash = initial_hash_seed;

//     for(int i = 0; i <= hashInput.length(); i++){       // random h
//         initial_hash = (initial_hash * 47) + int(hashInput[i]) + hashInput.length() * 27;
//     }

//     string initial_hash_str = to_string(initial_hash);      // 4 choosing char
//     int initial_hash_str_size = initial_hash_str.size();
    
//     const string hex = "0123456789abcdef";          // hex str
//     string hashOutput;

//     unsigned int random_var = initial_hash * initial_hash_seed;     // random variable
//     int random_num = 17;

//     for(int i = 0; i < 64; i++){        // for 64c // randomizing var // creating hashout
//         random_var += initial_hash_str[i * random_num % initial_hash_str_size] + initial_hash_seed * i * 3;
//         hashOutput += hex[random_var % 16];
//         random_num = random_num * 3 - 11;
//     }

//     return hashOutput;
// }

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
        new_transaction.sender_public_key = useriai[sender_id].public_key;
        new_transaction.recipient_public_key = useriai[random_numbers(0, 999)].public_key;

        while (new_transaction.sender_public_key == new_transaction.recipient_public_key)
        {
            new_transaction.recipient_public_key = useriai[random_numbers(0, 999)].public_key;
        }
        new_transaction.sum = useriai[sender_id].balance / 10;

        new_transaction.transaction_id_hash = Hashing(new_transaction.sender_public_key + new_transaction.recipient_public_key + to_string(new_transaction.sum));
        //cout << new_transaction.transaction_id_hash << " hashed transaction " <<endl;
        transakcijos.push_back(new_transaction);
    }
    return transakcijos;
}

block_header gen_block(int difficulty, int nonce, vector<transac> &transaction, int blocknum)
{
    block_header block;

    // for v0.1
    string all_transactions = "";

    for (int i = 0; i < 100; i++)
    {
        int transaction_id = random_numbers(0, transaction.size() - 1);
        block.transactions.push_back(transaction[transaction_id]);
        all_transactions += block.transactions.back().transaction_id_hash;
        transaction.erase(transaction.begin() + transaction_id); // deleting from transaction pool
    }

    block.difficulty_target = difficulty;

    if (blocknum == 0)
        block.prev_block_hash = "-";
    else
        block.prev_block_hash = block.block_hash;

    block.timestamp = time(0);
    block.version = "v0.1";

    block.merkel_root_hash = Hashing(all_transactions); // hashing(merkle_root(block.transactions));
    block.nonce = nonce;
    block.block_hash = Hashing(to_string(nonce));

    return block;
}
void print_to_file(vector<block_header> blockchain, int j)
{
    ofstream out;
    out.open("result.txt", fstream::app);

    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    out << "Block " << j + 1 << ": " << endl
        << endl
        << "Hash: " << blockchain.back().block_hash << endl
        << "Timestamp: " << std::ctime(&end_time)
        << "Version: " << blockchain.back().version << endl
        << "Merkel Root Hash: " << blockchain.back().merkel_root_hash << endl
        << "Number of transactions: " << blockchain.back().transactions.size() << endl
        << "Nonce: " << blockchain.back().nonce << endl
        << "Difficulty: " << blockchain.back().difficulty_target << endl
        << "---------------------------------" << endl
        << endl;
    // }

    out.close();
}