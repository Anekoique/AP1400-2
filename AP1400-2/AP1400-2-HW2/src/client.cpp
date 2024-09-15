#include "client.h"
#include "crypto.h"

Client::Client(std::string id, const Server& server) : id(id), server(&server)
{
    crypto::generate_key(public_key, private_key);
}

std::string Client::get_id()
{
    return id;
}

std::string Client::get_publickey()
{
    return public_key;
}

double get_wallet()
{
    
}
