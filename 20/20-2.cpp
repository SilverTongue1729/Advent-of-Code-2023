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
template<typename Iter> bool is_unique(Iter begin, Iter end) { set<typename iterator_traits<Iter>::value_type> unique_set; for (Iter it = begin; it != end; ++it) if (!unique_set.insert(*it).second) return false; return true; }

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

namespace internal {

// @param m `1 <= m`
// @return x mod m
constexpr long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

// Fast modular multiplication by barrett reduction
// Reference: https://en.wikipedia.org/wiki/Barrett_reduction
// NOTE: reconsider after Ice Lake
struct barrett {
    unsigned int _m;
    unsigned long long im;

    // @param m `1 <= m < 2^31`
    barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}

    // @return m
    unsigned int umod() const { return _m; }

    // @param a `0 <= a < m`
    // @param b `0 <= b < m`
    // @return `a * b % m`
    unsigned int mul(unsigned int a, unsigned int b) const {
        // [1] m = 1
        // a = b = im = 0, so okay

        // [2] m >= 2
        // im = ceil(2^64 / m)
        // -> im * m = 2^64 + r (0 <= r < m)
        // let z = a*b = c*m + d (0 <= c, d < m)
        // a*b * im = (c*m + d) * im = c*(im*m) + d*im = c*2^64 + c*r + d*im
        // c*r + d*im < m * m + m * im < m * m + 2^64 + m <= 2^64 + m * (m + 1) < 2^64 * 2
        // ((ab * im) >> 64) == c or c + 1
        unsigned long long z = a;
        z *= b;
#ifdef _MSC_VER
        unsigned long long x;
        _umul128(z, im, &x);
#else
        unsigned long long x =
            (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
        unsigned int v = (unsigned int)(z - x * _m);
        if (_m <= v) v += _m;
        return v;
    }
};

// @param n `0 <= n`
// @param m `1 <= m`
// @return `(x ** n) % m`
constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
    if (m == 1) return 0;
    unsigned int _m = (unsigned int)(m);
    unsigned long long r = 1;
    unsigned long long y = safe_mod(x, m);
    while (n) {
        if (n & 1) r = (r * y) % _m;
        y = (y * y) % _m;
        n >>= 1;
    }
    return r;
}

// Reference:
// M. Forisek and J. Jancina,
// Fast Primality Testing for Integers That Fit into a Machine Word
// @param n `0 <= n`
constexpr bool is_prime_constexpr(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 7 || n == 61) return true;
    if (n % 2 == 0) return false;
    long long d = n - 1;
    while (d % 2 == 0) d /= 2;
    constexpr long long bases[3] = {2, 7, 61};
    for (long long a : bases) {
        long long t = d;
        long long y = pow_mod_constexpr(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = y * y % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}
template <int n> constexpr bool is_prime = is_prime_constexpr(n);

// @param b `1 <= b`
// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};

    // Contracts:
    // [1] s - m0 * a = 0 (mod b)
    // [2] t - m1 * a = 0 (mod b)
    // [3] s * |m1| + t * |m0| <= b
    long long s = b, t = a;
    long long m0 = 0, m1 = 1;

    while (t) {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b

        // [3]:
        // (s - t * u) * |m1| + t * |m0 - m1 * u|
        // <= s * |m1| - t * u * |m1| + t * (|m0| + |m1| * u)
        // = s * |m1| + t * |m0| <= b

        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    // by [3]: |m0| <= b/g
    // by g != b: |m0| < b/g
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}

// Compile time primitive root
// @param m must be prime
// @return primitive root (and minimum in now)
constexpr int primitive_root_constexpr(int m) {
    if (m == 2) return 1;
    if (m == 167772161) return 3;
    if (m == 469762049) return 3;
    if (m == 754974721) return 11;
    if (m == 998244353) return 3;
    int divs[20] = {};
    divs[0] = 2;
    int cnt = 1;
    int x = (m - 1) / 2;
    while (x % 2 == 0) x /= 2;
    for (int i = 3; (long long)(i)*i <= x; i += 2) {
        if (x % i == 0) {
            divs[cnt++] = i;
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) {
        divs[cnt++] = x;
    }
    for (int g = 2;; g++) {
        bool ok = true;
        for (int i = 0; i < cnt; i++) {
            if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}
template <int m> constexpr int primitive_root = primitive_root_constexpr(m);

}

std::pair<long long, long long> crt(const std::vector<long long>& r,
                                    const std::vector<long long>& m) {
    assert(r.size() == m.size());
    int n = int(r.size());
    // Contracts: 0 <= r0 < m0
    long long r0 = 0, m0 = 1;
    for (int i = 0; i < n; i++) {
        assert(1 <= m[i]);
        long long r1 = internal::safe_mod(r[i], m[i]), m1 = m[i];
        if (m0 < m1) {
            std::swap(r0, r1);
            std::swap(m0, m1);
        }
        if (m0 % m1 == 0) {
            if (r0 % m1 != r1) return {0, 0};
            continue;
        }
        // assume: m0 > m1, lcm(m0, m1) >= 2 * max(m0, m1)

        // (r0, m0), (r1, m1) -> (r2, m2 = lcm(m0, m1));
        // r2 % m0 = r0
        // r2 % m1 = r1
        // -> (r0 + x*m0) % m1 = r1
        // -> x*u0*g % (u1*g) = (r1 - r0) (u0*g = m0, u1*g = m1)
        // -> x = (r1 - r0) / g * inv(u0) (mod u1)

        // im = inv(u0) (mod u1) (0 <= im < u1)
        long long g, im;
        std::tie(g, im) = internal::inv_gcd(m0, m1);

        long long u1 = (m1 / g);
        // |r1 - r0| < (m0 + m1) <= lcm(m0, m1)
        if ((r1 - r0) % g) return {0, 0};

        // u1 * u1 <= m1 * m1 / g / g <= m0 * m1 / g = lcm(m0, m1)
        long long x = (r1 - r0) / g % u1 * im % u1;

        // |r0| + |m0 * x|
        // < m0 + m0 * (u1 - 1)
        // = m0 + m0 * m1 / g - m0
        // = lcm(m0, m1)
        r0 += x * m0;
        m0 *= u1;  // -> lcm(m0, m1)
        if (r0 < 0) r0 += m0;
    }
    return {r0, m0};
}

using Pulse = tuple<string, string, bool>;

class Module {
 public:
  Module(const string& name, const vector<string>& destinations) : name(name), destinations(destinations) {}

  virtual ~Module() = default;

  virtual bool processPulse(const string& sender, bool pulse, queue<Pulse>& pulses) = 0;
  
  inline ostream& operator<<(ostream& out) const {
    cerr << name << ": ";
    for (auto& dest : destinations) cerr << dest << " ";
    cerr << nl;
    return out;
  }

  const string& getName() const { return name; }
  const vs& getDestinations() const { return destinations; }

 protected:
  const string name;
  const vs destinations;
};

class Button : public Module {
 public:
  Button(const string& name, const vs& destinations) : Module(name, destinations) {}

  bool processPulse(const string& sender, bool pulse, queue<Pulse>& pulses) override {
    for (auto dest : destinations) pulses.push({dest, name, pulse});
    return pulse;
  }
};

class Broadcast : public Module {
 public:
  Broadcast(const string& name, const vs& destinations) : Module(name, destinations) {}

  bool processPulse(const string& sender, bool pulse, queue<Pulse>& pulses) override {
    for (auto dest : destinations) pulses.push({dest, name, pulse});
    return pulse;
  }
};

class FlipFlop : public Module {
 public:
  FlipFlop(const string& name, const vs& destinations) : Module(name, destinations), state(false) {}

  bool processPulse(const string& sender, bool pulse, queue<Pulse>& pulses) override {
    if (pulse) return pulse;
    state = !state;
    for (auto& dest: destinations) pulses.push({dest, name, state});
    return state;
  }
  
  bool getState() const { return state; }
  
 private:
  bool state;
};

class Conjunction : public Module {
 public:
  Conjunction(const string& name, const vs& destinations) : Module(name, destinations) {}

  bool processPulse(const string& sender, bool pulse, queue<Pulse>& pulses) override {
    states[sender] = pulse;
    bool high = true;
    for (auto& [n, state] : states) if (!state) {
      high = false;
      break;
    }
    for (auto& dest: destinations) pulses.push({dest, name, !high});
    return !high;
  }
  
  const map<string, bool>& getStates() const { return states; }
  
  void addState(const string& name) {
    states[name] = false;
  }
  
 private:
  map<string, bool> states;
};

void solve(){
  // read modules
  map<string, unique_ptr<Module>> modules;
  set<string> conjunctions;
  string prx;
  
  while(!cin.eof()) {
    string line; getline(cin, line);
    istringstream iss(line);
    string name; iss >> name;
    string temp; iss >> temp;
    vs destinations;
    string dest;
    while (iss >> dest) {
      if (dest.back() == ',') dest.pop_back();
      destinations.push_back(dest);
    }
    
    if (name[0] == '%') {  // FlipFlop
      name = name.substr(1);
      modules[name] = make_unique<FlipFlop>(name, destinations);
    } elif (name[0] == '&'){  // Conjunction
      name = name.substr(1);
      modules[name] = make_unique<Conjunction>(name, destinations);
      conjunctions.insert(name);
    } else  // Broadcast
      modules[name] = make_unique<Broadcast>(name, destinations);
      
    if (destinations == vs{"rx"}) prx = name;
  }
  
  print(prx);
  
// print modules
  // for (auto& [name, module] : modules) module->operator<<(cerr);
  map<string,int> cycles;  // name, start, len
  
  // add states to conjunctions
  for (auto& [name, module] : modules) 
    for (auto& dest : module->getDestinations()) {
      if (conjunctions.count(dest)) 
        static_cast<Conjunction*>(modules[dest].get())->addState(name);
      if (dest == prx) { cycles[name] = 0; print(name); }
    }
    
  auto button = Button("button", {"broadcaster"});
  
  int n = sz(cycles), cnt=0;
  // process pulses
  for (int i=0; cnt<n; i++) {
    if (i%10000==0) cerr<<i<<nl;
    queue<Pulse> pulses;
    button.processPulse("init", false, pulses);
    while (!pulses.empty()) {
      auto [dest, src, state] = pulses.front(); pulses.pop();
      if (modules[dest] == nullptr) continue;
      auto pulse = modules[dest]->processPulse(src, state, pulses);
      if (cycles.count(dest) and pulse) {
        cycles[dest] = i+1;
        cnt++;
      }
    }
  }
  
  ll ans = 1;
  for (auto& [name, len] : cycles) {
    ans = lcm(ans, len);
  }
  
  cout<<ans<<nl;
  
  // vl r, m;
  // for (auto& [name, cycle] : cycles) {
  //   r.pb(cycle.ff);
  //   m.pb(cycle.ss);
  // }
  
  // auto [start, len] = crt(r,m);
  // cout<<start<<nl;
  
}

int main(){
#ifdef LOCAL
  auto fret = freopen("/home/sriteja/Competitive Programming/Debugging/IO/output_01.txt","w",stderr);
  if (!fret) { perror("unable to open stderr"); return 1; }
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
