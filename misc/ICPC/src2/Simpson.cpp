/*
This is a template for solving simpson integration
We are going to integrate \frac{cx+d}{ax+b} over L and R
*/
ld simpson(ld lower, ld upper){
    ld mid = (lower + upper) / 2;
    return (f(lower) + 4 * f(mid) + f(upper)) * (upper-lower) / 6;
}

ld simpson_integration(ld lower, ld upper, ld target){
    ld mid = (lower + upper) / 2;
    ld left_sum = simpson(lower, mid);
    ld right_sum = simpson(mid, upper);
    if (fabs(left_sum + right_sum - target) < eps){
        return left_sum + right_sum;
    }
    return simpson_integration(lower, mid, left_sum) + simpson_integration(mid, upper, right_sum);
}

//Call: simpson_integration(lower, upper, simpson(lower, upper)) << endl;
