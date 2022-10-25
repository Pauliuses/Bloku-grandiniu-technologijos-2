#include "func.hpp"

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

        transakcijos.push_back(new_transaction);
    }
    return transakcijos;
}