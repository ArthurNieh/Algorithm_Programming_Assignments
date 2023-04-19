#include<cstring>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int maximun_planar_subset(vector<vector<int>> &, int**, int, int);
void print_cut(vector<int> &, int**, int,int);

fstream fout;

int main(int argc, char* argv[]){
    
    fstream fin(argv[1]);
    
    fout.open(argv[2],ios::out);
    int chord_num;
    fin >> chord_num;
    int start_index,end_index;
    vector<int> chords(chord_num, -1);
    while (fin >> start_index >> end_index){
        chords[start_index] = end_index;
        chords[end_index] = start_index;
    }
printf("input done");
    int** M = new int* [chord_num];
    int** cut = new int* [chord_num];

    for(int i=0;i<chord_num;i++){
        M[i] = new int [chord_num];
        cut[i] = new int [chord_num];
        M[i][i] = 0;
        cut[i][i] = -1;
    }

    
    

    for(int i=0;i<chord_num;i++){
        if(i%1000==0){
            printf("%d\n", i);
        }
        int k = chords[i];
        for(int j=0;j<i;j++){
            if(j<=k && k<=i && (M[j][k-1] + 1 + M[k+1][i-1] > M[j][i-1])){
                M[j][i] = M[j][k-1] + 1 + M[k+1][i-1];
                cut[j][i] = k;
            }
            else{
                M[j][i] = M[j][i-1];
                cut[j][i] = cut[j][i-1];
            }
            // if(i<j){
            //     printf("error");
            // }
        }
    }
    

    printf("%d\n", M[0][chord_num-1]);
    fout << M[0][chord_num-1] << endl;

    print_cut(chords, cut, 0, chord_num-1);
    
    // printf("%ld\n", chords.size());
    // for(int i=0;i<chords.size();i++){
    //     printf("%d %d\n", i, chords[i]);
    // }

    return 0;
}
void print_cut(vector<int> &chords,int** cut, int start, int end){
    if(start>end){
        return;
    }
    if(cut[start][end] == cut[start][end-1]){
        print_cut(chords, cut, start, end-1);
        return;
    }
    int k = cut[start][end];
    if(k!=-1){
        print_cut(chords, cut, start, k-1);
        printf("%d %d\n", k, end);
        fout << k << " " << end << endl;
        print_cut(chords, cut, k+1, end-1);
        
    }

}
int maximun_planar_subset(vector<vector<int>> &chords, int** M, int start, int end){
    if(M[start][end] != -1){
        return M[start][end];
    }
    return 0;
}
