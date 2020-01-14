#pragma once
#include <math.h>
#include <assert.h>


enum class EAXIS : size_t
{
    X = 0,
    Y,
    Z,
    END
};

namespace math
{
    constexpr float pi = 3.141592f;
    constexpr float epsilon = 0.000001f;

    constexpr float RadianToDegree(float fRadian)
    {
        return fRadian * 180.f / pi;
    }

    constexpr float DegreeToRadian(float fDegree)
    {
        return fDegree * pi / 180.f;
    }
}

/*
C1. enum class와 enum의 차이에 대해서 공부하고, 적용해주세요.
1. enum class vs enum
- 같은 scope에서 enum은 같은 열거자 명으로 변수를 만들 때 안된다.
- enum class는 형변환 명시적으로 써야한다.

enum ECOLOR
{
    RED = -1,
    BLUE,
    GREEN
};

unsigned int a = RED; =======> enum class는 캐스팅 안해주면 컴파일 못한다.
cout << a;

C2. Define 말고 constexpr을 고려해주세요.
2.
- #define은 class, namespace 등의 scope를 무시
- type check

    #define mul(x,y) ( x + y )
    constexpr float multi(float x, float y)
    {
        return x * y;
    }

    string c;
    cout << mul(c, 2);
    cout << multi(c, 2);

    type check

C3. Namespace를 이용해서 Scope을 제한하면 어떻게 더 좋아질까요?
3.
- 같은 이름의 변수 함수에서 충돌을 피할 수 있다.

namespace test1
{
    int a = 5;
    float test(float a, float b) { return a; }
}

namespace test2
{
    int a = 6;
    float test(float a, float b) { return b; }
}

- 실수가 줄어든다.

*/
