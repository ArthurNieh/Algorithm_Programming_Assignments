#include<cstring>
#include<iostream>
#include<fstream>
#include<queue>

using namespace std;

class Edge{
    public:
        Edge(int s, int e, int w){
            start = s;
            end = e;
            weight = w;
        }
        int start;
        int end;
        int weight;
        void print(){
            cout << start << " " << end << " " << weight << endl;
        }
};
class cmp {
    public: 
        bool operator()(Edge a, Edge b) {
            return a.weight < b.weight;
        }
};
class Vertice{
    public:
        Vertice(int v){
            vertice_num = v;
            rank = 1;
            pred = v;
        }
        int vertice_num;
        int pred;
        int rank;
};
vector<Vertice> vertices;

int find_root(int v){
    int check = v;
    while(check != vertices[check].pred){
        check = vertices[check].pred;
    }
    int change = v;
    while(vertices[change].pred != check){
        int hold = vertices[change].pred;
        vertices[change].pred = check;
        change = hold;
    }
    return check;
}

int main(int argc, char* argv[]){
    
    fstream fin(argv[1]);
    fstream fout;

    fout.open(argv[2],ios::out);
    char graph_type;
    fin >> graph_type;
    int vertice_num, edge_num;
    fin >> vertice_num >> edge_num;

    // int** edges = new int* [vertice_num];
    // for(int i=0;i<vertice_num;i++){
    //     edges[i] = new int [vertice_num];
    //     for(int j=0;j<vertice_num;j++){
    //         edges[i][j] = -200;
    //     }
    // }

    int start_index, end_index, weight;
    priority_queue<Edge, vector<Edge>, cmp> pq;
    vector<Edge> edges_to_cut;

    if(graph_type == 'u'){
        while (fin >> start_index >> end_index >> weight){
            // edges[start_index][end_index] = weight;
            // edges[end_index][start_index] = weight;
            Edge e(start_index, end_index, weight);
            pq.push(e);
        }

        // initialize all vertice
        
        for(int i=0;i<vertice_num;i++){
            Vertice v(i);
            vertices.push_back(v);
        }

        int total_cut_weight = 0;
        while(!pq.empty()){
            Edge e = pq.top();
            int root_start = find_root(e.start);
            int root_end = find_root(e.end);
            if(root_start == root_end){
                edges_to_cut.push_back(e);
                total_cut_weight += e.weight;
            }
            else{
                if(vertices[root_start].rank > vertices[root_end].rank){
                    vertices[root_end].pred = root_start;
                }
                else if(vertices[root_start].rank < vertices[root_end].rank){
                    vertices[root_start].pred = root_end;
                }
                else{
                    vertices[root_end].pred = root_start;
                    vertices[root_start].rank += 1;
                }
            }
            pq.pop();
        }

        // output stage
        fout << total_cut_weight << endl;
        for(int i = 0; i < edges_to_cut.size(); i++){
            Edge e = edges_to_cut[i];
            fout << e.start << " " << e.end << " " << e.weight << endl;
        }
        
    }

    // for directed graph
    else if(graph_type == 'd'){
        while (fin >> start_index >> end_index >> weight){
            // edges[start_index][end_index] = weight;
        }
    }
    else{
        cout << "wrong graph type" << endl;
    }
    
    // for(int i=0;i<vertice_num;i++){
    //     for(int j=0;j<vertice_num;j++){
    //         cout << edges[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // while(!pq.empty()){
    //     Edge e = pq.top();
    //     e.print();
    //     pq.pop();
    // }


    return 0;
}
