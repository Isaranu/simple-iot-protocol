var mongojs = require('mongojs');
var testdb = mongojs('testdb');

function read(){

  var mycollection = testdb.collection('testcol');

  mycollection.find({}, function(err, docs){
    if(err) return console.log(err);
    console.log(docs);
    process.exit();
  });

}

read();
