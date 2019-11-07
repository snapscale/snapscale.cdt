#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract]] wcomplexsecondary : public contract {
   public:
      using contract::contract;

      wcomplexsecondary(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}

      [[eosio::action]]
         void insert(uint64_t pk, name user, uint64_t secondary) {
            eosio::print_f("INSERT\n");
            address_index addresses( get_self(), get_first_receiver().value );
            auto itr = addresses.find(pk);
            check(itr == addresses.end(), "This record already exists");
            addresses.emplace(get_self(), [&]( auto& row ) {
               row.key = pk;
               row.user = user;
               row.secondary1 = secondary;
               row.secondary2 = secondary * 2;
            });
         }

      [[eosio::action]]
         void get(uint64_t pk) {
            eosio::print_f("GET\n");
            address_index addresses( get_self(), get_first_receiver().value );

            auto sec = addresses.get_index<name("secondary1")>();

            auto sitr = sec.find(9);

            sitr = sec.lower_bound(9);
            sitr = sec.upper_bound(8);
         }

      [[eosio::action]]
         void modify(uint64_t pk, name user) {
            eosio::print_f("MODIFY\n");
            address_index addresses( get_self(), get_first_receiver().value );
            auto itr = addresses.find(pk);
            check(itr != addresses.end(), "This record does not exist");
            addresses.modify(itr, get_self(), [&]( auto& row ) {
               row.user = user;
            });
         }

      [[eosio::action]]
         void move(uint64_t pk) {
            eosio::print_f("MOVE\n");
            address_index addresses( get_self(), get_first_receiver().value );

            auto sec = addresses.get_index<name("secondary1")>();

            auto sitr = sec.find(9);
            auto send = sec.end();

            sitr--;
            sitr++;
            sitr++;
            sitr--;
            sitr++;
         }

      [[eosio::action]]
         void erase(uint64_t pk) {
            eosio::print_f("ERASE\n");
            address_index addresses( get_self(), get_first_receiver().value);
            auto sec = addresses.get_index<name("secondary1")>();
            auto sitr = sec.find(9);

            check(sitr != sec.end(), "Record does not exist but should");
            sec.erase(sitr);
            sitr = sec.find(9);
            check(sitr == sec.end(), "Record exists when it shouldn't");
         }

#if 0
      [[eosio::action]]
         void move2(uint64_t pk) {
            eosio::print_f("MOVE2\n");
            address_index addresses( get_self(), get_first_receiver().value);

            auto& obj = addresses.get(1);
            auto itr = addresses.iterator_to(obj);
         }

      [[eosio::action]]
         void erase2(uint64_t pk) {
            eosio::print_f("ERASE2\n");
            address_index addresses( get_self(), get_first_receiver().value);

            auto itr = addresses.end();
            itr--;
            addresses.erase(itr);
         }

      [[eosio::action]]
         void erase3(uint64_t pk) {
            eosio::print_f("ERASE3\n");
            address_index addresses( get_self(), get_first_receiver().value);

            auto itr = addresses.begin();
            itr++;
            itr++;
            addresses.erase(itr);
         }
#endif

   private:
      struct [[eosio::table]] person {
         uint64_t key;
         name user;
         uint64_t secondary1;
         uint64_t secondary2;
         // double secondary3;
         uint64_t primary_key() const { return key; }
         uint64_t by_secondary_1() const { return secondary1; }
         uint64_t by_secondary_2() const { return secondary2; }
         // double by_secondary_3() const { return secondary3; }
      };
      typedef eosio::multi_index<"people"_n, person,
         indexed_by<name("secondary1"), const_mem_fun<person, uint64_t, &person::by_secondary_1>>,
         indexed_by<name("secondary2"), const_mem_fun<person, uint64_t, &person::by_secondary_2>>
         // indexed_by<name("secondary3"), const_mem_fun<person, double, &person::by_secondary_3>>
      > address_index;

};

EOSIO_DISPATCH(wcomplexsecondary, (insert)(get)(modify)(move)(erase))
