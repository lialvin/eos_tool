#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "boost/algorithm/string.hpp"
#include "boost/multi_index_container.hpp"
#include "boost/multi_index/ordered_index.hpp"
#include "boost/multi_index/hashed_index.hpp"
#include "boost/multi_index/identity.hpp"
#include "boost/multi_index/member.hpp"

//WordCnt�࣬��¼�˵��ʼ���Ӧ�ĳ��ָ���
struct WordCnt {
    std::string word;
    int cnt;

    WordCnt(const std::string& word_, int cnt_) :
        word(word_),
        cnt(cnt_) {
        }

    //Ĭ�ϰ���cnt����
    bool operator<(const WordCnt& rhs) const {
        return cnt < rhs.cnt;
    }
};//WordCnt

typedef boost::multi_index::multi_index_container<
        //������Ԫ������
        WordCnt,
        boost::multi_index::indexed_by<
            //�����Ψһ��˳��ο�identtiy<WordCnt>��Ҳ����WordCnt.operator<
            boost::multi_index::ordered_non_unique<
                boost::multi_index::identity<WordCnt> >,
            //����Ҳ����hash��hashkeyʹ�� WorkdCnt::word
            boost::multi_index::hashed_unique<
                boost::multi_index::member<WordCnt, std::string, &WordCnt::word> >
        >
> WordCntContainer;

int testWordCnt() {
    WordCntContainer word_cnt_container;

    std::vector<std::string> contents;
    //�ı� -> ����vec
    boost::split(contents,
            "hello hello hello hello hello cpp cpp cpp cpp go go go python python shell",
            boost::is_any_of(" "));

    //ȡ�ڶ���������Ҳ����hash��
    auto& word_index = word_cnt_container.get<1>();
    for (size_t i = 0; i < contents.size(); ++i) {
        const std::string& word = contents[i];
        auto iter = word_index.find(word);
        //������cnt+1���������1
        if (iter == word_index.end()) {
            word_index.insert({word, 1});
        } else {
            word_index.modify(iter, [](WordCnt& word_cnt){ word_cnt.cnt++; });
        }
    }

    //ȡword_cnt_container������һ��������Ҳ���ǰ���cnt��������
    for (const auto word_cnt : word_cnt_container) {
        //shell   1
        //python  2
        //go      3
        //cpp     4
        //hello   5
        std::cout << word_cnt.word << "\t" << word_cnt.cnt << std::endl;
    }

    return 0;
}

