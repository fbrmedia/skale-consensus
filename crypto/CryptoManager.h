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

    @file CryptoManager.h
    @author Stan Kladko
    @date 2019
*/

#ifndef SKALED_CRYPTOMANAGER_H
#define SKALED_CRYPTOMANAGER_H



#include "openssl/ec.h"
#include "messages/NetworkMessage.h"

class Schain;
class SHAHash;
class ConsensusBLSSigShare;
class ThresholdSigShareSet;
class ThresholdSigShare;
class BlockProposal;
class ThresholdSignature;
class CryptoManager {

private:

    map<schain_index, ptr<pair<string, array<uint8_t, 16>>>> outgoingMACKeys;
    map<schain_index, ptr<pair<string, array<uint8_t, 16>>>> incomingMACKeys;


    uint64_t  totalSigners;
    uint64_t  requiredSigners;

    bool sgxEnabled = false;

    ptr<string> sgxIP;
    ptr<string> sgxSSLKeyFileFullPath;
    ptr<string> sgxSSLCertFileFullPath;
    ptr<string> sgxECDSAKeyName;
    ptr<string> sgxECDSAPublicKey;


    Schain* sChain;

    ptr<string> signECDSA(ptr<SHAHash> _hash);

    bool verifyECDSA(ptr<SHAHash> _hash, ptr<string> _sig);

    ptr<ThresholdSigShare> signSigShare(ptr<SHAHash> _hash, block_id _blockId);

    //EC_KEY* ecdsaKey;


public:

    CryptoManager(Schain& sChain);

    Schain *getSchain() const;

    ptr<ThresholdSignature> verifyThresholdSig(ptr<SHAHash> _hash, ptr<string> _signature, block_id _blockId);

    ptr<ThresholdSigShareSet> createSigShareSet(block_id _blockId);

    ptr<ThresholdSigShare>
    createSigShare(ptr<string> _sigShare, schain_id _schainID, block_id _blockID, schain_index _signerIndex);

    void signProposalECDSA(BlockProposal* _proposal);

    bool verifyProposalECDSA(ptr<BlockProposal> _proposal, ptr<string> _hashStr, ptr<string> _signature);

    ptr<ThresholdSigShare> signDAProofSigShare(ptr<BlockProposal> _p);

    ptr<ThresholdSigShare> signBinaryConsensusSigShare(ptr<SHAHash> _hash, block_id _blockId);

    ptr<ThresholdSigShare> signBlockSigShare(ptr<SHAHash> _hash, block_id _blockId);

    ptr<string> signNetworkMsg(NetworkMessage& _msg);

    bool verifyNetworkMsg(NetworkMessage &_msg);
};


#endif //SKALED_CRYPTOMANAGER_H
