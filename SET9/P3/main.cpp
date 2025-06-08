#include <iostream>
#include <map>
#include <queue>
#include <string>

int main() {
    size_t n;
    std::cin>>n;
    std::vector<size_t> key(n);
    for(size_t i =0;i<n;++i){
        std::cin>>key[i];
    }
    std::string answer;

    std::map<size_t,std::string> map;
    for(size_t i = 0; i<128;++i){
        map[i] = std::string(1,static_cast<char>('\0'+i));
    }
    answer = std::string(1,static_cast<char>(key[0]));
    size_t idx = 128;
    size_t len = key.size();

    std::string current= std::string(1,static_cast<char>(key[0]));;
    size_t current_idx;
    std::string sub_current;
    size_t i = 1;
    size_t j = 1;

    while(i<len){
        sub_current = current;
        current_idx = key[i];
        if(map.find(current_idx)!=map.end()){
            current = map[current_idx];
            answer+= current;
        }
        if(map.find(current_idx)==map.end()){
            if(idx==current_idx){
                current = sub_current;
                current+=sub_current[0];
                answer+= current;
            }
        }
        ++i;
        ++idx;
        map[idx-1]  = sub_current;
        map[idx-1] += current[0];
    }
    std::cout<<answer;
    return 0;
}