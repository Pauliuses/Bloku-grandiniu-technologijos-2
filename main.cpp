#include "func.hpp"

int main()
{


    vector<user> useriai = generate_user(1000);
    vector<transac> transakcijos = generate_transactions(10000, useriai);

    vector<block_header> blockchain_blocks;

    int difficulty = 1;
    int x = 0;

    ofstream out;
    out.open("result.txt", fstream::trunc);

    while (transakcijos.size() > 0)
    {
        //cout << " here " <<endl;
            //cout << "here " <<endl;
            int counting_0 = 0;
            unsigned int number = random_numbers(0, INT_MAX);
            string number_hash = Hashing(to_string(number));


            for (int j = 0; j < difficulty; j++)
            {
                if (number_hash[j] == '0')
                    counting_0++;
            }


            if (counting_0 == difficulty)
            {
                blockchain_blocks.push_back(gen_block(difficulty, number, transakcijos, x));

                print_to_file(blockchain_blocks, x);

                x++;
            }
    }
}