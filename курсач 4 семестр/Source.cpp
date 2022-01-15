#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <bitset>
#include <algorithm>

#define bit 64
typedef long long ll;
using namespace std;

ll nod(ll u, ll n) //NOD(перебор)
{

	if (n < u)
	{
		swap(n, u);
	}
	while (u)
	{
		n %= u;
		swap(n, u);
	}
	return n;
}
ll otricModul(ll p, ll n)// Нахождение модуля при отрицательном числе
{
	if (p < 0) {
		for (int i = 0; i < 10000; i++)
		{
			p = p + n;
			if (p > 0) break;
		}
	}
	return p;
}
void find_s_t(ll n, ll* s, ll* t) {
	//розкладання числа n-1
	while (*t % 2 == 0)
	{
		*t /= 2;
		(*s)++;
	}
}
ll st(ll a, ll b, ll m) {	//швидке піднесення до степеня
	ll r = 1;
	while (b) {
		if (b & 1) {
			r *= a;
			r %= m;
		}
		a *= a;
		a %= m;
		b >>= 1;
	}
	return r;
}

ll miller(ll n)// Алгоритм Міллера-Рабіна
{
	int k = 10;
	ll xp = 0;
	int p = 1;
	ll xx;
	ll s = 0;
	ll t = n - 1;
	find_s_t(n, &s, &t);

	for (int i = 1; i <= k; i++) {
		srand(time(NULL));
		int a = rand() % (n - 3) + 2;
		ll xx = st(a, t, n);
		if (xx == 1 || xx == n - 1) continue;
		for (int j = 0; j < s - 1; j++) {
			ll x = st(xx, 2, n);
			if (x == 1) return false;
			xp = x;
			if (x == n - 1) break;

		}
		if (xp != n - 1)
			p = 0;
	}

	if (p == 0) return 0;
	else return n;

}
vector<ll> factorize(ll x)
{
	vector<ll> factors;

	for (int i = 2; i <= sqrt(x); i++) {
		while (x % i == 0) {
			factors.push_back(i);
			x /= i;
		}
	}

	if (x != 1) {
		factors.push_back(x);
	}

	return factors;
}
bool find2p(ll x1, ll y1, ll a, ll* x, ll* y, ll n) // удвоение точки
{ 
	ll alfa = (3*pow(x1,2)+a)/(2*y1);
	if (alfa < 0) alfa = otricModul(alfa, n);
	else alfa = alfa % n;

	
	ll del = nod(alfa, n);
	if (del != 1 && del != n)
	{
		vector <ll> v(32);
		vector <ll> v1(32);
		ll q = n / del;
		
		if (del<=3 && miller(q) == q || miller(del)==del && q<=3 || miller(del) && miller(q))
		{
			cout << " ( " << del << ", " << n / del << " )";
			return true;
		}
		else
		{
			v = factorize(del);
			v1 = factorize(q);
			cout << "(";
			for (int i = 0; i < v.size(); i++)
			{
				cout << v[i] << "*";
			}
			for (int i = 0; i < v1.size(); i++)
			{
				if (i == v1.size() - 1) cout << v1[i];
				else cout << v1[i] << "*";
			}
			cout << ")" << endl;
			return true;
		}
		return true;
	}

	*x = -2*x1+alfa;
	if (*x < 0)*x = otricModul(*x, n);
	else *x = *x% n;

	*y = -y1+alfa*(x1-*x);
	if (*y < 0)*y = otricModul(*y, n);
	else *y = *y % n;
	
}
bool findPplusP(ll x1, ll y1, ll x2, ll y2, ll* x, ll* y, ll n, ll a) // сумма точек
{
	ll alfa = ((y2 - y1) / (x2 - x1));
	if (alfa < 0) alfa = otricModul(alfa, n);
	else alfa = alfa % n;

	ll del = nod(alfa, n);
	if (del != 1 && del != n)
	{
		vector <ll> v(32);
		vector <ll> v1(32);
		ll q = n / del;

		if (del <= 3 && miller(q) == q || miller(del)==del && q <= 3 || miller(del) && miller(q))
		{
			cout << " ( " << del << ", " << n / del << " )";
			return true;
		}
		else
		{
			v = factorize(del);
			v1 = factorize(q);
			cout << "(";
			for (int i = 0; i < v.size(); i++)
			{
				cout << v[i] << "*";
			}
			for (int i = 0; i < v1.size(); i++)
			{
				if (i == v1.size() - 1) cout << v1[i];
				else cout << v1[i] << "*";
			}
			cout << ")" << endl;
			return true;
		}
		return true;
	}

	*x = -x1 - x2 + pow(alfa, 2);
	if (*x < 0)*x = otricModul(*x, n);
	else *x = *x % n;
	
	*y = -y1 + alfa * (x1-*x);
	if (*y < 0)*y = otricModul(*y, n);
	else *y = *y % n;
	
}
int stepenDva(int ch)//Перевод из 10-тичной системы в 2-ю
{
	int t = ch;
	int k, i = 2;
	while (i <= t)
	{
		if (t % i == 0)
		{
			k = 1;
			t = t / i;
			while (t % i == 0) {
				t /= i;
				k++;
			}
			if (k > 1) return k;
			if (t > 1)
				cout << "*";
		}
		
		i = i + 1;
	}
	return 1;
}
bool proofStepen( ll k, ll x1, ll y1, ll a, ll n, ll *Px, ll *Py) // Вычисление кратного, тоесть максимальную степень сравниваем
{
	ll tochka = k;
	vector <ll> chisla(bit);
	for (int i = 0; i < bit; i++)
	{
		chisla[i] = pow(2, i);
	}
	
	vector <ll> v(bit);
	for (int j = 0; k > 0; j++)
	{
		v[j] += (k % 2) * pow(10.0, j);
		k /= 2;
	}
	reverse(v.begin(), v.end());
	int count = 0;
	for (int i = 0; i < bit; i++)
	{
		if (v[i] == 0) count++;
		else break;
	}
	vector <int> v1(bit -count);
	vector <int> perexod(bit - count);
	int c = bit - count;
	for (int i = 0; i < bit -c; i++)
	{
		
		if (count < bit)
		{
			v1[i] = v[count];
		}
		count++;
		if (count == bit) break;
	}
	for (int i = 0; i < v1.size(); i++)
	{
		if (v1[i] > 1) v1[i] = 1;
	}
	v.clear();
	v.shrink_to_fit();
	
	int j = 0;
	for (int i = 0; i < perexod.size(); i++)
	{
		for (; j < v1.size(); j++)
		{
			if (v1[j] == 1)
			{
				perexod[i] = chisla[j];
				j++;
				break;
				
			}
			
		}
		
	}
	v1.clear();
	chisla.clear();
	v1.shrink_to_fit();
	chisla.shrink_to_fit();

	ll g = 0;
	ll x = x1;
	ll y = y1;

	int kk = perexod[(perexod.size() - 2)/2]/2;
	vector < vector <ll> > points(2, vector <ll>(kk + 1));

	points[0][0] = x1;
	points[1][0] = y1;
	
	
	for (int pi = 2; pi < kk + 1;pi++)
	{
		for (int pj = 0; pj < 1; pj++)
		{
			if (y1 != 0)
			{
				if (find2p(x1, y1, a, &x, &y, n)) return 1;

				points[pj][pi] = x;
				points[pj + 1][pi] = y;
				x1 = x;
				y1 = y;
				pi++;
			}
			else 
			{
				findPplusP(x1, y1, x, y, &x, &y, n, a);
				x1 = x;
				y1 = y;
				findPplusP(x1, y1, x, y, &x, &y, n, a);
				x1 = x;
				y1 = y;
				pi++;
			}
		
		}

	}

	if (perexod[0] / 2 == 0 && perexod[1]==2)
	{
		findPplusP(points[0][0], points[1][0], points[0][2], points[1][2], &x, &y, n, a);
		for (int i = 2; i < perexod.size()-1; i++)
		{

			findPplusP(x, y, points[0][perexod[i]], points[1][perexod[i]], &x, &y, n, a);

		}
	}
	else
	{
		for (int i = 0; i < perexod.size() - 1; i++)
		{
			findPplusP(x, y, points[0][perexod[i]], points[1][perexod[i]], &x, &y, n, a);
		}
	}
	
	
	
	ll del = 0;
	del = nod((x, y), n);
		if (del != 1 && del != n)
		{
			vector <ll> v(32);
			vector <ll> v1(32);
			ll q = n / del;

			if (del <= 3 && miller(q) == q || miller(del)==del && q <= 3 || miller(del) && miller(q))
			{
				cout << " ( " << del << ", " << n / del << " )";
				return true;
			}
			else
			{
				v = factorize(del);
				v1 = factorize(q);
				cout << "(";
				for (int i = 0; i < v.size(); i++)
				{
					cout << v[i] << "*";
				}
				for (int i = 0; i < v1.size(); i++)
				{
					if (i + 1 == v1.size()) cout << v1[i];
					cout << v1[i] << "*";
				}
				cout << ")" << endl;


				return true;
			}
			return true;
		}
	

	*Px = points[0][perexod[perexod.size() - 2]];
	*Py = points[1][perexod[perexod.size() - 2]];
	return false;


}
int findStepen(int p, ll b1)//Находим макс степень
{
	ll k ;
	for (int i = 1; i < 1000; i++)
	{
		k = 0;
		k = pow(p, i);
		if (k<b1 && pow(p, i + 1)>b1) break;
	}

	return k;
}




ll findB(ll a, ll x, ll y, ll n) //Находим b
{
	ll b = pow(y, 2) - pow(x, 3) - a * x;
	b = otricModul(b,n) % n;
	return b;
}



int main()
{

	/////////////////////////////////////////////////////////////////////////////////////////////
									//1 стадия алгоритма//
	/////////////////////////////////////////////////////////////////////////////////////////////

	setlocale(LC_ALL, "Russian");
	
		ll n;
		cout << "Введите число, которое нужно разложить: ";
		cin >> n;
		cout << endl << endl;
	first:
		srand(time(NULL));
		ll a = 1 + rand() % (n - 16);

		ll x = 1 + rand() % (n - 16), y = 1 + rand() % (n - 16);

	start:
		ll B1 = 50 + rand() % (n - 500);
		ll b = findB(a, x, y, n);
		ll u = 4 * pow(a, 3) + 27 * pow(b, 2);
		ll g = nod(u, n);
		if (n == g) goto start;
		if (g < n && g>1)
		{

			vector <ll> v(32);
			vector <ll> v1(32);
			ll q = n / g;

			if (g <= 3 && miller(q) == q || miller(g) == g && q <= 3 || miller(g) && miller(q))
			{
				cout << " ( " << g << ", " << n / g << " )";
				return true;
			}
			else
			{
				v = factorize(g);
				v1 = factorize(q);
				cout << "(";
				for (int i = 0; i < v.size(); i++)
				{
					cout << v[i] << "*";
				}
				for (int i = 0; i < v1.size(); i++)
				{
					if (i == v1.size()-1) cout << v1[i];
					else cout << v1[i] << "*";
				}
				cout << ")" << endl;
				
			}
			
			return 1;
		}

		cout << endl << endl << "Имеем элептическую кривую: E: y^2=x^3+ax+b, где y="<<y<<", x="<<x<<", a="<<a<<", b="<<b << ";  и базовую точку генератора P0("<<x<<","<<y<<")" << endl << endl;

		vector<ll> primeMasZero(B1);
		int k = 0;
		for (int j = 5; j < B1; j++)
		{
			if (miller(j) != 0)
			{

				primeMasZero[k] = miller(j);
				k++;
			}

		}

		int count = 0;
		for (ll i = 0; i < B1; i++)
		{
			if (primeMasZero[i] != 0) count++;
			else break;
		}

		vector<ll> primeMas(k);

		for (ll i = 0; i < count; i++)
		{
			primeMas[i] = primeMasZero[i];
		}


		primeMasZero.clear();
		primeMasZero.shrink_to_fit();

		int r = 0;

		vector < vector <ll> > stepeni(2, vector <ll>(primeMas.size()));
		for (ll i = 0; i < primeMas.size(); i++)
		{
			r = findStepen(primeMas[i], B1);
			stepeni[0][i] = primeMas[i];
			stepeni[1][i] = r;
		}

		ll Px = 0, Py = 0;

		for (ll i = 0; i < primeMas.size(); i++)
		{
			if (proofStepen(stepeni[1][i], x, y, a, n, &Px, &Py)) return 1;
		}

		primeMas.clear();
		primeMas.shrink_to_fit();

		primeMasZero.clear();
		primeMasZero.shrink_to_fit();

		stepeni.clear();
		stepeni.shrink_to_fit();

		/////////////////////////////////////////////////////////////////////////////////////////////
										//2 стадия алгоритма//
		/////////////////////////////////////////////////////////////////////////////////////////////

		ll B2 = B1 + rand() % (B1 * 20 - B1);

		vector<ll> primeMasZero2(B2);
		int k2 = 0;
		for (int j = 5; j < B1; j++)
		{
			if (miller(j) != 0)
			{

				primeMasZero2[k2] = miller(j);
				k++;
			}

		}

		int count2 = 0;
		for (ll i = 0; i < B2; i++)
		{
			if (primeMasZero2[i] != 0) count2++;
			else break;
		}

		vector<ll> primeMas2(k);

		for (ll i = 0; i < count2; i++)
		{
			primeMas[i] = primeMasZero2[i];
		}


		primeMasZero2.clear();
		primeMasZero2.shrink_to_fit();

		x = Px;
		y = Py;
		for (ll i = 0; i < primeMas.size(); i++)
		{
			if (proofStepen(primeMas[i], x, y, a, n, &Px, &Py)) return 1;
		}


		primeMas.clear();
		primeMas.shrink_to_fit();
		goto first;
	
	return 0;
}