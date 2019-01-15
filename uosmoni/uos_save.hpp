
#ifndef DAPPCLI_TIME_SAVE_HPP
#define DAPPCLI_TIME_SAVE_HPP

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <string>
 
#include <iostream>
#include <fstream>

class timeSave {
public:
    timeSave(boost::asio::io_context& io) :strand_(io),
    timer1_(io,boost::asio::chrono::seconds(1)),
	timer2_(io,boost::asio::chrono::seconds(1)),
	count_(0)
	{
        timer1_.async_wait(boost::asio::bind_executor(strand_,boost::bind(&timeSave::onSave1,this)));
        timer2_.async_wait(boost::asio::bind_executor(strand_,boost::bind(&timeSave::onSave2,this)));
    }

    ~timeSave() {
        std::cout << "Final count is " << count_ << std::endl;
    }

    void onSave1() {
        
        std::cout << "Timer 1: " << count_ << std::endl;
        ++count_;
		saveData();	
		timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(5));
		timer1_.async_wait(boost::asio::bind_executor(strand_,boost::bind(&timeSave::onSave1,this)));        
    }

    void onSave2() {
        if (count_ < 10) {
            std::cout << "Timer 2: " << count_ << std::endl;
            ++count_;
            timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));
            timer2_.async_wait(boost::asio::bind_executor(strand_,boost::bind(&timeSave::onSave2,this)));
        }
    }
	
	void updateData(string  hostdata)
	{
		int pos = hostdata.find("\n");
		string keystr = hostdata.substr(0,pos);
		uosdata[keystr] = hostdata;
	}
	
private:

	//save disk data
	void  saveData()
	{		
	
	    string strFile = "/home/qicity/aaa.txt";
	    ofstream outfile(strFile.c_str());   
   
		for(auto iter = uosdata.begin(); iter != uosdata.end(); iter++)  			
		{	
			outfile<< iter->second << endl;
			//cout<<iter->first<<' '<<iter->second<<endl;   
		}	
		
		outfile.close();
		
		uosdata.erase( uosdata.begin(), uosdata.end() );  
	}
	
	std::map<string,string> uosdata;
	
    boost::asio::steady_timer timer1_;
    boost::asio::steady_timer timer2_;
    int count_;
    boost::asio::io_context::strand strand_;
};
 

#endif //DAPPCLI_TIME_SAVE_HPP

