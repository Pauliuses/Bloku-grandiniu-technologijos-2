#include "func.hpp"

int main()
{

    vector<user> useriai = generate_user(1000);
    vector<transac> transakcijos = generate_transactions(10000, useriai);

    vector<block_header> blockchain_blocks;
    vector<int> candidates = {1, 2, 3, 4, 5};

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
        // cout << " here " <<endl;
        // cout << "here " <<endl;
        // cout << blockchain_blocks.size() <<endl;
        shuffle(candidates.begin(), candidates.end(), std::default_random_engine(seed));
        int counting_0 = 0;

        unsigned int number = random_numbers(0, INT_MAX);
        // cout << number <<endl;
        string number_hash = Hashing(to_string(number));
        // cout << number_hash <<endl;
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
            // cout << y << "is pirmo" << endl;
            //  cout << number_hash <<endl;
            //  break;
            print_to_file(blockchain_blocks, x, y, bandymas);
            check++;
            break;
        }
        if (y > fiksuotas_kiekis - 1)
            break;
    }

    if (check < 1)
    {
        blockchain_blocks.resize(0);
        // cout << blockchain_blocks.size() <<endl;
        y = 0;

        while (blockchain_blocks.size() < 5)
        {
            int bandymas = 2;
            // cout << " here " <<endl;
            // cout << "here " <<endl;
            // cout << blockchain_blocks.size() <<endl;
            shuffle(candidates.begin(), candidates.end(), std::default_random_engine(seed));
            int counting_0 = 0;

            unsigned int number = random_numbers(0, INT_MAX);
            // cout << number <<endl;
            string number_hash = Hashing(to_string(number));
            // cout << number_hash <<endl;
            y++;

            for (int j = 0; j < difficulty; j++)
            {
                if (number_hash[j] == '0')
                    counting_0++;
            }

            if (counting_0 == difficulty && y < 40)
            {
                blockchain_blocks.push_back(blocks_generation(difficulty, number, transakcijos, candidates[x]));
                x++;
                cout << y << endl;
                // cout << number_hash <<endl;
                // break;
                print_to_file(blockchain_blocks, x, y, bandymas);
                break;
            }
        }
    }
}