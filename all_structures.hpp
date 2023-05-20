#ifndef ALL_STRUCTURES
#define ALL_STRUCTURES 1
#include <string>
#include <stdexcept>
#include <future>

enum class Hashes {
    MD5,
    SHA256,
    CRC32
};

struct file {
    std::string filename;
    std::string expected_hash;
    std::string got_hash;
};

struct task {
    std::string filename;
    std::string expected_hash;
    Hashes algorithm;
    std::promise<std::string> prom;

    task(file some_file, Hashes got_algorithm, std::promise<std::string> smth) {
        filename = some_file.filename;
        expected_hash = some_file.expected_hash;
        algorithm = got_algorithm;
        prom = smth;
    }
};


const char* algorithmToText(Hashes algorithm) {
    switch (algorithm)
    {
    case Hashes::CRC32: return "CRC32";
    case Hashes::MD5: return "MD5";
    case Hashes::SHA256: return "SHA256";
    default: return "";
    }
};

Hashes parseAlgorithm(std::string something) {
    if (std::string("CRC32") == something || std::string("crc32") == something) {
        return Hashes::CRC32;
    }
    if (std::string("MD5") == something || std::string("md5") == something) {
        return Hashes::MD5;
    }
    if (std::string("SHA256") == something || std::string("sha256") == something) {
        return Hashes::SHA256;
    }
    throw std::invalid_argument("Unknown algorithm");
};

#endif