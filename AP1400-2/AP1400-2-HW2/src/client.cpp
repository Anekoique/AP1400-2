#include "client.h"
#include "server.h"
#include "crypto.h"
#include <random>

Client::Client(std::string id, const Server& server) : id(id), server(&server) {
    crypto::generate_key(public_key, private_key);
}

std::string Client::get_id() { return id; }

std::string Client::get_publickey() const { return public_key; }

double Client::get_wallet() { return server->get_wallet(id); }

std::string Client::sign(std::string txt) const {
    std::string signature = crypto::signMessage(private_key, txt);
    return signature;
}

bool Client::transfer_money(std::string receiver, double value) {
    if (server->get_client(receiver) == nullptr) return false;
    std::string trx = id + '-' + receiver + '-' + std::to_string(value);
    std::cout << trx;
    return server->add_pending_trx(trx, sign(trx));
}

size_t Client::generate_nonce() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 9);
    return dist(mt);
} 
