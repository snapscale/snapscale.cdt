#include <eosio/name.hpp>
#include <eosio/print.hpp>
#include <eosio/types.h>

#include <cstring>
#include <map>
#include <string>
#include <vector>

#pragma once

struct intrinsic_table {
   intrinsic_table() {
#if 0
      eosio::print_f("intrinsic_table default constructor called\n");
#endif
   };

   intrinsic_table(const intrinsic_table& from){
      // eosio::print_f("intrinsic_table copy constructor called\n");
      t_id = from.t_id;
      primary_key = from.primary_key;
      value = from.value;
      buffer_size = from.buffer_size;
   }

   intrinsic_table(std::string t_id, uint64_t primary_key, const void* val, uint32_t buffer_size):
            t_id{ t_id }, primary_key{ primary_key }, buffer_size{ buffer_size} {
      value = std::string((char*)val, buffer_size);
   }

   bool operator ==(intrinsic_table t2) {
      return t_id == t2.t_id && primary_key == t2.primary_key;
   }

   bool operator <(const intrinsic_table t2) const {
      return primary_key < t2.primary_key;
   }

   uint64_t primary_key;
   uint32_t buffer_size;
   std::string t_id;
   std::string value;
};


/*
 * TODO:
 * Since the iterator cache depends on getting reset with the apply context/is dependent on `find` being called first,
 * these may need to be wrapped in an object that gets reset in each of the expect(?) functions?
 */
extern std::vector<intrinsic_table>* table_iterator;
extern std::map<std::string, intrinsic_table>* tables;
extern std::map<std::string, std::vector<intrinsic_table>>* tables_v;

