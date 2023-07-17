#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <map>
#include <iomanip>

class Account {
public:
    std::string username;
    std::string password;
    std::string accountType;

    Account(const std::string& username, const std::string& password, const std::string& accountType)
        : username(username), password(password), accountType(accountType) {}

    std::string getAccountType() const {
        return accountType;
    }
};


class AccountManager {
private:
    std::vector<Account> accounts;

public:
    AccountManager() {}

    void loadAccountCredentials(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string username, password, accountType;
            if (std::getline(iss, username, ',') && std::getline(iss, password, ',') && std::getline(iss, accountType, ',')) {
                accounts.push_back(Account(username, password, accountType));
            }
        }

        file.close();
    }

    bool validateLogin(const std::string& username, const std::string& password, const std::string& accountType) {
        for (const auto& account : accounts) {
            if (account.username == username && account.password == password && account.accountType == accountType) {
                return true;
            }
        }
        return false;
    }

     const std::vector<Account>& getAccounts() const {
        return accounts;
    }
};

class StackNode {
public:
    std::string data;
    StackNode* next;

    StackNode(const std::string& data) : data(data), next(nullptr) {}
};

class Stack {
private:
    StackNode* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const std::string& data) {
        StackNode* newNode = new StackNode(data);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            return;
        }

        StackNode* temp = top;
        top = top->next;
        delete temp;
    }

    std::string peek() const {
        if (isEmpty()) {
            return "";
        }

        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }
};

class EmployeeList {
private:
    struct Employee {
        int id;
        std::string name;
        std::string bday;
        std::string gender;
        int age;
        std::string civil;
        std::string position;
        std::string status;
        std::string phone;
        std::string email;
        std::string address;
        std::string bank;
        double salary;
        Employee* next;

        Employee(int id, const std::string& name, const std::string& bday, const std::string& gender, int age, const std::string& civil, const std::string& position, const std::string& status, const std::string& phone, const std::string& email, const std::string& address, const std::string& bank, double salary)
            : id(id), name(name), bday(bday), gender(gender), age(age), civil(civil), position(position), status(status), phone(phone), email(email), address(address), bank(bank), salary(salary), next(nullptr) {}
    };
    std::string currentAccountType;
    Employee* head;
    Employee* tail;
    int nextId;

    Stack loginStack;
    AccountManager accountManager;
     std::map<std::string, double> positions;

public:
    EmployeeList() : head(nullptr), tail(nullptr), nextId(1) {
        accountManager.loadAccountCredentials("credentials.txt"); 
        initializePositions();
    }

    void initializePositions() {
        positions["Software Engineer"] = 50000.0;
        positions["Data Scientist"] = 60000.0;
        positions["Network Administrator"] = 40000.0;
        positions["UX Designer"] = 45000.0;
        positions["Database Administrator"] = 45000.0;
        positions["Cybersecurity Analyst"] = 55000.0;
        positions["Web Developer"] = 45000.0;
        positions["IT Manager"] = 70000.0;
        positions["Product Manager"] = 65000.0;
        positions["Quality Assurance Engineer"] = 45000.0;
    }

    int getValidIntegerInput(std::istream& inputStream) {
        while (true) {
            std::string input;
            std::getline(inputStream, input);

            try {
                size_t pos;
                int value = std::stoi(input, &pos);
                if (pos == input.length()) {
                    return value;
                }
            } catch (const std::exception& e) {
            }
            std::cout << "Invalid input, Enter Again: " << std::endl;
        }
    }

    double getValidDoubleInput(std::istream& inputStream) {
        while (true) {
            std::string input;
            std::getline(inputStream, input);

            try {
                size_t pos;
                double value = std::stod(input, &pos);
                if (pos == input.length()) {
                    return value;
                }
            } catch (const std::exception& e) {
            }
            std::cout << "Invalid input. Enter again:" << std::endl;
        }
    }

    bool checkList(){
        if (!hasEmployees()) {
            std::cout << "The employee list is empty." << std::endl;
            system("PAUSE");
            return false;
        }
        else{
            return true;
        }
    }
    
    bool hasEmployees() const {
        return head != nullptr;
    }

    bool validateLogin(const std::string& username, const std::string& password, const std::string& accountType) {
        return accountManager.validateLogin(username, password, accountType);
    }

    void login() {
        std::string username, password;
        std::cout << "LOG IN" << std::endl;
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        const std::vector<Account>& accounts = accountManager.getAccounts();
        for (const auto& account : accounts) {
            if (account.username == username && account.password == password) {
                std::cout << "Login successful!" << std::endl;
                currentAccountType = account.getAccountType();
                loginStack.push(username);
                return;
            }
        }

        std::cout << "Invalid username or password. Login failed." << std::endl;
    }



    bool isLoggedIn() {
        return !loginStack.isEmpty();
    }

    void logout() {
        if (isLoggedIn()) {
            std::cout << "Logging out user: " << loginStack.peek() << std::endl;
            loginStack.pop();
        } else {
            std::cout << "No user logged in." << std::endl;
        }
    }

    void addEmployee(const std::string& name, const std::string& bday, const std::string& gender, int age, const std::string& civil, const std::string& position, const std::string& status, const std::string& phone, const std::string& email, const std::string& address, const std::string& bank) {
        double salary;
        if(status != "Full Time"){
            salary = 0;
        }
        else{
            if (positions.find(position) == positions.end()) {
            std::cout << "Invalid position. Employee not added." << std::endl;
            return;
        }

        salary = positions[position];
        }
        
        
        Employee* newEmployee = new Employee(nextId, name, bday, gender, age, civil, position, status, phone, email, address, bank, salary);
        nextId++;

        if (head == nullptr) {
            head = newEmployee;
            tail = newEmployee;
        } else {
            tail->next = newEmployee;
            tail = newEmployee;
        }
    }

    void deleteEmployee(int id) {
        system("CLS");
        if (head == nullptr) {
            std::cout << "Employee not found!" << std::endl;
            return;
        }

        if (head->id == id) {
            Employee* temp = head;
            head = head->next;
            delete temp;
            std::cout << "Employee deleted successfully." << std::endl;
            return;
        }

        Employee* current = head;
        while (current->next != nullptr) {
            if (current->next->id == id) {
                Employee* temp = current->next;
                current->next = current->next->next;
                delete temp;
                std::cout << "Employee deleted successfully." << std::endl;
                return;
            }
            current = current->next;
        }

        std::cout << "Employee not found!" << std::endl;
    }

    void displayEmployees(){
        char chh;
        int id;
        
        if(!checkList()){
            return;
        }
        do{
        system("CLS");
        Employee* current = head;
        std::cout << "Current Employees" << std::endl;
        std::cout << "ID\t\tName" << std::endl;
        while (current != nullptr) {
            std::cout << current->id << "\t\t" << current->name << std::endl;
            current = current->next;
        }

        std::cout << std::endl << std::endl;
        std::cout << "[A] Display Employee Details" << std::endl;
        std::cout << "[B] Exit" << std::endl;

        std::cin >> chh;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("CLS");
            switch(toupper(chh)){
                case 'A':{
                    std::cout << "Enter Employee ID: ";
                    id = getValidIntegerInput(std::cin);
                    system("CLS");
                    searchEmployee(id);
                    system("pause");
                    break;
                }
                case 'B':{
                return;
                break;
                }
                default:{
                    std::cout << "Invalid Choice" << std::endl;
                    system("PAUSE");
                }
            }
            system("CLS");
        }while(toupper(chh) != 'B');
    }

    void searchEmployee(int id) const {
        system("CLS");
        Employee* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->id == id) {
                std::cout << "Employee Information:" << std::endl << std::endl;
                std::cout << "ID: " << current->id << std::endl << std::endl;
                std::cout << "Name: " << current->name << std::endl << std::endl;
                std::cout << "Birthday: " << current->bday << std::endl << std::endl;
                std::cout << "Gender: " << current->gender << std::endl << std::endl;
                std::cout << "Age: " << current->age << std::endl << std::endl;
                std::cout << "Civil Status: " << current->civil << std::endl << std::endl;
                std::cout << "Phone Number: " << current->phone << std::endl << std::endl;
                std::cout << "Email Address: " << current->email << std::endl << std::endl;
                std::cout << "Address: " << current->address << std::endl << std::endl;
                std::cout << "Bank Information: " << current->bank << std::endl << std::endl;
                std::cout << "Position: " << current->position << std::endl << std::endl;
                std::cout << "Employment Status: " << current->status << std::endl << std::endl;

                found = true;
                break;
            }
            current = current->next;
        }

        if (!found) {
            std::cout << "Employee not found!" << std::endl;
        }
    }

    void editEmployee(int id) {
        system("CLS");
        Employee* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->id == id) {
                std::cout << "Employee Found!" << std::endl;
                std::cout << "Enter new employee details (leave blank to retain existing information):" << std::endl;

                std::string name;
                std::cout << "Name: ";
                std::getline(std::cin, name);
                if (!name.empty()) {
                    current->name = name;
                }

                std::string bday;
                std::cout << "Birthday: ";
                std::getline(std::cin, bday);
                if (!bday.empty()) {
                    current->bday = bday;
                }

                std::string gender;
                std::cout << "Gender: ";
                std::getline(std::cin, gender);
                if (!gender.empty()) {
                    current->gender = gender;
                }

                std::string ageStr;
                std::cout << "Age: ";
                std::getline(std::cin, ageStr);
                if (!ageStr.empty()) {
                    try {
                        int age = std::stoi(ageStr);
                        current->age = age;
                    } catch (const std::exception& e) {
                        std::cout << "Invalid age format. Age not updated." << std::endl;
                    }
                }

                std::string civil;
                std::cout << "Civil Status: ";
                std::getline(std::cin, civil);
                if (!civil.empty()) {
                    current->civil = civil;
                }

                std::string position;
                std::cout << "Position: ";
                std::getline(std::cin, position);
                if (!position.empty()) {
                    if (positions.find(position) == positions.end()) {
                        std::cout << "Invalid position. Position not updated." << std::endl;
                    } else {
                        current->position = position;
                        current->salary = positions[position];
                    }
                }

                std::string status;
                std::cout << "Employment Status: ";
                while (status != "Full Time" && status != "Part Time") {
                        std::cout << "Employment Status (Full Time or Part Time): " << std::endl;
                        std::getline(std::cin, status);
                        if (status != "Full Time" && status != "Part Time") {
                            std::cout << "Please enter either 'Full Time' or 'Part Time'";
                        }
                    }
                if (!status.empty()) {
                    current->status = status;
                }

                std::string phone;
                std::cout << "Phone Number: ";
                std::getline(std::cin, phone);
                if (!phone.empty()) {
                    current->phone = phone;
                }

                std::string email;
                std::cout << "Email Address: ";
                std::getline(std::cin, email);
                if (!email.empty()) {
                    current->email = email;
                }

                std::string address;
                std::cout << "Address: ";
                std::getline(std::cin, address);
                if (!address.empty()) {
                    current->address = address;
                }

                std::string bank;
                std::cout << "Bank Account Number: ";
                std::getline(std::cin, bank);
                if (!bank.empty()) {
                    current->bank = bank;
                }

                found = true;
                break;
            }
            current = current->next;
        }

        if (!found) {
            std::cout << "Employee not found!" << std::endl;
        }
    }

    void updateSalary(int id, double newSalary) {
        Employee* current = head;
        while (current != nullptr) {
            if (current->id == id) {
                current->salary = newSalary;
                std::cout << "Salary updated successfully." << std::endl;
                return;
            }
            current = current->next;
        }

        std::cout << "Employee not found!" << std::endl;
    }

    void displaySalary(int id) const {
        Employee* current = head;
        bool found = false;
        int hours;
        int rate;

        while (current != nullptr) {
            if (current->id == id) {
                double payroll;
                if (current->status == "Full Time") {
                    payroll = current->salary;
                }
                else if(current->status == "Part Time"){
                    std::cout << "Enter Hours Worked: "  << std::endl;
                    std::cin >> hours;
                    std::cout << "Enter Hourly Rate: " << std::endl;
                    std::cin >> rate;
                    payroll = rate * hours;
                }
                double SSS = payroll * 0.025;
                double PhilHealth = payroll * 0.015;
                double PagIbig = payroll * 0.01;
                double deductions = SSS + PhilHealth + PagIbig;
                double taxableSalary = payroll - deductions;
                double tax;
                if (payroll < 10000) {
                    tax = taxableSalary * 0.05;
                } else if (taxableSalary < 30000) {
                    tax = 500 + ((taxableSalary - 10000) * 0.1);
                } else if (taxableSalary < 70000) {
                    tax = 2500 + ((taxableSalary - 30000) * 0.15);
                } else if (taxableSalary < 140000) {
                    tax = 8500 + ((taxableSalary - 70000) * 0.20);
                } else if (taxableSalary < 250000) {
                    tax = 22500 + ((taxableSalary - 140000) * 0.25);
                } else if (taxableSalary < 500000) {
                    tax = 50000 + ((taxableSalary - 250000) * 0.30);
                } else if (taxableSalary > 500000) {
                    tax = 125000 + ((taxableSalary - 500000) * 0.32);
                }

                double netSalary = taxableSalary - tax;
                std::cout << "Payroll for Employee ID " << id << ":" << std::endl;
                std::cout << "Employee: " << current->name << std::endl;
                std::cout << "Gross Salary: " << std::fixed << std::setprecision(2) << payroll << std::endl;
                std::cout << "Deductions:" << std::fixed << std::setprecision(2) << std::endl;
                std::cout << "\tSSS: " << std::fixed << std::setprecision(2) << SSS << std::endl;
                std::cout << "\tPhilHealth: " << std::fixed << std::setprecision(2) << PhilHealth << std::endl;
                std::cout << "\tPagIbig: " << std::fixed << std::setprecision(2) << PagIbig << std::endl;
                std::cout << "Total Deductions: " << std::fixed << std::setprecision(2) << deductions << std::endl;
                std::cout << "Taxable Salary: " << std::fixed << std::setprecision(2) << taxableSalary << std::endl;
                std::cout << "Tax: " << std::fixed << std::setprecision(2) << tax << std::endl;
                std::cout << "Net Salary: " << std::fixed << std::setprecision(2) << netSalary << std::endl;

                found = true;
                break;
            }
            current = current->next;
        }

        if (!found) {
            std::cout << "Employee not found!" << std::endl;
        }
        system("PAUSE");
        system("CLS");
    }

    void manageEmployee() {
        if (currentAccountType != "HR") {
            std::cout << "Access denied. Only HR accounts can manage employees." << std::endl;
            system("PAUSE");
            return;
        }
        char ch;
        int id;
        do {
            system("CLS");
            std::cout << "Manage Employees" << std::endl << std::endl;
            std::cout << "[A] Add Employee" << std::endl;
            std::cout << "[B] Edit Employee Information" << std::endl;
            std::cout << "[C] Remove Employee" << std::endl;
            std::cout << "[D] View Employees" << std::endl;
            std::cout << "[E] Back" << std::endl << std::endl;
            std::cin >> ch;

            switch (toupper(ch)) {
                case 'A': {
                    system("CLS");
                    std::cout << "Employee Information Form" << std::endl;
                    std::cin.ignore();
                    std::string name;
                    std::string bday;
                    std::string gender;
                    std::string Input;
                    int age;
                    std::string civil;
                    std::string position;
                    std::string status;
                    std::string phone;
                    std::string email;
                    std::string address;
                    std::string bank;
                    double salary;
                    int daysOfWork = 0;
                    int hoursOfWork = 0;

                    std::cout << "Name: " << std::endl;
                    std::getline(std::cin, name);
                    std::cout << "Birthday: " << std::endl;
                    std::getline(std::cin, bday);
                    std::cout << "Gender: " << std::endl;
                    std::getline(std::cin, gender);
                    std::cout << "Age: " << std::endl;
                    age = getValidIntegerInput(std::cin);
                    std::cout << "Civil Status: " << std::endl;
                    std::getline(std::cin, civil);

                    std::cout << "Phone Number: " << std::endl;
                    std::getline(std::cin, phone);
                    std::cout << "Email Address: " << std::endl;
                    std::getline(std::cin, email);
                    std::cout << "Address: " << std::endl;
                    std::getline(std::cin, address);
                    std::cout << "Bank Information: " << std::endl;
                    std::getline(std::cin, bank);

                    std::cout << "Position: " << std::endl;
                    std::getline(std::cin, position);

                    while (status != "Full Time" && status != "Part Time") {
                        std::cout << "Employment Status (Full Time or Part Time): " << std::endl;
                        std::getline(std::cin, status);
                        if (status != "Full Time" && status != "Part Time") {
                            std::cout << "Please enter either 'Full Time' or 'Part Time'";
                        }
                    }


                    addEmployee(name, bday, gender, age, civil, position, status, phone, email, address, bank);
                    std::cout << "Employee Added Successfully!" << std::endl;
                    system("PAUSE");
                    break;
                }
                case 'B': {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if(!checkList()){
                        break;
                    };
                    system("CLS");
                    std:: cout << "Enter ID: " << std::endl;
                    id = getValidIntegerInput(std::cin);
                    editEmployee(id);
                    std::cout << std::endl << std::endl;
                    system("PAUSE");
                    break;
                }
                case 'C': {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if(!checkList()){
                        break;
                    };
                    system("CLS");
                    std:: cout << "Enter ID: " << std::endl;
                    id = getValidIntegerInput(std::cin);
                    deleteEmployee(id);
                    system("PAUSE");
                    break;
                }
                case 'D':{
                    displayEmployees();
                    break;
                }
                case 'E':
                    return;
                    break;
                default:
                    std::cout << "Invalid option selected!" << std::endl;
                    system("PAUSE");
            }
            system("CLS");
        } while (toupper(ch) != 'D');
    }

    void managePayroll() {
        if (currentAccountType != "Payroll") {
            std::cout << "Access denied. Only payroll accounts can manage payroll." << std::endl;
            system("PAUSE");
            return;
        }
        char ch;
        int id;
        do {
            system("CLS");
            std::cout << "Manage Payroll" << std::endl << std::endl;
            std::cout << "[A] Display Employee Salary" << std::endl;
            std::cout << "[B] Update Employee Salary" << std::endl;
            std::cout << "[C] Back" << std::endl << std::endl;
            std::cin >> ch;

            switch (toupper(ch)) {
                case 'A': {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if(!checkList()){
                        break;
                    };
                    system("CLS");
                    std:: cout << "Enter ID: " << std::endl;
                    id = getValidIntegerInput(std::cin);
                    displaySalary(id);
                    break;
                }
                case 'B': {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if(!checkList()){
                        break;
                    };
                    system("CLS");
                    std:: cout << "Enter ID: " << std::endl;
                    id = getValidIntegerInput(std::cin);
                    double newSalary;
                    std::cout << "Enter New Salary: " << std::endl;
                    newSalary = getValidIntegerInput(std::cin);
                    updateSalary(id, newSalary);
                    break;
                }
                case 'C':
                    return;
                    break;
                default:
                    std::cout << "Invalid option selected!" << std::endl;
                    system("PAUSE");
                    break;
            }
            system("CLS");
        } while (toupper(ch) != 'C');
    }

};

int main() {
    system("CLS");
    char choice;
    EmployeeList employeeList;

    do {
        while(!employeeList.isLoggedIn()){
        employeeList.login();
        system("PAUSE");
        system("CLS");
    }
        system("CLS");
        std::cout << "Tech Company" << std::endl << std::endl;
        std::cout << "Menu" << std::endl << std::endl;
        std::cout << "[A] Human Resources" << std::endl;
        std::cout << "[B] Payroll" << std::endl;
        std::cout << "[C] Logout" << std::endl;
        std::cout << "[D] Exit" << std::endl << std::endl;
        std::cin >> choice;

        switch (toupper(choice)) {
            case 'A':
                employeeList.manageEmployee();
                break;
            case 'B':
                employeeList.managePayroll();
                break;
            case 'C':
                system("CLS");
                employeeList.logout();       
                break;
            case 'D':
                system("CLS");
                std::cout << "Shutting down..." << std::endl;
                break;
            default:
                std::cout << "Invalid option selected!" << std::endl;
                system("PAUSE");
                break;
        }
        system("CLS");
    } while (toupper(choice) != 'D');

    return 0;
}
