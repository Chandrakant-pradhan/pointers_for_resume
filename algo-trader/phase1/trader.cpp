#include "receiver.h"
#include <vector>
// functions
int string_compare(const std::string& str1, const std::string& str2) {
    size_t i = 0;
    while (i < str1.length() && i < str2.length()) {
        if (str1[i] != str2[i]) {
            return (str1[i] < str2[i]) ? -1 : 1;
        }
        i++;
    }
    if (str1.length() == str2.length()) {
        return 0; // Strings are equal
    }
    return (str1.length() < str2.length()) ? -1 : 1;
}

bool vector_compare(std::vector<std::pair<std::string, int>> a, std::vector<std::pair<std::string, int>> b)
{
    for (int i = 0; i < a.size(); i++)
    {
        // std::pair<std::string, int> temp = a[i];
        bool is_found = false;
        for (int j = 0; j < b.size(); j++)
        {
            if (string_compare(a[i].first , b[j].first) != 0 || a[i].second != b[j].second)
            {
                continue;
            }
            else if(string_compare(a[i].first , b[j].first) == 0 && a[i].second == b[j].second)
            {
                is_found = true;
                break;
            }
        }
        if (is_found)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
int my_stoi(std::string& str) {
    long i = 0;
    for (char ch : str) {
        if (ch >= '0' && ch <= '9') {
            i = i * 10 + (ch - '0');
        } else {
            // Handle non-numeric characters if needed
            // For example, break the loop or throw an exception
        }
    }
    return i;
}


// part 1
struct company
{
    int value = 0;
    int best_buy = 0;
    int best_sell = 0;
    std::string label = "";
};

std::vector<company> market;
std::string rem = "";

// part 2
struct stock
{
    std::vector<std::pair<std::string, int>> lab_quant;
    int price = 0;
    char mode;
};
std::vector<stock> stock_market;
int arbitrage_finder(std::vector<int>& subset){
    if(subset.size() == 1){
        return -1;
    }
    std::vector<std::pair<std::string,int>>label_buffer; //int is their coeff
    for(int i=0 ; i<subset.size() ; i++){
        stock temp = stock_market[subset[i]];
        for(auto& j : temp.lab_quant){
            bool found = false;
            int index;
            for(int k = 0 ; k<label_buffer.size();k++){
                if(j.first != label_buffer[k].first){
                    continue;
                }
                else{
                    found = true;
                    index = k;
                    break;
                }
            }
            if(!found){
                if(temp.mode == 's'){
                label_buffer.push_back({j.first , -1 * j.second});}

                else if(temp.mode == 'b'){
                label_buffer.push_back({j.first , j.second});}
            }
            else{
                if(temp.mode == 's'){
                    label_buffer[index].second -= j.second;}
                else if(temp.mode == 'b'){
                    label_buffer[index].second += j.second;
                }
            }
        }
    }

    int ans = 0;
    bool is_it=true;
    for(int l=0 ; l<label_buffer.size() ; l++){
        if(label_buffer[l].second !=0){
           is_it = false;
        }
        else{
            continue;
        }
    }
    if(is_it){
        for(int i=0 ; i<subset.size() ; i++){
           if(stock_market[subset[i]].mode == 'b'){
            ans += stock_market[subset[i]].price;
           }
           else if (stock_market[subset[i]].mode == 's'){
            ans -= stock_market[subset[i]].price;
           }
        }
        return ans;
    }
    return -1;
}

void printer(stock temp , char c){
    for(int i=0 ; i<temp.lab_quant.size();i++){
        std::cout<< temp.lab_quant[i].first << " "<<temp.lab_quant[i].second<<" ";
    }
    std::cout<<temp.price<<" "<<c;
}

std::pair<std::vector<int> , int> arbitrage_opportunities ;
int max_arbitrage = 0;
//PART 3
struct limit_stock
{
    std::vector<std::pair<std::string, int>> lab_quant;
    int price = 0;
    int quantity=0;
    char mode;
};
std::vector<limit_stock> limit_market;
std::pair<std::vector<std::pair<int,int>>,int> arb_opp ;
// std::pair<std::vector<std::pair<int,int>>,int> reset_arb_opp;
int max_limit_arb = 0;

std::vector< std::vector<int>> util(std::vector<int> subset){
    std::vector<int> myvec(subset.size());
    for(int i = 0; i < subset.size(); i++){
        // std::cout<<subset[i].first.quantity<<"\n";
        myvec[i] = limit_market[subset[i]].quantity;
    }
    std::vector<std::vector<int>> result;
    std::vector<int> current(myvec.size(), 1);

    while (true) {
        result.push_back(current);

        // Increment the last element
        int i = myvec.size() - 1;
        while (i >= 0 && current[i] == myvec[i]) {
            current[i] = 1;
            i--;
        }

        if (i < 0) {
            break;
        }

        current[i]++;
    }

    return result;
}

int helper(std::vector<int>& def , std::vector<int> current_perm ){
      if(def.size() == 1){
        return -1;
    }
    std::vector<std::pair<std::string,int>>label_buffer;
    for(int i=0 ; i<def.size() ; i++){
        limit_stock temp = limit_market[def[i]];
        for(auto& j : temp.lab_quant){
            bool found = false;
            int index;
            for(int k = 0 ; k<label_buffer.size();k++){
                if(j.first != label_buffer[k].first){
                    continue;
                }
                else{
                    found = true;
                    index = k;
                    break;
                }
            }
            if(!found){
                //label_buffer.push_back({j.first , j.second * current_perm[i]});
                if(temp.mode == 's'){
                label_buffer.push_back({j.first , -1 * j.second * current_perm[i]});}

                else if(temp.mode == 'b'){
                label_buffer.push_back({j.first , j.second*current_perm[i]});}
            }
            else{
                if(temp.mode == 's'){
                    label_buffer[index].second -= j.second * current_perm[i];}
                else if(temp.mode == 'b'){
                    label_buffer[index].second += j.second * current_perm[i];
                }
            }
        }
    }
    int ans = 0;
    bool is_it=true;
    for(int l=0 ; l<label_buffer.size() ; l++){
        if(label_buffer[l].second !=0){
           is_it = false;
        }
        else{
            continue;
        }
    }
    if(is_it){
        for(int i=0 ; i<def.size() ; i++){
           if(limit_market[def[i]].mode == 'b'){
            ans += limit_market[def[i]].price*current_perm[i];
           }
           else if (limit_market[def[i]].mode == 's'){
            ans -= limit_market[def[i]].price*current_perm[i];
           }
        }
        return ans;
    }
    return -1;
}

int limit_arbitrage_finder(std::vector<int>& abc , std::vector<std::pair<int,int>>&best_one){
    int maxi = 0;
    int best_k = -1;
    std::vector<std::vector<int>> perm = util(abc);
    

    for(int k =0 ; k < perm.size() ; k++){
        // for(int lam = 0 ;lam < perm[k].size() ; lam ++){
        //      std::cout<<perm[k][lam]<<"\n";
        //  }
        // std::vector<int> updated_subset; 
        std::vector<int> current_perm = perm[k];
        // for(int l = 0 ; l<subset.size();l++){
        //     limit_stock t = limit_market[subset[l]];
        //     std::vector<std::pair<std::string, int>> gh = t.lab_quant;
        //     for(int mn =0 ; mn < gh.size() ; mn++){
        //         gh[mn].second *= current_perm[l];
        //     }
        //     //gh is our new lab_quan
        //     t.lab_quant = gh;
        //     t.price *= current_perm[l];
        //     // t.quantity = current_perm[l];
        //     // stock temp;
        //     // temp.lab_quant = t.lab_quant;
        //     // temp.price = t.price;
        //     // temp.mode = t.mode;
        //     updated_subset.push_back({t,subset[l].second});
        // }
        int arb_cost = helper(abc , current_perm);
            if(arb_cost > maxi){
            maxi = arb_cost;
            best_k = k;
        }  
    }
    if(best_k != -1){
        for(int i =0;i<abc.size(); i++){
            best_one.push_back({perm[best_k][i],abc[i]});
        }
        return maxi;
    }
    return -1;
    
}
void printer2(limit_stock temp, char c, int q){
    std::vector<std::pair<std::string, int>> t = temp.lab_quant;
    for(int i=0 ; i<t.size();i++){
        std::cout<< t[i].first <<" "<<t[i].second<<" ";
    }
    std::cout<<temp.price<<" "<<q<<" "<<c;
}



int main(int argc, char **argv)
{
    Receiver rcv;
    bool eof = false;
    while (!eof)
    {
        std::string message = rcv.readIML();
        if (message.find("$") != std::string::npos)
        {
            rcv.terminate();
            eof = true;
        }
        if (rem.length() != 0)
        {
            rem = rem + message;
            message = rem;
            rem = "";
        }
        for (int i = 0; i < message.length(); i++)
        {
            if (message[i] == '\r' || message[i] == '\n')
            {
                message[i] = '*';
            }
        }
        std::istringstream iss(message);
        std::string word;
        std::vector<std::string> words;

        while (std::getline(iss, word, '*'))
        {
            words.push_back(word);
        }
        if (words[words.size() - 1][words[words.size() - 1].size() - 1] == '$')
        {
            words[words.size() - 1].pop_back();
        }
        for (auto i : words)
        {
            if (i[i.length() - 1] != '#')
            {
                words.pop_back();
                rem = rem + i;
            }
            else
            {
                continue;
            }
        }

        if (strcmp(argv[1], "1") == 0)
        {
            for (int i = 0; i < words.size(); i++)
            {
                if (i > 0)
                {
                    std::cout << "\r\n";
                }
                std::istringstream iss(words[i]);
                std::string word1;
                std::vector<std::string> words1;

                while (std::getline(iss, word1, ' '))
                {
                    words1.push_back(word1);
                }

                std::string firms = words1[0];
                int cost = std::stoi(words1[1]);

                std::string mode = words1[2];
                std::string b = "b#";
                std::string s = "s#";
                std::string b_dollar = "b#$";
                std::string s_dollar = "s#$";

                bool found = 0;
                for (auto &i : market)
                {
                    if (i.label != firms)
                    {
                        continue;
                    }
                    else
                    {
                        found = 1;
                        if (mode == s || mode == s_dollar)
                        {
                            if (i.best_sell)
                            {
                                if (i.best_sell > cost)
                                {
                                    i.best_sell = 0;
                                }
                                else
                                {
                                    std::cout << "No Trade";
                                    break;
                                }
                            }
                            if (i.best_buy)
                            {
                                if (i.best_buy == cost)
                                {
                                    i.best_buy = 0;
                                    std::cout << "No Trade";
                                    break;
                                }
                            }
                            if (i.value > cost)
                            {
                                i.value = cost;
                                std::cout << firms + " " << cost << " b";
                                break;
                            }
                            else
                            {
                                i.best_sell = cost;
                                std::cout << "No Trade";
                                break;
                            }
                        }
                        else if (mode == b || mode == b_dollar)
                        {
                            if (i.best_buy)
                            {
                                if (i.best_buy < cost)
                                {
                                    i.best_buy = 0;
                                }
                                else
                                {
                                    std::cout << "No Trade";
                                    break;
                                }
                            }
                            if (i.best_sell)
                            {
                                if (i.best_sell == cost)
                                {
                                    i.best_sell = 0;
                                    std::cout << "No Trade";
                                    break;
                                }
                            }
                            if (i.value < cost)
                            {
                                i.value = cost;
                                std::cout << firms + " " << cost << " s";
                                break;
                            }
                            else
                            {
                                i.best_buy = cost;
                                std::cout << "No Trade";
                                break;
                            }
                        }
                    }
                }
                // Code for new company
                if (!found)
                {
                    company firm;
                    firm.label = firms;
                    firm.value = cost;
                    market.push_back(firm);
                    if (mode == b || mode == b_dollar)
                    {
                        std::cout << firms << " " << cost << " "
                                  << "s";
                    }
                    else
                    {
                        std::cout << firms << " " << cost << " "
                                  << "b";
                    }
                }
            }
            std::cout << "\r\n";
        }
        if (strcmp(argv[1], "2") == 0){
            for (int i = 0; i < words.size(); i++){
                if (i > 0){
                    std::cout << "\r\n";
                }
                std::istringstream iss(words[i]);
                std::string word1;
                std::vector<std::string> words1;

                while (std::getline(iss, word1, ' ')){
                    words1.push_back(word1);
                }
                std::vector<std::pair<std::string, int>> temp;
                int cost;
                char mod;

                for (int i = 0; i <= words1.size() - 3; i = i + 2){
                    temp.push_back({words1[i], std::stoi(words1[i + 1])});
                }
                cost = std::stoi(words1[words1.size() - 2]);
                mod = words1[words1.size() - 1][0];

                // preparing for searching the stock in the existing ones
                bool is_b = false;
                bool is_s = false;
                int b_index;
                int s_index;
                int index_b_found;
                int index_s_found;
                std::vector<stock *> matching_stocks;
                for (int i = 0; i < stock_market.size(); i++){
                    if (vector_compare(stock_market[i].lab_quant, temp)){
                        if (stock_market[i].mode == 'b' ){
                            is_b = true;
                            b_index = matching_stocks.size();
                            index_b_found = i;
                            matching_stocks.push_back(&stock_market[i]);
                            if (is_s){
                                break;
                            }
                            continue;
                        }
                        else if (stock_market[i].mode == 's'){
                            is_s = true;
                            s_index = matching_stocks.size();
                            index_s_found = i;
                            matching_stocks.push_back(&stock_market[i]);
                            if (is_b){
                                break;
                            }
                            continue;
                        }
                    }
                }
                if(matching_stocks.size() == 0){
                    stock newStock;
                    newStock.lab_quant = temp;
                    newStock.price = cost;
                    newStock.mode = mod;
                    stock_market.push_back(newStock);
                }
                // if found the stock compare with new one
                
                else if (matching_stocks.size() == 1){
                    if (matching_stocks[0]->mode == 'b'){
                        if (mod == 'b'){
                            if (matching_stocks[0]->price >= cost){
                                // kill that trade and give out No Trade
                                std::cout << "No Trade";
                                continue;
                            }
                            else{
                                stock_market.erase(stock_market.begin() + index_b_found);
                                stock mystock;
                                mystock.lab_quant = temp;
                                mystock.price = cost;
                                mystock.mode = 'b';
                                stock_market.push_back(mystock);
                            }
                        }
                        else if (mod == 's'){
                            // very very imp haldle the cancellation of both the existing and new Trade
                            // which are of different type
                            if (matching_stocks[0]->price == cost){
                                stock_market.erase(stock_market.begin() + index_s_found);
                                std::cout << "No Trade";
                                continue;
                            }
                            // else just keep the new one as it is
                            else{
                                stock mystock;
                                mystock.lab_quant = temp;
                                mystock.price = cost;
                                mystock.mode = 's';
                                stock_market.push_back(mystock);
                            }
                        }
                    }
                    else if (matching_stocks[0]->mode == 's'){
                        if (mod == 's'){
                            if (matching_stocks[0]->price <= cost) {
                                // kill that trade and give out No Trade
                                std::cout << "No Trade";
                                continue;
                            }
                            else{
                                stock_market.erase(stock_market.begin() + index_s_found);
                                stock mystock;
                                mystock.lab_quant = temp;
                                mystock.price = cost;
                                mystock.mode = 's';
                                stock_market.push_back(mystock);
                            }
                        }
                        else if (mod == 'b'){
                            // very very imp haldle the cancellation of both the existing and new Trade
                            // which are of different type and move on to next line of input
                            if (matching_stocks[0]->price == cost){
                                stock_market.erase(stock_market.begin() + index_b_found);
                                std::cout << "No Trade";
                                continue;
                            }
                            else{
                                stock mystock;
                                mystock.lab_quant = temp;
                                mystock.price = cost;
                                mystock.mode = 'b';
                                stock_market.push_back(mystock);
                            }
                        }
                    }
                }

                else if (matching_stocks.size() == 2){
                    // first compare with same sign
                    // then compare with opp sign
                    if (mod == 'b'){
                        stock *buy = matching_stocks[b_index];
                        if (buy->price >= cost){
                            // kill the trade
                            std::cout << "No Trade";
                            continue;
                        }
                        else{
                            // we need to delete that buy trade then which we will do later
                            // now check with the sell trade of the same stock
                            stock *sell = matching_stocks[s_index];
                            if (sell->price == cost){
                                // Cancel out the old trade (of complementary type)
                                //with this new one and print No Trade
                                if(index_b_found > index_s_found){
                                    stock_market.erase(stock_market.begin() + index_b_found);
                                    stock_market.erase(stock_market.begin() + index_s_found);
                                }else{
                                    stock_market.erase(stock_market.begin() + index_s_found);
                                    stock_market.erase(stock_market.begin() + index_b_found);
                                }
                                std::cout << "No Trade";
                                continue;
                            }
                            else{
                                // else keep both the new and old of complementary type 
                                //and delete the one with same type
                                stock mystock;
                                mystock.lab_quant = temp;
                                mystock.price = cost;
                                mystock.mode = 'b';
                                stock_market.push_back(mystock);
                            }
                        }
                    }
                    else if (mod == 's'){
                        stock *sell = matching_stocks[s_index];
                        if (sell->price <= cost){
                            std::cout << "No Trade";
                        }
                        else{
                            // we need to delete that sell trade then which we will do later
                            // now check with the buy trade of the same stock
                            stock *buy = matching_stocks[b_index];
                            if (buy->price == cost){
                                // Cancel out the old trade (of complementary type)
                                //with this new one and print No Trade
                                if(index_b_found > index_s_found){
                                    stock_market.erase(stock_market.begin() + index_b_found);
                                    stock_market.erase(stock_market.begin() + index_s_found);
                                }else{
                                    stock_market.erase(stock_market.begin() + index_s_found);
                                    stock_market.erase(stock_market.begin() + index_b_found);
                                }
                                std::cout << "No Trade";
                                continue;
                            }
                            else{
                                // else keep both the new and old of complementary type 
                                //and delete the one with same type
                                stock mystock;
                                mystock.lab_quant = temp;
                                mystock.price = cost;
                                mystock.mode = 's';
                                stock_market.push_back(mystock);
                            }
                        }
                    }
                }

                // ARBITRAGE FIND
                int k = stock_market.size();
                long long pow_set = 1 << (k-1);
                int maxim = 0;
                for (int counter = 0; counter <  pow_set; counter++){
                    std::vector<int> subset;
                    for (int j = 0; j < k-1; j++) {
                        if (counter & (1 << j)) {
                            //subset.push_back({stock_market[j],j});
                            subset.push_back(j);
                        }
                    }
                    subset.push_back(k-1);
                    int arbitrage_cost = arbitrage_finder(subset);
                    if(arbitrage_cost  > maxim){
                        maxim = arbitrage_cost;
                        arbitrage_opportunities = {subset , arbitrage_cost};
                    }
                    else{
                      continue;
                    }
                }
                if(maxim == 0){
                    std::cout<<"No Trade";
                    continue;
                }
        
                max_arbitrage += maxim;
                for(int lamda = arbitrage_opportunities.first.size() - 1; lamda >=0 ; lamda-- ){
                    int erase_index = arbitrage_opportunities.first[lamda];
                    stock temp_i = stock_market [arbitrage_opportunities.first[lamda]];
                    //code for printing
                    if(temp_i.mode == 'b'){
                        printer(temp_i,'s');
                    }
                    else if(temp_i.mode == 's'){
                        printer(temp_i,'b');
                    }
                    if(lamda){std::cout<<"\n";}
                    stock_market.erase(stock_market.begin() + erase_index);
                }
                
            }
            
        }

        if (strcmp(argv[1], "3") == 0){
            for (int i = 0; i < words.size(); i++){
                if (i > 0){
                    std::cout << "\r\n";
                }
                std::istringstream iss(words[i]);
                std::string word1;
                std::vector<std::string> words1;

                while (std::getline(iss, word1, ' ')){
                    words1.push_back(word1);
                }
                std::vector<std::pair<std::string, int>> temp;
        
                int cost;
                char mod;
                int quantity;
                for (int i = 0; i <= words1.size() - 4; i = i + 2){
                    temp.push_back({words1[i], std::stoi(words1[i + 1])});
                }

                cost = std::stoi(words1[words1.size() - 3]);
                quantity = std::stoi(words1[words1.size() - 2]);
                mod = words1[words1.size() - 1][0];

                // idhar tak sahi
                std::vector<std::pair<limit_stock *,int>> matching_stocks;
                for (int i = 0; i < limit_market.size(); i++){
                    if (vector_compare(limit_market[i].lab_quant, temp)){
                       if(mod != limit_market[i].mode){
                        if(cost == limit_market[i].price){
                            matching_stocks.push_back({&limit_market[i],i});
                        }
                       }
                    }
                }

                //cancellation
                if(matching_stocks.size() == 0){
                    limit_stock k;
                    k.lab_quant = temp;
                    k.mode = mod;
                    k.price = cost;
                    k.quantity = quantity; 
                    limit_market.push_back(k);
                }
                else{
                    int l=0;
                    while(quantity >= matching_stocks[l].first->quantity && l < matching_stocks.size()){
                        quantity -= matching_stocks[l].first->quantity;
                        l++;
                    }
                    if(quantity){
                       if(l < matching_stocks.size()){
                          int index = matching_stocks[l].second;
                          limit_market[index].quantity -= quantity;
                          std::cout<<"No Trade";
                        for(int i=l-1; i>=0;i--){
                            limit_market.erase(limit_market.begin() + matching_stocks[i].second);
                        }
                        continue;
                        }
                       else{
                            for(int i=l-1; i>=0;i--){
                              limit_market.erase(limit_market.begin() + matching_stocks[i].second);
                          }
                            limit_stock k;
                            k.lab_quant = temp;
                            k.mode = mod;
                            k.price = cost;
                            k.quantity = quantity; 
                            limit_market.push_back(k);
                       }  
                    }
                    else{
                        std::cout<<"No Trade";
                        continue;
                    }
                }
                //cancellation is done
                //arbitrage shuru
                int k = limit_market.size();
                long long pow_set = 1 << (k-1);
                int muxi=0;
                for (int counter = 0; counter <  pow_set; counter++){
                    std::vector<int> subset;
                    for (int j = 0; j < k-1; j++) {
                        if (counter & (1 << j)) {
                            subset.push_back(j);
                        }
                    }
                    subset.push_back(k-1);
                    std::vector<std::pair<int,int>> best_one;
                    int arbitrage_cost = limit_arbitrage_finder(subset , best_one);
                    if(arbitrage_cost  > muxi){
                        //std::cout<<"__"<<arbitrage_cost<<"\n";
                        arb_opp = {best_one,arbitrage_cost};
                        muxi = arbitrage_cost;
                        best_one.clear();
                    }
                    else{
                      continue;
                    }
                }
                if(muxi== 0){
                    std::cout<<"No Trade";
                    continue;
                }
                  
                max_limit_arb += muxi;
                for(int ab=arb_opp.first.size()-1;ab>=0;ab--){
                    int index = arb_opp.first[ab].second;
                    int sub = arb_opp.first[ab].first;
                    if(limit_market[index].mode == 'b'){
                        printer2(limit_market[index],'s',sub);
                    }
                    else if(limit_market[index].mode == 's'){
                        printer2(limit_market[index],'b',sub);
                    }
                    limit_market[index].quantity -= sub;
                    if(limit_market[index].quantity == 0){
                        limit_market.erase(limit_market.begin() + index);
                    }
                    if(ab){std::cout<<"\n";}
                }
                
        }
    }
    if(strcmp(argv[1], "2") == 0){
        std::cout<<"\n"<<max_arbitrage;
    }
    if(strcmp(argv[1], "3") == 0){
        std::cout<<"\n"<<max_limit_arb;
    }
}  
}