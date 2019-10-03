#include <eosio/name.hpp>
#include <eosio/types.h>

#include <map>
#include <string>
#include <vector>

struct intrinsic_table {
   intrinsic_table() = default;

   // TODO: This feels terribly wrong...
   intrinsic_table(int64_t t_id, uint64_t primary_key, const void* value, uint32_t buffer_size):
         t_id{ t_id }, primary_key{ primary_key } {
      value = new char[buffer_size+1]; 
      memcpy(&value, &this->value, buffer_size);
   }

   ~intrinsic_table() {
      delete [] value;
   }

   int64_t t_id;
   uint64_t primary_key;
   char* value;
};


std::vector<intrinsic_table> table_iterator;
std::map<std::string, intrinsic_table> tables;


/*
intrinsic_table find_or_create_table(capi_name code, capi_name scope, capi_name table) {
   std::string key = eosio::name{ code }.to_string() + eosio::name{ scope }.to_string() + eosio::name{ table }.to_string();
   auto val = tables.find(key);
   if (val != tables.end()) {
      return val->second;
   }
   else {
      intrinsic_table t;
      tables[key] = t;
      return t;
   }
}
*/

