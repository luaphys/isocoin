// Copyright (c) 2011-2016 The isocoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "isocoinCore/Account.h"
#include "isocoinCore/isocoinFormatUtils.h"
#include "isocoinCore/Currency.h"

class TransactionBuilder {
public:

  typedef std::vector<isocoin::AccountKeys> KeysVector;
  typedef std::vector<Crypto::Signature> SignatureVector;
  typedef std::vector<SignatureVector> SignatureMultivector;

  struct MultisignatureSource {
    isocoin::MultisignatureInput input;
    KeysVector keys;
    Crypto::PublicKey srcTxPubKey;
    size_t srcOutputIndex;
  };

  TransactionBuilder(const isocoin::Currency& currency, uint64_t unlockTime = 0);

  // regenerate transaction keys
  TransactionBuilder& newTxKeys();
  TransactionBuilder& setTxKeys(const isocoin::KeyPair& txKeys);

  // inputs
  TransactionBuilder& setInput(const std::vector<isocoin::TransactionSourceEntry>& sources, const isocoin::AccountKeys& senderKeys);
  TransactionBuilder& addMultisignatureInput(const MultisignatureSource& source);

  // outputs
  TransactionBuilder& setOutput(const std::vector<isocoin::TransactionDestinationEntry>& destinations);
  TransactionBuilder& addOutput(const isocoin::TransactionDestinationEntry& dest);
  TransactionBuilder& addMultisignatureOut(uint64_t amount, const KeysVector& keys, uint32_t required);

  isocoin::Transaction build() const;

  std::vector<isocoin::TransactionSourceEntry> m_sources;
  std::vector<isocoin::TransactionDestinationEntry> m_destinations;

private:

  void fillInputs(isocoin::Transaction& tx, std::vector<isocoin::KeyPair>& contexts) const;
  void fillOutputs(isocoin::Transaction& tx) const;
  void signSources(const Crypto::Hash& prefixHash, const std::vector<isocoin::KeyPair>& contexts, isocoin::Transaction& tx) const;

  struct MultisignatureDestination {
    uint64_t amount;
    uint32_t requiredSignatures;
    KeysVector keys;
  };

  isocoin::AccountKeys m_senderKeys;

  std::vector<MultisignatureSource> m_msigSources;
  std::vector<MultisignatureDestination> m_msigDestinations;

  size_t m_version;
  uint64_t m_unlockTime;
  isocoin::KeyPair m_txKey;
  const isocoin::Currency& m_currency;
};
