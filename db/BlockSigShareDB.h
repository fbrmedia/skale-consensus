/*
    Copyright (C) 2019 SKALE Labs

    This file is part of skale-consensus.

    skale-consensus is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    skale-consensus is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with skale-consensus.  If not, see <https://www.gnu.org/licenses/>.

    @file BlockSigShare.h
    @author Stan Kladko
    @date 2019
*/


#ifndef SKALED_BLOCK_SIG_SHARES_DB
#define SKALED_BLOCK_SIG_SHARES_DB

class CommittedBlock;
class ThresholdSignature;

#include "LevelDB.h"

class CryptoManager;

class BlockSigShareDB : public LevelDB {

    Schain* sChain;

    recursive_mutex m;

    const string getFormatVersion();

public:

    BlockSigShareDB(string &_dirName, string &_prefix, node_id _nodeId, uint64_t _maxDBSize, Schain *_sChain);

    ptr<ThresholdSignature> checkAndSaveShare(ptr<ThresholdSigShare> _sigShare, ptr<CryptoManager> _cryptoManager);

};


#endif //SKALED_BLOCK_SIG_SHARES_DB
