#include "utility.h"
void Utility::string_to_record(string& line,record& r){   
    string temp;
    istringstream iss(line);
    getline(iss,r.roll_no,',');
    getline(iss,r.name,',');
    getline(iss,r.father_name,',');
    getline(iss,r.date_of_birth,',');
    getline(iss,r.branch,',');
    getline(iss,temp,',');
    r.year_of_admission = stoi(temp);
    getline(iss,temp,',');
    r.year_of_passing = stoi(temp);
    getline(iss,r.district,',');
    getline(iss,r.state,',');
    getline(iss,temp,',');
    r.pin = stoi(temp);
    getline(iss,r.country,',');
}
size_t Utility::count(const string& file_name){
    ifstream fin;
    fin.open(file_name);
    if(!fin){
        cout<<"Error in opening "<<file_name<<" file."<<endl;
    }
    size_t c{0};
    string temp;
    while(!fin.eof()){
        getline(fin,temp);
        c++;
    }
    fin.close();
    return c;
}
void Utility::show(const record& r){
    cout<<setw(10)<<left<<r.roll_no<<setw(20)<<left<<r.name<<setw(20)<<left<<r.father_name
        <<setw(15)<<left<<r.date_of_birth<<setw(8)<<left<<r.branch<<setw(12)<<left<<r.year_of_admission
        <<setw(12)<<left<<r.year_of_passing<<setw(20)<<left<<r.district<<setw(20)<<left<<r.state
        <<setw(8)<<left<<r.pin<<r.country<<endl;
}
bool Utility::is_leap_year(const int& year){
    if(year%4==0){
        return (year%100!=0||year%400==0);
    }
    return false;
}
void Utility::add_in_file(const record& r){
    ofstream fout;
    fout.open(FILE_NAME,ios::app);
    if(!fout)
        cout<<"Error in opening "<<FILE_NAME<<endl;
    fout<<"\n"<<r.roll_no<<','<<r.name<<','<<r.father_name<<','<<r.date_of_birth<<','<<r.branch<<','<<r.year_of_admission
    <<','<<r.year_of_passing<<','<<r.district<<','<<r.state<<','<<r.pin<<','<<r.country;
    fout.close();
}
void Utility::write_file(record* r, size_t len){
    ofstream fout;
    fout.open(FILE_NAME,ios::ate);
    if(!fout)
        cout<<"Error in opening "<<FILE_NAME<<endl;
    fout<<r[0].roll_no<<','<<r[0].name<<','<<r[0].father_name<<','<<r[0].date_of_birth<<','<<r[0].branch<<','<<r[0].year_of_admission
        <<','<<r[0].year_of_passing<<','<<r[0].district<<','<<r[0].state<<','<<r[0].pin<<','<<r[0].country;
    for(size_t i{1};i<len;i++){
        fout<<"\n"<<r[i].roll_no<<','<<r[i].name<<','<<r[i].father_name<<','<<r[i].date_of_birth<<','<<r[i].branch<<','<<r[i].year_of_admission
            <<','<<r[i].year_of_passing<<','<<r[i].district<<','<<r[i].state<<','<<r[i].pin<<','<<r[i].country;
    }
    fout.close();
}