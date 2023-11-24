#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;
//tarif be sorat global
enum typeWork {
    fullTime,partTime
};
struct Date {
    int year,month,day;
};
struct Person {
    string name;
    char family[50];
    int id;
    int tell;
    Date birthday;
    Date start2Work;
    Date end2Work;
    typeWork salary;
};
bool saveWarning(string warningType);
void eraseFileLine(string path, string eraseLine);
bool deletePerson(int id);
bool TFsearch(int id);
Person readFromDatabase(int id);
Person getPersonData();
void save2Database(Person person);
void showDB(string path);
void showAllDB(string path);
bool editPerson(Person person);
void searchPerson(int id);
int main() {
    //******************************************************
    int dastor,idSearch;
    cout<<"Be barname DataBase khosh amadid, baraye ezafe kardan adade 1, baraye namayesh hame adad 2";
    cout<<" va baraye search kardan adad 3 ra vared konid: ";
    cin>>dastor;

    switch (dastor) {
        case 1:
            save2Database(getPersonData());
            break;
        case 2:
            showAllDB("main.txt");
            break;
        case 3:
            cout<<"ID ra baraye search kardan vared konid: ";
            cin>>idSearch;
            searchPerson(idSearch);
            break;

    }
    return 0;
}
void writeDown() {//yek file be esme wrtieDown dorost mikonad ke zaman system ra dar khod zakhire mikonad
    time_t  tt;
    struct tm * ti;
    time(&tt);
    ti = localtime(&tt);
    ofstream writeDown("writeDown.txt", ios::trunc);//file ra reset mikonad ta ro-nevisi shavad
    writeDown << asctime(ti);
    writeDown.close();
}

bool saveWarning(string warningType) {//check kardan zakhire taxirat
    int warningCode;
    string javab;
    if (warningType == "add") {
        warningCode = 1;
    } else if (warningType == "delete") {
        warningCode = 2;
    } else if (warningType == "edit") {
        warningCode = 3;
    }

    switch (warningCode) {//switch conditions faghat ba int kar mikonad
        case 1:
            cout<<"Az add kardan in fard motmaenid?(y/n)";
            cin>>javab;
            if (javab == "y") {
                return true;
            } else {
                writeDown();//agar karbard taxirat ra zaxire nakard writeDown() ejra mikonim
                return false;
            }
        case 2:
            cout<<"az delete kardan in fard motmaenid?(y/n)";
            cin>>javab;
            if (javab == "y") {
                return true;
            } else {
                writeDown();
                return false;
            }
        case 3:
            cout<<"Az edit kardan in fard motmaenid?(y/n)";
            cin>>javab;
            if (javab == "y") {
                return true;
            } else {
                writeDown();
                return false;
            }
    }
}
void eraseFileLine(string path, string eraseLine) {//baraye hazf yek khat moshakhas az file
    string line;
    ifstream fin(path);
    ofstream temp("temp.txt");//hame khat ha ra bejoz khat hazfy dar file temp minevisad
    while (getline(fin, line)) {//sepas main.txt ra hazf karde va temp.txt ra rename mikonad
        if(line != eraseLine) {
            temp << line << "\n";
        }
    }
    temp.close();
    fin.close();
    const char *p = path.c_str();
    remove(p);
    rename("temp.txt",p);
}

bool deletePerson(int id) {//yek ID ra gerefte va file marbote ra hazf mikonad
    string toBeDeletedPath;
    toBeDeletedPath = ""+to_string(id)+".txt";
    if( remove(toBeDeletedPath.c_str()) == 0) {//file ra ke ID an ra gerefte hazf mikonad
        eraseFileLine("main.txt",to_string(id));//hamchenin khat marbote ra dar main.txt hazf mikonad
        return true;
    } else {
        return false;
    }
}

bool TFsearch(int id) {//search kardan baraye ID va return kardan TRUE ya FALSE
    string line;
    ifstream searchId("main.txt");
    if (searchId.is_open()) {
        while (!searchId.eof()) {
            getline(searchId, line);
            if (to_string(id) == line) {
                searchId.close();
                return true;
            }
        }
    }
    searchId.close();
    return false;
}

Person readFromDatabase(int id) {//bar-aks save2DB, ba estefade az file ID yek copy az person dorost mikonad
    int lineCounter = 1;
    string line;
    if (TFsearch(id)) {
        Person fetchedPerson;
        ifstream fetchedFile(to_string(id)+".txt");
        if (fetchedFile.is_open()) {
            while (!fetchedFile.eof()) {
                getline(fetchedFile,line);//khat be khat file ra paymayesh karde va anra dar copy Person migozarad
                switch (lineCounter) {
                    case 1:
                        fetchedPerson.name = line;
                        break;
                    case 2:
                        for (int i = 0; i < line.length();i++) {
                            fetchedPerson.family[i] = line[i];
                        }
                        break;
                    case 3:
                        fetchedPerson.tell = stoi(line);
                        break;
                    case 4:
                        fetchedPerson.id = stoi(line);
                        break;
                    case 5:
                        fetchedPerson.birthday.year = stoi(line);
                        break;
                    case 6:
                        fetchedPerson.birthday.month = stoi(line);
                        break;
                    case 7:
                        fetchedPerson.birthday.day = stoi(line);
                        break;
                    case 8:
                        fetchedPerson.start2Work.year = stoi(line);
                        break;
                    case 9:
                        fetchedPerson.start2Work.month = stoi(line);
                        break;
                    case 10:
                        fetchedPerson.start2Work.day = stoi(line);
                        break;
                    case 11:
                        fetchedPerson.end2Work.year = stoi(line);
                        break;
                    case 12:
                        fetchedPerson.end2Work.month = stoi(line);
                        break;
                    case 13:
                        fetchedPerson.end2Work.day = stoi(line);
                        break;
                    case 14:
                        if (line == "Full-Time") {
                            fetchedPerson.salary = fullTime;
                        } else {
                            fetchedPerson.salary = partTime;
                        }
                }
                lineCounter++;
            }
        }
        fetchedFile.close();
        return fetchedPerson;
    }
    Person nullPerson;
    cout<<"Shaxs mored nazar yaft nashod";
    return nullPerson;
}

Person getPersonData() {
    cout<<"name, lastname, tell, id, birthday, start2Work, end2work ra vered konid: ";
    Person addPerson;
    //dorost karden yek copy az Person va gereftan info az karbar va rikhtan info dar addPerson
    cin>>addPerson.name>>addPerson.family>>addPerson.tell>>addPerson.id>>addPerson.birthday.year>>addPerson.birthday.month>>addPerson.birthday.day;
    cin>>addPerson.start2Work.year>>addPerson.start2Work.month>>addPerson.start2Work.day;
    cin>>addPerson.end2Work.year>>addPerson.end2Work.month>>addPerson.end2Work.day;
    //baraye entexab noe kar
    int noeKar = 10;
    while (noeKar) {//ta zamani ke karbar adad 1 ya 2 ra vared nakonad, halghe baste nemishavad
        cout<<"baraye full-time job enter 1 va baraye part-time job enter 2";
        cin>>noeKar;
        if (noeKar == 1) {
            addPerson.salary = fullTime;
            break;
        } else if (noeKar == 2) {
            addPerson.salary = partTime;
            break;
        } else {
            noeKar = 5;
            cout<<"Please enter a valid number, 1 for full-time and 2 for part-time";
        }
    }
    if (saveWarning("add")) {//farakhani saveWarning
        return addPerson;//agar ghasde save dashte bashad, addPerson return mishavad
    } else {//dar xair in sorat az barname kharej mishavad
        exit(0);
    }
}

void save2Database (Person person) {//yek copy az Person ra dar Database zaxire mikonad
    string workKind;
    ofstream userFile(to_string(person.id) + ".txt");//ijad va baz kardan yek file text ba esme person.id
    if (userFile.is_open()) {//check kardan baz shodon file
        //moshaxas kardan noe kar va tabdil kardan an be string
        if (person.salary == fullTime) {
            workKind = "Full-Time";
        } else {
            workKind = "Part-Time";
        }
        //neveshtan moshaxasat person dar file ba esme person.id
        userFile << person.name <<"\n"<< person.family <<"\n"<<person.tell<<"\n"<<person.id<<"\n"<<
                 person.birthday.year << "\n" << person.birthday.month << "\n" << person.birthday.day << "\n" <<
                 person.start2Work.year << "\n" << person.start2Work.month << "\n" << person.start2Work.day << "\n" <<
                 person.end2Work.year << "\n" << person.end2Work.month << "\n" << person.end2Work.day << "\n" << workKind;

        userFile.close();
        //dorost kardan main.txt va zaxire kardan ID dar an
        ofstream mainFile("main.txt", ios::app);
        mainFile << person.id << "\n";
        mainFile.close();
    } else {
        cout<<"amaliat zaxire sazi be moshkel xord";
        exit(0);
    }
}

void showDB(string path) {//path ra gerefte va file marbote re neshan midahad
    char ch;
    ifstream showF(path);
    if(showF.is_open()) {
        showF.seekg(0, ios::beg);
        showF.get(ch);
        while(!showF.eof()) {
            cout.put(ch);
            showF.get(ch);
        }
        cout<<"\n";//baraye behter kardan showAll, chon bazi az field ha be ham michasbidand
        showF.close();
    } else {
        exit(0);
    }
}

void showAllDB(string path) {//neshan dadan hame file haye Database
    string line;
    ifstream showAll(path);
    showAll.seekg(0,ios::beg);
    while(!showAll.eof()) {//khat be khat main.txt ra ba line migirad
        getline(showAll,line);
        showDB(line+".txt");//ba estefade az showDB file ra neshan midahad
    }
    showAll.close();
}

bool editPerson(Person person) {
    int fieldNum;
    cout<<"chand ghesmat ra edit mikonid: ";
    cin>>fieldNum;
    if (fieldNum < 1 || fieldNum > 8) {//agar tedad field haye entekhab shode eshtebah bashad, barname kharej mishavad
        exit(1);
    } else {
        string editFields[fieldNum];//field haye entekhab shode ra dar editFields mirizim
        cout<<"field haye ra ke mikhahid edit konid ba fasele vared konid:\n1.Name\n2.LastName\n3.Tell\n4.ID";
        cout<<"\n5.Birthday\n6.Start to Work\n7.End to Work\n8.Type of work(Full-Time or Part-Time)";
        for (int i = 0; i < fieldNum; i++) {
            cin>>editFields[i];
        }
        int personIdBackUp = person.id;//bayad az ID copy begirim chon shayad ID niz edit shavad

        for (int editCommand = 0; editCommand < fieldNum; editCommand++) {

            switch (stoi(editFields[editCommand])) {
                case 1:
                    cout<<"Enter new name: ";
                    cin>>person.name;
                    break;
                case 2:
                    cout<<"Enter new lastName: ";
                    cin>>person.family;
                    break;
                case 3:
                    cout<<"Enter new tell: ";
                    cin>>person.tell;
                    break;
                case 4:
                    cout<<"Enter new ID: ";
                    cin>>person.id;
                    break;
                case 5:
                    cout<<"Enter new Birthday(YYYY MM DD): ";
                    cin>>person.birthday.year>>person.birthday.month>>person.birthday.day;
                    break;
                case 6:
                    cout<<"Enter new Start2Work(YYYY MM DD): ";
                    cin>>person.start2Work.year>>person.start2Work.month>>person.start2Work.day;
                    break;
                case 7:
                    cout<<"Enter new End2Work(YYYY MM DD): ";
                    cin>>person.end2Work.year>>person.end2Work.month>>person.end2Work.day;
                    break;
                case 8:
                    int workKind = 5;
                    while (workKind) {
                        cout<<"baraye full-time job adad 1 va baraye part-time job adad 2 ra vared konid";
                        cin>>workKind;
                        if (workKind == 1) {
                            person.salary = fullTime;
                            break;
                        } else if (workKind == 2) {
                            person.salary = partTime;
                            break;
                        } else {
                            workKind = 5;
                            cout<<"adad vared shode dorost nist";
                        }
                    }
            }
        }
        if (saveWarning("edit")) {
            deletePerson(personIdBackUp);//file asly fard ra hazf karde va yek file jadid edit shode ra ijad mikonim
            save2Database(person);
        } else {
            exit(2);
        }
    }
}

void searchPerson(int id) {
    int command;
    string line,toBeDeletedPath;
    ifstream searchFile("main.txt");
    if (searchFile.is_open()) {
        while (!searchFile.eof()) {
            getline(searchFile,line);
            if (to_string(id) == line) {
                cout<<"shaxs mored nazar yaft shod\n1.Delete\n2.Show\n3.Edit";
                cin>>command;
                switch (command) {
                    case 1://Delete
                        searchFile.close();
                        if (saveWarning("delete")) {
                            if (deletePerson(stoi(line))) {
                                cout<<"File mored nazar hazf show";
                            } else {
                                cout<<"dar hazf file moshkeli pish amad";
                            }
                        } else {
                            exit(8);
                        }
                        break;

                    case 2://Show
                        showDB(line+".txt");
                        break;

                    case 3://Edit
                        searchFile.close();
                        editPerson(readFromDatabase(id));
                        break;
                }

            }
        }
        searchFile.close();
    } else {
        cout<<"File payda nashod";
    }
}