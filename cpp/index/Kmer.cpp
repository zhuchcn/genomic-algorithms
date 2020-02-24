
#include "Kmer.h"

Kmer::Kmer(int k, std::string text) : k_(k), text_(text), index_() {
    index();
}

Kmer::Kmer() {}

Kmer::~Kmer() {}

void Kmer::index(){
    for(int i = 0; i < text_.length() - k_ + 1; ++i){
        std::string kmer = text_.substr(i, k_);
        if(index_.find(kmer) == index_.end())
            index_.insert({{kmer, {i}}});
        else index_[kmer].push_back(i);
    }
}

std::vector<int> Kmer::query(std::string pattern) const {
    std::vector<int> offsets;

    auto it = index_.find(pattern.substr(0,k_));

    if(it == index_.end()) return offsets;

    for(auto i = it->second.begin(); i < it->second.end(); ++i) {
        if(pattern.substr(k_) == text_.substr((*i)+k_, pattern.length()-k_))
            offsets.push_back((*i));
    }
    return offsets;
}