#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class IOinterface
{
public:
    virtual istream& read(istream& in) = 0;
    virtual ostream& write(ostream& out) const = 0;
};

class Ingredients
{
    string name;
    bool alergens;
    int grams;

public:
    Ingredients(string, bool, int);
    Ingredients(const Ingredients& aux);
    Ingredients& operator=(const Ingredients& aux);
    friend istream& operator>>(istream& in, Ingredients& aux);
    friend ostream& operator<<(ostream& out, const Ingredients& aux);

    string getName()
    {
        return this->name;
    }
    int getGrams()
    {
        return this->grams;
    }
    void setGrams(int g)
    {
        this->grams = this->grams + g;
    }
};

Ingredients::Ingredients(string name="anonim", bool alergens=false, int grams=0)
{

    this->name = name;
    this->alergens = alergens;
    this->grams = grams;
}

Ingredients::Ingredients(const Ingredients& aux)
{
    this->name = aux.name;
    this->alergens = aux.alergens;
    this->grams = aux.grams;
}

Ingredients& Ingredients::operator=(const Ingredients& aux)
{

    if(this != &aux)
    {
        this->name = aux.name;
        this->alergens = aux.alergens;
        this->grams = aux.grams;
    }

    return *this;
}

istream& operator>>(istream& in, Ingredients& aux)
{

    cout << "The name of the ingredient: ";
    in >> aux.name;
    cout << "\nDoes it contain alergens: ";
    in >> aux.alergens;
    cout << "\nQuantity: ";
    in >> aux.grams;

    return in;
}

ostream& operator<<(ostream& out, const Ingredients& aux)
{

    out << "Name: " << aux.name << endl;
    out << "Alergens: " << aux.alergens << endl;
    out << "Grams: " << aux.grams << endl;

    return out;
}

class Dish: public IOinterface
{
protected:
    string name;
    vector<Ingredients> ingredientsList;
/// int minutesPrep;
/// int kcal;

public:
    Dish();
    Dish(string, vector<Ingredients>);
    Dish(const Dish&);
    Dish& operator=(const Dish&);
    virtual Ingredients& operator[](int i)
    {
        return ingredientsList[i];
    }
    virtual int getSize()
    {
        return ingredientsList.size();
    }
    friend istream &operator >> (istream &in, Dish &d)
    {
        return d.read(in);
    }

    friend ostream& operator<<(ostream& out, const Dish& d)
    {
        return d.write(out);
    }

    istream& read(istream& in)
    {
        int k;
        system("CLS");
        cout << "Name: ";
        in >> this->name;

        if(!this->ingredientsList.empty())
        {
            this->ingredientsList.clear();
        }
        while(true)
        {
            system("CLS");
            cout<< "1 - New ingredient \n0 - Complete ";
            cin >> k;
            system("CLS");
            if(k == 0)
                break;
            else
            {
                this->ingredientsList.push_back(*(new Ingredients()));
                in >> this->ingredientsList.back();
            }
        }
        //cout << "How long does it take to make this dish: ";
        //in >> this->minutesPrep;

        return in;
    }
    ostream& write(ostream& out) const
    {
        out << "Name: " << this->name << endl;
        //out << "Preparation in minutes: " << this->minutesPrep << endl;
        out<<"Ingredients: \n";
        for(int i=0; i<this->ingredientsList.size(); i++)
            out << "\n * " << this->ingredientsList[i];

        return out;
    }
    virtual ~Dish() {}
};
Dish::Dish()
{

    this->name = "anonim";
    this->ingredientsList = {};
    //this->minutesPrep = minutesPrep;
}
Dish::Dish(string name="anonim", vector<Ingredients> ingredientsList = {})
{

    this->name = name;
    this->ingredientsList = ingredientsList;
    //this->minutesPrep = minutesPrep;
}

Dish::Dish(const Dish& aux)
{
    this->name = aux.name;
    this->ingredientsList = aux.ingredientsList;
    //this->minutesPrep = aux.minutesPrep;
}

Dish& Dish::operator=(const Dish& aux)
{

    if(this != &aux)
    {
        this->name = aux.name;
        this->ingredientsList = aux.ingredientsList;
        //this->minutesPrep = aux.minutesPrep;
    }

    return *this;
}

class Meal:virtual public Dish
{
protected:
    int protein_grams;

public:
    Meal(string name="anonim", vector<Ingredients> ingredientsList = {}, int protein_grams = 0)
        :Dish(name, ingredientsList)
    {
        this->protein_grams = protein_grams;
    }
    Meal(const Meal&);
    Meal& operator=(const Meal&);

    istream& read(istream& in)
    {
        this->Dish::read(in);
        cout << "Protein grams? ";
        in >> this->protein_grams;
        return in;
    }

    ostream& write(ostream& os) const
    {
        this->Dish::write(os);
        cout << "Protein grams: " << this->protein_grams << endl;
        return os;
    }
    friend istream &operator >> (istream &in, Meal &m)
    {
        return m.read(in);
    }

    friend ostream& operator<<(ostream& out, const Meal& m)
    {
        return m.write(out);
    }
    virtual ~Meal() {}
};

Meal::Meal(const Meal& obj): Dish(obj)
{
    this->protein_grams = protein_grams;
}
Meal& Meal::operator =(const Meal& obj)
{
    if(this != &obj)
    {
        Dish::operator=(obj);
        this->protein_grams = obj.protein_grams;
    }
    return *this;
}
class Desert:virtual public Dish
{
protected:
    int sugar_grams;

public:
    Desert(string name="anonim", vector<Ingredients> ingredientsList = {}, int sugar_grams = 0)
        :Dish(name, ingredientsList)
    {
        this->sugar_grams = sugar_grams;
    }
    Desert(const Desert&);
    Desert& operator=(const Desert&);

    istream& read(istream& in)
    {
        this->Dish::read(in);
        cout << "Sugar grams? ";
        in >> this->sugar_grams;
        return in;
    }

    ostream& write(ostream& os) const
    {
        this->Dish::write(os);
        cout << "Sugar grams: " << this->sugar_grams << endl;
        return os;
    }
    friend istream &operator >> (istream &in, Desert &d)
    {
        return d.read(in);
    }

    friend ostream& operator<<(ostream& out, const Desert& d)
    {
        return d.write(out);
    }
    virtual ~Desert() {}
};

Desert::Desert(const Desert& obj): Dish(obj)
{
    this->sugar_grams = sugar_grams;
}
Desert& Desert::operator =(const Desert& obj)
{
    if(this != &obj)
    {
        Dish::operator=(obj);
        this->sugar_grams = obj.sugar_grams;
    }
    return *this;
}

class Combo: public Meal, public Desert
{
    bool WJET;
public:

    Combo(string name="anonim", vector<Ingredients> ingredientsList = {}, int protein_grams = 0, int surgar_grams = 0, bool WJET = 0): Dish(name, ingredientsList), Meal(name,
                ingredientsList, protein_grams), Desert(name, ingredientsList, sugar_grams)
    {
        this->WJET = WJET;
    }

    Combo(const Combo& obj): Dish(obj), Meal(obj), Desert(obj)
    {
        this->WJET = obj.WJET;
    }

    Combo& operator =(const Combo& obj)
    {
        if(this != &obj)
        {
            Meal::operator=(obj);
            Desert::operator=(obj);
            this->WJET = obj.WJET;
        }
        return *this;
    }

    istream& read(istream& in)
    {
        Dish::read(in);
        cout << "Protein grams: \n";
        in >> this->protein_grams;
        cout << "Sugar grams: \n";
        in >> this->sugar_grams;
        cout << "Would Jamila eat this? ";
        in >> this->WJET;
        system("CLS");
        return in;
    }
    ostream& write(ostream& os) const
    {
        Dish::write(os);
        os << "\nProtein grams: " << this->protein_grams << endl;
        os << "Sugar grams: " << this->sugar_grams << endl;
        os << "Would Jamila eat this?: " << this->WJET << endl;
        return os;
    }
    virtual ~Combo() {}
};

//class

class RecipeBookJamila
{
    Dish* dish;
public:
    Dish getDish()
    {
        return *this->dish;
    }
    friend istream& operator >>(istream& in, RecipeBookJamila& obj)
    {
        cout << "1. Meal\n";
        cout << "2. Desert\n";
        cout << "3. Combo\n";
        int k;
        cin >> k;
        if(k == 1)
            obj.dish = new Meal();
        if(k == 2)
            obj.dish = new Desert();
        if(k == 3)
            obj.dish = new Combo();
        in >> *obj.dish;
        return in;
    }

    friend ostream& operator<<(ostream& os, const RecipeBookJamila& obj)
    {
        os << "Dish:\n" << *obj.dish << endl;
        return os;
    }
};

class Kitchen
{
    vector<RecipeBookJamila> recipes;
    vector<Ingredients> fridge;
public:
    void addRecipe();
    void showRecipes();
    void whatIsInMyFridge();
    void newStuffInMyFridge();
    void jamilaHelp();
};


void Kitchen::addRecipe()
{
    RecipeBookJamila R;
    cin>>R;
    recipes.push_back(R);
}

void Kitchen::newStuffInMyFridge()
{
    Ingredients I;
    cin>>I;
    for(int i = 0; i < fridge.size(); i++)
        if(fridge[i].getName() == I.getName())
        {
            fridge[i].setGrams(I.getGrams());
            return;
        }

    fridge.push_back(I);
    system("CLS");
}

void Kitchen::whatIsInMyFridge()
{
    if(fridge.size() == 0)
    {
        int i;
        cout<<"Your fridge is empty :(\nPress 0 to go back!";
        cin>>i;
        system("CLS");
    }

    for(int i = 0; i < fridge.size(); i++)
        cout << fridge[i] << '\n';
    int i;
    cout<<"Press 0 to go back!";
    cin>>i;
    system("CLS");
}

void Kitchen::showRecipes()
{
    if(recipes.size() == 0)
    {
        int i;
        cout<<"Your Jamila Cooking Book is empty right now :(\nPress 0 to go back!";
        cin>>i;
        system("CLS");
    }
    for(int i = 0; i < recipes.size(); i++)
        cout << recipes[i] << '\n';
    int i;
    cout<<"Press 0 to go back!";
    cin>>i;
    system("CLS");
}
void Kitchen::jamilaHelp()
{
    int ok3 = 0;
    for(int i = 0; i < recipes.size(); i++)///fiecare reteta
    {
        int ok2 = 1;
        for(int j = 0; j < recipes[i].getDish().getSize(); j++)///fiecare ingredient din reteta
        {
            int ok = 0;
            for(int p = 0; p < fridge.size(); p++)///vad ce am eu in frigider
                if(recipes[i].getDish()[j].getName() == fridge[p].getName())
                {
                    if(recipes[i].getDish()[j].getGrams() <= fridge[p].getGrams())
                    {
                        ok = 1;
                        break;
                    }
                }
            if(ok == 0)
            {
                ok2 = 0;
                break;
            }

        }
        if(ok2 == 1)
        {
            cout<<recipes[i];
            cout<<"--------------";
            ok3 = 1;
        }
    }
    if(ok3 == 0)
    {
        int i;
        cout<<"Nu ai ce mancare sa faci :(\nPress 0 to go back!";
        cin>>i;
        system("CLS");
    }
    if(ok3 == 1)
    {
        int i;
        cout<<"Acestea sunt retele recomandate de Jamila :)\nPress 0 to go back!";
        cin>>i;
        system("CLS");
    }


}


int main()
{
    //Desert M;
    //Dish* dish;

    //Ingredients A, B;
    //Meal D;
    //cin >> A;
    //cin>>B;
    //system("CLS");
    //cin>>D;
    //Dish D2(D);
    //cout<<D2;
    Kitchen K;
    //Dish* d = new Combo;
    //K.addRecipe();
    //K.addRecipe()
    int t = 1;
    while(t == 1)
    {
        cout << "1. New recipe\n";
        cout << "2. Show my recipes\n";
        cout << "3. What is in my fridge?\n";
        cout << "4. I went shopping\n";
        cout << "5. Jamila, what can i cook?\n";
        cout << "6. Stop\n";
        int c;
        cin >> c;
        system("CLS");
        switch(c)
        {
        case 1:
        {
            K.addRecipe();
            break;
        }

        case 2:
        {
            K.showRecipes();
            break;
        }

        case 3:
        {
            K.whatIsInMyFridge();
            break;
        }

        case 4:
        {
            K.newStuffInMyFridge();
            break;
        }
        case 5:
        {
            K.jamilaHelp();
            break;
        }
        default:
        {
            t = 0;
            break;
        }
        }
    }
    return 0;
}

///1 3 PuiGratarSiTartaLamaie 1 pui 0 150 1 piper 0 10 1 lamaie 0 50 1 biscuiti 0 350 1 lapte_condensat 1 200 0 30 40 1
///4 pui 0 150 4 lamaie 0 80 4 biscuiti 0 350 4 lapte_condensat 0 250 4 piper 0 9


