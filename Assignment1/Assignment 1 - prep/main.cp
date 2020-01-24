//
//  main.cpp
//  Assignment 1
//
//  Created by Gurman Brar on 2020-01-16.
//  Copyright © 2020 Gurman Brar. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

//PURPOSE: Repersents an instance of one artwork peice
class Artwork{
    string artist_name, title;
    unsigned int year_made;
    
public:
    //Empty or default constructor
    Artwork() : year_made(0) {}
    
    //Parametric constructor
    Artwork(string new_name, string new_title, unsigned int new_year) :
    artist_name(new_name), title(new_title), year_made(new_year){}
    
    //Overloaded operator ==
    bool operator==(const Artwork& rhs) const{ // ensures that the object is not modified
        
        bool are_equal = artist_name == rhs.artist_name;
        are_equal = are_equal && title == rhs.title;
        are_equal = are_equal && year_made == rhs.year_made;
        return are_equal;
    }

};

//PURPOSE: Child class of Artwork that holds attributes of a sold peice of art
class SoldArtwork : public Artwork{
    string customer_name, customer_adress;
    double sale_amount;
    
public:
    //Empty default constructor
    SoldArtwork() : sale_amount(0) {}
    
    //Parametric constructor
    SoldArtwork(string new_name, string new_adress, double sale_price,
                Artwork new_artwork) :
    customer_name(new_name), customer_adress(new_adress), sale_amount(sale_price), Artwork(new_artwork) {} // calling artwork constructor to handel the implicit init.
    
    //Overloaded Operator ==
    bool operator==(const SoldArtwork& rhs) const{
        bool are_equal = customer_name == rhs.customer_name;
        are_equal = are_equal && customer_adress == rhs.customer_adress;
        are_equal = are_equal && sale_amount == rhs.sale_amount;
        are_equal = are_equal && static_cast<Artwork>(rhs) == static_cast<Artwork>(*this);
        return are_equal;
    }
};


//PURPOSE: represents models of artwork pecies held by an art gallery
class ArtCollection{
    vector<Artwork> myArtwork;
    vector<SoldArtwork> mySoldArtwork;
public:
    bool insert_artwork(const Artwork& artwork_info){
        
        //Bool to keep track of duplicate
        bool has_duplicate = false;
        
        //iterate through my artwork to check for duplicate value
        for(int entry = 0; entry < myArtwork.size() && !has_duplicate; ++entry){
            if(myArtwork[entry] == artwork_info){
                has_duplicate = true;
            }
            else has_duplicate = false;
        }
        
        //insert the given artwork into the artwork vector, else return false since insert failed
        if(!has_duplicate) {
            myArtwork.push_back(artwork_info);
            return true;
        }
        else return false;
    }
    
    /*PURPOSE: faciliatates the sale of artwork, removal from one vector and addition of
     instance to another */
    bool sell_artwork(const SoldArtwork& sold_info){
        
        //iterates through the vector and checks for position of the artwork info
        for(int entry = 0; entry < myArtwork.size(); entry++){
            if(myArtwork[entry] == static_cast<Artwork>(sold_info)){
                swap(myArtwork[entry], myArtwork[myArtwork.size() - 1]);
                myArtwork.pop_back();
                mySoldArtwork.push_back(sold_info);
            }
        }
        return true;
    }
    
    bool operator==(const ArtCollection& rhs) const{
        bool is_equal = true;
        
        if(myArtwork.size() != rhs.myArtwork.size() || mySoldArtwork.size() != rhs.mySoldArtwork.size()) return is_equal = false;
        
        while(myArtwork.size() == rhs.myArtwork.size()){
        for(int i = 0; i < myArtwork.size() && is_equal; i++){
            if(myArtwork[i] == rhs.myArtwork[i]){
                is_equal = true;
            } else {
                is_equal = false;
            }
        }
        
        for(int j = 0; j < mySoldArtwork.size() && is_equal; j ++){
            if(mySoldArtwork[j] == rhs.mySoldArtwork[j]){
                is_equal = true;
            } else{
                is_equal = false;
            }
          }
        }
        
        return is_equal;
        
    
    }
    
    friend ArtCollection operator+(const ArtCollection lhs, const ArtCollection rhs) {
        ArtCollection combination;
        
        for(int j = 0; j < lhs.myArtwork.size(); j++){
            combination.insert_artwork(lhs.myArtwork[j]);
        }
        for(int i = 0; i < rhs.myArtwork.size(); i++){
            combination.insert_artwork(rhs.myArtwork[i]);
        }
        for(int k = 0; k < lhs.mySoldArtwork.size(); k++){
            combination.sell_artwork(lhs.mySoldArtwork[k]);
        }
        for(int l = 0; l < rhs.mySoldArtwork.size(); l++){
            combination.sell_artwork(rhs.mySoldArtwork[l]);
        }

        return combination;
    }
    
};


int main(){
    
    
    
    return 0;
};

