#include <eosio/eosio.hpp>
#include <eosio/tester.hpp>

using namespace eosio;
using namespace eosio::native;

class [[eosio::contract]] multiidxtest : public contract {
   public:
      using contract::contract;

      multiidxtest(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}

      [[eosio::action]]
      void insert(uint64_t pk, name user, uint64_t secondary) {
         address_index addresses( get_self(), get_first_receiver().value );
         auto itr = addresses.find(pk);
         check(itr == addresses.end(), "This record already exists");
         std::array<uint128_t, 2> t = {1,2};
         eosio::checksum256 chk{t};
         addresses.emplace(get_self(), [&]( auto& row ) {
            row.key = pk;
            row.user = user;
            row.secondary1 = secondary;
            row.secondary2 = secondary * 2;
            row.secondary3 = chk;
         });
         eosio::print_f("Insert: %, %", pk, user);
      }

      [[eosio::action]]
      void getsec(uint64_t pk) {
         address_index addresses( get_self(), get_first_receiver().value );

         auto sec = addresses.get_index<name("secondary1")>();
         auto sitr = sec.find(10);

         eosio::print_f("Get: %, %", sitr->key, sitr->user);
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
         eosio::print_f("ERASE: Find 1\n");
         auto sitr = sec.find(9);

         check(sitr != sec.end(), "Record does not exist but should");
         sec.erase(sitr);
         eosio::print_f("ERASE: Find 2\n");
         sitr = sec.find(9);
         check(sitr == sec.end(), "Record exists when it shouldn't");
      }

   private:
      struct [[eosio::table]] person {
         uint64_t key;
         name user;
         uint64_t secondary1;
         uint64_t secondary2;
         checksum256 secondary3;
         uint64_t primary_key() const { return key; }
         uint64_t by_secondary_1() const { return secondary1; }
         uint64_t by_secondary_2() const { return secondary2; }
         checksum256 by_secondary_3() const { return secondary3; }
      };
      typedef eosio::multi_index<"people"_n, person,
         indexed_by<name("secondary1"), const_mem_fun<person, uint64_t, &person::by_secondary_1>>,
         indexed_by<name("secondary2"), const_mem_fun<person, uint64_t, &person::by_secondary_2>>,
         indexed_by<name("secondary3"), const_mem_fun<person, checksum256, &person::by_secondary_3>>
      > address_index;

};

EOSIO_DISPATCH(multiidxtest, (insert)(getsec)(modify)(move)(erase))

void set_read_action_data(const uint64_t primary_key, const eosio::name user, const uint64_t secondary) {
   intrinsics::set_intrinsic<intrinsics::read_action_data>(
      [&, primary_key, user, secondary](void *m, uint32_t len) {
         check(len <= 3*sizeof(eosio::name), "failed from read_action_data");

         memcpy(m, &primary_key, sizeof(uint64_t));
         memcpy((char *)m + sizeof(uint64_t), &user, sizeof(eosio::name));
         memcpy((char *)m + 2*sizeof(uint64_t), &secondary, sizeof(uint64_t));
         return len;
      }
   );
}

void set_action_data_size() {
   intrinsics::set_intrinsic<intrinsics::action_data_size>(
      [&]() {
         return (uint32_t)3*sizeof(eosio::name);
      }
   );
}

EOSIO_TEST_BEGIN(multi_index_test)
   intrinsics::set_intrinsic<intrinsics::current_receiver>(
      []() {
         return eosio::name{"test"}.value;
      }
   );

   CHECK_PRINT("Insert: 0, bob",
      []() {
         set_action_data_size();
         int pk = 0;
         int secondary = (-pk) + 10;
         set_read_action_data(pk, eosio::name{"bob"}, secondary);
         apply("test"_n.value, "test"_n.value, "insert"_n.value);
      }
   );

   CHECK_PRINT("Get: 0, bob",
      []() {
         set_action_data_size();
         int pk = 0;
         int secondary = (-pk) + 10;
         set_read_action_data(pk, eosio::name{"bob"}, secondary);
         apply("test"_n.value, "test"_n.value, "getsec"_n.value);
      }
   );

EOSIO_TEST_END

int main(int argc, char** argv) {
   silence_output(true);
   EOSIO_TEST(multi_index_test);
   return has_failed();
}
