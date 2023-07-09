#include <iostream>
#include <string>

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
        std::string department;
        std::string status;
        std::string phone;
        std::string email;
        std::string address;
        std::string bank;
        double salary;
        int daysOfWork;
        int hoursOfWork;
        Employee* next;

        Employee(int id, const std::string& name, const std::string& bday, const std::string& gender, int age, const std::string& civil, const std::string& position, const std::string& department, const std::string& status, const std::string& phone, const std::string& email, const std::string& address, const std::string& bank, double salary, int daysOfWork = 0, int hoursOfWork = 0)
            : id(id), name(name), bday(bday), gender(gender), age(age), civil(civil), position(position), department(department), status(status), phone(phone), email(email), address(address), bank(bank), salary(salary), daysOfWork(daysOfWork), hoursOfWork(hoursOfWork), next(nullptr) {}
    };

    Employee* head;
    Employee* tail;
    int nextId;

    Stack loginStack;

public:
    EmployeeList() : head(nullptr), tail(nullptr), nextId(1) {}

    bool hasEmployees() const {
        return head != nullptr;
    }

    bool validateLogin(const std::string& username, const std::string& password) {
        return (username == "admin" && password == "password");
    }

    void login() {
        std::string username, password;
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        if (validateLogin(username, password)) {
            std::cout << "Login successful!" << std::endl;
            loginStack.push(username);
        } else {
            std::cout << "Invalid username or password. Login failed." << std::endl;
        }
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

    void addEmployee(const std::string& name, const std::string& bday, const std::string& gender, int age, const std::string& civil, const std::string& position, const std::string& department, const std::string& status, const std::string& phone, const std::string& email, const std::string& address, const std::string& bank, double salary, int daysOfWork = 0, int hoursOfWork = 0) {
        Employee* newEmployee = new Employee(nextId, name, bday, gender, age, civil, position, department, status, phone, email, address, bank, salary, daysOfWork, hoursOfWork);
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

    void displayEmployees() const {
        char chh;
        int idd;

        if (!hasEmployees()) {
            std::cout << "The employee list is empty." << std::endl;
            return;
        }

        Employee* current = head;
        while (current != nullptr) {
            std::cout << current->id << ") Name: " << current->name << std::endl;
            current = current->next;
        }

        std::cout << std::endl << std::endl;
        do{
        std::cout << "[A] Display Employee Details" << std::endl;
        std::cout << "[B] Exit" << std::endl;

        std::cin >> chh;
            switch(toupper(chh)){
                case 'A':{
                    std::cout << "Enter Employee ID" << std::endl;
                    std::cin >> idd;
                    searchEmployee(idd);
                    break;
                }
                case 'B':{
                break;
                }
            }
        }while(toupper(chh) != 'B');
    }

    void searchEmployee(int id) const {
        Employee* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->id == id) {
                std::cout << "Employee Information:" << std::endl;
                std::cout << "ID: " << current->id << std::endl;
                std::cout << "Name: " << current->name << std::endl;
                std::cout << "Birthday: " << current->bday << std::endl;
                std::cout << "Gender: " << current->gender << std::endl;
                std::cout << "Age: " << current->age << std::endl;
                std::cout << "Civil Status: " << current->civil << std::endl;
                std::cout << "Position: " << current->position << std::endl;
                std::cout << "Department: " << current->department << std::endl;
                std::cout << "Employment Status: " << current->status << std::endl;
                std::cout << "Phone Number: " << current->phone << std::endl;
                std::cout << "Email Address: " << current->email << std::endl;
                std::cout << "Address: " << current->address << std::endl;
                std::cout << "Bank Information: " << current->bank << std::endl;
                if (current->status == "PART TIME") {
                    std::cout << "Days of Work: " << current->daysOfWork << std::endl;
                    std::cout << "Hours of Work: " << current->hoursOfWork << std::endl;
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

    void editEmployee(int id) {
        if (!hasEmployees()) {
            std::cout << "The employee list is empty." << std::endl;
            return;
        }

        Employee* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->id == id) {
                std::cout << "Employee Found!" << std::endl;
                std::cout << "Enter new employee details (leave blank to retain existing information):" << std::endl;

                std::string name;
                std::cout << "Name: ";
                std::cin.ignore();
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
                    current->position = position;
                }

                std::string department;
                std::cout << "Department: ";
                std::getline(std::cin, department);
                if (!department.empty()) {
                    current->department = department;
                }

                std::string status;
                std::cout << "Employment Status: ";
                std::getline(std::cin, status);
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

                if (current->status == "PART TIME") {
                    std::cout << "Days of Work: ";
                    std::cin >> current->daysOfWork;
                    std::cout << "Hours of Work: ";
                    std::cin >> current->hoursOfWork;
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

        while (current != nullptr) {
            if (current->id == id) {
                double payroll;
                if (current->status == "FULL TIME") {
                    payroll = current->salary;
                } else if (current->status == "PART TIME") {
                    payroll = current->salary * current->daysOfWork * current->hoursOfWork;
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
                std::cout << "Gross Salary: " << payroll << std::endl;
                std::cout << "Deductions:" << std::endl;
                std::cout << "\tSSS: " << SSS << std::endl;
                std::cout << "\tPhilHealth: " << PhilHealth << std::endl;
                std::cout << "\tPagIbig: " << PagIbig << std::endl;
                std::cout << "Total Deductions: " << deductions << std::endl;
                std::cout << "Taxable Salary: " << taxableSalary << std::endl;
                std::cout << "Tax: " << tax << std::endl;
                std::cout << "Net Salary: " << netSalary << std::endl;

                found = true;
                break;
            }
            current = current->next;
        }

        if (!found) {
            std::cout << "Employee not found!" << std::endl;
        }
    }

    void manageEmployee() {
        if (!isLoggedIn()) {
            std::cout << "Please login to access employee management." << std::endl;
            login();
            if (!isLoggedIn()) {
                return;
            }
        }

        char ch;
        do {
            std::cout << "Manage Employees" << std::endl << std::endl;
            std::cout << "[A] Add Employee" << std::endl;
            std::cout << "[B] Edit Employee Information" << std::endl;
            std::cout << "[C] Fire Employee" << std::endl;
            std::cout << "[D] Back" << std::endl << std::endl;
            std::cin >> ch;

            switch (toupper(ch)) {
                case 'A': {
                    std::cout << "Employee Information Form" << std::endl;
                    std::cin.ignore();
                    std::string name;
                    std::string bday;
                    std::string gender;
                    int age;
                    std::string civil;
                    std::string position;
                    std::string department;
                    std::string status;
                    std::string phone;
                    std::string email;
                    std::string address;
                    std::string bank;
                    double salary;
                    int daysOfWork = 0;
                    int hoursOfWork = 0;

                    std::cout << "Name: ";
                    std::getline(std::cin, name);
                    std::cout << "Birthday: ";
                    std::getline(std::cin, bday);
                    std::cout << "Gender: ";
                    std::getline(std::cin, gender);
                    std::cout << "Age: ";
                    std::cin >> age;
                    std::cin.ignore();
                    std::cout << "Civil Status: ";
                    std::getline(std::cin, civil);
                    std::cout << "Position: ";
                    std::getline(std::cin, position);
                    std::cout << "Department: ";
                    std::getline(std::cin, department);
                    std::cout << "Employment Status (FULL TIME or PART TIME): ";
                    std::getline(std::cin, status);
                    std::cout << "Phone Number: ";
                    std::getline(std::cin, phone);
                    std::cout << "Email Address: ";
                    std::getline(std::cin, email);
                    std::cout << "Address: ";
                    std::getline(std::cin, address);
                    std::cout << "Bank Information: ";
                    std::getline(std::cin, bank);
                    std::cout << "Salary: ";
                    std::cin >> salary;

                    if (status == "PART TIME") {
                        std::cout << "Days of Work: ";
                        std::cin >> daysOfWork;
                        std::cout << "Hours of Work: ";
                        std::cin >> hoursOfWork;
                    }

                    addEmployee(name, bday, gender, age, civil, position, department, status, phone, email, address, bank, salary, daysOfWork, hoursOfWork);
                    break;
                }
                case 'B': {
                    if (!hasEmployees()) {
                        std::cout << "The employee list is empty." << std::endl;
                        return;
                    }
                    int id;
                    std::cout << "Enter Employee ID: ";
                    std::cin >> id;
                    editEmployee(id);
                    break;
                }
                case 'C': {
                    if (!hasEmployees()) {
                        std::cout << "The employee list is empty." << std::endl;
                        return;
                    }
                    int id;
                    std::cout << "Enter Employee ID: ";
                    std::cin >> id;
                    deleteEmployee(id);
                    break;
                }
                case 'D':
                    break;
                default:
                    std::cout << "Invalid option selected!" << std::endl;
            }
        } while (toupper(ch) != 'D');
    }

    void managePayroll() {
        if (!isLoggedIn()) {
            std::cout << "Please login to access payroll management." << std::endl;
            login();
            if (!isLoggedIn()) {
                return;
            }
        }

        char ch;
        do {
            std::cout << "Manage Payroll" << std::endl << std::endl;
            std::cout << "[A] Display Employee Salary" << std::endl;
            std::cout << "[B] Update Employee Salary" << std::endl;
            std::cout << "[C] Back" << std::endl << std::endl;
            std::cin >> ch;

            switch (toupper(ch)) {
                case 'A': {
                    if (!hasEmployees()) {
                        std::cout << "The employee list is empty." << std::endl;
                        return;
                    }
                    std::cout << "Enter Employee ID: ";
                    int id;
                    std::cin >> id;
                    displaySalary(id);
                    break;
                }
                case 'B': {
                    if (!hasEmployees()) {
                        std::cout << "The employee list is empty." << std::endl;
                        return;
                    }
                    std::cout << "Enter Employee ID: ";
                    int id;
                    std::cin >> id;
                    double newSalary;
                    std::cout << "Enter New Salary: ";
                    std::cin >> newSalary;
                    updateSalary(id, newSalary);
                    break;
                }
                case 'C':
                    break;
                default:
                    std::cout << "Invalid option selected!" << std::endl;
                    break;
            }
        } while (toupper(ch) != 'C');
    }
};

int main() {
    char choice;
    EmployeeList employeeList;

    //employeeList.addEmployee("Juan dela Cruz", "1990-05-15", "Male", 31, "Single", "Software Engineer", "IT Department", "FULL TIME", "09123456789", "juan@example.com", "Manila, Philippines", "0123456789", 50000);
    //employeeList.addEmployee("Maria Santos", "1995-09-20", "Female", 26, "Married", "Data Analyst", "Finance Department", "PART TIME", "09123456788", "maria@example.com", "Quezon City, Philippines", "9876543210", 30000, 3, 4);


    do {
        std::cout << "Employee Database" << std::endl << std::endl;
        std::cout << "Menu" << std::endl << std::endl;
        std::cout << "[A] List of Employees" << std::endl;
        std::cout << "[B] Manage Employees" << std::endl;
        std::cout << "[C] Manage Payroll" << std::endl;
        std::cout << "[D] Login" << std::endl;
        std::cout << "[E] Logout" << std::endl;
        std::cout << "[F] Exit" << std::endl << std::endl;
        std::cin >> choice;

        switch (toupper(choice)) {
            case 'A':
                employeeList.displayEmployees();
                break;
            case 'B':
                employeeList.manageEmployee();
                break;
            case 'C':
                employeeList.managePayroll();
                break;
            case 'D':
                employeeList.login();
                break;
            case 'E':
                employeeList.logout();
                break;
            case 'F':
                std::cout << "Shutting down..." << std::endl;
                break;
            default:
                std::cout << "Invalid option selected!" << std::endl;
                break;
        }
    } while (toupper(choice) != 'F');

    return 0;
}
