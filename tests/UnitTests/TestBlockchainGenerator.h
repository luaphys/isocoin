// Copyright (c) 2011-2016 The isocoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <vector>
#include <unordered_map>

#include "isocoinCore/Account.h"
#include "isocoinCore/isocoinBasic.h"
#include "isocoinCore/Currency.h"
#include "isocoinCore/BlockchainIndices.h"
#include "crypto/hash.h"

#include "../TestGenerator/TestGenerator.h"

class TestBlockchainGenerator
{
public:
  TestBlockchainGenerator(const isocoin::Currency& currency);

  //TODO: get rid of this method
  std::vector<isocoin::Block>& getBlockchain();
  std::vector<isocoin::Block> getBlockchainCopy();
  void generateEmptyBlocks(size_t count);
  bool getBlockRewardForAddress(const isocoin::AccountPublicAddress& address);
  bool generateTransactionsInOneBlock(const isocoin::AccountPublicAddress& address, size_t n);
  bool getSingleOutputTransaction(const isocoin::AccountPublicAddress& address, uint64_t amount);
  void addTxToBlockchain(const isocoin::Transaction& transaction);
  bool getTransactionByHash(const Crypto::Hash& hash, isocoin::Transaction& tx, bool checkTxPool = false);
  const isocoin::AccountBase& getMinerAccount() const;
  bool generateFromBaseTx(const isocoin::AccountBase& address);

  void putTxToPool(const isocoin::Transaction& tx);
  void getPoolSymmetricDifference(std::vector<Crypto::Hash>&& known_pool_tx_ids, Crypto::Hash known_block_id, bool& is_bc_actual,
    std::vector<isocoin::Transaction>& new_txs, std::vector<Crypto::Hash>& deleted_tx_ids);
  void putTxPoolToBlockchain();
  void clearTxPool();

  void cutBlockchain(uint32_t height);

  bool addOrphan(const Crypto::Hash& hash, uint32_t height);
  bool getGeneratedTransactionsNumber(uint32_t height, uint64_t& generatedTransactions);
  bool getOrphanBlockIdsByHeight(uint32_t height, std::vector<Crypto::Hash>& blockHashes);
  bool getBlockIdsByTimestamp(uint64_t timestampBegin, uint64_t timestampEnd, uint32_t blocksNumberLimit, std::vector<Crypto::Hash>& hashes, uint32_t& blocksNumberWithinTimestamps);
  bool getPoolTransactionIdsByTimestamp(uint64_t timestampBegin, uint64_t timestampEnd, uint32_t transactionsNumberLimit, std::vector<Crypto::Hash>& hashes, uint64_t& transactionsNumberWithinTimestamps);
  bool getTransactionIdsByPaymentId(const Crypto::Hash& paymentId, std::vector<Crypto::Hash>& transactionHashes);

  bool getTransactionGlobalIndexesByHash(const Crypto::Hash& transactionHash, std::vector<uint32_t>& globalIndexes);
  bool getMultisignatureOutputByGlobalIndex(uint64_t amount, uint32_t globalIndex, isocoin::MultisignatureOutput& out);
  void setMinerAccount(const isocoin::AccountBase& account);

private:
  struct MultisignatureOutEntry {
    Crypto::Hash transactionHash;
    uint16_t indexOut;
  };

  struct KeyOutEntry {
    Crypto::Hash transactionHash;
    uint16_t indexOut;
  };
  
  void addGenesisBlock();
  void addMiningBlock();

  const isocoin::Currency& m_currency;
  test_generator generator;
  isocoin::AccountBase miner_acc;
  std::vector<isocoin::Block> m_blockchain;
  std::unordered_map<Crypto::Hash, isocoin::Transaction> m_txs;
  std::unordered_map<Crypto::Hash, std::vector<uint32_t>> transactionGlobalOuts;
  std::unordered_map<uint64_t, std::vector<MultisignatureOutEntry>> multisignatureOutsIndex;
  std::unordered_map<uint64_t, std::vector<KeyOutEntry>> keyOutsIndex;

  std::unordered_map<Crypto::Hash, isocoin::Transaction> m_txPool;
  mutable std::mutex m_mutex;

  isocoin::PaymentIdIndex m_paymentIdIndex;
  isocoin::TimestampTransactionsIndex m_timestampIndex;
  isocoin::GeneratedTransactionsIndex m_generatedTransactionsIndex;
  isocoin::OrphanBlocksIndex m_orthanBlocksIndex;

  void addToBlockchain(const isocoin::Transaction& tx);
  void addToBlockchain(const std::vector<isocoin::Transaction>& txs);
  void addToBlockchain(const std::vector<isocoin::Transaction>& txs, const isocoin::AccountBase& minerAddress);
  void addTx(const isocoin::Transaction& tx);

  bool doGenerateTransactionsInOneBlock(isocoin::AccountPublicAddress const &address, size_t n);
};
