/*
This algorithm concerns efficient evaluation of sum of number theoric functions like phi or mu.
We know that using Eulerian sieve, we can only archieve O(n) time complexity.
What we are doing is to archieve O(n^{2/3}) time complexity.
The example program shows how to evaluate sum of phi and sum of mu efficientyl.
For smaller n (n less than (N^{2/3}), we use calculate them as usual.
For larger n, see getphi and getmu
*/

//See Sieve for more technical details.
//When i is prime, phi[i] = i-1;mu[i] = -1; Otherwise, inside the inner loop, let p = primes[j].
//Then it follows phi[p*i] = phi[i] * (p-1); mu[p*i] = -mu[i];
//finally, when i % p == 0, phi[p*i] = phi[i]*p and mu[p*i] = 0;

ll getphi(ll n)
{
  if (n <= m) return phi[n];
  if (phi_cheat.find(n) != phi_cheat.end()) return phi_cheat[n];
  ll ans = (ll)n*(n + 1) / 2; //this is \sum_{i = 1}^n \sum_{d | n} \phi(d)
  //when getting mu, ans = 1
  ll last;
  for (ll i = 2;i <= n;i = last + 1)
  {
    last = n / (n / i);
    ans -= (last-i+1)*getphi(n / i);
  }
  phi_cheat[n] = ans;
  return ans;
}
