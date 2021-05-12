//参考サイト : http://www.ic-net.or.jp/home/takaken/nt/slide/hash.html

#include<bits/stdc++.h>
#define rep(i,n) for(int i = 0; i < (n); ++i)
using namespace std;
#define pri(str) cout << str << endl
using ll = long long;
using P = pair<int, int>;

const ll MX = 1e18;
const long double PI = acos(-1);

/* 順列型の最小完全ハッシュ関数 
string s:ハッシュの数列, P p: (階乗, 総和)*/
P factorial_hash(string s, P p)
{
    if(s.length() <= 1)
        return P(1,0);
    else
    {
        int len = s.length()-1;
        int num = s[0]-'0';
        for(int i = 1; i < s.length(); i++)
        {
            if(s[0] < s[i])
                s[i] = s[i]-1;
        }
        s.erase(s.begin());
        p = factorial_hash(s, p);
        return P(p.first*len, num*p.first*len+p.second);
            
    }
}


/* 順列型の最小完全ハッシュ関数を逆算*/
void factorial_num(ll n, vector<ll> &v)
{
    if(n <= 1)
    {
        v[0] = 1;
        v[1] = 1;
        return;
    }
    else
    {
        factorial_num(n-1, v);
        v[n-1] = (n-1) * v[n-2];
        return ;
    }
        
}

ll Back_calculation(P p, int len, vector<ll> &v)
{
    if(len <= 0)
        return 0;
    else
        return p.first * pow(10, len) + Back_calculation(P(p.second / v[len-1], p.second % v[len-1]), len-1, v);
}

int main()
{
    string s; cin >> s;
    P p(0,0);
    int mm = factorial_hash(s, p).second;
    pri(mm);


    //逆算
    vector<ll> v(s.size());
    factorial_num(s.size(), v);
    P p1(0, mm);
    ll m = Back_calculation(p1, s.size(), v);

    vector<ll> vv(s.size()); rep(i, s.size()) vv[i] = i;
    ostringstream ss;
	ss << setw(s.size()) << setfill('0') << m << "\n";
	string str(ss.str());
    string ans = "";
    
    rep(i, s.size())
    {
        int count = 0;
        rep(j, s.size())
        {
            if(vv[j] == MX) continue;

            if(str[i] - '0' == count)
            {
                ans += to_string(vv[j]);
                vv[j] = MX;
                break;
            }
            count++;
        }
    }

    pri(ans);
    return 0;
}
