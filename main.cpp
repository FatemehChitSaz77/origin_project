#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;



string generate_random_number (int length)
{
    string number;
    for (int i = 0; i < length; ++i)
    {
        number += to_string (rand () % 10);
    }
    return number;
}

string generate_expiration_date(int years_in_future) {
    srand(time(0));

    time_t now = time(0);
    tm *itm = localtime(&now);
    int year = 1900 + itm->tm_year + years_in_future;

    int day = rand() % 31 + 1;

    int month = rand() % 12 + 1;

    if (month <= 6) {
        if (day > 31) day = 31;
    } else {
        if (day > 30) day = 30;
    }

    string day_str = (day < 10 ? "0" : "") + to_string(day);
    string month_str = (month < 10 ? "0" : "") + to_string(month);

    string expiration_date = day_str + "/" + month_str + "/" + to_string(year);

    return expiration_date;
}


class BankAccount
{
public:

protected:
    string account_number;
    string shaba_number;
    string type;
    string card_number;
    string cvv2;
    string expiryDate;
    string firstpassword;
    string secondpassword;
    string dynamicpassword;
    double balance;
    vector <pair<double, time_t>> transfers;

public:
    BankAccount () {}
    BankAccount(string _type, string _account_number,
                string _shaba_number, string _card_number, string _cvv2,
                string _expiryDate, string _firstpassword,
                string _secondpassword, double _balance)
            : account_number(_account_number), shaba_number(_shaba_number),
              type(_type), card_number(_card_number), cvv2(_cvv2), expiryDate(_expiryDate),
              firstpassword(_firstpassword), secondpassword(_secondpassword),
              balance(_balance) {}

    string getType () const { return type; }

    void setType (string _type) { type = _type; }

    string getAccountNumber () const { return account_number; }

    void setAccountNumber (string _account_number) { account_number = _account_number; }

    string getShabaNumber () const { return shaba_number; }

    void setShabaNumber (string _shaba_number) { shaba_number = _shaba_number; }

    string getCardNumber () const { return card_number; }

    void setCardNumber (string _card_number) { card_number = _card_number; }

    string getCVV2 () const { return cvv2; }

    void setCVV2 (string _cvv2) { cvv2 = _cvv2; }

    string getFirstPassword () const { return firstpassword; }

    void setFirstPassword (string _firstpassword) { firstpassword = _firstpassword; }

    string getSecondPassword () const { return secondpassword; }

    void setSecondPassword (string _secondpassword) { secondpassword = _secondpassword; }

    double getBalance () const { return balance; }

    void setBalance (double _balance) { balance = _balance; }

    string getExpiryDate () const { return expiryDate; }
    
    void setExpiryDate (const string & date) { expiryDate = date; }
    
    void updateExpiryDate (int years_in_future) { expiryDate = generate_expiration_date (years_in_future); }
    
    string getDynamicPin() const { return dynamicpassword; }

    void setDynamicPin(const string& _dynamicpassword) const { dynamicpassword == _dynamicpassword; }

    const vector<pair<double, time_t>>& getTransfers() const { return transfers; }
 
    void setTransfers(const vector<pair<double, time_t>>& trans) { transfers = trans; }

    static string generate_card_number ()
    {
        return generate_random_number (12);
    }

    static string generate_account_number ()
    {
        return generate_random_number (7);
    }

    static string generate_shaba_number ()
    {
        return "IR" + generate_random_number (16);
    }

    static string generate_password (int length)
    {
        string password;
        for (int i = 0; i < length; ++i)
        {
            password += to_string (rand () % 10);
        }
        return password;
    }
    
    void add_transfer(double amount, time_t timestamp) {
    transfers.push_back(make_pair(amount, timestamp));
    }

    double check_transfer_time(time_t current_time) {
        double total = 0.0;
        for (const auto& transfer : transfers) {
            if (difftime(current_time, transfer.second) <= 86400) {
                total+= transfer.first;
            }
        }
        return total;
    }

    string generate_dynamic_pin(){
        stringstream ss;
        for (int i = 0; i < 8; ++i){
            ss << rand() % 10;
        }
        dynamicpassword = ss.str();
        return dynamicpassword;
    }

    bool is_dynamic_pin_valid(const string& password) {
        if (password == dynamicpassword) {
            dynamicpassword.clear();
            return true;
        }
        return false;
    }

    void save (ofstream & outFile)
    {
        outFile << account_number << " " << card_number << " " << shaba_number <<
                " " << type << " " << cvv2 << " " << expiryDate << " " << firstpassword <<
                " " << secondpassword << " " << balance << endl;
    }

    void load (ifstream & inFile)
    {
        inFile >> account_number >> card_number >> shaba_number >> type
               >> cvv2 >> expiryDate >> firstpassword >> secondpassword
               >> balance;
    }

};

class User
{
private:
    string name;
    string nationalID;
    string password;
    string username;
    int age;
    
public:
    User () {}
    
    User (string name, string nationalID, int age, string password,
          string username)
    {
        this->name = name;
        this->nationalID = nationalID;
        this->password = password;
        this->username = username;
        this->age = age;
    }

    void set_name (string _name) { name = _name; }

    string get_name () const { return name; }

    void set_nationalID (string ID) { nationalID = ID; }

    string get_nationalID () const { return nationalID; }

    void set_age (int _age) { age = _age; }

    int get_age () const { return age; }

    void setUsername (string _username) { username = _username; }

    void setPassword (string pass) { password = pass; }

    string get_password () const { return password; }

    string get_username () const { return username; }

    void save (ofstream & outFile)
    {
        outFile << name << " " << nationalID << " "
                << age << " " << username << " " << password << endl;
    }

    void load (ifstream & inFile)
    {
        inFile >> name >> nationalID >> age >> username >> password;
    }
};

template <typename T>
class Node {
    public :
    T data;
    Node* next;
    
    Node(T data) : data(data), next(nullptr) {}
};

template <typename T>
class LinkedList {
    private:
    
    Node<T>* head;
    Node<T>* tail;
    
    public:
    LinkedList() : head(nullptr), tail(nullptr) {}
    
    void add_to_list(T data) {
        Node<T>* newnode = new Node<T>(data);
        if (head == nullptr){
            head = newnode;
            tail = newnode;
        }
        else {
            tail -> next = newnode;
            tail = newnode;
        }
    }
    
    Node<T>* getHead() const {
        return head;
    }
};

void add_account() {
    int max_accounts = 5; 
    int num_accounts = 0; 

    User user;
    cout << "Enter name: ";
    string nameuser = " ";
    getline(cin, nameuser);
    user.set_name(nameuser);
    

    cout << "Enter national ID: ";
    string nationalcode = " ";
    getline(cin, nationalcode);
    user.set_nationalID(nationalcode);
    cin.ignore();

    cout << "Enter age: ";
    int userage ;
    cin >> userage;
    user.set_age(userage);
    cin.ignore();

    cout << "Enter username: ";
    string username_input;
    getline(cin, username_input);
    user.setUsername(username_input);

    cout << "Enter password: ";
    string password_input = " ";
    getline(cin, password_input);
    user.setPassword(password_input);

    while (num_accounts < max_accounts) {
        BankAccount account;
        cout << "Enter account type: ";
        string account_type = " ";
        getline(cin, account_type);
        account.setType(account_type);

        cout << "Enter first password of your account: ";
        string user_first_password_inp = " ";
                getline(cin, user_first_password_inp);
        account.setFirstPassword(user_first_password_inp);

        cout << "Do you want to have a second password? (Y/N): ";
        char answer;
        cin >> answer;
        cin.ignore();

        if (answer == 'Y' || answer == 'y') {
            cout << "Enter second password of your account: ";
            string user_second_password_inp = " ";
            getline(cin, user_second_password_inp);
            account.setSecondPassword(user_second_password_inp);
        }

        cout << "Enter initial balance: ";
        double userbalance = 0.0;
        cin >> userbalance;
        account.setBalance(userbalance);

        if (userbalance < 50.0) {
            cout << "Initial balance must be at least 50!" << endl;
            cout << "Account creation failed." << endl;
            return;
        }

        account.setAccountNumber(generate_random_number(12));
        account.setShabaNumber("IR" + generate_random_number(16));
        account.setCardNumber(generate_random_number(12));
        account.setCVV2(generate_random_number(3));
        account.setExpiryDate(generate_expiration_date(3));

        ofstream outFile("data.txt", ios::app);
        if (outFile.is_open()) {
            outFile << "User Information:" << endl;
            outFile << "Name: " << user.get_name() << endl;
            outFile << "National ID: " << user.get_nationalID() << endl;
            outFile << "Age: " << user.get_age() << endl;
            outFile << "Username: " << user.get_username() << endl;
            outFile << "Password: " << user.get_password() << endl;

            outFile << "Bank Account Information:" << endl;
            outFile << "Account Number: " << account.getAccountNumber() << endl;
            outFile << "Shaba Number: " << account.getShabaNumber() << endl;
            outFile << "Account Type: " << account.getType() << endl;
            outFile << "Card Number: " << account.getCardNumber() << endl;
            outFile << "CVV2: " << account.getCVV2() << endl;
            outFile << "Expiry Date: " << account.getExpiryDate() << endl;
            outFile << "Balance: " << account.getBalance() << endl;
            outFile << "First Password: " << account.getFirstPassword() << endl;

            if (!account.getSecondPassword().empty()) {
                outFile << "Second Password: " << account.getSecondPassword() << endl;
            }

            outFile << "----------------------------------------" << endl;
            outFile.close();
            cout << "Account added successfully!" << endl;
        } else {
            cout << "Unable to open file!" << endl;
        }

        num_accounts++;
        cout << "Do you want to add another bank account? (Y/N): ";
        char add_another;
        cin >> add_another;
        cin.ignore();

        if (add_another != 'Y' && add_another != 'y') {
            break;
        }
    }

    if (num_accounts >= max_accounts) {
        cout << "You have reached the maximum number of bank accounts!" << endl;
    }
}

void read_data_from_file(vector<User>& users, vector<BankAccount>& accounts) {
    ifstream inFile("data.txt");
    if (!inFile) {
        cerr << "Unable to open file data.txt";
        exit(1);
    }

    User user;
    BankAccount account;
    string line;
    while (getline(inFile, line)) {
        if (line.find("Name:") != string::npos) {
            string name = line.substr(line.find(":") + 2);
            user.set_name(name);

            getline(inFile, line); // National ID
            string nationalID = line.substr(line.find(":") + 2);
            user.set_nationalID(nationalID);

            getline(inFile, line); // Age
            int age = stoi(line.substr(line.find(":") + 2));
            user.set_age(age);

            getline(inFile, line); // Username
            string username = line.substr(line.find(":") + 2);
            user.setUsername(username);

            getline(inFile, line); // Password
            string password = line.substr(line.find(":") + 2);
            user.setPassword(password);
        } else if (line.find("Account Number:") != string::npos) {
            string account_number = line.substr(line.find(":") + 2);
            account.setAccountNumber(account_number);

            getline(inFile, line); // Shaba Number
            string shaba_number = line.substr(line.find(":") + 2);
            account.setShabaNumber(shaba_number);

            getline(inFile, line); // Account Type
            string type = line.substr(line.find(":") + 2);
            account.setType(type);

            getline(inFile, line); // Card Number
            string card_number = line.substr(line.find(":") + 2);
            account.setCardNumber(card_number);

            getline(inFile, line); // CVV2
            string cvv2 = line.substr(line.find(":") + 2);
            account.setCVV2(cvv2);

            getline(inFile, line); // Expiry Date
            string expiry_date = line.substr(line.find(":") + 2);
            account.setExpiryDate(expiry_date);

            getline(inFile, line); // Balance
            double balance = stod(line.substr(line.find(":") + 2));
            account.setBalance(balance);
            
            getline(inFile, line);
            string first_password = line.substr(line.find(":") + 2);
            account.setFirstPassword(first_password);

            getline(inFile, line); // Second Password
            if (line.find(":") != string::npos) {
                string second_password = line.substr(line.find(":") + 2);
                account.setSecondPassword(second_password);
            }

            users.push_back(user);
            accounts.push_back(account);

            getline(inFile, line); 
        }
    }

    inFile.close();
}


void save_data_to_file(const vector<User>& users, const vector<BankAccount>& accounts) {
    ofstream outFile("data.txt", ios::trunc);
    if (!outFile) {
        cerr << "Unable to open file data.txt";
        exit(1);
    }

    for (size_t i = 0; i < users.size(); ++i) {
        outFile << "User Information:" << endl;
        outFile << "Name: " << users[i].get_name() << endl;
        outFile << "National ID: " << users[i].get_nationalID() << endl;
        outFile << "Age: " << users[i].get_age() << endl;
        outFile << "Username: " << users[i].get_username() << endl;
        outFile << "Password: " << users[i].get_password() << endl;

        outFile << "Bank Account Information:" << endl;
        outFile << "Account Number: " << accounts[i].getAccountNumber() << endl;
        outFile << "Shaba Number: " << accounts[i].getShabaNumber() << endl;
        outFile << "Account Type: " << accounts[i].getType() << endl;
        outFile << "Card Number: " << accounts[i].getCardNumber() << endl;
        outFile << "CVV2: " << accounts[i].getCVV2() << endl;
        outFile << "Expiry Date: " << accounts[i].getExpiryDate() << endl;
        outFile << "Balance: " << accounts[i].getBalance() << endl;
        outFile << "First Password: " << accounts[i].getFirstPassword() << endl;
        
        if (!accounts[i].getSecondPassword().empty()) {
            outFile << "Second Password: " << accounts[i].getSecondPassword() << endl;
        }

        outFile << "----------------------------------------" << endl;
    }

    outFile.close();
}

void change_first_password(vector<User>& users, vector<BankAccount>& accounts){
    string username = " ", password = " ", current_first_password = " ", new_first_password = " ", cardnumber = " ";
    
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password to login: ";
    cin >> password;
    cout << "Enter your card number: ";
    cin >> cardnumber;
    cout << "Enter current first pasword: ";
    cin >> current_first_password;
    cout << "Enter new first password: ";
    cin >> new_first_password;
    
    int user_index = -1, account_index = -1;
    
    for (size_t i = 0; i < users.size(); ++i){
        if (users[i].get_username() == username && users[i].get_password() == password){
            user_index = i;
            break;
        }
    }
    
     if (user_index == -1) {
            cout << "Invalid username or password!" << endl;
            return;
        }
    
    for (size_t i = 0; i < accounts.size(); ++i){
        if (accounts[i].getCardNumber() == cardnumber && users[user_index].get_username() == username) {
            account_index = i;
            break;
        }
    }
        
        if (account_index == -1) {
            cout << "Card number is not correct!" << endl;
            return;
        }
        
        if (accounts[account_index].getFirstPassword() != current_first_password){
            cout << "Your current first password is not true!" << endl;
            return;
        }
        
        accounts[account_index].setFirstPassword(new_first_password);
    
    save_data_to_file(users, accounts);
    cout << "Changed successfully!" << endl;
}


void change_second_password(vector<User>& users, vector<BankAccount>& accounts){
    string username = " ", password = " ", current_second_password = " ", new_second_password = " ", cardnumber = " ";
    
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password to login: ";
    cin >> password;
    cout << "Enter your card number: ";
    cin >> cardnumber;
    cout << "Enter current first pasword: ";
    cin >> current_second_password;
    cout << "Enter new first password: ";
    cin >> new_second_password;
    
    int user_index = -1, account_index = -1;
    
    for (size_t i = 0; i < users.size(); ++i){
        if (users[i].get_username() == username && users[i].get_password() == password){
            user_index = i;
            break;
        }
    }
    
     if (user_index == -1) {
            cout << "Invalid username or password!" << endl;
            return;
        }
    
    for (size_t i = 0; i < accounts.size(); ++i){
        if (accounts[i].getCardNumber() == cardnumber && users[user_index].get_username() == username) {
            account_index = i;
            break;
        }
    }
        
        if (account_index == -1) {
            cout << "Card number is not correct!" << endl;
            return;
        }
        
        if (accounts[account_index].getSecondPassword() != current_second_password){
            cout << "Your current first password is not true!" << endl;
            return;
        }
        
        accounts[account_index].setSecondPassword(new_second_password);
    
    save_data_to_file(users, accounts);
    cout << "Changed successfully!" << endl;
}




void card_to_card(vector<User>& users, vector<BankAccount>& accounts) {
    string username, password, source_card, destination_card, second_password;
    double amount;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter your card number: ";
    cin >> source_card;
    cout << "Enter destination card number: ";
    cin >> destination_card;
    cout << "Enter amount to transfer: ";
    cin >> amount;
    cout << "Enter second password: ";
    cin >> second_password;

    int user_index = -1, source_index = -1, destination_index = -1;

    // Find the user and check password
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].get_username() == username && users[i].get_password() == password) {
            user_index = i;
            break;
        }
    }

    if (user_index == -1) {
        cout << "Invalid username or password!" << endl;
        return;
    }

    //Check card number
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getCardNumber() == source_card && users[user_index].get_username() == username) {
            source_index = i;
            break;
        }
    }

    if (source_index == -1) {
        cout << "Invalid source card number!" << endl;
        return;
    }
    
    if (accounts[source_index].getSecondPassword().empty() || accounts[source_index].getSecondPassword() != second_password) {
        cout << "Invalid second password or second password is not set!" << endl;
        return;
    }

    // Validate destination card
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getCardNumber() == destination_card) {
            destination_index = i;
            break;
        }
    }

    if (destination_index == -1) {
        cout << "Invalid destination card number!" << endl;
        return;
    }
    
    //calculate number of card to card action in 24 h
    
    time_t current_time = time(0);
    double tranferred_amount_last_24h = accounts[source_index].check_transfer_time(current_time);
    
    if (tranferred_amount_last_24h + amount > 6000000) {
        cout << "Transfer limit exceeded!" << endl;
        return;
    }
    
    if (amount < 100000) {
        cout << "Enter second password: ";
        cin >> second_password;
        
        if (accounts[source_index].getSecondPassword()!= second_password) {
            cout << "Invalid second password!" << endl;
            return;
        }
    }
    
    //Max and Min of transfer in per action

    else if (amount >= 100000 && amount <= 3000000) {
        string dynamic_password = accounts[source_index].generate_dynamic_pin();
        cout << "Generate dynamic second password: " << dynamic_password << endl;
        cout << "Enter dynamic second password: ";
        cin >> dynamic_password;
        
        if (!accounts[source_index].is_dynamic_pin_valid(dynamic_password)) {
            cout << "Invalid dynamic second password: " << endl;
            return;
        }
    }
    
    else {
        cout << "Transfer amount exceds the limit for dynamic second password!" << endl;
        return;
    }
    
    
    
    //Show the name of reciever 
    cout << "Recipient Name: " << users[destination_index].get_name() << endl;
    
    //Do the formula of amount
    double fee = amount * 0.01;
    if (accounts[source_index].getBalance() < amount + fee) {
        cout << "Insufficient balance!" << endl;
        return;
    }

    accounts[source_index].setBalance(accounts[source_index].getBalance() - (amount + fee));
    accounts[destination_index].setBalance(accounts[destination_index].getBalance() + amount);

    // Save new data to file
    save_data_to_file(users, accounts);

    cout << "Transfer successful!" << endl;
}


void view_balance(const string& inp_username_to_check, const string& inp_password_to_check, const string& inp_acc_number_to_check){
    ifstream inFile("data.txt");
    if (!inFile.is_open()) {
        cout << "Unable to open file!" << endl;
        return;
    }
    
    string line;
    bool user_found = false, account_found = false;
    string saved_username, saved_password, saved_account_number;
    double balance;
    
    while(getline(inFile, line)) {
        if (line.find("Bank Account Information:") != string::npos) {
            if (user_found && account_found ) {
                cout << "Balance: " << balance << endl;
                return;
            }
            continue;
        }
        
        if (line.find("Username:") != string::npos) {
            saved_username = line.substr(line.find(":") + 2);
            continue;
        }
        
         if (line.find("Password:") != string::npos) {
            saved_password = line.substr(line.find(":") + 2);
            continue;
        }
        
         if (line.find("Account Number:") != string::npos) {
            saved_account_number = line.substr(line.find(":") + 2);
            continue;
        }
        
         if (line.find("Balance:") != string::npos) {
            balance = stod( line.substr(line.find(":") + 2));
            continue;
        }
        
        if (saved_username == inp_username_to_check && saved_password == inp_password_to_check && saved_account_number == inp_acc_number_to_check) {
            user_found = true;
            account_found = true;
        }
    }
    
    inFile.close();
    
    if(!user_found || !account_found){
        cout << "No matching account found!" << endl;
    }
    
}

//~~~~~~~~~~~~~~~~~For Link List~~~~~~~~~~~~~~~~~~~~

void read_data_from_file(LinkedList<User>& users, LinkedList<BankAccount>& accounts) {
    ifstream inFile("data.txt");
    if (!inFile) {
        cerr << "Unable to open file data.txt";
        exit(1);
    }

    User user;
    BankAccount account;
    string line;
    while (getline(inFile, line)) {
        if (line.find("Name:") != string::npos) {
            string name = line.substr(line.find(":") + 2);
            user.set_name(name);

            getline(inFile, line); // National ID
            string nationalID = line.substr(line.find(":") + 2);

            getline(inFile, line); // Age
            int age = stoi(line.substr(line.find(":") + 2));

            getline(inFile, line); // Username
            string username = line.substr(line.find(":") + 2);
            user.setUsername(username);

            getline(inFile, line); // Password
            string password = line.substr(line.find(":") + 2);
            user.setPassword(password);
        } else if (line.find("Account Number:") != string::npos) {
            string account_number = line.substr(line.find(":") + 2);
            account.setAccountNumber(account_number);

            getline(inFile, line); // Shaba Number
            string shaba_number = line.substr(line.find(":") + 2);
            account.setShabaNumber(shaba_number);

            getline(inFile, line); // Account Type
            string type = line.substr(line.find(":") + 2);
            account.setType(type);

            getline(inFile, line); // Card Number
            string card_number = line.substr(line.find(":") + 2);
            account.setCardNumber(card_number);

            getline(inFile, line); // CVV2
            string cvv2 = line.substr(line.find(":") + 2);
            account.setCVV2(cvv2);

            getline(inFile, line); // Expiry Date
            string expiry_date = line.substr(line.find(":") + 2);
            account.setExpiryDate(expiry_date);

            getline(inFile, line); // Balance
            double balance = stod(line.substr(line.find(":") + 2));
            account.setBalance(balance);

            getline(inFile, line); // First Password
            if (line.find(":") != string::npos) {
                string first_password = line.substr(line.find(":") + 2);
                account.setFirstPassword(first_password);
            }
            
            getline(inFile, line); // second Password
            if (line.find(":") != string::npos) {
                string second_password = line.substr(line.find(":") + 2);
                account.setSecondPassword(second_password);
            }

            users.add_to_list(user);
            accounts.add_to_list(account);

            getline(inFile, line);
        }
    }

    inFile.close();
}


void save_data_to_file(const LinkedList<User>& users, const LinkedList<BankAccount>& accounts) {
    ofstream outFile("data.txt", ios::trunc);
    if (!outFile) {
        cerr << "Unable to open file data.txt";
        exit(1);
    }

    Node<User>* userNode = users.getHead();
    Node<BankAccount>* accountNode = accounts.getHead();

    while (userNode != nullptr && accountNode != nullptr) {
        outFile << "User Information:" << endl;
        outFile << "Name: " << userNode->data.get_name() << endl;
        outFile << "Username: " << userNode->data.get_username() << endl;
        outFile << "Password: " << userNode->data.get_password() << endl;

        outFile << "Bank Account Information:" << endl;
        outFile << "Account Number: " << accountNode->data.getAccountNumber() << endl;
        outFile << "Shaba Number: " << accountNode->data.getShabaNumber() << endl;
        outFile << "Account Type: " << accountNode->data.getType() << endl;
        outFile << "Card Number: " << accountNode->data.getCardNumber() << endl;
        outFile << "CVV2: " << accountNode->data.getCVV2() << endl;
        outFile << "Expiry Date: " << accountNode->data.getExpiryDate() << endl;
        outFile << "Balance: " << accountNode->data.getBalance() << endl;
        outFile << "First Password: " << accountNode->data.getFirstPassword() << endl;
        outFile << "Second Password: " << accountNode->data.getSecondPassword() << endl;

        userNode = userNode->next;
        accountNode = accountNode->next;

        outFile << "------------------------" << endl;
    }

    outFile.close();
}

void change_first_password(LinkedList<User>& users, LinkedList<BankAccount>& accounts) {
    string username, password, current_first_password, new_first_password, cardnumber;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password to login: ";
    cin >> password;
    cout << "Enter your card number: ";
    cin >> cardnumber;
    cout << "Enter current first password: ";
    cin >> current_first_password;
    cout << "Enter new first password: ";
    cin >> new_first_password;

    Node<User>* userNode = users.getHead();
    Node<BankAccount>* accountNode = accounts.getHead();

    bool userFound = false;
    bool accountFound = false;

    while (userNode != nullptr) {
        if (userNode->data.get_username() == username && userNode->data.get_password() == password) {
            userFound = true;
            break;
        }
        userNode = userNode->next;
    }

    if (!userFound) {
        cout << "Invalid username or password!" << endl;
        return;
    }

    while (accountNode != nullptr) {
        if (accountNode->data.getCardNumber() == cardnumber && userNode->data.get_username() == username) {
            accountFound = true;
            break;
        }
        accountNode = accountNode->next;
    }

    if (!accountFound) {
        cout << "Card number is not correct!" << endl;
        return;
    }

    if (accountNode->data.getFirstPassword() != current_first_password) {
        cout << "Your current first password is not true!" << endl;
        return;
    }

    accountNode->data.setFirstPassword(new_first_password);
    save_data_to_file(users, accounts);
    cout << "Password changed successfully!" << endl;
}

int main ()
{
    srand(time(0));
    int choice = 0;

    cout << "Welcome to the Banking System!" << endl;
    cout << "1. Add Account" << endl;
    cout << "2. Change First Password" << endl;
    cout << "3. Change Second Password" << endl;
    cout << "4. Card to Card" << endl;
    cout << "5. View Balance" << endl;
    cout << "Enter your choice (1-5): ";
    cin >> choice;

    switch (choice)
    {
        case 1:
            add_account ();
            break;
            
        case 2:{
            LinkedList<User> users;
            LinkedList<BankAccount> accounts;
            read_data_from_file(users, accounts);
            change_first_password(users, accounts);
            break;
        }
        
        case 3:{
            vector<User> users;
            vector<BankAccount> accounts;
            read_data_from_file(users, accounts);
            change_first_password(users, accounts);
            break;
        }
        
        
        case 4:{
            
            vector<User> users;
            vector<BankAccount> accounts;
            
            read_data_from_file(users, accounts);
            card_to_card(users, accounts);
        }

        case 5:{
        string inp_username_to_check, inp_password_to_check, inp_acc_number_to_check;
        cout << "Enter your username: ";
        cin >> inp_username_to_check;
        
        cout << "Enter your password: ";
        cin >> inp_password_to_check;
        
        cout << "Enter your account number: ";
        cin >> inp_acc_number_to_check;
        
            view_balance(inp_username_to_check, inp_password_to_check, inp_acc_number_to_check);
        break;
        }

        default:
            cout << "Invalid choice! Please enter a number between 1 and 5." <<
                 endl;
            break;
    }

    return 0;
}