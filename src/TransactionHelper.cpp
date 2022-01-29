// Copyright © 2017-2022 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "TransactionHelper.h"

#include "Coin.h"

using namespace TW;


Data TransactionHelper::buildInput(TWCoinType coinType, const std::string& from, const std::string& to, const std::string& amount, const std::string& asset, const std::string& memo, const std::string& chainId) {
    // parse amount
    uint256_t amount256 { amount };
    return anyCoinBuildTransactionInput(coinType, from, to, amount256, asset, memo, chainId);
}

Data TransactionHelper::preImageHash(TWCoinType coinType, const Data& txInputData) {
    return anyCoinPreImageHash(coinType, txInputData);
}

Data TransactionHelper::compileWithSignature(TWCoinType coinType, const Data& txInputData, const Data& signature, const Data& publicKey) {
    Data txOutput;
    const auto publicKeyType = ::publicKeyType(coinType);
    if (!PublicKey::isValid(publicKey, publicKeyType)) {
        throw std::invalid_argument("Invalid public key");
    }
    const auto pub = PublicKey(publicKey, publicKeyType);
    anyCoinCompileWithSignature(coinType, txInputData, signature, pub, txOutput);
    return txOutput;
}