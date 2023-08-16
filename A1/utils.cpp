#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> initial_analysis(string filename,int thres){
    ifstream fin;
    fin.open(filename);
    if(!fin.is_open()){
        cerr<<"Cannot openfile \'"<<filename<<"\'"<<endl;
    }
    int p;
    map<int,int> itemsMap;
    while(fin>>p){
        if(itemsMap.find(p)==itemsMap.end()){
            itemsMap[p]=1;
        }
        else{
            itemsMap[p]++;
        }
    }

    fin.close();

    vector<vector<int>> itemsFreqVect;
    for(map<int,int>::iterator itr=itemsMap.begin();itr!=itemsMap.end();itr++){
        if(itr->second>=thres){
            itemsFreqVect.push_back(vector<int>(1,itr->first));
        }
    }
    
    return itemsFreqVect;
}

bool check_subsets(vector<int>& cand, vector<vector<int>>& F){
    int n = cand.size();
    for(int i=0;i<n;i++){
        bool subset_found=false;
        for(int j=0;j<F.size();j++){
            int x=0;
            int y=0;
            bool eq=true;
            while(y<n-1){
                if(x==i){
                    x++;
                }
                else{
                    if(F[j][y]!=cand[x]){
                        eq =false;
                        break;
                    }
                    x++;
                    y++;
                }
            }
            if(eq){
                subset_found = true;
                break;
            }
        }
        if(!subset_found){
            return false;
        }
    }
    return true;
}


vector<vector<int>> candidate_gen(vector<vector<int>>& F){
    int n = F[0].size();
    vector<vector<int>> candidates;
    for(int i=0;i<F.size()-1;i++){
        for(int j=i+1;j<F.size();j++){

            bool only_last_different = true;

            //Checking if only last element is different or not
            for(int k=0;k<n-1;k++){
                if(F[i][k]!=F[j][k]){
                    only_last_different = false;
                }
            }


            if(only_last_different){

                vector<int> new_candidate;
                for(int k=0;k<n-1;k++){
                    new_candidate.push_back(F[i][k]);
                }
                
                if(F[i][n-1]<=F[j][n-1]){
                    new_candidate.push_back(F[i][n-1]);
                    new_candidate.push_back(F[j][n-1]);
                }
                else{
                    new_candidate.push_back(F[j][n-1]);
                    new_candidate.push_back(F[i][n-1]);
                }

                //check_if all subsets are present or not
                if(check_subsets(new_candidate,F)){
                    candidates.push_back(new_candidate);
                }
            }
        }
    }
    return candidates;

}


vector<int> split_string(string s){
    vector<int> nums;
    string k="";
    for(char c: s){
        if(c==' '){
            nums.push_back(stoi(k));
            k="";
        }
        else{
            k+=c;
        }
    }
    if(k!=""){
        nums.push_back(stoi(k));
    }
    return nums;
}

bool is_subset(vector<int>& u,vector<int>& v){
    for(int i=0;i<u.size();i++){
        bool found =false;
        for(int j=0;j<v.size();j++){
            if(u[i]==v[j]){
                found=true;
                break;
            }
        }
        if(!found){
            return false;
        }
    }
    return true;
}

vector<vector<int>> frequent_candidates(vector<vector<int>>& C,string filename,int thres){
    vector<pair<vector<int>,int>> freq_C;
    for(int i=0;i<C.size();i++){
        freq_C.push_back(pair<vector<int>,int>(C[i],0));
    }
    

    ifstream fin;
    fin.open(filename);
    string s;
    while(getline(fin,s)){
        if(s=="") continue;
        vector<int> nums = split_string(s);

        for(int i=0;i<freq_C.size();i++){
            if(is_subset(freq_C[i].first,nums)){
                freq_C[i].second++;
            }
        }
    }

    fin.close();

    vector<vector<int>> F;
    for(int i=0;i<freq_C.size();i++){
        if(freq_C[i].second>=thres){
            F.push_back(freq_C[i].first);
        }
    }
    return F;
}

vector<vector<vector<int>>> mine_frequent_sets(string filename, int thres){
    vector<vector<vector<int>>> all_freq_sets;
    vector<vector<int>> F = initial_analysis(filename,thres);
    all_freq_sets.push_back(F);
    for(int i=0;i<F.size();i++){
        for(int j=0;j<F[i].size();j++){
            cout<<F[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;

    while(F.size()!=0){
        vector<vector<int>> C = candidate_gen(F);
        F=frequent_candidates(C,filename,thres);

        if(F.size()!=0){
            all_freq_sets.push_back(F);
            for(int i=0;i<F.size();i++){
                for(int j=0;j<F[i].size();j++){
                    cout<<F[i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<"size="<<F.size()<<endl;
            cout<<endl<<endl;
        }
    }
    return all_freq_sets;
    
}

int main(){
    string s="D_small.dat";
    vector<vector<vector<int>>> a= mine_frequent_sets(s,2400);
    
}