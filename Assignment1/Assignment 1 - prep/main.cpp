//
//  BME 122
//  Assignment 1
//
//  Created by Gurman Brar on 2020-01-16.
//  Copyright © 2020 Gurman Brar. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cassert>

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
    
    friend class artworkTest;

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
    
    friend class sellArtworkTest;
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
                return is_equal = false;
            }
        }
        
        for(int j = 0; j < mySoldArtwork.size() && is_equal; j ++){
            if(mySoldArtwork[j] == rhs.mySoldArtwork[j]){
                is_equal = true;
            } else{
                return is_equal = false;
            }
          }
        }
        
        return true;;
        
    
    }
    
    // External function that has direct access to private members of art collection
    friend ArtCollection operator+(const ArtCollection lhs, const ArtCollection rhs);
    friend class artCollectionTest;
    
};

ArtCollection operator+(const ArtCollection lhs, const ArtCollection rhs) {
    ArtCollection combination (lhs);
    
    for(int i = 0; i < rhs.myArtwork.size(); i++){
        combination.myArtwork.push_back(rhs.myArtwork[i]);
    }

    for(int j = 0; j < rhs.mySoldArtwork.size(); j++){
        combination.mySoldArtwork.push_back(rhs.mySoldArtwork[j]);
    }

    return combination;
}



class artCollectionTest{
    vector<Artwork> test_values;
    vector<SoldArtwork> sold_test_values;
    
    void setup(){
        Artwork a1("Gurman", "Brar", 2000), a2("Aryan", "Singh", 2000);
        Artwork a3("Eknoor", "Singh", 2001), a4("Dougie", "Anson", 2001);
        
        SoldArtwork s1("Gurman", "400 Webster road", 5000, a1);
        SoldArtwork s2("Aryan", "270 Webster road", 2000, a2);
        SoldArtwork s3("Eknoor", "120 Webster road", 3800, a3);
        SoldArtwork s4("Dougie", "090 Webster road", 200, a4);
        
        test_values.push_back(a1);
        test_values.push_back(a2);
        test_values.push_back(a3);
        test_values.push_back(a4);
        
        sold_test_values.push_back(s1);
        sold_test_values.push_back(s2);
        sold_test_values.push_back(s3);
        sold_test_values.push_back(s4);

    }
    
    
    void art_Collection_Test(){
        ArtCollection test_collection;
        ArtCollection test2_collection;
        ArtCollection combination;
        
        
        // Test within the ternary operator for feedback if the class method works
        cout<< (test_collection.insert_artwork(test_values[0]) ? "Test insert artwork passed" : "Test insert artwork failed") << endl;
        
        
        assert(test_collection.myArtwork.size() == 1);
        cout << "Test myArtwork.size() passed" << endl;
        
        
        assert(test_collection.insert_artwork(test_values[1]));
        cout << "Test to insert a2 into artcollection passed" << endl;
        
        
        assert(!test_collection.insert_artwork(test_values[1]));
        cout << "Test to insert a2 into artcollection failed since it has already been inserted" << endl;
        
        
        assert(test_collection.myArtwork.size() == 2);
        cout << "Size of the array is still 2, duplicate not inserted" << endl;
        
        
        // Populate the second art collection
        test2_collection.myArtwork.push_back(test_values[2]);
        test2_collection.myArtwork.push_back(test_values[3]);
        
        
        // Set an artcollection to the addition of two others
        combination = test_collection + test2_collection;
        
        
        assert(combination.myArtwork.size() == 4);
        cout << "Combination collection has 4 peices in it, so + operator has worked" << endl;
        
        assert(!(test_collection == test2_collection));
        cout << "The artcollections equal operator works since they do not contain equal objects" << endl;
        
        assert(test_collection.sell_artwork(sold_test_values[0]));
        assert(test_collection.myArtwork.size() == 1);
        assert(test_collection.mySoldArtwork.size() == 1);
        cout << "The sell artwork method of the artcollection class has worked" << endl;
    }
    
public:
    
    void run(){
        
        setup();
        art_Collection_Test();
        
    }

};



class artworkTest{
     vector<Artwork> test_values;
       
    void setup(){
        Artwork a1("Gurman", "Brar", 2000), a2("Aryan", "Singh", 2000);
        Artwork a3("Eknoor", "Singh", 2001), a4("Dougie", "Anson", 2001);
        test_values.push_back(a1);
        test_values.push_back(a2);
        test_values.push_back(a3);
        test_values.push_back(a4);
    }
    
    void artwork_test(){
        
        assert(test_values.size() == 4);
        cout << "The objects of the Artwork class are being created correctly" << endl;
        
        assert(!(test_values[0] == test_values[1]));
        cout << "The equal operator works correctly since the two objects are not equal" << endl;
    }
    
public:
    
    void run(){
        
        setup();
        artwork_test();
        
    }
    
    
};


class sellArtworkTest{
    vector<SoldArtwork> test_values;
    
    void setup(){
        Artwork a1("Gurman", "Brar", 2000), a2("Aryan", "Singh", 2000);
        Artwork a3("Eknoor", "Singh", 2001), a4("Dougie", "Anson", 2001);
        
        SoldArtwork s1("Gurman", "400 Webster road", 5000, a1);
        SoldArtwork s2("Aryan", "270 Webster road", 2000, a2);
        SoldArtwork s3("Eknoor", "120 Webster road", 3800, a3);
        SoldArtwork s4("Dougie", "090 Webster road", 200, a4);
        
        test_values.push_back(s1);
        test_values.push_back(s2);
        test_values.push_back(s3);
        test_values.push_back(s4);
    
    }
    
    void sell_artwork_test(){
        
        assert(test_values[0].sale_amount == 5000);
        assert(test_values[0].customer_name == "Gurman");
        assert(test_values[0].customer_adress == "400 Webster road");
        cout << "The soldArtwork constructor is functioning and the parameters can be assigned to the class attributes" << endl;
        
        
        assert(!(test_values[0] == test_values[1]));
        cout << "The equal operator works correctly" << endl;
                
    }
    
public:
    
    void run(){
        setup();
        sell_artwork_test();
    }
};

int main(){
    
    cout << "Now testing art collection . . ." << endl;
    
    cout << " " << endl;
    cout << " " << endl;
    
    artCollectionTest test;
    test.run();
    
    cout << " " << endl;
    cout << " " << endl;
    
    cout << "Now testing Artwork class and objects . . ." << endl;
    
    cout << " " << endl;
    cout << " " << endl;
    
    artworkTest test1;
    test1.run();
    
    cout << " " << endl;
    cout << " " << endl;
    
    cout << "Now testing sell Artwork class and objects . . ." << endl;
    
    cout << " " << endl;
    cout << " " << endl;
    
    sellArtworkTest test2;
    test2.run();
    
    cout << " " << endl;
    cout << " " << endl;
    
    cout << "The program has sucesfully run and been tested" << endl;
    
    return 0;
};

