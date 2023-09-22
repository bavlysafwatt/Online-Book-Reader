#include<bits/stdc++.h>
using namespace std;

int readInt(int low, int high){
    cout << "\nEnter number in range " << low << " - " << high << ": ";
    int choice; cin >> choice;
    if (low <= choice && choice <= high)
        return choice;
    cout << "ERROR: invalid number...Try again\n";
    return readInt(low, high);
}

int readmenu(const vector<string> &choices){
    cout << "\nMenu\n";
    for(int i = 0 ; i < choices.size() ; i++){
        cout << "\t" << i+1 << "- " << choices[i] << endl;
    }
    return readInt(1,choices.size());
}

string return_current_time_and_date(){
    auto now = chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(now);

    stringstream ss;
    ss << put_time(localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

class book{
private:
    string ispn;
    string title;
    string author;
    vector<string> pages;
public:
    void Read() {
		string str;
		cout << "Enter ISBN: ";
		cin >> str;
		set_ispn(str);

		cout << "Enter Title: ";
		cin >> str;
		set_title(str);

		cout << "Enter Author Name: ";
		cin >> str;
		set_author(str);

		cout << "Enter How many pages: ";
		int pages_count;
		cin >> pages_count;

		for (int page = 0; page < pages_count; ++page) {
			cout << "Enter page # " << page + 1 << ": ";
			cin >> str;
			pages.push_back(str);
		}
	}

    void set_ispn(const string &i){
        ispn = i;
    }

    void set_title(const string &i){
        title = i;
    }

    void set_author(const string &i){
        author = i;
    }

    void set_pages(const vector<string> &p){
        pages = p;
    }

    string get_ispn() const{
        return ispn;
    }
    string get_title() const{
        return title;
    }
    string get_author() const{
        return author;
    }
    vector<string> get_pages() const{
        return pages;
    }
};

class ReadingSession{
private:
    book Book;
    int current_page;
    string last_access;
public:
    ReadingSession(){}
    ReadingSession(const book &b):
        Book(b), current_page(0), last_access(return_current_time_and_date()) {
	}
    void setbook(book &B){
        Book = B;
    }
    book getbook() const{
        return Book;
    }
    void resetcurrentdateandtime(){
        last_access = return_current_time_and_date();
    }
    string getcurrentdateandtime() const{
        return last_access;
    }
    int getcurrentpage() const{
        return current_page;
    }

    void nextpage(){
        if (current_page < (int) Book.get_pages().size()-1)
            current_page++;
    }
    void previouspage() {
        if (current_page > 0)
            current_page--;
    }
    string getcurrentpagecontent() const{
        return Book.get_pages()[current_page];
    }
};

class user{
private:
    string name;
    string password;
    string email;
    string user_name;
    bool is_admin;
    vector<ReadingSession> history;
public:
	void print_user(){
	    cout << "Name: " << name << " ";
	    if(is_admin){
            cout << "| Admin ";
	    }
	    cout << endl;
	    cout << "Email: " << email << " \n";
	    cout << "User_name: " << user_name << endl;
	}

	void read(string &user_n){
	    setusername(user_n);
	    string str;
	    cout << "Enter password (no spaces): ";
		cin >> str;
		setpassword(str);

		cout << "Enter name (no spaces): ";
		cin >> str;
		setname(str);

		cout << "Enter email (no spaces): ";
		cin >> str;
		setemail(str);
	}
	void setname(string s){
	    name = s;
	}
	void setpassword(string s){
	    password = s;
	}
	void setemail(string s){
	    email = s;
	}
	void setusername(string s){
	    user_name = s;
	}
	void setisadmin(bool is){
	    is_admin = is;
	}
	string getname() const{
	    return name;
	}
	string getpassword() const{
	    return password;
	}
	string getemail() const{
	    return email;
	}
	string getusername() const{
	    return user_name;
	}
	bool isadmin() const{
	    return is_admin;
	}
	const vector<ReadingSession> &getsession() const{
	    return history;
	}
    ReadingSession AddReadingSession(book Book) {
        // We create pointer & later delete it
        ReadingSession session(Book);
        history.push_back(session);
        return session;
    }
};

class usermanager{
private:
    user current_user;
    map<string, user> user_object;
public:
    usermanager(const usermanager&) = delete;
	void operator=(const usermanager&) = delete;

    usermanager(){}

    void loaddatabase(){
        user user1;
		user1.setusername("mostafa");
		user1.setpassword("111");
		user1.setemail("most@gmail.com");
		user1.setisadmin(true);
		user1.setname("Mostafa Saad Ibrahim");
		user_object[user1.getusername()] = user1;

		user user2;
		user2.setusername("asmaa");
		user2.setpassword("222");
		user2.setemail("asmaa@gmail.com");
		user2.setisadmin(false);
		user2.setname("Asmaa Saad Ibrahim");
		user_object[user2.getusername()] = user2;
    }
    void access_system(){
        int choice = readmenu({"Login", "Sign Up"});
        if(choice==1) login();
        else sign_up();
    }

    void login(){
        loaddatabase();
        while(true){
            string un, pass;
            cout << "Enter user name (no spaces): ";
            cin >> un;
            cout << "Enter password (no spaces): ";
            cin >> pass;
            if(!user_object.count(un)){
                cout << "\nInvalid user user_name or password. Try again\n\n";
                continue;
            }
            user User = user_object[un];
            if(pass!=User.getpassword()){
                cout << "\nInvalid user user_name or password. Try again\n\n";
                continue;
            }
            current_user = User;
            break;
        }
    }

    void sign_up(){
        string user_name;
        while(true){
            cout << "Enter user name(no spaces): ";
            cin >> user_name;
            if(user_object.count(user_name))
                cout << "Already used, please try again." << endl;
            else
                break;
        }
        current_user.read(user_name);
        user_object[current_user.getusername()] = current_user;
    }
    user getcurrentuser(){
        return current_user;
    }
    ReadingSession AddReadingSession(book Book) {
        return current_user.AddReadingSession(Book);
    }
};

class bookmanager{
private:
    map<string, book> book_object;
public:
    bookmanager(const bookmanager&) = delete;
	void operator=(const bookmanager&) = delete;

    bookmanager(){}

	void loaddatabase(){
	    book book1;
		book1.set_ispn("00001");
		book1.set_author("Mostafa");
		book1.set_title("C++ how to program");
		vector<string> pages1 = { "A C++", "B C++", "C C++", "D C++", "E C++" };
		book1.set_pages(pages1);
		addbook(book1);

		book book2;
		book2.set_ispn("00002");
		book2.set_author("Morad");
		book2.set_title("Intro to algo");
		vector<string> pages2 = { "A Algo", "B Algo", "C Algo", "D Algo", "E " };
		book2.set_pages(pages2);
		addbook(book2);

		book book3;
		book3.set_ispn("00003");
		book3.set_author("Morad");
		book3.set_title("Data Structures in C++");
		vector<string> pages3 = { "A Data", "B Data", "C Data", "D Data", "E Data" };
		book3.set_pages(pages3);
		addbook(book3);
	}

	void addbook(book &Book){
	    book_object[Book.get_ispn()] = Book;
	}

	map<string, book> getbooks() const{
	    return book_object;
	}
};

class Userview{
private:
    usermanager &users_manager;
    bookmanager &books_manager;
public:
    Userview(usermanager & user_manager, bookmanager &book_manager) :
			users_manager(user_manager), books_manager(book_manager) {
	}
    void display(){
        user current_user = users_manager.getcurrentuser();
        cout << endl << endl << "Hello " << current_user.getname() << endl << endl;
        vector <string> menu;
        menu.push_back("View Profile");
		menu.push_back("List & Select from My Reading History");
		menu.push_back("List & Select from Available Books");
		menu.push_back("Logout");
		while(true){
            int choice = readmenu(menu);
            if(choice == 1) viewprofile();
            else if (choice == 2) listreadinghistory();
            else if(choice == 3) listavailablebook();
            else break;
		}
    }
    void viewprofile(){
            user current_user = users_manager.getcurrentuser();
		    cout << endl;
		    current_user.print_user();
		    cout << endl;
    }

    void displaysession(ReadingSession &session){
        vector<string> menu;
        menu.push_back("Next Page");
        menu.push_back("Previous Page");
        menu.push_back("Exit");
        while (true){
            cout << "Current Page: " << session.getcurrentpage()+1 << "/" << session.getbook().get_pages().size() << endl;
            cout << session.getcurrentpagecontent();
            int choice = readmenu(menu);
            if(choice==1) session.nextpage();
            else if(choice == 2) session.previouspage();
            else break;
        }
        session.resetcurrentdateandtime();
    }

    void listreadinghistory(){
        vector<ReadingSession> his = users_manager.getcurrentuser().getsession();
        cout << "Reading History." << endl;
        int idx = 0;
        for(auto &session : his){
            cout << "\t" << ++idx << "-" <<session.getbook().get_title() << " Page: " << session.getcurrentpage()+1 << "/" << session.getbook().get_pages().size() << "  " << session.getcurrentdateandtime() << endl;
        }
        if(idx==0) {
            cout << "No History." << endl;
            return;
        }
        cout << "\nWhich session to open?: ";
        int choice = readInt(1,idx);
        displaysession(his[choice-1]);
    }

    void listavailablebook(){
        const map<string, book> &books = books_manager.getbooks();
        int idx = 0;
        cout << "Available Books." << endl;
        for(const auto &b : books){
            cout << "\t" << ++idx << "-" << b.second.get_title() << endl;
        }
        cout << "\nWhich book to read?: ";
        int choice = readInt(1,idx);
        idx = 0;
        for(const auto &p : books){
            if(++idx==choice){
                ReadingSession session = users_manager.AddReadingSession(p.second);
                displaysession(session);
                break;
            }
        }
    }
};

class Adminview{
private:
    usermanager &user_manager;
    bookmanager &book_manager;
public:
    Adminview(usermanager & users_manager, bookmanager &books_manager) :
			user_manager(users_manager), book_manager(books_manager) {
	}
    void display(){
        user current_user = user_manager.getcurrentuser();
        cout << endl << endl << "Hello " << current_user.getname() << endl << endl;
        vector <string> menu;
        menu.push_back("View Profile");
		menu.push_back("Add Book");
		menu.push_back("Logout");
		while(true){
            int choice = readmenu(menu);
            if(choice == 1) viewprofile();
            else if (choice == 2) addbook();
            else break;
		}
    }
    void viewprofile(){
		    user current_user = user_manager.getcurrentuser();
		    cout << endl;
		    current_user.print_user();
		    cout << endl;
		}

		void addbook(){
		    book Book;
		    Book.Read();
		    book_manager.addbook(Book);
		}
};

class Onlinebookreadersystem{
private:
    bookmanager book_manager;
    usermanager user_manager;

    void LoadDatabase() {
		book_manager.loaddatabase();
		user_manager.loaddatabase();
	}
public:
    void Run(){
        LoadDatabase();
        while(true){
            user_manager.access_system();
            if(user_manager.getcurrentuser().isadmin()){
                Adminview view(user_manager, book_manager);
                view.display();
            }
            else{
                Userview view(user_manager, book_manager);
                view.display();
            }
        }
    }
    Onlinebookreadersystem() {}
};

int main(){
    Onlinebookreadersystem site;
    site.Run();
    return 0;
}