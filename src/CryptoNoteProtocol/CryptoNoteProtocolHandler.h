// Copyright (c) 2011-2016 The isocoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <atomic>

#include <Common/ObserverManager.h>

#include "isocoinCore/ICore.h"

#include "isocoinProtocol/isocoinProtocolDefinitions.h"
#include "isocoinProtocol/isocoinProtocolHandlerCommon.h"
#include "isocoinProtocol/IisocoinProtocolObserver.h"
#include "isocoinProtocol/IisocoinProtocolQuery.h"

#include "P2p/P2pProtocolDefinitions.h"
#include "P2p/NetNodeCommon.h"
#include "P2p/ConnectionContext.h"

#include <Logging/LoggerRef.h>

namespace System {
  class Dispatcher;
}

namespace isocoin
{
  class Currency;

  class isocoinProtocolHandler : 
    public i_isocoin_protocol, 
    public IisocoinProtocolQuery
  {
  public:

    isocoinProtocolHandler(const Currency& currency, System::Dispatcher& dispatcher, ICore& rcore, IP2pEndpoint* p_net_layout, Logging::ILogger& log);

    virtual bool addObserver(IisocoinProtocolObserver* observer) override;
    virtual bool removeObserver(IisocoinProtocolObserver* observer) override;

    void set_p2p_endpoint(IP2pEndpoint* p2p);
    // ICore& get_core() { return m_core; }
    virtual bool isSynchronized() const override { return m_synchronized; }
    void log_connections();

    // Interface t_payload_net_handler, where t_payload_net_handler is template argument of nodetool::node_server
    void stop();
    bool start_sync(isocoinConnectionContext& context);
    bool on_idle();
    void onConnectionOpened(isocoinConnectionContext& context);
    void onConnectionClosed(isocoinConnectionContext& context);
    bool get_stat_info(core_stat_info& stat_inf);
    bool get_payload_sync_data(CORE_SYNC_DATA& hshd);
    bool process_payload_sync_data(const CORE_SYNC_DATA& hshd, isocoinConnectionContext& context, bool is_inital);
    int handleCommand(bool is_notify, int command, const BinaryArray& in_buff, BinaryArray& buff_out, isocoinConnectionContext& context, bool& handled);
    virtual size_t getPeerCount() const override;
    virtual uint32_t getObservedHeight() const override;
    void requestMissingPoolTransactions(const isocoinConnectionContext& context);

  private:
    //----------------- commands handlers ----------------------------------------------
    int handle_notify_new_block(int command, NOTIFY_NEW_BLOCK::request& arg, isocoinConnectionContext& context);
    int handle_notify_new_transactions(int command, NOTIFY_NEW_TRANSACTIONS::request& arg, isocoinConnectionContext& context);
    int handle_request_get_objects(int command, NOTIFY_REQUEST_GET_OBJECTS::request& arg, isocoinConnectionContext& context);
    int handle_response_get_objects(int command, NOTIFY_RESPONSE_GET_OBJECTS::request& arg, isocoinConnectionContext& context);
    int handle_request_chain(int command, NOTIFY_REQUEST_CHAIN::request& arg, isocoinConnectionContext& context);
    int handle_response_chain_entry(int command, NOTIFY_RESPONSE_CHAIN_ENTRY::request& arg, isocoinConnectionContext& context);
    int handleRequestTxPool(int command, NOTIFY_REQUEST_TX_POOL::request& arg, isocoinConnectionContext& context);

    //----------------- i_isocoin_protocol ----------------------------------
    virtual void relay_block(NOTIFY_NEW_BLOCK::request& arg) override;
    virtual void relay_transactions(NOTIFY_NEW_TRANSACTIONS::request& arg) override;

    //----------------------------------------------------------------------------------
    uint32_t get_current_blockchain_height();
    bool request_missing_objects(isocoinConnectionContext& context, bool check_having_blocks);
    bool on_connection_synchronized();
    void updateObservedHeight(uint32_t peerHeight, const isocoinConnectionContext& context);
    void recalculateMaxObservedHeight(const isocoinConnectionContext& context);
    int processObjects(isocoinConnectionContext& context, const std::vector<block_complete_entry>& blocks);
    Logging::LoggerRef logger;

  private:

    System::Dispatcher& m_dispatcher;
    ICore& m_core;
    const Currency& m_currency;

    p2p_endpoint_stub m_p2p_stub;
    IP2pEndpoint* m_p2p;
    std::atomic<bool> m_synchronized;
    std::atomic<bool> m_stop;

    mutable std::mutex m_observedHeightMutex;
    uint32_t m_observedHeight;

    std::atomic<size_t> m_peersCount;
    Tools::ObserverManager<IisocoinProtocolObserver> m_observerManager;
  };
}
