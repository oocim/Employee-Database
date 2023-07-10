#include <iostream>
#include <string>
#include <limits>

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
        
        if (!hasEmployees()) {
            std::cout << "The employee list is empty." << std::endl;
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
                std::cout << "Position: " << current->position << std::endl << std::endl;
                std::cout << "Department: " << current->department << std::endl << std::endl;
                std::cout << "Employment Status: " << current->status << std::endl << std::endl;
                std::cout << "Phone Number: " << current->phone << std::endl << std::endl;
                std::cout << "Email Address: " << current->email << std::endl << std::endl;
                std::cout << "Address: " << current->address << std::endl << std::endl;
                std::cout << "Bank Information: " << current->bank << std::endl << std::endl;
                if (current->status == "PART TIME") {
                    std::cout << "Days of Work: " << current->daysOfWork << std::endl << std::endl;
                    std::cout << "Hours of Work: " << current->hoursOfWork << std::endl << std::endl;
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
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    current->daysOfWork = getValidIntegerInput(std::cin);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    current->hoursOfWork = getValidIntegerInput(std::cin);
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
        system("PAUSE");
        system("CLS");
    }

    void manageEmployee() {
        char ch;
        int id;
        do {
            system("CLS");
            std::cout << "Manage Employees" << std::endl << std::endl;
            std::cout << "[A] Add Employee" << std::endl;
            std::cout << "[B] Edit Employee Information" << std::endl;
            std::cout << "[C] Fire Employee" << std::endl;
            std::cout << "[D] Back" << std::endl << std::endl;
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
                    std::string department;
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
                    std::cout << "Position: " << std::endl;
                    std::getline(std::cin, position);
                    std::cout << "Department: " << std::endl;
                    std::getline(std::cin, department);

                    while (status != "FULL TIME" && status != "PART TIME") {
                        std::cout << "Employment Status (FULL TIME or PART TIME): " << std::endl;
                        std::getline(std::cin, status);
                        if (status != "FULL TIME" && status != "PART TIME") {
                            std::cout << "Invalid status. Please enter either 'FULL TIME' or 'PART TIME'." << std::endl;
                        }
                    }

                    std::cout << "Phone Number: " << std::endl;
                    std::getline(std::cin, phone);
                    std::cout << "Email Address: " << std::endl;
                    std::getline(std::cin, email);
                    std::cout << "Address: " << std::endl;
                    std::getline(std::cin, address);
                    std::cout << "Bank Information: " << std::endl;
                    std::getline(std::cin, bank);

                    if (status == "PART TIME") {
                        std::cout << "Salary: " << std::endl;
                        salary = getValidDoubleInput(std::cin);

                        std::cout << "Hours of Work: " << std::endl;
                        hoursOfWork = getValidIntegerInput(std::cin);

                        std::cout << "Days of Work: " << std::endl;
                        daysOfWork = getValidIntegerInput(std::cin);
                    } else {
                        std::cout << "Salary: " << std::endl;
                        salary = getValidDoubleInput(std::cin);
                    }

                    addEmployee(name, bday, gender, age, civil, position, department, status, phone, email, address, bank, salary, daysOfWork, hoursOfWork);
                    std::cout << "Employee Added Successfully!" << std::endl;
                    system("PAUSE");
                    break;
                }
                case 'B': {
                    if (!hasEmployees()) {
                        std::cout << "The employee list is empty." << std::endl;
                        system("PAUSE");
                        break;
                    }
                    system("CLS");
                    std:: cout << "Enter ID: " << std::endl;
                    id = getValidIntegerInput(std::cin);
                    editEmployee(id);
                    std::cout << std::endl << std::endl;
                    system("PAUSE");
                    break;
                }
                case 'C': {
                    if (!hasEmployees()) {
                        std::cout << "The employee list is empty." << std::endl;
                        system("PAUSE");
                        break;
                    }
                    system("CLS");
                    std:: cout << "Enter ID: " << std::endl;
                    id = getValidIntegerInput(std::cin);
                    deleteEmployee(id);
                    system("PAUSE");
                    break;
                }
                case 'D':
                    break;
                default:
                    std::cout << "Invalid option selected!" << std::endl;
            }
            system("CLS");
        } while (toupper(ch) != 'D');
    }

    void managePayroll() {
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
                    if (!hasEmployees()) {
                        std::cout << "The employee list is empty." << std::endl;
                        system("PAUSE");
                        break;
                    }
                    system("CLS");
                    std:: cout << "Enter ID: " << std::endl;
                    id = getValidIntegerInput(std::cin);
                    displaySalary(id);
                    break;
                }
                case 'B': {
                    if (!hasEmployees()) {
                        std::cout << "The employee list is empty." << std::endl;
                        system("PAUSE");
                        break;
                    }
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
                    break;
                default:
                    std::cout << "Invalid option selected!" << std::endl;
                    break;
            }
            system("CLS");
        } while (toupper(ch) != 'C');
    }

    void loginscreen(){
        std::cout << "ADMIN LOG IN" << std::endl;
        login();
    }
};

int main() {
    system("CLS");
    char choice;
    EmployeeList employeeList;

    employeeList.addEmployee("Juan dela Cruz", "1990-05-15", "Male", 31, "Single", "Software Engineer", "IT Department", "FULL TIME", "09123456789", "juan@example.com", "Manila, Philippines", "0123456789", 50000);
    employeeList.addEmployee("Maria Santos", "1995-09-20", "Female", 26, "Married", "Data Analyst", "Finance Department", "PART TIME", "09123456788", "maria@example.com", "Quezon City, Philippines", "9876543210", 30000, 3, 4);
    //employeeList.addEmployee("Vladimir Jocson", "1993-08-10", "Male", 28, "Single", "Senior Software Engineer", "IT Department", "FULL TIME", "09123456789", "vladimir@example.com", "Manila, Philippines", "0123456789", 60000);
    //employeeList.addEmployee("Sean Briones", "1992-06-25", "Male", 29, "Single", "Marketing Assistant", "Marketing Department", "PART TIME", "09123456788", "sean@example.com", "Quezon City, Philippines", "9876543210", 20000, 3, 20);
    //employeeList.addEmployee("Alex Penuliar", "1994-12-18", "Male", 27, "Single", "Junior Data Analyst", "Finance Department", "FULL TIME", "09123456787", "alex@example.com", "Makati City, Philippines", "0123456788", 40000);
    //employeeList.addEmployee("Kobe Capinpin", "1991-04-05", "Male", 32, "Married", "HR Manager", "Human Resources Department", "FULL TIME", "09123456786", "kobe@example.com", "Pasig City, Philippines", "0123456787", 70000);
    //employeeList.addEmployee("JC Magsino", "1993-11-12", "Female", 28, "Single", "Graphic Designer", "Creative Department", "PART TIME", "09123456785", "jc@example.com", "Taguig City, Philippines", "9876543219", 25000, 2, 15);
    //employeeList.addEmployee("Belle Mendoza", "1990-02-28", "Female", 31, "Married", "Project Manager", "Project Management Department", "FULL TIME", "09123456784", "belle@example.com", "Manila, Philippines", "0123456786", 80000);
    //employeeList.addEmployee("Maria Clara", "1996-07-15", "Female", 25, "Single", "Quality Assurance Analyst", "Quality Assurance Department", "PART TIME", "09123456783", "mariaclara@example.com", "Quezon City, Philippines", "9876543218", 22000, 2, 10);


    do {
        while(!employeeList.isLoggedIn()){
        employeeList.loginscreen();
        system("PAUSE");
        system("CLS");
    }
        system("CLS");
        std::cout << "Employee Database" << std::endl << std::endl;
        std::cout << "Menu" << std::endl << std::endl;
        std::cout << "[A] List of Employees" << std::endl;
        std::cout << "[B] Manage Employees" << std::endl;
        std::cout << "[C] Manage Payroll" << std::endl;
        std::cout << "[D] Logout" << std::endl;
        std::cout << "[E] Exit" << std::endl << std::endl;
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
                system("CLS");
                employeeList.logout();       
                break;
            case 'E':
                system("CLS");
                std::cout << "Shutting down..." << std::endl;
                break;
            default:
                std::cout << "Invalid option selected!" << std::endl;
                break;
        }
        system("PAUSE");
        system("CLS");
    } while (toupper(choice) != 'E');

    return 0;
}
