#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract]] wcomplexsingle : public contract {
   public:
      using contract::contract;

      wcomplexsingle(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}

      [[eosio::action]]
         void insert(uint64_t pk, name user) {
            eosio::print_f("INSERT\n");
            address_index addresses( get_self(), get_first_receiver().value );
            auto itr = addresses.find(pk);
            check(itr == addresses.end(), "This record already exists");
            addresses.emplace(get_self(), [&]( auto& row ) {
               row.key = pk;
               row.user = user;
            });
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
         void erase(uint64_t pk) {
            eosio::print_f("ERASE\n");
            address_index addresses( get_self(), get_first_receiver().value);

            auto itr = addresses.find(pk);
            check(itr != addresses.end(), "Record does not exist but should");
            addresses.erase(itr);
            itr = addresses.find(pk);
            check(itr == addresses.end(), "Record exists when it shouldn't");
         }

      [[eosio::action]]
         void move(uint64_t pk) {
            eosio::print_f("MOVE --- ");
            address_index addresses( get_self(), get_first_receiver().value);

            auto itr = addresses.begin();
            eosio::print_f("iter % %--- ", itr->user, itr->key);
            itr++;
            eosio::print_f("iter % %--- ", itr->user, itr->key);
            itr++;
            eosio::print_f("iter % %--- ", itr->user, itr->key);
            itr--;
            eosio::print_f("iter % %--- ", itr->user, itr->key);
            itr--;
            eosio::print_f("iter % %--- ", itr->user, itr->key);
            // itr--;
            // eosio::print_f("iter % %--- ", itr->user, itr->key);
         }

      [[eosio::action]]
         void erase2(uint64_t pk) {
            eosio::print_f("ERASE2 --- ");
            address_index addresses( get_self(), get_first_receiver().value);

            auto itr = addresses.end();
            itr--;
            eosio::print_f("iter % %--- ", itr->user, itr->key);
            addresses.erase(itr);
         }

      [[eosio::action]]
         void erase3(uint64_t pk) {
            eosio::print_f("ERASE3 --- ");
            address_index addresses( get_self(), get_first_receiver().value);

            auto itr = addresses.begin();
            eosio::print_f("iter %__", itr->user);
            itr++;
            eosio::print_f("iter %__", itr->user);
            addresses.erase(itr);
            eosio::print_f("iter %__", itr->user);
            itr++;
            eosio::print_f("iter %__", itr->user);
            itr--;
            eosio::print_f("iter %__", itr->user);
#if 0
            auto itr = addresses.begin();
            eosio::print_f("iter %__", itr->user);
            itr = addresses.erase(itr);
            eosio::print_f("iter %__", itr->user);
            itr++;
            eosio::print_f("iter %__", itr->user);
#endif 
         }

   private:
      struct [[eosio::table]] person {
         uint64_t key;
         name user;
         uint64_t primary_key() const { return key; }
      };
      typedef eosio::multi_index<"people"_n, person> address_index;

};

EOSIO_DISPATCH(wcomplexsingle, (insert)(modify)(erase)(erase2)(erase3)(move))
