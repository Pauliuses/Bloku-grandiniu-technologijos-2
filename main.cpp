#include "func.hpp"

int main()
{

    vector<user> useriai = generate_user(1000);
    vector<transac> transakcijos = generate_transactions(10000, useriai);

    vector<block_header> blockchain_blocks;
    vector<int> candidates = {1, 2, 3, 4, 5}; // sudaromi 5 potencialus kandidatai

    int difficulty = 1;
    int x = 0;
    int y = 0;
    int check = 0;
    int fiksuotas_kiekis = 10;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    ofstream out;
    out.open("result.txt", fstream::trunc);

    srand(time(NULL));

    while (blockchain_blocks.size() < 5)
    {
        int bandymas = 1;

        shuffle(candidates.begin(), candidates.end(), std::default_random_engine(seed)); // parenkamas atsitiktinis blokas-kandidatas
        int counting_0 = 0;

        unsigned int number = random_numbers(0, INT_MAX);

        string number_hash = Hashing(to_string(number));
        y++;

        for (int j = 0; j < difficulty; j++)
        {
            if (number_hash[j] == '0')
                counting_0++;
        }

        if (counting_0 == difficulty && y < fiksuotas_kiekis)
        {
            blockchain_blocks.push_back(blocks_generation(difficulty, number, transakcijos, candidates[x]));
            x++;

            print_to_file(blockchain_blocks, candidates[x], y, bandymas, transakcijos);
            check++;
            break;
        }
        if (y > fiksuotas_kiekis - 1)
            break;
    }

    if (check == 0)
    {
        blockchain_blocks.resize(0);
        y = 0;

        while (blockchain_blocks.size() < 5)
        {
            int bandymas = 2;

            shuffle(candidates.begin(), candidates.end(), std::default_random_engine(seed));
            int counting_0 = 0;

            unsigned int number = random_numbers(0, INT_MAX);
            string number_hash = Hashing(to_string(number));
            y++;

            for (int j = 0; j < difficulty; j++)
            {
                if (number_hash[j] == '0')
                    counting_0++;
            }

            if (counting_0 == difficulty && y < fiksuotas_kiekis*4)
            {
                blockchain_blocks.push_back(blocks_generation(difficulty, number, transakcijos, candidates[x]));
                x++;

                print_to_file(blockchain_blocks, candidates[x], y, bandymas, transakcijos);
                break;
            }
        }
    }
}