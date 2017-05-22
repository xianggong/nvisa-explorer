// C++ headers
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

// Linux headers
#include <elf.h>

int main(int argc, char* argv[]) {
  // Read file to save the content in a buffer
  std::vector<uint8_t> bytes;
  FILE* f = fopen("template.cubin", "rb+");
  assert(f);
  fseek(f, 0, SEEK_END);
  size_t size = ftell(f);
  bytes.resize(size);
  rewind(f);
  fread(bytes.data(), 1, size, f);
  // Scan section names to find which section has instruction text
  uint8_t* elf_base = bytes.data();
  const Elf64_Ehdr* elf_header = reinterpret_cast<const Elf64_Ehdr*>(elf_base);
  const uint8_t* section_header_table_base = reinterpret_cast<const uint8_t*>(
      elf_base) + elf_header->e_shoff;
  const Elf64_Shdr* section_name_header = reinterpret_cast<const Elf64_Shdr*>(
      section_header_table_base + elf_header->e_shstrndx *
      elf_header->e_shentsize);
  const uint8_t* section_name_base = reinterpret_cast<const uint8_t*>(
      elf_base) + section_name_header->sh_offset;
  int kernel_section_id = -1;
  for (uint32_t section_id = 0; section_id < elf_header->e_shnum;
      ++section_id) {
    const Elf64_Shdr* section_header = reinterpret_cast<const Elf64_Shdr*>(
          section_header_table_base + section_id * elf_header->e_shentsize);
    std::string section_name;
    for (int offset = section_header->sh_name; section_name_base[offset] != 0;
        ++offset) {
      section_name += section_name_base[offset];
    }
    if (section_name == ".text._Z10testKernelPfS_") {
      kernel_section_id = section_id;
      break;
    }
  }
  assert(kernel_section_id != -1);
  // Get instruction text
  const Elf64_Shdr* kernel_section_header = reinterpret_cast<const Elf64_Shdr*>(
      section_header_table_base + kernel_section_id * elf_header->e_shentsize);
  uint64_t inst_gold = 0;
  fseek(f, kernel_section_header->sh_offset + 8, SEEK_SET);
  fread(&inst_gold, 1, 8, f);
  fclose(f);
  printf("inst_gold = %016lx\n", inst_gold);
  // Change instruction bits
  assert(argc == 3);
  const int high_bit = std::stoi(argv[1]);
  const int low_bit = std::stoi(argv[2]);
  assert(high_bit >= low_bit);
  assert(high_bit - low_bit < 63);
  uint64_t num = 1ULL << (high_bit - low_bit + 1);
  uint64_t inst = inst_gold;
  for (uint64_t n = 0; n < num; ++n) {
    uint64_t high = inst & (((1ULL << (64 - high_bit)) - 1) << (high_bit + 1));
    uint64_t middle = n << low_bit;
    uint64_t low = inst & ((1ULL << low_bit) - 1);
    inst = high | middle | low;
    FILE* f = fopen("template.cubin", "rb+");
    fseek(f, kernel_section_header->sh_offset + 8, SEEK_SET);
    fwrite(&inst, 1, 8, f);
    fclose(f);
    printf("inst = %016lx\n", inst);
    system("cuobjdump -sass template.cubin | grep 0008");
  }
  // Recover instruction bits
  f = fopen("template.cubin", "rb+");
  fseek(f, kernel_section_header->sh_offset + 8, SEEK_SET);
  fwrite(&inst_gold, 1, 8, f);
  fclose(f);
  return 0;
}
 
