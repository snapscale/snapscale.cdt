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
            address_index addresses( get_self(), get_first_receiver().value );
            auto itr = addresses.find(pk);
            check(itr == addresses.end(), "This record already exists");
            addresses.emplace(get_self(), [&]( auto& row ) {
               row.key = pk;
               row.user = user;
               row.secondary1 = secondary;
               row.secondary2 = secondary;
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
         double secondary3;
         uint64_t primary_key() const { return key; }
         uint64_t by_secondary_1() const { return secondary1; }
         uint64_t by_secondary_2() const { return secondary2; }
         double by_secondary_3() const { return secondary3; }
      };
      typedef eosio::multi_index<"peoples"_n, person,
         indexed_by<name("secondary1"), const_mem_fun<person, uint64_t, &person::by_secondary_1>>,
         indexed_by<name("secondary2"), const_mem_fun<person, uint64_t, &person::by_secondary_2>>,
         indexed_by<name("secondary3"), const_mem_fun<person, double, &person::by_secondary_3>>
      > address_index;

};

EOSIO_DISPATCH(ncomplexsingle, (insert)(get)(modify)(move)(erase))

EOSIO_TEST_BEGIN(ncomplexsingle_test)
   intrinsics::set_intrinsic<intrinsics::read_action_data>(
      [](void* m, uint32_t len) {
         check(len <= 3*sizeof(eosio::name), "failed from read_action_data");
         uint64_t pk = primary_key;
         uint64_t user;
         uint64_t secondary = (-primary_key) + 10;

         switch (testnum) {
         case 0:
            user = eosio::name("bob").value;
            break;
         case 1:
            user = eosio::name("alice").value;
            break;
         case 2:
            user = eosio::name("john").value;
            break;
         case 3:
            user = eosio::name("lucy").value;
            break;
         }

         memcpy(m, &pk, sizeof(uint64_t));
         memcpy((char*)m + sizeof(eosio::name), &user, sizeof(eosio::name));
         memcpy((char*)m + 2*sizeof(uint64_t), &secondary, sizeof(uint64_t));
         return len; 
      }
   );

   intrinsics::set_intrinsic<intrinsics::action_data_size>(
      []() {
         return (uint32_t)3*sizeof(eosio::name);
      }
   );

   intrinsics::set_intrinsic<intrinsics::current_receiver>(
      []() {
         return eosio::name{"test"}.value;
      }
   );


   testnum = 0;
   primary_key = 0;
   apply("test"_n.value, "test"_n.value, "insert"_n.value);

#if 0
   testnum = 1;
   primary_key = 1;
   apply("test"_n.value, "test"_n.value, "insert"_n.value);

   testnum = 2;
   primary_key = 2;
   apply("test"_n.value, "test"_n.value, "insert"_n.value);

   testnum = 3;
   primary_key = 3;
   apply("test"_n.value, "test"_n.value, "insert"_n.value);

   primary_key = 2;
   apply("test"_n.value, "test"_n.value, "get"_n.value);

   testnum = 3;
   primary_key = 1;
   apply("test"_n.value, "test"_n.value, "modify"_n.value);

   primary_key = 1;
   apply("test"_n.value, "test"_n.value, "move"_n.value);

   testnum = 3;
   primary_key = 1;
   apply("test"_n.value, "test"_n.value, "erase"_n.value);

   primary_key = 1;
   apply("test"_n.value, "test"_n.value, "move"_n.value);

   primary_key = 1;
   apply("test"_n.value, "test"_n.value, "erase"_n.value);

   testnum = 3;
   primary_key = 1;
   apply("test"_n.value, "test"_n.value, "erase2"_n.value);
#endif

EOSIO_TEST_END

int main(int argc, char** argv) {
   silence_output(false);
   EOSIO_TEST(ncomplexsingle_test);
   return has_failed();
}
