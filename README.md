
# Blokų grandinių technologijos 2-oji užduotis (v0.2)

## Programos veikimas:
- Realizuotas ***Merkle Root Hash*** pagal binarinį ***Merkle tree*** veikimą
- Sukurtas balanso tikrinimas: yra patikrinama ar siuntėjas siunčia tokią sumą kuri neviršija siuntėjo balanso. Kitu atveju, transakcija yra ištrinama iš transakcijų ***pool'o*** 
- Sukurtas transakcijos ***hash'o*** tikrinimas: yra patikrinama ar transakcijos informacijos ***hash'as*** sutampa su transakcijos ID. Taip apsisaugoma nuo suklastotų transakcijų
- Sudaromi penki nauji potencialūs blokai (kadidatai): **1, 2, 3, 4, 5**, kurie yra sudaryti iš 100 transakcijų
- Yra nustatomas fiksuotas kiekis bandymų kiek kartų bus bandyta parinkti reikiamų savybių ***hash'ą***, kuris tenkinktų ***Difficulty target***. Jeigu nebuvo rastas blokas, kuris tenkintu savybes, tai yra pereinama prie kitų likusių kandidatų (***block'ų***)
- Jeigu nebuvo rastas nei vienas ***block'as***, kuris tenkintu savybes, tai yra didinamas ***hash'avimo*** bandymų skaičius
- Į failą **result.txt** spausdinama atrinkto ***block'o*** informacija: ***Hash, Timestamp, Version, Merkel Root Hash, Nonce, Difficulty, Number of transactions, Tries ir per kiek bandymų buvo surastas reikiamas hash'as***
- Į failą **transakcijos.txt** spausdinama atrinkto ***block'o*** siuntejų ir gavėjų ***public_key*** bei siunčiama suma

##  Failas: **result.txt**

```
Block of the blockchain 4: 
Hash: 0808fd940000f59c0808fd940000f59c0808fd940000f59c0808fd940000f59c
Timestamp: Wed Nov 02 19:06:08 2022
Version: 0.2
Merkel Root Hash: bf2a3fb9a720df28e618d5c85557cdcef5c60cb6fb667bf5e36c1b6422541104
Nonce: 20093
Difficulty: 1
Number of transactions: 100
Tries: 12
Reikiamu savybiu hashas surastas per: 2 bandyma 
```

##  Failas: **transakcijos.txt**
```
                        SIUNTĖJAS                                                              GAVĖJAS                                   SIUNČIAMA SUMA 

7f5ea61d6faccf5b069c1d7444330dc26d71a4b2bb9ae259abe80b9742d859b0 > b392ea6f894669f5be1c1d744441e328c3d718fe7756ae234d0a2db972d0d138 | persiunčia: 96 valiutos
b392ea5e872447d38bf8d93000fcadc26d71a196ffde269ac360831fc734157c > c4a3fb9200bdd06c47f9ea411130265bf60a6d9700ef37de4cf91ca88335268d | persiunčia: 197 valiutos
6e4d95e9350225b149d9ea4111edb106a1b5c5dd66459de13d0a2db941d1e249 > f25a517511fc98d33b1b3a1a993559bcd09373db72dad1f5917c1853bb9bba9a | persiunčia: 290 valiutos
6e4d952c4e9bbe4a157b0c633342ecb15c60b391aa89d1688ad7fa8651b748af > 369e95b99530dc177f9f7e5edd79ddf014d7b75fb61e153915b05c97ff1ffede | persiunčia: 214 valiutos
e6c51dc60e9bbe4a37b384ebbbecacb15c60d5d9220159024ad7fa8673ffc027 > e6c51d82ca577a06bf3b0c633320e0f590a4d5d9220159ce0693b642fb7748af | persiunčia: 185 valiutos
```

# Blokų grandinių technologijos 2-oji užduotis (v0.1)

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
