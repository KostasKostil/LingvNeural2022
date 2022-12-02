#include <bits/stdc++.h>

using namespace std;

int D = 5;
map<string, int> bestcats;

string getfield(string s, string c)
{
    int n = s.size();
    for (int i=0; i+c.size()<n; i++)
        if (s.substr(i, c.size()) == c)
        {
            int in = i + c.size();
            while (s[in] != '"' or s[in-1] == '\\')
                in++;
            string t = s.substr(i+c.size(), in-i-c.size());
            string g;
            for (int j=0; j<t.size(); j++)
            {
                if ((j + 1 < t.size()) and (t[j] == '\\') and (t[j+1] == '"'))
                    j++, g+='\'';
                else
                    g+=t[j];
            }
            return g;
        }
    return "";
}

void analyze()
{
    ifstream fin("all_news.json");

    map<string, int> cats;
    string s;
    string c = "\"category\": \"";
    while (getline(fin, s))
    {
        cats[getfield(s, c)]++;
    }
    vector<pair<string, int> > vcats(cats.begin(), cats.end());
    sort(vcats.begin(), vcats.end(), [&](auto x, auto y){ return x.second > y.second; });
    for (auto pa : vcats)
        cout<<pa.first<<" "<<pa.second<<"\n";
    for (int i=0; i<D; i++)
        bestcats[vcats[i].first] = i;
}

void process()
{
    ifstream fin("all_news.json");
    ofstream fout("news.csv");

    string s;
    string c = "\"category\": \"";
    string t = "\"headline\": \"";
    string d = "\"short_description\": \"";

    vector<string> out;
    while (getline(fin, s))
    {
        string cat = getfield(s, c);
        if (bestcats.count(cat))
        {
            ostringstream os;
            os<<"\""<<bestcats[cat]<<"\",\""<<getfield(s, t)<<"\",\""<<getfield(s, d)<<"\"\n";
            out.push_back(os.str());
        }
    }
    random_shuffle(out.begin(), out.end());
    for (auto s : out)
        fout<<s;
}

int main()
{
    analyze();
    process();

    return 0;
}
