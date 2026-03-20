//========================================================
// James Bui & Kien Le & Tren Meckel
// November 2024
// mytests.cpp
// This file contains the tests cases for Hash classes and
// for the Set class
//========================================================
#include "customexceptions.hpp"
#include "HashMap.hpp"
#include "Hash.hpp"
#include "HashMapTree.hpp"
#include "Set.hpp"

#include <iostream>
using namespace std;

HashMap<int, int> createSampleHashMap();
HashMapTree<int, int> createSampleHashMapTree();
Set<int> createSampleSet();

// Pass or Fail Testing
void testHashMap();
void testHashMapTree();
void testSet();

// Testing functions for HashMap
bool testHashMapInsert();
bool testHashMapDel();
bool testHashMapAccessor();
bool testHashMapSearch();
bool testEdgeCasesHashMap();

// Testing functions for HashMapTree
bool testHashMapTreeInsert();
bool testHashMapTreeRemove();
bool testHashMapTreeAccessor();
bool testHashMapTreeSearch();
bool testEdgeCasesHashMapTree();

// Testing functions for Set
bool testSetInsert();
bool testSetRemove();
bool testSetSearch();
bool testEdgeCasesSet();

//==============================================================
// main
// Initiate testing by calling testing methods.
// PARAMETERS:
// - none
// RETURN VALUE:
// - 0
//==============================================================
int main()
{
    cout << "Testing HashMap:" << endl;
    testHashMap();

    cout << "Testing HashMapTree:" << endl;
    testHashMapTree();

    cout << "Testing Set:" << endl;
    testSet();

    return 0;
}

//==============================================================
// createSampleHashMap
// Creates and returns a sample HashMap with predefined key-value pairs.
// PARAMETERS:
// - none
// RETURN VALUE:
// - HashMap<int, int> with predefined key-value pairs
//==============================================================
HashMap<int, int> createSampleHashMap()
{
    HashMap<int, int> map(10);
    for (int i = 0; i < 20; i++)
    {
        map.insert(i, i * 10);
    };
    return map;
}

//==============================================================
// createSampleHashMapTree
// Creates and returns a sample HashMapTree with predefined key-value pairs.
// PARAMETERS:
// - none
// RETURN VALUE:
// - HashMapTree<int, string> with predefined key-value pairs
//==============================================================
HashMapTree<int, int> createSampleHashMapTree()
{
    HashMapTree<int, int> mapTree(10);
    for (int i = 0; i < 20; i++)
    {
        mapTree.insert(i, i * 10);
    };
    return mapTree;
}

//==============================================================
// createSampleSet
// Creates and returns a sample Set with predefined elements.
// PARAMETERS:
// - none
// RETURN VALUE:
// - Set<int> with predefined elements
//==============================================================
Set<int> createSampleSet()
{
    Set<int> set;
    for (int i = 0; i < 20; i++)
    {
        set.insert(i * 10);
    };
    return set;
}

//******************************************
//*************HASH MAP TESTING*************
//******************************************

//==============================================================
// testHashMapInsert
// Tests the insertion functionality of the HashMap.
// Verifies that elements can be inserted and the map size is updated correctly.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapInsert()
{
    HashMap<int, int> map = createSampleHashMap();

    // Test inserting
    map.insert(-10, 100);
    if (map.search(-10) == nullptr || map.search(-10)->second != 100)
    {
        cout << "Error: Insertion failed" << endl;
        return false;
    }

    // Test inserting an existing key (should update)
    map.insert(10, 500);
    if (map.search(10) == nullptr || map.search(10)->second != 500)
    {
        cout << "Error: Insertion failed for inserting an existing key" << endl;
        return false;
    }

    return true;
}

//==============================================================
// testHashMapDel
// Tests the deletion functionality of the HashMap.
// Verifies that elements can be deleted and the map size is updated correctly.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapDel()
{
    HashMap<int, int> map = createSampleHashMap();

    // Test del
    map.del(10);
    if (map.search(10) != nullptr)
    {
        cout << "Error: Deletion failed" << endl;
        return false;
    }

    // Check other keys
    for (int i = 0; i < 20; i++)
    {
        if (i != 10 && map.search(i) == nullptr)
        {
            cout << "Error: Other keys are missing after deletion" << endl;
            return false;
        }
    };

    // Attempt to access the deleted key and ensure it throws an exception
    try
    {
        map[20];
        cout << "Error: Access to deleted key did not throw an exception" << endl;
        return false;
    }
    catch (const key_exception &e)
    {
    }

    return true;
}

//==============================================================
// testHashMapAccessor
// Tests the operator[] functionality of the HashMap.
// Verifies that values can be accessed and modified correctly using the operator[].
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapAccessor()
{
    HashMap<int, int> map = createSampleHashMap();

    // Check if the values are correct using the operator[]
    if (map[10] != 100)
    {
        cout << "Error: Incorrect value" << endl;
        return false;
    }

    // Test accessing a non-existent key
    try
    {
        map[-10];
        cout << "Error: Access to deleted key did not throw an exception" << endl;
        return false;
    }
    catch (const key_exception &e)
    {
    }
    return true;
}

//==============================================================
// testHashMapSearch
// Tests the search functionality of the HashMap.
// Verifies that elements can be searched correctly, both existing and non-existing.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapSearch()
{
    HashMap<int, int> map = createSampleHashMap();

    // Test searching
    auto item = map.search(15);
    if (item == nullptr || item->second != 150)
    {
        cout << "Error: Search failed" << endl;
        return false;
    }

    // Test searching for a non-existent key
    item = map.search(60);
    if (item != nullptr)
    {
        cout << "Error: Search failed" << endl;
        return false;
    }

    return true;
}

//==============================================================
// testEdgeCasesHashMap
// Tests edge cases for the HashMap class.
// Verifies behavior for inserting, removing, and searching for elements in edge cases.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testEdgeCasesHashMap()
{
    // Test empty map search
    HashMap<int, int> emptyMap;
    if (emptyMap.search(10) != nullptr)
    {
        cout << "Error: Empty map failed" << endl;
        return false;
    }

    // Test collision handling
    HashMap<int, int> mapWithCollision(1);
    for (int i = 0; i < 20; i++)
    {
        mapWithCollision.insert(i, i * 10);
    };
    for (int i = 0; i < 20; i++)
    {
        if (mapWithCollision.search(i) == nullptr || mapWithCollision.search(i)->second != i * 10)
        {
            cout << "Error: Collision handling failed" << endl;
            return false;
        }
    }

    return true;
}

//******************************************
//***********HASH MAP TREE TESTING**********
//******************************************

//==============================================================
// testHashMapTreeInsert
// Tests the insertion functionality of the HashMapTree.
// Verifies that new elements can be inserted correctly and the map size is updated.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapTreeInsert()
{
    HashMapTree<int, int> mapTree = createSampleHashMapTree();

    // Test inserting a new element
    mapTree.insert(-1, -1);
    if (mapTree.search(-1) == nullptr || mapTree.search(-1)->second != -1)
    {
        cout << "Error: Insert failed" << endl;
        return false;
    }

    // Test inserting an existing key (should update)
    mapTree.insert(0, -1);
    if (mapTree.search(0) == nullptr || mapTree.search(0)->second != -1)
    {
        cout << "Error: Insert failed" << endl;
        return false;
    }
    return true;
}

//==============================================================
// testHashMapTreeRemove
// Tests the removal functionality of the HashMapTree.
// Verifies that elements can be removed and keys are inaccessible after removal.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapTreeRemove()
{
    HashMapTree<int, int> mapTree = createSampleHashMapTree();

    // Test removing an existing element
    mapTree.remove(2);
    if (mapTree.search(2) != nullptr)
    {
        cout << "Error: Remove failed" << endl;
        return false;
    }

    try
    {
        mapTree.remove(5);
    }
    catch (const key_exception &e)
    {
    }

    return true;
}

//==============================================================
// testHashMapTreeAccessor
// Tests the operator[] functionality of the HashMapTree.
// Verifies that values can be accessed and modified correctly using the operator[].
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapTreeAccessor()
{
    HashMapTree<int, int> mapTree = createSampleHashMapTree();
    // Test operator[]
    if (mapTree[2] != 20)
    {
        cout << "Error: Operator[] failed" << endl;
        return false;
    }

    // Test accessing a non-existent key
    try
    {
        int item = mapTree[-10];
        cout << "Error: Access to deleted key did not throw an exception" << endl;
        return false;
    }
    catch (const key_exception &e)
    {
    }

    return true;
}

//==============================================================
// testHashMapTreeSearch
// Tests the search functionality of the HashMapTree.
// Verifies that elements can be searched correctly, both existing and non-existing.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testHashMapTreeSearch()
{
    HashMapTree<int, int> mapTree = createSampleHashMapTree();

    // Test searching for existing elements
    for (int i = 0; i < 20; i++)
    {
        if (mapTree.search(i) != nullptr && mapTree.search(i)->second != i * 10)
        {
            cout << "Error: Search failed" << endl;
            return false;
        }
    }

    // Test searching for a non-existing element
    if (mapTree.search(-1) != nullptr)
    {
        cout << "Error: Search failed" << endl;
        return false;
    }

    return true;
}

//==============================================================
// testEdgeCasesHashMapTree
// Tests edge cases for the HashMapTree class.
// Verifies behavior for inserting, removing, and searching for elements in edge cases.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testEdgeCasesHashMapTree()
{
    HashMapTree<int, int> mapTree(1);
    for (int i = 0; i < 20; i++)
    {
        mapTree.insert(i, i * 10);
    };
    for (int i = 5; i <= 15; i++)
    {
        mapTree.remove(i);
    }
    return true;
}

//******************************************
//****************SET TESTING***************
//******************************************

//==============================================================
// testSetInsert
// Tests the insertion functionality of the Set.
// Verifies that elements can be inserted into the set and that duplicates are not allowed.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testSetInsert()
{
    Set<int> set = createSampleSet();

    // Test inserting a new element
    set.insert(-1);
    if (!set.search(-1))
    {
        cout << "Error: Insert failed" << endl;
        return false;
    }

    // Test inserting a duplicate element (should not insert it again)
    set.insert(0);

    return true;
}

//==============================================================
// testSetRemove
// Tests the removal functionality of the Set.
// Verifies that elements can be removed and the set size is updated correctly.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testSetRemove()
{
    Set<int> set = createSampleSet();

    // Test removing an existing element
    set.remove(10);
    if (set.search(10))
    {
        cout << "Error: Remove failed" << endl;
        return false;
    }

    // Test removing a non-existing element
    try
    {
        set.remove(-1);
    }
    catch (const key_exception &e)
    {
    }
    return true;
}

//==============================================================
// testSetSearch
// Tests the search functionality of the Set.
// Verifies that elements can be searched correctly, both existing and non-existing.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testSetSearch()
{
    Set<int> set = createSampleSet();

    // Test searching for existing elements
    for (int i = 0; i < 20; i++)
    {
        if (!set.search(i * 10))
        {
            cout << "Error: Search failed" << endl;
            return false;
        };
    };

    // Test searching for a non-existing element
    if (set.search(-1))
    {
        cout << "Error: Search failed" << endl;
        return false;
    }

    return true;
}

//==============================================================
// testEdgeCasesSet
// Tests edge cases for the Set class.
// Verifies behavior for inserting, removing, and searching for elements in edge cases.
// PARAMETERS:
// - none
// RETURN VALUE:
// - true if the test passes, false if it fails
//==============================================================
bool testEdgeCasesSet()
{
    // Test duplicate insertion
    Set<int> duplicateSet;
    duplicateSet.insert(10);
    duplicateSet.insert(10);

    // Attempt to remove the element twice
    duplicateSet.remove(10);
    try
    {
        duplicateSet.remove(10); // Second removal should fail
        cout << "Error: Duplicate element was removed twice" << endl;
        return false;
    }
    catch (...)
    {
    }
    return true;
}

//******************************************
//***********FAIL OR PASS TESTING***********
//******************************************

//==============================================================
// testHashMap
// Testing functions and respective outputs for HashMap class.
// Updates and outputs the tally of passed and failed tests.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
void testHashMap()
{
    struct TestResult
    {
        int passed;
        int failed;
    };

    TestResult hashMap_result = {0, 0};

    if (testHashMapInsert())
    {
        cout << "testHashMapInsert passed" << endl;
        hashMap_result.passed++;
    }
    else
    {
        cout << "testHashMapInsert failed" << endl;
        hashMap_result.failed++;
    }

    if (testHashMapDel())
    {
        cout << "testHashMapDel passed" << endl;
        hashMap_result.passed++;
    }
    else
    {
        cout << "testHashMapDel failed" << endl;
        hashMap_result.failed++;
    }

    if (testHashMapAccessor())
    {
        cout << "testHashMapAccessor passed" << endl;
        hashMap_result.passed++;
    }
    else
    {
        cout << "testHashMapAccessor failed" << endl;
        hashMap_result.failed++;
    }

    if (testHashMapSearch())
    {
        cout << "testHashMapSearch passed" << endl;
        hashMap_result.passed++;
    }
    else
    {
        cout << "testHashMapSearch failed" << endl;
        hashMap_result.failed++;
    }

    if (testEdgeCasesHashMap())
    {
        cout << "testEdgeCasesHashMap passed" << endl;
        hashMap_result.passed++;
    }
    else
    {
        cout << "testHashMapSearch failed" << endl;
        hashMap_result.failed++;
    }

    cout << "HashMap Tests Passed: " << hashMap_result.passed << endl;
    cout << "HashMap Tests Failed: " << hashMap_result.failed << endl;
    cout << endl;
}

//==============================================================
// testHashMapTree
// Testing functions and respective outputs for HashMapTree class.
// Updates and outputs the tally of passed and failed tests.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
void testHashMapTree()
{
    struct TestResult
    {
        int passed;
        int failed;
    };
    TestResult mapTree_result = {0, 0};

    if (testHashMapTreeInsert())
    {
        cout << "testHashMapTreeInsert passed" << endl;
        mapTree_result.passed++;
    }
    else
    {
        cout << "testHashMapTreeInsert failed" << endl;
        mapTree_result.failed++;
    }

    if (testHashMapTreeRemove())
    {
        cout << "testHashMapTreeRemove passed" << endl;
        mapTree_result.passed++;
    }
    else
    {
        cout << "testHashMapTreeRemove failed" << endl;
        mapTree_result.failed++;
    }

    if (testHashMapTreeAccessor())
    {
        cout << "testHashMapTreeOperator passed" << endl;
        mapTree_result.passed++;
    }
    else
    {
        cout << "testHashMapTreeRemove failed" << endl;
        mapTree_result.failed++;
    }

    if (testHashMapTreeSearch())
    {
        cout << "testHashMapTreeSearch passed" << endl;
        mapTree_result.passed++;
    }
    else
    {
        cout << "testHashMapTreeSearch failed" << endl;
        mapTree_result.failed++;
    }

    if (testEdgeCasesHashMapTree())
    {
        cout << "testEdgeCasesHashMapTree passed" << endl;
        mapTree_result.passed++;
    }
    else
    {
        cout << "testEdgeCasesHashMapTree failed" << endl;
        mapTree_result.failed++;
    }

    cout << "HashMapTree Tests Passed: " << mapTree_result.passed << endl;
    cout << "HashMapTree Tests Failed: " << mapTree_result.failed << endl;
    cout << endl;
}

//==============================================================
// testSet
// Testing functions and respective outputs for Set class.
// Updates and outputs the tally of passed and failed tests.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
void testSet()
{
    struct TestResult
    {
        int passed;
        int failed;
    };
    TestResult set_result = {0, 0};

    if (testSetInsert())
    {
        cout << "testSetInsert passed" << endl;
        set_result.passed++;
    }
    else
    {
        cout << "testSetInsert failed" << endl;
        set_result.failed++;
    }

    if (testSetRemove())
    {
        cout << "testSetRemove passed" << endl;
        set_result.passed++;
    }
    else
    {
        cout << "testSetRemove failed" << endl;
        set_result.failed++;
    }

    if (testSetSearch())
    {
        cout << "testSetSearch passed" << endl;
        set_result.passed++;
    }
    else
    {
        cout << "testSetSearch failed" << endl;
        set_result.failed++;
    }

    if (testEdgeCasesSet())
    {
        cout << "testEdgeCasesSet passed" << endl;
        set_result.passed++;
    }
    else
    {
        cout << "testEdgeCasesSet failed" << endl;
        set_result.failed++;
    }

    cout << "Set Tests Passed: " << set_result.passed << endl;
    cout << "Set Tests Failed: " << set_result.failed << endl;
    cout << endl;
};
