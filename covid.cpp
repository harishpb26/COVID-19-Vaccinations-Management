#include <iostream>

#define COUNTRIES 5
#define STATES 5

typedef struct Person {
    bool isvaccinated;
    int age;
    int occupation;
    long long int id;
    std::string name;
    Person* right;
    Person* left;
} Person;

typedef struct People {
    long long int num;
    long long int num_vaccinated;
    Person* next;
} People;

// main db
People*** db;

void remove(Person* root){
    if(root){
        remove(root->left);
        remove(root->right);
        delete root;
        root = NULL;
    }
}

int main(){
    // dynamically allocate memory
    db = new People**[COUNTRIES];
    for(int i = 0; i < COUNTRIES; i++){
        db[i] = new People*[STATES];
        for(int j = 0; j < STATES; j++){
            db[i][j] = new People;
            db[i][j]->num = 0;
            db[i][j]->num_vaccinated = 0;
            db[i][j]->next = NULL;
        }
    }

    bool isvaccinated;
    int ch, country_code, state_code, occupation_code, age;
    long long int id;
    std::string name;

    while(1) {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "0 - Display country codes" << std::endl;
        std::cout << "1 - Display state codes" << std::endl;
        std::cout << "2 - Insert a person" << std::endl;
        std::cout << "3 - Vaccinate a person" << std::endl;
        std::cout << "4 - Check person's status" << std::endl;
        std::cout << "5 - Display summary" << std::endl;
        std::cout << "6 - Exit" << std::endl;
        std::cout << "Enter choice :- " << std::endl;
        std::cin >> ch;
        if(ch == 6)
            break;
        switch(ch){
            case 0 :
                break;
            case 1 :
                break;
            case 2 :
                std::cout << "Enter person id :- " << std::endl;
                std::cin >> id;
                // getchar();
                std::cout << "Enter person name :- " << std::endl;
                std::cin >> name;
                // getline(std::cin, name);
                std::cout << "Enter person age :- " << std::endl;
                std::cin >> age;

                std::cout << "Enter person's occupation code :- " << std::endl;
                std::cin >> occupation_code;

                std::cout << "Enter country code :- " << std::endl;
                std::cin >> country_code;

                std::cout << "Enter state code :- " << std::endl;
                std::cin >> state_code;

                std::cout << "Is person vaccinated?" << std::endl;
                std::cout << "0 : No" << std::endl;
                std::cout << "1 : Yes" << std::endl;
                std::cin >> isvaccinated;
                break;
            case 3 :
                std::cout << "Enter id, country code and state code of the person to vaccinate :- " << std::endl;
                std::cin >> id >> country_code >> state_code;
                break;
            case 4 :
                std::cout << "Enter id, country code and state code of the person to check status" << std::endl;
                std::cin >> id >> country_code >> state_code;
                break;
            case 5 :
                break;
            default :
                std::cout << "Invalid choice" << std::endl;
        }
    }
    for(int i = 0; i < COUNTRIES; i++){
        for(int j = 0; j < STATES; j++){
            remove(db[i][j]->next);
            delete db[i][j];
        }
        delete[] db[i];
    }
    delete[] db;
    return 0;
}
