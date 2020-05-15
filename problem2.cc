#include<bits/stdc++.h>
using namespace std;

const int M = 26;//alphabet size
const int N = 4e5+10;
#define ll long long int
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
	suffixAutomaton(string &s){
		n = s.length();
		st = new state[2*n];
		// cout<<"here"<<endl;
		last = 0;
		for(int i = 0; i < n; i++){
			addChar(s[i]);
		}
		for(int i = last; i != -1;i = st[i].link) st[i].terminal = true;
	}
	suffixAutomaton(string &s, int tmp){
		n = s.length();
		st = new state[2*n];
		ll ans = 0;
		// cout<<"here"<<endl;
		last = 0;
		for(int i = 0; i < n; i++){
			if(s[i] == '?'){
				cout<<ans<<endl;
			}
			else{
				addChar(s[i]);
				ans+=st[last].len - st[st[last].link].len;
			}
		}
		for(int i = last; i != -1;i = st[i].link) st[i].terminal = true;

	}
	~suffixAutomaton(){
		delete []st;
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
			if(curr == -1) return false;
		}
		return true;
	}
	vector<int> used;
	// call with dfs(0)
	ll dfs(int v){
		ll ret = 0;
		used[v] = 1;
		for(int i = 0; i < M; i++){
			int u = st[v].next[i];
			if(u!=-1 && !used[u]){
				ret += dfs(u);
			}
			else if(u!=1 && used[u]){
				ret+=st[u].cnt1;
			}
		}
		return st[v].cnt1 = ret+1;
	}
	ll countSubstrings(){
		return st[0].cnt1-1;
	}
	void klex(ll csum, ll k, string &ans, int curr){
		if(csum >= k) return;
		for(int i = 0; i < M; i++){
			if(st[curr].next[i] == -1) continue;
			int y = st[curr].next[i];
			if(csum + st[y].cnt1 >= k){
				ans+=('a'+i);
				klex(csum+1, k, ans, y);
				return;
			}
			else{
				csum+=st[y].cnt1;
			}
		} 
		ans = "";
	}
};

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	string s;
	int ind = 0;
	while(cin >> s){
		ind++;
		suffixAutomaton sa(s,ind);
		int n = s.length();
	}
	return 0;
}