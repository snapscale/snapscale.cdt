#include <eosio/eosio.hpp>
#include <eosio/name.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/tester.hpp>

#include <cstring>
#include <string>

using namespace eosio;
using namespace eosio::native;


class [[eosio::contract]] inttestern : public contract {
   public:
      using contract::contract;

      struct [[eosio::table]] testtable {
      };

      [[eosio::action]]
      void hi1(name nm) {
         char data1[5] = { 'a', 'b', 'c', 'd' };

         int32_t it1 = internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               0,
               data1,
               5
         );

         char data2[5] = { 'd', 'c', 'b', 'a' };

         int32_t it2 = internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               1,
               data2,
               5
         );

         char get_data[5];
         int32_t size = internal_use_do_not_use::db_get_i64(it1, &get_data, 5);

         check(size == 5, "wrong size returned from db_get_i64");
         check(std::string(get_data) == "abcd", "wrong data returned from db_get_i64 ---- " + std::string(get_data));
         print_f("data is %\n", get_data);
      }

      [[eosio::action]]
      void hi2(name nm) {
         char data1[5] = { 'a', 'a', 'a', 'a' };
         char data2[5] = { 'b', 'b', 'b', 'b' };
         char data3[5] = { 'c', 'c', 'c', 'c' };
         char data4[5] = { 'd', 'd', 'd', 'd' };

         int32_t it_0 = internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               0,
               data1,
               5
         );

         int32_t it_1 = internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               1,
               data2,
               5
         );

         int32_t it_2 = internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               2,
               data3,
               5
         );

         int32_t it_3 = internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               3,
               data4,
               5
         );

         int32_t it1 = internal_use_do_not_use::db_find_i64(
               "inttester"_n.value,
               "inttester"_n.value,
               "testtable"_n.value,
               0
         );

         int32_t it2 = internal_use_do_not_use::db_find_i64(
               "inttester"_n.value,
               "inttester"_n.value,
               "testtable"_n.value,
               2
         );

         char get_data[5];

         internal_use_do_not_use::db_get_i64(it1, &get_data, 5);
         print_f("data is %\n", get_data);

         internal_use_do_not_use::db_get_i64(it2, &get_data, 5);
         print_f("data is %\n", get_data);
      }

      [[eosio::action]]
      void hi3(name nm) {
         char data1[5] = { 'a', 'a', 'a', 'a' };
         char data2[5] = { 'b', 'b', 'b', 'b' };

         int32_t it_0 = internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               0,
               data1,
               5
         );

         char get_data[5];

         internal_use_do_not_use::db_get_i64(it_0, &get_data, 5);
         print_f("data is %\n", get_data);

         internal_use_do_not_use::db_update_i64(
               it_0,
               nm.value,
               data2,
               5
         );

         internal_use_do_not_use::db_get_i64(it_0, &get_data, 5);
         print_f("data is %\n", get_data);
      }

      [[eosio::action]]
      void hi4(name nm) {
         char data1[5] = { 'a', 'a', 'a', 'a' };
         char data2[5] = { 'b', 'b', 'b', 'b' };
         char data3[5] = { 'c', 'c', 'c', 'c' };
         char data4[5] = { 'd', 'd', 'd', 'd' };

         int32_t it_0 = internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               0,
               data1,
               5
         );

         int32_t it_1 = internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               1,
               data2,
               5
         );

         int32_t it_2 = internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               2,
               data3,
               5
         );

         int32_t it_3 = internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               3,
               data4,
               5
         );
         int32_t lowerbound = internal_use_do_not_use::db_lowerbound_i64(
               "inttester"_n.value,
               "inttester"_n.value,
               "testtable"_n.value,
               1
         );
         print_f("lowerbound is %\n", lowerbound);

         int32_t upperbound = internal_use_do_not_use::db_upperbound_i64(
           "inttester"_n.value,
           "inttester"_n.value,
           "testtable"_n.value,
           2
         );
         print_f("upperbound is %\n", upperbound);

         int32_t end = internal_use_do_not_use::db_end_i64(
           "inttester"_n.value,
           "inttester"_n.value,
           "testtable"_n.value
         );
         print_f("end is %\n", end);
      }

      [[eosio::action]]
      void hi5(name nm) {
         char data1[5] = { 'a', 'a', 'a', 'a' };
         char data2[5] = { 'b', 'b', 'b', 'b' };
         char data3[5] = { 'c', 'c', 'c', 'c' };
         char data4[5] = { 'd', 'd', 'd', 'd' };

         internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               0,
               data1,
               5
         );

         internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               1,
               data2,
               5
         );

         internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               2,
               data3,
               5
         );

         internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               3,
               data3,
               5
         );

         int32_t it1 = internal_use_do_not_use::db_find_i64(
               "inttester"_n.value,
               "inttester"_n.value,
               "testtable"_n.value,
               1
         );

         uint64_t primary;

         int32_t it2 = internal_use_do_not_use::db_next_i64(
               it1,
               &primary
         );

         print_f("next is %\n", primary);

         int32_t it3 = internal_use_do_not_use::db_previous_i64(
               it2,
               &primary
         );

         print_f("previous is %\n", primary);

         internal_use_do_not_use::db_remove_i64(it2);

         int32_t it4 = internal_use_do_not_use::db_next_i64(
               it3,
               &primary
         );

         print_f("next is %\n", primary);

      }
};


EOSIO_DISPATCH(inttestern, (hi1)(hi2)(hi3)(hi4)(hi5))

#define TEST1 false
#define TEST2 false
#define TEST3 false
#define TEST4 false
#define TEST5 true

EOSIO_TEST_BEGIN(inttestern_test)
   intrinsics::set_intrinsic<intrinsics::read_action_data>(
         [](void* m, uint32_t len) {
            size_t size = sizeof(char*)*5;
            check(len <= size, "failed from read_action_data");
            memcpy(m, std::string("abcd").c_str(), size);
            return len; 
         });

   intrinsics::set_intrinsic<intrinsics::action_data_size>(
         []() {
            size_t size = sizeof(char*)*5;
            return (uint32_t)size;
         });
#if TEST1
   CHECK_PRINT("data is abcd\n",
         []() {
            apply("test"_n.value, "test"_n.value, "hi1"_n.value);
         }
   );
#endif
#if TEST2
   CHECK_PRINT("data is aaaa\ndata is cccc\n",
         []() {
            apply("test"_n.value, "test"_n.value, "hi2"_n.value);
         }
   );
#endif
#if TEST3
   CHECK_PRINT("data is aaaa\ndata is bbbb\n",
         []() {
            apply("test"_n.value, "test"_n.value, "hi3"_n.value);
         }
   );
#endif
#if TEST4
   CHECK_PRINT("lowerbound is 0\nupperbound is 2\nend is 4\n",
         []() {
            apply("test"_n.value, "test"_n.value, "hi4"_n.value);
         }
   );
#endif
#if TEST5
   CHECK_PRINT("next is 2\nprevious is 1\nnext is 3\n",
         []() {
            apply("test"_n.value, "test"_n.value, "hi5"_n.value);
         }
   );
#endif
EOSIO_TEST_END

int main(int argc, char** argv) {
   silence_output(false);
   EOSIO_TEST(inttestern_test);
   return has_failed();
}

