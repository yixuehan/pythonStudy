#include <iostream>
#include <functional>
#include <memory>
using namespace std;

#include <boost/timer/timer.hpp>
#include <boost/asio.hpp>
using namespace boost;
using namespace boost::asio;

// thread_local int rbuffer_length;
// thread_local char rbuffer[4096];

struct DataBuffer
{
    // std::thread::id thread_id;
    DataBuffer()
        :length_ptr(new int),
         buffer_ptr(new char[4096], [](char *p){
                delete []p;
                })
    {}
    std::shared_ptr<int> length_ptr;
    std::shared_ptr<char> buffer_ptr;
};

class TcpServerBase
{
public:
    TcpServerBase(unsigned short port)
        :_io_context(1),
         _endpoint(ip::tcp::v4(), port),
         _acceptor(_io_context, _endpoint)
    {
    }

    void run()
    {
        _io_context.run();
    }

protected:
    asio::io_context _io_context;
    ip::tcp::endpoint _endpoint;
    ip::tcp::acceptor _acceptor;
};

class TcpServerJson : public TcpServerBase
{
public:
    TcpServerJson(unsigned short port)
        :TcpServerBase(port)
    {
        auto socket_ptr = std::make_shared<ip::tcp::socket>(_io_context);
        _acceptor.async_accept(*socket_ptr, std::bind(&TcpServerJson::do_accept, this, socket_ptr, std::placeholders::_1));
    }
    void do_accept(std::shared_ptr<ip::tcp::socket> socket_ptr, const system::error_code &ec)
    {
        if (ec) {
            cout << ec.value() << endl;
            cout << ec.message() << endl;
            return;
        }
        cout << "accept:" << socket_ptr->remote_endpoint().address().to_string() << ":" << socket_ptr->remote_endpoint().port() << endl;

        DataBuffer dataBuffer;
        async_read(*socket_ptr, buffer(reinterpret_cast<char*>(dataBuffer.length_ptr.get()), 4),
                   std::bind(&TcpServerJson::do_read_length, this, socket_ptr, dataBuffer,
                   std::placeholders::_1, std::placeholders::_2));

        socket_ptr = std::make_shared<ip::tcp::socket>(_io_context);
        _acceptor.async_accept(*socket_ptr, std::bind(&TcpServerJson::do_accept, this, socket_ptr, std::placeholders::_1));
    }

    void do_read_length(std::shared_ptr<ip::tcp::socket> socket_ptr, DataBuffer dataBuffer,
                        const boost::system::error_code &ec, size_t rbyte)
    {
        if (ec) {
            cout << ec.value() << endl;
            cout << ec.message() << endl;
            return;
        }
        cout << "read length:" << rbyte << endl;
        cout << "body length:" << *dataBuffer.length_ptr << endl;
        // dataBuffer.thread_id = std::this_thread::get_id();
        // assert (dataBuffer.thread_id == std::this_thread::get_id() && "接收与处理不在一个线程");
#if 0
        boost::system::error_code ec_body;
        rbyte = read(*socket_ptr, buffer(dataBuffer.buffer_ptr.get(), *dataBuffer.length_ptr), ec_body);
        do_read_body(socket_ptr, dataBuffer, ec_body, rbyte);
#else
        async_read(*socket_ptr, buffer(dataBuffer.buffer_ptr.get(), *dataBuffer.length_ptr),
                    std::bind(&TcpServerJson::do_read_body, this, socket_ptr, dataBuffer,
                    std::placeholders::_1, std::placeholders::_2));
#endif
        
    }

    void do_read_body(std::shared_ptr<ip::tcp::socket> socket_ptr, DataBuffer dataBuffer,
                      const boost::system::error_code &ec, size_t rbyte)
    {
        if (ec) {
            cout << ec.value() << endl;
            cout << ec.message() << endl;
            return ;
        }
        // assert (dataBuffer.thread_id == std::this_thread::get_id() && "接收与处理不在一个线程");
        assert(static_cast<int>(rbyte) == *dataBuffer.length_ptr);
        cout << "rbyte:" << rbyte << endl;
        cout << "body:" << std::string(dataBuffer.buffer_ptr.get(), rbyte) << endl;
        async_read(*socket_ptr, buffer(reinterpret_cast<char*>(dataBuffer.length_ptr.get()), 4),
                   std::bind(&TcpServerJson::do_read_length, this, socket_ptr, dataBuffer,
                   std::placeholders::_1, std::placeholders::_2));
    }
};

int main()
{
    TcpServerJson server(12345);
    for (int i = 0; i < 100; ++i) {
        std::thread([&]{
                server.run();
                }).detach();
    }
    server.run();
    return 0;
}
