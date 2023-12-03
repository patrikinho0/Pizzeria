#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Ingredient
{
private:
    string name;
    int quantity;
    float calories;

public:
    Ingredient(string n, int q, float c) : name(n), quantity(q), calories(c) {}
    float getCalories()
    {
        return calories;
    }
    string getName() 
    { 
        return name;
    }
    int getQuantity()
    {
        return quantity;
    }
};

class Pizza
{
private:
    string name;
    string dough;
    string sauce;
    float price;
    vector<Ingredient*> toppings;

public:
    float getCalories()
    {
        float totalCalories = 0;
        for (int i = 0; i < toppings.size(); ++i)
        {
            totalCalories += toppings[i]->getCalories();
        }
        return totalCalories;
    }
    void setName(string pizzaName)
    { 
        name = pizzaName;
    }
    void setDough(string pizzaDough) 
    { 
        dough = pizzaDough;
    }
    void setSauce(string pizzaSauce) 
    { 
        sauce = pizzaSauce;
    }
    void setToppings(vector<Ingredient*>& tp) 
    { 
        toppings = tp;
    }
    void addTopping(Ingredient* topping)
    {
        toppings.push_back(topping);
    }
    void displayPizza()
    {
        cout << "Pizza: " << name << endl;
        cout << "Dough: " << dough << endl;
        cout << "Sauce: " << sauce << endl;
        cout << endl;

        cout << "Toppings:" << endl;
        for (int i = 0; i < toppings.size(); ++i)
        {
            cout << "- " << toppings[i]->getName() << endl;
        }

        cout << "Calories: " << getCalories() << " kcal" << endl;
        cout << endl;
    }
};

class PizzaBuilder
{
protected:
    Pizza* pizza;

public:
    virtual void createNewPizza() 
    { 
        pizza = new Pizza(); 
    }
    virtual void buildName() = 0;
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void addToppings() = 0;
    virtual Pizza* getPizza()
    { 
        return pizza; 
    }
};

class MargheritaBuilder : public PizzaBuilder
{
public:
    MargheritaBuilder()
    {
        
    }
    void buildName()
    { 
        pizza->setName("Margherita"); 
    }
    void buildDough()
    { 
        pizza->setDough("Thin Crust"); 
    }
    void buildSauce()
    { 
        pizza->setSauce("Tomato"); 
    }
    void addToppings()
    {
        vector<Ingredient*> toppings;

        toppings.push_back(new Ingredient("Cheese", 1, 150.0));
        toppings.push_back(new Ingredient("Basil", 3, 10.0));
        toppings.push_back(new Ingredient("Mozzarella", 1, 250.0));

        pizza->setToppings(toppings);
    }
};

class PepperoniBuilder : public PizzaBuilder
{
public:
    PepperoniBuilder() 
    {
        
    }
    void buildName()
    { 
        pizza->setName("Pepperoni"); 
    }
    void buildDough()
    { 
        pizza->setDough("Thin Crust"); 
    }
    void buildSauce() 
    { 
        pizza->setSauce("Tomato"); 
    }
    void addToppings()
    {
        vector<Ingredient*> toppings;

        toppings.push_back(new Ingredient("Cheese", 1, 150.0));
        toppings.push_back(new Ingredient("Pepper", 2, 50.0));
        toppings.push_back(new Ingredient("Mozzarella", 1, 250.0));

        pizza->setToppings(toppings);
    }
};

class CustomBuilder : public PizzaBuilder
{
private:
    vector<Ingredient*> availableToppings;
public:
    CustomBuilder() 
    {
        availableToppings.push_back(new Ingredient("Mushroom", 1, 80.0));
        availableToppings.push_back(new Ingredient("Pepper", 2, 50.0));
        availableToppings.push_back(new Ingredient("Mozzarella", 1, 250.0));
        availableToppings.push_back(new Ingredient("Pineapple", 3, 100.0));
        availableToppings.push_back(new Ingredient("Chicken", 3, 300.0));
        availableToppings.push_back(new Ingredient("Salami", 3, 280.0));
    }
    void buildName()
    {
        cout << "Enter pizza name: ";
        string pizzaName;
        cin >> pizzaName;
        pizza->setName(pizzaName);
    }
    void buildDough()
    {
        cout << "Enter dough type: ";
        string pizzaDough;
        cin >> pizzaDough;
        pizza->setDough(pizzaDough);
    }
    void buildSauce()
    {
        cout << "Enter sauce type: ";
        string pizzaSauce;
        cin >> pizzaSauce;
        pizza->setSauce(pizzaSauce);
    }
    void addToppings()
    {
        cout << "Available Toppings:" << endl;
        for (int i = 0; i < availableToppings.size(); i++)
        {
            cout << " [" << i << "] " << availableToppings[i]->getName() << endl;
        }

        for (int i = 1; i < 4; i++)
        {
            int choice;
            cout << "Choose topping #" << i << ": ";
            cin >> choice;

            if (choice >= 0 && choice <= availableToppings.size())
            {
                pizza->addTopping(new Ingredient(
                    availableToppings[choice]->getName(),
                    availableToppings[choice]->getQuantity(),
                    availableToppings[choice]->getCalories()
                ));
            }
            else
            {
                cout << "Invalid choice. Skipping topping." << endl;
            }
        }
    }
};

class PizzaFactory
{
private:
    PizzaBuilder* pizzaBuilder;

public:
    void setPizzaBuilder(PizzaBuilder* pb)
    {
        pizzaBuilder = pb;
    }

    Pizza* getPizza()
    {
        return pizzaBuilder->getPizza();
    }

    void constructPizza()
    {
        pizzaBuilder->createNewPizza();
        pizzaBuilder->buildName();
        pizzaBuilder->buildDough();
        pizzaBuilder->buildSauce();
        pizzaBuilder->addToppings();
    }
};

int main()
{
    cout << "Welcome to the Pat Pizzeria!" << endl;
    cout << endl;

    PizzaFactory pizzaFactory;

    cout << "Choose a pizza type:" << endl;
    cout << "[1] Margherita" << endl;
    cout << "[2] Pepperoni" << endl;
    cout << "[3] Custom Pizza" << endl;

    int choice;
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    cout << endl;

    if (choice == 1)
    {
        // Margherita pizza
        PizzaBuilder* margheritaBuilder = new MargheritaBuilder();
        pizzaFactory.setPizzaBuilder(margheritaBuilder);

        pizzaFactory.constructPizza();
        Pizza* margheritaPizza = pizzaFactory.getPizza();
        margheritaPizza->displayPizza();
    }
    else if (choice == 2)
    {
        // Pepperoni pizza
        PizzaBuilder* pepperoniBuilder = new PepperoniBuilder();
        pizzaFactory.setPizzaBuilder(pepperoniBuilder);

        pizzaFactory.constructPizza();
        Pizza* pepperoniPizza = pizzaFactory.getPizza();
        pepperoniPizza->displayPizza();
    }
    else if (choice == 3)
    {
        // Custom pizza
        CustomBuilder* customBuilder = new CustomBuilder();
        pizzaFactory.setPizzaBuilder(customBuilder);

        cout << "Build Your Own Pizza" << endl;
        pizzaFactory.constructPizza();
        Pizza* customPizza = pizzaFactory.getPizza();
        customPizza->displayPizza();
    }
    else
    {
        cout << "Invalid choice. Exiting program." << endl;
        return 1;
    }

    return 0;
}
