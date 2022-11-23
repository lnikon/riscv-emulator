#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <stdexcept>

#define assertm(exp, msg) assert(((void)msg, exp))

// Constants
static constexpr const std::uint64_t RAM_SIZE{1024 * 1024 * 1};
static constexpr const std::uint64_t RAM_BASE{0x80000000};

// Types aliases
using Byte = std::uint8_t;
using HalfWord = std::uint16_t;
using Word = std::uint32_t;
using DoubleWord = std::uint64_t;
using QuadWord = std::uint64_t; // TODO: Do I need 128 byte registers?
using Size = std::uint64_t;
using Address = std::uint64_t;

/**
 * Possible number of bytes that emulator can load or store.
 */
enum class LoadStoreSize : Size {
  Byte = 1,
  HalfWord = 2,
  Word = 3,
  DoubleWord = 4,

  SizeOfEnum
};

class Memory {
public:
  Memory() = default;
  Memory(const Memory &) = default;
  Memory &operator=(const Memory &) = default;
  Memory(Memory &&) = default;
  Memory &operator=(Memory &&) = default;
  ~Memory() = default;

  // TODO: Can recursievly generate code for different sizes?
  DoubleWord Load(const Address addr, const LoadStoreSize size) {
    // Memory address space of RISC-V is circular.
    const auto addrAdjusted{(addr - RAM_BASE) % RAM_SIZE};
    switch (size) {
    case LoadStoreSize::Byte:
      return loadByte(addrAdjusted);
    case LoadStoreSize::HalfWord:
      return loadHalfWord(addrAdjusted);
    case LoadStoreSize::Word:
      return loadWord(addrAdjusted);
    case LoadStoreSize::DoubleWord:
      return loadDoubleWord(addrAdjusted);
    default:
      throw std::logic_error("Not supported LoadStoreSize" +
                             std::to_string(static_cast<Size>(size)));
    }
    // return m_memory[addrAdjusted] | m_memory[addrAdjusted + 1] << 8 |
    //        m_memory[addrAdjusted + 2] << 16 | m_memory[addrAdjusted + 3] <<
    //        24;
  }

  void Store(const Address addr, const Size size, const DoubleWord value) {
    // TODO: Implement different logic based on size
  }

private:
  DoubleWord loadByte(const Address addrAdjusted) {
    return static_cast<DoubleWord>(m_memory[addrAdjusted]);
  }

  DoubleWord loadHalfWord(const Address addrAdjusted) {
    return static_cast<DoubleWord>(m_memory[addrAdjusted]) |
           static_cast<DoubleWord>(m_memory[addrAdjusted + 1]) << 8;
  }

  DoubleWord loadWord(const Address addrAdjusted) {
    return static_cast<DoubleWord>(m_memory[addrAdjusted]) |
           static_cast<DoubleWord>(m_memory[addrAdjusted + 1]) << 8 |
           static_cast<DoubleWord>(m_memory[addrAdjusted + 2]) << 16 |
           static_cast<DoubleWord>(m_memory[addrAdjusted + 3]) << 24;
  }

  DoubleWord loadDoubleWord(const Address addrAdjusted) {
    return static_cast<DoubleWord>(m_memory[addrAdjusted]) |
           static_cast<DoubleWord>(m_memory[addrAdjusted + 1]) << 8 |
           static_cast<DoubleWord>(m_memory[addrAdjusted + 2]) << 16 |
           static_cast<DoubleWord>(m_memory[addrAdjusted + 3]) << 24 |
           static_cast<DoubleWord>(m_memory[addrAdjusted + 4]) << 32 |
           static_cast<DoubleWord>(m_memory[addrAdjusted + 5]) << 40 |
           static_cast<DoubleWord>(m_memory[addrAdjusted + 6]) << 48 |
           static_cast<DoubleWord>(m_memory[addrAdjusted + 7]) << 56;
  }

private:
  std::array<Byte, RAM_SIZE> m_memory;
};

int main(int argc, char **argv) { return 0; }
