#include <iostream>
#include <string>

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
        Employee* next;

        Employee(int id, const std::string& name, const std::string& bday, std::string& gender, int age, std::string& civil, const std::string& position, std::string& status, std::string& department, std::string& phone, const std::string& email, const std::string& address, const std::string& bank, double salary)
    : id(id), name(name), bday(bday), gender(gender), age(age), civil(civil), position(position), department(department), status(status), phone(phone), email(email), address(address), bank(bank), salary(salary), next(nullptr) {}

    };

    Employee* head;
    Employee* tail;
    int nextId;

public:
    EmployeeList() : head(nullptr), tail(nullptr), nextId(1) {}

    void addEmployee(const std::string& name, const std::string& bday, std::string& gender, int age, std::string& civil, const std::string& position, std::string& status, std::string& department, std::string& phone, const std::string& email, const std::string& address, const std::string& bank, double salary) {
        Employee* newEmployee = new Employee(nextId, name, bday, gender, age, civil, position, department, status, phone, email, address, bank, salary);
        nextId++;

        if (head == nullptr) {
            head = newEmployee;
            tail = newEmployee;
        } 
        else {
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
        Employee* current = head;
        while (current != nullptr) {
            std::cout << current->id << ") Name: " << current->name << std::endl;
            current = current->next;
        }
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

                    found = true;
                    break;
                }
                current = current->next;
            }

            if (!found) {
                std::cout << "Employee not found!" << std::endl;
            }
        }

        void editEmployee(int& id) {

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
                    int age = std::stoi(ageStr);
                    current->age = age;
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

                found = true;
                break;
            }
            current = current->next;
        }

        if (!found) {
            std::cout << "Employee not found!" << std::endl;
        }
    }

    void update_salary(int id, double newSalary) 
    {
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

    void display_salary(int id) const {
        Employee* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->id == id) {
                double payroll = current->salary;
                std::cout << "Payroll for Employee ID " << id << ": " << payroll << std::endl;
                found = true;
                break;
            }
            current = current->next;
        }

        if (!found) {
            std::cout << "Employee not found!" << std::endl;
        }
    }

    int calculate_salary(int salary)
    {
        int SSS, PhilHealth, tax, totaldeduc;
        SSS = salary * 0.05;
        PhilHealth = salary * 0.05;
        tax = salary * 0.05;

        totaldeduc = SSS + PhilHealth + tax;
        int netSalary = salary - totaldeduc;

        std::cout << "Total Deductions: " << totaldeduc << std::endl;
        std::cout << "Net Salary: " << netSalary << std::endl;

        return netSalary;
    }



    void manageEmployee(){
        system("cls");
        char ch;
        do{

            std::cout << "Manage Employees" << std::endl << std::endl;
            std::cout << "[A] Add Employee" << std::endl;
            std::cout << "[B] Edit Employee Information" << std::endl;
            std::cout << "[C] Fire Employee" << std::endl << std::endl;
            std::cout << "[D] Back" << std::endl << std::endl;
            std::cin >> ch;

            switch(toupper(ch)){
                case 'A': {
                    system("cls");
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
                    std::cout << "Employment Status: ";
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
                    
                    addEmployee(name, bday, gender, age, civil, position, department, status, phone, email, address, bank,salary);
                    system("pause");
                    system("cls");
                    break;
                }
                case 'B':
                    int id;
                    std::cout << "Enter Employee ID" << std::endl;
                    std::cin >> id;
                    editEmployee(id);
                    system("pause");
                    system("cls");
                    break;

                case 'C':
                    int search;
                    std::cout << "Enter Employee ID" << std::endl;
                    std::cin >> search;
                    deleteEmployee(search);
                    system("pause");
                    system("cls");
                    break;
                case 'D':
                    system("pause");
                    system("cls");
                    break;
                default:
                    std::cout << "Invalid option selected!" << std::endl;
            }
        }while(toupper(ch) != 'D');
    }

    void managePayroll()
    {
        system("cls");
        char ch;

        do {
            std::cout << "Manage Employees" << std::endl << std::endl;
            std::cout << "[A] Display Employee Salary" << std::endl;
            std::cout << "[B] Edit Employee Salary" << std::endl;
            std::cout << "[C] Back" << std::endl << std::endl;
            std::cin >> ch;

            switch (toupper(ch))
            {
                case 'A':
                {
                    system("cls");
                    std::cout << "Enter Employee ID: ";
                    int idd;
                    std::cin >> idd;
                    display_salary(idd);
                    system("pause");
                    system("cls");
                    break;
                }
                case 'B':
                {
                    system("cls");
                    std::cout << "Enter Employee ID: ";
                    int idd;
                    std::cin >> idd;
                    Employee* current = head;
                    int rate, days, salary;
                    while (current != nullptr) 
                    {
                        if(current->id == idd)
                        {
                            std::string status = current->status;
                            if (status == "PART TIME")
                            {
                                std::cout << "Enter Rate: ";
                                std::cin >> rate;
                                salary = rate * 30 * 8;
                            }
                            else if(status == "FULL TIME")
                            {
                                std::cout << "Enter Rate: ";
                                std::cin >> rate;
                            
                                salary = rate * 30;
                            }
                        }
                        current = current->next;
                    }
                    salary = calculate_salary(salary);
                    update_salary(idd, salary);
                    break;
                }
                case 'C':
                {
                    system("pause");
                    system("cls");
                    break;
                }
                default:
                {
                    std::cout << "Invalid option selected!" << std::endl;
                    break;
                }
            }
        } while (toupper(ch) != 'C');
    }

};

int main(){
    char choice;
    EmployeeList employeeList;
    
    do{
        system("cls");
        std::cout << "Employee Database" << std::endl << std::endl;
        std::cout << "Menu" << std::endl << std::endl;
        std::cout << "[A] List of Employees" << std::endl;
        std::cout << "[B] Manage Employees" << std::endl;
        std::cout << "[C] Employee Payroll" << std::endl;
        std::cout << "[D] Exit" << std::endl << std::endl;
        std::cin >> choice;

        switch(toupper(choice)){
            case 'A':
                std::cout << "Current Employees" << std::endl;
                employeeList.displayEmployees();
                std::cout << std::endl;
                char c;
                do{
                std::cout << "[A] View Employee Details" << std::endl;
                std::cout << "[B] Back" << std::endl;
                std::cin >> c;
                if(toupper(c) == 'A'){
                    std::cout << "Enter Employee" << std::endl;
                    int search;
                    std::cin >> search;
                    employeeList.searchEmployee(search); //NEED ERROR HANDLING
                }
                }while(toupper(c) != 'B');

                system("pause");
                system("cls");
                break;
            case 'B':
                employeeList.manageEmployee();
                break;
            case 'C':
                employeeList.managePayroll();
                system("pause");
                system("cls");
                break;
            case 'D':
                std::cout << "Shutting Down........." << std::endl;
                system("pause");
                system("cls");
                return 0;
                break;
            default:
                std::cout << "Invalid option selected!" << std::endl;
        }
    } while(toupper(choice) != 'D');

    return 0;
}