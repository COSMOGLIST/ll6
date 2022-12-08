#include "number.h"
#include "string"

uint2022_t from_uint(uint32_t i) {
    uint2022_t N;
    for (int q = 0; q < 68; q++) {
        N.line[q] = 0;
    }
    int j = 0;
    while (i > 0) {
        N.line[j] = i % 1000000000;
        i =  i / 1000000000;
        j++;
    }
    return uint2022_t(N);
}

uint2022_t from_string(const char* buff) {
    std::string i = buff;
    uint2022_t N;
    for (int q = 0; q < 68; q++) {
        N.line[q] = 0;
    }
    int j = 0;
    int length = i.length();
    while (length > 9) {
        for (int q = length - 9; q < length; q++) {
            int m = i[q] - 48;
            N.line[j] = N.line[j]*10 + m;
        }
        j++;
        length = length - 9;
    }
    for (int q = 0; q < length; q++) {
        int m = i[q] - 48;
        N.line[j] = N.line[j]*10 + m;

    }
    return uint2022_t(N);
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint32_t remember = 0;
    uint32_t helper = 0;
    uint2022_t result;
    for (int i = 0; i < 68; i++) {
        result.line[i] = lhs.line[i] % 100000000 + rhs.line[i] % 100000000 + remember;
        helper = result.line[i] / 100000000 + lhs.line[i] / 100000000 + rhs.line[i] / 100000000;
        remember = helper / 10;
        result.line[i] = result.line[i] + ( helper % 10 - result.line[i] / 100000000)*100000000;
    }
    return uint2022_t(result);
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint32_t remember = 0;
    uint32_t helper = 0;
    uint2022_t result;
    for (int i = 0; i < 68; i++) {
        if (lhs.line[i] >= rhs.line[i] + remember) {
            result.line[i] = lhs.line[i] - rhs.line[i] - remember;
            remember = 0;
        } else {
            helper = rhs.line[i] + remember - lhs.line[i];
            result.line[i] = 999999999 - helper + 1;
            remember = 1;
        }
    }
    return uint2022_t(result);
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result = from_uint(0);
    uint2022_t adder = from_uint(0);
    int left1, left2, left3, right1, right2, right3, res1, res2, res3, res4, res5, rem, nova, help;
    for (int i = 0; i < 68; i++) {
        for (int j = 0; j < 68; j++) {
            left1 = lhs.line[i] % 10000;
            left2 = (lhs.line[i] % 100000000 - left1)/10000;
            left3 = lhs.line[i] / 100000000;
            right1 = rhs.line[j] % 10000;
            right2 = (rhs.line[j] % 100000000 - right1)/10000;
            right3 = rhs.line[j] / 100000000;
            res1 = left1*right1;
            res2 = left1*right2 + left2*right1;
            res3 = left1*right3 + left2*right2 + left3*right1;
            res4 = left2*right3 + left3*right2;
            res5 = left3*right3;
            nova = res1 + (res2 % 10000) * 10000;
            help = nova / 100000000 + (res2 / 10000) % 10 + res3 % 10;
            nova = nova - (nova/100000000)*100000000 + (help % 10) * 100000000;
            rem = help / 10 + res2 / 100000 + res3 / 10 + res4*1000 + res5 * 10000000;
            adder = from_uint(0);
            adder.line[i+j] = nova;
            adder.line[i+j+1] = rem;
            if (adder != from_uint(0)) {
                result = result + adder;
            }
        }
    }
    return uint2022_t(result);
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    bool result = 1;
    for (int i = 0; i < 68; i++) {
        if (lhs.line[i] != rhs.line[i]) {
            result = 0;
            break;
        }
    }
    return result;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    bool result = 0;
    for (int i = 0; i < 68; i++) {
        if (lhs.line[i] != rhs.line[i]) {
            result = 1;
            break;
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    int remember = 0;
    for (int i = 67; i >= 0; i--) {
        if (value.line[i] != 0) {
            remember = i;
            break;
        }
    }
    int length = 0;
    int n;
    for (int i = remember; i >= 0; i--) {
        if (value.line[i] < 100000000 && i!= remember) {
            n = value.line[i];
            if (n == 0) {
                stream << "000000000";
            } else {
                while (n > 0) {
                    n = n / 10;
                    length++;
                }
                for (int j = 0; j < 9 - length; j++) {
                    stream << 0;
                }
                stream << value.line[i];
            }
        } else {
            stream << value.line[i];
        }
    }
    return stream;
}

