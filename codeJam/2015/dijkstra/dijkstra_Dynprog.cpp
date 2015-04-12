#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

struct Quat {
  bool neg;
  char ch;
  Quat() : neg(false), ch('1') {}
  Quat(bool n, char c) : neg(n), ch(c) {}
};

bool operator==(const Quat& lhs, const Quat& rhs)
{
    return (lhs.neg == rhs.neg && lhs.ch == rhs.ch);
}

Quat qprod[4][4] = {{Quat(false, '1'), Quat(false, 'i'), Quat(false, 'j'), Quat(false, 'k')},
                    {Quat(false, 'i'), Quat(true, '1'),  Quat(false, 'k'), Quat(true, 'j')},
                    {Quat(false, 'j'), Quat(true, 'k'),  Quat(true, '1'),  Quat(false, 'i')},
                    {Quat(false, 'k'), Quat(false, 'j'), Quat(true, 'i'),  Quat(true, '1')}};

std::vector<std::string> readInput ()
{
    std::vector<std::string> retVal;
    unsigned int numTests = 0;
    std::cin >> numTests; 

    for (unsigned int i=0; i<numTests; i++) {
        unsigned int x=0, l=0;
        std::string str;
        std::cin >> x >> l ;
        std::cin >> str ;
        std::string pushMe;
        for (unsigned int j=0; j<l; j++) {
            pushMe.append(str);
        }
        retVal.push_back(pushMe);
    }
    return retVal;
}

unsigned int getIndex(const Quat& q)
{
    switch (q.ch) {
        case '1' : return 0; 
        case 'i' : return 1;
        case 'j' : return 2;
        case 'k' : return 3;
        default : assert(0);
    }
    assert(0);
}

Quat qMult (const Quat& q1, const Quat& q2)
{
    Quat tabMul = qprod[getIndex(q1)][getIndex(q2)];
    if (q1.neg == true) {
        tabMul.neg = ! (tabMul.neg);
    }
    if (q2.neg == true) {
        tabMul.neg = ! (tabMul.neg);
    }
    return tabMul;
}

void computeDynProgArray(Quat **t, const std::vector<Quat>& quats) 
{
    for (unsigned int i=0; i<quats.size(); i++) {
        t[i][i] = quats[i];
    }

    for (unsigned int sz=2; sz <= quats.size(); sz++) {
        for (unsigned int i=0; i <= quats.size() - sz; i++) {
            unsigned int j = i + sz - 1;
            assert(i >= 0 && j >= 1 && i < quats.size() && j < quats.size());
            t[i][j] = qMult(t[i][j-1], quats[j]);
        }
    }

}

bool checkTest (Quat** arr, unsigned int limit) 
{
    if (limit < 3) {
        return false;
    }

    const unsigned int s1_start = 0;
    const unsigned int s3_end   = limit - 1;

    // we know that s1_start <= s1_end
    //              s1_end   <  s2_start
    //              s2_start <= s2_end
    //              s2_end   <  s3_start
    //              s3_start <= s3_end
    const Quat qi(false, 'i');
    const Quat qj(false, 'j');
    const Quat qk(false, 'k');
    for (unsigned int s1_end = 0; s1_end <= limit - 3; s1_end++) {
        unsigned int s2_start = s1_end + 1;
        for (unsigned int s3_start = s2_start + 1; s3_start <= limit - 1; s3_start++) {
            unsigned int s2_end = s3_start - 1;
            assert(s1_start >= 0 && s1_start <= limit - 3);
            assert(s1_end >= s1_start && s1_end <= limit - 3);
            assert(s2_start > s1_end);
            if (!(s2_end < s3_start) ){
                std::cout << limit << std::endl;
                std::cout << "(" << s1_start << ", " << s1_end << ")" << std::endl;
                std::cout << "(" << s2_start << ", " << s2_end << ")" << std::endl;
                std::cout << "(" << s3_start << ", " << s3_end << ")" << std::endl;
                assert(0);
            }
            assert(s3_start > s2_end  && s3_start <= limit - 1);
            assert(s3_end >= s3_start && s3_end <= limit - 1);
            if (arr[s1_start][s1_end] == qi && 
                arr[s2_start][s2_end] == qj && 
                arr[s3_start][s3_end] == qk) {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    std::vector<std::string> tests = readInput();
    unsigned int ctr=1;
    for(auto it = tests.begin(); it != tests.end(); it++, ctr++) {
        const std::string& str = (*it);

        std::vector<Quat> quats(str.size(), Quat());

        std::transform(str.begin(), str.end(), quats.begin(), [] (const char& ch) -> Quat {
            return Quat(false, ch);
        });

        assert(quats.size() == str.size());

        unsigned int str1Start      = 0;
        unsigned int str1EndLimit   = quats.size() - 3;
        unsigned int str3StartLimit = 2; 
        unsigned int str3End        = quats.size() - 1;

        //2-D array for dynamic programming
        Quat **arr = new Quat*[quats.size()];
        for (unsigned int i=0; i<quats.size(); i++) {
            arr[i] = new Quat[quats.size()];
        }

        for (unsigned int i=0; i<quats.size(); i++) {
            for (unsigned int j=i; j<quats.size(); j++) {
                arr[i][j] = quats[i];
            }
        }

        computeDynProgArray(arr, quats);
        bool result = checkTest(arr, quats.size());

        std::cout << "Case #" << ctr << ": " << (result ?  "YES" : "NO") << std::endl;

        for (unsigned int i=0; i<quats.size(); i++) {
            delete [] arr[i];
        }
        delete [] arr;
    }
    
}

