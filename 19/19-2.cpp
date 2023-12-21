#include "bits/stdc++.h"
using namespace std;

#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,bmi,bmi2,lzcnt,popcnt,mmx,avx,avx2,tune=native")

// #define for_(i,s,te) for (ll i=s,e=te; ((i<e)and(s<e)) or ((i>e)and(s>=e)); (s<e)?i++:i--)
#define for_(i,s,e) for (int i=s;i<e; i++)
#define for__(i,s,e) for (int i=s;i>e; i--)
#define popcount(x) __builtin_popcount(x)  // count set bits
#define popcountll(x) __builtin_popcountll(x)
#define gcd(x,y) __gcd(x,y)
#define clz(x) __builtin_clz(x)  // count leading zeros
#define clzll(x) __builtin_clzll(x)
#define ctz(x) __builtin_ctz(x)  // count trailing zeros
#define ctzll(x) __builtin_ctzll(x)
#define sz(a) int(a.size())
#define all(x) (x).begin(),(x).end()
#define allr(x) x.rbegin(),x.rend()
#define uniq(v) (v).erase(unique(all(v)),(v).end())
#define clr(x) memset(x,0,sizeof(x))
#define nl "\n"
#define _ << ' ' <<
#define elif else if
#define pb emplace_back
#define MP make_pair
#define UB upper_bound
#define LB lower_bound
#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<string> vs;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<vpii> vvpii;
typedef vector<vpll> vvpll;
typedef map<int,int> mii;
typedef map<ll,ll> mll;
// typedef array<int, 2> ii;
constexpr ll MOD = 1e9+7; // 998244353;

template<typename T> inline ll mod(T a, ll md = MOD) { return ((a%md)+md)%md; }
template<typename Iter> bool is_unique(Iter begin, Iter end) { std::set<typename std::iterator_traits<Iter>::value_type> unique_set; for (Iter it = begin; it != end; ++it) if (!unique_set.insert(*it).second) return false; return true; }

template<typename T1,typename T2> inline istream& operator >>(istream& in, pair<T1,T2>& a) { in>>a.ff>>a.ss; return in; }
template<typename T1,typename T2> inline ostream& operator <<(ostream& out, const pair<T1,T2>& a) { out<<a.ff<<" "<<a.ss; return out; }
template<typename T> inline istream& operator >>(istream& in, vector<T>& v) { for_(i,0,sz(v)) in>>v[i]; return in; }
template<typename T> typename enable_if<!is_same<T,char>::value,ostream&>::type operator<<(ostream& out, const vector<T>& v) { for(auto& e:v) out<<e<<" "; return out; }
template<typename T> ostream& operator<<(ostream& out, const vector<vector<T>>& vv) { for (auto& v:vv) out<<v<<nl; return out; }
template<typename T> inline istream& operator >>(istream& in, set<T>& s) { string str; while(!sz(str)) getline(in,str); istringstream iss(str); T vs; while (iss>>vs) s.insert(vs); return in; }
template<typename T> inline ostream& operator <<(ostream& out, const set<T>& s) { for(auto& vs:s) out<<vs<<" "; return out; }
template<typename T> inline istream& operator >>(istream& in, multiset<T>& s) { string str; while(!sz(str)) getline(in,str); istringstream iss(str); T vs; while(iss>>vs) s.insert(vs); return in; }
template<typename T> inline ostream& operator <<(ostream& out, const multiset<T>& s) { for(auto& vs:s) out<<vs<<" "; return out; }
template<typename T1,typename T2> inline pair<T1,T2> operator +(pair<T1,T2>& l,pair<T1,T2>& r) { return {l.ff+r.ff,l.ss+r.ss}; }

template<typename T> inline void g_in(vector<vector<T>>& g, int m, int rev) { T x,y; for_(i,0,m){ cin>>x>>y; g[--x].pb(--y); if(rev) g[y].pb(x); } }
template<typename T1, typename T2> inline void g_in(vector<vector<pair<T1,T2>>>& g, int m, int rev) { T1 x,y; T2 c; for_(i,0,m){ cin>>x>>y>>c; g[--x].pb(--y,c); if(rev) g[y].pb(x,c); } } 

#ifdef LOCAL
#include "/home/sriteja/Competitive Programming/Debugging/print.cpp"
#else
#define NDEBUG
#define print(...) ((void)0)  // print to cerr
#define printl(...) ((void)0)
#define cerr if(0) cerr
#endif

void solve(){
  struct Part {
    int x,m,a,s;
    
    int& operator[](char c) {
      switch(c) {
        case 'x': return x;
        case 'm': return m;
        case 'a': return a;
        case 's': return s;
      }
    }
  };
  struct Cond {
    char c;  // x,m,a,s
    bool comp;  // 0: <, 1: >
    int val;
  };
  struct Workflow {
    string name;
    vector<pair<Cond,string>> conds; // condition, map
    string def_map;
  };
  
  // read workflows
  vector<Workflow> workflows;
  int _i=0;
  while (1) {
    string line; getline(cin,line);
    if (line == "") break;
    istringstream iss(line);
    
    Workflow w;
    
    // read name
    while (1) {
      char c; iss>>c;
      if (c == '{') break;
      w.name += c;
    }
    
    // read conditions and maps separated by commas
    while (1) {
      char c, sign; iss>>c>>sign;
      if (sign!='<' and sign!='>') {
        w.def_map += c;
        if (sign!='}') {
          w.def_map += sign;
          while (1) {
            char c; iss>>c;
            if (c == '}') break;
            w.def_map += c;
          }
        }
        break;
      }
      
      Cond cond;
      cond.c = c;
      
      if (sign == '<') cond.comp = 0;
      else if (sign == '>') cond.comp = 1;
      
      int val; iss>>val;
      cond.val = val;
      
      char temp; iss>>temp;
      
      string map;
      while (1) {
        char c; iss>>c;
        if (c == ',') break;
        map += c;
      }
      
      w.conds.pb(cond,map);
    }
        
    workflows.pb(w);
  }
  
  // print work flows
  for (auto& w:workflows) {
    cerr<<w.name _ "{ ";
    for (auto& [c,m]:w.conds) 
      cerr<<c.c _ c.comp _ c.val _ ":" _ m _ ", ";
    cerr<<w.def_map<<" }"<<nl;
  }
  cerr<<nl<<flush;
  
  // read parts
  vector<Part> parts;
  while (1) {
    string line; getline(cin,line);
    if (line == "") break;
    istringstream iss(line);
    Part p;
    char temp; iss>>temp;
    
    for_(i,0,4) {
      char c; iss>>c;
      iss>>temp;
      if (c == 'x') iss>>p.x;
      elif (c == 'm') iss>>p.m;
      elif (c == 'a') iss>>p.a;
      elif (c == 's') iss>>p.s;
      iss>>temp;
      if (temp == '}') break;
    }
    
    parts.pb(p);
  }
  
  // print parts
  // for (auto& p:parts) 
  //   cerr<<"{ x="<<p.x _ " m="<<p.m _ " a="<<p.a _ " s="<<p.s<<" }"<<nl;
  // cerr<<nl<<flush;
  
  map<string,int> name_to_idx;
  for_(i,0,sz(workflows)) name_to_idx[workflows[i].name] = i;
  

  ll ans=0;
  
  auto dfs = [&](auto self, Part l, Part u, string map) -> void {
    if (l.x>u.x or l.m>u.m or l.a>u.a or l.s>u.s) return;
    if (map == "A") {
      ans += ll(u.x-l.x+1)*ll(u.m-l.m+1)*ll(u.a-l.a+1)*ll(u.s-l.s+1);
      return;
    } elif (map == "R") return;
    
    auto wf = workflows[name_to_idx[map]];
    
    for (auto& [c,m] : wf.conds){
      if (c.comp == 0) {  // <
        int prev = u[c.c];
        u[c.c] = min(u[c.c],c.val-1);
        self(self,l,u,m);
        u[c.c] = prev;
        l[c.c] = max(l[c.c],c.val);
      }
      elif (c.comp == 1) {  // >
        int prev = l[c.c];
        l[c.c] = max(l[c.c],c.val+1);
        self(self,l,u,m);
        l[c.c] = prev;
        u[c.c] = min(u[c.c],c.val);
      }
      if (l.x>u.x or l.m>u.m or l.a>u.a or l.s>u.s) return;
    }
    
    self(self,l,u,wf.def_map);
  };
  
  Part l = {1,1,1,1}, u = {4000,4000,4000,4000};
  dfs(dfs,l,u,"in");
  
  cout<<ans<<nl;
}

int main(){
#ifdef LOCAL
  auto fret = freopen("/home/sriteja/Competitive Programming/Debugging/IO/output_01.txt","w",stderr);
  if (!fret) { perror("ERROR"); return 1; }
#endif
  ios_base::sync_with_stdio(false); cin.tie(0);

  int tt=1,ttt;
  print(tt);
  ttt = tt;
  // auto start = chrono::steady_clock::now();
  while (tt--) {
    cerr<<"-------------- TC "<<ttt-tt<<" -----------------"<<nl;
    solve();
  };
  cerr<<"-------------- DONE -----------------"<<nl;
  
  string warning_string;
  while (getline(cin,warning_string).eof() == false or warning_string != ""){
    if (warning_string == "") continue;
    cerr<<"\n!!!!!! WARNING : UNREAD INPUT !!!!!!!\n"<<warning_string<<nl;
    while (getline(cin,warning_string)) cerr<<warning_string<<nl;
    break;
  }
  // auto end = chrono::steady_clock::now();
  // cerr << "Elapsed (s): " << chrono::duration_cast<chrono::milliseconds>(end - start).count()/1000.0 << endl;

  return 0;
}
