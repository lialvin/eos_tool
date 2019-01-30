#ifndef UOS_MONI_SERVER_HPP
#define UOS_MONI_SERVER_HPP

#include  "uos_save.hpp"

using boost::asio::ip::tcp;

class session
  : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket socket)
    : socket_(std::move(socket))
  {
     //memcpy(data_,"servr:",6);
  }

  void start()
  {
    do_read();
  }

private:
  void do_read()
  {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            //BOOST_LOG_TRIVIAL(info) << "receive "<< socket_.remote_endpoint().address()<< " length "<< length;  
            //BOOST_LOG_TRIVIAL(info) << "receive "<< data_ << " length "<< length;  
            do_deal(length);
          }
        });
  }

  void do_deal(std::size_t length)
  {
    
    std::string retstr("recv:once");
  
    auto self(shared_from_this());
    std::string nodestr(data_,length);    
    g_uosSave->updateData(nodestr );
    boost::asio::async_write(socket_, boost::asio::buffer(retstr.data(), retstr.length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            do_read();
          }
        });

  }

  tcp::socket socket_;
  
  enum { max_length = 3024 };
  char data_[max_length];
};

class server
{
public:
  server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            std::make_shared<session>(std::move(socket))->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
};

#endif
