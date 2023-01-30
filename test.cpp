#include "HashTable.h"
#include "spellcheck.h"
#include <iostream>
#include <cassert>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

vector<string> sVec( vector<string> vec )
{
    std::sort( vec.begin(), vec.end() );
    return vec;
}

void basicFunctionTest()
{
    cout << "entering basic Function Tests" << endl;

    HashTable ht;

    // "" is already in the hasttable
    ht.insert("");
    assert(ht.size() == 0);
    assert(ht.find("") == false);

    // test 1 insert
    ht.insert("human");
    assert(ht.size() == 1);

    assert(ht.find("human"));

    // test multiple inserts
    ht.insert( "vulcan" );
    ht.insert( "andorian" );
    ht.insert( "ferengi" );
    ht.insert( "cardassian" );
    ht.insert( "vorta" );
    ht.insert( "klingon" );

    // test load factor and size
    assert(ht.loadFactor() == (7.0 / 101));
    assert(ht.size() == 7);
  
    assert(ht.find( "vorta" ));
    assert(ht.find( "klingon" ));
    assert(ht.find( "vulcan" ));
    assert(ht.find( "cardassian" ));
    assert(ht.find( "andorian" ));
    assert(ht.find( "ferengi" ));

    // test multiple repeated inserts
    ht.insert( "vulcan" );
    ht.insert( "andorian" );
    ht.insert( "ferengi" );
    ht.insert( "vulcan" );

    // tests that the size has not changed
    assert(ht.size() == 7);

    cout << "entering basic Function Tests" << endl << endl;
}

void resizeTableTest()
{
    cout << "entering resize table Tests" << endl;

    HashTable ht(5);
    assert( ht.maxSize() == 11 );

    ht.insert( "cardassian" );
    ht.insert( "human" );
    ht.insert( "andorian" );
    ht.insert( "klingon" );
    ht.insert( "ferengi" );
    ht.insert( "vulcan" );
    ht.insert( "vorta" );

    assert( ht.loadFactor() == 7.0 / 11 );
    assert( ht.size() == 7 );

    assert( ht.find( "cardassian" ) );
    assert( ht.find( "human" ) );
    assert( ht.find( "andorian" ) );
    assert( ht.find( "klingon" ) );
    assert( ht.find( "ferengi" ) );
    assert( ht.find( "vulcan" ) );
    assert( ht.find( "vorta" ) );

    ht.insert( "bajoran" ); // should trigger resize

    assert( ht.size() == 8 );
    assert( ht.maxSize() == 23 );

    assert( ht.find( "cardassian" ) );
    assert( ht.find( "human" ) );
    assert( ht.find( "andorian" ) );
    assert( ht.find( "klingon" ) );
    assert( ht.find( "ferengi" ) );
    assert( ht.find( "vulcan" ) );
    assert( ht.find( "vorta" ) );
    ht.find("bajoran");
    assert( ht.find( "bajoran" ) );

    ht.insert( "klingon" );
    ht.insert( "ferengi" );
    ht.insert( "vulcan" );

    ht.insert( "borg" );
    ht.insert( "romulan" );

    assert( ht.find( "klingon" ) );
    assert( ht.find( "ferengi" ) );
    assert( ht.find( "vulcan" ) );

    assert( ht.find( "borg" ) );
    assert( ht.find( "romulan" ) );

    assert( ht.size() == 10 );
    cout << "finished resize table Tests" << endl << endl;
}

void givenFileTest()
{
    string filename = "wordlist1000.txt";
    ifstream fileStream( filename, ifstream::in );

    if( !fileStream.is_open() )
    {
        cout << "Unable to open file \"" << filename << "\"" << endl;
        return;
    }

    HashTable ht;
    string value;
    while( fileStream >> value ){
        ht.insert( value );
    }
    fileStream.close();

    ht.print();
}

void bigFileTest()
{
    cout << "entering Big fileTests" << endl;

    string filename = "words_alpha.txt";
    ifstream fileStream( filename, ifstream::in );

    if( !fileStream.is_open() )
    {
        cout << "Unable to open file \"" << filename << "\"" << endl;
        return;
    }

    HashTable ht;
    string value;
    while( fileStream >> value ){
        ht.insert( value );
        ht.find( value );
    }
    fileStream.close();
    cout << "exiting big file Tests" << endl << endl;
}

void Test()
{
    cout << "entering Tests" << endl;
    cout << "entering Tests" << endl << endl;
}

void missingLetterTest()
{
    HashTable ht;

    ht.insert( "xword" );
    ht.insert( "wxord" );
    ht.insert( "woxrd" );
    ht.insert( "worxd" );
    ht.insert( "wordx" );
    ht.insert( "different" );
    ht.insert( "wrd" );
    ht.insert( "ward" );
    ht.insert( "lord" );

    assert( missingLetter( ht, "word" ) == sVec( {"xword", "wxord", "woxrd", "worxd", "wordx"} ) );

    ht.insert( "word" );
    assert( missingLetter( ht, "word" ) == ( vector<string> ) {"word"} );

    assert( missingLetter( ht, "other" ) == ( vector<string> ) {} );
}


int main()
{
	// cout << "Setup done" << endl;

    // basicFunctionTest();
    // resizeTableTest();
    // givenFileTest();
    // missingLetterTest();
    // bigFileTest();
}