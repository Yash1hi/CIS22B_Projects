#include <iostream> 
#include <string> 
#include <sstream> 
#include <exception> 
using namespace std; 
class Name 
{ 
   private: 
     string  m_name ; 
   public: 
     Name(string name) : m_name(name) 
     { 
     } 
     string getName() 
     { 
          return m_name ; 
     } 
     virtual string toString() = 0 ; 
     virtual bool   contains(string search) = 0 ; 
     virtual bool   isTheSame(Name & another) = 0 ; 
}; 

class BadNameException : public runtime_error {
    public:
        BadNameException(string errMsg): runtime_error(errMsg) {}
};

class Word : public Name {
    private:
        string m_definition;
    public:
        Word(string name, string definition): Name(name), m_definition(definition) {
            bool wordOnlyBlanks = true;
            for (int i = 0; i < name.length(); i++) {
                if (name[i] != ' ') {
                    wordOnlyBlanks = false;
                    break;
                }
            }
            bool definitionOnlyBlanks = true;
            for (int i = 0; i < definition.length(); i++) {
                if (definition[i] != ' ') {
                    definitionOnlyBlanks = false;
                    break;
                }
            }
            
            if (name == "") {
                throw new BadNameException("Word cannot be empty.");
            }
            else if (wordOnlyBlanks) {
                throw new BadNameException("Word cannot be only blanks.");
            }
            else if (definition == "") {
                throw new BadNameException("Definition cannot be empty.");
            }
            else if (definitionOnlyBlanks) {
                throw new BadNameException("Definition cannot be only blanks.");
            }    
        }

        string toString() {
            return "WORD(" + Name::getName() + ") DEFINITION(" + m_definition + ")";
        }

        bool contains(string search) {
            bool contains = false;
            string name = Name::getName();
            size_t inName = name.find(search);
            size_t inDef = m_definition.find(search);
            if (inName != string::npos || inDef != string::npos) {
                contains = true;
            }
            return contains;
        }

        bool isTheSame(Name & another) {
            bool sameDef = false;
            Name *pWord;
            pWord = &another;
            Word *pAnother = dynamic_cast<Word *> (pWord);
            if (pAnother != nullptr) {
                sameDef = (pAnother->m_definition == m_definition);
            }
            return (another.getName() == Name::getName() && sameDef);
        }
};

class Item : public Name {
    private:
        double m_price;
    public:
        Item(string name, double price): Name(name), m_price(price) {
            bool itemOnlyBlanks = true;
            for (int i = 0; i < name.length(); i++) {
                if (name[i] != ' ') {
                    itemOnlyBlanks = false;
                    break;
                }
            }    
            if (name == "") {
                throw new BadNameException("Name cannot be empty.");
            }
            else if (itemOnlyBlanks) {
                throw new BadNameException("Name cannot be only blanks.");
            }
        }

        string toString() {
            stringstream ss;
            ss << "ITEM(" << Name::getName() << ") PRICE($" << m_price << ")";
            return ss.str();
        }

        bool contains(string search) {
            bool contains = false;
            string name = Name::getName();
            size_t inName = name.find(search);
            if (inName != string::npos) {
                contains = true;
            }
            return contains;
        }

        bool isTheSame(Name & another) {
            Name *pItem;
            pItem = &another;
            Item *pAnother = dynamic_cast<Item *> (pItem);
            return (another.getName() == Name::getName() && (pAnother != nullptr));
        }        
};

// Assumption: Will always return at least 1 as the last element will be the same as the last element
void countTheSameAsLast(Name* nameList[], int size, int & numSame, bool & firstLastSame) {
    numSame = 0;
    firstLastSame = (nameList[size-1]->isTheSame(*nameList[0]));
    for (int i = 0; i < size; i++) {
        if (nameList[size-1]->isTheSame(*nameList[i])) {
            numSame += 1;
        }
    }
}

void createTwoNames(Name* names[]) {
    string word, definition;
    Word *wordObj;
    try {
        cout << "Please enter a word: ";
        getline(cin, word);
        cout << "Please enter its definition: "; 
        getline(cin, definition);
        wordObj = new Word(word, definition);
    }
    catch (BadNameException *pErrObj) {
        cout << "Exception: " << pErrObj->what() << endl;
        wordObj = nullptr;
    }
    string item;
    double price;
    Item *priceObj;
    try {
        cout << "Please enter the name of the item: ";
        getline(cin, item);
        cout << "Please enter its price: "; 
        cin >> price;
        priceObj = new Item(item, price);
    }
    catch (BadNameException *pErrObj) {
        cout << "Exception: " << pErrObj->what() << endl;
        wordObj = nullptr;
    }
    if (wordObj != nullptr) {
        names[0] = wordObj;
    }
    else {
        names[0] = nullptr;
    }
    if (priceObj != nullptr) {
        names[1] = priceObj;
    }
    else {
        names[1] = nullptr;
    }

}

bool testWord() {
    bool passed = true;
    Word w1("school", "an educational institution");
    Word w2("school", "an educational institution");
    if (w1.toString() != "WORD(school) DEFINITION(an educational institution)") { passed = false; }
    if (w1.contains("1") || !(w1.contains("oo")) || !(w1.contains("educational"))) { passed = false; }
    if (!(w1.isTheSame(w2))) { passed = false; }
    try {
        Word w3("  ", "10");
    }
    catch (BadNameException *pErrObj) {
        string errorMsg = pErrObj->what();
        if (errorMsg != "Word cannot be only blanks.") {
            passed = false;
        }
    }
    try {
        Word w4("test", "  ");
    }
    catch (BadNameException *pErrObj) {
        string errorMsg = pErrObj->what();
        if (errorMsg != "Definition cannot be only blanks.") {
            passed = false;
        }
    }
    try {
        Word w5("", "test");
    }
    catch (BadNameException *pErrObj) {
        string errorMsg = pErrObj->what();
        if (errorMsg != "Word cannot be empty.") {
            passed = false;
        }
    }
    try {
        Word w6("test", "");
    }
    catch (BadNameException *pErrObj) {
        string errorMsg = pErrObj->what();
        if (errorMsg != "Definition cannot be empty.") {
            passed = false;
        }
    }
    return passed;
}

bool testItem() {
    bool passed = true;
    Item i1("eraser", 1.05);
    Item i2("eraser", 1.05);
    if (i1.toString() != "ITEM(eraser) PRICE($1.05)") { passed = false; }
    if (i1.contains("toodles") || !(i1.contains("eraser")) || !(i1.contains("ras"))) { passed = false; }
    if (!(i1.isTheSame(i2))) { passed = false; }
    try {
        Item i3("", 1.05);
    }
    catch (BadNameException *pErrObj) {
        string errorMsg = pErrObj->what();
        if (errorMsg != "Name cannot be empty.") {
            passed = false;
        }
    }
    try {
        Item i4("  ", 1.05);
    }
    catch (BadNameException *pErrObj) {
        string errorMsg = pErrObj->what();
        if (errorMsg != "Name cannot be only blanks.") {
            passed = false;
        }
    }
    return passed;
}

bool testCountTheSameAsLast() {
    bool passed = true;
    Item *i1 = new Item("eraser", 1.05);
    Item *i2 = new Item("eraser", 1.05);
    Item *i3 = new Item("eraser", 1.05);
    Word *w1 = new Word("eraser", "A written exam");
    Word *w2 = new Word("test", "A written exam");
    bool same;
    int numSame;
    Name* nameList[5] = {i1, i2, w1, w2, i3};
    countTheSameAsLast(nameList, 5, numSame, same);
    if (numSame != 3 || same != true) {
        passed = false;
    }
    return passed;
}

// Manual testing 
void testCreateTwoNames() {
    Name* names[2] = {nullptr, nullptr};
    createTwoNames(names);
}


int main() {
    cout << "Testing Word: " << boolalpha << testWord() << endl;
    cout << "Testing Item: " << boolalpha << testItem() << endl;
    cout << "Testing countTheSameAsLast: " << boolalpha << testCountTheSameAsLast() << endl;
    // Must be tested manually
    testCreateTwoNames();
}