#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <set>

template<class It>
size_t max_increasing_len(It p, It q)
{
    if (p == q) {
        return 0;
    }
    size_t maxSize = 1;
    size_t currentLength = 1;
    It p_prev = p;
    p++;
    while(p != q) {
        if (*(p_prev) < *(p)) {
            ++currentLength;
        } else {
            if (maxSize < currentLength) {
                maxSize = currentLength;
            }
            currentLength = 1;
        }
        p_prev++;
        p++;
    }
    if (maxSize < currentLength) {
        maxSize = currentLength;
    }
    return maxSize;
}

void queueOfGoblins() {
    std::deque <int> queueGoblins;
    int countRequests;
    std::cin >> countRequests;
    char marker;
    int numberOfGoblin;
    while (countRequests--) {
        std::cin >> marker;
        if (marker == '+' || marker == '*') {
            std::cin >> numberOfGoblin;
            if (marker == '+') {
                queueGoblins.push_back(numberOfGoblin);
            } else {
                auto iter = queueGoblins.cbegin();
                int sizeQueue = queueGoblins.size() % 2 == 0 ? queueGoblins.size() / 2 : queueGoblins.size() / 2 + 1;
                queueGoblins.insert(iter + sizeQueue, numberOfGoblin);
            }
        } else if (marker == '-') {
            std::cout << queueGoblins.front() << "\n";
            queueGoblins.pop_front();
        }
    }
}

void poliglots() {
    int countRequests;
    std::cin >> countRequests;
    int countPersons = countRequests;
    std::map <std::string, int> allKnows;
    std::set <std::string> anyKnows;
    int countLanguages;
    while (countRequests--) {
        std::cin >> countLanguages;
        std::string language;
        while (countLanguages--) {
            std::cin >> language;
            anyKnows.insert(language);
            if (allKnows.count(language) != 0) {
                allKnows[language] += 1;
            } else {
                allKnows[language] = 1;
            }
        }
    }
    std::vector <std::string> answerLanguages;
    for (auto iter{allKnows.begin()}; iter != allKnows.end(); ++iter) {
        if (iter->second == countPersons) {
            answerLanguages.push_back(iter->first);
        }
    } 
    std::cout << answerLanguages.size() << "\n";
    for (std::string word: answerLanguages) {
        std::cout << word << "\n";
    }
    std::cout << anyKnows.size() << "\n";
    for (std::string word: anyKnows) {
        std::cout << word << "\n";
    }
}
using namespace std;
vector <string> makeOneFromTwo(vector <string> first, vector <string>& second) {
        vector <string> result;
        for (string c1: first) {
            for (string c2: second) {
                string str = c1 + c2;
                result.push_back(str);
            }
        }
        return result;
}
vector <string> letterCombinations(string digits) {
    map <char, vector <string>> numbers;
    numbers['2'] = {"a", "b", "c"};
    numbers['3'] = {"d", "e", "f"};
    numbers['4'] = {"g", "h", "i"};
    numbers['5'] = {"j", "k", "l"};
    numbers['6'] = {"m", "n", "o"};
    numbers['7'] = {"p", "q", "r", "s"};
    numbers['8'] = {"t", "u", "v"};
    numbers['9'] = {"w", "x", "y", "z"};
    vector <string> answer;
    answer.push_back("");
    for (size_t i = 0; i < digits.size(); ++i) {
        answer = makeOneFromTwo(answer, numbers[digits[i]]);
    }
    return answer;
}
int main(){
    string str;
    cin >> str;
    vector <string> answer;
    answer = letterCombinations(str);
    for (string str: answer) {
        cout << str << " ";
    }
    return 0;
}