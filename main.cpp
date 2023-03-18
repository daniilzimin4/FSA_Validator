// Daniil Zimin
// d.zimin@innopolis.university
// tg: daniilzimin4

#include <bits/stdc++.h>

#include <utility>

#pragma GCC optimize("Ofast,no-stack-protector")

using namespace std;

typedef long long ll;
typedef long double ld;

mt19937 rnd(time(0));

#define ioss ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define file2 freopen("C:\\Users\\danii\\CLionProjects\\untitled\\input.txt", "r", stdin); freopen("C:\\Users\\danii\\CLionProjects\\untitled\\output.txt", "w", stdout);
#define file freopen("fsa.txt", "r", stdin); freopen("result.txt", "w", stdout);
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()

template<typename It>
class Range {
    It b, e;
public:
    Range(It b, It e) : b(b), e(e) {}

    It begin() const { return b; }

    It end() const { return e; }
};

template<typename ORange, typename OIt = decltype(std::begin(
        std::declval<ORange>())), typename It = std::reverse_iterator<OIt>>
Range<It> reverse(ORange &&originalRange) {
    return Range<It>(It(std::end(originalRange)), It(std::begin(originalRange)));
}

template<class T>
ll upmax(T &a, T b) { return (b > a) ? a = b, 1 : 0; }

template<class T>
ll upmin(T &a, T b) { return (b < a) ? a = b, 1 : 0; }

const ll inf = 1e18 + 7;

void E5() {
    cout << "Error:\nE5: Input file is malformed\n";
    exit(0);
}

set<string> get(const string &start) { // parse a string of the form 'start'[a,b,c] into set [a, b, c]
    string x;
    cin >> x;
    if (x.substr(0, start.size()) != start || x.size() <= start.size() || x[start.size()] != '[' || x.back() != ']') {
        E5();
    }
    set<string> ans;
    if (x == start + "[]"){ // Check if line present empty set
        return ans;
    }
    string tmp;
    for (int i = (int) start.size() + 1; i < x.size(); i += 1) { // parse
        if (x[i] == ',' || i == x.size() - 1) {
            if (tmp.empty())E5();
            ans.insert(tmp);
            tmp = "";
        } else {
            tmp += x[i];
        }
    }
    return ans;
}

map<pair<string, string>, vector<string>> getTrans(const string &start) { // parse transition line
    map<pair<string, string>, vector<string>> mp; // return map [state, alphabet] = [vector of next states]
    set<string> st = get(start);
    for (auto i: st) {
        string tmp;
        vector<string> tt;
        for (int j = 0; j < i.size(); j += 1) { // parse
            if (i[j] == '>') {
                if (tmp.empty())E5();
                tt.pb(tmp);
                tmp = "";
            } else {
                tmp += i[j];
            }
        }
        if (tmp.empty())E5(); // check Error 5
        tt.pb(tmp);
        if (tt.size() != 3)E5(); // check Error 5
        mp[{tt[0], tt[1]}].pb(tt[2]);
    }
    return mp;
}

void solve() {
    // Read input data
    set<string> states = get("states=");
    set<string> alpha = get("alpha=");
    set<string> init = get("init.st=");
    set<string> fin = get("fin.st=");
    map<pair<string, string>, vector<string>> trans = getTrans("trans=");

    { // Validate for Error 5
        string x;
        while(cin >> x){
            E5();
        }
        for (const auto &i: states) {
            for (auto j: i) {
                if (!(j >= 'a' && j <= 'z') && !(j >= 'A' && j <= 'Z') && !(j >= '0' && j <= '9')) {
                    E5();
                }
            }
        }
        for (const auto &i: alpha) {
            for (auto j: i) {
                if (!(j >= 'a' && j <= 'z') && !(j >= 'A' && j <= 'Z') && !(j >= '0' && j <= '9') && j != '_') {
                    E5();
                }
            }
        }
    }

    { // Validate for Error 1
        for (const auto &i: init) {
            if (!states.contains(i)) {
                cout << "Error:\nE1: A state '" << i << "' is not in the set of states\n";
                exit(0);
            }
        }
        for (const auto &i: fin) {
            if (!states.contains(i)) {
                cout << "Error:\nE1: A state '" << i << "' is not in the set of states\n";
                exit(0);
            }
        }
        for (const auto &i: trans) {
            if (!states.contains(i.first.first)) {
                cout << "Error:\nE1: A state '" << i.first.first << "' is not in the set of states\n";
                exit(0);
            }
            for (const auto &j: i.second) {
                if (!states.contains(j)) {
                    cout << "Error:\nE1: A state '" << j << "' is not in the set of states\n";
                    exit(0);
                }
            }
        }
    }

    { // Validate for Error 3
        for (const auto &i: trans) {
            if (!alpha.contains(i.first.second)) {
                cout << "Error:\nE3: A transition '" << i.first.second << "' is not represented in the alphabet\n";
                exit(0);
            }
        }
    }

    { // Validate for Error 4
        if (init.empty() || init.size() > 1) {
            cout << "Error:\nE4: Initial state is not defined\n";
            exit(0);
        }
    }

    { // Validate for Error 2
        // Check if undirected graph of transitions are connected
        map<string, vector<string>> fullGraph; // from directed trans map, make undirected
        for (const auto &i: trans) {
            for (const auto &j: i.second) {
                fullGraph[i.first.first].pb(j);
                fullGraph[j].pb(i.first.first);
            }
        }
        set<string> used; // simple dfs check
        function<void(string)> dfs = [&](const string &v) {
            used.insert(v);
            for (const auto &to: fullGraph[v]) {
                if (!used.contains(to)) {
                    dfs(to);
                }
            }
        };
        dfs(*init.begin()); // start vertex is init state
        if (used.size() != states.size()) {
            cout << "Error:\nE2: Some states are disjoint\n";
            exit(0);
        }
    }

    { // Calculate type of FSA (complete or incomplete)
        int ok = 1;
        for (const auto &i: states) {
            for (const auto &j: alpha) {
                ok &= trans.contains({i, j});
            }
        }
        // FSA complete only if there are exist every transition from each state
        if (ok) {
            cout << "FSA is complete\n";
        } else {
            cout << "FSA is incomplete\n";
        }
    }


    vector<pair<int, string>> warnings;

    { // W1
        if (fin.empty()) {
            warnings.emplace_back(1, " Accepting state is not defined");
        }
    }

    { // W2
        set<string> used; // simple dfs check (as for error 2, but for directed graph)
        function<void(string)> dfs = [&](const string &v) {
            used.insert(v);
            for (const auto &i: alpha) {
                if (trans.contains({v, i})) {
                    for (const auto &j: trans[{v, i}]) {
                        if (!used.contains(j)) {
                            dfs(j);
                        }
                    }
                }
            }
        };
        dfs(*init.begin());
        if (used.size() != states.size()) {
            warnings.emplace_back(2, " Some states are not reachable from the initial state");
        }
    }

    { // W3
        // FSA is nondeterministic if there are exists two outgoing edges of the same type from the any vertex
        for (const auto &i: trans) {
            if (i.second.size() > 1) {
                warnings.emplace_back(3, " FSA is nondeterministic");
                break;
            }
        }
    }
    if (!warnings.empty()) { // Print warnings
        cout << "Warning:\n";
        for (const auto &i: warnings) {
            cout << "W" << i.first << ':' << i.second << '\n';
        }
    }
}

signed main() {
//    ioss
    file
//   (a += b) -> return value

    int t = 1;
//    cin >> t;
    while (t--) {
        solve();
    }
    // printf("Time taken: %.10fs\n", (double)(clock() - CLOCK_START)/CLOCKS_PER_SEC);
    return 0;
}
