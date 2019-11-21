#include <eosio/eosio.hpp>
#include <eosio/tester.hpp>

using namespace eosio;
using namespace eosio::native;

struct [[eosio::table]] person {
   uint64_t key;
   name user;
   uint64_t secondary1;
   checksum256 secondary2;
   uint64_t primary_key() const { return key; }
   uint64_t by_secondary_1() const { return secondary1; }
   checksum256 by_secondary_2() const { return secondary2; }
};
typedef eosio::multi_index<"people"_n, person,
   indexed_by<name("secondary1"), const_mem_fun<person, uint64_t, &person::by_secondary_1>>,
   indexed_by<name("secondary2"), const_mem_fun<person, checksum256, &person::by_secondary_2>>
> address_index;

EOSIO_TEST_BEGIN(multi_index_test)
   eosio::name self{"test"};
   intrinsics::set_intrinsic<intrinsics::current_receiver>([&]() { return self.value; });
   address_index addresses( self, self.value );

   std::array<uint64_t, 2> t{1, 2};
   checksum256 chk{t};

   addresses.emplace(self, [&]( auto& row ) {
      row.key = 0;
      row.user = name{"bob"};
      row.secondary1 = 10;
      row.secondary2 = chk;
   });
   addresses.emplace(self, [&]( auto& row ) {
      row.key = 1;
      row.user = name{"alice"};
      row.secondary1 = 9;
      row.secondary2 = chk;
   });
   addresses.emplace(self, [&]( auto& row ) {
      row.key = 2;
      row.user = name{"john"};
      row.secondary1 = 8;
      row.secondary2 = chk;
   });

   auto itr = addresses.find(0);

   CHECK_EQUAL(itr->key, 0);
   CHECK_EQUAL(itr->user, name{"bob"});
   CHECK_EQUAL(itr->secondary1, 10);

   addresses.modify(itr, self, [&]( auto& row ) {
      row.user = name{"bruce"};
      row.secondary1 = 5;
   });

   itr = addresses.find(0);

   CHECK_EQUAL(itr->key, 0);
   CHECK_EQUAL(itr->user, name{"bruce"});
   CHECK_EQUAL(itr->secondary1, 5);

   itr = addresses.find(0);
   CHECK_NOT_EQUAL(itr, addresses.end());

   addresses.erase(itr);
   itr = addresses.find(0);
   CHECK_EQUAL(itr, addresses.end());

   itr = addresses.find(1);
   itr++;
   CHECK_EQUAL(itr->user, name{"john"});
   itr--;
   CHECK_EQUAL(itr->user, name{"alice"});
EOSIO_TEST_END

EOSIO_TEST_BEGIN(multi_index_remove_test)
   eosio::name self{"test"};
   intrinsics::set_intrinsic<intrinsics::current_receiver>([&]() { return self.value; });
   address_index addresses( self, self.value );

   std::array<uint64_t, 2> t{1, 2};
   checksum256 chk{t};

   addresses.emplace(self, [&]( auto& row ) {
      row.key = 0;
      row.user = name{"a"};
      row.secondary1 = 10;
      row.secondary2 = chk;
   });
   addresses.emplace(self, [&]( auto& row ) {
      row.key = 1;
      row.user = name{"b"};
      row.secondary1 = 9;
      row.secondary2 = chk;
   });
   addresses.emplace(self, [&]( auto& row ) {
      row.key = 2;
      row.user = name{"c"};
      row.secondary1 = 8;
      row.secondary2 = chk;
   });
   addresses.emplace(self, [&]( auto& row ) {
      row.key = 3;
      row.user = name{"d"};
      row.secondary1 = 7;
      row.secondary2 = chk;
   });
   addresses.emplace(self, [&]( auto& row ) {
      row.key = 4;
      row.user = name{"e"};
      row.secondary1 = 6;
      row.secondary2 = chk;
   });

   auto itr = addresses.find(0);
   addresses.erase(itr);

   /*
   itr = addresses.find(3);
   addresses.erase(itr);
   */
EOSIO_TEST_END
#if 0
EOSIO_TEST_BEGIN(multi_index_secondary_index_test)
   intrinsics::set_intrinsic<intrinsics::current_receiver>([]() { return eosio::name{TEST_NAME}.value; });

   eosio::name self{TEST_NAME};
   address_index addresses( self, eosio::name{TEST_NAME}.value );
   auto itr = addresses.find(0);
   check(itr == addresses.end(), "This record already exists");
   std::array<uint128_t, 2> t = {1,2};
   eosio::checksum256 chk{t};
   addresses.emplace(self, [&]( auto& row ) {
      row.key = 0;
      row.user = eosio::name{"bob"};
      row.secondary1 = 10;
      row.secondary2 = 10 * 2;
      row.secondary3 = chk;
   });

   auto sec = addresses.get_index<name("secondary1")>();
   auto sitr = sec.find(10);

   CHECK_EQUAL(sitr->key, 0);
   CHECK_EQUAL(sitr->user, eosio::name{"bob"});

EOSIO_TEST_END
#endif

int main(int argc, char** argv) {
   silence_output(false);
   EOSIO_TEST(multi_index_remove_test);
   return has_failed();
}
