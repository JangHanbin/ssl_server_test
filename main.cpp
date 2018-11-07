#include <iostream>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

#define MAX_CLIENTS 100

using namespace std;

void init_openssl()
{
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
    SSL_library_init();
}
int main(int argc, char* argv[])
{
    init_openssl();
    SSL_CTX *ctx = SSL_CTX_new(SSLv23_server_method());
    if(ctx==NULL)
    {
        cout<<"Unable to load context"<<endl;
        ERR_print_errors_fp(stderr);
        return -1;
    }

    SSL *ssl;

    if(!SSL_CTX_load_verify_locations(ctx,"./dork94.com.crt",NULL))
    {
        cout<<"Failed to load verify locations."<<endl;
        ERR_print_errors_fp(stderr);
        return -1;
    }

    /**************************************** Socket Setting*****************************************/
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd <0)
    {
        cout<<"Failed to open socket."<<endl;
        return -1;
    }

    int port = atoi(argv[1]);
    struct sockaddr_in s_addr;
    //init s_addr by zero byte
    bzero(&s_addr,sizeof(struct sockaddr_in));
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr =INADDR_ANY;
    s_addr.sin_port =htons(port);

    if(bind(fd, (struct sockaddr*)&s_addr,sizeof(struct sockaddr_in)) < 0)
    {
        cout<<"Failed to socket bind."<<endl;
        return -1;
    }

    //listen for clients
    listen(fd,MAX_CLIENTS);
    //Client fd
    int cfd;
    /**************************************** Socket Setting*****************************************/
    while(ctd = accept(cfd,0,0))
    {

    }
    BIO *accept_bio = BIO_new_socket()

    return 0;
}
