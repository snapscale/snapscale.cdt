#include <eosio/eosio.hpp>
#include <eosio/tester.hpp>

using namespace eosio;
using namespace eosio::native;

int testnum = 0;
int primary_key = 0;

class [[eosio::contract]] ncomplexsingle : public contract {
   public:
      using contract::contract;

      ncomplexsingle(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}

      [[eosio::action]]
         void insert(uint64_t pk, name user, uint64_t secondary) {
            eosio::print_f("INSERT\n");
            eosio::print_f("pk: % -- user: % -- secondary %\n", pk, user, secondary);
            address_index addresses( get_self(), get_first_receiver().value );
            auto itr = addresses.find(pk);
            check(itr == addresses.end(), "This record already exists");
            addresses.emplace(get_self(), [&]( auto& row ) {
               row.key = pk;
               row.user = user;
               row.secondary = secondary;
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
            eosio::print_f("MOVE\n");
            address_index addresses( get_self(), get_first_receiver().value);

            auto itr = addresses.begin();
            itr++;
            itr++;
            itr--;
            itr--;
            itr--;
         }

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

   private:
      struct [[eosio::table]] person {
         uint64_t key;
         name user;
         uint64_t secondary;
         uint64_t primary_key() const { return key; }
         uint64_t by_secondary() const { return secondary; }
      };
      typedef eosio::multi_index<"people"_n, person, indexed_by<
         name("secondary"), const_mem_fun<person, uint64_t, &person::by_secondary>
      >> address_index;

};

EOSIO_DISPATCH(ncomplexsingle, (insert))
