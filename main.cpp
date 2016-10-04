#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using std::vector;
using std::string;

class solution {
  public:
    vector<string> rearrangeString(const string & str, int k) {
        std::unordered_map<char,int> dict;
        for (auto ch : str) {
            if (dict.find(ch) == dict.end())
                dict[ch] = 0;
            dict[ch]++;
        }

        vector<string> result;
        for (auto it = dict.begin(); it != dict.end(); ++it) {
            string curr;
            auto temp = addOne(dict, curr, k);
            for (auto tmp : temp) {
                if (tmp.size() == str.size())
                    result.push_back(tmp);
            }
        }

        if (!result.empty()) {
            std::sort(result.begin(), result.end());
            auto it = std::unique(result.begin(), result.end());
            result.resize(std::distance(result.begin(), it));
        }

        return result;
    }

  private:
    vector<string> addOne(const std::unordered_map<char,int> & dict, const string & curr, int k)
    {
        vector<string> result;
        string charsNotAllowed;
        for (size_t i = 1; i < (size_t)k && curr.size() >= i ; i++)
            charsNotAllowed.append(curr.substr(curr.size()-i,1));
        // std::cout << charsNotAllowed << std::endl;
        vector<char> next = getNext(dict, charsNotAllowed);
        if (next.empty())
            result.push_back(curr);
        else {
            for (auto nx : next) {
                auto dict_update = dict;
                if (dict_update[nx] > 1)
                    dict_update[nx]--;
                else
                    dict_update.erase(nx);
                auto curr_update = curr;
                curr_update.append(1, nx);

                auto temp = addOne(dict_update, curr_update, k);
                for (auto s : temp)
                    result.push_back(s);
            }
            // std::sort(result.begin(), result.end());
            // auto it = std::unique(result.begin(), result.end());
            // result.resize(std::distance(result.begin(), it));
        }
        return result;
    }

    vector<char> getNext(const std::unordered_map<char,int> & dict, const string & charsNotAllowed)
    {
        vector<char> chars;
        for (auto it = dict.begin(); it != dict.end(); ++it) {
            if (charsNotAllowed.find(it->first) == string::npos)
                chars.push_back(it->first);
        }
        return chars;
    }
};

int main() {
    // string str{"aabbcc"};
    // int k = 3;

    string str{"aaabc"};
    int k = 3;
    
    // string str{"aaadbbcc"};
    // int k = 2;

    solution soln;
    vector<string> newStrs = soln.rearrangeString(str, k);
    if (!newStrs.empty()) {
        std::cout << "The rearranged strings are:\n";
        std::for_each(newStrs.begin(), newStrs.end(),
                      [](const string & s){
                          std::cout << s << std::endl;
                      });
    }
    else {
        std::cout << "There is no such string." << std::endl;
    }
}
