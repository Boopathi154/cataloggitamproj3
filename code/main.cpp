#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;

class Auction{
public:
    string itemName;
    unsigned long long startingPrice;
    unsigned long long highestBid;
    string highestBidder;
    bool active;
    unsigned long long bidIncrement;
    bool notifyPreviousBidder;
    map<string, unsigned long long> bidderMap;

    Auction(string name,unsigned long long price,unsigned long long increment,bool notify):itemName(name),startingPrice(price),highestBid(price),highestBidder("None"),active(true),bidIncrement(increment),notifyPreviousBidder(notify){}

    void placeBid(string bidder,unsigned long long amount){
        if(amount>=highestBid+bidIncrement){
            if(notifyPreviousBidder&&highestBidder!="None"){
                cout<<"Notification: "<<highestBidder<<", your bid has been surpassed by "<<bidder<<" with an amount of "<<amount<<endl;
            }
            highestBid=amount;
            highestBidder=bidder;
            bidderMap[bidder]=amount;
            cout<<"Bid placed successfully."<<endl;
        }
        else cout<<"Bid must be higher than the current highest bid plus the increment ("<<highestBid+bidIncrement<<")."<<endl;
    }

    void closeAuction(){
        active=false;
        cout<<"Auction for "<<itemName<<" closed. Highest bid: "<<highestBid<<" by "<<highestBidder<<endl;
    }
};

class OnlineAuctionSystem{
    vector<Auction> auctions;

public:
    void createAuction(string itemName,unsigned long long startingPrice,unsigned long long bidIncrement,bool notifyPreviousBidder){
        Auction newAuction(itemName,startingPrice,bidIncrement,notifyPreviousBidder);
        auctions.push_back(newAuction);
        cout<<"Auction for "<<itemName<<" created with starting price "<<startingPrice<<endl;
    }

    void viewAuctions(){
        if(auctions.empty()){
            cout<<"No auctions available."<<endl;
            return;
        }
        for(int i=0;i<auctions.size();i++){
            if(auctions[i].active){
                cout<<"Auction "<<i+1<<": "<<auctions[i].itemName<<", Starting Price: "<<auctions[i].startingPrice<<", Highest Bid: "<<auctions[i].highestBid<<", Highest Bidder: "<<auctions[i].highestBidder<<endl;
            }
        }
    }

    void placeBid(int auctionIndex,string bidder,unsigned long long amount){
        if(auctionIndex<0||auctionIndex>=auctions.size()){
            cout<<"Invalid auction index."<<endl;
            return;
        }
        if(auctions[auctionIndex].active){
            auctions[auctionIndex].placeBid(bidder,amount);
        }
        else cout<<"Auction is closed."<<endl;
    }

    void closeAuction(int auctionIndex){
        if(auctionIndex<0||auctionIndex>=auctions.size()){
            cout<<"Invalid auction index."<<endl;
            return;
        }
        if(auctions[auctionIndex].active){
            auctions[auctionIndex].closeAuction();
        }
        else cout<<"Auction is already closed."<<endl;
    }
};

int main(){
    OnlineAuctionSystem system;
    int choice;
    while(true){
        cout<<"1. Create Auction\n2. View Auctions\n3. Place Bid\n4. Close Auction\n5. Exit\nEnter your choice: ";
        cin>>choice;
        if(choice==1){
            string itemName;
            unsigned long long startingPrice, bidIncrement;
            bool notifyPreviousBidder;
            cout<<"Enter item name: ";
            cin.ignore();getline(cin,itemName);
            cout<<"Enter starting price: ";
            cin>>startingPrice;
            cout<<"Enter bid increment: ";
            cin>>bidIncrement;
            cout<<"Notify previous highest bidder when outbid? (1 for Yes, 0 for No): ";
            cin>>notifyPreviousBidder;
            system.createAuction(itemName,startingPrice,bidIncrement,notifyPreviousBidder);
        }
        else if(choice==2){
            system.viewAuctions();
        }
        else if(choice==3){
            int auctionIndex;
            string bidder;
            unsigned long long amount;
            cout<<"Enter auction index: ";
            cin>>auctionIndex;
            cout<<"Enter your name: ";
            cin.ignore();getline(cin,bidder);
            cout<<"Enter bid amount: ";
            cin>>amount;
            system.placeBid(auctionIndex-1,bidder,amount);
        }
        else if(choice==4){
            int auctionIndex;
            cout<<"Enter auction index to close: ";
            cin>>auctionIndex;
            system.closeAuction(auctionIndex-1);
        }
        else if(choice==5)break;
        else cout<<"Invalid choice. Try again."<<endl;
    }
    return 0;
}
