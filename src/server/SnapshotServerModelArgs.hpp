/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnapshotServerModelArgs.hpp
 * Author: klaus
 *
 * Created on 30. Dezember 2017, 23:42
 */

#ifndef SNAPSHOTSERVERMODELARGS_HPP
#define SNAPSHOTSERVERMODELARGS_HPP

static std::string sRequiredArgs = 
        "{"
            "\"SetClientHandle\": "
                "{\"subject\" :         \"string\" },"
            "\"GetClientHandle\": "
                "{\"subject\" :         \"string\" },"

            "\"GetSnapshots\": "
                "{\"clienthandle\" :    \"handle\" },"
            "\"GetSnapshotPathes\": "
                "{\"clienthandle\" :    \"handle\" ,"
                " \"snapshothandle\" :  \"handle\" },"
            "\"GetSnapshotFiles\": "
                "{\"clienthandle\" :    \"handle\" ,"
                " \"snapshothandle\" :  \"handle\" },"

            "\"AddSnapshot\": "
                "{\"clienthandle\" :    \"handle\" ,"
                " \"timestamp\" :       \"integer\" },"
            "\"AddSnapshotPath\": "
                "{\"clienthandle\" :    \"handle\" ,"
                " \"snapshothandle\" :  \"handle\" ,"
                " \"path\" :            \"string\" },"
            "\"AddSnapshotFiles\": "
                "{\"clienthandle\" :    \"handle\" ,"
                " \"snapshothandle\" :  \"handle\" ,"
                " \"pathhandle\" :      \"handle\" ,"
                " \"files\" :           \"array\" }"

        "}" ;
;

#endif /* SNAPSHOTSERVERMODELARGS_HPP */

