// Copyright (c) 2011-2016 The isocoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstddef>
#include <cstdint>

namespace isocoin {
class IisocoinProtocolObserver;

class IisocoinProtocolQuery {
public:
  virtual bool addObserver(IisocoinProtocolObserver* observer) = 0;
  virtual bool removeObserver(IisocoinProtocolObserver* observer) = 0;

  virtual uint32_t getObservedHeight() const = 0;
  virtual size_t getPeerCount() const = 0;
  virtual bool isSynchronized() const = 0;
};

} //namespace isocoin
