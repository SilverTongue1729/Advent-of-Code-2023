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
  vs grid;
  while(!cin.eof()){
    string s;
    getline(cin,s);
    grid.pb(s);
  }
  
  int n = sz(grid), m = sz(grid[0]);
  
  auto cycle = [&]() -> void {
    // push all 'O's up, they are blocked by '#'
    for_(i,0,m){
      int cnt=0;
      for__(j,n-1,-1){
        if (grid[j][i] == 'O') grid[j][i] = '.', cnt++;
        if (grid[j][i] == '#' or j==0) {
          int incr = (grid[j][i] == '#');
          for_(k,j+incr,j+incr+cnt) grid[k][i] = 'O';
          cnt = 0;
        }
      }
    }
    
    // push all 'O's left, they are blocked by '#'
    for_(i,0,n){
      int cnt=0;
      for__(j,m-1,-1){
        if (grid[i][j] == 'O') grid[i][j] = '.', cnt++;
        if (grid[i][j] == '#' or j==0) {
          int incr = (grid[i][j] == '#');
          for_(k,j+incr,j+incr+cnt) grid[i][k] = 'O';
          cnt = 0;
        }
      }
    }
    
    // push all 'O's down, they are blocked by '#'
    for_(i,0,m){
      int cnt=0;
      for_(j,0,n){
        if (grid[j][i] == 'O') grid[j][i] = '.', cnt++;
        if (grid[j][i] == '#' or j==n-1) {
          int incr = (grid[j][i] == '#');
          for__(k,j-incr,j-incr-cnt) grid[k][i] = 'O';
          cnt = 0;
        }
      }
    }
    
    // push all 'O's left, they are blocked by '#'
    for_(i,0,n){
      int cnt=0;
      for_(j,0,m){
        if (grid[i][j] == 'O') grid[i][j] = '.', cnt++;
        if (grid[i][j] == '#' or j==m-1) {
          int incr = (grid[i][j] == '#');
          for__(k,j-incr,j-incr-cnt) grid[i][k] = 'O';
          cnt = 0;
        }
      }
    }

  };
  
  int ind=0;
  cycle();
  ind++;
    
  map<vs,int> mp;
  
  mp[grid] = ind;

  while (true) {
    cycle();
    ind++;

    if (mp.count(grid)) {
      int st = mp[grid];
      int len = ind - st;
      int rem = (1000000000 - st) % len;
      for_(i,0,rem) cycle();
      break;
    }

    mp[grid] = ind;
  }
  
  ll ans=0;
  for_(i,0,n) for_(j,0,m) if (grid[i][j] == 'O') ans += n-i;
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
