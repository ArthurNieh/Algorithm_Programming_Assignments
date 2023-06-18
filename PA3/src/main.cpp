#include<cstring>
#include<iostream>
#include<fstream>
#include<queue>
#include<stack>

using namespace std;

class Edge{
    public:
        Edge(int s, int e, int w){
            start = s;
            end = e;
            weight = w;
            check_cut = 0;
        }
        int start;
        int end;
        int weight;
        bool check_cut;
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

bool** edges;

// check whether there is path from start to end, 1 for true, 0 for false
bool check_path(int start, int end, int vertice_num){
    // cout << start << " " << end << " : ";
    if(edges[start][end] == 1){
        // cout << "1 at here" <<endl;
        return 1;
    }

    // 1 for been to the vertice, 0 for not
    bool* ver_through = new bool [vertice_num];
    // for index tried
    // int* index_try_next = new int [vertice_num];
    for(int i=0;i<vertice_num;i++){
        ver_through[i] = 0;
        // index_try_next[i] = 0;
    }

    stack<int> dfs;
    ver_through[start] = 1;
    dfs.push(start);
    // int index_now = start;
    do{
        // cout<<"in while : "<< dfs.top()<<endl;
        if(dfs.top() == end){
            // cout << "successfully route compression" << endl;
            while(!dfs.empty()){
                edges[dfs.top()][end] = 1;
                dfs.pop();
            }
            break;
        }
        // int k = index_try_next[dfs.top()];
        // if(k == vertice_num){
        //     cout << "am i wrong" <<endl;
        //     dfs.pop();
        // }
        for(int i=0;i<vertice_num;i++){
            // index_try_next[dfs.top()] ++;
            if(edges[dfs.top()][i] == 1 && (!ver_through[i])){
                dfs.push(i);
                ver_through[i] = 1;
                break;
            }
            if(i == vertice_num - 1){
                // cout << "no route for " << dfs.top() <<endl;
                edges[start][dfs.top()] = 1;
                dfs.pop();
            }
        }
        
    }while(dfs.size()>0);
    // cout << edges[start][end] <<endl;
    return edges[start][end];
}

int main(int argc, char* argv[]){
    
    fstream fin(argv[1]);
    fstream fout;

    fout.open(argv[2],ios::out);
    char graph_type;
    fin >> graph_type;
    int vertice_num, edge_num;
    fin >> vertice_num >> edge_num;

    int start_index, end_index, weight;
    priority_queue<Edge, vector<Edge>, cmp> pq;
    vector<Edge> edges_to_cut;
    
    // initialize all vertice    
    for(int i=0;i<vertice_num;i++){
        Vertice v(i);
        vertices.push_back(v);
    }

    // for undirected graph
    if(graph_type == 'u'){
        while (fin >> start_index >> end_index >> weight){
            Edge e(start_index, end_index, weight);
            pq.push(e);
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
        // remember the possitive cut edges
        vector<Edge> pos_edges_cut;

        // adjacent matrix
        edges = new bool* [vertice_num];
        for(int i=0;i<vertice_num;i++){
            edges[i] = new bool [vertice_num];
            for(int j=0;j<vertice_num;j++){
                edges[i][j] = 0;
            }
            edges[i][i] = 1;
        }

        while (fin >> start_index >> end_index >> weight){
            // edges[start_index][end_index] = 1;
            Edge e(start_index, end_index, weight);
            pq.push(e);
        }

        int total_cut_weight = 0;
        while(!pq.empty()){
            Edge e = pq.top();
            int root_start = find_root(e.start);
            int root_end = find_root(e.end);
            if(root_start == root_end){
                edges_to_cut.push_back(e);
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
                edges[e.start][e.end] = 1;
                // for(int i=0;i<vertice_num;i++){
                //     if(edges[i][e.start]){ // if i to e.start has a path
                //         edges[i][e.end] = 1;
                //     }
                //     else if(edges[e.end][i]){
                //         edges[e.start][i] = 1;
                //     }
                // }
            }
            pq.pop();
        }
        // cout << "27, 41 : " << edges[27][41] <<endl;
        int edge_index = 0;
        while(edges_to_cut[edge_index].weight > 0){
            if(check_path(edges_to_cut[edge_index].end, edges_to_cut[edge_index].start, vertice_num)){
                total_cut_weight += edges_to_cut[edge_index].weight;
                pos_edges_cut.push_back(edges_to_cut[edge_index]);
            }
            else{
                // cout << "edge add" << endl;
                edges[edges_to_cut[edge_index].start][edges_to_cut[edge_index].end] = 1;
            }
            edge_index ++;
        }
        while(edge_index < edges_to_cut.size()){
            total_cut_weight += edges_to_cut[edge_index].weight;
            pos_edges_cut.push_back(edges_to_cut[edge_index]);
            edge_index ++;
        }

        // cout << "going to output" << endl;
        // output stage
        fout << total_cut_weight << endl;
        for(int i = 0; i < pos_edges_cut.size(); i++){
            Edge e = pos_edges_cut[i];
            fout << e.start << " " << e.end << " " << e.weight << endl;
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
