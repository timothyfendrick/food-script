#include <iostream>
#include <sstream> //stringstream
#include <vector>
#include <fstream>


using namespace std;

struct Food {

    string name;
    string input;
    int numCals;
    int numSugars;
    int numCarbs;
    bool isDrink; //if not so else food
    vector <string> characteristics;

    Food(string inputFull) {
        stringstream ss (inputFull);

        getline(ss, name, ','); //grabs name

        getline(ss, input, ','); //grabs input
        numCals = stoi(input);

        getline(ss, input, ',');
        numSugars = stoi(input);

        getline(ss, input, ',');
        numCarbs = stoi(input);

        getline(ss, input, ',');
        if(input == "True") {
            isDrink = true;
        }
        else {
            isDrink = false;
        }

        while(getline(ss, input, ',')) {
            characteristics.push_back(input);
        }
    }

    void print() {
        cout << name << endl;
        cout << "Calories: " << numCals << endl;
        cout << "Sugars: " << numSugars << endl;
        cout << "Carbs: " << numCarbs << endl;
        if(isDrink) {
            cout << "Drink" << endl;
        } else {
            cout << "Food" << endl;
        }
        cout << "Characteristics: " << endl;
        for(const string& characteristic : characteristics) {
            cout << characteristic;
            if(characteristic != characteristics[characteristics.size()]) {
                cout << ", ";
            }
        }
        cout << endl;
        cout << endl;
    }
};

void printMenu(){
    cout << "(1) Find all vegetarian options" << endl;
    cout << "(2) Find all Vegan options" << endl;
    cout << "(3) Find all Gluten Free and Vegan options" << endl;
    cout << "(4) Find all drink options" << endl;
    cout << "(5) Find all food options" << endl;
    cout << "(6) Find food options with 0 carbs and 0 sugar" << endl;
    cout << "(7) Find food options with less than 100 calories" << endl;
    cout << "(8) quits the program" << endl;
}

//bool drink (True) checking for drink, (False) checking for Food
void getType(vector <Food> &foods, bool drink) {
    for(Food food : foods) {
        if(food.isDrink  == drink) {
            food.print();
        }
    }
}

void checkCharacteristic(vector <Food> &foods, vector <string> checks) {
    int num = 0;
    for(Food food : foods) {
        for(string characteristic : food.characteristics) {
            if(checks.size() > 1) {
                for(string check : checks) {
                    if(check == characteristic){
                        num ++;
                    }
                }
                if(num == checks.size()) {
                    food.print();
                }
            }
            else{
                if(characteristic == checks[0]) {
                    food.print();
                    break;
                }
            }

        }
    }
}

void get0Carbs0Sugar(vector <Food> &foods) {
    for(Food food : foods) {
        if(!food.isDrink) {
            if(food.numCarbs == 0) {
                if(food.numSugars == 0) {
                    food.print();
                }
            }
        }
    }

}

void getLessThan100Cals(vector <Food> &foods) {
    for(Food food : foods) {
        if(!food.isDrink) {
            if(food.numCals > 100) {
                food.print();
            }
        }

    }
}
int main() {
    ifstream fin;
    fin.open("input.csv");

    vector <Food> foods;

    if(fin.is_open()) {
        string splicedInput;
        while(getline(fin, splicedInput)) {

            stringstream ss (splicedInput); // Writing to the string stream
            foods.push_back(Food {splicedInput});
        }
    }

    int selectionInput;
    do {
        printMenu();
        cout << "Which option would you like to see the results for?: ";
        cin >> selectionInput;


        switch (selectionInput) {
            case 1:
                checkCharacteristic(foods, {"Vegetarian"});
                break;
            case 2:
                checkCharacteristic(foods, {"Vegan"});
                break;
            case 3:
                checkCharacteristic(foods, {"Vegan"});
            case 4:
                getType(foods, true);
                break;
            case 5:
                getType(foods, false);
                break;
            case 6:
                get0Carbs0Sugar(foods);
                break;
            case 7:
                getLessThan100Cals(foods);
                break;
            default:
                cout << "Wrong Input";
        }

    }
    while(selectionInput != 8);

    return 0;
}