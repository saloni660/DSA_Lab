#include <bits/stdc++.h>
using namespace std;

void insert(int hash[][2], int key){
    int tempHash = key%10;
    int loc = key%10;
    while (true)
    {
        if(hash[loc][0]==-1){
            hash[loc][0]= key;
            break;
        }
        else if(hash[loc][1] != -1 && hash[loc][0]%10==tempHash){
            loc = hash[loc][1];
        }
        else if(hash[loc][1]==-1 && hash[loc][0]%10==tempHash){
            int tempLoc = loc+1;
            while (true)
            {
                if(tempLoc>10){
                    tempLoc = 0;
                }
                else if(hash[tempLoc][0]==-1){
                    break;
                }
                tempLoc++;
            }
            hash[tempLoc][0] = key;
            hash[loc][1]=tempLoc;
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

void search(int hash[][2]){

}

bool isFull(int hash[][2]){
    int i =0;
    while(true){
        if(hash[i][0]==-1){
            return false;
        }
        i++;
    }
    return true;
}

void display(int hash[][2]){
    cout<<"Ind"<<" "<<"Hash"<<" "<<"Chain"<<endl;
    for (int i = 0; i < 10; i++)
    {
        cout<<i<<" "<<hash[i][0]<<" "<< hash[i][1]<<endl;

    }
    
}

int main(){
    int hash[10][2];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            hash[i][j]=-1;
        }
        
    }

    string menu ="Enter your choice: \n1. Add\n2. Display\n3. Exit";
    int opt;
    do
    {
        cout<<menu<<endl;
        cout<<"Your choice: ";
        cin>>opt;
        switch (opt)
        {
        case 1:
            cout<<"\nEnter the element: ";
            int key;
            cin>>key;
            insert(hash,key);
            break;
        case 2:
            display(hash);
            break;
        case 3:
            exit(0);
        
        default:
            cout<<"\n Please enter a correct option"<< endl;
            break;
        }
    } while (true);
    
    
}