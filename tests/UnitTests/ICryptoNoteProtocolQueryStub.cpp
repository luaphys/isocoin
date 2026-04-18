// Copyright (c) 2011-2016 The isocoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "IisocoinProtocolQueryStub.h"

bool IisocoinProtocolQueryStub::addObserver(isocoin::IisocoinProtocolObserver* observer) {
  return false;
}

bool IisocoinProtocolQueryStub::removeObserver(isocoin::IisocoinProtocolObserver* observer) {
  return false;
}

uint32_t IisocoinProtocolQueryStub::getObservedHeight() const {
  return observedHeight;
}

size_t IisocoinProtocolQueryStub::getPeerCount() const {
  return peers;
}

bool IisocoinProtocolQueryStub::isSynchronized() const {
  return synchronized;
}

void IisocoinProtocolQueryStub::setPeerCount(uint32_t count) {
  peers = count;
}

void IisocoinProtocolQueryStub::setObservedHeight(uint32_t height) {
  observedHeight = height;
}

void IisocoinProtocolQueryStub::setSynchronizedStatus(bool status) {
    synchronized = status;
}
