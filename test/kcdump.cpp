/* 
 * File:   kcdump.cpp
 * Author: klaus
 *
 * Created on 6. Januar 2018, 08:50
 */

#include <cstdlib>
#include <regex>

#include "kcpolydb.h"

using namespace kyotocabinet ;

using namespace std;

int Usage()
    {
    fprintf(stderr, "%s\n", "Usage: dump <dbfile> [re]") ;
    return 1;
    }
/*
 * 
 */
int main(int argc, char** argv)
    {
    
    char * dbname ;
    const char * re = "." ;
    
    switch (argc)
        {
        case 3:
            re = argv[2] ;
        case 2:
            dbname = argv[1] ;
            break;
        default:
            return Usage() ;
        }
            

    PolyDB    * pDB = new PolyDB() ;

    if ( ! pDB -> open(dbname, PolyDB::OREADER) )
        {
        fprintf(stderr, "Cannot open %s\n", dbname) ;
        exit(1) ;
        }
    auto *pCursor = pDB -> cursor();
    pCursor->jump();
    while(true)
        {
        string key, val;
        auto rec = pCursor -> get(&key, &val, true);
        if ( ! rec )
            break;
        cout << key << ":" << val << "\n";
        }

    return 0;
    }

