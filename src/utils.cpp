//
// Created by MED45 on 26.07.2020.
//
#include "utils.h"

std::string uint64_to_hex(uint64_t value) {
    char hash[32];
    sprintf(hash, "%llx", value);
    return std::string(hash);
}

uint64_t hash_string(const std::string &filename, uint8_t seed) {
    uint64_t hash;
    uint8_t byte[16];
    MurmurHash3_x64_128(filename.c_str(), (int32_t)filename.size() + 1, seed, &byte);
    memcpy(&hash, byte, 8);
    return hash;
}

uint64_t calculate_first_containing_chunk(uint64_t file_offset, int32_t chunk_size) {
    return file_offset - (file_offset % chunk_size);
}

uint64_t calculate_last_containing_chunk(uint64_t file_offset, int32_t file_size, int32_t chunk_size) {
    return calculate_first_containing_chunk(file_offset + file_size, chunk_size);
}

bool decompress_chunk_data(const std::vector<uint8_t> &data, uint64_t decompressed_size, uint8_t* output) {
    int res = Kraken_Decompress(data.data(), data.size(), output, decompressed_size);
    return res!=-1;
}

