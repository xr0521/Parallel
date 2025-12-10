#include<iostream>
using namespace std;
void sort(int arr[],int length){
    int tmp=0;
    for(int i=0;i<length-1;++i){
        for(int j=0;j<length-i-1;j++){
           if(arr[j]>arr[j+1]){
               tmp=arr[j];
               arr[j]=arr[j+1];
               arr[j+1]=tmp;
           }
        }
    }
}
int main(){
    int arr[]={1,3,5,21,66,0,9};
    int length=sizeof(arr)/sizeof(arr[0]);
    sort(arr,length);
    for(auto& i:arr){
        std::cout<<i<<" ";
    }
    std::cout<<'\n';
    return 0;
}
