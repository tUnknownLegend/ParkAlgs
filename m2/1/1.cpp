/*
 * Задача 1. Хеш-таблица *
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество,
удаления строки из множества и проверки принадлежности данной строки множеству.

 * Для разрешения коллизий используйте двойное хеширование.

 * Требования: В таблице запрещено хранение указателей на описатель элемента.

 * Формат входных данных *
Каждая строка входных данных задает одну операцию над множеством.
Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.

 * Тип операции  – один из трех символов:
+  означает добавление данной строки в множество;
-  означает удаление  строки из множества;
?  означает проверку принадлежности данной строки множеству.
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.
При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
*/

// best time & space  complexity - o(1)
// worst time & space complexity - o(n)

#include <iostream>
#include <vector>
#include <cassert>

#ifndef LOAD_FACTOR_SIZE
#define LOAD_FACTOR_SIZE 3 / 4
#endif

#ifndef LOAD_FACTOR_DELETED
#define LOAD_FACTOR_DELETED 3 / 4
#endif

#ifndef HASH_TABLE_INIT_SIZE
#define HASH_TABLE_INIT_SIZE 8
#endif

using std::vector;
using std::string;

enum TCellState {
    Empty,
    Key,
    Deleted
};

struct StringHasher {
    unsigned int operator()(const string &key) const {
        unsigned int hash = 0;
        for (char i: key)
            hash = hash * 137 + i;
        return hash;
    }
};

struct SubStringHasher {
    unsigned int operator()(const string &key, const unsigned int size) const {
        unsigned int hash = 0;
        for (unsigned int i = 0; i < key.length() && i < 3; ++i)
            hash = (hash * 67) + key[i];
        hash += 3;
        return (hash % 2 == 0 ? --hash : hash);
    }
};

template<class T, class H1, class H2>
class HashTable {
public:
    HashTable(int initSize, const H1 &_hasher, const H2 &_subHasher);

    ~HashTable() = default;

    bool Has(const T &key) const;

    bool Add(const T &key);

    bool Delete(const T &key);

private:
    struct HashTableCell {
        T Key;
        TCellState CellState;
        unsigned int Hash;

        HashTableCell() : CellState(Empty), Hash(110) {}

        HashTableCell(const T &key, unsigned int hash) :
                Key(key), CellState(Key), Hash(hash) {}
    };

    H1 hasher;
    H2 subHasher;

    vector<HashTableCell> table;
    unsigned int keysCount;
    unsigned int deletedKeysCount;

    void reHash(int size);
};

template<class T, class H1, class H2>
HashTable<T, H1, H2>::HashTable(int initSize, const H1 &_hasher, const H2 &_subHasher) :
        hasher(_hasher),
        subHasher(_subHasher),
        table(initSize, HashTableCell()),
        keysCount(0),
        deletedKeysCount(0) {}

template<class T, class H1, class H2>
bool HashTable<T, H1, H2>::Has(const T &key) const {
    unsigned int tempHasha = hasher(key);
    unsigned int hash1 = tempHasha % table.size();
    unsigned int hash2 = subHasher(key, table.size());

    for (int i = 0; i < table.size(); ++i) {
        tempHasha = (hash1 + i * hash2) % table.size();
        if (table[tempHasha].CellState == Empty)
            return false;

        if (table[tempHasha].CellState == Key && table[tempHasha].Key == key)
            return true;
    }
    return false;
}

template<class T, class H1, class H2>
bool HashTable<T, H1, H2>::Add(const T &key) {
    if (keysCount >= table.size() * LOAD_FACTOR_SIZE) {
        reHash(2 * table.size());
    }

    if (deletedKeysCount >= table.size() * LOAD_FACTOR_DELETED) {
        reHash(table.size());
    }

    unsigned int absHash = hasher(key);
    unsigned int hash1 = absHash % table.size();
    unsigned int hash2 = subHasher(key, table.size());
    unsigned int tempHasha = 0;
    unsigned int firstDeletedHash = 0;
    bool firstDeleted = false;

    for (unsigned int i = 0; i < table.size(); ++i) {
        tempHasha = (hash1 + i * hash2) % table.size();
        if (table[tempHasha].CellState == Empty) {
            ++keysCount;

            if (firstDeleted) {
                table[firstDeletedHash].Key = key;
                table[firstDeletedHash].Hash = absHash;
                table[firstDeletedHash].CellState = Key;
                --deletedKeysCount;
                return true;
            }

            table[tempHasha].Key = key;
            table[tempHasha].Hash = absHash;
            table[tempHasha].CellState = Key;
            return true;
        }

        if (table[tempHasha].CellState == Key) {
            if (table[tempHasha].Key == key)
                return false;

            continue;
        }

        if (table[tempHasha].CellState == Deleted && !firstDeleted) {
            firstDeleted = true;
            firstDeletedHash = tempHasha;
        }
    }
    return false;
}

template<class T, class H1, class H2>
bool HashTable<T, H1, H2>::Delete(const T &key) {
    unsigned int tempHasha = hasher(key);
    unsigned int hash1 = tempHasha % table.size();
    unsigned int hash2 = subHasher(key, table.size());

    for (unsigned int i = 0; i < table.size(); ++i) {
        tempHasha = (hash1 + i * hash2) % table.size();
        if (table[tempHasha].CellState == Empty)
            return false;

        if (table[tempHasha].CellState == Key && table[tempHasha].Key == key) {
            table[tempHasha].CellState = Deleted;
            ++deletedKeysCount;
            assert(deletedKeysCount <= table.size());
            --keysCount;
            return true;
        }
    }
    return false;
}

template<class T, class H1, class H2>
void HashTable<T, H1, H2>::reHash(const int size) {
    vector<HashTableCell> newTable(size, HashTableCell());
    unsigned int newHash = 0;
    unsigned int subNewHash = 0;
    unsigned int tempHash = 0;
    for (unsigned int i = 0; i < table.size(); ++i) {
        if (table[i].CellState == Key) {
            newHash = table[i].Hash % newTable.size();
            subNewHash = subHasher(table[i].Key, newTable.size());
            for (unsigned int j = 0;; ++j) {
                tempHash = (newHash + j * subNewHash) % newTable.size();
                if (newTable[tempHash].CellState == Empty) {
                    newTable[tempHash].Key = table[i].Key;
                    newTable[tempHash].CellState = Key;
                    newTable[tempHash].Hash = table[i].Hash;
                    break;
                }
            }
        }
    }
    table = std::move(newTable);
    deletedKeysCount = 0;
}

int main() {
    StringHasher h1;
    SubStringHasher h2;
    assert(HASH_TABLE_INIT_SIZE % 2 == 0 && HASH_TABLE_INIT_SIZE >= 4);
    HashTable<string, StringHasher, SubStringHasher> table(HASH_TABLE_INIT_SIZE, h1, h2);
    char operation;
    string word;
    while (std::cin >> operation >> word) {
        if (operation == '+')
            std::cout << (table.Add(word) ? "OK" : "FAIL") << std::endl;
        if (operation == '?')
            std::cout << (table.Has(word) ? "OK" : "FAIL") << std::endl;
        if (operation == '-')
            std::cout << (table.Delete(word) ? "OK" : "FAIL") << std::endl;
    }
    return 0;
}