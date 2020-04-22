# SNAPSCALE.CDT (Contract Development Toolkit)
SNAPSCALE.CDT is a toolchain for WebAssembly (WASM) and set of tools to facilitate smart contract development for the SNAPSCALE platform. In addition to being a general purpose WebAssembly toolchain, [SNAPSCALE](https://github.com/eosio/eos) specific optimizations are available to support building SNAPSCALE smart contracts.  This new toolchain is built around [Clang 7](https://github.com/eosio/llvm), which means that SNAPSCALE.CDT has the most currently available optimizations and analyses from LLVM, but as the WASM target is still considered experimental, some optimizations are incomplete or not available.

### New Introductions
As of this release two new repositories are under the suite of tools provided by **SNAPSCALE.CDT**.  These are the [Ricardian Template Toolkit](https://github.com/eosio/ricardian-template-toolkit) and the [Ricardian Specification](https://github.com/eosio/ricardian-spec).  The **Ricardian Template Toolkit** is a set of libraries to facilitate smart contract writers in crafting their Ricardian contracts.  The Ricardian specification is the working specification for the above mentioned toolkit.  Please note that both projects are **alpha** releases and are subject to change.

### Attention
- There is currently a known issue that a minimum of 2 CPU cores is required for using SNAPSCALE.CDT

## Guided Installation or Building
```sh
git clone --recursive https://github.com/snapscale/snapscale.cdt
cd snapscale.cdt
mkdir build
cd build
cmake ..
make -j8
```

From here onward you can build your contracts code by simply exporting the `build` directory to your path, so you don't have to install globally (makes things cleaner).
Or you can install globally by running this command:

```sh
sudo make install
```

### Uninstall after manual installation

```sh
sudo rm -fr /usr/local/eosio.cdt
sudo rm -fr /usr/local/lib/cmake/eosio.cdt
sudo rm /usr/local/bin/eosio-*
```

## Installed Tools

* eosio-cpp
* eosio-cc
* eosio-ld
* eosio-init
* eosio-abidiff
* eosio-wasm2wast
* eosio-wast2wasm
* eosio-ranlib
* eosio-ar
* eosio-objdump
* eosio-readelf

Below tools are not installed after brew install, you get them only by building the repository and installing from scracth, [see here](#guided_installation_or_building_from_scratch)
eosio-abidiff
eosio-ranlib
eosio-ar
eosio-objdump
eosio-readelf

## License

[MIT](../LICENSE)

## Important

See [LICENSE](./LICENSE) for copyright and license terms.

All repositories and other materials are provided subject to the terms of this [IMPORTANT](./IMPORTANT.md) notice and you must familiarize yourself with its terms.  The notice contains important information, limitations and restrictions relating to our software, publications, trademarks, third-party resources, and forward-looking statements.  By accessing any of our repositories and other materials, you accept and agree to the terms of the notice.
