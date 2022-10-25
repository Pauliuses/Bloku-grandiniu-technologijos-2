#include "func.hpp"

int main()
{

    ofstream out;
    out.open("result.txt", fstream::trunc);

    vector<user> useriai = generate_user(1000);
    vector<transac> transakcijos = generate_transactions(10000, useriai);

    vector<block_header> blocks;

    int difficulty_target = 2;
    int i = 0;

    while (transakcijos.size() > 0)
    {
        while (true)
        {
            int diff_0_found = 0;
            unsigned int numonce = random_numbers(0, INT_MAX);
            string numonce_hash = Hashing(to_string(numonce));


            for (int j = 0; j < difficulty_target; j++)
            {
                if (numonce_hash[j] == '0')
                    diff_0_found++;
            }


            if (diff_0_found == difficulty_target)
            {
                blocks.push_back(gen_block(difficulty_target, numonce, transakcijos, i));
                cout << " cia " <<endl;

                print_to_file(blocks, i);

                i++;
            }
        }
    }
}