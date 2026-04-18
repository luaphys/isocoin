// Copyright (c) 2011-2016 The isocoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

namespace isocoin {

template <typename T>
class IObservable {
public:
  virtual void addObserver(T* observer) = 0;
  virtual void removeObserver(T* observer) = 0;
};

}
