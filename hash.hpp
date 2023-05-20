#ifndef HASH_FACTORY
#define HASH_FACTORY 12052023

#include <stddef.h>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdint>
#include <cstdio>
#include <array>
#include <sstream>
#include <iomanip>
#include <map>
#include <exception>
#include "all_structures.hpp"

class CRC32 {
    const unsigned int CRC32TABLE[256];

    public:
        CRC32(): CRC32TABLE {
            0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F,
            0xE963A535, 0x9E6495A3, 0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
            0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91, 0x1DB71064, 0x6AB020F2,
            0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
            0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9,
            0xFA0F3D63, 0x8D080DF5, 0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
            0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B, 0x35B5A8FA, 0x42B2986C,
            0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
            0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423,
            0xCFBA9599, 0xB8BDA50F, 0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
            0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D, 0x76DC4190, 0x01DB7106,
            0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
            0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D,
            0x91646C97, 0xE6635C01, 0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
            0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457, 0x65B0D9C6, 0x12B7E950,
            0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
            0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7,
            0xA4D1C46D, 0xD3D6F4FB, 0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
            0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9, 0x5005713C, 0x270241AA,
            0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
            0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81,
            0xB7BD5C3B, 0xC0BA6CAD, 0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
            0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683, 0xE3630B12, 0x94643B84,
            0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
            0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB,
            0x196C3671, 0x6E6B06E7, 0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
            0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5, 0xD6D6A3E8, 0xA1D1937E,
            0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
            0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55,
            0x316E8EEF, 0x4669BE79, 0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
            0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F, 0xC5BA3BBE, 0xB2BD0B28,
            0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
            0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F,
            0x72076785, 0x05005713, 0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
            0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21, 0x86D3D2D4, 0xF1D4E242,
            0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
            0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69,
            0x616BFFD3, 0x166CCF45, 0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
            0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB, 0xAED16A4A, 0xD9D65ADC,
            0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
            0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693,
            0x54DE5729, 0x23D967BF, 0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
            0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D} {}
        
        typedef unsigned long hash_type;
        hash_type operator()(const unsigned char *value, size_t length) {
            hash_type hash = 0xFFFFFFFF;

            for (size_t i = 0; i < length; ++i)
                hash = (hash >> 8) ^ CRC32TABLE[(hash ^ value[i]) & 0xFF];

            return hash ^ 0xFFFFFFFF;
        }

        std::string hash(const unsigned char *value, size_t length) {
            std::stringstream ss;
            ss << std::hex << (*this)(value, length);
            return ss.str();
        }
};

class MD5 {
    public:
        const unsigned int s[64] = {7,  12, 17, 22, 7,  12, 17, 22, 7,  12, 17, 22, 7,
                                12, 17, 22, 5,  9,  14, 20, 5,  9,  14, 20, 5,  9,
                                14, 20, 5,  9,  14, 20, 4,  11, 16, 23, 4,  11, 16,
                                23, 4,  11, 16, 23, 4,  11, 16, 23, 6,  10, 15, 21,
                                6,  10, 15, 21, 6,  10, 15, 21, 6,  10, 15, 21};

        const unsigned int K[64] = {
            0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
            0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
            0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
            0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
            0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
            0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
            0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
            0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
            0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
            0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
            0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

        unsigned int leftRotate(unsigned int x, unsigned int c) {
            return (x << c) | (x >> (32 - c));
        }

        std::string hash(const unsigned char *data, size_t len) {
            unsigned int a0 = 0x67452301;
            unsigned int b0 = 0xefcdab89;
            unsigned int c0 = 0x98badcfe;
            unsigned int d0 = 0x10325476;

            size_t padded_len = ((len + 8) / 64 + 1) * 64;
            unsigned char* padded_data = new unsigned char[padded_len];
            memcpy(padded_data, data, len);
            padded_data[len] = 0x80;

            for (size_t i = len + 1; i < padded_len - 8; ++i) {
                padded_data[i] = 0;
            }

            uint64_t bit_len = len * 8;
            memcpy(padded_data + padded_len - 8, &bit_len, 8);

            unsigned int A, B, C, D, F, g, temp;
            for (size_t i = 0; i < padded_len; i += 64) {
                A = a0;
                B = b0;
                C = c0;
                D = d0;

                for (unsigned int j = 0; j < 64; ++j) {
                    if (j <= 15) {
                        F = (B & C) | ((~B) & D);
                        g = j;
                    } else if (j <= 31) {
                        F = (D & B) | ((~D) & C);
                        g = (5*j + 1) % 16;
                    } else if (j <= 47) {
                        F = B ^ C ^ D;
                        g = (3*j + 5) % 16;
                    } else {
                        F = C ^ (B | (~D));
                        g = (7*j) % 16;
                    }

                    unsigned int m = i + g * 4;
                    F += A + K[j] + (padded_data[m+3]<<24 | padded_data[m+2]<<16 | padded_data[m+1]<<8 | padded_data[m+0]);
                    A = D;
                    D = C;
                    C = B;
                    B += leftRotate(F, s[j]);
                }

                a0 += A;
                b0 += B;
                c0 += C;
                d0 += D;
            }

            delete[] padded_data;

            unsigned char hash[16];
            memcpy(hash, &a0, 4);
            memcpy(hash + 4, &b0, 4);
            memcpy(hash + 8, &c0, 4);
            memcpy(hash + 12, &d0, 4);

            char result[33];
            for (int i = 0; i < 16; ++i) {
                sprintf(result + i*2, "%02x", hash[i]);
            }
            result[32] = '\0';

            return std::string(result);
        }

        std::string operator()(const unsigned char *data, size_t len) {
            return hash(data, len);
        }
};



class SHA256 {

    public:
        SHA256(): m_blocklen(0), m_bitlen(0) {
            m_state[0] = 0x6a09e667;
            m_state[1] = 0xbb67ae85;
            m_state[2] = 0x3c6ef372;
            m_state[3] = 0xa54ff53a;
            m_state[4] = 0x510e527f;
            m_state[5] = 0x9b05688c;
            m_state[6] = 0x1f83d9ab;
            m_state[7] = 0x5be0cd19;
        };
        void update(const unsigned char* data, size_t length) {
            for (size_t i = 0 ; i < length ; i++) {
                m_data[m_blocklen++] = data[i];
                if (m_blocklen == 64) {
                    transform();

                    // End of the block
                    m_bitlen += 512;
                    m_blocklen = 0;
                }
            }
        };
        void update(const std::string &data) {
            update(reinterpret_cast<const unsigned char*>(data.c_str()), data.size());
        };
        unsigned char* digest() {
            unsigned char * hash = new unsigned char[32];
            pad();
            revert(hash);
            return hash;
        };

        static std::string toString(const unsigned char* digest) {
            std::stringstream s;
            s << std::setfill('0') << std::hex;

            for(unsigned char i = 0 ; i < 32 ; i++) {
                s << std::setw(2) << (unsigned int) digest[i];
            }

            return s.str();
        };
        std::string operator()(const unsigned char* data, size_t length) {
            update(data, length);
            return toString(digest()); // toString?
        }
        std::string hash(const unsigned char* data, size_t length) {
            return (*this)(data, length);
        }

    private:
        unsigned char m_data[64];
        unsigned int m_blocklen;
        uint64_t m_bitlen;
        unsigned int m_state[8]; //A, B, C, D, E, F, G, H

        static constexpr std::array<unsigned int, 64> K = {
            0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,
            0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
            0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
            0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
            0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,
            0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
            0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,
            0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
            0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
            0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
            0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,
            0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
            0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,
            0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
            0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
            0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
        };

        static unsigned int rotr(unsigned int x, unsigned int n) {
            return (x >> n) | (x << (32 - n));
        };
        static unsigned int choose(unsigned int e, unsigned int f, unsigned int g) {
            return (e & f) ^ (~e & g);
        };
        static unsigned int majority(unsigned int a, unsigned int b, unsigned int c) {
            return (a & (b | c)) | (b & c);
        };
        static unsigned int sig0(unsigned int x) {
            return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
        };
        static unsigned int sig1(unsigned int x) {
            return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
        };
        void transform() {
            uint32_t maj, xorA, ch, xorE, sum, newA, newE, m[64];
            uint32_t state[8];

            for (unsigned char i = 0, j = 0; i < 16; i++, j += 4) { 
                m[i] = (m_data[j] << 24) | (m_data[j + 1] << 16) | (m_data[j + 2] << 8) | (m_data[j + 3]);
            }

            for (unsigned char k = 16 ; k < 64; k++) { 
                m[k] = sig1(m[k - 2]) + m[k - 7] + sig0(m[k - 15]) + m[k - 16];
            }

            for(unsigned char i = 0 ; i < 8 ; i++) {
                state[i] = m_state[i];
            }

            for (unsigned char i = 0; i < 64; i++) {
                maj   = majority(state[0], state[1], state[2]);
                xorA  = rotr(state[0], 2) ^ rotr(state[0], 13) ^ rotr(state[0], 22);

                ch = choose(state[4], state[5], state[6]);

                xorE  = rotr(state[4], 6) ^ rotr(state[4], 11) ^ rotr(state[4], 25);

                sum  = m[i] + K[i] + state[7] + ch + xorE;
                newA = xorA + maj + sum;
                newE = state[3] + sum;

                state[7] = state[6];
                state[6] = state[5];
                state[5] = state[4];
                state[4] = newE;
                state[3] = state[2];
                state[2] = state[1];
                state[1] = state[0];
                state[0] = newA;
            }

            for(unsigned char i = 0 ; i < 8 ; i++) {
                m_state[i] += state[i];
            }
        };
        void pad() {
            uint64_t i = m_blocklen;
            unsigned char end = m_blocklen < 56 ? 56 : 64;

            m_data[i++] = 0x80; 
            while (i < end) {
                m_data[i++] = 0x00; 
            }

            if(m_blocklen >= 56) {
                transform();
                memset(m_data, 0, 56);
            }

            m_bitlen += m_blocklen * 8;
            m_data[63] = m_bitlen;
            m_data[62] = m_bitlen >> 8;
            m_data[61] = m_bitlen >> 16;
            m_data[60] = m_bitlen >> 24;
            m_data[59] = m_bitlen >> 32;
            m_data[58] = m_bitlen >> 40;
            m_data[57] = m_bitlen >> 48;
            m_data[56] = m_bitlen >> 56;
            transform();
        };
        void revert(unsigned char* hash) {
            for (unsigned char i = 0 ; i < 4 ; i++) {
                for(unsigned char j = 0 ; j < 8 ; j++) {
                    hash[i + (j * 4)] = (m_state[j] >> (24 - i * 8)) & 0x000000ff;
                }
            }
        };

};


// Hash Factory
class HashFactory {
    public:
        static std::string hash(const unsigned char* data, size_t length, Hashes variation) {
            switch (variation) {
                case Hashes::CRC32: {
                    CRC32 hash_function;
                    return hash_function.hash(data, length);
                }
                case Hashes::MD5: {
                    MD5 hash_function;
                    return hash_function.hash(data, length);
                }
                case Hashes::SHA256: {
                    SHA256 hash_function;
                    return hash_function.hash(data, length);
                }
                default: {
                    throw std::invalid_argument("Invalid hash-function");
                }
            }
        }
};



#endif