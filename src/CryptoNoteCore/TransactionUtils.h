// Copyright (c) 2011-2016 The isocoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "isocoinCore/isocoinBasic.h"
#include "ITransaction.h"

namespace isocoin {

bool checkInputsKeyimagesDiff(const isocoin::TransactionPrefix& tx);

// TransactionInput helper functions
size_t getRequiredSignaturesCount(const TransactionInput& in);
uint64_t getTransactionInputAmount(const TransactionInput& in);
TransactionTypes::InputType getTransactionInputType(const TransactionInput& in);
const TransactionInput& getInputChecked(const isocoin::TransactionPrefix& transaction, size_t index);
const TransactionInput& getInputChecked(const isocoin::TransactionPrefix& transaction, size_t index, TransactionTypes::InputType type);

bool isOutToKey(const Crypto::PublicKey& spendPublicKey, const Crypto::PublicKey& outKey, const Crypto::KeyDerivation& derivation, size_t keyIndex);

// TransactionOutput helper functions
TransactionTypes::OutputType getTransactionOutputType(const TransactionOutputTarget& out);
const TransactionOutput& getOutputChecked(const isocoin::TransactionPrefix& transaction, size_t index);
const TransactionOutput& getOutputChecked(const isocoin::TransactionPrefix& transaction, size_t index, TransactionTypes::OutputType type);

bool findOutputsToAccount(const isocoin::TransactionPrefix& transaction, const AccountPublicAddress& addr,
        const Crypto::SecretKey& viewSecretKey, std::vector<uint32_t>& out, uint64_t& amount);

} //namespace isocoin
