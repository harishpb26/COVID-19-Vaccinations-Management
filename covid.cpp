#include <iostream>
#include <fstream>

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

bool checkCountryStateCodes(int country_code, int state_code){
    if(country_code < 0 || country_code >= COUNTRIES){
        std::cout << "Invalid country code" << std::endl;
        return false;
    }
    if(state_code < 0 || state_code >= STATES){
        std::cout << "Invalid state code" << std::endl;
        return false;
    }
    return true;
}

Person* insertBST(Person* root, Person* person){
    if(!root)
        return person;
    if(person->id < root->id)
        root->left = insertBST(root->left, person);
    else
        root->right = insertBST(root->right, person);
    return root;
}

void insertPerson(long long int id, std::string name, int age, int occupation_code, int country_code, int state_code){
    if(checkCountryStateCodes(country_code, state_code)){
        // create a Person
        Person* person = new Person;
        person->id = id;
        person->name = name;
        person->age = age;
        person->occupation = occupation_code;
        person->isvaccinated = false;
        person->left = NULL;
        person->right = NULL;

        People* metanode = db[country_code][state_code];
        metanode->next = insertBST(metanode->next, person);
        metanode->num += 1;
    }
}

Person* searchBST(Person* root, long long int id){
    Person* cur = root;
    while(cur){
        if(cur->id > id)
            cur = cur->left;
        else if(cur->id < id)
            cur = cur->right;
        else
            return cur;
    }
    return NULL;
}

void checkStatus(long long id, int country_code, int state_code){
    if(checkCountryStateCodes(country_code, state_code)){
        Person* root = db[country_code][state_code]->next;
        Person* target = searchBST(root, id);
        if(target){
            if(target->isvaccinated)
                std::cout << target->name << " has been vaccinated" << std::endl;
            else
                std::cout << target->name << " has not been vaccinated" << std::endl;
        }
        else
            std::cout << "Person not found" << std::endl;
    }
}

void displaySummary(){
    long long int num = 0;
    long long int num_vaccinated = 0;
    for(int i = 0; i < COUNTRIES; i++){
        for(int j = 0; j < STATES; j++){
                num += (db[i][j])->num;
                num_vaccinated += (db[i][j])->num_vaccinated;
        }
    }
    if(num){
        std::cout << "Number of persons vaccinated : " << num_vaccinated << std::endl;
        std::cout << "Number of persons : " << num << std::endl;
    }
    else
        std::cout << "No data found" << std::endl;
}

void readFile(std::string name){
    std::string text;

    // read contents into text
    std::ifstream fd(name);
    while (getline (fd, text)) {
        std::cout << text << std::endl;
    }
    fd.close();
}

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

    int ch, country_code, state_code, occupation_code, age;
    long long int id;
    std::string name;

    while(1) {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "0 - Display country codes" << std::endl;
        std::cout << "1 - Display state codes" << std::endl;
        std::cout << "2 - Insert a person" << std::endl;
        std::cout << "3 - Check person's status" << std::endl;
        std::cout << "4 - Display summary" << std::endl;
        std::cout << "5 - Exit" << std::endl;
        std::cout << "Enter choice :- " << std::endl;
        std::cin >> ch;
        if(ch == 5)
            break;
        switch(ch){
            case 0 :
                readFile("country_codes.txt");
                break;
            case 1 :
                readFile("state_codes.txt");
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

                readFile("occupation_codes.txt");
                std::cout << "Enter person's occupation code :- " << std::endl;
                std::cin >> occupation_code;

                readFile("country_codes.txt");
                std::cout << "Enter country code :- " << std::endl;
                std::cin >> country_code;

                readFile("state_codes.txt");
                std::cout << "Enter state code :- " << std::endl;
                std::cin >> state_code;

                insertPerson(id, name, age, occupation_code, country_code, state_code);
                break;
            case 3 :
                std::cout << "Enter id, country code and state code of the person to check status" << std::endl;
                std::cin >> id >> country_code >> state_code;
                checkStatus(id, country_code, state_code);
                break;
            case 4 :
                displaySummary();
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
