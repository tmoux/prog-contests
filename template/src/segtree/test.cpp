#include <string>

template<typename T>
concept bool Stringable = requires(T a) {
    {a.stringify()} -> std::string;
};

class Cat {
 public:
    std::string stringify() {
        return "meow";
    }

    void pet() {
    }
};

template<Stringable T>
void f(T a) {
    a.pet();
}

int main() {
    f(Cat());
    return 0;
}
