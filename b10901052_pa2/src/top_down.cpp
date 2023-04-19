#include<cstring>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

void print_cut(vector<int> &, int**, int, int, fstream &);
int MPS(vector<int> &, int**, int**, int, int);

int main(int argc, char* argv[]){
    
    fstream fin(argv[1]);
    fstream fout;

    fout.open(argv[2],ios::out);
    int chord_num;
    fin >> chord_num;
    int start_index,end_index;
    vector<int> chords(chord_num, -1);
    while (fin >> start_index >> end_index){
        chords[start_index] = end_index;
        chords[end_index] = start_index;
    }
    // printf("input done");
    int** M = new int* [chord_num];
    int** cut = new int* [chord_num];

    for(int i=0;i<chord_num;i++){
        M[i] = new int [chord_num];
        cut[i] = new int [chord_num];
        for(int j=0;j<chord_num;j++){
            M[i][j] = -1;
        }
        M[i][i] = 0;
        cut[i][i] = -1;
    }

    MPS(chords, M, cut, 0, chord_num-1);

    fout << M[0][chord_num-1] << endl;
    printf("%d\n", M[0][chord_num-1]);

    print_cut(chords, cut, 0, chord_num-1, fout);

    return 0;
}
void print_cut(vector<int> &chords,int** cut, int start, int end, fstream &fout){
    if(start>end){
        return;
    }
    if(cut[start][end] == cut[start][end-1]){
        print_cut(chords, cut, start, end-1, fout);
        return;
    }
    int k = cut[start][end];
    if(k!=-1){
        print_cut(chords, cut, start, k-1, fout);
        // printf("%d %d\n", k, end);
        fout << k << " " << end << endl;
        print_cut(chords, cut, k+1, end-1, fout);
    }
}
int MPS(vector<int> &chords, int** M, int** cut, int start, int end){
    // printf("start %d end %d\n", start, end);
    if(M[start][end]!=-1){
        return M[start][end];
    }
    if(start>end){
        // printf("seg!");
        return 0;
    }
    int k = chords[end];
    int without_chord = MPS(chords, M, cut, start, end-1);
    if(start<=k && k<end){
        int with_chord = MPS(chords, M, cut, start, k-1)
                        + 1 + MPS(chords, M, cut, k+1, end-1);
        if(with_chord > without_chord){
            M[start][end] = with_chord;
            cut[start][end] = k;
        }
        else{
            M[start][end] = without_chord;
            cut[start][end] = cut[start][end-1];
        }
    }
    else{
        M[start][end] = without_chord;
        cut[start][end] = cut[start][end-1];
    }
    return M[start][end];
}
