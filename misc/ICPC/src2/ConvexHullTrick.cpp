//This represents those relying on j only;i.e intercept
inline ll y_axis(int j){
    return dp[j] + a * s[j] * s[j] - b * s[j];
}
//This represents those relying on both i and j; i.e slope
inline ll x_axis(int j){
    return s[j];
}
inline ld getSlope(int j,int k){
    ld y = y_axis(k) - y_axis(j);
    ld x = x_axis(k) - x_axis(j);
    return y / x;
}
//s stores prefix sum
int head = 1;int tail = 1;
q[head] = 0;
for (int i = 1;i <= n;i++){
  dp[i] = a*s[i]*s[i] + b*s[i] + c;
  while (head < tail && getSlope(q[head],q[head+1]) >= 2*a*s[i]) head++;
  if (head <= tail){
    int j = q[head];
    dp[i] = max(dp[i], dp[j] + a *(s[i] - s[j]) * (s[i] - s[j]) + b*(s[i] - s[j]) + c);
  }
  while (head < tail && getSlope(q[tail],i) >= getSlope(q[tail-1],q[tail])) tail--;
  q[++tail] = i;
}
