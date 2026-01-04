#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int max_members=50;

void clearscreen(){
    cout<<"\n======================================================================================================\n\n";
}

int membersId[max_members];
string memberName[max_members];

int memberAge[max_members];
string memberPhone[max_members];

string memberPackage[max_members];
int MembersFee[max_members];
string memberFeeStatus[max_members];
int totalMember=0;

// login credentials
string AdminUsername = "admin";
string AdminPassword = "admin123";

string AttendentUsername = "attendant";
string AttendentPassword = "attendant123";

int checkIds[100];
string checkNames[100];
int totalCheck = 0;

// file handling functions

void loadMember(){
    ifstream inFile("members.txt");  // inFile checks krthi ke file opens or not.

    if (!inFile){     
        return;
    }
    totalMember = 0;

    while(inFile >> membersId[totalMember]){
        inFile.ignore();                     //(.ignore) buffer cleaner, discards old data so that next function not use it as input

        getline(inFile,memberName[totalMember]);

        inFile>> memberAge[totalMember];
        inFile.ignore();

        getline(inFile,memberPackage[totalMember]);
        getline(inFile,memberPhone[totalMember]);

        inFile >> MembersFee[totalMember];
        inFile.ignore();

        getline(inFile,memberFeeStatus[totalMember]);

        totalMember++ ;

        if(totalMember>=max_members)
            break;
    }
    inFile.close();

}

void saveMembers(){
    ofstream outFile("members.txt");     //it opens the file in output stream to avoid errors

    for(int i=0;i<totalMember;i++){  
        outFile << membersId[i] << endl;
        outFile << memberName[i] << endl;
        outFile << memberAge[i] << endl;
        outFile << memberPackage[i] << endl;
        outFile << memberPhone[i] << endl;
        outFile << MembersFee[i] << endl;
        outFile << memberFeeStatus[i] << endl;

    }

    outFile.close();
}

void LoadCheckIn(){
    ifstream inFile("checkins.txt");

    if(!inFile){
        return;
    }
    totalCheck=0;

    while(inFile>>checkIds[totalCheck]){
        inFile.ignore(); 
        getline(inFile,checkNames[totalCheck]);
        totalCheck++;

        if(totalCheck>=100)
            break;
    }
    inFile.close();
}

void saveCheckIn(){
    ofstream outFile("checkins.txt");

    for(int i=0;i<totalCheck;i++){
        outFile<<checkIds[i]<<endl;
        outFile<<checkNames[i]<<endl;

    }
    outFile.close();
}

// login screen and enter jisse code mai maza aye

void pressEnter(){
    cout<<"\nPress Enter to continue...";
    cin.ignore();
    cin.get();       // ye enter dabane tk nhi agey barega, jo zyda control dethi h user ko.
}

string Login(){
    clearscreen();
    cout<<"===== GYM MANAGEMENT SYSTEM ====="<<endl;
    cout<<"\n1. Login as Admin";
    cout<<"\n2. Login as Attendent";
    cout<<"\n3. Exit"<<endl;
    int choice;
    cout<<"Enter your choice(1-3)= ";
    
    if(!(cin >> choice)){             // ager input fail hogay
        cin.clear();                  // ye input lock krdega,error flag reset hogayga
        cin.ignore(10000, '\n');       // agley 10000 char tk ignore krega
        cout << "\nInvalid Input! Please enter a number (1-3)." << endl;
        pressEnter();
        return Login(); 
    }

    if (choice==1){
        clearscreen();
        cout << "====== ADMIN LOGIN ======" << endl;

        string username,password;
        cout<<"\nEnter Username=";
        cin>>username;
        cout<<"\nEnter Password= ";
        cin>>password;

        if(username==AdminUsername && password==AdminPassword){
            cout<<"\nLogin Successfull!"<<endl;
            pressEnter();
            return "admin";
        }
        else{
            cout<<"\nInvalid Credentials!";
            pressEnter();
            return Login();
        }

    }
   else if(choice==2)
    {
        clearscreen();
        cout << "====== ATTENDANT LOGIN ======" << endl;

        string username,password;
        cout<<"\nEnter Username=";
        cin>>username;
        cout<<"\nEnter Password= ";
        cin>>password;

        if(username==AttendentUsername && password==AttendentPassword){
            cout<<"\nLogin Successfull!"<<endl;
            pressEnter();
            return "attendent";     // act likes label to tell which type of experience shoudl he get like attendent/admin/ya simply koi bhi nhi.
        }
        else{
            cout<<"\nInvalid Credentials!"<<endl;
            pressEnter();
            return Login();
        }

    }
    
    else if(choice==3){
        return "exit";
    }

    else{
        cout<<"\nInvalid Credentials!";
        pressEnter();
        return Login();
    }

}

//admin functions

void AddMember(){
    clearscreen();
    cout<<"===== ADD MEMBERS =====" << endl;

    if(totalMember>=max_members){
        cout<<"Sorry Members Full !"<<endl;
        pressEnter();
        return;
    }

    int maxId = 0;
    for(int i = 0; i < totalMember; i++){
        if(membersId[i] > maxId){
            maxId = membersId[i];
        }
    }
    membersId[totalMember] = maxId + 1;  
    
    cin.ignore();

    
    cout<<"Enter the Member's Name =";
    getline(cin,memberName[totalMember]);
    while(memberName[totalMember].empty() || memberName[totalMember] == " "){
        cout<<"Name cannot be empty! Please enter a valid name: ";
        getline(cin,memberName[totalMember]);
    }
    
    cout<<"Enter Member's Age (10-100): ";
    while(!(cin >> memberAge[totalMember]) || memberAge[totalMember] < 10 || memberAge[totalMember] > 100){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid Age! Enter age between 10-100: ";
    }
    cin.ignore();  // Clear buffer after age input

    cout<<"Enter Member's Phone Number (11 digits): ";
    getline(cin,memberPhone[totalMember]);
    
    while(true){
        bool isValid = true;
        
        if(memberPhone[totalMember].empty()){
            isValid = false;
        }
        else if(memberPhone[totalMember].length() != 11){
            isValid = false;
        }
        else{
            for(int i = 0; i < memberPhone[totalMember].length(); i++){
                if(!isdigit(memberPhone[totalMember][i])){
                    isValid = false;
                    break;
                }
            }
        }
        
        
        if(isValid){
            for(int i = 0; i < totalMember; i++){
                if(memberPhone[i] == memberPhone[totalMember]){
                    cout<<"This phone number is already registered! Enter a different number: ";
                    getline(cin,memberPhone[totalMember]);
                    isValid = false;
                    break;
                }
            }
        }
        
        if(isValid){
            break;  
        }
        else if(memberPhone[totalMember].length() != 11 || !isValid){
            cout<<"Invalid phone number! Must be exactly 11 digits: ";
            getline(cin,memberPhone[totalMember]);
        }
    }
         

    int choice;
    cout << "\nPackage Options:" << endl;
    cout << "1. Basic  Rs. 1000/month" << endl;
    cout << "2. Standard Rs. 2000/month" << endl;
    cout << "3. Premium Rs. 3000/month" << endl;
    cout<<"Enter your Package Choice= ";
    
    
    while(!(cin >> choice) || choice < 1 || choice > 3){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid Input! Please enter a number (1, 2 or 3): ";
    }

    if(choice==1){
        MembersFee[totalMember]=1000;
        memberPackage[totalMember]="Basic";  
        cout<<"You Chose Basic Package 'RS.1000/' "<<endl;
        clearscreen();
    }
    else if(choice == 2){
        MembersFee[totalMember]=2000;
        memberPackage[totalMember]="Standard";  
        clearscreen();
        cout<<"You Chose Standard Package 'RS.2000/' "<<endl;
    }
    else if(choice == 3){
        MembersFee[totalMember]=3000;
        memberPackage[totalMember]="Premium";  
        clearscreen();
        cout<<"You Chose Premium Package 'RS.3000/' "<<endl;
    }

    memberFeeStatus[totalMember]="Paid";

    cout << "\nMember '" << memberName[totalMember] << "' added successfully!" << endl;
    cout << "Member ID: " << membersId[totalMember] << endl;

    totalMember++;

    saveMembers();
    pressEnter();

}

void removeMember(){
    clearscreen();
    cout<<"\n====== REMOVE MEMBER ======"<<endl;

    if(totalMember==0){
        cout<<"\nNo Member Found"<<endl;
        pressEnter();
        return;
    }

    int RemoveMemberid;
    cout<<"\nEnter the ID to remove: ";
    
    if(!(cin>> RemoveMemberid)){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nInvalid ID! Input must be a number." << endl;
        pressEnter();
        return;
    }

    bool Found= false;
    int indexToFound= -1;    // programming starts with 0 to prevent error we use -1 as index flag.

    for(int i=0;i<totalMember;i++){
        if(membersId[i]==RemoveMemberid){
            Found=true;
            indexToFound=i;
            break;
        }
    }

    if(Found){
        string RemoveName =memberName[indexToFound];
        int removedId = membersId[indexToFound];  

        for(int i=indexToFound;i<totalMember-1;i++){  
            membersId[i] = membersId[i + 1];        // ye gap fill kregi jo remove hoa tha uski wjha se
            memberName[i] = memberName[i + 1];
            memberAge[i] = memberAge[i + 1];
            memberPhone[i] = memberPhone[i + 1];
            memberPackage[i] = memberPackage[i + 1];
            MembersFee[i] = MembersFee[i + 1];
            memberFeeStatus[i] = memberFeeStatus[i + 1];
        }
        totalMember--;

        int newCheckTotal = 0;
        for(int i = 0; i < totalCheck; i++){
            if(checkIds[i] != removedId){
                // Keep this check-in (shift it down)
                checkIds[newCheckTotal] = checkIds[i];
                checkNames[newCheckTotal] = checkNames[i];
                newCheckTotal++;
            }
            // If checkIds[i] == removedId, skip it (delete it)
        }
        totalCheck = newCheckTotal;  
        saveCheckIn();  

        saveMembers();
        cout << "\nMember '" << RemoveName << "' and their check-in history removed successfully!" << endl;
        }
    else
    cout << "\nMember not found!" << endl;
    
    pressEnter();

}


void ViewMembers(){
    clearscreen();
    cout<<"====== ALL MEMBERS =====" << endl;

    if (totalMember==0){
        cout<<"\nNo members in the system!"<<endl;
        pressEnter();
        return;
    }
    cout<<"\nID_____Name__________Age____Package______Fee_____FeeStatus" << endl;
    cout<<"--------------------------------------------------------------------------"<<endl;
    for(int i =0;i<totalMember;i++){
        cout<<membersId[i]<<"     ";
        cout<<memberName[i]<<"          ";
        cout<<memberAge[i]<<"      ";  
        if(MembersFee[i]==1000)
            cout<<"Basic"<< "     ";  
        else if(MembersFee[i]==2000)
            cout<<"Standard"<< "     ";  
        else
            cout<<"Premium"<<"     ";
        cout<<MembersFee[i]<<"     ";
        cout<<memberFeeStatus[i];
        cout<<endl;
    }
    pressEnter();
}

void ViewRevenue(){
    clearscreen();
    cout<<"===== GYM REVENUE ====="<<endl;

    int totalRevenue=0;
    int paidMembers=0;

    for(int i=0;i<totalMember;i++){
        if(memberFeeStatus[i]=="Paid"){
            totalRevenue=totalRevenue+MembersFee[i];
            paidMembers++;
        }
    }

    cout<<"\nTotal Members: "<<totalMember<<endl;
    cout<<"\nPaid Members: "<<paidMembers<<endl;
    cout<<"\nPending Members: "<<(totalMember-paidMembers)<<endl;
    cout<<"\nTotal Revenue: "<<totalRevenue<<endl;

    pressEnter();
}

void AdminMenu(){
    while(true){      //infinite loop, ye chlthe rehegi jbtk exit function nhi dabata
        clearscreen();
        cout<<"===== ADMIN DASHBOARD ====="<<endl;
        cout<<"\n1. Add New Member "<<endl;
        cout << "2. Remove Member" << endl;
        cout << "3. View All Members" << endl;
        cout << "4. View Revenue" << endl;
        cout << "5. Logout" << endl;

        int choice;
        cout<<"\nEnter your choice (1-5): ";
        
        if(!(cin>>choice)){
            cin.clear(); 
            cin.ignore(10000, '\n'); 
            cout << "\nInvalid input! Please enter a number." << endl;
            pressEnter();
            continue; 
        }

        if(choice==1){
            AddMember();
        }
        else if(choice==2){
            removeMember();
        }
        else if(choice==3){
            ViewMembers();
        }
        else if(choice==4){
            ViewRevenue();
        }
        else if(choice==5){
            cout<<"\nLogging out... ..."<<endl;
            break;
        }
        else{
            cout<<"Invalid Choice!"<<endl;
            pressEnter();
        }
    }
    
}

//attendent functions

void recordCheckIn(){
    clearscreen();
    cout<<"======== RECORD CHECK-IN ======== ";

    if(totalMember==0){
        cout<<"\nNo members in the system! "<<endl;
        pressEnter();
        return;
    }

    int memberId;
    cout<<"\nEnter your Member ID: ";
    
    if(!(cin>>memberId)){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nInvalid ID! Numbers only." << endl;
        pressEnter();
        return;
    }

    int memberIndex=-1;
    
    for(int i=0;i<totalMember;i++){
        if(membersId[i]==memberId){
            memberIndex=i;
            break;
        }
    }
    
    if(memberIndex==-1){
        cout<<"\nMember Not Found! ";
        pressEnter();
        return;
    }

    checkIds[totalCheck]=membersId[memberIndex];
    checkNames[totalCheck]=memberName[memberIndex];
    totalCheck++;

    saveCheckIn();
    cout<<"\nCheck-Ins recorded for "<<memberName[memberIndex]<<"!"<<endl;
    pressEnter();
}

void searchMember(){
    clearscreen();
    cout<<"======== SEARCH MEMBER ========"<<endl;

    if(totalMember==0){
        cout<<"\nNo members found in the system! "<<endl;
        pressEnter();
        return;
    }

    cin.ignore();
    string searchName;
    cout<<"\nEnter the member name to search: ";
    getline(cin,searchName);

    cout<<"\nSearch Results:"<<endl;
    cout<<"------------------------------------------------"<<endl;

    bool found= false;

    for(int i=0;i<totalMember;i++){
        bool match= false;
        string lowerMemberName = memberName[i];
        string lowerSearchName = searchName;
        
        for (int j = 0; j < lowerMemberName.length(); j++) {    
            lowerMemberName[j] = tolower(lowerMemberName[j]);      //tolower converts all character of name to lowercase
        }
        for (int j = 0; j < lowerSearchName.length(); j++) {
            lowerSearchName[j] = tolower(lowerSearchName[j]);
        }
        
        
        if (lowerMemberName==lowerSearchName) {
            match = true;

        }
        
        if (match) {
            cout << "\nID: " << membersId[i] << endl;
            cout << "Name: " << memberName[i] << endl;
            cout << "Age: " << memberAge[i] << endl;
            cout << "Phone: " << memberPhone[i] << endl;
            cout << "Package: " << memberPackage[i] << endl;
            cout << "Fee: Rs. " << MembersFee[i] << endl;
            cout << "Status: " << memberFeeStatus[i] << endl;
            cout << "--------------------------------------------------" << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "No members found with that name!" << endl;
    }
    
    pressEnter();
}

void attendentMenu(){
        while(true){
            clearscreen();
            cout << "====== ATTENDANT DASHBOARD ======" << endl;
            cout << "\n1. Record Check-in" << endl;
            cout << "2. View All Members" << endl;
            cout << "3. Search Member" << endl;
            cout << "4. Register New Member" << endl;
            cout << "5. Logout" << endl;
        

        int choice;
        cout<<"\nEnter you choice(1-5): "<<endl;
        
        if(!(cin>>choice)){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid Input! Please enter a number." << endl;
            pressEnter();
            continue; 
        }

        if(choice==1){
            recordCheckIn();
        }
        else if(choice==2){
            ViewMembers();
        }
        else if(choice==3){
            searchMember();
        }
        else if(choice==4){
            AddMember();
        }
        else if(choice==5){
            cout<<"\nLogging out...."<<endl;
            break;
        }
        else{
            cout<<"Invalid choice! "<<endl;
            pressEnter();
        }
    }
}

int main(){

    loadMember();          // ye fetching krega pehle se stored data ko, kaam easy hogayga phir
    LoadCheckIn();

    cout << "\n**************************************************" << endl;
    cout << "  WELCOME TO GYM MANAGEMENT SYSTEM" << endl;
    cout << "**************************************************" << endl;
    pressEnter();

    while(true){
        string userType = Login();    // ye check krega return value from login, example ke admin,attendant ya exit kis trah interface lana h.

        if(userType =="exit"){
            cout<<"\nThank you for using the system! "<<endl;
            cout<<"Goodbye! "<<endl;
            break;
        }
        else if(userType=="admin"){
            AdminMenu();
        }
        else if(userType=="attendent"){
            attendentMenu();
        }
    }

    return 0;
}
