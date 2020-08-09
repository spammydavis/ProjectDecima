//
// Created by MED45 on 25.07.2020.
//

#include <iostream>
#include <filesystem>

#include "decima/archive/archive.h"
#include "utils.h"

#include <MurmurHash3.h>
#include <md5.h>

Decima::Archive::Archive(const std::string& workdir, const std::string& filename)
    : filepath(workdir + "\\" + filename) { }

Decima::Archive::Archive(const std::string& workdir, uint64_t filehash)
    : Archive(workdir, uint64_to_hex(filehash) + ".bin") { }

bool Decima::Archive::open() {
    std::error_code error;

    log("Archive", "Loading " + std::filesystem::path(filepath).stem().string() + " archive");
    filebuffer.map(filepath, error);

    if (error)
        return false;

    memcpy(&header, filebuffer.data(), sizeof(ArchiveHeader));

    if (!is_valid())
        return false;

    if (is_encrypted())
        decrypt(header.key, header.key + 1, (uint32_t*)&header + 2);

    std::size_t read_offset = sizeof(header);

    content_table.resize(header.content_table_size);
    log("Archive", "Reading " + std::to_string(header.content_table_size) + " file entries");
    memcpy(content_table.data(), filebuffer.data() + read_offset,
        sizeof(FileEntry) * header.content_table_size);

    read_offset += sizeof(FileEntry) * header.content_table_size;

    chunk_table.resize(header.chunk_table_size);
    log("Archive", "Reading " + std::to_string(header.chunk_table_size) + " chunks");
    memcpy(chunk_table.data(), filebuffer.data() + read_offset, sizeof(chunk_table.front()) * header.chunk_table_size);

    if (is_encrypted()) {
        for (auto& file_entry : content_table) {
            decrypt(file_entry.key, file_entry.key2, (uint32_t*)&file_entry);
        }

        for (auto& chunk : chunk_table) {
            auto saved_key = chunk.key_1;
            decrypt(chunk.key_1, chunk.key_2, (uint32_t*)&chunk);
            chunk.key_1 = saved_key;
        }
    }

    return true;
}

bool Decima::Archive::is_valid() const {
    return (header.version == Decima::Version::default_version || header.version == Decima::Version::encrypted_version);
}

bool Decima::Archive::is_encrypted() const {
    return header.version == Decima::Version::encrypted_version;
}

void Decima::Archive::decrypt(uint32_t key_1, uint32_t key_2, uint32_t* data) {
    const uint32_t inputKey[2][4] = {
        { key_1, encryption_key_1[1], encryption_key_1[2], encryption_key_1[3] },
        { key_2, encryption_key_1[1], encryption_key_1[2], encryption_key_1[3] }
    };

    uint32_t iv[4];

    for (int i = 0; i < 2; i++) {
        MurmurHash3_x64_128(inputKey[i], 0x10, seed, iv);
        for (int j = 0; j < 4; j++) {
            data[(i * 4) + j] ^= iv[j];
        }
    }
}

std::pair<std::vector<Decima::ChunkEntry>::iterator, std::vector<Decima::ChunkEntry>::iterator>
Decima::Archive::get_mio_boundaries(int32_t file_id) {
    if (file_id == -1)
        return { chunk_table.end(), chunk_table.end() };

    const auto& file_entry = content_table.at(file_id);

    const auto file_offset = file_entry.offset;
    const auto file_size = file_entry.size;

    const auto first_chunk = calculate_first_containing_chunk(file_offset, header.max_chunk_size);
    const auto last_chunk = calculate_last_containing_chunk(file_offset, file_size, header.max_chunk_size);

    const auto first_chunk_row = chunk_id_by_offset(first_chunk);
    const auto last_chunk_row = chunk_id_by_offset(last_chunk);

    return { chunk_table.begin() + first_chunk_row, chunk_table.begin() + last_chunk_row + 1 };
}

[[maybe_unused]] uint64_t Decima::Archive::get_file_index(const std::string& file_name) const {
    uint64_t hash = hash_string(sanitize_name(file_name), seed);
    return get_file_index(hash);
}

uint64_t Decima::Archive::get_file_index(uint64_t file_hash) const {
    for (std::size_t i = 0; i < content_table.size(); i++) {
        if (content_table[i].hash == file_hash)
            return i;
    }

    return -1;
}

uint64_t Decima::Archive::chunk_id_by_offset(uint64_t offset) {
    for (std::size_t i = 0; i < chunk_table.size(); i++) {
        if (chunk_table[i].uncompressed_offset == offset)
            return i;
    }

    return -1;
}

Decima::CompressedFile Decima::Archive::query_file(uint64_t file_hash) {
    //    log("Archive", "Queried " + uint64_to_hex(file_hash) + " file");
    auto file_id = get_file_index(file_hash);
    if (file_id == -1) {
        return Decima::CompressedFile(nullptr, nullptr, nullptr, true);
    }
    auto& file_entry = content_table.at(file_id);
    Decima::CompressedFile file(&file_entry, &filebuffer, this, is_encrypted());

    file.chunk_range = get_mio_boundaries(file_id);

    return file;
}

[[maybe_unused]] Decima::CompressedFile Decima::Archive::query_file(const std::string& file_name) {
    log("Archive", "Queried " + file_name + " file");
    return query_file(hash_string(sanitize_name(file_name), seed));
}
