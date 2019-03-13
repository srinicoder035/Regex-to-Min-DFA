#include<bits/stdc++.h>
using namespace std;
#define CHARSET 26

struct nst
{
    vector<int> a[CHARSET], e;
    bool f=0;
    bool s=0;
};

struct dst
{
    int a[CHARSET] = {-1};
    bool f=0;
    bool s=0;
};

bool present[CHARSET];

class Nfa 
{
    private:
        int nfa_size;
        stack<int> st;
    public:
        vector<nst> nfa;
        struct nst init_nfa_state;
        int start_state;
        int final_state;
        Nfa() 
        {
            nfa_size = 0;
            memset(present,false,sizeof(present));
        }
        // Utility to perform Union
        void union_()
        {
            nfa.push_back(init_nfa_state);
            nfa.push_back(init_nfa_state);
            int d = st.top(); st.pop();
            int c = st.top(); st.pop();
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            nfa[nfa_size].e.push_back(a);
            nfa[nfa_size].e.push_back(c);
            nfa[b].e.push_back(nfa_size+1);
            nfa[d].e.push_back(nfa_size+1);
            st.push(nfa_size);
            nfa_size++;
            st.push(nfa_size);
            nfa_size++;
        }
        //Utility to perform Concatination
        void concatenation()
        {
            int d = st.top(); st.pop();
            int c = st.top(); st.pop();
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            nfa[b].e.push_back(c);
            st.push(a);
            st.push(d);
        }
        // To perform Kleene Closure
        void kleeneClosure()
        {
            nfa.push_back(init_nfa_state);
            nfa.push_back(init_nfa_state);
            int b = st.top();
            st.pop();
            int a = st.top();
            st.pop();
            nfa[nfa_size].e.push_back(a);
            nfa[nfa_size].e.push_back(nfa_size+1);
            nfa[b].e.push_back(a);
            nfa[b].e.push_back(nfa_size+1);
            st.push(nfa_size);
            nfa_size++;
            st.push(nfa_size);
            nfa_size++;
        }

        void character(int i)
        {
            nfa.push_back(init_nfa_state);
            nfa.push_back(init_nfa_state);
            present[i] = true;
            nfa[nfa_size].a[i].push_back(nfa_size+1);
            st.push(nfa_size);
            nfa_size++;
            st.push(nfa_size);
            nfa_size++;
        }
        // Utility to print the NFA
        void printNFA()
        {
            cout<<endl<<endl;
            cout<<"State\t|";
            for(int i=0;i<CHARSET;i++)
            {
                if(present[i])
                    cout<<"\t"<<char(i+'a')<<"\t|";
            }
            cout<<"\teps\t|accepting state|  start state  |"<<endl;
            for(unsigned int i=0; i<nfa.size(); i++)
            {
                
                cout<<i<<"\t|\t";
                for(unsigned int k=0;k<CHARSET;k++)
                {
                    if(present[k])
                    {
                        for(unsigned int j=0; j<nfa[i].a[k].size(); j++)
                            cout<<nfa[i].a[k][j]<<' ';
                        cout<<"\t|\t";
                    }    
                }
                for(unsigned int j=0; j<nfa[i].e.size(); j++)cout<<nfa[i].e[j]<<' ';
                cout<<"\t|\t";
                if(nfa[i].f)
                    cout<<"Yes"; 
                else 
                    cout<<"No";
                cout<<"\t|\t";
                if(nfa[i].s)
                    cout<<"Yes"; 
                else 
                    cout<<"No";
                cout<<"\t|\n";

            }
        }
        void setState()
        {
            final_state=st.top();st.pop();
            start_state=st.top();st.pop();
            nfa[final_state].f=1;
            nfa[start_state].s=1;
        }

};

class Dfa 
{
    private:
        int dfa_size;
    public:
        vector<dst> dfa;
        struct dst init_dfa_state;
        Dfa()
        {
            dfa_size = 0;
        }
        // Utility to print the DFA
        void printDFA(){
            cout<<endl;
            cout<<"STATE\t|";
            for(int i=0;i<CHARSET;i++)
            {
                if(present[i])
                    cout<<"\t"<<char(i+'a')<<"\t|";
            }
            cout<<"\tFINAL\t|\tSTART\t|"<<endl;
            for(int i=0;i<dfa.size();i++){
                cout<<i<<"\t|\t";
                for(int j=0;j<CHARSET;j++)
                {
                    if(present[j])
                        cout<<dfa[i].a[j]<<"\t|\t";
                }
                cout<<dfa[i].f<<"\t|\t"<<dfa[i].s<<"\t|"<<endl;
            }
        }
};

string dispregex;


int priority(char c){
    switch(c){
        case '*': return 3;
        case '.': return 2;
        case '+': return 1;
        default: return 0;
    }
}

string insertConcat(string regexp){
    string ret="";
    char c,c2;
    for(unsigned int i=0; i<regexp.size()-1; i++){
        c=regexp[i];
        c2=regexp[i+1];
        ret+=c;
        if(c!='('&&c2!=')'&&c!='+'&&c2!='+'&&c2!='*'){
            ret+='.';
        }
    }
    ret+=regexp[regexp.size()-1];
    return ret;
}
//Utility to convert Regular Expression to Postfix Expression
string regularExpressionToPostfix(string regexp)
{
    string postfix="";
    stack<char> op;
    char c;
    for(unsigned int i=0; i<regexp.size(); i++)
    {
        switch(regexp[i])
        {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                postfix+=regexp[i]; break;
            case '(':
                op.push(regexp[i]); break;
            case ')':
                while(op.top()!='('){
                    postfix+=op.top();
                    op.pop();
                }
                op.pop();
                break;
            default:
                while(!op.empty()){
                    c=op.top();
                    if(priority(c)>=priority(regexp[i])){
                        postfix+=op.top();
                        op.pop();
                    }
                    else break;
                }
                op.push(regexp[i]);
        }
    }
    while(!op.empty())
    {
        postfix += op.top();
        op.pop();
    }
    return postfix;
}

//Utility to convert a postfix expression to NFA
void postfixNFAConversion(string postfix, Nfa* n)
{
    for(unsigned int i=0; i<postfix.size(); i++)
    {
        switch(postfix[i])
        {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z': n->character(postfix[i]-'a'); break;
        case '*': n->kleeneClosure(); break;
        case '.': n->concatenation(); break;
        case '+': n->union_();
        }
    }
}
// Utility to perform Epsilon Closure
void epsilonClosure(int state, set<int>&si, Nfa* n) {
    for(unsigned int i=0;i<n->nfa[state].e.size();i++){
        if(si.count(n->nfa[state].e[i])==0){
            si.insert(n->nfa[state].e[i]);
            epsilonClosure(n->nfa[state].e[i],si,n);
        }
    }
}

set<int> changeState(int c, set<int>&si ,Nfa* n) {
    set<int> temp;
    for (set<int>::iterator it=si.begin(); it!=si.end(); ++it){
        for(unsigned int j=0;j<n->nfa[*it].a[c].size();j++){
            temp.insert(n->nfa[*it].a[c][j]);
        }
    }
    return temp;
}
//Utility to convert NFA to DFA
void NFAtoDFAConversion(set<int>&si,queue<set<int> >&que,int start_state, Nfa* n, Dfa* d){
    map<set<int>, int> mp;
    mp[si]=-1;
    set<int> temp1;
    set<int> temp2;
    int ct=0;
    si.clear();
    si.insert(start_state);
    epsilonClosure(start_state,si,n);
    if(mp.count(si)==0){
        mp[si]=ct++;
        que.push(si);
    }
    int p=0;    //state count dfa
    bool f1=false;
    while(que.size()!=0){
        for(int i=0;i<CHARSET;i++)
        {
            if(present[i])
            {
                d->dfa.push_back(d->init_dfa_state);
                si=que.front();
                f1=false;
                //final state check
                for (set<int>::iterator it=si.begin(); it!=si.end(); ++it){
                    if(n->nfa[*it].f==true)
                        f1=true;
                }
                d->dfa[p].f=f1;
                temp1=changeState(i,si,n);
                si=temp1;
                for (set<int>::iterator it=si.begin(); it!=si.end(); ++it){
                    epsilonClosure(*it,si,n);
                }
                if(mp.count(si)==0){
                    mp[si]=ct++;
                    que.push(si);
                    d->dfa[p].a[i]=ct-1;
                }
                else{
                    d->dfa[p].a[i]=mp.find(si)->second;
                }
                temp1.clear(); 
            }
        }
        que.pop();
        p++;
    }
    bool final_flg = false;
    for(int i=0;i<p;i++){
        for(int j=0;j<CHARSET;j++)
        {
            if(present[j])
            {
                if(d->dfa[i].a[j]==-1)
                {
                    d->dfa[i].a[j]=p;
                    final_flg = true;
                }
            }      
        }
    }
    if(final_flg)
    {
        d->dfa.push_back(d->init_dfa_state);
        for(int i=0;i<CHARSET;i++)
        {
            if(present[i])
                d->dfa[p].a[i]=p;
        }
    }
    int sz = d->dfa.size();
    if(final_flg){
      for(int i=p+1;i<sz;i++)
        {
            d->dfa.pop_back();
        }     
    }
    else{
        for(int i=p;i<sz;i++)
        {
            d->dfa.pop_back();
        }
    }
}

Dfa minimize_dfa(vector<dst> dfa) {
    vector<int> grp(dfa.size());    
    vector<vector<int> > part(2, vector<int>()); 
    part[0].push_back(0);
    for(int i=1; i<(int)grp.size(); i++) {
        if(dfa[i].f==dfa[0].f) {
            grp[i]=0;
            part[0].push_back(i);
        } else {
            grp[i]=1;
            part[1].push_back(i);
        }
    }

    if(!part[1].size()) part.erase(part.end());

    bool chk=true;  
    int strt = 0;   
    while(chk) {
        chk=false;
        for(int i=0; i<part.size(); i++) {
            for(int j=0; j<CHARSET; j++) {
                if(present[j]) {
                    vector<pair<int,int> > trans(part[i].size());   
                    for(int k=0; k<part[i].size(); k++) {
                        if(dfa[part[i][k]].a[j] >= 0)
                            trans[k] = make_pair(grp[dfa[part[i][k]].a[j]],part[i][k]);
                        else
                            trans[k] = make_pair(-1,part[i][k]);
                    }
                    sort(trans.begin(), trans.end());
                    if(trans[0].first!=trans[trans.size()-1].first) {
                        chk=true;

                        int k, m = part.size()-1;

                        part[i].clear();
                        part[i].push_back(trans[0].second);
                        for(k=1; k<trans.size() and (trans[k].first==trans[k-1].first); k++) {
                            part[i].push_back(trans[k].second);
                        }

                        while(k<trans.size()) {
                            if(trans[k].first!=trans[k-1].first) {
                                part.push_back(vector<int> ());
                                m++;
                            }
                            grp[trans[k].second] = m;
                            part[m].push_back(trans[k].second);
                            k++;
                        }
                    }
                }
            }
        }
    }

    for(int i=0; i<part.size(); i++) {
        for(int j=0; j<part[i].size(); j++) {
            if(part[i][j]==0) strt=i;
        }
    }

    Dfa ans;
    for(int i=0; i<(int)part.size(); i++) {
        ans.dfa.push_back(ans.init_dfa_state);
        for(int j=0;j<CHARSET;j++)
        {
            if(present[j])
            {
                ans.dfa[i].a[j] = (dfa[part[i][0]].a[j]>=0)?grp[dfa[part[i][0]].a[j]]:-1;
            }
        }
        ans.dfa[i].f = dfa[part[i][0]].f;
    }
    ans.dfa[strt].s = 1;
    return ans;
}

int main()
{
    string regexp,postfix;
    cout<<"Enter the Regular Expression "<<endl;
    cin>>regexp;
    dispregex=regexp;
    regexp=insertConcat(regexp);
    postfix = regularExpressionToPostfix(regexp);
    cout<<"Postfix Expression "<<endl<<postfix<<endl;
    Nfa n;
    postfixNFAConversion(postfix,&n);
    n.setState();
    cout<<"Phase 1: Converting regular expression  to nfa using Thompson's construction algorithm"<<endl<<endl;        
    n.printNFA();
    cout<<endl<<"Phase 1 completed."<<endl;
    set<int> si;
    queue<set<int> > que;
    Dfa d;
    NFAtoDFAConversion(si,que,n.start_state,&n,&d);
    cout<<"Phase 2: Conversion from NFA to DFA "<<endl<<endl;
    d.printDFA();
    cout<<endl<<"Phase 2 completed."<<endl;
    Dfa min_dfa = minimize_dfa(d.dfa);
    cout<<endl;
    cout<<"Phase 3: Conversion from DFA to min DFA "<<endl<<endl;
    min_dfa.printDFA();
    cout<<endl;
    return 0;
}