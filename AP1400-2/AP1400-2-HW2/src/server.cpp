#include "server.h"
#include "client.h"
#include "crypto.h"
#include <random>
#include <iostream>
#include <regex>
#include <stdexcept>

// std::shared_ptr<Client> Server::add_client(std::string id)
// {
//     bool flag = true;
//     for (const auto& pair : clients) {
//         if (pair.first->get_id() == id) flag = false;
//     }
//     if (!flag) {
//         std::random_device rd;
//         std::mt19937 mt(rd());
//         std::uniform_int_distribution<int> dist(1000, 9999);
//         int rand = dist(mt);
// 
//         id += std::to_string(rand);
//         std::shared_ptr<Client> new_client = std::make_shared<Client>(id, *this);
//         clients.insert(std::pair<std::shared_ptr<Client>, double>(new_client, 5));
//         return new_client;
//     }
//     else {
//         std::shared_ptr<Client> new_client = std::make_shared<Client>(id, *this);
//         clients.insert(std::pair<std::shared_ptr<Client>, double>(new_client, 5));
//         return get_client(id);
//     }
// 
// }
//

std::shared_ptr<Client> Server::add_client(std::string id)
{
    if (get_client(id) != nullptr) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(1000, 9999);
        int randNum = dis(gen);
        id += std::to_string(randNum);
    }
    std::shared_ptr addedClient = make_shared<Client>(id, *this);
    clients.insert(make_pair(addedClient, 5));
    // clients[addedClient] = 5;
    return addedClient;
}

std::shared_ptr<Client> Server::get_client(std::string id) const
{
    for (const auto& pair : clients) {
        if (pair.first->get_id() == id) return pair.first;
    }
    std::cout << "Failed to find the Client, check the id." << std::endl;
    return nullptr;
    // for (const auto& [client_ptr, coins] : clients)
}

double Server::get_wallet(std::string id) const
{
    for (const auto& pair : clients) {
        if (pair.first->get_id() == id) return pair.second;
    }
    std::cout << "Failed to find the Client, check the id." << std::endl;
    return -1;
}

// bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value)
// {
//     size_t pos1, pos2;
//     bool flag = true, flag2 = true;
//     pos1 = trx.find('-');
//     pos2 = trx.rfind('-', trx.length()-1);
//     std::cout << pos1 << std::endl;
//     std::cout << pos2 << std::endl;
//     if (pos1 == std::string::npos || pos2 == std::string::npos || pos1 == pos2) {
//         throw std::runtime_error("Format error");
//     }
//     else {
//         sender = trx.substr(0, pos1);
//         receiver = trx.substr(pos1 + 1, pos2 - pos1 - 1);
//         value = std::stod(trx.substr(pos2 + 1, trx.size() - pos2));
//         return true;
//     }
// }

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value)
{
    std::regex pattern(R"((\w+)-(\w+)-(\d+\.\d+))");
//    std::regex pattern("(\\w+)-(\\w+)-(\\d+\\.\\d+)");
    std::smatch match;
    if (!std::regex_search(trx, match, pattern)) throw std::runtime_error("transaction not in format");
    if (match[0] != trx) throw std::runtime_error("transaction not in format");
    sender = match[1];
    receiver = match[2];
    value = std::stod(match[3]);
    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const
{
    std::string sender, receiver;
    double value;
    size_t pos1, pos2;
    pos1 = trx.find('-');
    pos2 = trx.rfind('-');
    sender = trx.substr(0, pos1);
    receiver = trx.substr(pos1 + 1, pos2 - pos1 - 1);
    value = std::stod(trx.substr(pos2 + 1, trx.size() - pos2));
    if (get_wallet(sender) >= value) {
        pending_trxs.push_back(trx);
        return true;
    }
    else return false;
}

size_t Server::mine() 
{
    std::string mempool;
    std::vector<std::string> mempools;
    std::string sender, receiver;
    double value;
    std::string nonce_;
    for (const auto trx : pending_trxs) mempool += trx;
    for (const auto trx : pending_trxs) {
        size_t pos1 = trx.find('-');
        size_t pos2 = trx.rfind('-');
        
        sender = trx.substr(0, pos1);
        receiver = trx.substr(pos1 + 1, pos2 - pos1 - 1);
        value = std::stod(trx.substr(pos2 + 1, trx.size() - pos2));

        std::string nonce = std::to_string(get_client(sender)->generate_nonce());
        std::string mempool_(mempool);
        mempool_ += nonce;
        std::string hash{crypto::sha256(mempool_)};

        std::string subHash = hash.substr(0, 10);
        std::cout << subHash << std::endl;
        if (subHash.find("00") != std::string::npos) {
            std::cout << sender << std::endl;
            nonce_ = nonce;
            std::cout << nonce_;
            for (auto& pair : clients) {
                if (pair.first->get_id() == sender) {
                    pair.second += 6.25;
                    pair.second -=value;
                }
                if (pair.first->get_id() == receiver) {
                    pair.second += value;
                }
            }
        }
        else {
            for (auto& pair : clients) {
                if (pair.first->get_id() == sender) {
                    pair.second -=value;
                }
                if (pair.first->get_id() == receiver) {
                    pair.second += value;
                }
            }

        }
        // clients.at(get_client(sender)) -= coins;
        // clients.at(get_client(receiver)) += coins;
    }
    pending_trxs.clear();
    // return std::stoi(nonce_);
    return 1;
}
