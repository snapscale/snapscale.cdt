#include <eosio/eosio.hpp>
#include <eosio/tester.hpp>

using namespace eosio;
using namespace eosio::native;

int testnum = 0;
uint64_t pk = 0;

class [[eosio::contract]] addressbookn : public contract {

   public:
      using contract::contract;

      addressbookn(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}

      [[eosio::action]]
         void insert(uint64_t pk, name user1, name user2) {
            address_index addresses( get_self(), get_first_receiver().value );
            address_index addresses2( get_self(), get_first_receiver().value );

            auto it = addresses.find(pk);
            if( it == addresses.end() ) {
               print_f("\tinsert\n");
               addresses.emplace(user1, [&]( auto& row ) {
                  row.key = pk;
                  row.user1 = user1;
                  row.user2 = user2;
               });
            }

            auto it2 = addresses2.find(pk);
            if( it2 == addresses2.end() ) {
               print_f("\tinsert\n");
               addresses2.emplace(user1, [&]( auto& row ) {
                  row.key = pk;
                  row.user1 = user1;
                  row.user2 = user2;
               });
            }
         }

      [[eosio::action]]
         void modify(uint64_t pk, name user1, name user2) {
            address_index addresses( get_self(), get_first_receiver().value );
            address_index addresses2( get_self(), get_first_receiver().value );

            auto it = addresses.find(pk);
            print_f("\tmodify\n");
            addresses.modify(it, user1, [&]( auto& row ) {
               row.user1 = user1;
               row.user2 = user2;
            });

            auto it2 = addresses2.find(pk);
            print_f("\tmodify\n");
            addresses2.modify(it2, user1, [&]( auto& row ) {
               row.user1 = user1;
               row.user2 = user2;
            });
         }

      [[eosio::action]]
         void erase(uint64_t pk) {
            address_index addresses( get_self(), get_first_receiver().value);
            address_index addresses2( get_self(), get_first_receiver().value);

            auto it = addresses.find(pk);
            check(it != addresses.end(), "Record does not exist");
            addresses.erase(it);

            auto it2 = addresses.find(pk);
            check(it2 == addresses.end(), "Record should not exist");

            auto it3 = addresses2.find(pk);
            check(it3 != addresses2.end(), "Record does not exist");
            addresses2.erase(it3);

            auto it4 = addresses2.find(pk);
            check(it4 == addresses2.end(), "Record should not exist");
         }

   private:
      struct [[eosio::table]] person {
         uint64_t key;
         name user1;
         name user2;
         uint64_t primary_key() const { return key; }
      };
      typedef eosio::multi_index<"people"_n, person> address_index;
};

EOSIO_DISPATCH(addressbookn, (insert)(modify)(erase))

EOSIO_TEST_BEGIN(addressbookn_test)
   intrinsics::set_intrinsic<intrinsics::read_action_data>(
         [](void* m, uint32_t len) {
            check(len <= (2*sizeof(eosio::name) + sizeof(uint64_t)), "failed from read_action_data");
            uint64_t user2;

            uint64_t user1 = eosio::name("bob").value;
            if (testnum == 0) {
               user2 = eosio::name("alice").value;
            } else {
               user2 = eosio::name("joe").value;
            }

            memcpy(m, &pk, sizeof(uint64_t));
            memcpy((char*)m + sizeof(uint64_t), &user1, sizeof(eosio::name));
            memcpy((char*)m + sizeof(uint64_t) + sizeof(eosio::name), &user2, sizeof(eosio::name));
            return len; 
         });

   intrinsics::set_intrinsic<intrinsics::action_data_size>(
         []() {
            return (uint32_t)(2*sizeof(eosio::name) + sizeof(uint64_t));
         });

   intrinsics::set_intrinsic<intrinsics::require_auth>(
         [](capi_name nm) {
         });

   intrinsics::set_intrinsic<intrinsics::current_receiver>(
         []() {
            return eosio::name{"test"}.value;
         });


   print_f("---First Apply---\n");
   apply("test"_n.value, "test"_n.value, "insert"_n.value);

#if 0
   testnum = 1;

   print_f("---Second Apply---\n");
   apply("test"_n.value, "test"_n.value, "upsert"_n.value);

   print_f("---Third Apply---\n");
   apply("test"_n.value, "test"_n.value, "remove"_n.value);
#endif
EOSIO_TEST_END

int main(int argc, char** argv) {
   silence_output(false);
   EOSIO_TEST(addressbookn_test);
   return has_failed();
}
