#include "http_server.h"

int main()
{
    HttpServer server("0.0.0.0", 8888);
    server.run();
}
