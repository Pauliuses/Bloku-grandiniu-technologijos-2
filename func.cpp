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
string merkle_tree(vector<transac> transakcijos)
{
    vector<string> copy_of_transactions;

    for (int i = 0; i < transakcijos.size(); i++)
    {
        copy_of_transactions.push_back(transakcijos[i].transaction_id_hash);
    }

    while (copy_of_transactions.size() > 1)
    {
        vector<string> temp_copy_of_transactions;

        if (copy_of_transactions.size() % 2 != 0)
            copy_of_transactions.push_back(copy_of_transactions.back());

        for (int i = 0; i < copy_of_transactions.size() / 2; i++)
            temp_copy_of_transactions.push_back(Hashing(copy_of_transactions[i] + copy_of_transactions[i + 1]));

        copy_of_transactions = temp_copy_of_transactions;
    }

    return copy_of_transactions[0];
}
vector<user> generate_user(int size)
{
    vector<user> useriai;

    for (int i = 0; i < size; i++)
    {
        user new_user;

        new_user.name = "Useris: " + std::to_string(i);
        new_user.public_key = Hashing(new_user.name);

        new_user.balance = random_numbers(1000, 1000000);

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
            new_transaction.recipient_public_key = useriai[atsitiktinis].public_key;
        }
        new_transaction.sum = useriai[sender_id].balance / 100;

        new_transaction.transaction_id_hash = Hashing(new_transaction.sender_public_key + new_transaction.recipient_public_key + to_string(new_transaction.sum));
        transakcijos.push_back(new_transaction);
    }

    int sender_id, receiver_id;

    for (int i = 0; i < size; i++) // Tikrinama ar transakcijos hashas sutampa su transakcijos ID
    {

        for (int j = 0; j < useriai.size(); j++)
        {
            if (useriai.at(j).public_key == transakcijos.at(i).sender_public_key)
            {

                sender_id = j;
                break;
            }
            else
                sender_id = -1;
        }
        for (int j = 0; j < useriai.size(); j++)
        {
            if (useriai.at(j).public_key == transakcijos.at(i).recipient_public_key)
            {
                receiver_id = j;
                break;
            }
            else
                receiver_id = -1;
        }

        if (sender_id == -1 || receiver_id == -1)
            transakcijos.erase(transakcijos.begin() + i);
        else if (transakcijos.at(i).sum <= useriai[sender_id].balance ||
                 Hashing(transakcijos.at(i).sender_public_key + transakcijos.at(i).recipient_public_key +
                         to_string(transakcijos.at(i).sum)) == transakcijos.at(i).transaction_id_hash)
        {
            useriai[sender_id].balance -= transakcijos.at(i).sum;
            useriai[receiver_id].balance += transakcijos.at(i).sum;
        }
    }

    return transakcijos;
}

block_header blocks_generation(int difficulty, int number, vector<transac> &transaction, int block_count)
{
    block_header blocks;

    string all_transactions;

    blocks.version = "0.2";

    blocks.nonce = number;

    blocks.timestamp = time(0);

    blocks.block_hash = Hashing(to_string(number));

    for (int i = 0; i < 100; i++)
    {
        int transaction_id = random_numbers(0, transaction.size() - 1);

        blocks.transactions.push_back(transaction[transaction_id]);

        all_transactions += blocks.transactions.back().transaction_id_hash;

        transaction.erase(transaction.begin() + transaction_id);
    }

    if (block_count != 0)
        blocks.prev_block_hash = blocks.block_hash;

    blocks.merkel_root_hash = Hashing(merkle_tree(blocks.transactions));

    blocks.difficulty_target = difficulty;

    return blocks;
}
void print_to_file(vector<block_header> blockchain_blocks, int x, int bandymai, int kelintas, vector<transac> transactions)
{
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    ofstream fr;
    fr.open("result.txt", fstream::app);

    fr << "Block of the blockchain " << x << ": " << endl;
    fr << "Hash: " << blockchain_blocks.back().block_hash << endl;
    fr << "Timestamp: " << ctime(&end_time);
    fr << "Version: " << blockchain_blocks.back().version << endl;
    fr << "Merkel Root Hash: " << blockchain_blocks.back().merkel_root_hash << endl;
    fr << "Nonce: " << blockchain_blocks.back().nonce << endl;
    fr << "Difficulty: " << blockchain_blocks.back().difficulty_target << endl;
    fr << "Number of transactions: " << blockchain_blocks.back().transactions.size() << endl;
    fr << "Tries: " << bandymai << endl;
    fr << "Reikiamu savybiu hashas surastas per: " << kelintas << " bandyma " << endl;
    fr << endl;

    ofstream transakciju_perziura;
    transakciju_perziura.open("transakcijos.txt", fstream::trunc);

    transakciju_perziura << setw(35) << " SIUNTĖJAS ";
    transakciju_perziura << setw(70) << " GAVĖJAS ";
    transakciju_perziura << setw(50) << " SIUNČIAMA SUMA " <<endl;
    transakciju_perziura <<endl;

    for (int i = 0; i < blockchain_blocks.at(0).transactions.size(); i++)
        transakciju_perziura << blockchain_blocks.at(0).transactions.at(i).sender_public_key << " > " << blockchain_blocks.at(0).transactions.at(i).recipient_public_key
                             << " | persiunčia: " << transactions.at(i).sum << " valiutos" << endl;

    transakciju_perziura.close();
    fr.close();
}