#include <iostream>

class EmployeeList {
private:
    struct Employee {
        std::string name;
        std::string bday;
        int age;
        std::string position;
        std::string email;
        std::string address;
        std::string bank;
        Employee* next;

        Employee(const std::string& name, const std::string& bday, int age, const std::string& position, const std::string& email, const std::string& address, const std::string& bank)
            : name(name), bday(bday), age(age), position(position), email(email), address(address), bank(bank), next(nullptr) {}
    };

    Employee* head;
    Employee* tail;

public:
    EmployeeList() : head(nullptr), tail(nullptr) {}

    // Add Employee and Details
    void addEmployee(const std::string& name, const std::string& bday, int age, const std::string& position, const std::string& email, const std::string& address, const std::string& bank) {
        Employee* newEmployee = new Employee(name, bday, age, position, email, address, bank);

        if (head == nullptr) {
            head = newEmployee;
            tail = newEmployee;
        } else {
            tail->next = newEmployee;
            tail = newEmployee;
        }
    }

    void displayEmployees() const {
        Employee* current = head;
        while (current != nullptr) {
            std::cout << "Name: " << current->name << std::endl;
            current = current->next;
        }
    }

    void searchEmployee(const std::string& name) const {
        Employee* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->name == name) {
                std::cout << "Employee Information:" << std::endl;
                std::cout << "Name: " << current->name << std::endl;
                std::cout << "Birthday: " << current->bday << std::endl;
                std::cout << "Age: " << current->age << std::endl;
                std::cout << "Position: " << current->position << std::endl;
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
                    std::string name;
                    std::string bday;
                    int age;
                    std::string position;
                    std::string email;
                    std::string address;
                    std::string bank;

                    std::cout << "Name: ";
                    std::cin >> name; 
                    std::cout << "Birthday: ";
                    std::cin >> bday; 
                    std::cout << "Age: ";
                    std::cin >> age;
                    std::cout << "Position: ";
                    std::cin >> position;
                    std::cout << "Email Address: ";
                    std::cin >> email;
                    std::cout << "Address: ";
                    std::cin >> address;
                    std::cout << "Bank Information: ";
                    std::cin >> bank; 

                    addEmployee(name, bday, age, position, email, address, bank);
                    system("pause");
                    system("cls");
                    break;
                }

                case 'B':
                    // TODO: Edit employee function
                    system("pause");
                    system("cls");
                    break;

                case 'C':
                    // TODO: Delete employee function
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
                    std::string search;
                    std::cin >> search;
                    employeeList.searchEmployee(search);
                }
                }while(toupper(c) != 'B');

                system("pause");
                system("cls");
                break;
            case 'B':
                std::cout << "Managing employees..." << std::endl;
                employeeList.manageEmployee();
                break;
            case 'C':
                std::cout << "Processing employee payroll..." << std::endl;
                // TODO: Implement logic for processing payroll
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
