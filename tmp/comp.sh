#!/bin/bash
eosio-cpp inttester.cpp

cleos set abi inttester inttester.abi
cleos set code inttester inttester.wasm
