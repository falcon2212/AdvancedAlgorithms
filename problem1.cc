#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define ld long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define _h cout<<"here"<<endl;
#define fill(a,v) memset(a,v,sizeof(a));
#define all(v) v.begin(),v.end()
#define rep(i,n) for(int i=0;i<n;i+=1)
#define prarr(a,n) rep(i,n) cout<<a[i]<<" \n"[i==n-1];// printf("%s\n"," " );
#define ff first
#define ss second
#define pu push_back
#define tr(...) cout<<__FUNCTION__<<' '<<__LINE__<<" = ";trace(#__VA_ARGS__, __VA_ARGS__)
template<typename S, typename T> 
ostream& operator<<(ostream& out,pair<S,T> const& p){out<<'('<<p.ff<<", "<<p.ss<<')';return out;}
template<typename T>
ostream& operator<<(ostream& out,vector<T> const& v){
int l=v.size();for(int i=0;i<l-1;i++)out<<v[i]<<' ';if(l>0)out<<v[l-1];return out;}
template<typename T>
void trace(const char* name, T&& arg1){cout<<name<<" : "<<arg1<<endl;}
template<typename T, typename... Args>
void trace(const char* names, T&& arg1, Args&&... args){
const char* comma = strchr(names + 1, ',');cout.write(names, comma-names)<<" : "<<arg1<<" | ";trace(comma+1,args...);}
const int inf = 1e9+10;
const int M = 26;//alphabet size
struct suffixAutomaton{
	struct state{
		int len, link;
		int next[M];
		ll cnt1;
		bool terminal;
		state(){
			len = 0; link = -1; terminal = false;
			cnt1 = 0;
			for(int i = 0; i < M; i++) next[i] = -1;
		}
	};
	state *st;
	int last,sz = 1;
	char offset = 'a';
	int n;
	ll *dp;
	suffixAutomaton(string &s){
		n = s.length();
		dp = new ll[2*n];
		for(int i = 0; i < 2*n; i++) dp[i] = 1;
		st = new state[2*n];
		last = 0;
		for(int i = 0; i < n; i++){
			// cout<<i<<" ";
			addChar(s[i]);
		}
		for(int i = last; i != -1;i = st[i].link) st[i].terminal = true;

		dfs(0);	
	}
	void addChar(char chr){
		int curr = sz++;
		int c = chr-offset;
		st[curr].len = st[last].len+1;
		int p = last;
		for(; p != -1 && st[p].next[c] == -1; p = st[p].link){
			st[p].next[c] = curr;
		}
		last = curr;
		if(p == -1){
			st[curr].link = 0;
			return;
		}
		
		int q = st[p].next[c];
		if(st[p].len + 1 == st[q].len){
			st[curr].link = q;
			return;
		}
		
		int clone = sz++;
		st[clone].len = st[p].len+1;
		for(int i = 0; i < M; i++) st[clone].next[i] = st[q].next[i];
		st[clone].link = st[q].link;
		st[q].link = clone;
		for(; p != -1 && st[p].next[c] == q; p = st[p].link){
			st[p].next[c] = clone;
		}
		st[curr].link = clone;
	}
	void printAutomaton(){
		for(int i = 0; i < sz; i++){
			cout<<"-------BEGIN"<<endl;
			cout<<"i "<<i<<" len(i) "<<st[i].len<<" link(i) "<<st[i].link<<endl;
			for(int j = 0; j < 5; j++) cout<<st[i].next[j]<<" ";cout<<endl;
			cout<<"-------END-----------"<<endl;
		}
	}
	bool isSubstring(string &s1){
		for(int i = 0,curr = 0; i < (int)s1.length(); i++){
			curr = st[curr].next[s1[i]-offset];
			cout<<curr<<endl;
			if(curr == -1) return false;
		}
		return true;
	}
	ll dfs(int v){
		ll ret = 0;
		for(int i = 0; i < M; i++){
			int u = st[v].next[i];
			if(u!=-1){
				ret += dfs(u);
			}
		}
		return st[v].cnt1 = ret+1;
	}
	ll countSubstrings(){
		return st[0].cnt1-1;
	}
	void klex(ll csum, ll k, string &ans, int curr){
		if(csum >= k) return;
		tr(csum, k, ans, curr);
		for(int i = 0; i < M; i++){
			if(st[curr].next[i] == -1) continue;
			int y = st[curr].next[i];
			if(csum + st[y].cnt1 >= k){
				ans+=('a'+i);
				klex(csum+1, k, ans, y);
				return;
			}
			else{
				/*
				state.cnt1 keeps track of number of distinct substrings
				reachable from this state.
				*/
				csum+=st[y].cnt1;
			}
		}	
		ans = "";
	}
};

void solve(){

	// char *s = new char[100010];
	string s;
	cin >> s;
	int n = s.length();
	// cout << s.length()<<endl;
	suffixAutomaton sa(s);
	sa.printAutomaton();
	// s = "aaa";
	// return;
	int q;	
	cin>>q;
	ll k = 0;
	sa.dfs(0);
	string ans = "";
	// for(int i = 1; i <=20 ; i++){
	// 	ans = "";
	// 	cout <<i<<" : ";
	// 	sa.kth(i, ans);
	// 	cout<<ans<<endl;
	// }
	// q = 0;
	while(q--){
		ans = "";
		cin >> k;
		// cnt++;
		sa.klex(0, k, ans, 0);
		if(ans == "") continue;
		cout<<ans<<endl;
	}

}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	// int n = s.length();
	// cout<<sa.countSubstrings()<<endl;
	// // cin >> k;
	// for(int i = 0 ; i <= n; i++){
	// 	cout<<sa.kth(i+1)<<endl;

	// }
	// cout<<sa.kth(1000)<<endl;
	return 0;
}