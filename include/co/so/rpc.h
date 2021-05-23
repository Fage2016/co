#pragma once

#include "../json.h"
#include "co/hash.h"
#include <unordered_map>

namespace rpc {

class Service {
  public:
    Service() = default;
    virtual ~Service() = default;

    virtual const char* name() const = 0;

    virtual void process(const Json& req, Json& res) = 0;
};

class Server {
  public:
    Server();
    ~Server();

    /**
     * add a service 
     *   - Multiple services can be added into the server. 
     * 
     * @param s  a pointer to a Service, it must be created with operator new.
     */
    void add_service(Service* s);

    /**
     * add a pair of username and password 
     *   - Multiple usernames and passwords can be added into the server.
     */
    void add_userpass(const char* user, const char* pass);

    /**
     * add usernames and passwords
     * 
     * @param s  a json string: { "user1":"pass1", "user2":"pass2" }
     */
    void add_userpass(const char* s);

    /**
     * start the rpc server 
     *   - By default, key and ca are NULL, and ssl is disabled.
     * 
     * @param ip    server ip, either an ipv4 or ipv6 address.
     * @param port  server port
     * @param key   path of ssl private key file.
     * @param ca    path of ssl certificate file.
     */
    void start(const char* ip, int port, const char* key=NULL, const char* ca=NULL);

  private:
    void* _p;

    DISALLOW_COPY_AND_ASSIGN(Server);
};

class Client {
  public:
    Client(const char* ip, int port, bool use_ssl=false);
    ~Client();

    void set_userpass(const char* user, const char* pass);

    void call(const Json& req, Json& res);

    void ping();

  private:
    void* _p;

    DISALLOW_COPY_AND_ASSIGN(Client);
};

} // rpc
