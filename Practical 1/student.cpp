#include "student.h"
Student::Student()
    :u(new Utility),no_of_records(u->count(FILE_NAME)),array_length(no_of_records),student(new record[array_length]){
    ifstream fin;
    fin.open(FILE_NAME);
    if(!fin){
        cout<<"Error in opening "<<FILE_NAME<<" file"<<endl;
    }
    string line;
    size_t i{0};
    while(!fin.eof()){
        getline(fin,line);
        u->string_to_record(line,student[i]);
        i++;
    }
}
void Student::display(){
    cout<<setw(10)<<left<<"Roll No"<<setw(20)<<left<<"Name"<<setw(20)<<left<<"Father\'s Name"
        <<setw(15)<<left<<"Date Of Birth"<<setw(8)<<left<<"Branch"<<setw(12)<<left<<"Year of"
        <<setw(12)<<left<<"Year of"<<setw(20)<<left<<"District"<<setw(20)<<left<<"State"
        <<setw(8)<<left<<"PIN"<<"Country"<<endl;
    cout<<setw(10)<<left<<" "<<setw(20)<<left<<" "<<setw(20)<<left<<" "
        <<setw(15)<<left<<" "<<setw(8)<<left<<" "<<setw(12)<<left<<"Admission"
        <<setw(12)<<left<<"Passing(T)*"<<endl;
    cout<<string(150,'-')<<endl;    
    size_t i{};
    for(size_t i{};i<no_of_records;i++)
        u->show(student[i]);
    cout<<"\nNumber of Records: "<<no_of_records<<"\t*T:Tentative"<<endl;
}
void Student::display(vector<record>& r){
    cout<<setw(10)<<left<<"Roll No"<<setw(20)<<left<<"Name"<<setw(20)<<left<<"Father\'s Name"
        <<setw(15)<<left<<"Date Of Birth"<<setw(8)<<left<<"Branch"<<setw(12)<<left<<"Year of"
        <<setw(12)<<left<<"Year of"<<setw(20)<<left<<"District"<<setw(20)<<left<<"State"
        <<setw(8)<<left<<"PIN"<<"Country"<<endl;
    cout<<setw(10)<<left<<" "<<setw(20)<<left<<" "<<setw(20)<<left<<" "
        <<setw(15)<<left<<" "<<setw(8)<<left<<" "<<setw(12)<<left<<"Admission"
        <<setw(12)<<left<<"Passing(T)*"<<endl;
    cout<<string(150,'-')<<endl;    
    size_t i{};
    for(size_t i{};i<r.size();i++)
        u->show(r[i]);
    cout<<"\nNumber of Records: "<<r.size()<<"\t*T:Tentative"<<endl;
}
int Student::is_key(string& rno){
    for(size_t i{}; i<no_of_records;i++){
        if(student[i].roll_no==rno){
            return i;
        }
    }
    return -1;
}
bool Student::valid_rollno(string& rno){
    //format: CO${year_of_admission}${branch}${serial_no}
    if(rno.length()!=7)
        return false;
    if(!(rno[0]=='c'||rno[0]=='C'))
        return false;
    if(!(rno[1]=='o'||rno[1]=='O'))
        return false;      
    {
        string temp{rno.substr(2,5)};
        for(auto c : temp){
            if(!isdigit(c))
                return false;
        }
    }
    {
        int target = (int)rno[4]-48;
        if(!((target==CSE_CODE)||(target==CIVIL_CODE)||(target==ECE_CODE)||(target==MECH_CODE)))
            return false;
    }
    {
        unsigned int temp = ((int)rno[2]-48)*10 +((int)rno[3]-48);
        if(!(temp>=(START_YEAR%100)||temp<=(PRESENT_YEAR%100)))
            return false;
    }
    return true;
}
bool Student::hasSpace(){
    if(no_of_records==array_length)
        return false;
    return true;
}
void Student::createSpace(){
    size_t c{0};
    array_length+=10;
    record* temp_array = new record[array_length];
    for (size_t i {}; i < no_of_records; i++)
        temp_array[i] = student[i];
    record* temp = student;
    student = temp_array;
    temp_array = temp;
    delete []temp_array;
    temp_array = nullptr;
    temp = nullptr;
}
void Student::input(){
    record r;
    cout<<"Enter the Roll no of the student (format: COxxxxx): ";
    do{
        getline(cin,r.roll_no);
        if(!valid_rollno(r.roll_no))
            {cout<<"Invalid Roll No.! Re-enter the Roll No.!"<<endl;continue;}
        else if(is_key(r.roll_no)>=0)
            {cout<<"Roll No. already exists! Re-enter the Roll No.!"<<endl;continue;}
        break;
    }while(true);
    transform(r.roll_no.begin(), r.roll_no.begin()+2,r.roll_no.begin(), ::toupper);      
    if(!hasSpace())
        createSpace();
    cout<<"Enter Student's name : ";
    getline(cin,r.name);
    cout<<"Enter Father's name : ";
    getline(cin,r.father_name);
    cout<<"Enter  Date of Birth (format:dd/mm/yyyy) :"<<endl;
    //getline(cin,r.date_of_birth);
    {
        int date , month , year;
        cout<<"Enter year : ";
        do{
            cin>>year;
            if(year>PRESENT_YEAR-16)
                {cout<<"Invalid Year! Re-Enter"<<endl;continue;}
            break;
        }while(true);
        cout<<"Enter month : ";
        do{
            cin>>month;
            if(month>12 || month<1)
                {cout<<"Invalid Month! Re-Enter"<<endl;continue;}
            break;
        }while(true);
        cout<<"Enter Date : ";
        {
            bool flag = true;
            do{
                cin>>date;
                switch(month){
                    case 4:
                    case 6:
                    case 9:
                    case 11:{
                        if(date>=1&&date<=31)
                            flag=false;
                    }
                    break;
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                    case 8:
                    case 10:
                    case 12:{
                        if(date>=1&&date<=30)
                            flag=false;
                    }
                    break;
                    case 2:{
                        if(u->is_leap_year(year)){
                            if(date>=1&&date<=29)
                                flag=false;
                        }
                        else{
                            if(date>=1&&date<=28)
                            flag=false;
                        }
                    }
                    break;
                }
                if(flag)
                    cout<<"Invalid Date! Re-Enter"<<endl;
            }while(flag);
        }
        ostringstream oss;
        oss<<date<<"/"<<month<<"/"<<year;
        r.date_of_birth = oss.str();
    }
    cin.ignore();
    cout<<"Enter District : ";
    getline(cin,r.district);
    cout<<"Enter State : ";
    getline(cin,r.state);
    cout<<"Enter Country : ";
    getline(cin,r.country);
    cout<<"Enter PIN : ";
    do{
        {
            string temp;
            getline(cin,temp);
            r.pin = stoi(temp);
        }
        if(r.pin<1000000&&r.pin>99999)
            break;
        cout<<"Invalid PIN! Re-enter the PIN!"<<endl;
    }while(true);
    {
        int target = (int)r.roll_no[4]-48;
        switch (target)
        {
            case CSE_CODE:
                r.branch= "CSE";
            break;
            case ECE_CODE:
                r.branch= "ECE";
            break;
            case CIVIL_CODE:
                r.branch= "CIVIL";
            break;
            case MECH_CODE:
                r.branch= "MECH";
            break;
        }
    }
    {
        unsigned int temp = ((int)r.roll_no[2]-48)*10 +((int)r.roll_no[3]-48);
        if(temp <= PRESENT_YEAR%100){
            r.year_of_admission = 2000+ temp;
            r.year_of_passing = r.year_of_admission + 5;
        }
        else{
            r.year_of_admission = 1900+ temp;
            r.year_of_passing = r.year_of_admission + 5;
        }
    }
    u->add_in_file(r);
    student[no_of_records]= r;
    no_of_records++;
}
void Student::update(){
    string rno;
    int index;
    cout<<"Enter the Roll no of the student whose record is to be updated(format: COxxxxx): ";
    do{
        getline(cin,rno);
        index = is_key(rno);
        if(!valid_rollno(rno))
            {cout<<"Invalid Roll No.! Re-enter the Roll No.!"<<endl;continue;}
        else if(index==-1)
            {cout<<"Roll No. doesn't exist! Re-enter the Roll No.!"<<endl;continue;}
        break;
    }while(true);
    bool flag {true};
    do{
        cout<<"Enter Field you want to update : "<<endl;
        cout<<"1. Student Name\n2. Father's Name\n3. Year of Passing\n4. Branch\n5. District\n6. State\n7. Country\n8. PIN\n9. Exit"<<endl;
        switch(getch()){
            case 49://name
            {
                cout<<"Enter new name : "<<endl;
                getline(cin,student[index].name);
                cout<<"\nName updated successfully to : "<<student[index].name;
            }
            break;
            case 50://father's name
            {
                cout<<"Enter new father's name : "<<endl;
                getline(cin,student[index].father_name);
                cout<<"\nFather's name updated successfully to : "<<student[index].father_name;
            }
            break;
            case 51://year of passing
            {
                do{
                    cout<<"Enter new year of passing : "<<endl;
                    string temp;
                    getline(cin,temp);
                    if(stoi(temp)<student[index].year_of_admission){
                        cout<<"Invalid data! Re-enter"<<endl;
                        continue;
                    }
                    cout<<"\nYear of Passing updated successfully to : "<<student[index].year_of_passing;
                    break;
                }while(true);
            }
            break;
            case 52://branch
            {
                cout<<"Select the branch : \n1.CSE\t2.ECE\n3.MECH\t4.CIVIL"<<endl;
                bool flag = true;
                do{
                    switch(getch()){
                        case 49:
                            {flag = false;student[index].branch="CSE"; student[index].roll_no[4] = CSE_CODE+48;}
                        break;
                        case 50:
                            {flag = false;student[index].branch="ECE"; student[index].roll_no[4] = ECE_CODE+48;}
                        break;
                        case 51:
                            {flag = false;student[index].branch="MECH"; student[index].roll_no[4] = MECH_CODE+48;}
                        break;
                        case 52:
                            {flag = false;student[index].branch="CIVIL"; student[index].roll_no[4] = CIVIL_CODE+48;}
                        break;
                    }
                }while(flag);
                cout<<"\nYear of branch updated successfully to : "<<student[index].branch;
                break;
            }
            case 53://district
            {
                cout<<"Enter new district : "<<endl;
                getline(cin,student[index].district);
                cout<<"\nDistrict updated successfully to : "<<student[index].father_name;
            }
            break;cout<<"Enter Field you want to update : "<<endl;
            case 54://state
            {
                cout<<"Enter new state : "<<endl;
                getline(cin,student[index].state);
                cout<<"\nState updated successfully to : "<<student[index].state;
            }
            break;
            case 55://country
            {
                cout<<"Enter new country : "<<endl;
                getline(cin,student[index].country);
                cout<<"\nCountry updated successfully to : "<<student[index].country;
            }
            break;
            case 56://pin
            {
                cout<<"Enter new PIN : "<<endl;
                do{
                    string temp;
                    getline(cin,temp);
                    if(stoi(temp)<1000000&&stoi(temp)>99999)
                        break;
                    cout<<"Invalid PIN! Re-enter the PIN!"<<endl;
                }while(true);
                cout<<"\nPIN updated successfully to : "<<student[index].pin;
            }
            break;
            case 57://exit
                flag = false;
            break;
        }
        cout<<"\nPress any key to continue......"<<endl;
        getch();
        system("CLS");
    }while(flag);
    u->write_file(student,no_of_records);
}
void Student::remove(){
    string rno;
    int index;
    cout<<"Enter the Roll no of the student whose record is to be deleted(format: COxxxxx): ";
    do{
        getline(cin,rno);
        index = is_key(rno);
        if(!valid_rollno(rno))
            {cout<<"Invalid Roll No.! Re-enter the Roll No.!"<<endl;continue;}
        else if(index==-1)
            {cout<<"Roll No. doesn't exist! Re-enter the Roll No.!"<<endl;continue;}
        break;
    }while(true);
    array_length=no_of_records-1;
    record* temp_array = new record[array_length];
    
    for(size_t i{}, j{};j<array_length;i++,j++){
        if(i==index)
            i++;
        temp_array[j] = student[i];
    }
    u->write_file(temp_array,array_length);
    {
        record* temp = student;
        student = temp_array;
        temp_array = temp;
        delete []temp_array;
        temp_array = nullptr;
        temp=nullptr;
    }
    no_of_records--; 
}
void Student::generate_report(){
    bool flag = true;
    do{
        system("CLS");
        cout<<"Generate report on the basis of :\n1.Common Name\n2.Common District\n3.Common State\n4.Exit"<<endl;
        switch(getch()){
            case 49:{
                string name;
                cout<<"\nEnter name to search : ";
                getline(cin,name);
                vector<record> v;
                for(size_t i{}; i < no_of_records; i++){
                    if (name==student[i].name){
                        v.push_back(student[i]);
                    }
                }
                cout<<"\nGENERATED REPORT :\n"<<endl;
                display(v);
                cout<<"Press any key to continue to the report generation menu......"<<endl;
                getch();
            }
            break;
            case 50:{
                string district;
                cout<<"\nEnter district to search : ";
                getline(cin,district);
                vector<record> v;
                for(size_t i{}; i < no_of_records; i++){
                    if (district==student[i].district){
                        v.push_back(student[i]);
                    }
                }
                cout<<"\nGENERATED REPORT :\n"<<endl;
                display(v);
                cout<<"Press any key to continue to the report generation menu......"<<endl;
                getch();
            }
            break;
            case 51:{
                string state;
                cout<<"\nEnter state to search : ";
                getline(cin,state);
                vector<record> v;
                for(size_t i{}; i < no_of_records; i++){
                    if (state==student[i].state){
                        v.push_back(student[i]);
                    }
                }
                cout<<"\nGENERATED REPORT :\n"<<endl;
                display(v);
                cout<<"Press any key to continue to the report generation menu......"<<endl;
                getch();
            }
            break;
            case 52:
                flag = false;
            break;
        }
    }while(flag);
}
Student::~Student(){
    delete []student;
    student = nullptr;
    delete u;
    u = nullptr;
}