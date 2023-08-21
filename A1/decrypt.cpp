#include<fstream>
#include<iostream>
#include<unordered_map>
#include<vector>
#include<limits.h>
#include<set>

void map_insert(std::unordered_map<int,std::vector<int>>& map,std::string s,int& min_key){
    int key=-1;
    std::vector<int> nums;
    std::string k="";
    for(char c: s){
        if(c==' '){
            if(key==-1){
                key = std::stoi(k);
                if(key<min_key) min_key =key;
            }
            else nums.push_back(std::stoi(k));
            k="";
        }
        else{
            k+=c;
        }
    }
    if(k!=""){
        nums.push_back(std::stoi(k));
    }
    map[key]=nums;
}

void decrypt_transaction(std::unordered_map<int,std::vector<int>> & map ,std::set<int>& tra ,std::string s,int min_key){
    int p;
    std::string k="";
    for(char c: s){
        if(c==' '){
            p = std::stoi(k);
            if(p<min_key){
                tra.insert(p);
            }
            else{
                std::vector<int> nums = map[p];
                for(int x: nums){
                    tra.insert(x);
                }
            }
            k="";
        }
        else{
            k+=c;
        }
    }
    if(k!=""){
        p = std::stoi(k);
        if(p<min_key){
            tra.insert(p);
        }
        else{
            std::vector<int> nums = map[p];
            for(int x: nums){
                tra.insert(x);
            }
        }
    }
}

int main(int argc, const char *argv[]){

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

    std::string s;
    int map_size;

    getline(fin,s);

    map_size = std::stoi(s);

    int min_key= INT_MAX;
    std::unordered_map<int,std::vector<int>> map;


    for(int i=0;i<map_size;i++){
        getline(fin,s);
        map_insert(map,s,min_key);
    }


    while(getline(fin,s)){
        std::set<int> tra;
        decrypt_transaction(map,tra,s,min_key);
        for(int x:tra){
            fout<<x<<" ";
        }
        fout<<std::endl;
    }
}