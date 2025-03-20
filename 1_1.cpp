#include <bits/stdc++.h>
using namespace std;

void insert(int hash[],int key){
    int loc = key%10;
    while(true){
        if(hash[loc]==-1 || hash[loc]==-2){
            hash[loc] = key;
            break;
        }
        else{
            if(loc>=9){
                loc=0;
            }
            else{
                loc++;
            }
        }
    }
}
void search(int hash[], int key){
    int loc = key%10;
    while (true)
    {
        if(hash[loc]== key){
            cout<< key <<"found at"<< loc<<endl;
            break;
        }
        else{
            if(loc>=9){
                loc = 0;
            }
            else{
                loc++;
            }
        }
    }
    
}
void display(int hash[]){
    cout<< "ind" << " " << "key"<<endl;
    for (int i = 0; i < 10; i++)
    {
        cout<< i << " "<< hash[i]<<endl;
    }
    

}

int main(){
    int hash[10];
    for (int i = 0; i < 10; i++)
    {
        hash[i]=-1;
    }

    string menu = "Enter one of the choice:\n1. Add element\n2. Search element\n3. Display\n4. Exit";
    
    int opt;
    
    int data;

    do{
        cout<<menu<<endl;
        cout<<"Your choice: ";cin>>opt;
        switch(opt){
            case 1:
                cout<<"Enter element to add";
                cin>>data;
                insert(hash,data);
                break;
            case 2:
                cout<<"Enter element to search";
                cin>>data;
                search(hash,data);
                break;
            case 3:
                display(hash);
                break;
            case 4:
                exit(0);
                break;
            default:
                cout<<"Please enter correct option";
                break;
        }
    }while(true);
    return 0;
}