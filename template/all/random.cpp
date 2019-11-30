random_device device;
mt19937 gen(device());
uniform_int_distribution<int> dist(1,36);
cout << dist(gen) << '\n';
