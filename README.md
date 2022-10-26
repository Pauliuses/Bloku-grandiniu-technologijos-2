# Blokų grandinių technologijos 2

## Programos veikimas:
- Sugeneruojama 1000 vartotojų funkcijoje **_generate_user(int)_**, kurie pavadinti: "Useris: 1", "Useris: 2", "Useris 3".... ir jų **_public_key_** yra sukuriamas suhashuojant vardą. Taip pat jiems priskiriamas balansas nuo 1000 iki 1000000
- Sugeneruojama 10000 transakcijų funkcijoje **_generate_transactions(int, vector<user>)_**, kur parenkami siuntėjas ir gavėjas, transakcijos suma ir iš jų yra sudaromas hash kodas
- Tikrinamas sukurto **_nonce_** sudėtingumas ar atitinka nustatytąjį.
- Jeigu **_nonce_** sudėtingumas atitinka, pereinama prie funkcijos **_gen_block(int, int, vector<transac> &, int)_** kur **_merkel_root_hash_** yra gaunamas suhashinus visas transakcijas, kurios yra bloke. Taip pat tos transakcijos yra pašalinamos. 
  
## Informacija apie blokus yra pateikiama tekstiniame faile **_result.txt_**:
  
```
Block of the blockchain 1: 
Hash: 07c4b908621f42169f405b71ead969ae1be2c4f9a4f0f12abd5b4cb3cb887dcc
Timestamp: Wed Oct 26 22:52:04 2022
Version: 0.1
Merkel Root Hash: 1bd93b750daea046c49075bb955767800a282e72df9dff39c162640a8854397f
Nonce: 5950
Difficulty: 1
Number of transactions: 100
```

## Kaip pasileisti programą:
- Parsisiųsti ir įsidiegti C++ kompiliatorių
- Norint sukompiliuoti programą terminale rašykite make
- Norint paleisti programą terminale rašykite ./prog
