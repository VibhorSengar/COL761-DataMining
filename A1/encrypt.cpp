#include <cassert>
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>
#include<fstream>
#include<algorithm>
#include<unordered_set>
#include "fptree.hpp"


Transaction split_string(std::string s,int& max_item,long long& item_count){
    Transaction nums;
    int p;
    std::string k="";
    for(char c: s){
        if(c==' '){
            p = std::stoi(k);
            if(p>max_item) max_item = p;
            nums.push_back(p);
            k="";
        }
        else{
            k+=c;
        }
    }
    if(k!=""){
        p = std::stoi(k);
        if(p>max_item) max_item = p;
        nums.push_back(p);
    }
    item_count+=nums.size();
    return nums;
}

int min(int a,int b){
    if (a<b) return a;
    else return b;
}

bool is_subset(std::set<int>& a, std::unordered_set<int>& b){
    for(int x:a){
        if(b.find(x)==b.end()) return false;
    }
    return true;
}

int main(int argc, const char *argv[])
{   

    if(argc<3){
        std::cerr<< "Not enough arguments"<<std::endl;
    }

    std::string infile = argv[1];
    std::string outfile = argv[2];

    std::ifstream fin;
    fin.open(infile);

    std::ofstream fout;
    fout.open(outfile);

    if(!fin.is_open()){
        std::cerr<<infile<<" not found."<<std::endl;
    }


    std::vector<Transaction> transactions;

    int max_item = 0;
    std::string s;

    long long item_count = 0;
    while(getline(fin,s)){
        transactions.push_back(split_string(s,max_item,item_count));
    }
    max_item++;

    int factor;
    int num_trans = transactions.size();

    if(item_count<=400000){
        factor = 0.75;
    }
    else if(item_count<20000000){
        factor = 0.005;
    }
    else{
        factor = 0.25;
    }
    const int minimum_support_threshold = num_trans*factor;

    std::cout<<"Frequent set Mining started...."<<std::endl;

    const FPTree fptree{ transactions, minimum_support_threshold };

    const std::set<Pattern> patterns = fptree_growth( fptree );

    std::cout<<"Frequent set Mining completed....\nEncrypting File...."<<std::endl;


    int mx_size=0;

    for(auto x: patterns){
        int k = x.first.size();
        if(k>mx_size){
            mx_size = k;
        }
    }
    std::vector<std::vector<std::pair<std::pair<std::set<int>,int>,bool>>> pat(mx_size-1);

    for(auto x: patterns){
        int k = x.first.size();
        if(k>1){
            std::pair<std::pair<std::set<int>,int>,bool> p(std::pair<std::set<int>,int> (x.first,max_item++),false);
            pat[k-2].push_back(p);
        }
    }

    
    std::vector<std::vector<int>> new_transactions;
    for(int i=0;i<transactions.size();i++){
        std::unordered_set<int> tra (transactions[i].begin(),transactions[i].end());
        std::vector<int> n_tra;
        int s = min(tra.size(),pat.size()+1);
        while(tra.size()>0 && s>1){
            bool fnd= false;
            for(int j=0;j<pat[s-2].size();j++){
                if(is_subset(pat[s-2][j].first.first,tra)){
                    n_tra.push_back(pat[s-2][j].first.second);
                    pat[s-2][j].second=true;
                    for(int x:pat[s-2][j].first.first){
                        tra.erase(x);
                    }
                    s = min(s,min(tra.size(),pat.size()+1));
                    fnd=true;
                    break;
                }
            }
            if(!fnd) s--;
        }
        for(int x: tra){
            n_tra.push_back(x);
        }
        new_transactions.push_back(n_tra);
    }

    int map_size=0;
    for(auto x: pat){
        for(auto y : x){
            if(y.second) map_size++;
        }
    }

    fout<<map_size<<std::endl;
    for(auto x: pat){
        for(auto y : x){
            if(y.second){
                fout<<y.first.second<<" ";
                for(int z: y.first.first){
                    fout<<z<<" ";
                }
                fout<<std::endl;
            }
        }
    }
    for(std::vector<int> a: new_transactions){
        for(int b: a){
            fout<<b<<" ";
        }
        fout<<std::endl;
    }

    return EXIT_SUCCESS;
}
