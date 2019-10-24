#include <eosio/eosio.hpp>
#include <eosio/name.hpp>
#include <eosio/multi_index.hpp>

using namespace eosio;

class [[eosio::contract]] inttester : public contract {
   public:
      using contract::contract;

      struct [[eosio::table]] testtable {
      };

      [[eosio::action]]
      void hi(name nm) {
         print_f("Hello, %", nm);

         char data1[5] = { 'a', 'b', 'c', 'd' };

         int32_t it1 = internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               0,
               data1,
               5
         );

         print_f("\t it %", it1);

         char data2[5] = { 'd', 'c', 'b', 'a' };

         int32_t it2 = internal_use_do_not_use::db_store_i64(
               "inttester"_n.value,
               "testtable"_n.value,
               nm.value,
               1,
               data2,
               5
         );

         print_f("\t it %", it2);

         char get_data[5];

         int32_t size = internal_use_do_not_use::db_get_i64(it1, &get_data, 5);

         print_f("\t get_data %", get_data);
         print_f("\t size %", size);
      }

      [[eosio::action]]
      void hi1(name nm) {
         print_f("Hello, %", nm);

         int32_t it = internal_use_do_not_use::db_find_i64(
               "inttester"_n.value,
               "inttester"_n.value,
               "testtable"_n.value,
               0
         );

         char data[5] = { 'b', 'b', 'b', 'b' };
         internal_use_do_not_use::db_update_i64(
            it,
            "inttester"_n.value,
            data,
            5
         );

         char get_data[5];
         int32_t size = internal_use_do_not_use::db_get_i64(it, &get_data, 5);

         print_f("\t get_data %", get_data);
         print_f("\t size %", size);

         internal_use_do_not_use::db_remove_i64(it);
      }

      [[eosio::action]]
      void hi2(name nm) {
         print_f("Hello, %", nm);

         int32_t it1 = internal_use_do_not_use::db_find_i64(
               "inttester"_n.value,
               "inttester"_n.value,
               "testtable"_n.value,
               0
         );

         print_f("\t it1 %", it1);

         uint64_t primary1;
         int32_t it2 = internal_use_do_not_use::db_next_i64(it1, &primary1);

         print_f("\t it2 % primary1 %", it2, primary1);

         uint64_t primary2;
         int32_t it3 = internal_use_do_not_use::db_previous_i64(it2, &primary2);

         print_f("\t it3 % primary2 %", it3, primary2);
      }

      [[eosio::action]]
      void hi3(name nm) {
         int32_t lowerbound = internal_use_do_not_use::db_lowerbound_i64(
               "inttester"_n.value,
               "inttester"_n.value,
               "testtable"_n.value,
               0
         );
         print_f("\t lowerbound % ", lowerbound);

         int32_t upperbound = internal_use_do_not_use::db_upperbound_i64(
           "inttester"_n.value,
           "inttester"_n.value,
           "testtable"_n.value,
           0
         );
         print_f("\t upperbound % ", upperbound);

         int32_t end = internal_use_do_not_use::db_end_i64(
           "inttester"_n.value,
           "inttester"_n.value,
           "testtable"_n.value
         );
         print_f("\t end % ", end);
      }

};
