//
// Created by MED45 on 25.07.2020.
//

#include "Tracy.hpp"

#include <MurmurHash3.h>

#include "decima/archive/archive.hpp"

static inline bool is_encrypted(Decima::Version version) {
    return version == Decima::Version::encrypted_version;
}
static inline bool is_valid(Decima::Version version) {
    return version == Decima::Version::default_version || is_encrypted(version);
}

static void decrypt(uint32_t key_1, uint32_t key_2, uint32_t* data) {
    const std::uint32_t key[8] = {
        key_1, Decima::encryption_key_1[1], Decima::encryption_key_1[2], Decima::encryption_key_1[3],
        key_2, Decima::encryption_key_1[1], Decima::encryption_key_1[2], Decima::encryption_key_1[3]
    };

    std::uint32_t iv[8];
    MurmurHash3_x64_128(key, 16, Decima::seed, iv);
    MurmurHash3_x64_128(key + 4, 16, Decima::seed, iv + 4);

    data[0] ^= iv[0];
    data[1] ^= iv[1];
    data[2] ^= iv[2];
    data[3] ^= iv[3];
    data[4] ^= iv[4];
    data[5] ^= iv[5];
    data[6] ^= iv[6];
    data[7] ^= iv[7];
}

Decima::Archive::Archive(const std::string& path)
    : m_stream(path)
    , path(path) { open(); }

bool Decima::Archive::open() {
    ZoneScopedNS("Archive loading", 128);
    TracyMessageL("Loading  Archive");

    memcpy(&header, m_stream.data(), sizeof(ArchiveHeader));
    if (!is_valid(header.version))
        return false;

    memcpy(&content_info, m_stream.data() + sizeof(ArchiveHeader), sizeof(ArchiveContentInfo));

    if (is_encrypted(header.version))
        decrypt(header.key, header.key + 1, (uint32_t*)&content_info);

    std::size_t read_offset = sizeof(ArchiveHeader) + sizeof(ArchiveContentInfo);
    {
        ZoneScopedNS("Entries reading", 128);
        content_table.resize(content_info.content_table_size);
        memcpy(content_table.data(), m_stream.data() + read_offset, sizeof(FileEntry) * content_info.content_table_size);
    }
    read_offset += sizeof(FileEntry) * content_info.content_table_size;
    {
        ZoneScopedNS("Chunks reading", 128);
        chunk_table.resize(content_info.chunk_table_size);
        memcpy(chunk_table.data(), m_stream.data() + read_offset, sizeof(chunk_table.front()) * content_info.chunk_table_size);
    }
    if (is_encrypted(header.version)) {
        {
            ZoneScopedNS("Entry decrypting", 128);
            for (auto& file_entry : content_table) {
                decrypt(file_entry.key_0, file_entry.key_1, (uint32_t*)&file_entry);
            }
        }
        {
            ZoneScopedNS("Chunk info decrypting", 128);
            for (auto& chunk : chunk_table) {
                auto saved_key = chunk.key_0;
                decrypt(chunk.key_0, chunk.key_1, (uint32_t*)&chunk);
                chunk.key_0 = saved_key;
            }
        }
    }
    TracyMessageL("Building hash to file index map");
    {
        ZoneScopedN("Hash to index map") for (std::size_t index = 0; index < content_table.size(); index++) {
            m_hash_to_index.emplace(content_table.at(index).hash, index);
        }
    }
    return true;
}

Decima::OptionalRef<Decima::CoreFile> Decima::Archive::query_file(std::uint64_t hash) {
    ZoneScopedNS("File quering", 128) if (auto index = m_hash_to_index.find(hash); index != m_hash_to_index.end()) {
        auto cache = m_cache.find(index->second);

        if (cache == m_cache.end()) {
            ash::buffer buffer(m_stream.begin(), m_stream.end());
            Decima::CoreFile file(&content_table.at(index->second), buffer, this, is_encrypted(header.version));
            cache = m_cache.emplace(index->second, std::move(file)).first;
        }

        return std::make_optional(std::ref(cache->second));
    }

    return {};
}
