/*!
 *
 * Date: Jan 8 2018
 */


function generic_query(json_in, renderer){
        $.ajax({
            url:            'json',
            type:           'post',
            mimeType:       'application/json',
            data:           JSON.stringify(json_in),        
            dataType:       'json',
            headers:        {'Content-Type' : 'application/json'},
            success: function(data,status){
                        renderer(data) ;
                        },
            error: function(xhr, desc, err){
                            console.log(xhr);
                            console.log("Desc:"+desc+" Err:"+err);
                        }
            })
    };


function render_json(json_data)
    {
    $("#display").val(JSON.stringify(json_data));
    $(".clienthandle").val(json_data.clienthandle);
    enumerate_snapshots.clienthandle = json_data.clienthandle;
    dump_snapshot.clienthandle = json_data.clienthandle;
    dump_files.clienthandle = json_data.clienthandle;
    get_file.clienthandle = json_data.clienthandle;
    }

function render_snapshots(json_data)
    {
    $("#display").val(JSON.stringify(enumerate_snapshots) + JSON.stringify(json_data));
    $(".snapshothandle").val(json_data.snapshots[0]);
    dump_snapshot.snapshothandle = json_data.snapshots[0];
    dump_files.snapshothandle = json_data.snapshots[0];
    get_file.snapshothandle = json_data.snapshots[0];
    }

function render_snapshot(json_data)
    {
    $("#display").val(JSON.stringify(dump_snapshot) + "\n\n" + JSON.stringify(json_data));
    $(".pathhandle").val(json_data.handlearray[0]);
    dump_files.pathhandle = json_data.handlearray[0];
    get_file.pathhandle = json_data.handlearray[0];
    }

function render_files(json_data)
    {
    $("#display").val(JSON.stringify(dump_files) + "\n\n" + JSON.stringify(json_data));
    $(".filehandle").val(dl);
    get_file.filehandle = json_data.filehandles[0];

    var dl = "/dl" ;
    $("#dlfilehandle").val(json_data.filehandles[0]);
    $(".dl_file").attr("action", dl) ;

    var ul = "/ul" ;
    $("#ulfilehandle").val(json_data.filehandles[0]);
    $(".ul_file").attr("action", ul) ;

    }

function render_file(json_data)
    {
    $("#display").val(JSON.stringify(get_file) + "\n\n" + JSON.stringify(json_data));
    }
