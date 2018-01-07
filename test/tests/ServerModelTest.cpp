/*
 * File:   ServerModelTest.cpp
 * Author: ramst
 *
 * Created on 13.12.2012, 09:55:25
 */

#include "ServerModelTest.hpp"
#include "src/common/StrUtil.hpp"

#include <boost/filesystem.hpp>
using namespace boost::filesystem ;
using namespace std ;


CPPUNIT_TEST_SUITE_REGISTRATION(ServerModelTest);

/// Create a new SnapshotData object Test
ServerModelTest::ServerModelTest()
    {
    system("/usr/bin/rm /tmp/*.kch") ;
    m_pModel = NULL; // ground pointer
    }

ServerModelTest::~ServerModelTest()
    {
    clean();
    }

/// delete all pointers that may be there
void ServerModelTest::clean()
    {
    if ( m_pModel )
        {
        delete m_pModel ;
        m_pModel = NULL ;
        }
    }

/// setup a test - cleanup leftovers, create a test object
void ServerModelTest::setUp()
    {
    clean() ;
    m_pModel = new SnapshotServerModelKC () ;
    
    boost::property_tree::ptree test_settings 
            = m_pModel -> pt_from_json("{\"DBRoot\": \"/tmp\"}");
    m_pModel -> Provision(test_settings);
    }

/// teardown a test
void ServerModelTest::tearDown()
    {
    clean() ;
    }

/// basic test
void ServerModelTest::testBasic()
    {
    CPPUNIT_ASSERT_MESSAGE( "Test set up?" , m_pModel != NULL ) ;
    
    string sHandle = m_pModel -> create_handle() ;
    CPPUNIT_ASSERT_MESSAGE( "create_handle ok?" , sHandle.length() == 17 ) ;
    
    boost::property_tree::ptree pt, res ;
    
        {
        // Try missing args error response
        cerr << "Negativetest: missing arg 'subject' for SetClientHandle\n";
        pt = m_pModel -> pt_from_json ("{\"action\":\"set\"}") ;

        res = m_pModel -> SetClientHandle(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "Missing args gives error?" , res.find("ERROR") != res.not_found() ) ;
        }

    string sClientHandle ;
    string sSubject("cn=test") ;
        {
        // obtain a new handle
        cerr << "SetClientHandle: " << sSubject << "\n";
        pt = m_pModel -> pt_from_json ("{\"action\": \"set\", \"arg\": \"clienthandle\", \"subject\": \"cn=test\"}") ;

        res = m_pModel -> SetClientHandle(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "SetClientHandle gives no error?" , res.find("ERROR") == res.not_found() ) ;
        CPPUNIT_ASSERT_MESSAGE( "SetClientHandle yields handle?" , res.find("clienthandle") != res.not_found() ) ;
        sClientHandle = res.get<std::string>("clienthandle") ;
        cerr << "SetClientHandle: got handle " << sClientHandle << "\n";        
        }

        {
        // get handle
        cerr << "GetClientHandle: " << sSubject << "\n";
        pt = m_pModel -> pt_from_json ("{\"action\": \"get\", \"arg\": \"clienthandle\", \"subject\": \"cn=test\"}") ;

        res = m_pModel -> GetClientHandle(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "GetClientHandle gives no error?" , res.find("ERROR") == res.not_found() ) ;
        CPPUNIT_ASSERT_MESSAGE( "GetClientHandle yields handle?" , res.find("clienthandle") != res.not_found() ) ;
        std::string sClientHandle2 = res.get<std::string>("clienthandle") ;
        CPPUNIT_ASSERT_MESSAGE( "GetClientHandle got old handle?" , sClientHandle == sClientHandle2 ) ;
        cerr << "GetClientHandle: got " << sClientHandle2 << "\n";
        }

        std::string sSnapshotHandle ;
        {
        // add a snapshot
        cerr << "AddSnapshot: add with timestamp 131313 \n";
        std::string sJSON = std::string("{\"action\": \"add\", "
                            " \"arg\": \"snapshot\","
                            " \"timestamp\": 131313,"
                            " \"clienthandle\": \"") + sClientHandle + "\"}" ;
        pt = m_pModel -> pt_from_json (sJSON) ;

        res = m_pModel -> AddSnapshot(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshot gives no error?" , res.find("ERROR") == res.not_found() ) ;
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshot yields handle?" , res.find("snapshothandle") != res.not_found() ) ;
        sSnapshotHandle = res.get<std::string>("snapshothandle") ;
        cerr << "AddSnapshot: got handle " << sSnapshotHandle << "\n";
        }

        std::string sSnapshotPathHandle ;
        {
        cerr << "AddSnapshotPath:  add path test to " << sSnapshotHandle << "\n";
        // add a snapshot path
        std::string sJSON = std::string("{\"action\": \"add\", "
                            " \"arg\": \"snapshotpath\","
                            " \"path\": \"test\","
                            " \"clienthandle\": \"") + sClientHandle + "\"," 
                            " \"snapshothandle\": \""+ sSnapshotHandle + "\"}" ;
        pt = m_pModel -> pt_from_json (sJSON) ;

        res = m_pModel -> AddSnapshotPath(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshotPath gives no error?" , res.find("ERROR") == res.not_found() ) ;
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshotPath yields handle?" , res.find("pathhandle") != res.not_found() ) ;
        sSnapshotPathHandle = res.get<std::string>("pathhandle") ;
        cerr << "AddSnapshotPath:  got handle " << sSnapshotPathHandle << "\n";
        }

        {
        // add files to snapshot
        cerr << "AddSnapshotFiles:  add files to  " << sSnapshotPathHandle << "\n";
        std::string sJSON = std::string("{\"action\": \"add\", "
                            " \"arg\": \"snapshotfiles\","
                            " \"clienthandle\": \"") + sClientHandle + "\"," 
                            " \"pathhandle\": \"" + sSnapshotPathHandle + "\"," 
                            " \"snapshothandle\": \""+ sSnapshotHandle + "\"}" ;
        pt = m_pModel -> pt_from_json (sJSON) ;

        std::vector<std::string> sFiles, sMetas, sHandles ;
        sFiles.push_back("file1") ;
        sMetas.push_back("size1,mtime,perms");
        sFiles.push_back("file2") ;
        sMetas.push_back("size2,mtime,perms");
        sFiles.push_back("file3") ;
        sMetas.push_back("size3,mtime,perms");
        
        StrUtil::add_vector(pt, "filenames", sFiles);
        StrUtil::add_vector(pt, "filemetainfos", sMetas);

        res = m_pModel -> AddSnapshotFiles(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshotFiles gives no error?" , res.find("ERROR") == res.not_found() ) ;
        StrUtil::get_vector(res, "filehandles", sHandles);
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshotFiles yields handles?" , sHandles.size() == sFiles.size() ) ;
        
        cerr << "AddSnapshotFiles: got " << sHandles.size() << " handles, first:" <<sHandles[0] << "\n";

        }
        
        string sMySnapshotHandle ;
        {
        // get snapshots
        cerr << "GetSnapshots: for " << sClientHandle << "\n";
            
        std::string sJSON = std::string("{\"action\": \"get\", "
                            " \"arg\": \"snapshots\","
                            " \"clienthandle\": \"") + sClientHandle + "\"}" ;
        pt = m_pModel -> pt_from_json (sJSON) ;

        res = m_pModel -> GetSnapshots(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "GetSnapshots gives no error?" , res.find("ERROR") == res.not_found() ) ;
        vector<string> sSnapShots ;
        StrUtil::get_vector(res, "snapshots", sSnapShots) ;
        CPPUNIT_ASSERT_MESSAGE( "GetSnapshots gives handles?" , sSnapShots.size()>0 ) ;
        sMySnapshotHandle = sSnapShots[0] ;
        cerr << "GetSnapshots: got " << sSnapShots.size() << " shandles, first " << sSnapShots[0] << "\n";
        }

        string sPathHandle ;
        {
        // get snapshotpathes
        cerr << "GetSnapshotsPathes: for " << sMySnapshotHandle << "\n";
            
        std::string sJSON = std::string("{\"action\": \"get\", "
                            " \"arg\": \"snapshotpathes\","
                            " \"clienthandle\": \"") + sClientHandle + "\"," 
                            " \"snapshothandle\": \"" + sMySnapshotHandle + "\"}" ;
        pt = m_pModel -> pt_from_json (sJSON) ;

        res = m_pModel -> GetSnapshotPathes(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "GetSnapshotsPathes gives no error?" , res.find("ERROR") == res.not_found() ) ;
        //cerr << "GetSnapshotPathes: "; StrUtil::dump_pt(cerr, res);

        string sTS =  res.get("timestamp", "");
        CPPUNIT_ASSERT_MESSAGE( "GetSnapshotsPathes timestamp ok?" , sTS == "131313" ) ;
        
        vector<string> sPathes, sHandles ;
        StrUtil::get_vector(res, "patharray", sPathes) ;
        StrUtil::get_vector(res, "handlearray", sHandles) ;
        CPPUNIT_ASSERT_MESSAGE( "GetSnapshotsPathes gives handles?" , sPathes.size()>0 ) ;
        CPPUNIT_ASSERT_MESSAGE( "GetSnapshotsPathes gives all handles?" , sPathes.size() == sHandles.size() ) ;
        sPathHandle = sHandles[0];
        }

        {
        // get snapshotfiles
        cerr << "GetSnapshotsFiles: for " << sMySnapshotHandle << "\n";
            
        std::string sJSON = std::string("{\"action\": \"get\", "
                            " \"arg\": \"snapshotfiles\","
                            " \"clienthandle\": \"") + sClientHandle + "\"," 
                            " \"pathhandle\": \"" + sPathHandle + "\"," 
                            " \"snapshothandle\": \"" + sMySnapshotHandle + "\"}" ;
        pt = m_pModel -> pt_from_json (sJSON) ;

        res = m_pModel -> GetSnapshotFiles(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "GetSnapshotFiles gives no error?" , res.find("ERROR") == res.not_found() ) ;
        //cerr << "GetSnapshotFiles: "; StrUtil::dump_pt(cerr, res);

        vector<string> sFiles, sHandles, sMetas ;
        StrUtil::get_vector(res, "filenames", sFiles) ;
        StrUtil::get_vector(res, "filehandles", sHandles) ;
        StrUtil::get_vector(res, "filemetainfos", sMetas) ;
        CPPUNIT_ASSERT_MESSAGE( "GetSnapshots gives handles?" , sFiles.size()>2 ) ;
        CPPUNIT_ASSERT_MESSAGE( "GetSnapshots gives all handles 1?" , sFiles.size() == sHandles.size() ) ;
        CPPUNIT_ASSERT_MESSAGE( "GetSnapshots gives all handles 2?" , sFiles.size() == sMetas.size() ) ;
        }

        string sPathHandle2 ;
        {
        cerr << "AddSnapshotPath:  add path test2 to " << sSnapshotHandle << "\n";
        // add a snapshot path
        std::string sJSON = std::string("{\"action\": \"add\", "
                            " \"arg\": \"snapshotpath\","
                            " \"path\": \"test2\","
                            " \"clienthandle\": \"") + sClientHandle + "\"," 
                            " \"snapshothandle\": \""+ sSnapshotHandle + "\"}" ;
        pt = m_pModel -> pt_from_json (sJSON) ;

        res = m_pModel -> AddSnapshotPath(pt) ;
        cerr << "AddSnapshotPath: "; StrUtil::dump_pt(cerr, res);
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshotPath gives no error?" , res.find("ERROR") == res.not_found() ) ;
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshotPath yields handle?" , res.find("pathhandle") != res.not_found() ) ;
        string sSnapshotPathHandle = res.get<std::string>("pathhandle") ;
        cerr << "AddSnapshotPath:  got handle " << sSnapshotPathHandle << "\n";
        sPathHandle2 = sSnapshotPathHandle ;
        }

        {
        // add more files to snapshot, path 2
        cerr << "AddSnapshotFiles:  add files to  " << sSnapshotPathHandle << "\n";
        std::string sJSON = std::string("{\"action\": \"add\", "
                            " \"arg\": \"snapshotfiles\","
                            " \"clienthandle\": \"") + sClientHandle + "\"," 
                            " \"pathhandle\": \"" + sPathHandle2 + "\"," 
                            " \"snapshothandle\": \""+ sSnapshotHandle + "\"}" ;
        pt = m_pModel -> pt_from_json (sJSON) ;

        std::vector<std::string> sFiles, sMetas, sHandles ;
        sFiles.push_back("file4") ;
        sMetas.push_back("size4,mtime,perms");
        sFiles.push_back("file5") ;
        sMetas.push_back("size5,mtime,perms");
        sFiles.push_back("file6") ;
        sMetas.push_back("size6,mtime,perms");
        
        StrUtil::add_vector(pt, "filenames", sFiles);
        StrUtil::add_vector(pt, "filemetainfos", sMetas);

        res = m_pModel -> AddSnapshotFiles(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshotFiles gives no error?" , res.find("ERROR") == res.not_found() ) ;
        StrUtil::get_vector(res, "filehandles", sHandles);
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshotFiles yields handles?" , sHandles.size() == sFiles.size() ) ;
        
        cerr << "AddSnapshotFiles: got " << sHandles.size() << " handles, first:" <<sHandles[0] << "\n";

        }
        {
        // add more files to snapshot, path 1
        cerr << "AddSnapshotFiles:  add files to  " << sSnapshotPathHandle << "\n";
        std::string sJSON = std::string("{\"action\": \"add\", "
                            " \"arg\": \"snapshotfiles\","
                            " \"clienthandle\": \"") + sClientHandle + "\"," 
                            " \"pathhandle\": \"" + sSnapshotPathHandle + "\"," 
                            " \"snapshothandle\": \""+ sSnapshotHandle + "\"}" ;
        pt = m_pModel -> pt_from_json (sJSON) ;

        std::vector<std::string> sFiles, sMetas, sHandles ;
        sFiles.push_back("file4") ;
        sMetas.push_back("size4,mtime,perms");
        sFiles.push_back("file5") ;
        sMetas.push_back("size5,mtime,perms");
        sFiles.push_back("file6") ;
        sMetas.push_back("size6,mtime,perms");
        
        StrUtil::add_vector(pt, "filenames", sFiles);
        StrUtil::add_vector(pt, "filemetainfos", sMetas);

        res = m_pModel -> AddSnapshotFiles(pt) ;
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshotFiles gives no error?" , res.find("ERROR") == res.not_found() ) ;
        StrUtil::get_vector(res, "filehandles", sHandles);
        CPPUNIT_ASSERT_MESSAGE( "AddSnapshotFiles yields handles?" , sHandles.size() == sFiles.size()*2 ) ;
        
        cerr << "AddSnapshotFiles: got " << sHandles.size() << " handles, first:" <<sHandles[0] << "\n";

        }
        


        
    }

