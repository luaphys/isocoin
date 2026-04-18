// Copyright (c) 2011-2016 The isocoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "IWalletLegacy.h"
#include "ITransfersContainer.h"

#include <unordered_map>
#include <unordered_set>
#include <time.h>
#include <boost/functional/hash.hpp>

#include "isocoinCore/isocoinBasic.h"
#include "crypto/crypto.h"

namespace isocoin {
class ISerializer;

typedef std::pair<Crypto::PublicKey, size_t> TransactionOutputId;
}

namespace std {

template<> 
struct hash<isocoin::TransactionOutputId> {
  size_t operator()(const isocoin::TransactionOutputId &_v) const {    
    return hash<Crypto::PublicKey>()(_v.first) ^ _v.second;
  } 
}; 

}

namespace isocoin {


struct UnconfirmedTransferDetails {

  UnconfirmedTransferDetails() :
    amount(0), sentTime(0), transactionId(WALLET_LEGACY_INVALID_TRANSACTION_ID) {}

  isocoin::Transaction tx;
  uint64_t amount;
  uint64_t outsAmount;
  time_t sentTime;
  TransactionId transactionId;
  std::vector<TransactionOutputId> usedOutputs;
};

class WalletUnconfirmedTransactions
{
public:

  explicit WalletUnconfirmedTransactions(uint64_t uncofirmedTransactionsLiveTime);

  bool serialize(isocoin::ISerializer& s);

  bool findTransactionId(const Crypto::Hash& hash, TransactionId& id);
  void erase(const Crypto::Hash& hash);
  void add(const isocoin::Transaction& tx, TransactionId transactionId, 
    uint64_t amount, const std::list<TransactionOutputInformation>& usedOutputs);
  void updateTransactionId(const Crypto::Hash& hash, TransactionId id);

  uint64_t countUnconfirmedOutsAmount() const;
  uint64_t countUnconfirmedTransactionsAmount() const;
  bool isUsed(const TransactionOutputInformation& out) const;
  void reset();

  std::vector<TransactionId> deleteOutdatedTransactions();

private:

  void collectUsedOutputs();
  void deleteUsedOutputs(const std::vector<TransactionOutputId>& usedOutputs);

  typedef std::unordered_map<Crypto::Hash, UnconfirmedTransferDetails, boost::hash<Crypto::Hash>> UnconfirmedTxsContainer;
  typedef std::unordered_set<TransactionOutputId> UsedOutputsContainer;

  UnconfirmedTxsContainer m_unconfirmedTxs;
  UsedOutputsContainer m_usedOutputs;
  uint64_t m_uncofirmedTransactionsLiveTime;
};

} // namespace isocoin
