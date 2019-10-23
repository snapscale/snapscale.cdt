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

   intrinsic_row(std::string t_id, uint64_t primary_key, const void* val, uint32_t buffer_size):
            t_id{ t_id }, primary_key{ primary_key }, buffer_size{ buffer_size} {
      value = std::string((char*)val, buffer_size);
   }

   bool operator ==(const intrinsic_row r2) const {
      return t_id == r2.t_id && primary_key == r2.primary_key;
   }

   bool operator <(const intrinsic_row r2) const {
      return primary_key < r2.primary_key;
   }

   uint64_t primary_key;
   uint32_t buffer_size;
   std::string t_id;
   std::string value;
};


static const intrinsic_row NULLROW{ "", -1, "", 0 };

extern std::map<std::string, std::vector<intrinsic_row>>* key_to_table;
extern std::map<int32_t, std::vector<intrinsic_row>>* iterator_to_table;
