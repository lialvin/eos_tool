
#ifndef DAPPCLI_TCP_CLIENT_HPP
#define DAPPCLI_TCP_CLIENT_HPP

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <string>
#include "connection.hpp"
#include <iostream>


namespace dapp {
namespace server2 {

class cliTimer {
public:
    cliTimer(boost::shared_ptr<boost::asio::io_context>  io) :strand_(*io),
    timer1_(*io,boost::asio::chrono::seconds(1)),timer2_(*io,boost::asio::chrono::seconds(1)),count_(0){
        timer1_.async_wait(boost::asio::bind_executor(strand_,boost::bind(&cliTimer::print1,this)));
        timer2_.async_wait(boost::asio::bind_executor(strand_,boost::bind(&cliTimer::print2,this)));
    }

    ~cliTimer() {
        std::cout << "Final count is " << count_ << std::endl;
    }

    void print1() {
        if (count_ < 10) {
            std::cout << "Timer 1: " << count_ << std::endl;
            ++count_;
        timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(5));
        timer1_.async_wait(boost::asio::bind_executor(strand_,boost::bind(&cliTimer::print1,this)));
        }
    }

    void print2() {
        if (count_ < 10) {
            std::cout << "Timer 2: " << count_ << std::endl;
            ++count_;
            timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));
            timer2_.async_wait(boost::asio::bind_executor(strand_,boost::bind(&cliTimer::print2,this)));
        }
    }

private:
    boost::asio::steady_timer timer1_;
    boost::asio::steady_timer timer2_;
    int count_;
    boost::asio::io_context::strand strand_;
};
}; //server
};//dapp

#endif //DAPPCLI_TCP_CLIENT_HPP

