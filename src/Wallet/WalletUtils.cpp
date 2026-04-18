// Copyright (c) 2011-2016 The isocoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "WalletUtils.h"

#include "isocoin.h"

namespace isocoin {

bool validateAddress(const std::string& address, const isocoin::Currency& currency) {
  isocoin::AccountPublicAddress ignore;
  return currency.parseAccountAddressString(address, ignore);
}

}
