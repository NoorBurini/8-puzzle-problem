#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

bool goal_test(vector<int>a)
{
    return a[0]==0 && a[1]==1 && a[2]==1 && a[3]==2 && a[4]==3 && a[5]==3 && a[6]==4 && a[7]==5 && a[8]==6; 
}

class State{
    public:
    vector<int>a;
    int cost;
    int index;//empty square
    int level;//for IDS
    State *Parent;
    vector<State*>Childs;
    string action;
    State(vector<int>&arr,State *parent);
    void Up();
    void Down();
    void Left();
    void Right();
    void Print();
};

State::State(vector<int>&arr,State *parent){
        a=arr;
        this->Parent=parent;
        for(int i=0;i<9;i++)
        if(a[i]==0)index=i;
    }

void State::Up(){
        if(index-3>=0)
            {
                swap(a[index],a[index-3]);
                index=index-3;
            }
        action="Up";
    }

void State::Down(){
        if(index+3<=8)
            {
                swap(a[index],a[index+3]);
                index=index+3;
            }
        action="Down";
    }

void State::Left(){
        if(index%3!=0)
            {
                swap(a[index],a[index-1]);
                index=index-1;
            }
        action="Left";
    }

void State::Right(){
        if(index%3!=2)
            {
                swap(a[index],a[index+1]);
                index=index+1;
            }
        action="Right";
    }
    
void State::Print(){
        cout<<a[0]<<' '<<a[1]<<' '<<a[2]<<'\n';
        cout<<a[3]<<' '<<a[4]<<' '<<a[5]<<'\n';
        cout<<a[6]<<' '<<a[7]<<' '<<a[8]<<'\n';
    }
    
void BFS(State *initial)
{
    cout<<"--Breadth First Search Algorithm --\n";
    int level=0,generated_cnt=0,expanded_cnt=0;
    vector<string>path;
    State *goal_state;
    queue<State*>Generated;
    map<vector<int>, int> Expanded;
    Generated.push(initial);
    bool goal_found=goal_test(initial->a);
    while(!goal_found)
    {
        if(Expanded[initial->a]){
            Generated.pop();
            initial=Generated.front();
            continue;
        }

        if(initial->index==4){//4 moves ,center
            State *s[4];
            for(int i=0;i<4;i++)s[i]=new State(initial->a,initial);
            s[0]->Left();
            s[1]->Right();
            s[2]->Up();
            s[3]->Down();
            for(int i=0;i<4;i++){
                initial->Childs.push_back(s[i]);
                Generated.push(s[i]);
                //s[i]->Print();
            }
            for(int i=0;i<4;i++)
            {
                if(goal_test(s[i]->a)==1){
                    goal_found=1;
                    goal_state=s[i];
                    break;
                }
            }
        }

        else if(initial->index==0||initial->index==2||initial->index==6||initial->index==8)//2 moves
        {
            State *s[2];
            for(int i=0;i<2;i++)s[i]=new State(initial->a,initial);
            if(initial->index==0)
            {
                s[0]->Down();
                s[1]->Right();
            }
            else if(initial->index==2)
            {
                s[0]->Down();
                s[1]->Left();
            }
            else if(initial->index==6)
            {
                s[0]->Right();
                s[1]->Up();
            }
            else if(initial->index==8)
            {
                s[0]->Left();
                s[1]->Up();
            }
            for(int i=0;i<2;i++){
                initial->Childs.push_back(s[i]);
                Generated.push(s[i]);
                //s[i]->Print();
            }
            for(int i=0;i<2;i++)
            {
                if(goal_test(s[i]->a)==1){
                    goal_found=1;
                    goal_state=s[i];
                    break;
                }
            }
        }
        else if(initial->index==1||initial->index==3||initial->index==5||initial->index==7)//3moves
        {
            State *s[3];
            for (int i = 0; i < 3; i++)s[i]=new State(initial->a,initial);
            if(initial->index==1)
            {
                s[0]->Left();
                s[1]->Right();
                s[2]->Down();
            }
            else if(initial->index==3)
            {
                s[0]->Up();
                s[1]->Right();
                s[2]->Down();
            }
            else if(initial->index==5)
            {
                s[0]->Left();
                s[1]->Up();
                s[2]->Down();
            }
            else if(initial->index==7)
            {
                s[0]->Left();
                s[1]->Right();
                s[2]->Up();
            }
            for(int i=0;i<3;i++){
                initial->Childs.push_back(s[i]);
                Generated.push(s[i]);
                //s[i]->Print();
            }
            for(int i=0;i<3;i++)
            {
                if(goal_test(s[i]->a)==1){
                    goal_found=1;
                    goal_state=s[i];
                    break;
                }
            }
        }
        Expanded[initial->a]++;
        expanded_cnt++;
        Generated.pop();
        initial=Generated.front();
    }
    vector<vector<int>>v;
    generated_cnt=expanded_cnt+Generated.size();
    while(goal_state->Parent!=NULL){
        level++;
        v.push_back(goal_state->a);
        path.push_back(goal_state->action);
        goal_state=goal_state->Parent;
    }
    bool f=0;
    if(v.size()<11)f=1;
    reverse(v.begin(),v.end());
    reverse(path.begin(),path.end());
    cout<<"Solution path :\n";
    for(int i=0;i<path.size();i++){
        cout<<path[i]<<'\n';
        if(f){
            cout<<v[i][0]<<' '<<v[i][1]<<' '<<v[i][2]<<'\n';
            cout<<v[i][3]<<' '<<v[i][4]<<' '<<v[i][5]<<'\n';
            cout<<v[i][6]<<' '<<v[i][7]<<' '<<v[i][8]<<'\n';
            cout<<'\n';
        }
    }
    cout<<'\n'<<"Generted nodes = "<<generated_cnt<<'\n';
    cout<<"Expanded nodes = "<<expanded_cnt<<'\n';
    cout<<"Found at level : "<<level;
}

void IDS(State *initial)
{
    cout<<"--Iterative Deepening Search Algorithm --\n";
    cout<<"Initial State : \n";
    initial->Print();
    State *X=initial;
    int generated_cnt=0,expanded_cnt=0;
    vector<string>path;
    initial->level=0;
    int level;
    stack<State*>Generated;
    State *goal_state;
    map<vector<int>,int>Expanded;
    bool goal_found=goal_test(initial->a),f=0;
    int limit=0;
    while(!goal_found){
        Generated.push(X);
        initial=X;
        initial->Childs.clear();
        while(Generated.size()&&!goal_found)
            {
                //if(initial->level==0)cout<<initial->Childs.size()<<endl;
                if(Expanded[initial->a]){
                    Generated.pop();
                    if(Generated.size())initial=Generated.top();
                    continue;
                }
                if(initial->level==limit ){
                    if(limit>0){
                        Generated.pop();
                        Expanded[initial->a];
                        if(Generated.size())initial=Generated.top();
                        continue;
                    }
                    else{
                        Generated.pop();
                        break;
                    }
                }
                Generated.pop();
                if(initial->index==4){//4 moves ,center
                    State *s[4];
                    for(int i=0;i<4;i++){
                        s[i]=new State(initial->a,initial);
                        (s[i]->level)=(s[i]->Parent->level)+1;
                    }
                    s[0]->Left();
                    s[1]->Right();
                    s[2]->Up();
                    s[3]->Down();
                    for(int i=0;i<4;i++){
                        initial->Childs.push_back(s[i]);
                        Generated.push(s[i]);
                        generated_cnt++;
                    }
                    for(int i=0;i<4;i++)
                    {
                        if(goal_test(s[i]->a)==1){
                            goal_found=1;
                            goal_state=s[i];
                            break;
                        }
                    }
                }

                else if(initial->index==0||initial->index==2||initial->index==6||initial->index==8)//2 moves
                {
                    State *s[2];
                    for(int i=0;i<2;i++){
                        s[i]=new State(initial->a,initial);
                        (s[i]->level)=(s[i]->Parent->level)+1;
                    }
                    if(initial->index==0)
                    {
                        s[0]->Down();
                        s[1]->Right();
                    }
                    else if(initial->index==2)
                    {
                        s[0]->Down();
                        s[1]->Left();
                    }
                    else if(initial->index==6)
                    {
                        s[0]->Right();
                        s[1]->Up();
                    }
                    else if(initial->index==8)
                    {
                        s[0]->Left();
                        s[1]->Up();
                    }
                    for(int i=0;i<2;i++){
                        initial->Childs.push_back(s[i]);
                        Generated.push(s[i]);
                        generated_cnt++;
                    }
                    for(int i=0;i<2;i++)
                    {
                        if(goal_test(s[i]->a)==1){
                            goal_found=1;
                            goal_state=s[i];
                            break;
                        }
                    }
                }
                else if(initial->index==1||initial->index==3||initial->index==5||initial->index==7)//3moves
                {
                    State *s[3];
                    for (int i = 0; i < 3; i++){
                        s[i]=new State(initial->a,initial);
                        (s[i]->level)=(s[i]->Parent->level)+1;
                    }
                    if(initial->index==1)
                    {
                        s[0]->Left();
                        s[1]->Right();
                        s[2]->Down();
                    }
                    else if(initial->index==3)
                    {
                        s[0]->Up();
                        s[1]->Right();
                        s[2]->Down();
                    }
                    else if(initial->index==5)
                    {
                        s[0]->Left();
                        s[1]->Up();
                        s[2]->Down();
                    }
                    else if(initial->index==7)
                    {
                        s[0]->Left();
                        s[1]->Right();
                        s[2]->Up();
                    }
                    for(int i=0;i<3;i++){
                        initial->Childs.push_back(s[i]);
                        Generated.push(s[i]);
                        generated_cnt++;
                    }
                    for(int i=0;i<3;i++)
                    {
                        if(goal_test(s[i]->a)==1){
                            goal_found=1;
                            goal_state=s[i];
                            break;
                        }
                    }
                }
                Expanded[initial->a]++;
                expanded_cnt++;
                initial=Generated.top();
                if(Generated.size()==0 || goal_found)break;
            }
            limit++;
            Expanded.clear();
    }
    vector<vector<int>>v;
    generated_cnt=expanded_cnt+Generated.size();
    while(goal_state->Parent!=NULL){
        level++;
        v.push_back(goal_state->a);
        path.push_back(goal_state->action);
        goal_state=goal_state->Parent;
    }
    bool lt10=0;
    if(v.size()<11)lt10=1;
    reverse(v.begin(),v.end());
    reverse(path.begin(),path.end());
    cout<<"Solution path :\n";
    for(int i=0;i<path.size();i++){
        cout<<path[i]<<'\n';
        if(lt10){
            cout<<v[i][0]<<' '<<v[i][1]<<' '<<v[i][2]<<'\n';
            cout<<v[i][3]<<' '<<v[i][4]<<' '<<v[i][5]<<'\n';
            cout<<v[i][6]<<' '<<v[i][7]<<' '<<v[i][8]<<'\n';
            cout<<'\n';
        }
    }
    cout<<'\n'<<"Generted nodes = "<<generated_cnt<<'\n';
    cout<<"Expanded nodes = "<<expanded_cnt<<'\n';
    cout<<"Found at level : "<<path.size();
}

int manhattan(vector<int>a){
    int sum=0;
    int arr[3][3];
    bool f1=0,f3=0;
    int c=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            arr[i][j]=a[c++];
        }
    }
    int goal[3][3]={{0,1,1},{2,3,3},{4,5,6}};
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++){
                bool f=0;
                for(int l=0;l<3;l++)
                {
                    if(arr[i][j]==goal[k][l]&&arr[i][j]!=0){
                        sum+=(abs(i-k)+abs(j-l));
                        if(arr[i][j]==1)goal[k][l]=10;
                        if(arr[i][j]==3)goal[k][l]=10;
                        f=1;
                        break;
                    }
                }
                if(f)break;
            }
        }
    }
    return sum;
}

int H1(vector<int>a){
    int goal[9]={0,1,1,2,3,3,4,5,6};
    int c=0;
    for(int i=0;i<a.size();i++){
        if(a[i]!=goal[i]&&a[i]!=0)c++;
    }
    return c;
}

void A_Star(State *initial){
    cout<<"--A* Search Algorithm --\n";
    cout<<"Initial State : \n";
    initial->Print();
    initial->level=0;
    initial->cost=0;
    int cost=manhattan(initial->a)+H1(initial->a)+initial->level;
    vector<pair<int,State*>>v;
    v.push_back(make_pair(initial->cost,initial));
    int Expanded=1,Generated=0;
    map<vector<int>,int>Ex;
    while(1){
        v.erase(v.begin());
        sort(v.begin(),v.end());
        initial=v[0].second;
        Generated++;
        if(goal_test(initial->a))break;
        if(Ex[initial->a]==1)continue;
        if(initial->index==4){//4 moves ,center
                    State *s[4];
                    for(int i=0;i<4;i++){
                        s[i]=new State(initial->a,initial);
                        (s[i]->level)=(s[i]->Parent->level)+1;
                    }
                    s[0]->Left();
                    s[1]->Right();
                    s[2]->Up();
                    s[3]->Down();
                    for(int i=0;i<4;i++){
                        initial->Childs.push_back(s[i]);
                        s[i]->cost=manhattan(s[i]->a)+H1(s[i]->a)+s[i]->level;
                        v.push_back(make_pair(s[i]->cost,s[i]));
                    }
                }

                else if(initial->index==0||initial->index==2||initial->index==6||initial->index==8)//2 moves
                {
                    State *s[2];
                    for(int i=0;i<2;i++){
                        s[i]=new State(initial->a,initial);
                        (s[i]->level)=(s[i]->Parent->level)+1;
                    }
                    if(initial->index==0)
                    {
                        s[0]->Down();
                        s[1]->Right();
                    }
                    else if(initial->index==2)
                    {
                        s[0]->Down();
                        s[1]->Left();
                    }
                    else if(initial->index==6)
                    {
                        s[0]->Right();
                        s[1]->Up();
                    }
                    else if(initial->index==8)
                    {
                        s[0]->Left();
                        s[1]->Up();
                    }
                    for(int i=0;i<2;i++){
                        initial->Childs.push_back(s[i]);
                        s[i]->cost=manhattan(s[i]->a)+H1(s[i]->a)+s[i]->level;
                        v.push_back(make_pair(s[i]->cost,s[i]));
                    }
                }
                else if(initial->index==1||initial->index==3||initial->index==5||initial->index==7)//3moves
                {
                    State *s[3];
                    for (int i = 0; i < 3; i++){
                        s[i]=new State(initial->a,initial);
                        (s[i]->level)=(s[i]->Parent->level)+1;
                    }
                    if(initial->index==1)
                    {
                        s[0]->Left();
                        s[1]->Right();
                        s[2]->Down();
                    }
                    else if(initial->index==3)
                    {
                        s[0]->Up();
                        s[1]->Right();
                        s[2]->Down();
                    }
                    else if(initial->index==5)
                    {
                        s[0]->Left();
                        s[1]->Up();
                        s[2]->Down();
                    }
                    else if(initial->index==7)
                    {
                        s[0]->Left();
                        s[1]->Right();
                        s[2]->Up();
                    }
                    for(int i=0;i<3;i++){
                        initial->Childs.push_back(s[i]);
                        s[i]->cost=manhattan(s[i]->a)+H1(s[i]->a)+s[i]->level;
                        v.push_back(make_pair(s[i]->cost,s[i]));
                    }
                }
                Expanded++;
                Ex[initial->a]++;
    }
    vector<string>path;
    vector<vector<int>>steps;
    State *goal_state=initial;
    while(goal_state->Parent!=NULL){
        path.push_back(goal_state->action);
        steps.push_back(goal_state->a);
        goal_state=goal_state->Parent;
    }
    bool lt10=0;
    if(v.size()<11)lt10=1;
    reverse(v.begin(),v.end());
    reverse(path.begin(),path.end());
    cout<<"Solution path :\n";
    for(int i=0;i<path.size();i++){
        cout<<path[i]<<'\n';
        if(lt10){
            cout<<steps[i][0]<<' '<<steps[i][1]<<' '<<steps[i][2]<<'\n';
            cout<<steps[i][3]<<' '<<steps[i][4]<<' '<<steps[i][5]<<'\n';
            cout<<steps[i][6]<<' '<<steps[i][7]<<' '<<steps[i][8]<<'\n';
            cout<<'\n';
        }
    }
    cout<<"Generated Nodes= "<<Generated+v.size()<<endl;
    cout<<"Expanded Nodes = "<<Expanded<<endl;
    cout<<"Found at level = "<<steps.size();
}

int main(){
    freopen("output.txt","w",stdout);
    vector<int>a{2,1,1,4,3,0,3,5,6};
    auto rng = default_random_engine { random_device {}() };
    shuffle(a.begin(), a.end(), rng);
    State *initial=new State(a,NULL);
    cout<<"Initial state : \n";
    initial->Print();
    BFS(initial);
    cout<<"\n-------------------------------------------\n";
    IDS(initial);
    cout<<"\n-------------------------------------------\n";
    A_Star(initial);
    return 0;
}