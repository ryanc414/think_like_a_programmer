/*
 * 5-1. Let's try implementing a class using the basic framework. Consider a class to
 * store the data for an automobile. We'll have three pieces of data: a manufacturer
 * name and model name, both strings, and a model year, an integer. Create a
 * class with get/set methods for each data member. Make sure you make good
 * decisions concerning details like member names. It's not important that you
 * follow my particular naming convention. What'ss important is that you think
 * about the choices you make and are consistent in your decisions.
 */

#include <iostream>
#include <string>


// Automobile class storing manufacturer name, model name, and model year.
class Automobile {
  public:
    Automobile() = default;
    Automobile(std::string manufacturer, std::string model, int year);

    std::string manufacturer() const;
    void set_manufacturer(std::string manufacturer);
    std::string model() const;
    void set_model(std::string model);
    int year() const;
    void set_year(int year);

    friend std::ostream &
    operator<<(std::ostream &strm, Automobile const &automobile);

  private:
    std::string manufacturer_;
    std::string model_;
    int year_;

    bool IsValidYear(int year);
};

// Test basic usage of the Automobile class.
int main() {
    Automobile car_a;
    car_a.set_manufacturer("Ford");
    car_a.set_model("Focus");
    car_a.set_year(2016);
    std::cout << "car_a = " << car_a << std::endl;

    Automobile car_b("Vauxhall", "Corsa", 2017);
    std::cout << "car_b = " << car_b << std::endl;

    // Try to set an invalid year.
    try {
        car_b.set_year(-999);
    } catch (std::out_of_range &err) {
        std::cout << "Caught out_of_range: " << err.what() << std::endl;
    }

    return 0;
}

// Construct a new Automobile from its manufacturer name, model and year.
Automobile::Automobile(std::string manufacturer, std::string model, int year) :
        manufacturer_(manufacturer), model_(model), year_(year) {
    if (!IsValidYear(year)) {
        throw std::out_of_range("Invalid year");
    }
}

// Get the manufacturer name.
std::string Automobile::manufacturer() const {
    return manufacturer_;
}

// Set the manufacturer name.
void Automobile::set_manufacturer(std::string manufacturer) {
    manufacturer_ = manufacturer;
}

// Get the model name.
std::string Automobile::model() const {
    return model_;
}

// Set the model name.
void Automobile::set_model(std::string model) {
    model_ = model;
}

// Get the year.
int Automobile::year() const {
    return year_;
}

// Set the year.
void Automobile::set_year(int year) {
    if (!IsValidYear(year)) {
        throw std::out_of_range("Invalid year.");
    }
    year_ = year;
}

// Enable stream output of the Automobile.
std::ostream & operator<<(std::ostream &strm, Automobile const &automobile) {
    strm << "Automobile["
         << automobile.manufacturer() << ", "
         << automobile.model() << ", "
         << automobile.year() << "]";

    return strm;
}

// Validate an Automobile's year. For our simple example a valid year must be
// in the range 1900-2100.
bool Automobile::IsValidYear(int year) {
    return (year >= 1900) && (year < 2100);
}

