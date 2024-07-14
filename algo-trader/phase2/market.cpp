#include "market.h"
#include <fstream>
#include <sstream>
bool vector_compare(std::vector<std::pair<std::string, int>> a, std::vector<std::pair<std::string, int>> b){
    for (int i = 0; i < a.size(); i++){
        std::pair<std::string, int> temp = a[i];
        bool is_found = false;
        for (int j = 0; j < b.size(); j++){
            if (temp != b[j]){
                continue;
            }
            else{
                is_found = true;
                break;
            }
        }
        if (is_found){
            continue;
        }
        else{
            return false;
        }
    }
    return true;
}

void tradePrinter(std::string buyer, std::string seller, int quantity, std::vector<std::pair<std::string, int>> lab_quant, int price){
    std::cout << buyer << " purchased " << quantity << " share of ";
    for(int i=0 ; i<lab_quant.size();i++){
        if (lab_quant.size() == 1 && lab_quant[0].second == 1){
            std::cout<< lab_quant[i].first << " ";
        }else{
            std::cout<< lab_quant[i].first << " "<<lab_quant[i].second<<" ";
        }
    }
    std::cout << "from " << seller << " for $" << price << "/share"<<"\n"; 
}

market::market(int argc, char** argv)
{
	//std::vector<std::pair<pq,pq>> arr;
}

void market::start(){   

	std::string filename = "output.txt";

    std::ifstream fileStream(filename);

    // Check if the file is open
    if (fileStream.is_open()) {
        std::string line;
        int index=0;
        // Read and print each line of the file
        while (std::getline(fileStream, line)) {
            index++;
            if(line == "TL") continue;
            else if(line == "!@") break;
            std::istringstream iss(line);
            std::string it;
            std::vector<std::string> buffer;

            while (std::getline(iss, it, ' ')){
                buffer.push_back(it);
            }
            int time = std::stoi(buffer[0]);
            int quantity = std::stoi(buffer[buffer.size()-2].substr(1));
            int price = std::stoi(buffer[buffer.size()-3].substr(1));
            int exp;
            if(std::stoi(buffer[buffer.size()-1]) != -1){
                exp = time + std::stoi(buffer[buffer.size()-1]);
            }else{
               exp = INT32_MAX;
            }
            if(!quantity){
                continue;
            }
            // if(index == 34){
            //     std::cout<<quantity<<std::endl;
            // }

            std::string mode = buffer[2];
            std::string broker = buffer[1];

            int broker_index ;
            for(broker_index = 0; broker_index < broker_list.size(); broker_index++){
                if(broker_list[broker_index].name == broker){
                    break;
                }
            }
            if(broker_index == broker_list.size()){
                broker_list.push_back({broker,0,0,0});
            }
               
            std::vector<std::pair<std::string, int>> temp;
            for (int i = 3; i <= buffer.size() - 4; i = i + 2){
                if((i + 1 < buffer.size()-3)){
                    temp.push_back({buffer[i], std::stoi(buffer[i + 1])});
                }else{
                    temp.push_back({buffer[i], 1});
                }
            }

            remove(time);

            int gh;
            bool same = false;

            for(gh=0; gh < arr.size(); gh++){
                if(mode == "BUY"){
                    if(arr[gh].second.size()){
                        if(vector_compare(temp, arr[gh].second.top().lab_quant)){
                            break;
                        }
                    }
                    else if(arr[gh].first.size()){
                        if(vector_compare(temp, arr[gh].first.top().lab_quant)){
                            same = true;
                            break;
                        }
                    }
                }
                else{
                    if(arr[gh].first.size()){
                        if(vector_compare(temp, arr[gh].first.top().lab_quant)){
                            break;
                        }
                    }
                    else if(arr[gh].second.size()){
                        if(vector_compare(temp, arr[gh].second.top().lab_quant)){
                            same = true;
                            break;
                        }
                    }
                }
            }
            if(same){
                 order chandu_order = {
                    time,
                    exp,
                    broker,
                    temp,
                    price,
                    quantity,
                    mode,
                    broker_index,
                };
                if(mode == "BUY"){
                    arr[gh].first.push(chandu_order);
                }
                else{
                    arr[gh].second.push(chandu_order);
                }
                continue;
            }
            if(gh == arr.size()) {
                 order chandu_order = {
                    time,
                    exp,
                    broker,
                    temp,
                    price,
                    quantity,
                    mode,
                    broker_index,
                };

                pq max_pq;
                pq min_pq;
                if(mode == "BUY"){
                    max_pq.push(chandu_order);
                }
                else{
                    min_pq.push(chandu_order);
                }

                arr.push_back({max_pq,min_pq});
                continue;
            }
            else if(gh < arr.size()){
                if(mode == "SELL"){
                    //std::cout<<"abe"<<"\n";
                    while(arr[gh].first.size() && arr[gh].first.top().price >= price){

                        if (arr[gh].first.top().quantity > quantity){
                            arr[gh].first.dec(quantity);
                            //print the trade 
                            broker_list[arr[gh].first.top().broker_index].buys += quantity;
                            broker_list[arr[gh].first.top().broker_index].transfer -= arr[gh].first.top().price * quantity;
                            broker_list[broker_index].sells += quantity;
                            broker_list[broker_index].transfer += arr[gh].first.top().price * quantity;
                            tot_transfer += arr[gh].first.top().price * quantity;
                            tot_shares += quantity;
                            comp_trades++;

                            tradePrinter(arr[gh].first.top().broker, broker, quantity, temp, arr[gh].first.top().price);
                            quantity = 0;
                            break;
                        }else{
                            quantity -= arr[gh].first.top().quantity;
                            //print the trade
                            //std::cout<<" 2 "<<arr[gh].first.top().quantity<<" "<<quantity<<" "<<index<<std::endl;
                            broker_list[arr[gh].first.top().broker_index].buys += arr[gh].first.top().quantity;
                            broker_list[arr[gh].first.top().broker_index].transfer -= arr[gh].first.top().price * arr[gh].first.top().quantity;
                            broker_list[broker_index].sells += arr[gh].first.top().quantity;
                            broker_list[broker_index].transfer += arr[gh].first.top().price * arr[gh].first.top().quantity;
                            tot_transfer += arr[gh].first.top().price * arr[gh].first.top().quantity;
                            tot_shares += arr[gh].first.top().quantity;
                            comp_trades++;

                            tradePrinter(arr[gh].first.top().broker,broker, arr[gh].first.top().quantity, temp, arr[gh].first.top().price);
                            arr[gh].first.pop();
                            if(!quantity) break;
                        }
                    }
                    if(quantity){
                        order chandu_order = {
                        time,
                        exp,
                        broker,
                        temp,
                        price,
                        quantity,
                        mode,
                        broker_index,
                    };
                        arr[gh].second.push(chandu_order);
                    }
                }
                else if(mode == "BUY"){
                    //std::cout<<"abe saale"<<"\n";
                    while(arr[gh].second.size() && arr[gh].second.top().price <= price){
                        if (arr[gh].second.top().quantity > quantity){
                            arr[gh].second.dec(quantity);
                            //print the trade 
                            //std::cout<<" 3 "<<std::endl;
                            broker_list[arr[gh].second.top().broker_index].sells += quantity;
                            broker_list[arr[gh].second.top().broker_index].transfer += arr[gh].second.top().price * quantity;
                            broker_list[broker_index].buys += quantity;
                            broker_list[broker_index].transfer -= arr[gh].second.top().price * quantity;
                            tot_transfer += arr[gh].second.top().price * quantity;
                            tot_shares += quantity;
                            comp_trades++;

                            tradePrinter(broker, arr[gh].second.top().broker, quantity, temp, arr[gh].second.top().price);
                            quantity =0;
                            break;
                        }else {
                            quantity -= arr[gh].second.top().quantity;
                            //print the trade
                            //std::cout<<" 4 "<<arr[gh].second.top().quantity<<" "<<quantity<<" "<<index<<std::endl;
                            broker_list[arr[gh].second.top().broker_index].sells += arr[gh].second.top().quantity;
                            broker_list[arr[gh].second.top().broker_index].transfer += arr[gh].second.top().price * arr[gh].second.top().quantity;;
                            broker_list[broker_index].buys += arr[gh].second.top().quantity;
                            broker_list[broker_index].transfer -= arr[gh].second.top().price * arr[gh].second.top().quantity;
                            tot_transfer += arr[gh].second.top().price * arr[gh].second.top().quantity;
                            tot_shares += arr[gh].second.top().quantity;
                            comp_trades++;

                            tradePrinter(broker, arr[gh].second.top().broker, arr[gh].second.top().quantity, temp, arr[gh].second.top().price);
                            arr[gh].second.pop();
                            if(!quantity) break;
                        }
                    }
                    if(quantity){
                        order chandu_order = {
                        time,
                        exp,
                        broker,
                        temp,
                        price,
                        quantity,
                        mode,
                        broker_index,
                    };
                        arr[gh].first.push(chandu_order);
                    }
                }
            }


        }

        // Close the file stream
        fileStream.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    std::cout<<std::endl<<"---End of Day---"<<std::endl;
    std::cout << "Total Amount of Money Transferred: $"<<tot_transfer<<std::endl;
    std::cout << "Number of Completed Trades: "<<comp_trades<<std::endl;
    std::cout << "Number of Shares Traded: "<<tot_shares<<std::endl;
    for(const auto &v : broker_list){
        std::cout<<v.name<<" bought "<<v.buys<< " and sold " << v.sells << " for a net transfer of $"<<v.transfer<<std::endl;
    }
}
