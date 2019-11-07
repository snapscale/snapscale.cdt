#include <eosio/name.hpp>
#include <eosio/print.hpp>
#include <eosio/types.h>

#include <cstring>
#include <map>
#include <string>
#include <vector>

#pragma once

struct intrinsic_row {
   intrinsic_row() = default;

   intrinsic_row(std::string table_key, uint64_t primary_key, const void* buffer, uint32_t buffer_size):
            table_key{ table_key }, primary_key{ primary_key }, buffer_size{ buffer_size} {
      data = std::string((char*)buffer, buffer_size);
   }

   bool operator ==(const intrinsic_row r2) const {
      return table_key == r2.table_key && primary_key == r2.primary_key;
   }

   bool operator <(const intrinsic_row r2) const {
      return primary_key < r2.primary_key;
   }

   std::string table_key;
   uint64_t primary_key;

   std::string data;
   uint32_t buffer_size;
};

union secondary_index_union {
   uint64_t idx64;
   uint128_t idx128;

   double idxdouble;
   long double idxlongdouble;

   uint128_t idx256; // TODO:??
};

struct secondary_index_row {
   secondary_index_union val;
   uint64_t primary_key;
};

enum secondary_index_type { empty, idx64, idx128, idxdouble, idxlongdouble, idx256 };
struct secondary_index {
   secondary_index_type tag;
   std::vector<secondary_index_row> rows;
   std::string table_key;
};


static const eosio::name TESTING_CODE = eosio::name{ "test" };
static const intrinsic_row NULLROW{ "", -1, "", 0 };

// Primary Index
extern std::map<std::string, std::vector<intrinsic_row>>* key_to_table;
extern std::map<int32_t, std::vector<intrinsic_row>>* iterator_to_table;

// Secondary Indexes
extern std::map<std::string, secondary_index[16]>* key_to_secondary_indexes;
extern std::map<int32_t, secondary_index[16]>* iterator_to_secondary_indexes;

extern std::map<std::string, int32_t>* key_to_iterator_secondary;
