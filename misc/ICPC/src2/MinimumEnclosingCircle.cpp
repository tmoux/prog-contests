point a[maxn];

void getCenter2(point a,point b,point & c)
{
    c.x = (a.x+b.x)/2;
    c.y = (a.y+b.y)/2;
}

void getCenter3(point a,point b,point c,point &d)
{
    double a1 = b.x-a.x, b1 = b.y-a.y, c1 = (a1*a1+b1*b1)/2;
    double a2 = c.x-a.x, b2 = c.y-a.y, c2 = (a2*a2+b2*b2)/2;
    double de = (a1 * b2 - b1 * a2);
    d.x = a.x + (c1 * b2 - c2 * b1)/de;
    d.y = a.y + (a1 * c2 - a2 * c1)/de;
}


    //randomP_shuffle before using
    radius = 0;
    center = a[0];
    for (int i = 1;i < n;++i)
    {
        if (!isIn(a[i], center, radius))
        {
            radius = 0;
            center = a[i];
            for (int j = 0;j < i;++j)
                if (!isIn(a[j], center, radius))
                {
                    getCenter2(a[i], a[j], center);
                    radius = dis(a[i],center);
                    for (int k = 0;k < j;++k) if (!isIn(a[k], center, radius))
                    {
                        getCenter3(a[i], a[j], a[k], center);
                        radius = dis(a[k],center);
                    }
                }
        }
    }
    //printf("%.2lf\n%.2lf %.2lf\n",radius,center.x,center.y);
    printf("%.3lf\n",radius);
    return 0;
}
