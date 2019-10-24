#include <eosio/eosio.hpp>
#include <eosio/tester.hpp>

using namespace eosio;
using namespace eosio::native;

int testnum = 0;

class [[eosio::contract]] addressbookn : public contract {

   public:
      using contract::contract;

      addressbookn(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}

      [[eosio::action]]
         void upsert(name user, name user2) {
            print_f("\trequire_auth\n");
            print_f("\t%\n", user.to_string());
            print_f("\t%\n", user2.to_string());
            require_auth( user );
            address_index addresses( get_self(), get_first_receiver().value );
            print_f("\tfind\n");
            auto iterator = addresses.find(user.value);
            print_f("\tpost-find\n");
            if( iterator == addresses.end() ) {
               print_f("\tinsert\n");
               addresses.emplace(user, [&]( auto& row ) {
                  row.key = user;
                  row.user = user2;
               });
               print_f("\tpost-insert\n");
            }
            else {
               print_f("\tmodify\n");
               addresses.modify(iterator, user, [&]( auto& row ) {
                  row.user = user2;
               });
               print_f("\tpost-modify\n");
            }
         }

      [[eosio::action]]
         void erase(name user) {
            require_auth(user);

            address_index addresses( get_self(), get_first_receiver().value);

            auto iterator = addresses.find(user.value);
            check(iterator != addresses.end(), "Record does not exist");
            addresses.erase(iterator);

            auto it2 = addresses.find(user.value);
            check(it2 == addresses.end(), "Record should not exist");
         }

   private:
      struct [[eosio::table]] person {
         name key;
         name user;
         uint64_t primary_key() const { return key.value; }
      };
      typedef eosio::multi_index<"people"_n, person> address_index;

};

EOSIO_DISPATCH(addressbookn, (upsert)(erase))

EOSIO_TEST_BEGIN(addressbookn_test)
   intrinsics::set_intrinsic<intrinsics::read_action_data>(
         [](void* m, uint32_t len) {
            check(len <= 2*sizeof(eosio::name), "failed from read_action_data");
            uint64_t pk;
            uint64_t user;
            pk = eosio::name("bob").value;
            if (testnum == 0) {
               user = eosio::name("alice").value;
            } else {
               user = eosio::name("joe").value;
            }

            memcpy(m, &pk, sizeof(eosio::name));
            memcpy((char*)m + sizeof(eosio::name), &user, sizeof(eosio::name));
            return len; 
         });

   intrinsics::set_intrinsic<intrinsics::action_data_size>(
         []() {
            return (uint32_t)2*sizeof(eosio::name);
         });

   intrinsics::set_intrinsic<intrinsics::require_auth>(
         [](capi_name nm) {
         });

   intrinsics::set_intrinsic<intrinsics::current_receiver>(
         []() {
            return eosio::name{"test"}.value;
         });


   print_f("---First Apply---\n");
   apply("test"_n.value, "test"_n.value, "upsert"_n.value);

   testnum = 1;

   print_f("---Second Apply---\n");
   apply("test"_n.value, "test"_n.value, "upsert"_n.value);

   print_f("---Third Apply---\n");
   apply("test"_n.value, "test"_n.value, "remove"_n.value);
EOSIO_TEST_END

int main(int argc, char** argv) {
   silence_output(false);
   EOSIO_TEST(addressbookn_test);
   return has_failed();
}
