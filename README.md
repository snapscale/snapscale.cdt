
<a href="#chinese">点击此处直达中文版 </a>


# SnapScale CDT (Contract Development Toolkit)
SnapScale.CDT is a toolchain for WebAssembly (WASM) and set of tools to facilitate smart contract development for the SnapScale platform. In addition to being a general purpose WebAssembly toolchain, [SnapScale](https://github.com/snapscale/snapscale) specific optimizations are available to support building SnapScale smart contracts.  This new toolchain is built around [Clang 7](https://github.com/eosio/llvm), which means that SnapScale.CDT has the most currently available optimizations and analyses from LLVM, but as the WASM target is still considered experimental, some optimizations are incomplete or not available.

### Attention
- There is currently a known issue that a minimum of 2 CPU cores is required for using SnapScale.CDT

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


## License

SnapScale is released under the Apache 2.0 license and is offered “AS IS” without warranty of any kind, express or implied. Any security provided by the SnapScale software depends in part on how it is used, configured, and deployed. SnapScale is built upon many third-party libraries such as WABT (Apache License) and WAVM (BSD 3-clause) which are also provided “AS IS” without warranty of any kind.

## Important

See [LICENSE](./LICENSE) for copyright and license terms.

All repositories and other materials are provided subject to the terms of this [IMPORTANT](./IMPORTANT.md) notice and you must familiarize yourself with its terms.  The notice contains important information, limitations and restrictions relating to our software, publications, trademarks, third-party resources, and forward-looking statements.  By accessing any of our repositories and other materials, you accept and agree to the terms of the notice. <br>

<br>

---

<a id="chinese"></a><br>
# SnapScale CDT（智能合约开发工具包）
SnapScale.CDT 是WebAssembly（WASM）的工具链，提供了基于SnapScale 配置智能合约的系列开发工具。除了作为通用WebAssembly工具链之外，[SnapScale.CDT](https://github.com/snapscale/snapscale)对支持SnapScale 智能合约开发进行了特别优化。SnapScale.CDT 基于[Clang 7](https://github.com/eosio/llvm)构建，这意味着SnapScale.CDT 具备LLVM中最新的优化和分析功能，但是由于WASM目前仍处于实验阶段，因此某些优化功能尚不完整或不可用。

### 请注意
- 使用SnapScale.CDT至少需要2个CPU内核
## 安装和创建指南
```sh
git clone --recursive https://github.com/snapscale/snapscale.cdt
cd snapscale.cdt
mkdir build
cd build
cmake ..
make -j8
```

您只需将`创建` 目录导出到您的路径即可构建合同代码，不必进行全局安装（使操作更简洁）。或者，您可以通过运行以下命令进行全局安装：
```sh
sudo make install
```

### 手动安装后卸载

```sh
sudo rm -fr /usr/local/eosio.cdt
sudo rm -fr /usr/local/lib/cmake/eosio.cdt
sudo rm /usr/local/bin/eosio-*
```


## 许可协议

SnapScale 遵循Apache 2.0 开源协议发布，按“原样”提供，没有任何明示或暗示的担保。SnapScale 软件提供的任何安全性部分取决于它的使用，配置和部署方式。 SnapScale 建立在许多第三方库上，如Binaryen（Apache许可证）和WAVM（BSD 3-clause），它们也是“按现状”提供的，没有任何形式的保证。


## 重要事项

有关版权和许可条款，请参考[许可协议](./LICENSE) 。

我们提供的所有信息都受限于本[重要通知](./IMPORTANT.md) 您必须熟悉其中的条款。该通知包含了关于我们的软件、发布、商标、第三方资源和前瞻性声明的重要信息、条件和限制。您获取任何材料的时候就意味着您接受并同意该通知的条款。
