#include <iostream>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <cstring>
#include<bits/stdc++.h>
using namespace std;

class Classroom{
private:
    struct SubjectNode{
        string code;
        string name;
        int numberOfLearn;
        int numberOfDo;
        SubjectNode *left, *right;
    };

    struct ScoreNode{
        string code;
        int index;
        double score;
        ScoreNode *next;
    };

    struct StudentNode{
        string code;
        string firstName;
        string lastName;
        string gender;
        string phoneNumber;
        ScoreNode *scoreNode;
        StudentNode *next;
    };

    struct ClassroomNode{
        string code;
        string name;
        int year;
        StudentNode *st;
    };
    
    struct List{
    	int size;
    	ClassroomNode *classroom[1000];
	};

public:
	List ds;
    SubjectNode *root;
    int size;
    ofstream outfile;
    //string stCodeArr[1000];
    //int stLength;

    Classroom(){
        size = 0;
        //stLength = 0;
        root = NULL;

        if(fexists("dslh.txt") == 1){
            readClassroomFromFile();
        }

        if(fexists("dsmh.txt") == 1){
            readMhFromFile();
        }

        if(fexists("dssv.txt") == 1){
            readSVFromFile();
        }

        if(fexists("dsscore.txt") == 1){
            readScoreFromFile();
        }
    }

    void readScoreFromFile(){
    	
        ifstream infile;
        infile.open("dsscore.txt");

        string data;
        string arr[1000];
        int j = 0;

        while (1){
            getline(infile, data);
            if(!data.empty()){
                arr[j] = data;
                j ++;
                data = "";
            } else
                break;
        }
        infile.close();

        for(int i = 0; i < j; i++){
            string classCode, stCode, subCode;
            int indexExam;
            float score;
            int start = 0, count = 0;

            for(int k = 0; k < arr[i].length(); k++){
                if(count == 4){
                    indexExam = atoi(arr[i].substr(start, arr[i].length() - start + 1 ).c_str());
                    addScoreFromFileFunc(classCode, stCode, subCode, score, indexExam);
                }

                if(arr[i].at(k) == '-'){

                    if(count == 3){
                        score = atoi(arr[i].substr(start, k - start).c_str());
                        count ++;
                    }

                    if(count == 2){
                        subCode = arr[i].substr(start, k - start);
                        count ++;
                    }

                    if(count == 1){
                        stCode = arr[i].substr(start, k - start);
                        count ++;
                    }

                    if(count == 0){
                        classCode = arr[i].substr(start, k);
                        count ++;
                    }

                    start = k+1;
                }
            }
        }

    }

    void addScoreFromFileFunc(string classCode, string studentCode, string subjectCode, float score, int indexExam){
        int classRoomIndex = isExistClassroom(classCode);
        if(isExistStudent(ds.classroom[classRoomIndex]->code, studentCode) == 0){
            cout << "--- Sinh vien khong ton tai ---" << endl;
            return;
        }

        if(isExistSubject(subjectCode) == 0){
            cout << "--- Mon hoc khong ton tai ---" << endl;
            return;
        }

        StudentNode *currentNode = ds.classroom[classRoomIndex]->st;
        while(currentNode != NULL){
            if(currentNode->code == studentCode){
                ScoreNode *newNode = new ScoreNode;
                newNode->code = subjectCode;
                newNode->score = score;
                newNode->index = indexExam;
                newNode->next = NULL;

                ScoreNode *p = currentNode->scoreNode;
                while (p!=NULL){
                    if(p->next == NULL) break;
                    p = p->next;
                }

                if(p == NULL){
                    currentNode->scoreNode = newNode;
                } else{
                    p->next = newNode;
                }
            }
            currentNode = currentNode->next;
        }
        cout << "         " << endl;
    }

    void readSVFromFile(){
        ifstream infile;
        infile.open("dssv.txt");

        string data;
        string arr[1000];
        int j = 0;

        while (1){
            getline(infile, data);
            if(!data.empty()){
                arr[j] = data;
                j ++;
                data = "";
            } else
                break;
        }
        infile.close();

        for(int i = 0; i < j; i++){
            string classCode, stCode, firstName, lastName, gender, phone;
            int start = 0, count = 0;

            for(int k = 0; k < arr[i].length(); k++){
                if(count == 5){
                    phone = arr[i].substr(start, k - start + 10 );
                    addStudentFunc(classCode, stCode, firstName, lastName, gender, phone, 0);
                }

                if(arr[i].at(k) == '-'){
                    if(count == 4){
                        gender = arr[i].substr(start, k - start);
                        count ++;
                    }

                    if(count == 3){
                        lastName = arr[i].substr(start, k - start);
                        count ++;
                    }

                    if(count == 2){
                        firstName = arr[i].substr(start, k - start);
                        count ++;
                    }

                    if(count == 1){
                        stCode = arr[i].substr(start, k - start);
                        count ++;
                    }

                    if(count == 0){
                        classCode = arr[i].substr(start, k);
                        count ++;
                    }

                    start = k+1;
                }
            }
        }
    }

    void readClassroomFromFile(){
        string data;
        string arr[1000];
        int j = 0;

        ifstream infile;
        infile.open("dslh.txt");

        while (1){
            getline(infile, data);

            if(!data.empty()){
                arr[j] = data;
                j ++;
                data = "";
            } else
                break;
        }
        infile.close();

        for(int i = 0; i < j; i++){
            string code, name;
            int year, start = 0, count = 0;
            for(int k = 0; k < arr[i].length(); k++){
                if(count == 2){
                    year = atoi(arr[i].substr(start, arr[i].length() - start + 1 ).c_str());
                    addClassroomFunc(code, name, year, 0);
                    break;
                }

                if(arr[i].at(k) == '-'){
                    if(count == 1){
                        name = arr[i].substr(start, k - start);
                        count ++;
                    }

                    if(count == 0){
                        code = arr[i].substr(start, k);
                        count ++;
                    }

                    start = k+1;
                }
            }
        }
    }

    void readMhFromFile(){
        string data;
        string arr[1000];
        int j = 0;
        ifstream infile;
        infile.open("dsmh.txt");

        while (1){
            getline(infile, data);
            if(!data.empty()){
                arr[j] = data;
                j ++;
                data = "";
            } else
                break;
        }
        infile.close();

        for(int i = 0; i < j; i++){
            string name, code;
            int STCLT, STCTH, start = 0, count = 0;

            for(int k = 0; k < arr[i].length(); k++){
                if(count == 3){
                    STCTH = atoi(arr[i].substr(start, k - start + 1 ).c_str());
                    addSubjectFunc(code, name, STCLT, STCTH, 0);
                    break;
                }

                if(arr[i].at(k) == '-'){
                    if(count == 2){
                        STCLT = atoi(arr[i].substr(start, k - start).c_str());
                        count ++;
                    }

                    if(count == 1){
                        code = arr[i].substr(start, k - start);
                        count ++;
                    }

                    if(count == 0){
                        name = arr[i].substr(start, k);
                        count ++;
                    }

                    start = k+1;
                }
            }
        }
    }

    void writeFile(int key){
        switch (key){
            case 1:
                writeDslh();
                break;
            case 2:
                writeStudentList();
                break;
            case 3:
                writeDsmh();
                break;
            case 4:
                writeScore();
                break;
        }
    }

    void writeScore(){
        ofstream outfile;
        outfile.open("dsscore.txt");

        for(int i = 0; i < size; i++){
            StudentNode *node = ds.classroom[i]->st;
            while (node != NULL){
                ScoreNode *sc = node->scoreNode;

                while (sc != NULL){
                    outfile << ds.classroom[i]->code << "-" << node->code << "-" << sc->code << "-" << sc->score << "-" << sc->index << endl;
                    sc = sc->next;
                }

                node = node ->next;
            }
        }
        outfile.close();
    }

    void writeStudentList(){
        ofstream outfile;
        outfile.open("dssv.txt");

        for(int i = 0; i < size; i++){
            StudentNode *node = ds.classroom[i]->st;
            while (node != NULL){
                outfile << ds.classroom[i]->code << "-" << node->code << "-" << node->firstName << "-" << node->lastName << "-" << node->gender << "-" << node->phoneNumber << endl;
                node = node->next;
            }
        }
        outfile.close();
    }

    void writeDslh(){
        ofstream outfile;
        outfile.open("dslh.txt");

        for(int k = 0; k < size; k++){
            outfile << ds.classroom[k]->code << "-" << ds.classroom[k]->name << "-" << ds.classroom[k]->year << endl;
        }
        outfile.close();
    }

    void writeDsmh(){
        outfile.open("dsmh.txt");
        writeAllSubject(root);
        outfile.close();
    }

    void writeAllSubject(SubjectNode *root){
        if(root != NULL){
            writeAllSubject(root->left);
            outfile << root->name << "-" << root->code << "-" << root->numberOfLearn<< "-" << root->numberOfDo << endl;
            writeAllSubject(root->right);
        }
    }

    bool fexists(const std::string& filename) {
        std::ifstream ifile(filename.c_str());
        return (bool)ifile;
    }

    void mainMenu(){
        int key;
        system("cls");
        cout << "\n================= MENU ===================" << endl;
        cout << "1. Quan li lop" << endl;
        cout << "2. Quan li sinh vien" << endl;
        cout << "3. Quan li mon hoc" << endl;
        cout << "4. Quan li diem mon hoc" << endl;
        cout << "0. Exit" << endl;
        while (1){
            cout << "Nhap lua chon: "; cin >> key;

            switch(key){
                case 1: classroomMenu();
                case 2: studentMenu();
                case 3: subjectMenu();
                case 4: scoreMenu();
                case 0: exit(0);
                default:
                    cout << "Lua chon khong phu hop!" << endl;
            }
        }
    }

    void classroomMenu(){
        int key;

        while(1){
            system("cls");
            cout << "\n=========== QUAN LI LOP HOC =============" << endl;
            cout << "1. Them Lop" << endl;
            cout << "2. Xoa Lop" << endl;
            cout << "3. Chinh sua lop" << endl;
            cout << "4. In danh sach lop theo nam" << endl;
            cout << "5. In danh sach tat ca lop" << endl;
            cout << "0. Menu Chinh" << endl;
            cout << "Nhap lua chon: "; cin >> key;

            switch(key){
                case 1: addClassroom();
                    getch();
                    break;
                case 2: deleteClassroom();
                    getch();
                    break;
                case 3: editClassroom();
                    getch();
                    break;
                case 4: printByYear();
                    getch();
                    break;
                case 5: system("cls");
					printAllClass();
                    getch();
                    break;
                case 0: mainMenu();
                default:
                    cout << "Lua chon khong phu hop!" << endl;
            }
        }
    }
	 
	
    void printAllClass(){
    	ClassroomNode *min= new ClassroomNode;
    	int vitrimin;
		for (int i = 0; i < size-1 ; i++){
			min= ds.classroom[i];
			
			vitrimin=i;
			
			for (int j= i + 1 ; j < size; j++){
					if(ds.classroom[j]->code.compare(min->code) < 0){
						min= ds.classroom[j]; 
						
						vitrimin=j;
				}
			}
				ds.classroom[vitrimin] = ds.classroom[i] ;	
				ds.classroom[i]=min;	
		}

        cout << "======== Danh sach tat ca cac lop ============" << endl;
        for (int i = 0; i < size; i++){
            cout << setw(3) << (i+1) << ". " << setw(5) << "Ma lop: " << setw(10) << ds.classroom[i]->code << " | Ten lop: " << setw(35) << ds.classroom[i]->name << " | Nam hoc : " << ds.classroom[i]->year << endl;
        }
    }

    int isExistClassroom(string code){
        for(int i = 0; i < size; i++){
            if(ds.classroom[i]->code == code)
                return i;
        }

        return -1;
    }

    void addClassroom(){
        string code, name;
        int year;

        while(1){
        	system("cls");
        	printAllClass();
            cout << "\n--- Nhap thong tin lop moi ---" << endl;
            cout << "Ma Lop: ";
            cin.ignore();
            getline(cin, code);
            if(isExistClassroom(code) > -1 ){
            cout << "\n--- Lop da ton tai! ---" << endl;
            return;
			}
            if(code.length() == 1 && code.at(0) == 32){
                cout << "--- Ket thuc nhap lop moi ---" << endl;
                break;
            }
            cout << "Ten Lop: ";
            cin.ignore(0);
            getline(cin, name);
            cout << "Nam hoc: ";
            cin >> year;
			
            addClassroomFunc(code, name, year, 1);
        }

    }

    void addClassroomFunc(string code, string name, int year, int flag){
        if(isExistClassroom(code) > -1 ){
            cout << "\n--- Lop da ton tai! ---" << endl;
            
            getch();
        } else{
			ds.classroom[size]= new ClassroomNode;
            ds.classroom[size]->code = code;
            
            ds.classroom[size]->name = name;
            ds.classroom[size]->year = year;
            ds.classroom[size]->st = NULL;
            size ++;
            writeFile(1);
            cout << "\nThem Lop thanh cong!" << endl;
        }
    }

    void addClassroomFunc(ClassroomNode *newClassroom){
        ds.classroom[size] = newClassroom;
        size++;
    }

    void deleteClassroom(){
        string code;
		system("cls");
		printAllClass();
        cout << "Nhap ma Lop: "; 
        cin.ignore();
        getline(cin, code);
        if(code.length() == 1 && code.at(0) == 32 ){
	        cout << "--- Ket thuc xoa lop  ---" << endl;
	        return;
        }
        deleteClassroomFunc(code);
        writeFile(1);
    }

    void deleteClassroomFunc(string code){
        if(isExistClassroom(code) == -1){
            cout << "\nLop khong ton tai! " << endl;
        } else {
            int flag = 0;

            for(int i = 0; i < size; i++){
                if(ds.classroom[i]->code == code){
                    if(i == (size-1)){
                        size --;
                        break;
                    } else {
                        size --;
                        flag = 1;
                    }
                }

                if(flag == 1){
                    ds.classroom[i] = ds.classroom[i+1];
                }
            }
            system("cls");
            cout << "\nXoa lop thanh cong !" << endl;
			printAllClass();
        }
    }
	


    void editClassroom(){
        string code, value;
        int key, year;
        system("cls");
		printAllClass();
        cout << "Nhap ma Lop: "; 
        
        cin.ignore();
        getline(cin, code);
        if(code.length() == 1 && code.at(0) == 32 ){
	        cout << "--- Ket thuc sua lop  ---" << endl;
	        return;
        }
        int Index=isExistClassroom(code);
        
		if(isExistClassroom(code)==-1){
            cout << "\nMa Lop khong ton tai! " << endl;
            return;
        }
        
        ClassroomNode *classroom[Index];


        while (1){
           int Index=isExistClassroom(code);
			ClassroomNode *classroom[Index];
            cout << "\n========== Chon thong tin lop muon chinh sua ==============" << endl;
            cout << "1. Ten lop: " << ds.classroom[Index]->name << endl;
            cout << "2. Nam hoc: " << ds.classroom[Index]->year << endl;
            cout << "0. Tro lai" << endl;
            cout << "Nhap lua chon: " << endl; cin >> key;

            if(key == 1){
                cout << "Nhap ten lop moi: ";
                cin.ignore();
                getline(cin, value);
                transform(value.begin(), value.end(), value.begin(), ::toupper);
                editClassroomFunc(ds.classroom[Index]->code, value, ds.classroom[Index]->year, ds.classroom[Index]->st);
            }

            if (key == 2){
                cout << "Nhap nam hoc: "; cin >> year;
                editClassroomFunc(ds.classroom[Index]->code, ds.classroom[Index]->name, year, ds.classroom[Index]->st);
            }
			system("cls");
			printAllClass();
            if(key == 0) classroomMenu();
        }
    }
	
	ClassroomNode *getClassroom(string code){
        for(int i = 0; i < size; i++){
            if(ds.classroom[i]->code == code){
                return ds.classroom[i];
            }
        }
        ClassroomNode *a;
        return a;
    }
	
    void editClassroomFunc(string code, string name, int year, StudentNode *st){
    	ClassroomNode *newClassroom = getClassroom(code);
        newClassroom->name = name;
        newClassroom->year = year;
        deleteClassroomFunc(code);
        addClassroomFunc(newClassroom);
        writeFile(1);
    }

    void printByYear(){
        int year;
        cout << "Nhap nam hoc: "; cin >> year;
        cout << "\nDanh sach lop tai nam: " << year << endl;

        for(int i = 0; i < size; i++){
            if(ds.classroom[i]->year == year){
              	cout << "=================================================" << endl;
                cout <<  i + 1 << ". Ma Lop: " << setw(10) << ds.classroom[i]->code << " | ";
                cout << "Ten Lop: " << setw(30)  << ds.classroom[i]->name << " | ";
                cout << "Nam: "<< ds.classroom[i]->year << endl;
            }
        }
    }

    /*
     * Menu sinh vien
     */
    void studentMenu(){
        int key;
		string classroomCode;
        while (1){
            system("cls");
            cout << "\n\n============ Quan li sinh vien ===========" << endl;
            cout << "1. Nhap sinh vien" << endl;
            cout << "2. Xoa sinh vien" << endl;
            cout << "3. Chinh sua thong tin sinh vien" << endl;
            cout << "4. In danh sach sinh vien trong lop" << endl;
            cout << "0. Menu chinh" << endl;

            cout << "\nNhap lua chon: ";
            cin >> key;
            switch(key){
                case 1: addStudent();
                    getch();
                    break;
                case 2: deleteStudent();
                    getch();
                    break;
                case 3: editStudent();
                    getch();
                    break;
                case 4: 
               		system("cls");
					printAllClass();
                	cout << "Nhap ma Lop: "; 
					cin.ignore();
			        getline(cin, classroomCode);
			        if(classroomCode.length() == 1 && classroomCode.at(0) == 32 ){
				    	cout << "--- Ket thuc in  ---" << endl;
				    	getch();
				        break;
			        }
					system("cls");
					printAllStudent(classroomCode);
                    getch();
                    break;
                case 0: mainMenu();
            }
        }
    }

    void addStudent(){
        string classroomCode, code, firstName, lastName, gender, phone;
        while(1){
    		system("cls");
        	printAllClass();
            cout << "\nNhap thong tin sinh vien" << endl;
            
            cout << "Ma lop muon them sinh vien: "; 
            cin.ignore();
            getline(cin, classroomCode);
            if(classroomCode.length() == 1 && classroomCode.at(0) == 32 ){
	        cout << "--- Ket thuc them sinh vien  ---" << endl;
	        return;
            }
            system("cls");
            printAllStudent(classroomCode);
            int index = isExistClassroom(classroomCode);
            if(index == -1){
                cout << "--- Ma lop khong ton tai ---" << endl;
                break;
            }
            cout << "Ma sv: ";
            cin.ignore(0);
            getline(cin, code);
            for(int l = 0; l < size; l++){
            if(isExistStudent(ds.classroom[l]->code, code) == 1){
                cout << "\n--- Sinh vien da ton tai! ---" << endl;
                return;
            }
        }

            if(code.length() == 1 && code.at(0) == 32){
                cout << "--- Ket thuc nhap sinh vien ---" << endl;
                break;
            }
            cout << "Ho: "; 
			cin.ignore(0);
            getline(cin, firstName);
            transform(firstName.begin(), firstName.end(), firstName.begin(), ::toupper);
            cout << "Ten: ";
            cin.ignore(0);
            getline(cin, lastName);
            transform(lastName.begin(), lastName.end(), lastName.begin(), ::toupper);
            while(1){
			cout << "Gioi tinh: ";
            cin.ignore(0);
            getline(cin, gender);
            transform(gender.begin(), gender.end(), gender.begin(), ::toupper);
            if (gender.compare("NAM")!=0){
            	if (gender.compare("NU")!=0){
            		cout << "Chi duoc nhap nam va nu!!!" << endl;
					}
				else break;
				cout << "Chi duoc nhap nam va nu!!!" << endl;
				}
			else break;
			}
            cout << "So DT: "; 
            cin.ignore(0);
            getline(cin, phone);
            addStudentFunc(classroomCode, code, firstName, lastName, gender, phone, 1);
            writeFile(2);
        }
    }

    int isExistStudent(string classroomCode, string studentCode){
        int classroomIndex = isExistClassroom(classroomCode);

        if(ds.classroom[classroomIndex]->st == NULL){
            return 0;
        } else{
            StudentNode *currentNode = ds.classroom[classroomIndex]->st;
            while (currentNode != NULL){
                if(currentNode->code == studentCode)
                    return 1;
                currentNode = currentNode->next;
            }
// han che: tat ung dung thi mang stCodeArr se bi xoa, lan sau nhap lai sinh vien trung nhau chi bao loi ? 
//            for(int k = 0; k < stLength; k++){
//                if(stCodeArr[k] == studentCode){
//                    return 1;
//                }
//            }
            return 0;
        }
    }

    StudentNode* createStudentNode(string code, string firstName, string lastName, string gender, string phoneNumber){
        StudentNode *newNode = new StudentNode;
        newNode->code = code;
        newNode->firstName = firstName;
        newNode->lastName = lastName;
        newNode->gender = gender;
        newNode->phoneNumber = phoneNumber;
        newNode->next = NULL;
        newNode->scoreNode = NULL;

        return newNode;
    }

    void addStudentFunc(string classroomCode, string code, string firstName, string lastName, string gender, string phoneNumber, int flag){
        int classroomIndex = isExistClassroom(classroomCode);

        StudentNode *newNode = createStudentNode(code, firstName, lastName, gender, phoneNumber);
        if(isExistClassroom(classroomCode) == -1 ) {
            cout << "\nLop khong ton tai! ";
            return;
        }

        for(int l = 0; l < size; l++){
            if(isExistStudent(ds.classroom[l]->code, code) == 1){
                cout << "\n--- Sinh vien da ton tai! ---" << endl;
                return;
            }
        }

        if(isExistStudent(classroomCode, code) == 1){
            cout << "\n--- Sinh vien da co trong lop! ---" << endl;
        } else{
            StudentNode *currentNode = new StudentNode;
            currentNode = ds.classroom[classroomIndex]->st;
            if(currentNode == NULL){
                ds.classroom[classroomIndex]->st = newNode;
            } else {
                while (currentNode->next != NULL){
                    currentNode = currentNode->next;
                }
                currentNode->next = newNode;
//                stCodeArr[stLength] = code;
//                stLength = stLength + 1;
            }

            cout << "\n--- Them sinh vien thanh cong! --- " << endl;
        }
    }

    void deleteStudent(){
        string classroomCode, stCode;
        system("cls");
		printAllClass();
        cout << "Nhap ma lop: ";
        cin.ignore();
        getline(cin, classroomCode);
        if(classroomCode.length() == 1 && classroomCode.at(0) == 32 ){
	    	cout << "--- Ket thuc xoa sinh vien  ---" << endl;
	        return;
        }
        system("cls");
		printAllStudent(classroomCode);
		if(isExistClassroom(classroomCode) == -1) {
            cout << "\nLop khong ton tai! ";
            return;
        }
        cout << "Nhap ma sv muon xoa: "; 
        cin.ignore(0);
        getline(cin, stCode);
		if(stCode.length() == 1 && stCode.at(0) == 32){
            return;
        }
        deleteStudentFunc(classroomCode, stCode);
        writeFile(2);
        system("cls");
		printAllStudent(classroomCode);
		getch();
    }

    void deleteStudentFunc(string classroomCode, string stCode){
        int classroomIndex = isExistClassroom(classroomCode);

        if(isExistClassroom(classroomCode) == -1) {
            cout << "\nLop khong ton tai! ";
            return;
        }
	
        if(isExistStudent(classroomCode, stCode) == 0){
            cout << "\nSinh vien khong co trong lop! " << endl;
        } else {
            StudentNode *currentNode = ds.classroom[classroomIndex]->st;
            if (currentNode->code == stCode) {
                if(currentNode->next == NULL){
                    ds.classroom[classroomIndex]->st = NULL;
                } else {
                    ds.classroom[classroomIndex]->st = ds.classroom[classroomIndex]->st->next;
                }
            } else {
                StudentNode *beforeCurrent = currentNode;
                while (currentNode != NULL) {
                    if (currentNode->code == stCode) {
                        if (currentNode->next == NULL) {
                            beforeCurrent->next = NULL;
                        } else {
                            beforeCurrent->next = currentNode->next;
                        }
                        break;
                    }
                    beforeCurrent = currentNode;
                    currentNode = currentNode->next;
                }
            }
            cout << "\nXoa sinh vien thanh cong! " << endl;
        }
    }

    StudentNode* getStudent(string classroomCode, string stCode){
        int classroomIndex = isExistClassroom(classroomCode);

        StudentNode *stNode = ds.classroom[classroomIndex]->st;
        while (stNode != NULL){
            if(stNode->code == stCode){
                return stNode;
            }
            stNode = stNode->next;
        }
    }

    void editStudent(){
        string classroomCode, stCode, value;
        int key, year;
        system("cls");
		printAllClass();
        cout << "Nhap ma Lop: "; 
		cin.ignore();
        getline(cin, classroomCode);
        if(classroomCode.length() == 1 && classroomCode.at(0) == 32 ){
	    	cout << "--- Ket thuc chinh sua sinh vien  ---" << endl;
	        return;
        }
        int Index=isExistClassroom(classroomCode);
        if(isExistClassroom(classroomCode) == -1){
            cout << "\nMa Lop khong ton tai! " << endl;
            return;
        }
        ClassroomNode classroom[Index];

        
		system("cls");
		printAllStudent(classroomCode);
		
        cout << "Ma sv muon chinh sua: "; 
        cin >> stCode;

        if(isExistStudent(classroomCode, stCode) == 0){
            cout << "\n Sinh vien khong co trong lop! " << endl;
            return;
        }
		
        while (1){
            StudentNode *stNode = getStudent(classroomCode, stCode);
            cout << "\n========== Nhap lua chon chinh sua thong tin sv ==============" << endl;
            cout << "1. Ho: " << stNode->firstName << endl;
            cout << "2. Ten: " << stNode->lastName  << endl;
            cout << "3. Gioi tinh: " << stNode->gender << endl;
            cout << "4. So DT: " << stNode->phoneNumber << endl;
            cout << "0. Tro lai" << endl;

            cout << "Nhap lua chon: "; cin >> key;
            if(key == 0){
                studentMenu();
            }

            if(key == 1 || key == 2|| key == 3|| key == 4){
                cout << "Nhap gia tri: ";
                cin.ignore();
                getline(cin, value);
                cout << "  ";
                editStudentFunc(classroomCode, stCode, value, key);
                cout << ".";
                writeFile(2);
            }
            system("cls");
			printAllStudent(classroomCode);
        }
    }

    void editStudentFunc(string classroomCode, string stCode, string value, int key ){
        int classroomIndex = isExistClassroom(classroomCode);

        if(isExistClassroom(classroomCode) == -1) {
            cout << "\nLop khong ton tai! ";
            return;
        }

        if(isExistStudent(classroomCode, stCode) == 0){
            cout << "\n Sinh vien khong co trong lop! " << endl;
        } else {
            StudentNode *currentNode = ds.classroom[classroomIndex]->st;

            while(currentNode != NULL){
                if(currentNode->code == stCode){
                        if (key==1){
                        	transform(value.begin(), value.end(), value.begin(), ::toupper);
                            currentNode->firstName = value;
						}
                        if (key==2){
                        	transform(value.begin(), value.end(), value.begin(), ::toupper);
                            currentNode->lastName = value;
						}
                        if (key==3){
                        	transform(value.begin(), value.end(), value.begin(), ::toupper);
                            currentNode->gender = value;
						}
                        if (key==4)
                            currentNode->phoneNumber = value;
                        else return;
                    }
                    currentNode = currentNode-> next;
                }
            }
            cout << "\n Sua thong tin sinh vien thanh cong! " << endl;
        }
    

    void printAllStudent(string classroomCode){
        

        int classroomIndex = isExistClassroom(classroomCode);
        if (classroomIndex == -1) {
            cout << "\n Ma lop khong ton tai! " << endl;
            return;
        }

        StudentNode *p = ds.classroom[classroomIndex]->st;
        if(p == NULL){
            cout << "--- Lop chua co sinh vien ---" << endl;
            return;
        }

        StudentNode *q = new StudentNode;

        while (p->next != NULL){
            q = p -> next;
            while (q != NULL) {
                if((q->lastName).compare(p->lastName) < 0){
                    StudentNode *tmp = new StudentNode;
                    tmp->code = q->code;
                    tmp->firstName = q->firstName;
                    tmp->lastName = q->lastName;
                    tmp->gender = q->gender;
                    tmp->phoneNumber = q->phoneNumber;
                    tmp->scoreNode = q->scoreNode;
                    tmp->next = NULL;

                    q->code = p->code;
                    q->firstName = p->firstName;
                    q->lastName = p->lastName;
                    q->gender = p->gender;
                    q->phoneNumber = p->phoneNumber;
                    q->scoreNode = p->scoreNode;

                    p->code = tmp->code;
                    p->firstName = tmp->firstName;
                    p->lastName = tmp->lastName;
                    p->gender = tmp->gender;
                    p->phoneNumber = tmp->phoneNumber;
                    p->scoreNode = tmp->scoreNode;
                }
                q = q->next;
            }
            p = p->next;
        }

        cout << "Danh sach sinh vien trong lop: " << classroomCode << endl;
        cout << "=========================================================" << endl;
        int count = 1;
        StudentNode *currentNode = ds.classroom[classroomIndex]->st;
        while (currentNode != NULL){
            cout << "Ho va Ten: " << setw(25)  << currentNode->firstName << " "  << setw(11) << currentNode->lastName << " | ";
            cout << "Ma SV: " << setw(14)  << currentNode->code << " | ";
            cout << "Gioi tinh: " << setw(14)  << currentNode->gender << " | ";
            cout << "So DT: " << setw(14)  << currentNode->phoneNumber << endl;
            count ++;
            currentNode = currentNode->next;
        }
    }

/*
MON HOC
*/

    void subjectMenu(){
        int key;

        while (1){
            system("cls");
            cout << "\n=========== QUAN LI MON HOC =============" << endl;
            cout << "1. Them Mon Hoc" << endl;
            cout << "2. Xoa Mon Hoc" << endl;
            cout << "3. Chinh sua Mon Hoc" << endl;
            cout << "4. In danh sach Mon Hoc " << endl;
            cout << "0. Menu Chinh" << endl;

            cout << "Nhap lua chon: "; cin >> key;

            switch (key){
                case 1: addSubject();
                    getch();
                    break;
                case 2: deleteSubject();
                    getch();
                    break;
                case 3: editSubject();
                    getch();
                    break;
                case 4:
                	system("cls");
                    cout << "\n========== Tat ca mon hoc ==========" << endl;
                    printAllSubject(root);
                    getch();
                    break;
                case 0: mainMenu();
            }
        }
    }

    void addSubject(){
        string code, name;
        int STCLT, STCTH;
		system("cls");
		printAllSubject(root);
        cout <<"Nhap ma mon hoc: "; 
        cin.ignore();
        getline(cin, code);
        if(code.length() == 1 && code.at(0) == 32 ){
	    	cout << "--- Ket thuc them mon  ---" << endl;
	        return;
        }
        if(isExistSubject(code) == 1){
            cout << "Ma mon hoc da ton tai!" << endl;
            return;
        }

        cout <<"Nhap ten mon hoc: ";
        cin.ignore(0);
        getline(cin, name);
        transform(name.begin(), name.end(), name.begin(), ::toupper);
        cout << "Nhap STCLT: "; cin >> STCLT;
        cout << "Nhap STCTH: "; cin >> STCTH;

        addSubjectFunc(code, name, STCLT, STCTH, 1);
        writeFile(3);
        system("cls");
        printAllSubject(root);
    }

    SubjectNode* createSubject(string code, string name, int numberOfLearn, int numberOfDo){
        SubjectNode *newNode = new SubjectNode;
        newNode->code = code;
        newNode->name = name;
        newNode->numberOfLearn = numberOfLearn;
        newNode->numberOfDo = numberOfDo;
        newNode->left = newNode->right = NULL;

        return newNode;
    }

    int isExistSubject(string code){
        SubjectNode *p = root;
        while (p != NULL){
            if(p->code == code){
                return 1;
            }
            if(p->code.compare(code) < 0) {
                p = p->right;
            }
            else if(p->code.compare(code) > 0) {
                p = p->left;
            }
        }
        return 0;
    }

//    int isExistSubjectByName(string name){
//
//        SubjectNode *p = root;
//        while (p != NULL){
//            if(p->name == name){
//                return 1;
//            }
//            if(p->code.compare(name) < 0) {
//                p = p->right;
//                continue;
//            }
//            if(p->code.compare(name) > 0) {
//                p = p->left;
//            }
//        }
//        return 0;
//    }

    void addSubjectFunc(string code, string name, int STCLT, int STCTH, int flag){
        SubjectNode *newNode = createSubject(code, name, STCLT, STCTH);

        if(isExistSubject(code) == 1 /*|| isExistSubjectByName(name) == 1*/){
            cout << "\n--- Mon hoc da ton tai! ---" << endl;
            return;
        }

        if(root == NULL){
            root = newNode;
            cout << "\n--- Them mon hoc thanh cong! ---" << endl;
            return;
        }

        SubjectNode *currentNode = root;
        SubjectNode *parentNode = NULL;
        while (1){
            parentNode = currentNode;

            if(currentNode->code.compare(code) > 0){
                currentNode = currentNode->left;

                if(currentNode == NULL){
                    parentNode->left = newNode;
                    cout << "\n--- Them mon hoc thanh cong! ---" << endl;
                    return;
                }
            } 
			 if(currentNode->code.compare(code) < 0){
                currentNode = currentNode->right;
                if(currentNode == NULL){
                    parentNode->right = newNode;
                    cout << "\n--- Them mon hoc thanh cong! ---" << endl;
                    return;
                }
            }
        }
    }

    void deleteSubject(){
        string code;
        system("cls");
        printAllSubject(root);
        cout << "Nhap ma mon hoc: ";
        cin.ignore();
        getline(cin, code);
        if(code.length() == 1 && code.at(0) == 32 ){
	    	cout << "--- Ket thuc xoa mon ---" << endl;
	        return;
        }
        if(isExistSubject(code) == 0){
            cout << "\nMon hoc khong ton tai! " << endl;
            return;
        }
        root = deleteSubjectFunc(root, code);
        writeFile(3);
        system("cls");
        cout << "\nXoa mon hoc thanh cong! " << endl;
        printAllSubject(root);
        getch();
    }

    SubjectNode* minValue(SubjectNode *root){
        SubjectNode *newNode = new SubjectNode;
        newNode->code = root->code;
        newNode->name = root->name;
        newNode->numberOfLearn = root->numberOfLearn;
        newNode->numberOfDo = root->numberOfDo;

        while (root->left != NULL){
            newNode->code = root->left->code;
            newNode->name = root->left->name;
            newNode->numberOfLearn = root->left->numberOfLearn;
            newNode->numberOfDo = root->left->numberOfDo;

            root = root->left;
        }

        return newNode;
    }

    SubjectNode* deleteSubjectFunc(SubjectNode *root, string code){
        if (root == NULL) return root;

        if(root->code.compare(code) > 0)
            root->left = deleteSubjectFunc(root->left, code);
        else if(root->code.compare(code) < 0) {
            root->right = deleteSubjectFunc(root->right, code);
        } else{
            if(root->left == NULL)
                return root->right;
            else if(root->right == NULL)
                return root->left;

            SubjectNode *tmp = minValue(root->right);
            root->code = tmp->code;
            root->name = tmp->name;
            root->numberOfLearn = tmp->numberOfLearn;
            root->numberOfDo = tmp->numberOfDo;

            root->right = deleteSubjectFunc(root->right, code);
        }

        return  root;
    }

    void editSubject(){
        string value, code;
        int key;

		system("cls");
        printAllSubject(root);
        cout << "Nhap ma mon hoc: ";
        cin.ignore();
        getline(cin, code);
        if(code.length() == 1 && code.at(0) == 32 ){
	    	cout << "--- Ket thuc sua mon ---" << endl;
	        return;
        }
        if(isExistSubject(code) == 0){
            cout << "\n Mon hoc khong ton tai! " << endl;
            return;
        }

        while (1){
            cout << "\n ==== Lua chon thong tin chinh sua thong tin mon hoc =====" << endl;
            cout << "1. Ten mon hoc" << endl;
            cout << "2. STCLT" << endl;
            cout << "3. STCTH" << endl;
            cout << "0. Tro lai" << endl;

            cout << "Nhap lua chon: ";
            cin >> key;
            if(key == 0){
                subjectMenu();
            }

            if(key == 1){
                cout << "Nhap gia tri: ";
                cin.ignore();
        		getline(cin, value);
                editSubjectFunc(code, value, 1);
                writeFile(3);
            }
            
            if(key == 2){
                cout << "Nhap gia tri: ";
                cin.ignore();
        		getline(cin, value);
                editSubjectFunc(code, value, 2);
                writeFile(3);
            }
            
            if(key == 3){
                cout << "Nhap gia tri: ";
        		cin.ignore();
        		getline(cin, value);
                editSubjectFunc(code, value, 3);
                writeFile(3);
            }
            
            system("cls");
        	printAllSubject(root);
        }
    }

    void editSubjectFunc(string Code, string value, int key){
        SubjectNode *p = root;
	
        while (p != NULL){
            if(p->code == Code){
                    if (key == 1){
                    	transform(value.begin(), value.end(), value.begin(), ::toupper);
                        p->name = value;
					}
                    if (key == 2)
                        p->numberOfLearn = atoi(value.c_str());
                    if (key == 3)
                        p->numberOfDo = atoi(value.c_str());
                cout << "Chinh sua mon hoc thanh cong!!!" << endl;
                return;
            }
            if(p->code.compare(Code) > 0){
                p = p->left;
            }
            if(p->code.compare(Code) < 0){
                p = p->right;
            }
        }
        system("cls");
        printAllSubject(root);
    }

    void printAllSubject(SubjectNode *root){
        if(root != NULL){
            printAllSubject(root->left);
            cout << "Ten mon hoc: " << setw(35) << root->name << " | ";
            cout << "Ma mon hoc: " << setw(15) << root->code << " | ";
            cout << "STCLT: " << setw(2) << root->numberOfLearn << " | ";
            cout << "STCTH: " << setw(2) << root->numberOfDo << endl;
            cout << "-------------------------------------------------------------------------------------------------------" << endl ;
            printAllSubject(root->right);
        }
    }

    //Diem
    void scoreMenu(){
        int key;

        while (1){
            system("cls");
            cout << "\n ======== Quan li diem ========" << endl;
            cout << "1. Nhap va chinh sua diem" << endl;
            cout << "2. In diem" << endl;
            cout << "3. In diem trung binh" << endl;
            cout << "4. In diem tong ket" << endl;
            cout << "0. Tro lai" << endl;

            cout << "Nhap lua chon: " << endl;
            cin >> key;
            switch (key){
                case 1: addScore();
                    getch();
                    break;
                case 2: printScore();
                    getch();
                    break;
                case 3: printAVG();
                    getch();
                    break;
                case 4: printScoreYear();
                    getch();
                    break;
                case 0: mainMenu();
            }
        }
    }

    void addScore(){
        string subjectCode, classroomCode, stCode;
        int index, key;
        double score;
		system("cls");
		printAllClass();
        cout << "Nhap ma lop hoc:";
        cin.ignore();
        getline(cin, classroomCode);
        
        if(classroomCode.length() == 1 && classroomCode.at(0) == 32 ){
	    	cout << "--- Ket thuc nhap diem ---" << endl;
	        return;
        }
        
        if(isExistClassroom(classroomCode) == -1){
            cout << "--- Ma lop hoc khong ton tai ---" << endl;
            cout << "Ket thuc nhap diem!!!" << endl;
            return;
        }

		system("cls");
		printAllSubject(root);
		cout << endl << endl;
        cout << "Nhap ma mon hoc muon nhap diem: "; cin >> subjectCode;
        system("cls");
        cout << "Nhap lan thi: "; cin >> index;

        SubjectNode *subjectNode = getSubject(subjectCode);
        if(subjectNode == NULL){
            cout << "--- Mon hoc khong ton tai ---" << endl;
            cout << "\n--- Nhap lai ---" << endl;
            return;
        }

        addScoreFunc(classroomCode, subjectCode, index);
        while (1){
            printAllStudentJoinExam(classroomCode, subjectCode, index, 0);
            cout << "Ban co muon chinh sua diem: " << endl;
            cout << "1. Co" << endl << "2. Khong" << endl;

            cout << "Nhap lua chon: "; cin >> key;
            if(key == 2) break;
            if(key == 1) {
                cout << "Nhap Ma sv: "; cin >> stCode;
                cout << "Nhap diem: "; cin >> score;
                editScoreFunc(stCode, subjectCode, score, index);
            }
        }
    }

    void editScoreFunc(string studentCode, string subjectCode, float score, int indexExam){
        if(isExistStudent(ds.classroom[saveClassroomIndex]->code, studentCode) == 0){
            cout << "--- Sinh vien khong ton tai ---" << endl;
            return;
        }

        if(isExistSubject(subjectCode) == 0) {
            cout << "--- Mon hoc khong ton tai ---" << endl;
            return;
        }

        StudentNode *currentNode = ds.classroom[saveClassroomIndex]->st;
        while(currentNode != NULL){
            if(currentNode->code == studentCode){
                ScoreNode *p = currentNode->scoreNode;
                while (p!=NULL){
                    if(p->code == subjectCode && p->index == indexExam){
                        p->score = score;
                        break;
                    }
                    p = p->next;
                }
                break;
            }
            currentNode = currentNode->next;
        }

        writeFile(4);
    }

    void addScoreFunc(string classroomCode, string subjectCode, int indexExam){
        int classroomIndex = isExistClassroom(classroomCode);
        if(classroomIndex == -1){
            cout << "\nMa lop khong ton tai! " << endl;
            return;
        }

        StudentNode *currentNode = ds.classroom[classroomIndex]->st;
        if(currentNode == NULL) {
            cout << "--- Khong ton tai sinh vien ---" << endl;
            return;
        }

        while (currentNode != NULL){
            ScoreNode *scoreNode = new ScoreNode;
            scoreNode->code = subjectCode;
            scoreNode->index = indexExam;
            scoreNode->score = 0;
            scoreNode->next = NULL;

            if(currentNode->scoreNode == NULL){
                currentNode->scoreNode = scoreNode; // dau danh sach
            } else {
                ScoreNode *p = currentNode->scoreNode;
                while (p != NULL){
                    if(p->code == subjectCode && p->index == indexExam){ // da ton tai node
                        break;
                    }

                    if(p->next == NULL){ // cuoi danh sach
                        p->next = scoreNode;
                        break;
                    }
                    p = p->next;
                }
            }

            currentNode = currentNode->next;
        }
        writeFile(4);
    }

    SubjectNode* getSubject(string code){
        if(root == NULL)
            return root;

        SubjectNode *p = root;
        while (p != NULL){
            if(p->code.compare(code) == 0){
                return p;
            }
            if(p->code.compare(code) > 0){
                p = p->left;
                continue;
            }
            if(p->code.compare(code) < 0)
                p = p->right;
        }
    }

    int saveClassroomIndex;
    
    void printAllStudentJoinExam(string classroomCode, string subjectCode, int indexExam, int flag){
        int classroomIndex = isExistClassroom(classroomCode);
        saveClassroomIndex = classroomIndex;
        StudentNode *currentNode = ds.classroom[classroomIndex]->st;
        int index = 1;

        ofstream outfile;
        if(flag == 0){
            outfile.open("score.txt");
        }else{
            outfile.open("AVG.txt");
        }

        if(flag == 1){
            cout << "\n==========================================================" << endl;
            cout << "            BANG DIEM MON HOC" << endl;
            cout << "      Lop: " << classroomCode << "      Lan thi: " << indexExam << endl;
            cout << "      Mon hoc: " << getSubject(subjectCode)->name << endl;

        }
        cout << setw(2) << "\nSTT" << setw(7) << setfill(' ') << "MASV" << setw(10)  << "HO" << setw(10) << setfill(' ')  << "TEN" << setw(10) << setfill(' ')  << "DIEM" << endl;
        outfile << setw(2) << "\nSTT" << setw(7) << setfill(' ') << "MASV" << setw(10)  << "HO" << setw(10) << setfill(' ')  << "TEN" << setw(10) << setfill(' ')  << "DIEM" << endl;

        while (currentNode != NULL){
            ScoreNode *p = currentNode->scoreNode;
            while (p!=NULL){
                if(p->code == subjectCode && p->index == indexExam){
                    cout << setw(2) << index << setfill(' ') << " " << currentNode->code << setw(11) <<  setfill(' ') << currentNode->firstName << setw(11) << setfill(' ') << currentNode->lastName << setw(8) << setfill(' ');
                    outfile << setw(2) << index << setfill(' ') << " " << currentNode->code << setw(11) << setfill(' ') << currentNode->firstName << setw(11) << setfill(' ') << currentNode->lastName << setw(8) << setfill(' ');
                    if(p->score > 0) {
                        cout << p->score << endl;
                        outfile << p->score << endl;
                        outfile.close();
                    } else {
                        cout << setw(5) << setfill(' ') << "  chua_co" << endl;
                        outfile << setw(5) << setfill(' ') << " chua_co" << endl;
                        outfile.close();
                    }
                }
                p = p->next;
            }
            index ++;
            currentNode = currentNode->next;
        }
    }

    void printScore(){
        string maLop, mamh, masv;
        int lanthi, key;
        float score;
		system("cls");
		printAllClass();
        cout << "Ma lop: "; 
        cin.ignore();
        getline(cin, maLop);
        
        if(maLop.length() == 1 && maLop.at(0) == 32 ){
	    	cout << "--- Ket thuc in diem ---" << endl;
	        return;
        }
        
        if(isExistClassroom(maLop) == -1) {
            cout << "--- Ma lop khong ton tai ---" << endl;
            return;
        }
		system("cls");
		printAllSubject(root);
        cout << "Ma mon hoc: "; cin >> mamh;
        if(isExistSubject(mamh) == 0) {
            cout << "--- Ma mon hoc khong ton tai ---" << endl;
            return;
        }

        cout << "Lan thi: "; cin >> lanthi;
        system("cls");
        printAllStudentJoinExam(maLop, mamh, lanthi, 1);
    }

    void printAVG(){
        string malop;
        int year;
		system("cls");
		printAllClass();
        cout << "Nhap ma lop: "; 
        cin.ignore();
        getline(cin, malop);
        
        if(malop.length() == 1 && malop.at(0) == 32 ){
	    	cout << "--- Ket thuc in diem ---" << endl;
	        return;
        }
        
        if(isExistClassroom(malop) == -1){
            cout << "--- Ma lop khong ton tai ---" << endl;
            return;
        }
        cout << "Nam hoc: "; cin >> year;
        printAvgFunc(malop, year);
    }

    void printAvgFunc(string classroomCode, int year){
        ofstream outfile;
        outfile.open("AVG.txt");

        int classroomIndex = isExistClassroom(classroomCode);
        int index = 1;
        if(ds.classroom[classroomIndex]->year != year){
            cout << "Lop khong co trong nam" << year << endl;
        } else {
        	system("cls");
            cout << "\n======================================================================================" << endl;
            cout << "BANG THONG KE DIEM TRUNG BINH KHOA HOC" << endl;
            outfile << "BANG THONG KE DIEM TRUNG BINH KHOA HOC" << endl;
            cout << "Lop: " << ds.classroom[classroomIndex]->name << "    Nam nhap hoc: " << year << endl;
            outfile << "Lop: " << ds.classroom[classroomIndex]->name << "    Nam nhap hoc: " << year << endl;
            cout << endl;
            outfile << endl;
            cout << "STT" << setw(7) << setfill(' ') <<"         MASV" << setw(7) << setfill(' ') << "          HO       " << setw(7) << setfill(' ') << "        TEN       "  << "  DiemTB   "  << endl;
            outfile << "STT" << setw(7) << setfill(' ') <<"        MASV" << setw(7) << setfill(' ') << "          HO     " << setw(7) << setfill(' ') << "        TEN       "  << "  DiemTB   " << endl;

            StudentNode *currentNode = ds.classroom[classroomIndex]->st;
            while (currentNode != NULL){
                int tc = 0;
                float total = 0;
                ScoreNode *tmp = currentNode->scoreNode;
                // Lay gia tri diem cao nhat tai 1 lan thi

                float diem[1000];
                string maMon[1000];
                int diemSize = 0;

                while (tmp != NULL){
                    int aa = isContainSubCode(tmp->code, maMon, diemSize);
                    if(aa > -1){ // maMon[k] khong trung ma mon voi tmp->code
                        if(tmp->score > diem[aa]){
                            diem[aa] = tmp->score;
                        }
                        tmp = tmp->next;
                        continue;
                    }

                    diem[diemSize] = tmp->score;
                    maMon[diemSize] = tmp->code;
                    diemSize ++;
                    tmp = tmp->next;
                }

                for(int k = 0; k < diemSize; k++){
                    total += diem[k];
                }
                tc = diemSize;
                cout << index << setw(15) << setfill(' ') << currentNode->code << setw(15) << setfill(' ')<< currentNode->firstName << setw(15) << setfill(' ') << currentNode->lastName << setw(15) << setfill(' ') << setprecision (5) << (float)total/tc << endl;
                outfile << index << setw(15) << setfill(' ') << currentNode->code << setw(15) << setfill(' ')<< currentNode->firstName << setw(15) << setfill(' ') << currentNode->lastName << setw(15) << setfill(' ') << setprecision (5) << (float)total/tc << endl;
                currentNode = currentNode->next;
                index++;
            }
            outfile.close();
        }
    }

    int isContainSubCode(string code, string maMon[1000], int diemSize){
        for(int k = 0; k < diemSize; k++){
            if(code == maMon[k]){
                return k;
            }
        }

        return -1;
    }

    int getTcByCode(string code){
        if(root == NULL)
            return 0;

        SubjectNode *p = root;
        while (p != NULL){
            if(p->code.compare(code) == 0){
                return p->numberOfLearn;
            }
            if(p->code.compare(code) > 0){
                p = p->left;
                continue;
            }
            if(p->code.compare(code) < 0)
                p = p->right;
        }
    }

    void printScoreYear(){
        string classCode;
        int year;
        ofstream outfile;
        outfile.open("tongket.txt");
		system("cls");
		printAllClass();
        cout << "Nhap ma lop: "; cin >> classCode;
        if(isExistClassroom(classCode) == -1) {
            cout << "--- Ma lop khong ton tai ---" << endl;
            return;
        }
        cout << "Nhap nam: "; cin >> year;

        int classroomIndex = isExistClassroom(classCode);
        if(ds.classroom[classroomIndex]->year != year){
            cout << "\nKhong ton tai lop hoc nay trong nam: " << year << endl;
            return;
        }
		system("cls");
        StudentNode *stNode = ds.classroom[classroomIndex]->st;
        int index = 1;

        cout << "\n\nBANG DIEM TONG KET" << endl;
        outfile << "\n\nBANG DIEM TONG KET" << endl;
        cout << "Lop: " << ds.classroom[classroomIndex]->code << " Nam nhap hoc: " << year << endl << endl;
        outfile << "Lop: " << ds.classroom[classroomIndex]->code << " Nam nhap hoc: " << year << endl << endl;
        cout << "STT "  << setw(10) << "Masv " << setw(36) << "          HoTen         ";
        outfile << "STT " << setw(10) << "Masv " << setw(36) << "           HoTen         ";

        string tmpScore[1000];
        int tmpSize = 0;

        string tmpScore2[1000];
        int tmpSize2 = 0;

        ScoreNode *scoreNode = stNode->scoreNode;
        int flag2 = 0;
        while (scoreNode != NULL) {

            for(int e = 0; e < tmpSize2; e++){
                if(tmpScore2[e] == scoreNode->code){
                    scoreNode = scoreNode->next;
                    flag2 = 1;
                    break;
                }
            }
            if(flag2 == 1){
                flag2 = 0;
                continue;
            }
            cout << scoreNode->code << "   " ;
			outfile << scoreNode->code << "   ";

            tmpScore2[tmpSize2] = scoreNode->code;
            tmpSize2 ++;
            scoreNode = scoreNode->next;
        }

        while(stNode != NULL){
            int flag = 0;
            scoreNode = stNode->scoreNode;
            cout << "\n" << index << setw(7) << "    " << setw(8) <<  stNode->code << "  " << setw(30) << stNode->firstName+" "+stNode->lastName;
            outfile << "\n" << index << setw(7) << "    " << setw(8) <<  stNode->code << "  " << setw(30) << stNode->firstName+" "+stNode->lastName;
            while (scoreNode != NULL){
                ScoreNode *p = scoreNode;
                double max = scoreNode->score;

                for(int e = 0; e < tmpSize; e++){
                    if(tmpScore[e] == scoreNode->code){
                        scoreNode = scoreNode->next;
                        flag = 1;
                        break;
                    }
                }
                if(flag == 1){
                    flag = 0;
                    continue;
                }

                tmpScore[tmpSize] = scoreNode->code;
                tmpSize ++;

                while (p != NULL){
                    if(p->score > max && p->code == scoreNode->code){
                        max = p->score;
                    }
                    p = p->next;
                }
                cout << setw(3) << "  " << max << "  " ;
                outfile << setw(3) << "  " << max << "  " ;
                scoreNode = scoreNode->next;
            }

            stNode = stNode->next;
            tmpSize = 0;
        }
    }
};

int main(){
    Classroom classroom ;
    classroom.mainMenu();

    return 0;
}
