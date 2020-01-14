#pragma once


#include "CMath.h"
#include "CVector.h"
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

class CStopWatch
{
    std::chrono::system_clock::time_point tstart;
    std::chrono::system_clock::time_point tend;

public:
    void start()
    {
        tstart = std::chrono::system_clock::now();
    }
    void end()
    {
        tend = std::chrono::system_clock::now();
        std::cout << (std::chrono::duration_cast<std::chrono::milliseconds>(tend - tstart)).count() << " ms " << std::endl;
    }
};

namespace check
{
    template <typename T>
    bool IsSame(const std::vector<T>& src, const CVector<T>& dst)
    {
        int iSize = dst.size();
        iSize == src.size() ? assert(true) : assert(false && "size diffrent");

        bool bCheck = true;
        for (int i = 0; i < iSize; ++i)
        {
            if (src[i] != dst[i])
            {
                bCheck = false;
                std::cout << "[" << i << "] : diffrent" << "src: " << src[i] << " dst: " << dst[i] << std::endl;
            }
        }
        assert(bCheck);
        return bCheck;
    }
    template <typename T>
    bool IsSame(const CVector<T>& src, const CVector<T>& dst)
    {
        int iSize = dst.size();
        iSize == src.size() ? assert(true) : assert(false && "size diffrent");

        bool bCheck = true;
        for (int i = 0; i < iSize; ++i)
        {
            if (src[i] != dst[i])
            {
                bCheck = false;
                std::cout << "[" << i << "] : diffrent" << "src: " << src[i] << " dst: " << dst[i] << std::endl;
            }
        }
        assert(bCheck);
        return bCheck;
    }

    template <typename T>
    void vecpush(CVector<T>& src ,int n)
    {
        src.clear();
        for (int i = 0; i < n; ++i)
        {
            src.push_back(i);
        }
    }
    template <typename T>
    void vecpush(vector<T>& src, int n)
    {
        src.clear();
        for (int i = 0; i < n; ++i)
        {
            src.push_back(i);
        }
    }

    template <typename T>
    void cprint(const CVector<T>& src)
    {
        int iSize = src.size();
        for (int i = 0; i < iSize; ++i)
        {
            cout << "[" << i << "] : " << src[i] << endl;
        }
        cout << endl;
    }
    template <typename T>
    void csizecapacity(const CVector<T>& src)
    {
        cout << "size : " << src.size() << endl;
        cout << "capacity : " << src.capacity() << endl;
    }

}

namespace cvector
{
    using namespace check;

    void insert_test()
    {
        CVector<int> dst;
        vecpush(dst,100);

        vector<int> src;
        vecpush(src, 100);

        CVector<int>::iterator diter = dst.begin();
        CVector<int>::iterator deiter = dst.end();

        diter = diter + (int)(dst.size() / 2);
        dst.insert(diter, 30, 777);

        vector<int>::iterator siter = src.begin();
        vector<int>::iterator seiter = src.end();

        siter = siter + (int)(src.size() / 2);
        src.insert(siter, 30, 777);

        if (check::IsSame(src, dst))
        {
            cout << "ok" << endl;
        }
    }

    void erase_test()
    {
        CVector<int> dst;
        vecpush(dst, 100);

        vector<int> src;
        vecpush(src, 100);

        CVector<int>::iterator diter = dst.begin();
        CVector<int>::iterator deiter = dst.end();

        vector<int>::iterator siter = src.begin();
        vector<int>::iterator seiter = src.end();

        //1.
        diter = diter + (int)(dst.size() / 2);
        dst.erase(diter,deiter);

        siter = siter + (int)(src.size() / 2);
        src.erase(siter, seiter);

        if (check::IsSame(src, dst))
        {
            cout << "ok" << endl;
        }

        //2.
        vecpush(dst, 129);
        vecpush(src,129);
        diter = dst.begin();
        deiter = dst.end();
        siter = src.begin();
        seiter = src.end();

        diter = diter + (int)(dst.size() / 2);
        dst.erase(diter, diter + 29);

        siter = siter + (int)(src.size() / 2);
        src.erase(siter, siter + 29);

        if (check::IsSame(src, dst))
        {
            cout << "ok" << endl;
        }
    }

    void copy_test()
    {
        CVector<int> src;
        vecpush(src,30001);

        cout << "src" << endl;
        csizecapacity(src);

        CVector<int> dst1(src);
        cout << "dst1" << endl;
        csizecapacity(dst1);

        CVector<int> dst2 = src;
        cout << "dst2" << endl;
        csizecapacity(dst2);

        if (IsSame(src, dst1) && IsSame(src, dst2))
        {
            cout << "ok" << endl;
        }

        CVector<int> a;
        cout << "a" << endl;
        csizecapacity(a);

        dst1 = a;
        cout << "dst1" << endl;
        csizecapacity(dst1);
    }

    void copy_this_test()
    {
        CVector<double> me;
        CVector<double> another(me);

        vecpush(me, 100);
        me = me;

        vector<int> mine;
        vecpush(mine, 100);
        mine = mine;
    }

    void max_size_test()
    {
        int iSize;
        int iCapacity;

        CVector<int> src;
        /*
        while (1)
        {
            // warning : Maxsize = std::numeric_limits<int>::max() / 2 - 1;

            iSize = src.size();
            iCapacity = src.capacity();

            for (int i = iSize; i <= iCapacity; ++i)
            {
                src.push_back(i);
            }
            iSize = src.size();
            iCapacity = src.capacity();

            csizecapacity(src);
        }
        */
    }

    template <typename T>
    CVector<T> temporaryCVector()
    {
        CVector<T> a;
        vecpush(a, 100);
        return a;
    }

    template <typename T>
    vector<T> temporaryVector()
    {
        vector<T> a;
        vecpush(a, 100);
        return a;
    }

    void move_test()
    {
        vector<int> d1(temporaryVector<int>());

        CVector<int> dst1(temporaryCVector<int>());
        csizecapacity(dst1);

        CVector<int> dst2;
        vecpush(dst2, 2);
        dst1 = dst2 = temporaryCVector<int>();
        csizecapacity(dst2);

        if (check::IsSame(dst1, dst2))
        {
            cout << "ok" << endl;
        }

    }

    void swap_test()
    {
        CVector<float> me;
        vecpush(me,20);
        me.swap(me);

        CVector<int> src;
        CVector<int> dst;
        vecpush(src, 20);

        src.swap(dst);

        cprint(dst);
        cprint(src);

        vecpush(src, 10);
        vecpush(dst, 20);

        src.swap(dst);

        csizecapacity(src);
        csizecapacity(dst);
    }
}

namespace matrix
{
    void printMatrix(const Matrix4x4& m)
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                cout << m[i][j] << "\t";
            }
            cout << "\n";
        }
    }

    void IdentityMatrix()
    {
        Matrix4x4 a = Matrix4x4::Identity4x4;
        printMatrix(a);
    }
}