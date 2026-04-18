// Copyright (c) 2011-2016 The isocoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstdint>
#include <initializer_list>

namespace isocoin {
namespace parameters {

const uint64_t isocoin_MAX_BLOCK_NUMBER                   = 500000000;
const size_t   isocoin_MAX_BLOCK_BLOB_SIZE                = 500000000;
const size_t   isocoin_MAX_TX_SIZE                        = 1000000000;
const uint64_t isocoin_PUBLIC_ADDRESS_BASE58_PREFIX       = 0x2788; // addresses start with "iso"
const size_t   isocoin_MINED_MONEY_UNLOCK_WINDOW          = 60;
const uint64_t isocoin_BLOCK_FUTURE_TIME_LIMIT            = 60 * 60 * 2;

const size_t   BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW             = 60;

// 41 million coins with 8 decimal places = 41000000 * 10^8
const uint64_t MONEY_SUPPLY                                  = UINT64_C(4100000000000000);
const unsigned EMISSION_SPEED_FACTOR                         = 18;
static_assert(EMISSION_SPEED_FACTOR <= 8 * sizeof(uint64_t), "Bad EMISSION_SPEED_FACTOR");

const size_t   isocoin_REWARD_BLOCKS_WINDOW               = 100;
const size_t   isocoin_BLOCK_GRANTED_FULL_REWARD_ZONE     = 10000;
const size_t   isocoin_COINBASE_BLOB_RESERVED_SIZE        = 600;
const size_t   isocoin_DISPLAY_DECIMAL_POINT              = 8;
const uint64_t MINIMUM_FEE                                   = 100000; // 0.001 ISO
const uint64_t DEFAULT_DUST_THRESHOLD                        = MINIMUM_FEE;

const uint64_t DIFFICULTY_TARGET                             = 120; // seconds
const uint64_t EXPECTED_NUMBER_OF_BLOCKS_PER_DAY             = 24 * 60 * 60 / DIFFICULTY_TARGET;
const size_t   DIFFICULTY_WINDOW                             = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;
const size_t   DIFFICULTY_CUT                                = 60;
const size_t   DIFFICULTY_LAG                                = 15;
static_assert(2 * DIFFICULTY_CUT <= DIFFICULTY_WINDOW - 2, "Bad DIFFICULTY_WINDOW or DIFFICULTY_CUT");

const size_t   MAX_BLOCK_SIZE_INITIAL                        =  20 * 1024;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_NUMERATOR         = 100 * 1024;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_DENOMINATOR       = 365 * 24 * 60 * 60 / DIFFICULTY_TARGET;

const uint64_t isocoin_LOCKED_TX_ALLOWED_DELTA_BLOCKS     = 1;
const uint64_t isocoin_LOCKED_TX_ALLOWED_DELTA_SECONDS    = DIFFICULTY_TARGET * isocoin_LOCKED_TX_ALLOWED_DELTA_BLOCKS;

const uint64_t isocoin_MEMPOOL_TX_LIVETIME                = 60 * 60 * 24;
const uint64_t isocoin_MEMPOOL_TX_FROM_ALT_BLOCK_LIVETIME = 60 * 60 * 24 * 7;
const uint64_t isocoin_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL = 7;

const size_t   FUSION_TX_MAX_SIZE                            = isocoin_BLOCK_GRANTED_FULL_REWARD_ZONE * 30 / 100;
const size_t   FUSION_TX_MIN_INPUT_COUNT                     = 12;
const size_t   FUSION_TX_MIN_IN_OUT_COUNT_RATIO              = 4;

const char     isocoin_BLOCKS_FILENAME[]                  = "blocks.dat";
const char     isocoin_BLOCKINDEXES_FILENAME[]            = "blockindexes.dat";
const char     isocoin_BLOCKSCACHE_FILENAME[]             = "blockscache.dat";
const char     isocoin_POOLDATA_FILENAME[]                = "poolstate.bin";
const char     P2P_NET_DATA_FILENAME[]                       = "p2pstate.bin";
const char     isocoin_BLOCKCHAIN_INDICES_FILENAME[]      = "blockchainindices.dat";
const char     MINER_CONFIG_FILE_NAME[]                      = "miner_conf.json";
} // parameters

const char     isocoin_NAME[]                             = "isocoin";
const char     GENESIS_COINBASE_TX_HEX[]                     = ""; // fill after running --print-genesis-tx

const uint8_t  CURRENT_TRANSACTION_VERSION                   =  1;
const uint8_t  BLOCK_MAJOR_VERSION_1                         =  1;
const uint8_t  BLOCK_MINOR_VERSION_0                         =  0;

const size_t   BLOCKS_IDS_SYNCHRONIZING_DEFAULT_COUNT        =  10000;
const size_t   BLOCKS_SYNCHRONIZING_DEFAULT_COUNT            =  200;
const size_t   COMMAND_RPC_GET_BLOCKS_FAST_MAX_COUNT         =  1000;

const int      P2P_DEFAULT_PORT                              = 19370;
const int      RPC_DEFAULT_PORT                              = 19371;

const size_t   P2P_LOCAL_WHITE_PEERLIST_LIMIT                =  1000;
const size_t   P2P_LOCAL_GRAY_PEERLIST_LIMIT                 =  5000;

const size_t   P2P_CONNECTION_MAX_WRITE_BUFFER_SIZE          = 16 * 1024 * 1024;
const uint32_t P2P_DEFAULT_CONNECTIONS_COUNT                 = 8;
const size_t   P2P_DEFAULT_WHITELIST_CONNECTIONS_PERCENT     = 70;
const uint32_t P2P_DEFAULT_HANDSHAKE_INTERVAL                = 60;
const uint32_t P2P_DEFAULT_PACKET_MAX_SIZE                   = 50000000;
const uint32_t P2P_DEFAULT_PEERS_IN_HANDSHAKE                = 250;
const uint32_t P2P_DEFAULT_CONNECTION_TIMEOUT                = 5000;
const uint32_t P2P_DEFAULT_PING_CONNECTION_TIMEOUT           = 2000;
const uint64_t P2P_DEFAULT_INVOKE_TIMEOUT                    = 60 * 2 * 1000;
const size_t   P2P_DEFAULT_HANDSHAKE_INVOKE_TIMEOUT          = 5000;
const char     P2P_STAT_TRUSTED_PUB_KEY[]                    = "";

const std::initializer_list<const char*> SEED_NODES = {
  //"your_seed_ip1.com:19370",
  //"your_seed_ip2.com:19370",
};

// Network ID - unique to IsoCoin, will not conflict with other isocoin coins
const static boost::uuids::uuid isocoin_NETWORK = { {
  0x49, 0x53, 0x4F, 0xC0,   // ISO + random
  0xA3, 0x7F, 0x11, 0xEE,
  0xB4, 0x2D, 0xC8, 0x5B,
  0x3E, 0x9F, 0x47, 0x2A
} };

struct CheckpointData {
  uint32_t height;
  const char* blockId;
};

#ifdef __GNUC__
__attribute__((unused))
#endif

const std::initializer_list<CheckpointData> CHECKPOINTS = {
  // add checkpoints here after launch
  // { 10000, "blockhashhere" },
};
} // isocoin

#define ALLOW_DEBUG_COMMANDS
